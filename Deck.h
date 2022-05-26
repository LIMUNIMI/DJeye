#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "MyLookAndFeel.h"


class Deck : public juce::Component
{

public:
    Deck();
    ~Deck();

    void paint (juce::Graphics&) override;
    void resized() override;
protected:
    Slider testSlider1;
    Slider testSlider2;
    MyLookAndFeel laf;

private:
    // TODO: meglio di un define in questo caso siccome c'è una divisione?
    static constexpr auto componentAngle = MathConstants<float>::twoPi/NUM_COMPONENTS;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)

};

