#pragma once

#include <JuceHeader.h>
#include "shapebuttonadaptedv2.h"
#include "ShapeButtonAdapted.h"
#include "MyLookAndFeel.h"

//==============================================================================
/*
*/
class hoverZoomTest  : public juce::Component
{
public:
    hoverZoomTest();
    ~hoverZoomTest() override;

    void paint (juce::Graphics&) override;
    void resized() override;

protected:
    void sendMidi (const int noteNumber);
    void toggleZoom (Button* buttonToZoom);
    void manageActionOnButton(Button* button);

private:
    MyLookAndFeel customTheme;

    //ImageButton buttonSx;
    //ImageButton buttonDx;
    DrawableButton buttonSx;
    DrawableButton buttonDx;
    Button* selectedButton;
    std::unique_ptr<MidiOutput>  midiOut;
    ComponentAnimator animator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (hoverZoomTest)
};
