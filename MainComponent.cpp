#include "MainComponent.h"

//TODO: aggiunge popup al right click che visualizza una barra di scorriemnnto (?)
//TODO: controlla se c'è qualcosa riguardo al rotary sensitivity della rotella -> non c'è
//TODO: finire mapping
//TODO: aggiungere f11 schermo intero (opppure avvia schermo intero di default?)
//TODO: aggiungere ctr+q e ctrl+w

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
