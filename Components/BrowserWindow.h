#pragma once

#include "VerticalStrip.h"
#include "ConfigurableContainer.h"
/**
 * @brief The BrowserWindow class is a simple window which displays controls to navigate the dj software browser
 */
class BrowserWindow : public juce::Component
{
public:
    BrowserWindow(juce::MidiOutput*  midiOut);

    void resized() override;

    void closeBrowser();

    Component *getMainWindowPointer() const;
    void setMainWindowPointer(Component *newMainWindowPointer);

protected:
    VerticalStrip leftStrip, middleStrip, rightStrip;
    Component* mainWindowPointer;
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserWindow)
};

