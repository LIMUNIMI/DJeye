#include "Deck.h"

Deck::Deck(const std::vector<Deck::ComponentType> ComponentList)
{
    numComponents = std::size(ComponentList);
    if (numComponents){
        int numGeneratedRadialComponents =  0;

        // COMPONENT INITITALIZATION
        for(uint i = 0 ; i < numComponents ; i++){ // filling map

            switch(ComponentList[i]){
            case Deck::Play:
                //components[ComponentList[i]] = new DrawableButtonAdaptive {"playBtn",DrawableButton::ButtonStyle::ImageFitted}; break;
                components[ComponentList[i]] = std::make_unique<DrawableButtonAdaptive>("playBtn",DrawableButton::ButtonStyle::ImageFitted); break;
            case Deck::Crossfader:      break;
            case Deck::Browser:         break;
            case Deck::HeadphoneOut:    break;
            case Deck::Sync:            break;
            case Deck::SyncMaster:      break;
            case Deck::MasterVolume:    break;
            case Deck::HeadphoneVolume: break;
            case Deck::Seek:
            case Deck::Cue:
            case Deck::HPLPFilter:
            case Deck::Volume:
            case Deck::Loop:
                components[ComponentList[i]] = std::make_unique<SliderAdaptive>(); break;
            default:                    break;
            }
        }

        for(auto& [tipo, comp] : components){ // common properties
            addAndMakeVisible (comp.get ());

            switch(tipo){
            case Deck::Play:
            {
                DrawableButtonAdaptive *button = static_cast<DrawableButtonAdaptive*>(comp.get());
                //auto button = std::make_unique<DrawableButtonAdaptive>(comp);
                //auto button = std::make_unique<DrawableButtonAdaptive>(std::move(comp));
                //auto button = static_cast<DrawableButtonAdaptive*>(comp);

                Path p;
                p.addEllipse (Rectangle<float>(0,0,1,1));
                button->setHitBox (p);

                //button->onClick = = componentsActions[tipo];
                break;
            }
            case Deck::Crossfader:      break;
            case Deck::Browser:         break;
            case Deck::HeadphoneOut:    break;
            case Deck::Sync:            break;
            case Deck::SyncMaster:      break;
            case Deck::MasterVolume:    break;
            case Deck::HeadphoneVolume: break;
            case Deck::Seek:
            case Deck::Cue:
            case Deck::HPLPFilter:
            case Deck::Volume:
            case Deck::Loop:
            { // TODO: setMouseDragSensitivity, setVelocityModeParameters, setVelocitySensitivity
                SliderAdaptive *slider = static_cast<SliderAdaptive*>(comp.get());
                //auto slider = std::make_unique<SliderAdaptive>(comp);
                //auto slider = dynamic_cast<SliderAdaptive*>(comp);
                slider->setSliderStyle  (juce::Slider::RotaryVerticalDrag);
                slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
                slider->setRange        (0,127,1);

                auto startAngle = numGeneratedRadialComponents*(getComponentAngle() + getComponentSeparationAngle());
                slider->setRotaryParameters (startAngle, startAngle + getComponentAngle(),true);
                slider->setAutoFitHitBoxToRotaryParameters (true);
                //slider->onValueChange = componentsActions[tipo];
                //slider->onMouseUp     = componentsActions.at(tipo);

                numGeneratedRadialComponents++;
                break;
            }
            default: break;
            }
        }

        for(auto& [tipo, comp] : components){ // Specific settings
            switch(tipo){
            case Deck::Play:{
                DrawableButtonAdaptive *button = static_cast<DrawableButtonAdaptive*>(comp.get());
                auto image = Drawable::createFromImageData (BinaryData::circleButton_svg,BinaryData::circleButton_svgSize);
                button->setImages (image.get ());
            }break;
            case Deck::Crossfader:      break;
            case Deck::Browser:         break;
            case Deck::HeadphoneOut:    break;
            case Deck::Sync:            break;
            case Deck::SyncMaster:      break;
            case Deck::MasterVolume:    break;
            case Deck::HeadphoneVolume: break;
            case Deck::Seek:            break;
            case Deck::Cue:             break;
            case Deck::HPLPFilter:{
                SliderAdaptive *HPFilter = static_cast<SliderAdaptive*>(comp.get());
                //auto slider = dynamic_cast<SliderAdaptive*>(comp);
                auto image = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
                HPFilter->setImage (image.get());//std::move(shape));

                HPFilter->setSnapToMiddleValue(true);
                HPFilter->setDoubleClickReturnValue (true, 0.5f*HPFilter->getRange ().getLength ());
                break;
            }
            case Deck::Volume:          break;
            case Deck::Loop:            break;
            default:                    break;
            }
        }

        //        auto HPFilter = components.count (Deck::HPLPFilter) ? (SliderAdaptive*)components[Deck::HPLPFilter] : nullptr;
        //        if (HPFilter) {HPFilter->setSnapToMiddleValue(true);}


       {
            /*testSlider2.setSliderStyle  (juce::Slider::RotaryVerticalDrag);
            testSlider2.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

            auto shape = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
            testSlider2.setImage (shape.get());//std::move(shape));

            //testSlider1.onValueChange = []{midiOut->sendMessageNow(juce::MidiMessage::noteOn (1, noteNumber, (juce::uint8) 100))};
            testSlider2.onValueChange = []{DBG("slider2mosso");};
            testSlider2.onMouseUp = []{DBG("slider2click");};
            testSlider2.setRange (0.0,127.0,1);
            testSlider2.setAutoFitHitBoxToRotaryParameters (true);
            testSlider2.setDoubleClickReturnValue (true, 0.5f*testSlider2.getRange ().getLength ());
            testSlider2.setSnapToMiddleValue (true);
            //addAndMakeVisible (testSlider2);*/
        }

    }

}

Deck::~Deck(){} //TODO: rimovibile?

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::blueviolet);
}

void Deck::resized()
{
    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim};
    componentsContainer.setCentre (getLocalBounds ().getCentre ());

    for (auto& [tipo, comp] : components) {//const?

        //common
        switch(tipo){
        case Deck::Play:{
            auto diametroDaTogliere = (1-INNER_CIRCLE_TO_SLIDER_RATIO) * minDim*0.5f;
            diametroDaTogliere += SEPARATION_TO_COMPONENT_DIMENSION_RATIO * diametroDaTogliere + DECK_PADDING;
            comp->setBounds(componentsContainer.reduced (diametroDaTogliere));
            break;
        }
        case Deck::Crossfader:      break;
        case Deck::Browser:         break;
        case Deck::HeadphoneOut:    break;
        case Deck::Sync:            break;
        case Deck::SyncMaster:      break;
        case Deck::MasterVolume:    break;
        case Deck::HeadphoneVolume: break;
        case Deck::Seek:
        case Deck::Cue:
        case Deck::HPLPFilter:
        case Deck::Volume:
        case Deck::Loop:{
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


