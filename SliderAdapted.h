#include <JuceHeader.h>
#include "Parameters.h"
/* A slider that hit-tests only in the pie shape of the slider's rotary parameters
 * volevo farlo in modo che fosse impostebile dall'esterno lo shape ma KISS
*/
class SliderAdapted : public Slider
{
public:
    SliderAdapted();

    //TODO pensare se devo overridare entrambe o ne basta una: credo che servano entrambe
    //note: shadows the component's method
    void setRotaryParameters (RotaryParameters p) noexcept;

    //note: shadows the component's method
    void setRotaryParameters (float startAngleRadians,
                              float endAngleRadians,
                              bool stopAtEnd) noexcept;

    /*NOTA:Note that for components on the desktop, this method will be ignored, because it's
     *         not always possible to implement this behaviour on all platforms.
     *         non capisco bene che voldì*/
    bool hitTest (int x, int y) override;

    void resized () override;

    /**
     * @brief getBoundingBox get the path used for hit-testing
     */
    Path getBoundingBox();

    /**
     * @brief resizeBoundingBoxToFitRotaryParameters update the bounding box to match the pie-shape delimited by the rotary parameters
     */
    void resizeBoundingBoxToFitRotaryParameters();
protected:
    /**
     * @brief setBoundingBox set the new path for hit-testing
     */
    void setBoundingBox (Path newBoundingBox);

private:
    //
    /**
     * @brief boundingBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath boundingBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdapted)
};

