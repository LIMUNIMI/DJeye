#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
/* A slider that hit-tests only in the pie shape of the slider's rotary parameters
 * volevo farlo in modo che ol bounding box fosse impostabile dall'esterno ma KISS
 * inoltre funziona sol con dehli bounds quadrati e non rettangolari
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

    /**
     * @brief getBoundingBox get the path used for hit-testing
     */
    Path getBoundingBox() const;

    /**
     * @brief resizeBoundingBoxToFitRotaryParameters update the bounding box to match the pie-shape delimited by the rotary parameters
     */
    void resizeBoundingBoxToFitRotaryParameters();

    //TODO: sbagliato usare un unique_ptr qui?
    void setImage (const Drawable* image);



protected:
    /**
     * @brief setBoundingBox set the new path for hit-testing
     */
    void setBoundingBox (const Path &newBoundingBox);

    /**
     * @brief MakeSliceWithPadding returns a path which is the slider slice, reduced by a padding
     * @param rectToFitIn rectangle where the pie shound be drawn. note this is the rectangle which whould be used for a full-circle pie
     * @param paddingSides the padding to remove from the rotParams to amke the slice (note this is the TOTAl reduction in radious
     * @param paddingTopBottom the padding to remove from the inner-most and from the outer-most part of the slide (nothe this is the TOTAL reduction in size, both from top and from bottom
     * @return path representing the slider reduced by a padding
     */
    Path MakeSlice(const Rectangle<float> &rectToFitIn,
                   const float paddingSides = 0,
                   const float paddingTopBottom = 0) const;
private:
    //
    /**
     * @brief boundingBox the component's path used for hit-testing
     * utilizzo un drawablepath invece che un path perchè è un component
     * => può essere messo come figlio del deck
     * => si muove da solo insieme la parent
     */
    DrawablePath boundingBox;

    std::unique_ptr<Drawable> normalImage;
    Drawable* currentImage = nullptr;
    //int edgeIndent = 3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdapted)
};

