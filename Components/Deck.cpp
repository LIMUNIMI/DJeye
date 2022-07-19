#include "Deck.h"

Deck::Deck(const Deck::ComponentType* ComponentList):
    testButton ("megabottone",DrawableButton::ButtonStyle::ImageFitted)
{
    if (ComponentList){
        numComponents = sizeof(ComponentList);
        int numRadialComponents = 0;

        // Component inizialization
        for(int i = 0 ; i < numComponents ; ++i){ //filling map

            switch(ComponentList[i]){
            case Deck::Play:
                components[i] = new DrawableButtonAdaptive ("playBtn",DrawableButton::ButtonStyle::ImageFitted); break;
            case Deck::Crossfader:
                break;
            case Deck::Browser:
                break;
            case Deck::HeadphoneOut:
                break;
            case Deck::Sync:
                break;
            case Deck::SyncMaster:
                break;
            case Deck::MasterVolume:
                break;
            case Deck::HeadphoneVolume:
                break;
            case Deck::Seek:
            case Deck::Cue:
            case Deck::HPLPFilter:
            case Deck::Volume:
            case Deck::Loop:
                components[i] = new SliderAdaptive (); break;
            default:
                break;

            }
        }

        for(auto& [tipo, comp] : components){ // common properties

            switch(tipo){
            case Deck::Play:
            {//TODO usare smartpointers
                auto button = dynamic_cast<DrawableButtonAdaptive*>(comp);
                //auto button = static_cast<DrawableButtonAdaptive*>(comp);
                auto image = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
                button->setImages (image.get ()); //TODO: spostare fuori

                Path p;
                p.addEllipse (Rectangle<float>(0,0,1,1));
                button->setHitBox (p);

                button->onClick = []{DBG("bottoneClick");};
                break;
            }
                //case Deck::HeadphoneOut:
                //case Deck::Sync:
                //case Deck::SyncMaster:
                //case Deck::HeadphoneVolume:
            case Deck::Seek:
            case Deck::Cue:
            case Deck::HPLPFilter:
            case Deck::Volume:
            case Deck::Loop:
            {
                auto slider = dynamic_cast<SliderAdaptive*>(comp);
                slider->setSliderStyle  (juce::Slider::RotaryVerticalDrag);
                slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

                auto startAngle = numRadialComponents*(getComponentAngle() + getComponentSeparationAngle());
                slider->setRotaryParameters (startAngle, startAngle + getComponentAngle(),true);
                //slider.onValueChange =  componentsActions[i];
                //slider.onMouseUp = componentsActions.at(i);
                slider->setRange (0,127,1);
                slider->setAutoFitHitBoxToRotaryParameters (true);

                numRadialComponents++;
                break;
            }
            default: break;
            }

            addAndMakeVisible (comp);

        }

        // Specific settings
        auto HPFilter = (SliderAdaptive*)components[Deck::HPLPFilter];// TODO: test, da ettore se non inizializzato?
        if (HPFilter) {HPFilter->setSnapToMiddleValue(true);}

        /*{//itera nella mappa
            switch(){
             case Loop
             set image
            }
        }*/


        //TODO: setMouseDragSensitivity, setVelocityModeParameters, setVelocitySensitivity

        {
            testSlider1.setSliderStyle  (juce::Slider::RotaryVerticalDrag);
            testSlider1.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
            //testSlider1.setRotaryParameters (0,getComponentAngle(),true);

            auto shape = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
            testSlider1.setImage (shape.get ());
            //testSlider1.onValueChange = []{midiOut->sendMessageNow(juce::MidiMessage::noteOn (1, noteNumber, (juce::uint8) 100))};
            testSlider1.onValueChange = []{DBG("slider1mosso");};
            testSlider1.onMouseUp = []{DBG("slider1click");};
            testSlider1.setRange (1.0,5.0,1);
            testSlider1.setAutoFitHitBoxToRotaryParameters (true);
            //addAndMakeVisible (testSlider1);
        }

        {
            testSlider2.setSliderStyle  (juce::Slider::RotaryVerticalDrag);
            testSlider2.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

            auto shape = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
            testSlider2.setImage (shape.get());//std::move(shape));

            testSlider2.onValueChange = []{DBG("slider2mosso");};
            testSlider2.onMouseUp = []{DBG("slider2click");};
            testSlider2.setRange (0.0,127.0,1);
            testSlider2.setDoubleClickReturnValue (true, 0.5f*testSlider2.getRange ().getLength ());
            testSlider2.setAutoFitHitBoxToRotaryParameters (true);
            testSlider2.setSnapToMiddleValue (true);
            //addAndMakeVisible (testSlider2);
        }

        {
            auto image = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
            testButton.setImages (image.get ());

            Path p;
            p.addEllipse (Rectangle<float>(0,0,1,1));
            testButton.setHitBox (p);

            testButton.onClick = []{DBG("bottoneClick");};
            //addAndMakeVisible (testButton);
        }
    }

}

