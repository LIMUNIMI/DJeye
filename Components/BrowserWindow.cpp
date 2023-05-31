#include "BrowserWindow.h"

BrowserWindow::BrowserWindow():
    leftStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
                ConfigurableContainer::LoadLeft,}},
    middleStrip{*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::ScrollUp,
        ConfigurableContainer::Spacer,//non è il modo più elegante di dividere lo schermo da tutto sommato funziona bene dai
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::ScrollDown}},
    rightStrip  {*new std::vector<ConfigurableContainer::ComponentType> {ConfigurableContainer::LoadRight}}
{
        auto ch = 3;

        leftStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadLeft, [&,ch]{
            DBG("l");
            setVisible(false);
            getTopLevelComponent ()->setVisible (true);
            delete this;
        });

        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollUp, [&,ch]{DBG("u");});

        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollDown, [&,ch]{DBG("d");});

        rightStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadRight, [&,ch]{DBG("r");});
//           dynamic_cast<DocumentWindow*>(getTopLevelComponent ())->setMinimised  (false);
//           setVisible (false);
//           /*midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));*/ });

//        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollUp, [&,ch]{
//            DBG("up");
//            delete this;
//            dynamic_cast<DocumentWindow*>(getTopLevelComponent ())->setMinimised  (false);
//            setVisible (false);
//            /*midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));*/ });

    addAndMakeVisible (leftStrip  );
    addAndMakeVisible (middleStrip);
    addAndMakeVisible (rightStrip );
}


void BrowserWindow::resized()
{
    //|-|-----|-|
    //|l|  c  |r|

    auto area = getBounds ();
    auto sideWidth = getWidth ()/7;
    leftStrip.setBounds   (area.removeFromLeft  (sideWidth));
    rightStrip.setBounds  (area.removeFromRight (sideWidth));
    middleStrip.setBounds (area                            );
}
