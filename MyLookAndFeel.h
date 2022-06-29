#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

#define PRIMARY_COLOUR juce::Colours::darkblue
#define SECONDARY_COLOUR juce::Colours::aliceblue

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    MyLookAndFeel() {

        auto baseColour = Colours::red;

        setColour (Slider::thumbColourId,               Colour::greyLevel (0.95f));
        setColour (Slider::textBoxOutlineColourId,      Colours::transparentWhite);
        setColour (Slider::rotarySliderFillColourId,    baseColour);
        setColour (Slider::rotarySliderOutlineColourId, Colours::white);
        setColour (Slider::trackColourId,               Colours::black);

        setColour (TextButton::buttonColourId,  Colours::white);
        setColour (TextButton::textColourOffId, baseColour);

        setColour (TextButton::buttonOnColourId, findColour (TextButton::textColourOffId));
        setColour (TextButton::textColourOnId,   findColour (TextButton::buttonColourId));
    }

    void drawRotarySlider(Graphics& g,
                          int /*x*/, int /*y*/, int width, int height,
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


    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                    float sliderPos, float minSliderPos, float maxSliderPos,
                                    const Slider::SliderStyle style, Slider& slider) override
        {
        g.fillAll (slider.findColour (Slider::backgroundColourId));

                if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
                {
                    Path p;

                    if (style == Slider::LinearBarVertical)
                        p.addRectangle ((float) x, sliderPos, (float) width, 1.0f + (float) height - sliderPos);
                    else
                        p.addRectangle ((float) x, (float) y, sliderPos - (float) x, (float) height);

                    auto baseColour = slider.findColour (Slider::rotarySliderFillColourId)
                                            .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                                            .withMultipliedAlpha (0.8f);

                    g.setColour (baseColour);
                    g.fillPath (p);

                    auto lineThickness = jmin (15.0f, (float) jmin (width, height) * 0.45f) * 0.1f;
                    g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
                }
                else
                {
                    drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
                    //drawLinearSliderThumb      (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
                }
        }



    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        auto sliderRadius = (float) getSliderThumbRadius (slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal())
        {
            auto iy = (float) y + (float) height * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r ((float) x - sliderRadius * 0.5f, iy, (float) width + sliderRadius, sliderRadius);
            auto onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        }
        else
        {
            auto ix = (float) x + (float) width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (ix, (float) y - sliderRadius * 0.5f, sliderRadius, (float) height + sliderRadius);
            auto onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillPath (off);
    }




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLookAndFeel)
};
