#include "Deck.h"

Deck::Deck(){

    //setLookAndFeel (&laf);

    //testSlider.setRange (0, 10, 0);
    testSlider1.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    testSlider1.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    testSlider1.setRotaryParameters (0,componentAngle,true);
    addAndMakeVisible (testSlider1);

    testSlider2.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    testSlider2.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    testSlider2.setRotaryParameters (0,componentAngle,true);
    addAndMakeVisible (testSlider2);


    }

Deck::~Deck(){}

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::aliceblue);
}

void Deck::resized()
{
    auto minDim = jmin(getWidth (),getHeight());
    auto box = Rectangle (minDim,minDim).reduced (40);
    box.setCentre (getBounds ().getCentre ());

    testSlider1.setBounds(box);
    testSlider2.setBounds(box);
    testSlider2.setTransform (AffineTransform::rotation (componentAngle,box.getCentreX (),box.getCentreY ()));// da spostare fuori
    testSlider2.setTransform (AffineTransform::rotation (componentAngle,box.getCentreX (),box.getCentreY ()));// da spostare fuori
}

