#pragma once

#include <JuceHeader.h>
#include "shapebuttonadaptedv2.h"
#include "ShapeButtonAdapted.h"
#include "MyLookAndFeel.h"
#include "Deck.h"

//==============================================================================
/*
*/
class hoverZoomTest  : public juce::Component
{
public:
    hoverZoomTest();
    ~hoverZoomTest() override;

    void paint (juce::Graphics&) override;
    void resized() override;

protected:
    void /*constexpr*/ sendMidi (const int noteNumber);
    void toggleZoom (/*const*/ Deck* deckToZoom);
    void /*constexpr*/ manageActionOnButton(const Button* button) ;

private:
    MyLookAndFeel customTheme;

    //ImageButton buttonSx;
    //ImageButton buttonDx;
    Deck deckSx;
    Deck deckDx;
    Deck* selectedDeck = &deckSx;
    std::unique_ptr<MidiOutput>  midiOut;

    ComponentAnimator animator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (hoverZoomTest)
};
