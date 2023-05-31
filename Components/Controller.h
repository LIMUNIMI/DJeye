#pragma once

#include <JuceHeader.h>
#include "../MyLookAndFeel.h"
#include "Deck.h"
#include "MiddleStrip.h"

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

private:
    MyLookAndFeel laf;

    Deck deckSx;
    Deck deckDx;
    Deck* selectedDeck = &deckSx;

    MiddleStrip middleStrip;

    std::unique_ptr<MidiOutput>  midiOut;

    ComponentAnimator animator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
