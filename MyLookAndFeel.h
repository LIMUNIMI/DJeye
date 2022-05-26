#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

#define PRIMARY_COLOUR juce::Colours::blue
#define SECONDARY_COLOUR juce::Colours::aliceblue
#define SLIDER_TO_INNER_CIRCLE_RATIO 0.2f

#pragma once
#include <JuceHeader.h>

//in questo caso i parametri li teniamo qua perchè non devono essere utilizzati in varie classi, come quelli dei DSP
#define BORDER_WIDTH 1.5f
#define SCALE_TO_KNOB_RATIO 0.85f

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    MyLookAndFeel() {}

    void drawRotarySlider(Graphics& g,
        int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
        Slider&) override
    {

        const auto minDim = jmin(width,height);
        auto bounds = Rectangle<int> (x, y, minDim, minDim).toFloat().reduced (10);//TODO: rivedere questo reduced
        bounds.setCentre(width/2,height/2);//GCC traduce da solo /2 in *0.5? boh, credo di si

        // Draw outline
        Path outline;
        auto lineThickness = jmin (15.0f, (float) jmin (width, height) * 0.45f) * 0.1f;//TODO: aggiustare magic number
        outline.addPieSegment (bounds,rotaryStartAngle,rotaryEndAngle,SLIDER_TO_INNER_CIRCLE_RATIO);

        g.setColour (SECONDARY_COLOUR);
        g.strokePath (outline,PathStrokeType (lineThickness));

        // Draw value
        Path section;
        auto angle = jmap(sliderPosProportional,rotaryStartAngle,rotaryEndAngle);
        section.addPieSegment (bounds,rotaryStartAngle,angle,SLIDER_TO_INNER_CIRCLE_RATIO);

        g.setColour (PRIMARY_COLOUR);
        g.fillPath (section);
}
};
