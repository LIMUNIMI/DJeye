#include "ConfigurableContainer.h"

//TODO: decidere se muovere tutto quello che riguarda radial components in Deck

ConfigurableContainer::ConfigurableContainer(const std::vector<ConfigurableContainer::ComponentType> ComponentList)
{

    // COMPONENT INITITALIZATION
    for(auto type : ComponentList){ // filling component map

        switch(type){
        case ConfigurableContainer::Play:{

            auto playBtn = std::make_unique<DrawableButtonAdaptive>("playBtn",DrawableButton::ButtonStyle::ImageFitted);
            Path p;
            p.addEllipse (Rectangle<float>(0,0,1,1));
            playBtn->setAccuracyPaddingRatio (ComponentActualAccuracyPaddingRatio);
            playBtn->setToggleable (true);
            playBtn->setClickingTogglesState (true);
            playBtn->setHitBox (p);
            components[type] = std::move(playBtn);

        }break;
        case ConfigurableContainer::LoadLeft:
        case ConfigurableContainer::LoadRight:
        case ConfigurableContainer::ScrollDown:
        case ConfigurableContainer::ScrollUp:
        case Browser:{

            auto rectBtn = std::make_unique<DrawableButtonAdaptive>("rectBtn",DrawableButton::ButtonStyle::ImageStretched);

            Path rectHB; // hitbox for these buttons is rectangular
            rectHB.addRectangle   (Rectangle<float>(0,0,1,1));
            rectBtn->setHitBox (rectHB);
            //rectBtn.setAccuracyPaddingRatio (ComponentActualAccuracyPaggingRatio);
            components[type] = std::move(rectBtn);

        }break;
        case ConfigurableContainer::Crossfader: {

            auto crossfader =  std::make_unique<SliderAdaptive>();

            Path rectHB; // hitbox for crossfader rectangular
            rectHB.addRectangle (Rectangle<float>(0,0,1,1));
            crossfader->setHitBox                     (rectHB);

            crossfader->setSliderStyle                (juce::Slider::LinearHorizontal);
            crossfader->setTextBoxStyle               (juce::Slider::NoTextBox, false, 0, 0);
            crossfader->setSliderSnapsToMousePosition (false);
            crossfader->setRange                      (0.0f, 127.0f, 1.0f);
            crossfader->setDoubleClickReturnValue     (true, 0.5f*crossfader->getRange ().getLength ());
            crossfader->setSnapToMiddleValue          (true);
            crossfader->setValue (0.5f*crossfader->getRange ().getLength ());
            //browserButton.setAccuracyPaddingRatio    (ComponentActualAccuracyPaggingRatio);
            components[type] = std::move(crossfader);

        } break;
        case ConfigurableContainer::Spacer:{//NOTE: spacer does not figure inside the components map. since they're kind of special. is this bad design? i guess so... ops
//            auto spacer = std::make_unique<Component>();
//            components[type] = std::move(spacer);

        }break;
        case ConfigurableContainer::Seek:
        case ConfigurableContainer::Cue:
        case ConfigurableContainer::HPLPFilter:
        case ConfigurableContainer::Volume:
        case ConfigurableContainer::Loop:{

            // TODO: setMouseDragSensitivity, setVelocityModeParameters, setVelocitySensitivity
            auto slider =  std::make_unique<SliderAdaptive>();
            slider->setSliderStyle  (juce::Slider::RotaryVerticalDrag);
            slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
            slider->setRange        (0.0f, 127.0f, 1.0f);
            components[type] = std::move(slider);

        }break;
        default:                    break;
        }
    }


    for(auto& [tipo, comp] : components){ // Specific settings
        addAndMakeVisible (comp.get ());
        switch(tipo){
        case ConfigurableContainer::Play:{
            //TODO: rimane nero al cambio immagine, como mais?
            DrawableButtonAdaptive *button = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto imageOff  = Drawable::createFromImageData (BinaryData::playBtnPlay_svg ,BinaryData::playBtnPlay_svgSize );
            auto imageOn   = Drawable::createFromImageData (BinaryData::playBtnPause_svg,BinaryData::playBtnPause_svgSize);
            button->setImages (imageOff.get (),nullptr,nullptr,nullptr,imageOn.get (),nullptr,nullptr,nullptr);

        }break;
        case ConfigurableContainer::Crossfader:      break;
        case LoadLeft: {

            DrawableButtonAdaptive *load = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
            load->setImages (image.get ());

        } break;
        case LoadRight: {

            DrawableButtonAdaptive *load = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
            load->setImages (image.get ());

        } break;
        case ScrollDown: {

            DrawableButtonAdaptive *scroll = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
            scroll->setImages (image.get ());

        } break;
        case ScrollUp: {

            DrawableButtonAdaptive *browser = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
            browser->setImages (image.get ());

        } break;
        case ConfigurableContainer::Browser:{

            DrawableButtonAdaptive *browser = static_cast<DrawableButtonAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::menu_svg,BinaryData::menu_svgSize);
            browser->setImages (image.get ());

        }break;
        case ConfigurableContainer::HeadphoneOut:    break;
        case ConfigurableContainer::Sync:            break;
        case ConfigurableContainer::SyncMaster:      break;
        case ConfigurableContainer::MasterVolume:    break;
        case ConfigurableContainer::HeadphoneVolume: break;
        case ConfigurableContainer::Seek: {

        } break;
        case ConfigurableContainer::Cue: {

        } break;
        case ConfigurableContainer::HPLPFilter:{

            SliderAdaptive *hplpfilter = static_cast<SliderAdaptive*>(comp.get());
            //auto slider = dynamic_cast<SliderAdaptive*>(comp);
            auto image = Drawable::createFromImageData (BinaryData::knob_svg,BinaryData::knob_svgSize);
            //auto image = Drawable::createFromImageData (BinaryData::knob_eps,BinaryData::knob_epsSize);
            hplpfilter->setImage (image.get());//std::move(shape));

            hplpfilter->setSnapToMiddleValue(true);
            hplpfilter->setDoubleClickReturnValue (true, 0.5f*hplpfilter->getRange ().getLength ());
            hplpfilter->setValue (0.5f*hplpfilter->getRange ().getLength ());

        }break;
        case ConfigurableContainer::Volume:{

            SliderAdaptive *volume = static_cast<SliderAdaptive*>(comp.get());
            auto image = Drawable::createFromImageData (BinaryData::volume_svg,BinaryData::volume_svgSize);
            volume->setImage (image.get());//std::move(shape));

        }break;
        case ConfigurableContainer::Loop:{

            SliderAdaptive *loop = static_cast<SliderAdaptive*>(comp.get());
            loop->setRange(0,6,1);// da 1/8 a 8 barre
            loop->setValue(4);

        }break;
        default: break;
        }
    }

}

