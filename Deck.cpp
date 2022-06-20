#include "Deck.h"
#include "Utils.h"

Deck::Deck(){

    setLookAndFeel (&laf);

    //TODO: setMouseDragSensitivity
    {
        testSlider1.setSliderStyle (juce::Slider::RotaryVerticalDrag);
        testSlider1.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        //testSlider1.setRotaryParameters (-componentAngle/2,componentAngle/2,true);//l'angolo negativo lo fa arrabbiare
        testSlider1.setRotaryParameters (0,componentAngle,true);

        auto shape = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
        testSlider1.setImage (shape.get ());
        addAndMakeVisible (testSlider1);
    }

    {
        testSlider2.setSliderStyle (juce::Slider::RotaryVerticalDrag);
        testSlider2.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        testSlider2.setRotaryParameters (componentAngle+componentSeparationAngle, 2 * componentAngle + componentSeparationAngle,true);

        auto shape = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
        testSlider2.setImage (shape.get ());

        testSlider2.setDoubleClickReturnValue (true, 0.5f*testSlider2.getRange ().getLength ());
        addAndMakeVisible (testSlider2);
    }


}

Deck::~Deck(){
    setLookAndFeel (nullptr);
}

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::blueviolet);

    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim}/*.reduced (5)*/;//TODO: magic number 5
    componentsContainer.setCentre (getBounds ().getCentre ());

    g.drawRect (componentsContainer);
    //g.drawEllipse (componentsContainer.reduced (55).toFloat (),4.0f);

    /*
    g.setColour (Colours::blue);
    //g.drawRect (testSlider1.getBounds ());
    //g.drawRect (testSlider2.getBounds ());
    //g.fillPath (testSlider1.getBoundingBox ());
    //g.fillPath (testSlider2.getBoundingBox ());
    */
}

void Deck::resized()
{
    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim}.reduced (10);//TODO: magic number
    componentsContainer.setCentre (getBounds ().getCentre ());
    testSlider1.setBounds(componentsContainer);
    testSlider2.setBounds(componentsContainer);

    /*//https://it.wikipedia.org/wiki/Trasformazione_affine
    auto trasformVersoAlto = AffineTransform::translation (0,-COMPONENTS_SEPARATION);
    testSlider1.setTransform (trasformVersoAlto);
    testSlider2.setTransform (AffineTransform::rotation (componentAngle+componentSeparationAngle,componentsContainer.getCentreX (),componentsContainer.getCentreY ()));
    */

}

