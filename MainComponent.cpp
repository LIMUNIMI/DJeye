#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(hoverzoomtestWindow);
    //addAndMakeVisible (deck);
    setSize (600, 400);
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
    g.fillAll (Colours::greenyellow);
}


void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto minDim = jmin(getWidth (),getHeight());
    auto deckContainerRect = Rectangle {minDim,minDim};
    deckContainerRect.setCentre (getBounds ().getCentre ());
    deck.setBounds(deckContainerRect/*.reduced (DECK_MARGIN)*/);

    hoverzoomtestWindow.setBounds(getLocalBounds());
}
