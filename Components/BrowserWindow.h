#pragma once

#include "VerticalStrip.h"
#include "ConfigurableContainer.h"
/**
 * @brief The BrowserWindow class is a simple window which displays controls to navigate the dj software browser
 */
class BrowserWindow : public juce::Component
{
public:
    BrowserWindow(std::shared_ptr<MidiOutput>  midiOut);

    void resized() override;

    /**
    * @brief Closes this popup window
    */
    void closeBrowser();

    /**
     * @brief Returns the main window this browser will make visible when closing
     * @return
     */
    Component *getMainWindow() const;
    /**
     * @brief Sets the main window this browser will make visible when closing
     * @param newMainWindowPointer
     */
    void setMainWindow(Component *newMainWindowPointer);

protected:
    VerticalStrip leftStrip, middleStrip, rightStrip;
    Component* mainWindow;
    std::shared_ptr<MidiOutput> midiOut;
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserWindow)
};

