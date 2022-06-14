#include <JuceHeader.h>
#include "Parameters.h"
class SliderAdapted : public Slider
{
public:
    SliderAdapted();
    //TODO: decidere se fare uno sliderAdapted (che si adatta automaticamente) e quindi fare lo shading di setRotaryParameters
    // oppure fare uno sliderAdaptive, per il quale va chaimato ResizeBoundingBoxToFit() a mano dopo aver richiamato setRotaryParameters
    //TODO pensare se devo overridare entrambe o ne basta una
    void setRotaryParameters (RotaryParameters p) noexcept;

    void setRotaryParameters (float startAngleRadians,
                              float endAngleRadians,
                              bool stopAtEnd) noexcept;

    /*NOTA:Note that for components on the desktop, this method will be ignored, because it's
     *         not always possible to implement this behaviour on all platforms.
     *         non capisco bene che voldì*/
    bool hitTest (int x, int y) override;

    void resized () override;

    void setBoundingBox (Path newBoundingBox);

    Path getBoundingBox();

    void resizeBoundingBoxToFit();
    void moved();
protected:

private:
    Path boundingBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdapted)
};

