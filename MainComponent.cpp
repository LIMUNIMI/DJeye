#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(controller);
    setSize (600, 400);
    //setFramesPerSecond (60); // This sets the frequency of the update calls.
}


MainComponent::~MainComponent()
{
}

//==============================================================================
//void MainComponent::update()
//{
//    // This function is called at the frequency specified by the setFramesPerSecond() call
//    // in the constructor. You can use it to update counters, animate values, etc.
//}

//==============================================================================
void MainComponent::paint (juce::Graphics& g) //chiamata dopo il resized
{
    g.fillAll (Colours::greenyellow);
}


void MainComponent::resized()
{
    controller.setBounds(getLocalBounds());
}
