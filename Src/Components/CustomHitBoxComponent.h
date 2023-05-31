#pragma once
#include <JuceHeader.h>

class CustomHitBoxComponent//: public juce::Component
{
public:
    CustomHitBoxComponent();
    ~CustomHitBoxComponent(){};

    //NOTE i path vengono copiati in modoprofondo, quindi basta prenderli per ref
    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path& newHitBox);

    /**
     * @brief setHitBox set the new path for hit-testing
     */
    void setHitBox (const Path&& newHitBox);

    /**
     * @brief getHitBox get the path used for hit-testing
     */
    Path getHitBox() const;

    float getAccuracyPaddingRatio() const;
    void setAccuracyPaddingRatio(float newAccuracyPaddingRatio);

    //bool hitTest (int x, int y) override;

protected:

    virtual void updateHitBoxBounds() = 0;

    /**
     * @brief HitBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath HitBox;
    float accuracyPaddingRatio = 0;
};

