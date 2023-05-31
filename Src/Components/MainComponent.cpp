#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(controller);
    setSize (1, 1);//just to give initial value
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
   g.fillAll (Colour::fromString (laf.colourDark));
}


void MainComponent::resized()
{
    controller.setBounds(getLocalBounds().reduced (CONTROLLLER_RECUCTION));
    //Desktop::getInstance().setKioskModeComponent(&controller, false);
}