void ConfigurableContainer::paint (juce::Graphics& /*g*/) {}


void ConfigurableContainer::mouseEnter(const MouseEvent &/*event*/)
{
    if (onMouseEnter) onMouseEnter();
}

void ConfigurableContainer::mouseExit(const MouseEvent &/*event*/)
{
    if (onMouseExit) onMouseExit();
}

uint ConfigurableContainer::getNumRadialComponents() const
{
    //prob si può fare meglio
    uint count = 0;
    for (auto& [tipo,comp] : components)
        if (isRadialComponent(ConfigurableContainer::ComponentType(tipo)))  count++;
    return count;
}

uint ConfigurableContainer::getNumComponents() const
{
    return components.size ();
}

void ConfigurableContainer::setComponentOnValueChange(const ConfigurableContainer::ComponentType componentType, std::function<void (const int val)> newComponentOnValueChange)
{
    if (components.count (componentType)){
        SliderAdaptive *slider = dynamic_cast<SliderAdaptive*>(components[componentType].get());
        //NOTE: non sono sicuro di quanto questa sia una ciofecata
        //NOTE: non so se la capture clause "=" sia la scelta miogliore, ma funziona
        if(slider) slider->onValueChange =[=]{ newComponentOnValueChange(slider->getValue ());};
    }
}

void ConfigurableContainer::setComponentOnClick(const ConfigurableContainer::ComponentType componentType, std::function<void ()> newComponentOnClick)
{
    if(components.count (componentType)){
        SliderAdaptive         *slider = dynamic_cast<SliderAdaptive*>         (components[componentType].get());
        DrawableButtonAdaptive *button = dynamic_cast<DrawableButtonAdaptive*> (components[componentType].get());

        if(slider)      slider->onMouseUp = newComponentOnClick;
        else if(button) button->onClick   = newComponentOnClick;
    }

}



