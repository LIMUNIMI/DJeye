#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

#define PRIMARY_COLOUR juce::Colours::darkblue
#define SECONDARY_COLOUR juce::Colours::aliceblue

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    MyLookAndFeel() {}

    void drawRotarySlider(Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          Slider&) override
    {

        //TODO: sfumatura radiale
        //TODO: bordo più spesso

        const auto minDim = jmin(width,height);
        auto bounds = Rectangle<int> (minDim, minDim).toFloat()/*.reduced (DECK_PADDING)*/;
        bounds.setCentre(width/2,height/2);//GCC traduce da solo /2 in *0.5? boh, credo di si

        // Draw outline
        Path outline;
        //const auto lineThickness = jmin (15.0f, (float) minDim * 0.45f) * 0.3f;//TODO: aggiustare magic numbers
        const auto lineThickness = SLIDER_PADDING*2;
        outline.addPieSegment (bounds.reduced(SLIDER_PADDING),rotaryStartAngle,rotaryEndAngle,INNER_CIRCLE_TO_SLIDER_RATIO);

        /*outline.closeSubPath ();
        g.setColour (Colours::red);
        g.drawRect (bounds);
        g.drawRect (bounds.reduced (SLIDER_MARGIN));
*/
        g.setColour (SECONDARY_COLOUR);
        g.strokePath (outline.createPathWithRoundedCorners (COMPONENT_CORNER_ROUNDING),PathStrokeType (lineThickness));//TODO: aggiustare magic numbers

        // Draw value
        Path section;
        const auto angle = jmap(sliderPosProportional,rotaryStartAngle,rotaryEndAngle);
        section.addPieSegment (bounds.reduced(SLIDER_PADDING),rotaryStartAngle,angle,INNER_CIRCLE_TO_SLIDER_RATIO);

        g.setColour (PRIMARY_COLOUR);
        g.fillPath (section.createPathWithRoundedCorners (COMPONENT_CORNER_ROUNDING));
    }

    //modificare drawDrawableButton? implementata in v2 oppure drawbuttonbackground?
    //oppure drawButtonBackground? in teoria no perchè solo i drawable li metto nel radiale,
    //che bordello, non so che fare se più bottoni devono avere forme diverse
    //usare shapebutton? problema sono uno shape

};
