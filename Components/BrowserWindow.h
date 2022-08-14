#pragma once

#include "VerticalStrip.h"
#include "ConfigurableContainer.h"
/**
 * @brief The BrowserWindow class is a simple window which displays controls to navigate the dj software browser
 */
class BrowserWindow : public juce::Component
{
public:
    BrowserWindow();

    void resized() override;

protected:
    VerticalStrip leftStrip, middleStrip, rightStrip;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserWindow)
};

