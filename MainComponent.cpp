#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()

//:button("test",juce::Colours::red,juce::Colours::darkred,juce::Colours::purple)
{

//    juce::Path buttonShape;
//    buttonShape.startNewSubPath (juce::Point<float> (10, 100));
//    buttonShape.lineTo (juce::Point<float> (50, 50));
//    buttonShape.quadraticTo(juce::Point<float>(100,125),juce::Point<float> (50,200));
//    buttonShape.lineTo (juce::Point<float> (10, 150));
//    buttonShape.closeSubPath();
//    buttonShape = buttonShape.createPathWithRoundedCorners (2);
//    button.setShape(buttonShape,true,true,true);
//    addAndMakeVisible(button);


    //a = new juce::Image();
    //juce::ImageButton::setImages(false,true,true,...,1.0f,juce::Colours::transparentBlack,null,0.5f,juce::Colours::transparentBlack,null,0.5f,juce::Colours::transparentBlack);

    //button.setImage
    addChildComponent(window,0);
    addAndMakeVisible(window);
    setSize (400, 300);
    setFramesPerSecond (60); // This sets the frequency of the update calls.
}


MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::update()
{
    // This function is called at the frequency specified by the setFramesPerSecond() call
    // in the constructor. You can use it to update counters, animate values, etc.
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g) //chiamata dopo il resized
{
    g.fillAll (juce::Colour(0x44ff0000));
//    juce::Path buttonShapeControl = juce::Path(button.getShape());
//    buttonShapeControl.applyTransform(AffineTransform::translation(100, 0));
//    g.setColour(Colour(0xffaaff00));
//    g.fillPath(buttonShapeControl);

}


void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    window.setBounds(getLocalBounds());
}
