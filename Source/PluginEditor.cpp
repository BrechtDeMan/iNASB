/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//LookAndFeelCustom* iNASBAudioProcessorEditor::customLookAndFeel = NULL;

//[/MiscUserDefs]

//==============================================================================
iNASBAudioProcessorEditor::iNASBAudioProcessorEditor (iNASBAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (gainSlider = new Slider ("new slider"));
    gainSlider->setRange (-24, 24, 0.01);
    gainSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    gainSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    gainSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    gainSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    gainSlider->addListener (this);

    addAndMakeVisible (thresholdSlider = new Slider ("new slider"));
    thresholdSlider->setRange (0, 1, 0.001);
    thresholdSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    thresholdSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    thresholdSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    thresholdSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    thresholdSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    thresholdSlider->addListener (this);

    addAndMakeVisible (labelAlpha = new Label ("new label",
                                               TRANS("[alpha]")));
    labelAlpha->setFont (Font (15.00f, Font::plain));
    labelAlpha->setJustificationType (Justification::centredLeft);
    labelAlpha->setEditable (false, false, false);
    labelAlpha->setColour (Label::textColourId, Colours::white);
    labelAlpha->setColour (TextEditor::textColourId, Colours::black);
    labelAlpha->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelClassEMA = new Label ("new label",
                                                  TRANS("[classEMA]")));
    labelClassEMA->setFont (Font (15.00f, Font::plain));
    labelClassEMA->setJustificationType (Justification::centredLeft);
    labelClassEMA->setEditable (false, false, false);
    labelClassEMA->setColour (Label::textColourId, Colours::white);
    labelClassEMA->setColour (TextEditor::textColourId, Colours::black);
    labelClassEMA->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelClassRaw = new Label ("new label",
                                                  TRANS("[classraw]")));
    labelClassRaw->setFont (Font (15.00f, Font::plain));
    labelClassRaw->setJustificationType (Justification::centredLeft);
    labelClassRaw->setEditable (false, false, false);
    labelClassRaw->setColour (Label::textColourId, Colours::white);
    labelClassRaw->setColour (TextEditor::textColourId, Colours::black);
    labelClassRaw->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gainASlider = new Slider ("new slider"));
    gainASlider->setRange (-12, 12, 0.1);
    gainASlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    gainASlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    gainASlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    gainASlider->setColour (Slider::textBoxTextColourId, Colours::white);
    gainASlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainASlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    gainASlider->addListener (this);

    addAndMakeVisible (gainBSlider = new Slider ("new slider"));
    gainBSlider->setRange (-12, 12, 0.1);
    gainBSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    gainBSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    gainBSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    gainBSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    gainBSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    gainBSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    gainBSlider->addListener (this);

    addAndMakeVisible (comboBoxA = new ComboBox ("new combo box"));
    comboBoxA->setEditableText (false);
    comboBoxA->setJustificationType (Justification::centredLeft);
    comboBoxA->setTextWhenNothingSelected (String::empty);
    comboBoxA->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBoxA->addItem (TRANS("1"), 1);
    comboBoxA->addItem (TRANS("2"), 2);
    comboBoxA->addItem (TRANS("None"), 3);
    comboBoxA->addListener (this);

    addAndMakeVisible (comboBoxB = new ComboBox ("new combo box"));
    comboBoxB->setEditableText (false);
    comboBoxB->setJustificationType (Justification::centredLeft);
    comboBoxB->setTextWhenNothingSelected (String::empty);
    comboBoxB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBoxB->addItem (TRANS("1"), 1);
    comboBoxB->addItem (TRANS("2"), 2);
    comboBoxB->addItem (TRANS("None"), 3);
    comboBoxB->addListener (this);

    addAndMakeVisible (trainAButton = new TextButton ("new button"));
    trainAButton->setButtonText (TRANS("Train A"));
    trainAButton->addListener (this);
    trainAButton->setColour (TextButton::buttonColourId, Colour (0xff650000));
    trainAButton->setColour (TextButton::buttonOnColourId, Colours::red);
    trainAButton->setColour (TextButton::textColourOnId, Colour (0xff6a5858));
    trainAButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (trainBButton = new TextButton ("new button"));
    trainBButton->setButtonText (TRANS("Train B"));
    trainBButton->addListener (this);
    trainBButton->setColour (TextButton::buttonColourId, Colour (0xff650000));
    trainBButton->setColour (TextButton::buttonOnColourId, Colours::red);
    trainBButton->setColour (TextButton::textColourOnId, Colour (0xff6a5858));
    trainBButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (finishButton = new TextButton ("new button"));
    finishButton->setButtonText (TRANS("Finish"));
    finishButton->addListener (this);
    finishButton->setColour (TextButton::buttonColourId, Colours::red);
    finishButton->setColour (TextButton::buttonOnColourId, Colours::red);
    finishButton->setColour (TextButton::textColourOnId, Colour (0xff6a5858));
    finishButton->setColour (TextButton::textColourOffId, Colours::white);

    addAndMakeVisible (labelSchmittFlag = new Label ("new label",
                                                     TRANS("[schmittFlag]")));
    labelSchmittFlag->setFont (Font (15.00f, Font::plain));
    labelSchmittFlag->setJustificationType (Justification::centredLeft);
    labelSchmittFlag->setEditable (false, false, false);
    labelSchmittFlag->setColour (Label::textColourId, Colours::white);
    labelSchmittFlag->setColour (TextEditor::textColourId, Colours::black);
    labelSchmittFlag->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (hysteresisSlider = new Slider ("new slider"));
    hysteresisSlider->setRange (0, 0.4, 0.001);
    hysteresisSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    hysteresisSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    hysteresisSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    hysteresisSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    hysteresisSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    hysteresisSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    hysteresisSlider->addListener (this);

    addAndMakeVisible (inertiaSlider = new Slider ("new slider"));
    inertiaSlider->setRange (0.7, 0.9, 0.001);
    inertiaSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    inertiaSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    inertiaSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    inertiaSlider->setColour (Slider::textBoxTextColourId, Colours::white);
    inertiaSlider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    inertiaSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    inertiaSlider->addListener (this);

    addAndMakeVisible (labelFrameSize = new Label ("new label",
                                                   TRANS("[numSamples]")));
    labelFrameSize->setFont (Font (15.00f, Font::plain));
    labelFrameSize->setJustificationType (Justification::centredLeft);
    labelFrameSize->setEditable (false, false, false);
    labelFrameSize->setColour (Label::textColourId, Colours::white);
    labelFrameSize->setColour (TextEditor::textColourId, Colours::black);
    labelFrameSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSampleRate = new Label ("new label",
                                                    TRANS("[sampleRate]")));
    labelSampleRate->setFont (Font (15.00f, Font::plain));
    labelSampleRate->setJustificationType (Justification::centredLeft);
    labelSampleRate->setEditable (false, false, false);
    labelSampleRate->setColour (Label::textColourId, Colours::white);
    labelSampleRate->setColour (TextEditor::textColourId, Colours::black);
    labelSampleRate->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelFrameCounter = new Label ("new label",
                                                      TRANS("[frameCounter]")));
    labelFrameCounter->setFont (Font (15.00f, Font::plain));
    labelFrameCounter->setJustificationType (Justification::centredLeft);
    labelFrameCounter->setEditable (false, false, false);
    labelFrameCounter->setColour (Label::textColourId, Colours::white);
    labelFrameCounter->setColour (TextEditor::textColourId, Colours::black);
    labelFrameCounter->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (featureToggleButton = new ToggleButton ("new toggle button"));
    featureToggleButton->setButtonText (TRANS("Spectral classification"));
    featureToggleButton->addListener (this);
    featureToggleButton->setColour (ToggleButton::textColourId, Colours::white);


    //[UserPreSize]
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 850, 290);
    //[/UserPreSize]

    setSize (600, 420);


    //[Constructor] You can add your own custom stuff here..

	UpdateInterfaceValues();

	//************************************ SET LOOKANDFEEL **********************************
