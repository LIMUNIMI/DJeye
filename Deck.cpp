#include "Deck.h"
#include "Utils.h"

Deck::Deck():
testButton ("megabottone",DrawableButton::ButtonStyle::ImageFitted){

    setLookAndFeel (&laf);
    //TODO: 1 Inserire i due deck nello zoom
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
        testSlider2.setRotaryParameters (componentAngle+componentSeparationAngle,
                                         2 * componentAngle + componentSeparationAngle, true);

        auto shape = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
        testSlider2.setImage (shape.get());//std::move(shape));

        testSlider2.setDoubleClickReturnValue (true, 0.5f*testSlider2.getRange ().getLength ());
        testSlider2.onMouseUp = []{DBG("slider2");};
        addAndMakeVisible (testSlider2);
    }

    {
        auto shape = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
        testButton.setImages (shape.get ());

        Path p;
        p.addEllipse (Rectangle<float>(0,0,1,1));
        //p.closeSubPath ();
        testButton.setHitBox (p);

        testButton.onClick = []{DBG("bottone");};
        addAndMakeVisible (testButton);
    }

}

Deck::~Deck(){
    setLookAndFeel (nullptr);
}

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::blueviolet);

    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim}.reduced (DECK_PADDING);
    componentsContainer.setCentre (getBounds ().getCentre ());

    g.setColour (Colours::blue);
    //g.fillPath (testButton.getHitBox ());
    //g.drawRect (testSlider1.getBounds ());
    //g.drawRect (testSlider2.getBounds ());
    //g.fillPath (testSlider2.getBoundingBox ());

}

void Deck::resized()
{
    /*auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim}.reduced (DECK_PADDING);
    componentsContainer.setCentre (getBounds ().getCentre ());
    testSlider1.setBounds(componentsContainer);
    testSlider2.setBounds(componentsContainer);*/
    auto minDim = jmin(getWidth (),getHeight());
    //deck is always square
    testSlider1.setBoundsInset (BorderSize((int)DECK_PADDING));
    testSlider2.setBoundsInset (BorderSize((int)DECK_PADDING));

    auto diametroDaTogliere = (1-INNER_CIRCLE_TO_SLIDER_RATIO)* minDim*0.5f;
    diametroDaTogliere += SEPARATION_TO_COMPONENT_DIMENSION_RATIO*diametroDaTogliere + DECK_PADDING;

    testButton.setBoundsInset (BorderSize((int)diametroDaTogliere));


    /*//https://it.wikipedia.org/wiki/Trasformazione_affine
    auto trasformVersoAlto = AffineTransform::translation (0,-COMPONENTS_SEPARATION);
    testSlider1.setTransform (trasformVersoAlto);
    testSlider2.setTransform (AffineTransform::rotation (componentAngle+componentSeparationAngle,componentsContainer.getCentreX (),componentsContainer.getCentreY ()));
    */

}

void Deck::mouseEnter(const MouseEvent &event)
{
    if (onMouseEnter) onMouseEnter();
}

void Deck::mouseExit(const MouseEvent &event)
{
    if (onMouseExit) onMouseExit();
}

