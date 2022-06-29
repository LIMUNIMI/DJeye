#pragma once
#include "DrawableButtonAdaptive.h"
#include "SliderAdaptive.h"

class MiddleStrip : public juce::Component
{
public:
    MiddleStrip();

    void resized() override;

    void paint (Graphics &g) override;

private:
    DrawableButtonAdaptive browserButton;
    SliderAdaptiveSnap crossfader;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiddleStrip)
};

