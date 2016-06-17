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

#ifndef __JUCE_HEADER_76EC2134DC7A4B7C__
#define __JUCE_HEADER_76EC2134DC7A4B7C__

//[Headers]     -- You can add your own extra header files here --

//#include "../../Shared/LookAndFeelCustom.h" //used to be _nographics
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class iNASBAudioProcessorEditor  : public AudioProcessorEditor,
                                   public Timer,
                                   public SliderListener,
                                   public ComboBoxListener,
                                   public ButtonListener
{
public:
    //==============================================================================
    iNASBAudioProcessorEditor (iNASBAudioProcessor* ownerFilter);
    ~iNASBAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;

	//static LookAndFeelCustom* customLookAndFeel;

	AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;

    iNASBAudioProcessor* getProcessor() const
    {
        return static_cast <iNASBAudioProcessor*> (getAudioProcessor());
    }

    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);

	void UpdateInterfaceValues();

	void SetComboBoxActivity(ComboBox * comboBox, bool active);
	void SetSliderActivity(Slider * slider, bool active);


    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> gainSlider;
    ScopedPointer<Slider> thresholdSlider;
    ScopedPointer<Label> labelAlpha;
    ScopedPointer<Label> labelClassEMA;
    ScopedPointer<Label> labelClassRaw;
    ScopedPointer<Slider> gainASlider;
    ScopedPointer<Slider> gainBSlider;
    ScopedPointer<ComboBox> comboBoxA;
    ScopedPointer<ComboBox> comboBoxB;
    ScopedPointer<TextButton> trainAButton;
    ScopedPointer<TextButton> trainBButton;
    ScopedPointer<TextButton> finishButton;
    ScopedPointer<Label> labelSchmittFlag;
    ScopedPointer<Slider> hysteresisSlider;
    ScopedPointer<Slider> inertiaSlider;
    ScopedPointer<Label> labelFrameSize;
    ScopedPointer<Label> labelSampleRate;
    ScopedPointer<Label> labelFrameCounter;
    ScopedPointer<ToggleButton> featureToggleButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (iNASBAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_76EC2134DC7A4B7C__
