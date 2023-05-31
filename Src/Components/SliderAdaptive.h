#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"
/* A slider that hit-tests ina custom hitbox, it can be set to automatically deduce the Hitbox from its rotary parameters (pie shape)
 *
 * inoltre funziona sol con dehli bounds quadrati e non rettangolari (?)
*/

class SliderAdaptive : public juce::Slider
{
public:
    SliderAdaptive();
    ~SliderAdaptive(){}

    //TODO pensare se devo overridare entrambe o ne basta una: credo che servano entrambe
    //note: shadows the component's method
    void setRotaryParameters (RotaryParameters p) noexcept;

    //NOTE: shadows the component's method
    void setRotaryParameters (float startAngleRadians,
                              float endAngleRadians,
                              bool stopAtEnd) noexcept;

    /*NOTE:Note that for components on the desktop, this method will be ignored, because it's
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

    //TODO: usare gli smart pointers??
    void setImage (const Drawable* image);

    //NOTE i path vengono copiati in modoprofondo, quindi basta prenderli per ref
    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path& newHitBox);

    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path&& newHitBox);


    bool getAutoFitHitBoxToRotaryParameters() const;

    /**
     * @brief setAutoFitToRotaryParameters set if the Hitbox should bound automatically to the slider's rotary parameter (pie shape)
     */
    void setAutoFitHitBoxToRotaryParameters(bool newAutoFitToRotaryParameters);

    /**
     * @brief resizeHitBoxToFitRotaryParameters update the hit box to match the pie-shape delimited by the rotary parameters
     */
    void resizeHitBoxToFitRotaryParameters();
    bool getSnapToMiddleValue() const;
    void setSnapToMiddleValue(bool newSnapToMiddleValue);

    float getAccuracyPaddingRatio() const;
    void setAccuracyPaddingRatio(float newAccuracyPaddingRatio);


    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override;

    int getNumWheelTicksIgnored() const;
    void setNumWheelTicksIgnored(int newNumWheelTicksIgnored);

protected:

    /**
     * @brief MakeSliceWithPadding returns a path which is the slider slice, reduced by a padding
     * @param rectToFitIn rectangle where the pie shound be drawn. note this is the rectangle which whould be used for a full-circle pie
     * @param paddingSides the padding to remove from the rotParams to make the slice (note this is the reduction from each side)
     * @param paddingTopBottom the padding to remove from the inner-most and from the outer-most part of the slide (nothe this is the reduction from each side)
     * @return path representing the slider reduced by a padding
     */
    //TODO: forse va messa nelle utilities??
    Path MakeSlice(const Rectangle<float> &rectToFitIn,
                   const float paddingSides = 0,
                   const float paddingTopBottom = 0) const;


    /**
     * @brief resizeHitBoxToFitBounds update the hit box size to the bounds of this component
     * note that AutoFitToRotaryParameters should be set to false for this to work
     */
    void resizeHitBoxToFitBounds();

    /**
     * @brief updateHitBoxBounds calls resizeHitBoxToFitBounds() or resizeHitBoxToFitRotaryParameters() depending on the vaue of autoFitToRotaryParameters
     */
    void updateHitBoxBounds();

private:
    /**
     * @brief snapValue note that it snaps only when using velocitydrag, otherwise (like scrolling with mousewheel) it wouldn't move after snapping
     */
    double snapValue(double attemptedValue, DragMode dragMode) override;

    /**
     * @brief HitBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath HitBox;
    std::unique_ptr<Drawable> image;
    bool autoFitHitBoxToRotaryParameters = false;
    bool snapToMiddleValue = false;

    float accuracyPaddingRatio = 0;// so che questa proprietà c'è anche in drawablebuttonadaptive ma mi sembrava esagerato fare una calsse padre splo per questo parametro. boh forse serve un'interfaccia? TODO: pensa a sta roba

    int numWheelTicksIgnored   = 0;
    int wheelTickCounter        = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdaptive)
};

