/*
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

#if JUCE_INTEL
#define JUCE_SNAP_TO_ZERO(n)    if (! (n < -1.0e-8 || n > 1.0e-8)) n = 0;
#else
#define JUCE_SNAP_TO_ZERO(n)
#endif

iNASBAudioProcessor::iNASBAudioProcessor()
:
_numChannels            (1)     // dummy - will be set in prepareToPlay
,_numSamples			(1)     // dummy - will be set in prepareToPlay/processBlock
,_sampleRate			(1)     // dummy - will be set in prepareToPlay
,_thresholdLevel        (0.005) // highest absolute value of
,_lastUIWidth			(850)
,_lastUIHeight			(650)

{
    Reset(); // set parameter values
}

iNASBAudioProcessor::~iNASBAudioProcessor()
{
}

//-----------------------------------------------------------------------------
// P R E P A R E   T O   P L A Y
void iNASBAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // If sample rate/block size changes or straight after construction
    if (_numSamples != samplesPerBlock || _sampleRate != sampleRate)
    {
        _sampleRate  = sampleRate;
        _numSamples  = samplesPerBlock;
        _numChannels = getNumInputChannels();
    }
    
    _lagFilterAOutput = 0;
    _lagFilterBOutput = 0;
    
}


//-----------------------------------------------------------------------------
// P R O C E S S   B L O C K
void iNASBAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // _numSamples calculated each frame, as this can vary e.g. at the end of a looped region (frame size < host's block size)
    _numSamples = buffer.getNumSamples();
    AudioSampleBuffer monoInput(1,_numSamples); // auxiliary sum buffer
    float* extractorInput; // auxiliary sum buffer as float array
    
    float channelAStatus;
    float channelBStatus;
    float signal;
    
    // Gain values from dB to linear
    float gain = powf(10.0f, _gainIndB/20.f);   // input gain
    float gainA = powf(10.0f, _gainAIndB/20.f); // output A gain
    float gainB = powf(10.0f, _gainBIndB/20.f); // output B gain
    
    monoInput.clear(); // empty auxiliary sum channel
    
    for (int channel = 0; channel < _numChannels; ++channel)
    {
        buffer.applyGain(channel, 0, _numSamples, gain);
        monoInput.addFrom(0, 0, buffer, channel, 0, _numSamples);
    }
    
    
    // if buffer is non-silent
    if (monoInput.getMagnitude(0, _numSamples) > _thresholdLevel)
    {
        _frameCounter  = (_frameCounter + 1) % 10000;  // count number of active frames so far (reset at 9999)
        extractorInput = monoInput.getWritePointer(0); // convert AudioSampleBuffer to float*
        
        // TRAINING
        if (_inTraining)
        {
            // train classifier
            classifier.Train(extractorInput, _numSamples, _sampleRate, _trainOnChannelB);
            
            // send to whatever channel you want these in (i.e. follow label)
            if (_trainOnChannelB) // mute channel A and multiply channel B with gainB
            {
                buffer.clear(0, 0, _numSamples);            // mute left channel
                buffer.applyGain(1, 0, _numSamples, gainB); // apply gain to right channel
            }
            else                  // mute channel B and multiple channel A with gainA
            {
                buffer.applyGain(0, 0, _numSamples, gainA); // left channel
                buffer.clear(1, 0, _numSamples);            // mute right channel
            }
        }
        
        // NORMAL OPERATION
        else
        {
            // TRAINING NOT READY
            //...
            
            
            // TRAINING READY
            
            // Extract features + pass on to classifier
            _classRaw = classifier.Classify(extractorInput, _numSamples, _sampleRate);
            
            float rms = buffer.getRMSLevel(1, 0, _numSamples); // TEMP
            _classRaw = (rms > _threshold) ? 1.0f : 0.0f; // TEMP
            
            
            if (_spectralFeature==true)
            {
                signal = _classRaw;
            }
            else
            {
                signal = rms*4.0f;
                
            }
            
            
            if (_schmittFlag == 1)
            {
                if (signal < (0.5f-_hysteresis))
                {
                    _schmittFlag = 0;
                }
            }
            else
            {
                if (signal > (0.5f+_hysteresis))
                {
                    _schmittFlag = 1;
                }
            }
            
            if (_schmittFlag ==1 )
            {
                channelAStatus = 0.0;
                channelBStatus = 1.0;
            } else
            {
                channelAStatus = 1.0;
                channelBStatus = 0.0;
            }
            
            
            float channelALevel = _lagFilterAOutput*_lagFilterAOutput;
            float channelBLevel = _lagFilterBOutput*_lagFilterBOutput;

            
            buffer.applyGain(0, 0, _numSamples, channelALevel*gainA);
            buffer.applyGain(1, 0, _numSamples, channelBLevel*gainB);
            
            
            _lagFilterAOutput = (channelAStatus * _filterCoefficient2) + (_lagFilterAOutput * _filterCoefficient1);
            _lagFilterBOutput = (channelBStatus * _filterCoefficient2) + (_lagFilterBOutput * _filterCoefficient1);
            
        }
        
    }
    
}


//-----------------------------------------------------------------------------
// T O G G L E   T R A I N I N G
void iNASBAudioProcessor::ToggleTraining(bool trainOnChannelB)
{
    _frameCounter    = 0; // reset frame counter
    
    // if A was on and A clicked: switch training off
    // if A was on and B clicked: leave training on, switch to B
    // if B was on and B clicked: switch training off
    // if B was on and A clicked: leave training on, switch to A
    
    if (_inTraining) // if we were training
    {
        if (trainOnChannelB == _trainOnChannelB) // if same button clicked
        {
            // switch training off
            _inTraining = false;
        }
        else // if different button clicked
        {
            // leave training on but toggle channel
            _trainOnChannelB = !_trainOnChannelB;
        }
    }
    else // if not in training
    {
        _inTraining      = !_inTraining;    // toggle to 'In Training'
        _trainOnChannelB = trainOnChannelB; // set to channel A (false) or B (true)
    }
    
    
}

//-----------------------------------------------------------------------------
// F I N I S H :   P R E P A R E   C L A S S I F I E R
void iNASBAudioProcessor::PrepareClassifier()
{
    // train on collected examples
}


//-----------------------------------------------------------------------------
// R E S E T
void iNASBAudioProcessor::Reset()
{
    // unity gains
    _gainIndB   = 0.0f;
    _gainAIndB  = 0.0f;
    _gainBIndB  = 0.0f;
    
    _threshold  = 0.2f;
    _classRaw   = 0.5f; // start on the edge (between channel 0 and 1)
    _classBool  = false;
    _tauInMs    = 20.0f;
    calculateAlpha();
    _schmittFlag = 0;
    _hysteresis = 0.2;
    _inertia = 0.75;
    _filterCoefficient1 = _inertia;
    _filterCoefficient2 = 1.0-_filterCoefficient1;
    
    _inTraining = false;
    _trainOnChannelB = false;
    _trainingReady = false;
    _spectralFeature = false;
}

//-----------------------------------------------------------------------------
// S E T   T I M E   C O N S T A N T
void iNASBAudioProcessor::calculateAlpha()
{
    _alpha = expf(-1000.0f / (_sampleRate * _tauInMs));
}


//-----------------------------------------------------------------------------
//
void iNASBAudioProcessor::releaseResources()
{
    // When playback stops, you can use this to free up any spare memory, etc.
}


bool iNASBAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* iNASBAudioProcessor::createEditor()
{
    return new iNASBAudioProcessorEditor (this);
}


//==============================================================================
void iNASBAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // SAVE STATE INFO
    XmlElement xml("iNASB_XML");
    
    // Knobs
    xml.setAttribute("_gain"       ,_gainIndB);
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary(xml, destData);
}

void iNASBAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // LOAD STATE INFO
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    // make sure that it's actually our type of XML object..
    if(xmlState->hasTagName("iNASB_XML"))
    {
        
        // Knobs
        _gainIndB       = (float) xmlState->getDoubleAttribute("_gain",true);
        
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new iNASBAudioProcessor();
}

const String iNASBAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool iNASBAudioProcessor::silenceInProducesSilenceOut() const
{
    return true;
}

int iNASBAudioProcessor::getNumParameters()
{
    return _PARAMtotalNumParams;
}

float iNASBAudioProcessor::getParameter (int index) // externally accessible
{
    switch (index)
    {
        case _PARAMgain:            return (GetGainIndB());
        default:					return 0.0f;
    }
}

void iNASBAudioProcessor::setParameter (int index, float newValue) // externally accessible
{
    switch (index)
    {
        case _PARAMgain:
            SetGainIndB(newValue);
            break;
        default:
            break;
    }
}

const String iNASBAudioProcessor::getParameterName (int index) // externally accessible
{
    switch (index)
    {
        case _PARAMgain:            return "Gain (dB)";
        default:					break;
    }
    return String::empty;
}

const String iNASBAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

const String iNASBAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String iNASBAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool iNASBAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool iNASBAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool iNASBAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool iNASBAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

int iNASBAudioProcessor::getNumPrograms()
{
    return 0;
}

int iNASBAudioProcessor::getCurrentProgram()
{
    return 0;
}

void iNASBAudioProcessor::setCurrentProgram (int index)
{
}

const String iNASBAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void iNASBAudioProcessor::changeProgramName (int index, const String& newName)
{
}