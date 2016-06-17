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

#ifndef __PLUGINPROCESSOR_H_88534BAA__
#define __PLUGINPROCESSOR_H_88534BAA__

#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>
#include "Classifier.h"

class iNASBAudioProcessor  : public AudioProcessor
{
public:
    iNASBAudioProcessor();
    ~iNASBAudioProcessor();
    
    //==============================================================================
	// V S T   M E T H O D S

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    AudioProcessorEditor* createEditor();
	bool silenceInProducesSilenceOut() const;
	virtual double getTailLengthSeconds() const {return 0;};
    bool hasEditor() const;
    const String getName() const;
    int getNumParameters();
    float getParameter (int index);
    void setParameter (int index, float newValue);
    const String getParameterName (int index);
    const String getParameterText (int index);
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    bool acceptsMidi() const;
    bool producesMidi() const;
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

	//==============================================================================
	// E N U M S

	enum Parameters
	{
        _PARAMgain,
        _PARAMthreshold,
        _PARAMtau,
        _PARAMgainA,
        _PARAMgainB,
        _PARAMrouteA,
        _PARAMrouteB,
		_PARAMtotalNumParams
	};
    
    enum RoutingState
    {
        _channel0=0,    // route to first channel
        _channel1,      // route to second channel
        _none           // mute
    };

    //==============================================================================
	// O U R   M E T H O D S
    
    void Reset();
    void calculateAlpha();
    void ToggleTraining(bool trainOnChannelB);
    
    void PrepareClassifier();

private:

	// Accessors and mutators
    inline float    GetGainIndB();
    inline void     SetGainIndB(float gainIndB);
    inline float    GetThreshold();
    inline void     SetThreshold(float threshold);
    inline float    GetTauInMs();
    inline void     SetTauInMs(float tauInMs);
    inline float    GetAlpha();
    inline void     SetAlpha(float alpha);
    inline float    GetGainAIndB();
    inline void     SetGainAIndB(float gainAIndB);
    inline float    GetGainBIndB();
    inline void     SetGainBIndB(float gainBIndB);
    inline float    GetClassRaw();
    inline void     SetClassRaw(float classRaw);
    inline float    GetClassEMA();
    inline void     SetClassEMA(float classEMA);
    
    inline void     ForceReady();
    inline void     SetFeature(bool isSpectral);
    
    inline float    GetNumSamples();
    inline float    GetSampleRate();
    inline float    GetFrameCounter();
    
    
    // Simon's accessors and mutators
    inline int      GetSchmittFlag();
    inline void     SetSchmittFlag(int schmittFlag);
    
    inline float    GetHysteresis();
    inline void     SetHysteresis(float hysteresis);
    
    inline float    GetInertia();
    inline void     SetInertia(float inertia);
    
    
    // Parameters
	int	_numChannels;
	int	_numSamples;
    int _sampleRate;
    float _gainIndB;
    float _threshold;
    float _tauInMs;
    float _alpha;           // calculated in function of _tauInMs
    float _gainAIndB;       // output gain on channel A
    float _gainBIndB;       // output gain on channel B
    RoutingState _routeA;   // where does A route to
    RoutingState _routeB;   // where does B route to
    float _thresholdLevel;
    
    bool _inTraining;
    bool _trainOnChannelB;
    bool _trainingReady;
    bool _spectralFeature;

	bool _isFirstFrame;

	int _lastUIWidth, _lastUIHeight;
    
    // Auxiliary variables
    float _classRaw;
    float _classEMA;
    bool _classBool;
    int _frameCounter;
    Classifier classifier;
    
    // Simon's Variables
    int _schmittFlag;
    float _hysteresis;
    float _inertia;

    float _filterCoefficient1;
    float _filterCoefficient2;
    
    float _lagFilterAOutput;
    float _lagFilterBOutput;
    
	friend class iNASBAudioProcessorEditor;
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (iNASBAudioProcessor);
};

//============================================================================= 
// I N L I N E   F U N C T I O N S   C O D E   S E C T I O N 


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetGainIndB()
{
	return _gainIndB;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetGainIndB(float gainIndB)
{
	_gainIndB = gainIndB;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetThreshold()
{
    return _threshold;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetThreshold(float threshold)
{
    _threshold = threshold;
}

//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetTauInMs()
{
    return _tauInMs;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetTauInMs(float tauInMs)
{
    _tauInMs = tauInMs;
}

//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetAlpha()
{
    return _alpha;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetAlpha(float alpha)
{
    _alpha = alpha;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetGainAIndB()
{
    return _gainAIndB;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetGainAIndB(float gainAIndB)
{
    _gainAIndB = gainAIndB;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetGainBIndB()
{
    return _gainBIndB;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetGainBIndB(float gainBIndB)
{
    _gainBIndB = gainBIndB;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetClassRaw()
{
    return _classRaw;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetClassRaw(float classRaw)
{
    _classRaw = classRaw;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetClassEMA()
{
    return _classEMA;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetClassEMA(float classEMA)
{
    _classEMA = classEMA;
}

//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::ForceReady()
{
    _trainingReady = true;
}

//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetFeature(bool isSpectral)
{
    _spectralFeature = isSpectral;
}


//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetNumSamples()
{
    return _numSamples;
}

//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetSampleRate()
{
    return _sampleRate;
}

//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetFrameCounter()
{
    return _frameCounter;
}


inline int
iNASBAudioProcessor::GetSchmittFlag()
{
    return  _schmittFlag;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetSchmittFlag(int schmittFlag)
{
    _schmittFlag = schmittFlag;
}

//-----------------------------------------------------------------------------
//
inline float
iNASBAudioProcessor::GetHysteresis()
{
    return _hysteresis;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetHysteresis(float hysteresis)
{
    _hysteresis = hysteresis;
}


inline float
iNASBAudioProcessor::GetInertia()
{
    return _inertia;
}


//-----------------------------------------------------------------------------
//
inline void
iNASBAudioProcessor::SetInertia(float inertia)
{
    _inertia = inertia;
    _filterCoefficient1 = _inertia;
    _filterCoefficient2 = 1.0-_filterCoefficient1;
}


#endif  // __PLUGINPROCESSOR_H_88534BAA__
