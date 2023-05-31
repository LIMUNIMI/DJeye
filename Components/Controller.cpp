#include "Controller.h"

Controller::Controller()
{
#if JUCE_LINUX || JUCE_BSD || JUCE_MAC || JUCE_IOS || DOXYGEN
    midiOut = juce::MidiOutput::createNewDevice("DJEYE");
#else
    midiOut = juce::MidiOutput::openDevice("DJEYE"); //TODO: da testare
#endif

    if (midiOut){
        //TODO: eccezione
    }

    /*animator = Desktop::getInstance().getAnimator ();

//    auto image = ImageCache::getFromMemory (BinaryData::circleButton_png, BinaryData::circleButton_pngSize);
//    auto transp = Colours::transparentWhite;
//    buttonSx.setImages (false,true,true,image,1.0f,transp,nullptr,0.5f,transp,nullptr,1.0f,transp,0.8f);
//    buttonDx.setImages (false,true,true,image,1.0f,transp,nullptr,0.5f,transp,nullptr,1.0f,transp,0.8f);*/

    deckSx.onMouseEnter = [&] {toggleZoom (&deckSx);};
    deckDx.onMouseEnter = [&] {toggleZoom (&deckDx);};

    addAndMakeVisible(deckSx);
    addAndMakeVisible(deckDx);
    addAndMakeVisible(middleStrip);

    setLookAndFeel (&laf);
    setSize (500, 500);
}

Controller::~Controller()
{
    setLookAndFeel (nullptr);
}

void Controller::paint (juce::Graphics& /*g*/) {}

void Controller::resized()
{
    /*deckSx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    deckSx.setCentreRelative (0.25f,0.5f);

    deckDx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    deckDx.setCentreRelative (0.75f,0.5f);*/

    toggleZoom(selectedDeck);
}

void Controller::sendMidi(const int noteNumber)
{
    midiOut->sendMessageNow(juce::MidiMessage::noteOn (1, noteNumber, (juce::uint8) 100));
}

void Controller::toggleZoom(Deck* deckToZoom){

    // |---|-|---|
    // | s |m| d |

    auto area = getLocalBounds ();
    auto deckToUnZoom = deckToZoom == &deckDx ? &deckSx : &deckDx;
    auto boundsBig    = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*4/7)://2/3
                                                area.removeFromRight(getWidth()*4/7);
    auto boundsMiddle = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*1/7)://2/3
                                                area.removeFromRight(getWidth()*1/7);
    auto boundsSmall  = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*3/7)://1/3
                                                area.removeFromRight(getWidth()*3/7);

    boundsMiddle.reduce (0,DECK_MARGIN);

    animator.animateComponent(deckToUnZoom,boundsSmall.reduced (DECK_MARGIN),1,300,false,2,1);
    animator.animateComponent(deckToZoom,boundsBig.reduced (DECK_MARGIN),1,300,false,2,1);
    animator.animateComponent(&middleStrip,boundsMiddle,1,300,false,2,1);

}

/*
 * monitorare midi dal terminale
 * visualizzare lista porte:
 * aconnect -i -o -l
 * dump porta:
 * aseqdump -p [numeroporta]
*/

