Deck::~Deck(){} //TODO: rimovibile?

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::blueviolet);

    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim}.reduced (DECK_PADDING);
    componentsContainer.setCentre (getBounds ().getCentre ());

    g.setColour (Colours::blue);
    //g.fillPath (testButton.getHitBox ());
    //g.drawRect (testSlider1.getBounds ());
    //g.drawRect (testSlider2.getBounds ());
    //g.fillPath (testSlider2.getBoundingBox ());

}

void Deck::resized()
{
    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim};
    componentsContainer.setCentre (getLocalBounds ().getCentre ());

    //    for(int i = 0 ; i < numComponents  && components[i] != nullptr; ++i){
    //        Component* comp = components[i];

    for (auto& [tipo, comp] : components) {//const?

        //common
        switch(tipo){
        case Deck::Play:{

            auto diametroDaTogliere = (1-INNER_CIRCLE_TO_SLIDER_RATIO) * minDim*0.5f;
            diametroDaTogliere += SEPARATION_TO_COMPONENT_DIMENSION_RATIO * diametroDaTogliere + DECK_PADDING;
            comp->setBounds(componentsContainer.reduced (diametroDaTogliere));
            break;
        }
            //case Deck::HeadphoneOut:
            //case Deck::Sync:
            //case Deck::SyncMaster:
        //case Deck::HeadphoneVolume:
        case Deck::Seek:
        case Deck::Cue:
        case Deck::HPLPFilter:
        case Deck::Volume:
        case Deck::Loop:
        {
            comp->setBounds (componentsContainer.reduced (DECK_PADDING));
            break;
        }
        default: break;
        }
    }

    /*if deck was quaranteed to be square
    testSlider1.setBoundsInset (BorderSize((int)DECK_PADDING));
    testSlider2.setBoundsInset (BorderSize((int)DECK_PADDING));
    testButton.setBoundsInset (BorderSize((int)diametroDaTogliere));*/
    /*//https://it.wikipedia.org/wiki/Trasformazione_affine
    auto trasformVersoAlto = AffineTransform::translation (0,-COMPONENTS_SEPARATION);
    testSlider1.setTransform (trasformVersoAlto);
    testSlider2.setTransform (AffineTransform::rotation (getComponentAngle()+getComponentSeparationAngle(),componentsContainer.getCentreX (),  componentsContainer.getCentreY ()));
    */

}

void Deck::mouseEnter(const MouseEvent &/*event*/)
{
    if (onMouseEnter) onMouseEnter();
}

void Deck::mouseExit(const MouseEvent &/*event*/)
{
    if (onMouseExit) onMouseExit();
}

int Deck::getNumRadialComponents() const
{
    return    components.count(Deck::ComponentType::Seek)
            + components.count(Deck::ComponentType::Cue)
            + components.count(Deck::ComponentType::HPLPFilter)
            + components.count(Deck::ComponentType::Volume)
            + components.count(Deck::ComponentType::Loop);

}


