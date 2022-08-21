#include "BrowserWindow.h"

BrowserWindow::BrowserWindow(juce::MidiOutput* midiOut):
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
    rightStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::LoadRight}}
{
        auto ch = 3;
        leftStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadLeft, [&,ch]{
            //midiOut->sendMessageNow(juce::MidiMessage::noteOn          (ch, 2, (juce::uint8) 127));
            closeBrowser ();
        });

        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollUp, [&,ch]{DBG("u");

        });

        middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollDown, [&,ch]{DBG("d");});

        rightStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadRight, [&,ch]{DBG("r");});

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

void BrowserWindow::closeBrowser()
{
    auto mainWin = dynamic_cast<DocumentWindow*> (getMainWindowPointer ());
    mainWin->setFullScreen (false);
    mainWin->setFullScreen (true);
    mainWin->setVisible   (true);

    removeFromDesktop ();
    delete this;
    DBG("closing browser");
}

Component *BrowserWindow::getMainWindowPointer() const
{
    return mainWindowPointer;
}

void BrowserWindow::setMainWindowPointer(Component *newMainWindowPointer)
{
    mainWindowPointer = newMainWindowPointer;
}

