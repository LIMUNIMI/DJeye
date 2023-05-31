#include "BrowserWindow.h"

BrowserWindow::BrowserWindow(std::shared_ptr<MidiOutput> midiOutput):
    leftStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::LoadLeft,}},
    middleStrip{*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::ScrollUp,
        ConfigurableContainer::Spacer,//non è il modo più elegante di dividere lo schermo da tutto sommato funziona bene dai
        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
////        ConfigurableContainer::Spacer,
////        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
//        ConfigurableContainer::Spacer,
        ConfigurableContainer::Spacer,
        ConfigurableContainer::ScrollDown}},
    rightStrip  {*new std::vector<ConfigurableContainer::ComponentType> {
        ConfigurableContainer::LoadRight}}
{
        midiOut = std::move(midiOutput);

        // NOTE: since unfocusAllComponents() does not give underlying DJ SW focus, in some lambdas a hack is implemented.
        // visibility is temporarely set to false, so that no juce component is present on the screen,
        // the underlying software gets focus and can get midi conrols which require window focus.
        // (IN MIXX navigating the library is achieved through keyboard emulation)

        {//setup lambdas
            auto ch = 3;

            leftStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadLeft, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 0, (juce::uint8) 127));
                closeBrowser ();
            });

            middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollUp, [&,ch]{
                //setVisible   (false);
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 1, (juce::uint8) 127));
                //setVisible   (true);
            });

            middleStrip.setComponentOnClick (ConfigurableContainer::ComponentType::ScrollDown, [&,ch]{
                //setVisible   (false);
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 2, (juce::uint8) 127));
                //setVisible   (true);
            });

            rightStrip.setComponentOnClick (ConfigurableContainer::ComponentType::LoadRight, [&,ch]{
                midiOut->sendMessageNow(juce::MidiMessage::noteOn (ch, 3, (juce::uint8) 127));
                closeBrowser ();
            });
        }

    addAndMakeVisible (leftStrip  );
    addAndMakeVisible (middleStrip);
    addAndMakeVisible (rightStrip );
    setAlwaysOnTop(true);
    DBG((hasKeyboardFocus (true) ? "lo ha" : "non lo ha"));
    setLookAndFeel (&laf);
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
    mainWindow->setVisible   (true);
    mainWindow->setFullScreen (true);

    removeFromDesktop ();
    DBG("closing browser");
    delete this;
}

DocumentWindow *BrowserWindow::getMainWindow() const
{
    return mainWindow;
}

void BrowserWindow::setMainWindow(DocumentWindow *newMainWindow)
{
    mainWindow = newMainWindow;
}

