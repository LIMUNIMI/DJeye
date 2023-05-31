#include "Controller.h"

Controller::Controller():
    deckSx{*new std::vector<ConfigurableContainer::ComponentType> {
           ConfigurableContainer::Play,
           ConfigurableContainer::Seek,
           ConfigurableContainer::Cue,
           ConfigurableContainer::HPLPFilter,
           ConfigurableContainer::Volume,
           ConfigurableContainer::Loop}},

    deckDx{*new std::vector<ConfigurableContainer::ComponentType> {
           ConfigurableContainer::Play,
           ConfigurableContainer::HPLPFilter,
           ConfigurableContainer::Seek}},

    middleStrip{*new std::vector<ConfigurableContainer::ComponentType> {
                ConfigurableContainer::Spacer,
                ConfigurableContainer::Browser,
                ConfigurableContainer::Spacer,
                //ConfigurableContainer::Spacer,
                ConfigurableContainer::Spacer,
                ConfigurableContainer::Crossfader,
                ConfigurableContainer::Spacer}}

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
//        deckSx.setComponentOnClick (ConfigurableContainer::ComponentType::Play, [&,ch]{

//            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));

//        });

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Seek, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Cue, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, value)); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Cue, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::HPLPFilter, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 22, value)); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::HPLPFilter, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 4, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Volume, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 23, value)); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Volume, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 5, (juce::uint8) 127)); });

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Loop, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 24, value)); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Loop, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127)); });
    }
    {// setup lambdas for deckDx
        auto ch = 2;
        //TODO: quando azz note-off?
        deckDx.setComponentOnClick (ConfigurableContainer::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Seek, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Cue, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, value)); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Cue, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::HPLPFilter, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 22, value)); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::HPLPFilter, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 4, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Volume, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 23, value)); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Volume, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 5, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Loop, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 24, value)); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Loop, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127)); });
    }
    {// setup lambdas for middleStrip
        auto ch = 2;
        //TODO: quando azz note-off?
        deckDx.setComponentOnClick (ConfigurableContainer::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Seek, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });
    }

    //NOTE: these lambda initialization are separated to guarantee the flexibility of the components which can or cannot be included in the deck

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
    g.fillAll (Colour::fromString (laf.colourDark));
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
    auto boundsVertical = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*1/7)://2/3
                                                  area.removeFromRight(getWidth()*1/7);
    auto boundsSmall  = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*3/7)://1/3
                                                area.removeFromRight(getWidth()*3/7);

    boundsVertical.reduce (0,DECK_MARGIN);

    animator.animateComponent(deckToUnZoom,boundsSmall.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(deckToZoom,boundsBig.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(&middleStrip,boundsVertical,1,111,false,0,1);

}


/*
 * monitorare midi da terminale
 * ~aconnect -i -o -l      // visualizzare lista porte
 * ~aseqdump -p [#porta]   // dump messaggi sulla porta
*/
