#pragma once

#include <JuceHeader.h>
#include "shapebuttonadaptedv2.h"
#include "ShapeButtonAdapted.h"
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
    void toggleZoom (ShapeButtonAdaptedv2* buttonToZoom);
    void manageActionOnButton(ShapeButtonAdaptedv2* button);

private:

    ShapeButtonAdaptedv2 buttonSx;
    ShapeButtonAdaptedv2 buttonDx;
    ShapeButtonAdaptedv2* selectedButton;
    std::unique_ptr<MidiOutput>  midiOut;
    ComponentAnimator animator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (hoverZoomTest)
};
