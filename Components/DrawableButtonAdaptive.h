#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"

class DrawableButtonAdaptive : public juce::DrawableButton
{
public:
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
    /**
     * @brief Set the new path for hit-testing
     * note: paths are deep-copied
     */
    void setHitBox (const Path& newHitBox);
    /**
     * @brief Set the new path for hit-testing
     * note: paths are deep-copied
     */
    void setHitBox (const Path&& newHitBox);
    float getAccuracyPaddingRatio() const;
    void setAccuracyPaddingRatio(float newAccuracyPaddingRatio);

protected:
    /**
    * @brief Updates the hitbox bounds taking into consideration the accuracyPaddingRatio.
    * It gets automatically called when updating the hitbox, the accuracyPaddingRatio or the window is resized
    */
    void updateHitBoxBounds();


private:
    //
    /**
     * @brief HitBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath HitBox;
    float accuracyPaddingRatio = 0;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawableButtonAdaptive)
};


