#pragma once
#include <JuceHeader.h>

class DrawableButtonAdapted : public DrawableButton
{
public:
    //DrawableButtonAdapted();
    /** Creates a DrawableButtonAdapted.

        After creating one of these, use setImages() to specify the drawables to use.

        @param buttonName           the name to give the component
        @param buttonStyle          the layout to use

        @see ButtonStyle, setButtonStyle, setImages
    */
    DrawableButtonAdapted (const String& buttonName,
                    ButtonStyle buttonStyle);

    ~DrawableButtonAdapted(){};


    bool hitTest(int x, int y) override;

    void resized () override;

    /**
     * @brief getBoundingBox get the path used for hit-testing
     */
    Path getBoundingBox();

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


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrawableButtonAdapted)
};


