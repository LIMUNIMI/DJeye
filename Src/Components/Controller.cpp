#include "Controller.h"
//TODO: rendere unique pointer l'inizializzaizone: il problema è che la make unique nno trova il costruttore implicito
//oppure renderlo simile al funzionamento del parameterlayout?
Controller::Controller():
    deckSx{*new std::vector<ConfigurableContainer::ComponentType> {
           ConfigurableContainer::Play,
           ConfigurableContainer::Seek,
           //ConfigurableContainer::Cue,
           ConfigurableContainer::HeadphoneOut,
           ConfigurableContainer::HPLPFilter,
           ConfigurableContainer::Volume,
           ConfigurableContainer::Loop}},

    deckDx{*new std::vector<ConfigurableContainer::ComponentType> {
           ConfigurableContainer::Play,
           ConfigurableContainer::Seek,
           //ConfigurableContainer::Cue,
           ConfigurableContainer::HeadphoneOut,
           ConfigurableContainer::HPLPFilter,
           ConfigurableContainer::Volume,
           ConfigurableContainer::Loop}},

    middleStrip{*new std::vector<ConfigurableContainer::ComponentType> {
                ConfigurableContainer::Spacer,
                ConfigurableContainer::Browser,
                ConfigurableContainer::Spacer,
                ConfigurableContainer::Spacer,
                ConfigurableContainer::Crossfader,
                ConfigurableContainer::Spacer}}

/*                ConfigurableContainer::Spacer,
                  ConfigurableContainer::Crossfader,
                  ConfigurableContainer::Spacer,
                  ConfigurableContainer::Spacer,
                  ConfigurableContainer::ScrollUp,
                  ConfigurableContainer::Spacer,
                  ConfigurableContainer::ScrollDown,
                  ConfigurableContainer::Spacer,
                  ConfigurableContainer::Spacer,
                  ConfigurableContainer::Browser,
                  ConfigurableContainer::Spacer*/
{
    std::unique_ptr< MidiOutput > unique = nullptr;
#if JUCE_LINUX || JUCE_BSD || JUCE_MAC || JUCE_IOS || DOXYGEN
    unique = juce::MidiOutput::createNewDevice("DJEYE");
#else
    auto devices = juce::MidiOutput::getAvailableDevices();
    for (int i = 0; i <= devices.indexOf(devices.getLast()); i++) {
        if (devices[i].name == "DJEYE")
            unique = juce::MidiOutput::openDevice(devices[i].identifier);
    }
#endif
    if(unique == nullptr){
        DBG("unable to open/create port");
        return;
    }
    midiOut = std::move(unique);

    //animator = Desktop::getInstance().getAnimator ();

    deckDx.onMouseEnter = [&] {toggleZoom (&deckDx);};
    deckSx.onMouseEnter = [&] {toggleZoom (&deckSx);};

    {// setup lambdas for deckSx
        int ch = 1;
        //TODO: quando azz note-off? mai heheheh
        deckSx.setComponentOnClick (ConfigurableContainer::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));});

        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Seek, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

//        deckSx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Cue, [&,ch](const int value){
//            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, value)); });
//        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::Cue, [&,ch]{
//            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

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
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127));
            midiOut->sendMessageNow(juce::MidiMessage::noteOff         (ch, 6, (juce::uint8) 127));
            deckSx.toggleComponentAlpha (ConfigurableContainer::ComponentType::Loop);           });

        deckSx.setComponentOnClick       (ConfigurableContainer::ComponentType::HeadphoneOut, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 7, (juce::uint8) 127));
            midiOut->sendMessageNow(juce::MidiMessage::noteOff         (ch, 7, (juce::uint8) 127));
            deckSx.toggleComponentAlpha (ConfigurableContainer::ComponentType::HeadphoneOut);   });

    }

    {// setup lambdas for deckDx
        auto ch = 2;
        deckDx.setComponentOnClick (ConfigurableContainer::ComponentType::Play, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127)); });

        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Seek, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Seek, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });

//        deckDx.setComponentOnValueChange (ConfigurableContainer::ComponentType::Cue, [&,ch](const int value){
//            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 21, value)); });
//        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::Cue, [&,ch]{
//            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 3, (juce::uint8) 127)); });

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
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 6, (juce::uint8) 127));
            midiOut->sendMessageNow(juce::MidiMessage::noteOff         (ch, 6, (juce::uint8) 127));
            deckDx.toggleComponentAlpha (ConfigurableContainer::ComponentType::Loop);           });

        deckDx.setComponentOnClick       (ConfigurableContainer::ComponentType::HeadphoneOut, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 7, (juce::uint8) 127));
            midiOut->sendMessageNow(juce::MidiMessage::noteOff         (ch, 7, (juce::uint8) 127));
            deckDx.toggleComponentAlpha (ConfigurableContainer::ComponentType::HeadphoneOut);   });
    }

    {// setup lambdas for middleStrip
        auto ch = 3;
        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::Browser, [&,ch]{
            auto mainWin = dynamic_cast<DocumentWindow*> (getTopLevelComponent ());
            auto* browser = new BrowserWindow(midiOut);
            browser->setVisible (true);
            browser->setBounds (getBounds ().expanded (CONTROLLLER_RECUCTION));
            browser->addToDesktop (ComponentPeer::windowIsTemporary);
            browser->setMainWindow (mainWin);
            mainWin ->setFullScreen (false);
            mainWin ->setVisible (false);

/* metodi alternativi:
            Desktop::getInstance().setKioskModeComponent(this);

            auto win = dynamic_cast<DocumentWindow*> (getTopLevelComponent   ());
            auto btn = dynamic_cast<Button*>         (win->getMinimizeButton ());
            btn->triggerClick ();
*/

            //midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 100, (juce::uint8) 127));
        });

        middleStrip.setComponentOnValueChange (ConfigurableContainer::ComponentType::Crossfader, [&,ch](const int value){
            midiOut->sendMessageNow(juce::MidiMessage::controllerEvent (ch, 20, value )); });
        middleStrip.setComponentOnClick       (ConfigurableContainer::ComponentType::Crossfader, [&,ch]{
            midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127)); });
    }

    addAndMakeVisible (deckSx);
    addAndMakeVisible (deckDx);
    addAndMakeVisible (middleStrip);
    setLookAndFeel (&laf);
//    setSize (800, 800);
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
    auto deckToUnZoom   = deckToZoom == &deckDx ? &deckSx : &deckDx;
    auto boundsBig      = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*4/7):
                                                  area.removeFromRight(getWidth()*4/7);
    auto boundsVertical = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*1/7):
                                                  area.removeFromRight(getWidth()*1/7);
    auto boundsSmall    = deckToZoom == &deckSx ? area.removeFromLeft (getWidth()*3/7):
                                                  area.removeFromRight(getWidth()*3/7);

    boundsVertical.reduce (0,DECK_MARGIN);

    animator.animateComponent(deckToUnZoom,boundsSmall.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(deckToZoom,boundsBig.reduced (DECK_MARGIN),1,111,false,0,1);
    animator.animateComponent(&middleStrip,boundsVertical,1,111,false,0,1);

}

