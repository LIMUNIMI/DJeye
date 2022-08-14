#include "Deck.h"

Deck::Deck(const std::vector<ConfigurableContainer::ComponentType> ComponentList) :
    ConfigurableContainer{ComponentList}
{
    //generate radial components clockwise equally spaced around a circle
    uint numGeneratedRadialComponents = 0;

    for(auto type : ComponentList){
        auto comp = components[type].get();
        if(isRadialComponent(type)){
            SliderAdaptive *slider = static_cast<SliderAdaptive*>(comp);
            auto startAngle = numGeneratedRadialComponents*(getComponentAngle() + getComponentSeparationAngle());
            slider->setRotaryParameters (startAngle, startAngle + getComponentAngle(),true);
            slider->setAutoFitHitBoxToRotaryParameters (true);
            slider->setAccuracyPaddingRatio (ComponentActualAccuracyPaddingRatio);
            numGeneratedRadialComponents++;
        }
    }

}

void Deck::resized()
{
    auto minDim = jmin(getWidth (),getHeight());
    auto componentsContainer = Rectangle {minDim,minDim};
    componentsContainer.setCentre (getLocalBounds ().getCentre ());

    for (auto& [tipo, comp] : components) {//const?

        //common
        switch(tipo){
        case ConfigurableContainer::Play:{

            auto diametroDaTogliere = (1-INNER_CIRCLE_TO_SLIDER_RATIO) * minDim*0.5f;
            diametroDaTogliere += SEPARATION_TO_COMPONENT_DIMENSION_RATIO * diametroDaTogliere + DECK_PADDING;
            comp->setBounds(componentsContainer.reduced (diametroDaTogliere));

        }break;
        case ConfigurableContainer::Crossfader:      break;
        case ConfigurableContainer::Browser:         break;
        case ConfigurableContainer::HeadphoneOut:    break;
        case ConfigurableContainer::Sync:            break;
        case ConfigurableContainer::SyncMaster:      break;
        case ConfigurableContainer::MasterVolume:    break;
        case ConfigurableContainer::HeadphoneVolume: break;
        case ConfigurableContainer::Seek:
        case ConfigurableContainer::Cue:
        case ConfigurableContainer::HPLPFilter:
        case ConfigurableContainer::Volume:
        case ConfigurableContainer::Loop:{

            comp->setBounds (componentsContainer.reduced (DECK_PADDING));

        }break;
        default: break;
        }
    }

    /*if ConfigurableContainer was guaranteed to be square
    testSlider1.setBoundsInset (BorderSize((int)ConfigurableContainer_PADDING));
    testSlider2.setBoundsInset (BorderSize((int)ConfigurableContainer_PADDING));
    testButton.setBoundsInset (BorderSize((int)diametroDaTogliere));*/
    /*//https://it.wikipedia.org/wiki/Trasformazione_affine
    auto trasformVersoAlto = AffineTransform::translation (0,-COMPONENTS_SEPARATION);
    testSlider1.setTransform (trasformVersoAlto);
    testSlider2.setTransform (AffineTransform::rotation (getComponentAngle()+getComponentSeparationAngle(),componentsContainer.getCentreX (),  componentsContainer.getCentreY ()));
    */

}

void Deck::paint(Graphics & /*g*/)
{
    //g.fillAll (Colours::white.withAlpha (0.1f));
}

const bool Deck::isRadialComponent(const ComponentType componentType) const
{
    auto array = {ConfigurableContainer::ComponentType::Seek,
                  ConfigurableContainer::ComponentType::Cue,
                  ConfigurableContainer::ComponentType::HPLPFilter,
                  ConfigurableContainer::ComponentType::Volume,
                  ConfigurableContainer::ComponentType::Loop};

    return std::find(std::begin(array), std::end(array), componentType) != std::end(array);
}
