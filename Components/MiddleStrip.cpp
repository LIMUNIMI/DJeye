#include "MiddleStrip.h"

MiddleStrip::MiddleStrip():
    browser ("browserButton",DrawableButton::ButtonStyle::ImageFitted)
{
    {
        crossfader.setSliderStyle (juce::Slider::LinearHorizontal);
        crossfader.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

        auto shape = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
        crossfader.onValueChange = []{DBG("crossfaderMosso");};
        crossfader.setRange (0,127,1);
        addAndMakeVisible (crossfader);
    }

    addAndMakeVisible (browser);
}

void MiddleStrip::resized()
{
    Component::resized ();

    auto area = getLocalBounds ();
    crossfader.setBounds (area.removeFromTop    (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));
    browser.setBounds    (area.removeFromBottom (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));

//    crossfader.setBoundsRelative (0.0f, 0.0f, 0.5f, 0.25f);
//    crossfader.setCentreRelative (0.5f, 0.25f);

//    browser.setBoundsRelative (0.0f, 0.0f, 0.5f, 0.25f);
//    browser.setCentreRelative (0.5f, 0.75f);

}

void MiddleStrip::paint(Graphics &g)
{
    g.fillAll (Colours::azure);
}
