#include "Deck.h"

Deck::Deck(const std::vector<Deck::ComponentType> ComponentList)
{
    numComponents = std::size(ComponentList);
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

    for(uint i = 0 ; i < numComponents ; i++){ // common properties (still using for and not foreach since this way i can insert radial components in the order gaved by ComponentList)
        auto comp = components[ComponentList[i]].get();

        switch(ComponentList[i]){
        case Deck::Play:
        {
            DrawableButtonAdaptive *button = static_cast<DrawableButtonAdaptive*>(comp);

            Path p;
            p.addEllipse (Rectangle<float>(0,0,1,1));
            button->setAccuracyPaddingRatio (ComponentActualAccuracyPaddingRatio);
            button->setHitBox (p);

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
            SliderAdaptive *slider = static_cast<SliderAdaptive*>(comp);
            slider->setSliderStyle  (juce::Slider::RotaryVerticalDrag);
            slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
            slider->setRange        (0,127,1);

            auto startAngle = numGeneratedRadialComponents*(getComponentAngle() + getComponentSeparationAngle());
            slider->setRotaryParameters (startAngle, startAngle + getComponentAngle(),true);
            slider->setAutoFitHitBoxToRotaryParameters (true);
            slider->setAccuracyPaddingRatio (ComponentActualAccuracyPaddingRatio);

            numGeneratedRadialComponents++;
            break;
        }
        default: break;
        }
    }

    for(auto& [tipo, comp] : components){ // Specific settings
        addAndMakeVisible (comp.get ());

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
            SliderAdaptive *hplpfilter = static_cast<SliderAdaptive*>(comp.get());
            //auto slider = dynamic_cast<SliderAdaptive*>(comp);
            auto image = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
            hplpfilter->setImage (image.get());//std::move(shape));

            hplpfilter->setSnapToMiddleValue(true);
            hplpfilter->setDoubleClickReturnValue (true, 0.5f*hplpfilter->getRange ().getLength ());
            hplpfilter->setValue (0.5f*hplpfilter->getRange ().getLength ());
            break;
        }
        case Deck::Volume:{
            SliderAdaptive *volume = static_cast<SliderAdaptive*>(comp.get());
            //auto slider = dynamic_cast<SliderAdaptive*>(comp);
            auto image = Drawable::createFromImageData (BinaryData::volume_svg,BinaryData::volume_svgSize);
            volume->setImage (image.get());//std::move(shape));
            break;
        }
        case Deck::Loop:            {
            SliderAdaptive *loop = static_cast<SliderAdaptive*>(comp.get());
            loop->setRange(0,6,1);// da 1/8 a 8 barre
            loop->setValue(4);
        }break;
        default:                    break;
        }
    }

    //        auto HPFilter = components.count (Deck::HPLPFilter) ? (SliderAdaptive*)components[Deck::HPLPFilter] : nullptr;
    //        if (HPFilter) {HPFilter->setSnapToMiddleValue(true);}
}

Deck::~Deck(){} //TODO: rimovibile?

void Deck::paint (juce::Graphics& g) {
    g.fillAll (Colours::blueviolet.withAlpha (0.2f));
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

    /*if deck was guaranteed to be square
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
    int count = 0;
    for (auto& [tipo,comp] : components)
        if (isRadialComponent(Deck::ComponentType(tipo)))  count++;
    return count;
}

const bool Deck::isRadialComponent(const ComponentType componentType) const
{
    auto array = {Deck::ComponentType::Seek,
                  Deck::ComponentType::Cue,
                  Deck::ComponentType::HPLPFilter,
                  Deck::ComponentType::Volume,
                  Deck::ComponentType::Loop};

    return std::find(std::begin(array), std::end(array), componentType) != std::end(array);
}

void Deck::setComponentOnValueChange(const Deck::ComponentType componentType, std::function<void (const int val)> newComponentOnValueChange)
{
    if (components.count (componentType)){
        SliderAdaptive *slider = dynamic_cast<SliderAdaptive*>(components[componentType].get());
        //NOTE: non sono sicuro di quanto questa sia una ciofecata
        //NOTE: non so se la capture clause "=" sia la scelta miogliore, ma funziona
        if(slider) slider->onValueChange =[=]{ newComponentOnValueChange(slider->getValue ());};
    }
}

void Deck::setComponentOnClick(const Deck::ComponentType componentType, std::function<void ()> newComponentOnClick)
{
    if(components.count (componentType)){
        SliderAdaptive         *slider = dynamic_cast<SliderAdaptive*>         (components[componentType].get());
        DrawableButtonAdaptive *button = dynamic_cast<DrawableButtonAdaptive*> (components[componentType].get());

        if(slider)      slider->onMouseUp = newComponentOnClick;
        else if(button) button->onClick   = newComponentOnClick;
    }

}



