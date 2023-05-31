#pragma once
#include "MyLookAndFeel.h"


class MyLookAndFeelLoop : public MyLookAndFeel
{
public:
    MyLookAndFeelLoop(/*int NumComponents*/) {

    }

void drawRotarySlider(Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                      Slider& slider) override

{
    MyLookAndFeel::drawRotarySlider (g,x,y,width,height,sliderPosProportional,rotaryStartAngle,rotaryEndAngle,slider); //this sould be on the declaration
    auto nTicks = slider.getRange ().getLength ();
    g.setColour (juce::Colours::white);
    auto rect = Rectangle(0,0,20,20);
    rect.setCentre(slider.getLocalBounds ().getCentre ());
    auto normValue = slider.getValue ()/ nTicks;
    float angle = jmap((float)normValue, rotaryStartAngle, rotaryEndAngle);
//    rect.applyTransform(AffineTransform::rotation(angle).translated(bounds.getCentre()));
//    g.drawText ("1/2", rect, juce::Justification::centred, true);

}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLookAndFeelLoop)
    String sliderValueToBeatsDuration(int value){
        switch(value){
        case 0: return "1/8";
        case 1: return "1/4";
        case 2: return "1/2";
        case 3: return "1";
        case 4: return "2";
        case 5: return "4";
        case 6: return "8";
        }
    }
};
