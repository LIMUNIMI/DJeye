#include "Controller.h"

Controller::Controller():
    deckSx{*new std::vector<Deck::ComponentType> {
           Deck::Play,
           Deck::Seek,
           Deck::Cue,
           Deck::HPLPFilter,
           Deck::Volume,
           Deck::Loop}},
    deckDx{*new std::vector<Deck::ComponentType> {
           Deck::Play,
           Deck::HPLPFilter,
           Deck::Seek,
           }}
{
#if JUCE_LINUX || JUCE_BSD || JUCE_MAC || JUCE_IOS || DOXYGEN
    midiOut = juce::MidiOutput::createNewDevice("DJEYE");
#else
    midiOut = juce::MidiOutput::openDevice("DJEYE"); //TODO: da testare
#endif
    if (midiOut){
        //TODO: eccezione
    }


    //animator = Desktop::getInstance().getAnimator ();

    deckDx.onMouseEnter = [&] {toggleZoom (&deckDx);};
    deckSx.onMouseEnter = [&] {toggleZoom (&deckSx);};

    {// setup lambdas for deckSx
        int ch = 1;
        //TODO: quando azz note-off?
        deckSx.setComponentOnClick (Deck::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (Deck::ComponentType::Seek, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, val )); });
        deckSx.setComponentOnClick       (Deck::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (Deck::ComponentType::Cue, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, val)); });
        deckSx.setComponentOnClick       (Deck::ComponentType::Cue, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (Deck::ComponentType::HPLPFilter, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 22, val)); });
        deckSx.setComponentOnClick       (Deck::ComponentType::HPLPFilter, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 4, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (Deck::ComponentType::Volume, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 23, val)); });
        deckSx.setComponentOnClick       (Deck::ComponentType::Volume, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 5, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (Deck::ComponentType::Loop, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 24, val)); });
        deckSx.setComponentOnClick       (Deck::ComponentType::Loop, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127)); });
    }
    {// setup lambdas for deckDx
        auto ch = 2;
        //TODO: quando azz note-off?
        deckDx.setComponentOnClick (Deck::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (Deck::ComponentType::Seek, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, val )); });
        deckDx.setComponentOnClick       (Deck::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (Deck::ComponentType::Cue, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, val)); });
        deckDx.setComponentOnClick       (Deck::ComponentType::Cue, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (Deck::ComponentType::HPLPFilter, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 22, val)); });
        deckDx.setComponentOnClick       (Deck::ComponentType::HPLPFilter, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 4, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (Deck::ComponentType::Volume, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 23, val)); });
        deckDx.setComponentOnClick       (Deck::ComponentType::Volume, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 5, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (Deck::ComponentType::Loop, [&,ch](const int val){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 24, val)); });
        deckDx.setComponentOnClick       (Deck::ComponentType::Loop, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127)); });
    }//NOTE: these lambda initialization are separated to guarantee the flexibility of the components which can or cannot be included in the deck

    addAndMakeVisible(deckSx);
    addAndMakeVisible(deckDx);
    addAndMakeVisible(middleStrip);

    setLookAndFeel (&laf);
    setSize (800, 800);
}

Controller::~Controller()
{
    setLookAndFeel (nullptr);
}

void Controller::paint (juce::Graphics& g) {
    g.fillAll (Colours::aliceblue);
}

void Controller::resized()
{
    /*deckSx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    deckSx.setCentreRelative (0.25f,0.5f);

    deckDx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    deckDx.setCentreRelative (0.75f,0.5f);*/

    toggleZoom(selectedDeck);
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

    animator.animateComponent(deckToUnZoom,boundsSmall.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(deckToZoom,boundsBig.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(&middleStrip,boundsMiddle,1,111,false,0,1);

}


/*
 * monitorare midi da terminale
 * ~aconnect -i -o -l      // visualizzare lista porte
 * ~aseqdump -p [#porta]   //dump porta
*/

















