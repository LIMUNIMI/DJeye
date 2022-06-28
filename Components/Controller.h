#pragma once

#include <JuceHeader.h>
#include "../MyLookAndFeel.h"
#include "Deck.h"

//==============================================================================
/*
*/
class Controller  : public juce::Component
{
public:
    Controller();
    ~Controller() override;

    void paint (juce::Graphics&) override;
    void resized() override;

protected:
    void /*constexpr*/ sendMidi (const int noteNumber);
    void toggleZoom (/*const*/ Deck* deckToZoom);
    void /*constexpr*/ manageActionOnButton(const Button* button) ;

private:
    MyLookAndFeel laf;

    Deck deckSx;
    Deck deckDx;
    Deck* selectedDeck = &deckSx;

    std::unique_ptr<MidiOutput>  midiOut;

    ComponentAnimator animator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
