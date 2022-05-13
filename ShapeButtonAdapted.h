#pragma once
#include <JuceHeader.h>

class ShapeButtonAdapted : public Button //: public ImageButton
{// dovuta reimplementare per implementare lo hittest che deve accedere allo shape
public:
    ShapeButtonAdapted (const juce::String& t, Colour n, Colour o, Colour d)
        : Button (t),
          normalColour   (n), overColour   (o), downColour   (d),
          normalColourOn (n), overColourOn (o), downColourOn (d),
          useOnColours(false),
          maintainShapeProportions (false),
          outlineWidth (0.0f)
    {
    }

    ~ShapeButtonAdapted() {}

    void setColours (Colour newNormalColour, Colour newOverColour, Colour newDownColour)
    {
        normalColour = newNormalColour;
        overColour   = newOverColour;
        downColour   = newDownColour;
    }

    void setOnColours (Colour newNormalColourOn, Colour newOverColourOn, Colour newDownColourOn)
    {
        normalColourOn = newNormalColourOn;
        overColourOn   = newOverColourOn;
        downColourOn   = newDownColourOn;
    }

    void shouldUseOnColours (bool shouldUse)
    {
        useOnColours = shouldUse;
    }

    void setOutline (Colour newOutlineColour, const float newOutlineWidth)
    {
        outlineColour = newOutlineColour;
        outlineWidth = newOutlineWidth;
    }

    void setBorderSize (BorderSize<int> newBorder)
    {
        border = newBorder;
    }

    void setShape (const Path& newShape,
                                            const bool resizeNowToFitThisShape,
                                            const bool maintainShapeProportions_,
                                            const bool hasShadow)
    {
        shape = newShape;
        maintainShapeProportions = maintainShapeProportions_;

        shadow.setShadowProperties (DropShadow (Colours::black.withAlpha (0.5f), 3, Point<int>()));
        setComponentEffect (hasShadow ? &shadow : nullptr);

        if (resizeNowToFitThisShape)
        {
            auto newBounds = shape.getBounds();

            if (hasShadow)
                newBounds = newBounds.expanded (4.0f);

            shape.applyTransform (AffineTransform::translation (-newBounds.getX(),
                                  -newBounds.getY()));

            setSize (1 + (int) (newBounds.getWidth()  + outlineWidth) + border.getLeftAndRight(),
                     1 + (int) (newBounds.getHeight() + outlineWidth) + border.getTopAndBottom());
        }

        repaint();
    }

    void paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        if (! isEnabled())
        {
            shouldDrawButtonAsHighlighted = false;
            shouldDrawButtonAsDown = false;
        }

        auto r = border.subtractedFrom (getLocalBounds())
                 .toFloat()
                 .reduced (outlineWidth * 0.5f);

        if (getComponentEffect() != nullptr)
            r = r.reduced (2.0f);

        if (shouldDrawButtonAsDown)
        {
            const float sizeReductionWhenPressed = 0.04f;

            r = r.reduced (sizeReductionWhenPressed * r.getWidth(),
                           sizeReductionWhenPressed * r.getHeight());
        }

        auto trans = shape.getTransformToScaleToFit (r, maintainShapeProportions);

        if      (shouldDrawButtonAsDown)        g.setColour (getToggleState() && useOnColours ? downColourOn   : downColour);
        else if (shouldDrawButtonAsHighlighted) g.setColour (getToggleState() && useOnColours ? overColourOn   : overColour);
        else                                    g.setColour (getToggleState() && useOnColours ? normalColourOn : normalColour);

        g.fillPath (shape, trans);

        if (outlineWidth > 0.0f)
        {
            g.setColour (outlineColour);
            g.strokePath (shape, PathStrokeType (outlineWidth), trans);
        }
    }

    //TODO: farlo funzionare
    bool hitTest(int x, int y) override
    {
        return shape.contains(x,y,0.1f);
    }

    void resized() override{
        auto bounds = getLocalBounds ();
        shape.scaleToFit (bounds.getX (),bounds.getY (),
                          bounds.getWidth (),bounds.getHeight (),true);
    }

private:
    //==============================================================================
    Colour normalColour,   overColour,   downColour,
           normalColourOn, overColourOn, downColourOn, outlineColour;
    bool useOnColours;
    DropShadowEffect shadow;
    Path shape;
    BorderSize<int> border;
    bool maintainShapeProportions;
    float outlineWidth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShapeButtonAdapted)
};
