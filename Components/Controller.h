#pragma once
#include <JuceHeader.h>
#include "../MyLookAndFeel.h"
#include "Deck.h"
#include "VerticalStrip.h"
#include "BrowserWindow.h"

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
    void toggleZoom (Deck* deckToZoom);

private:

    MyLookAndFeel laf;

    Deck deckSx;
    Deck deckDx;
    Deck* selectedDeck = &deckSx;

    VerticalStrip middleStrip;

    std::unique_ptr<MidiOutput>  midiOut;

    ComponentAnimator animator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
