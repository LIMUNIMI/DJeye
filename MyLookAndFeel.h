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


    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                    const Slider::SliderStyle style, Slider& slider) override
        {
            auto sliderRadius = (float) getSliderThumbRadius (slider);

            bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());

            auto knobColour = slider.findColour (Slider::rotarySliderFillColourId)
                                    .withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                                    .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f);

            g.setColour (knobColour);

            if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
            {
                float kx, ky;

                if (style == Slider::LinearVertical)
                {
                    kx = (float) x + (float) width * 0.5f;
                    ky = sliderPos;
                    g.fillRect (Rectangle<float> (kx - sliderRadius, ky - 2.5f, sliderRadius * 2.0f, 5.0f));
                }
                else
                {
                    kx = sliderPos;
                    ky = (float) y + (float) height * 0.5f;
                    g.fillRect (Rectangle<float> (kx - 2.5f, ky - sliderRadius, 5.0f, sliderRadius * 2.0f));
                }
            }
            else
            {
                // Just call the base class for the demo
                LookAndFeel_V4::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            }
        }

};
