#pragma once
#include <JuceHeader.h>
#include "hoverzoomtest.h"

hoverZoomTest::hoverZoomTest():
    buttonSx("buttonSx",juce::Colours::yellow,juce::Colours::green,juce::Colours::purple),
    buttonDx("buttonDx",juce::Colours::yellow,juce::Colours::green,juce::Colours::purple)
{
    #if JUCE_LINUX || JUCE_BSD || JUCE_MAC || JUCE_IOS || DOXYGEN
    midiOut = juce::MidiOutput::createNewDevice("DJEYE");
    #else
    midiOut = juce::MidiOutput::openDevice("DJEYE"); //da testare
    #endif
    if (midiOut == nullptr){
        //eccezione
    }
    //animator = Desktop::getInstance().getAnimator ();
    buttonSx.onClick = [this] {sendMidi(34);};
    buttonSx.onStateChange = [this] {manageActionOnButton(&buttonSx);};
    buttonDx.onClick = [this] {sendMidi(37);};
    buttonDx.onStateChange = [this] {manageActionOnButton(&buttonDx);};


    addAndMakeVisible(buttonSx);
    addAndMakeVisible(buttonDx);
    setSize (400, 300);

    //resizing happening...

    auto dimensionMaxSx = jmax(buttonSx.getWidth(), buttonSx.getHeight());
    Path circle;
    circle.addEllipse(buttonSx.getBounds().getCentreX(),
                      buttonSx.getBounds().getCentreY(),
                      dimensionMaxSx,
                      dimensionMaxSx);
    buttonSx.setShape(circle,true,true,false);
    buttonDx.setShape(circle,true,true,false);//assuming buttonsx and dx are equal at start
    buttonDx.setOutline (Colours::aliceblue,5.0f);
    buttonSx.setOutline (Colours::aliceblue,5.0f);
}

hoverZoomTest::~hoverZoomTest() {}

void hoverZoomTest::paint (juce::Graphics& g) {}

void hoverZoomTest::resized()
{//solo quando la **finestra** è resized
    auto area = getLocalBounds ();
    buttonSx.setBounds(area.removeFromLeft(getWidth()/2).reduced (20));
    buttonDx.setBounds(area.removeFromRight(getWidth()/2).reduced (20));
    if (selectedButton != nullptr)
        toggleZoom(selectedButton);
}

void hoverZoomTest::sendMidi(const int noteNumber)
{
    midiOut->sendMessageNow(juce::MidiMessage::noteOn (1, noteNumber, (juce::uint8) 100));
}

void hoverZoomTest::manageActionOnButton(ShapeButtonAdaptedv2* button){

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


void hoverZoomTest::toggleZoom(ShapeButtonAdaptedv2* buttonToZoom){
    auto area = getLocalBounds ();
    auto buttonToUnZoom = buttonToZoom == &buttonDx ? &buttonSx : &buttonDx;
    auto boundsBig = buttonToZoom == &buttonSx ? area.removeFromLeft (getWidth()*2/3) :
                                                 area.removeFromRight (getWidth()*2/3);
    auto boundsSmall = buttonToZoom == &buttonSx ? area.removeFromLeft (getWidth()*1/3) :
                                                   area.removeFromRight (getWidth()*1/3);

    animator.animateComponent(buttonToUnZoom,boundsSmall.reduced (20),1,300,false,2,1);
    animator.animateComponent(buttonToZoom,boundsBig.reduced (20),1,300,false,2,1);

}

/*
 * monitorare midi dal terminale
 * visualizzare lista porte:
 * aconnect -i -o -l
 * dump porta:
 * aseqdump -p [numeroporta]
*/

















