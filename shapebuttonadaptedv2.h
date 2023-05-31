#pragma once
#include <JuceHeader.h>

class ShapeButtonAdaptedv2 : public ShapeButton{
public:
    ShapeButtonAdaptedv2 (const juce::String& t, Colour n, Colour o, Colour d)
    :ShapeButton(t,n,o,d)
    {
    }

    ~ShapeButtonAdaptedv2() override {}

    void setShape (const Path& newShape,
                   bool resizeNowToFitThisShape,
                   bool maintainShapeProportions,
                   bool hasDropShadow)
    {//lo so è una ladrata, non viene overridato il metodo superiore.
        clickableShape = newShape;
        ShapeButton::setShape(clickableShape,resizeNowToFitThisShape,maintainShapeProportions,hasDropShadow);
    }

    bool hitTest(int x, int y) override
    {
        //return ShapeButton::contains (x,y,1.0f);
        return clickableShape.contains (x,y,1.0f);
    }

    void resized() override{
        //overridato perchè il bottone in realtà non scala automaticamente lo shape che contiene
        auto bounds = getLocalBounds ();
        clickableShape.scaleToFit (bounds.getX (),bounds.getY (),
                          bounds.getWidth (),bounds.getHeight (),true);
    }

    Path& getShape (){
    return clickableShape;
    }

protected:
    Path clickableShape;

private:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShapeButtonAdaptedv2)
};

