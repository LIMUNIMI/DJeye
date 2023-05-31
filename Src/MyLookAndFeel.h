#pragma once
#include <JuceHeader.h>
#include "Components/SliderAdaptive.h"
#include "Parameters.h"


class MyLookAndFeel : public LookAndFeel_V4
{
public:
    //https://0to255.com/7762f4

    //const String accentColour    = "";
    //const String colourDark      = "ff324399"; //sfondo
    const String colourDark      = "ff160970"; //sfondo
    const String colourLessDark  = "ff3213ee"; //icone slider
    const String colourLessLight = "ff8a7bf4"; //riempimento slider
    const String colourLight     = "ffbcb1fa"; //sfondo slider
    //slider sfondo non hover: a99bfa
    MyLookAndFeel(/*int NumComponents*/) {
        //numComponents = NumComponents;

        setColour (Slider::backgroundColourId,          Colour::fromString(colourLight));      //sfondo slider
        //setColour (Slider::trackColourId,               Colour::fromString(colourLight));
        setColour (Slider::thumbColourId,               Colour::fromString (colourLessDark));
        setColour (Slider::rotarySliderFillColourId,    Colour::fromString (colourLessLight)); //riempimento slider
        setColour (Slider::rotarySliderOutlineColourId, Colour::fromString (colourLight));    //bordo slider
        setColour(DrawableButton::backgroundOnColourId, Colours::transparentWhite);
        //setColour (DrawableButton::backgroundColourId,  Colours::transparentWhite);
        //        setColour (TextButton::buttonColourId,  Colours::white);
        //        setColour (TextButton::textColourOffId, Colours::white);
        //        setColour (TextButton::buttonOnColourId, findColour (TextButton::textColourOffId));
        //        setColour (TextButton::textColourOnId,   findColour (TextButton::buttonColourId));

    }

    MouseCursor getMouseCursorFor(Component& /*c*/) override{
#if DEBUG
        return MouseCursor(MouseCursor::StandardCursorType::CrosshairCursor);
#else
        return MouseCursor(MouseCursor::StandardCursorType::NoCursor);
#endif
    }

    void drawRotarySlider(Graphics& g,
                          int /*x*/, int /*y*/, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          Slider& slider) override
    {

        //TODO: sfumatura radiale (?)

        const auto minDim = jmin(width,height);
        auto bounds = Rectangle<int> (minDim, minDim).toFloat()/*.reduced (DECK_PADDING)*/;
        bounds.setCentre(width/2,height/2);//GCC traduce da solo /2 in *0.5? boh, credo di si

        {// Draw outline + background
            Path p;
            p.addPieSegment (bounds.reduced(SLIDER_PADDING),rotaryStartAngle,rotaryEndAngle,INNER_CIRCLE_TO_SLIDER_RATIO);

            auto colour = slider.findColour (Slider::backgroundColourId)
                    .withMultipliedSaturation (slider.isMouseOver () ? 0.7f : 1.4f);
//            DBG(colour.toString ());

            g.setColour (colour);
            g.fillPath (p.createPathWithRoundedCorners (COMPONENT_CORNER_ROUNDING));

            //const auto lineThickness = jmin (15.0f, (float) minDim * 0.45f) * 0.3f;//TODO: aggiustare magic numbers
            //const auto lineThickness = SLIDER_PADDING*2;
            //g.strokePath (outline.createPathWithRoundedCorners (COMPONENT_CORNER_ROUNDING),PathStrokeType (lineThickness));//TODO: aggiustare magic numbers
        }

        {// Draw value pie
            Path p;
            const auto angle = jmap(sliderPosProportional,rotaryStartAngle,rotaryEndAngle);

            SliderAdaptive *sliderA = dynamic_cast<SliderAdaptive*> (&slider);
            p.addPieSegment (bounds.reduced(SLIDER_PADDING),
                             sliderA->getSnapToMiddleValue()? angle-0.03 : rotaryStartAngle,
                             sliderA->getSnapToMiddleValue()? angle+0.03 : angle,
                             INNER_CIRCLE_TO_SLIDER_RATIO);

            auto colour = slider.findColour (Slider::rotarySliderFillColourId)
                    .withMultipliedSaturation (slider.isMouseOver () ? 0.8f : 1.4f);

            g.setColour (colour);
            g.fillPath (p.createPathWithRoundedCorners (COMPONENT_CORNER_ROUNDING));
        }
    }

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {

        if (style == Slider::LinearHorizontal)
        {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb      (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
        else
        {
            LookAndFeel_V4::drawLinearSlider (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    /**
    * @brief drawLinearSliderBackground draws the track of the lider
    */
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float sliderPos,
                                     float minSliderPos,
                                     float maxSliderPos,
                                     const Slider::SliderStyle style, Slider& slider) override
    {
        if (style == Slider::LinearHorizontal)
        {            
            auto colour = slider.findColour (Slider::backgroundColourId)
                    .withMultipliedSaturation (slider.isMouseOver () ? 1.0f : 1.3f);
            g.setColour (colour);

            Path backGround;
            backGround.addRoundedRectangle (slider.getLocalBounds (), COMPONENT_CORNER_ROUNDING);
            g.fillPath(backGround);

        }
        else{
            LookAndFeel_V4::drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos,
                                float minSliderPos,
                                float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override
    {

        if (style == Slider::LinearHorizontal)
        {
            auto thumb = Rectangle<float>(slider.getHeight()*0.2f,slider.getHeight());
            thumb.setCentre (sliderPos, slider.getLocalBounds ().getCentreY());

            Path roundedThumb;
            roundedThumb.addRoundedRectangle (thumb, COMPONENT_CORNER_ROUNDING/2);

            auto baseColour = slider.findColour (Slider::thumbColourId)
                    .withMultipliedSaturation (slider.isMouseOver () ? 1.0f : 1.3f);
            g.setColour (baseColour);
            g.fillPath  (roundedThumb);

            auto thumbLine = thumb;
            thumbLine.removeFromRight (thumb.getWidth ()/3.0f);
            thumbLine.removeFromLeft (thumb.getWidth ()/3.0f);
            auto baseColourLine = slider.findColour (Slider::rotarySliderFillColourId)
                    .withMultipliedSaturation (slider.isMouseOver () ? 1.0f : 1.3f);
            g.setColour (baseColourLine);
            g.fillRect (thumbLine);

        }
        else
        {
            LookAndFeel_V4::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    //    int getSliderThumbRadius (Slider& slider) override
    //    {
    //        return  slider.isHorizontal() ? static_cast<int> ((float) slider.getHeight() / 3)
    //                                      : static_cast<int> ((float) slider.getWidth()  / 3);
    //    }

    //    int getNumComponents() const{
    //        return numComponents;
    //    }


private:
    //int numComponents;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLookAndFeel)
};
