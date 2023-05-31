#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"

class DrawableButtonAdaptive : public DrawableButton
{
public:
    //DrawableButtonAdapted();
    /** Creates a DrawableButtonAdapted.

        After creating one of these, use setImages() to specify the drawables to use.

        @param buttonName           the name to give the component
        @param buttonStyle          the layout to use

        @see ButtonStyle, setButtonStyle, setImages
    */
    DrawableButtonAdaptive (const String& buttonName,
                    ButtonStyle buttonStyle);

    ~DrawableButtonAdaptive(){};


    bool hitTest(int x, int y) override;

    void resized () override;

    /**
     * @brief getHitBox get the path used for hit-testing
     */
    Path getHitBox() const noexcept;
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

private:
    //
    /**
     * @brief HitBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath HitBox;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawableButtonAdaptive)
};


