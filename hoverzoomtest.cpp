#pragma once
#include <JuceHeader.h>
#include "hoverzoomtest.h"

hoverZoomTest::hoverZoomTest():
//    buttonSx("buttonSx"),
//    buttonDx("buttonDx")
      buttonSx ("buttonSx",DrawableButton::ButtonStyle::ImageFitted),
      buttonDx ("buttonDx",DrawableButton::ButtonStyle::ImageFitted)
{
#if JUCE_LINUX || JUCE_BSD || JUCE_MAC || JUCE_IOS || DOXYGEN
    midiOut = juce::MidiOutput::createNewDevice("DJEYE");
#else
    midiOut = juce::MidiOutput::openDevice("DJEYE"); //TODO: da testare
#endif
    if (midiOut == nullptr){
        //eccezione
    }
    //animator = Desktop::getInstance().getAnimator ();
    buttonSx.onClick = [this] {sendMidi(34);};
    buttonSx.onStateChange = [this] {manageActionOnButton(&buttonSx);};
    buttonDx.onClick = [this] {sendMidi(37);};
    buttonDx.onStateChange = [this] {manageActionOnButton(&buttonDx);};

    setLookAndFeel (&customTheme);

//    auto image = ImageCache::getFromMemory (BinaryData::circleButton_png, BinaryData::circleButton_pngSize);
//    auto transp = Colours::transparentWhite;

//    buttonSx.setImages (false,true,true,image,1.0f,transp,Image(),0.5f,transp,Image(),1.0f,transp,0.8f);
//    buttonDx.setImages (false,true,true,image.createCopy (),1.0f,transp,Image(),0.5f,transp,Image(),1.0f,transp,0.8f);

    auto shape = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
    buttonDx.setImages (shape.get ());
    buttonSx.setImages (shape.get ());

    addAndMakeVisible(buttonSx);
    addAndMakeVisible(buttonDx);

    setSize (400, 400);
}

hoverZoomTest::~hoverZoomTest() {}

void hoverZoomTest::paint (juce::Graphics& g) {}

void hoverZoomTest::resized()
{//solo quando la **finestra** è resized

    buttonSx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    buttonSx.setCentreRelative (0.25f,0.5f);

    buttonDx.setBoundsRelative (0.0f,0.0f,0.45f,0.95f);
    buttonDx.setCentreRelative (0.75f,0.5f);

    toggleZoom(selectedButton);
}

void hoverZoomTest::sendMidi(const int noteNumber)
{
    midiOut->sendMessageNow(juce::MidiMessage::noteOn (1, noteNumber, (juce::uint8) 100));
}

void hoverZoomTest::manageActionOnButton(Button* button){

    switch(button->getState() ) {
    case juce::Button::ButtonState::buttonOver:
        toggleZoom (button);
        break;
        //      case juce::Button::ButtonState::buttonDown:
        //        sendMidi (34);
        //        break;
        //    case juce::Button::ButtonState::buttonNormal:

        //        break;
    }

}

void hoverZoomTest::toggleZoom(Button* buttonToZoom){

    auto area = getLocalBounds ();
    auto buttonToUnZoom = buttonToZoom == &buttonDx ? &buttonSx : &buttonDx;
    auto boundsBig = buttonToZoom == &buttonSx ? area.removeFromLeft (getWidth()*2/3) :
                                                 area.removeFromRight (getWidth()*2/3);
    auto boundsSmall = buttonToZoom == &buttonSx ? area.removeFromLeft (getWidth()*1/3) :
                                                   area.removeFromRight (getWidth()*1/3);

    animator.animateComponent(buttonToUnZoom,boundsSmall.reduced (20),1,500,false,2,1);
    animator.animateComponent(buttonToZoom,boundsBig.reduced (20),1,500,false,2,1);

}

/*
 * monitorare midi dal terminale
 * visualizzare lista porte:
 * aconnect -i -o -l
 * dump porta:
 * aseqdump -p [numeroporta]
*/

















