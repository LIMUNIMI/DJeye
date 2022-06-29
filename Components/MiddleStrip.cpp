#include "MiddleStrip.h"

MiddleStrip::MiddleStrip():
    browserButton ("browserButton",DrawableButton::ButtonStyle::ImageStretched)//TODO: imageFitted
{
    Path rectHB;
    rectHB.addRectangle (Rectangle<float>(0,0,1,1));

    {//crossfader setup
        crossfader.setSliderStyle                (juce::Slider::LinearHorizontal);
        crossfader.setTextBoxStyle               (juce::Slider::NoTextBox, false, 0, 0);
        crossfader.setSliderSnapsToMousePosition (false);
        crossfader.setRange                      (0,127,1);
        crossfader.setDoubleClickReturnValue     (true, 0.5f*crossfader.getRange ().getLength ());
        crossfader.setHitBox                     (rectHB);

        crossfader.onValueChange = []{DBG("crossfaderMosso");};

        addAndMakeVisible (crossfader);
    }

    {//browserButton setup
        auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
        browserButton.setImages (image.get ());
        browserButton.setHitBox (rectHB);

        browserButton.onClick = []{DBG("browserButtonClick");};

        addAndMakeVisible (browserButton);
    }

}

void MiddleStrip::resized()
{
    Component::resized ();

    auto area = getLocalBounds ();
    browserButton.setBounds (area.removeFromTop    (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));
    crossfader.setBounds    (area.removeFromBottom (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));

}

void MiddleStrip::paint(Graphics &g)
{
    g.fillAll (Colours::aliceblue);
}