//	if( customLookAndFeel == NULL )
//	{
//		customLookAndFeel = new LookAndFeelCustom();
//		LookAndFeel::setDefaultLookAndFeel (/*&*/customLookAndFeel);
//	}

	//***************************************************************************************

    startTimer (50);

    //[/Constructor]
}

iNASBAudioProcessorEditor::~iNASBAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainSlider = nullptr;
    thresholdSlider = nullptr;
    labelAlpha = nullptr;
    labelClassEMA = nullptr;
    labelClassRaw = nullptr;
    gainASlider = nullptr;
    gainBSlider = nullptr;
    comboBoxA = nullptr;
    comboBoxB = nullptr;
    trainAButton = nullptr;
    trainBButton = nullptr;
    finishButton = nullptr;
    labelSchmittFlag = nullptr;
    hysteresisSlider = nullptr;
    inertiaSlider = nullptr;
    labelFrameSize = nullptr;
    labelSampleRate = nullptr;
    labelFrameCounter = nullptr;
    featureToggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void iNASBAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff880909));

    g.setColour (Colour (0xffc04444));
    g.fillRoundedRectangle (12.0f, 217.0f, 340.0f, 127.0f, 10.000f);

    g.setColour (Colours::red);
    g.fillEllipse (42.0f, 79.0f, 88.0f, 88.0f);

    g.setColour (Colour (0xff2c333b));
    g.fillEllipse (58.0f, 95.0f, 56.0f, 56.0f);

    g.setColour (Colour (0xff650000));
    g.fillRoundedRectangle (54.0f, 6.0f, 342.0f, 40.0f, 10.000f);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 22.30f, Font::bold));
    g.drawText (TRANS("iNtelligent Audio Switch Box"),
                6, 13, 439, 24,
                Justification::centredTop, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("GAIN"),
                3, 55, 166, 30,
                Justification::centred, true);

    g.setColour (Colours::red);
    g.fillEllipse (181.0f, 79.0f, 88.0f, 88.0f);

    g.setColour (Colour (0xff2c333b));
    g.fillEllipse (197.0f, 95.0f, 56.0f, 56.0f);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("THRESHOLD"),
                142, 55, 166, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("dB"),
                2, 182, 166, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("alpha:"),
                18, 316, 75, 30,
                Justification::centredRight, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("class EMA:"),
                18, 268, 81, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("class raw:"),
                18, 244, 81, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 50.70f, Font::plain));
    g.drawText (TRANS("A >"),
                374, 227, 116, 42,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 50.70f, Font::plain));
    g.drawText (TRANS("B >"),
                374, 298, 116, 42,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("<DEBUG>"),
                44, 220, 81, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("Smtt Flag:"),
                18, 292, 81, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("HYSTERESIS"),
                287, 55, 166, 30,
                Justification::centred, true);

    g.setColour (Colours::red);
    g.fillEllipse (327.0f, 79.0f, 88.0f, 88.0f);

    g.setColour (Colour (0xff2c333b));
    g.fillEllipse (343.0f, 95.0f, 56.0f, 56.0f);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("INERTIA"),
                423, 55, 166, 30,
                Justification::centred, true);

    g.setColour (Colours::red);
    g.fillEllipse (463.0f, 79.0f, 88.0f, 88.0f);

    g.setColour (Colour (0xff2c333b));
    g.fillEllipse (479.0f, 95.0f, 56.0f, 56.0f);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("frame size:"),
                170, 244, 86, 30,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("sample rate:"),
                146, 268, 110, 30,
                Justification::centredRight, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain));
    g.drawText (TRANS("frame counter:"),
                146, 292, 110, 30,
                Justification::centredRight, true);

    //[UserPaint] Add your own custom painting code here..

    // Knob bounds
    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    g.drawText (String(gainSlider->getMinimum()),
                17, 151, 39, 30,
                Justification::centredRight, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    g.drawText (String(gainSlider->getMaximum()),
                112, 151, 39, 30,
                Justification::centredLeft, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    g.drawText (String(thresholdSlider->getMinimum()),
                159, 151, 39, 30,
                Justification::centredRight, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    g.drawText (String(thresholdSlider->getMaximum()),
                254, 151, 39, 30,
                Justification::centredLeft, true);


    // Version number
    String str("v ");
    str.append(JucePlugin_VersionString, 4);
    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 11.00f, Font::plain));
    g.drawText (str,
                189, 37, 54, 30,
                Justification::centredLeft, true);

    //[/UserPaint]
}

