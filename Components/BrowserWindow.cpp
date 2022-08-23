#include "BrowserWindow.h"

BrowserWindow::BrowserWindow(std::shared_ptr<MidiOutput> midiOutput):
    leftStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::LoadLeft,}},
    middleStrip{*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::ScrollUp,
        ConfigurableContainer::Spacer,//non è il modo più elegante di dividere lo schermo da tutto sommato funziona bene dai
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::ScrollDown}},
    rightStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::LoadRight}}
{
        midiOut = std::move(midiOutput);

        {//setup lambdas
            auto ch = 3;

            leftStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadLeft, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 0, (juce::uint8) 127));
                closeBrowser ();
            });

            middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollUp, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));
            });

            middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollDown, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 2, (juce::uint8) 127));
            });

            rightStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadRight, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 3, (juce::uint8) 127));
                closeBrowser ();
            });
        }

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
    auto mainWin = dynamic_cast<DocumentWindow*> (getMainWindow ());
    mainWin->setFullScreen (false);
    mainWin->setFullScreen (true);
    mainWin->setVisible   (true);

    removeFromDesktop ();
    delete this;
    DBG("closing browser");
}

Component *BrowserWindow::getMainWindow() const
{
    return mainWindow;
}

void BrowserWindow::setMainWindow(Component *newMainWindow)
{
    mainWindow = newMainWindow;
}

