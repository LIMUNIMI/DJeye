#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
/* A slider that hit-tests only in the pie shape of the slider's rotary parameters
 *
 * inoltre funziona sol con dehli bounds quadrati e non rettangolari (?)
*/
class SliderAdapted : public Slider
{
public:
    SliderAdapted();
    ~SliderAdapted(){};

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

    void paint(Graphics& g) override ;

    void resized () override;

    void mouseUp(const MouseEvent &) override;
    std::function<void()> onMouseUp;

    /** You can assign a lambda to this callback object to have it called when the slider detects a mouseUp. */

    /**
     * @brief getHitBox get the path used for hit-testing
     */
    Path getHitBox() const;

    /**
     * @brief resizeHitBoxToFitRotaryParameters update the bounding box to match the pie-shape delimited by the rotary parameters
     */
    void resizeHitBoxToFitRotaryParameters();

    //TODO: usare gli smart pointers??
    void setImage (const Drawable* image);

    //NOTA i path vengono copiati in modoprofondo, quindi basta prenderli per ref
    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path& newHitBox);

    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path&& newHitBox);


protected:

    /**
     * @brief MakeSliceWithPadding returns a path which is the slider slice, reduced by a padding
     * @param rectToFitIn rectangle where the pie shound be drawn. note this is the rectangle which whould be used for a full-circle pie
     * @param paddingSides the padding to remove from the rotParams to make the slice (note this is the reduction from each side)
     * @param paddingTopBottom the padding to remove from the inner-most and from the outer-most part of the slide (nothe this is the reduction from each side)
     * @return path representing the slider reduced by a padding
     */
    Path MakeSlice(const Rectangle<float> &rectToFitIn,
                   const float paddingSides = 0,
                   const float paddingTopBottom = 0) const;
private:
    //
    /**
     * @brief HitBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath HitBox;
    std::unique_ptr<Drawable> image;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdapted)
};