void iNASBAudioProcessorEditor::resized()
{
    gainSlider->setBounds (3, 82, 164, 102);
    thresholdSlider->setBounds (144, 82, 164, 102);
    labelAlpha->setBounds (96, 323, 56, 24);
    labelClassEMA->setBounds (95, 272, 56, 24);
    labelClassRaw->setBounds (95, 247, 56, 24);
    gainASlider->setBounds (467, 230, 65, 49);
    gainBSlider->setBounds (467, 299, 65, 49);
    comboBoxA->setBounds (519, 240, 49, 21);
    comboBoxB->setBounds (519, 305, 49, 21);
    trainAButton->setBounds (98, 365, 101, 45);
    trainBButton->setBounds (212, 365, 101, 45);
    finishButton->setBounds (326, 365, 186, 45);
    labelSchmittFlag->setBounds (95, 297, 56, 24);
    hysteresisSlider->setBounds (289, 82, 164, 102);
    inertiaSlider->setBounds (424, 82, 164, 102);
    labelFrameSize->setBounds (260, 246, 79, 24);
    labelSampleRate->setBounds (259, 272, 79, 24);
    labelFrameCounter->setBounds (259, 294, 79, 24);
    featureToggleButton->setBounds (456, 16, 120, 24);
    //[UserResized] Add your own custom resize handling here..
    getProcessor()->_lastUIWidth = getWidth();
    getProcessor()->_lastUIHeight = getHeight();
    //[/UserResized]
}

void iNASBAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    iNASBAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        ourProcessor->SetGainIndB(gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == thresholdSlider)
    {
        //[UserSliderCode_thresholdSlider] -- add your slider handling code here..
        ourProcessor->SetThreshold(thresholdSlider->getValue());
        //[/UserSliderCode_thresholdSlider]
    }
    else if (sliderThatWasMoved == gainASlider)
    {
        //[UserSliderCode_gainASlider] -- add your slider handling code here..
        ourProcessor->SetGainAIndB(gainASlider->getValue());
        //[/UserSliderCode_gainASlider]
    }
    else if (sliderThatWasMoved == gainBSlider)
    {
        //[UserSliderCode_gainBSlider] -- add your slider handling code here..
        ourProcessor->SetGainBIndB(gainBSlider->getValue());
        //[/UserSliderCode_gainBSlider]
    }
    else if (sliderThatWasMoved == hysteresisSlider)
    {
        //[UserSliderCode_hysteresisSlider] -- add your slider handling code here..
        ourProcessor->SetHysteresis(hysteresisSlider->getValue());

        //[/UserSliderCode_hysteresisSlider]
    }
    else if (sliderThatWasMoved == inertiaSlider)
    {
        //[UserSliderCode_inertiaSlider] -- add your slider handling code here..
        ourProcessor->SetInertia(inertiaSlider->getValue());
        //[/UserSliderCode_inertiaSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void iNASBAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBoxA)
    {
        //[UserComboBoxCode_comboBoxA] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBoxA]
    }
    else if (comboBoxThatHasChanged == comboBoxB)
    {
        //[UserComboBoxCode_comboBoxB] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBoxB]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void iNASBAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    iNASBAudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == trainAButton)
    {
        //[UserButtonCode_trainAButton] -- add your button handler code here..
        ourProcessor->ToggleTraining(false);
        //[/UserButtonCode_trainAButton]
    }
    else if (buttonThatWasClicked == trainBButton)
    {
        //[UserButtonCode_trainBButton] -- add your button handler code here..
        ourProcessor->ToggleTraining(true);
        //[/UserButtonCode_trainBButton]
    }
    else if (buttonThatWasClicked == finishButton)
    {
        //[UserButtonCode_finishButton] -- add your button handler code here..
        //[/UserButtonCode_finishButton]
    }
    else if (buttonThatWasClicked == featureToggleButton)
    {
        //[UserButtonCode_featureToggleButton] -- add your button handler code here..
        ourProcessor->SetFeature(featureToggleButton->getToggleState());
        //[/UserButtonCode_featureToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void iNASBAudioProcessorEditor::SetComboBoxActivity(ComboBox * comboBox, bool active)
{
	if (active){
		comboBox->setColour(ComboBox::backgroundColourId, Colours::white);
	}else{
		comboBox->setColour(ComboBox::backgroundColourId, Colours::grey);
	}
}

void iNASBAudioProcessorEditor::SetSliderActivity(Slider * slider, bool active)
{
	if (active){
		slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff5c00));
		slider->addListener (this);
	}else{
		slider->setColour (Slider::rotarySliderFillColourId, Colours::grey);
		slider->removeListener(this);
	}
}

void iNASBAudioProcessorEditor::UpdateInterfaceValues()
{
	iNASBAudioProcessor* ourProcessor = getProcessor();

    // Update Sliders
    gainSlider          ->setValue(ourProcessor->_gainIndB,dontSendNotification);
    thresholdSlider     ->setValue(ourProcessor->_threshold,dontSendNotification);
    hysteresisSlider    ->setValue(ourProcessor->_hysteresis,dontSendNotification);

    // Set alpha label
    labelAlpha->setText(String(ourProcessor->GetAlpha()), dontSendNotification);
    labelAlpha->setVisible(true);
}

// This timer periodically checks whether any of the parameters have changed...
void iNASBAudioProcessorEditor::timerCallback()
{
	iNASBAudioProcessor* ourProcessor = getProcessor();
    labelClassRaw       ->setText(String(ourProcessor->GetClassRaw()),      dontSendNotification);
    labelClassEMA       ->setText(String(ourProcessor->GetClassEMA()),      dontSendNotification);
    labelSchmittFlag    ->setText(String(ourProcessor->GetSchmittFlag()),   dontSendNotification);
    labelFrameSize      ->setText(String(ourProcessor->GetNumSamples()),    dontSendNotification);
    labelSampleRate     ->setText(String(ourProcessor->GetSampleRate()),    dontSendNotification);
    labelFrameCounter   ->setText(String(ourProcessor->GetFrameCounter()),  dontSendNotification);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="iNASBAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="iNASBAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="420">
  <BACKGROUND backgroundColour="ff880909">
    <ROUNDRECT pos="12 217 340 127" cornerSize="10" fill="solid: ffc04444" hasStroke="0"/>
    <ELLIPSE pos="42 79 88 88" fill="solid: ffff0000" hasStroke="0"/>
    <ELLIPSE pos="58 95 56 56" fill="solid: ff2c333b" hasStroke="0"/>
    <ROUNDRECT pos="54 6 342 40" cornerSize="10" fill="solid: ff650000" hasStroke="0"/>
    <TEXT pos="6 13 439 24" fill="solid: ffffffff" hasStroke="0" text="iNtelligent Audio Switch Box"
          fontname="Default monospaced font" fontsize="22.300000000000000711"
          bold="1" italic="0" justification="12"/>
    <TEXT pos="3 55 166 30" fill="solid: ffffffff" hasStroke="0" text="GAIN"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <ELLIPSE pos="181 79 88 88" fill="solid: ffff0000" hasStroke="0"/>
    <ELLIPSE pos="197 95 56 56" fill="solid: ff2c333b" hasStroke="0"/>
    <TEXT pos="142 55 166 30" fill="solid: ffffffff" hasStroke="0" text="THRESHOLD"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="2 182 166 30" fill="solid: ffffffff" hasStroke="0" text="dB"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="18 316 75 30" fill="solid: ffffffff" hasStroke="0" text="alpha:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="34"/>
    <TEXT pos="18 268 81 30" fill="solid: ffffffff" hasStroke="0" text="class EMA:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="18 244 81 30" fill="solid: ffffffff" hasStroke="0" text="class raw:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="374 227 116 42" fill="solid: ffffffff" hasStroke="0" text="A &gt;"
          fontname="Default monospaced font" fontsize="50.700000000000002842"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="374 298 116 42" fill="solid: ffffffff" hasStroke="0" text="B &gt;"
          fontname="Default monospaced font" fontsize="50.700000000000002842"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="44 220 81 30" fill="solid: ffffffff" hasStroke="0" text="&lt;DEBUG&gt;"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="18 292 81 30" fill="solid: ffffffff" hasStroke="0" text="Smtt Flag:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="287 55 166 30" fill="solid: ffffffff" hasStroke="0" text="HYSTERESIS"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <ELLIPSE pos="327 79 88 88" fill="solid: ffff0000" hasStroke="0"/>
    <ELLIPSE pos="343 95 56 56" fill="solid: ff2c333b" hasStroke="0"/>
    <TEXT pos="423 55 166 30" fill="solid: ffffffff" hasStroke="0" text="INERTIA"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <ELLIPSE pos="463 79 88 88" fill="solid: ffff0000" hasStroke="0"/>
    <ELLIPSE pos="479 95 56 56" fill="solid: ff2c333b" hasStroke="0"/>
    <TEXT pos="170 244 86 30" fill="solid: ffffffff" hasStroke="0" text="frame size:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="146 268 110 30" fill="solid: ffffffff" hasStroke="0" text="sample rate:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="34"/>
    <TEXT pos="146 292 110 30" fill="solid: ffffffff" hasStroke="0" text="frame counter:"
          fontname="Default monospaced font" fontsize="15" bold="0" italic="0"
          justification="34"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="b7cd5ae6d0a3bfc6" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="3 82 164 102" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="-24" max="24" int="0.010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="be2ae20f89114100" memberName="thresholdSlider"
          virtualName="" explicitFocusOrder="0" pos="144 82 164 102" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="0" max="1" int="0.0010000000000000000208" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="df915327158eed70" memberName="labelAlpha"
         virtualName="" explicitFocusOrder="0" pos="96 323 56 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[alpha]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="92426e7729ca72fb" memberName="labelClassEMA"
         virtualName="" explicitFocusOrder="0" pos="95 272 56 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[classEMA]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1464ac1c13716d9d" memberName="labelClassRaw"
         virtualName="" explicitFocusOrder="0" pos="95 247 56 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[classraw]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="e6fc9f99289e2282" memberName="gainASlider"
          virtualName="" explicitFocusOrder="0" pos="467 230 65 49" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="-12" max="12" int="0.10000000000000000555" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="bf1cb09997c54479" memberName="gainBSlider"
          virtualName="" explicitFocusOrder="0" pos="467 299 65 49" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="-12" max="12" int="0.10000000000000000555" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="new combo box" id="d00e3caa5e5442b3" memberName="comboBoxA"
            virtualName="" explicitFocusOrder="0" pos="519 240 49 21" editable="0"
            layout="33" items="1&#10;2&#10;None" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="88d7b9b87640815b" memberName="comboBoxB"
            virtualName="" explicitFocusOrder="0" pos="519 305 49 21" editable="0"
            layout="33" items="1&#10;2&#10;None" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="8d424731168649fa" memberName="trainAButton"
              virtualName="" explicitFocusOrder="0" pos="98 365 101 45" bgColOff="ff650000"
              bgColOn="ffff0000" textCol="ff6a5858" textColOn="ffffffff" buttonText="Train A"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="d1cfc4f5f055a059" memberName="trainBButton"
              virtualName="" explicitFocusOrder="0" pos="212 365 101 45" bgColOff="ff650000"
              bgColOn="ffff0000" textCol="ff6a5858" textColOn="ffffffff" buttonText="Train B"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="ac8b0deb16ecb50b" memberName="finishButton"
              virtualName="" explicitFocusOrder="0" pos="326 365 186 45" bgColOff="ffff0000"
              bgColOn="ffff0000" textCol="ff6a5858" textColOn="ffffffff" buttonText="Finish"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="65333b68838d6599" memberName="labelSchmittFlag"
         virtualName="" explicitFocusOrder="0" pos="95 297 56 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[schmittFlag]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="4f6ac4f05e036ab" memberName="hysteresisSlider"
          virtualName="" explicitFocusOrder="0" pos="289 82 164 102" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="0" max="0.4000000000000000222" int="0.0010000000000000000208"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="8eaa2fe3c02ce0fa" memberName="inertiaSlider"
          virtualName="" explicitFocusOrder="0" pos="424 82 164 102" rotarysliderfill="7fffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxoutline="808080"
          min="0.69999999999999995559" max="0.9000000000000000222" int="0.0010000000000000000208"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="67d72531100fc146" memberName="labelFrameSize"
         virtualName="" explicitFocusOrder="0" pos="260 246 79 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[numSamples]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="21e0ed9a90e7172e" memberName="labelSampleRate"
         virtualName="" explicitFocusOrder="0" pos="259 272 79 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[sampleRate]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d339818e3eb91ff" memberName="labelFrameCounter"
         virtualName="" explicitFocusOrder="0" pos="259 294 79 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="[frameCounter]"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="d8a68a6364d0af34" memberName="featureToggleButton"
                virtualName="" explicitFocusOrder="0" pos="456 16 120 24" txtcol="ffffffff"
                buttonText="Spectral classification" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
