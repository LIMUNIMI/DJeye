#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"
#include "SliderAdaptive.h"
#include "DrawableButtonAdaptive.h"

/*deck must be square (?)*/
class Deck : public juce::Component/*, public juce::AudioProcessorValueTreeState::Listener*/
{

public:    
    //TODO: riposizionare questo enum
    /**
     * @brief The ComponentType enum describes which type of components can be in the controller
     */
    enum ComponentType{
        Play,           // stops and plays the track
        Crossfader,     // Crossfades between tracks
        SyncMaster,     // Controls if the track is the tempo master for sync
        Sync,           // Controls the sync
        HeadphoneOut,   // Controls if track is sent to headphone output
        HeadphoneVolume,// Controls the global volume in the headphones
        MasterVolume,   // Controls the master volume
        Browser,        // Opens a browser to choose tracks
        //radialcomponents:
        Seek,           // Seeks through track
        Cue,            // sets unsets and triggers cuepoints
        HPLPFilter,     // controls HP LP filter knob
        Volume,         // controls track volume
        Loop            // Controls loops parameters (size,etc)
    };

    Deck(const std::vector<Deck::ComponentType> ComponentList);
    //Deck(const Deck::ComponentType* ComponentList);
    //Deck(std::unique_ptr<int>... ComponentList);
    ~Deck();
    //juce::AudioProcessorValueTreeState j;
    void paint (juce::Graphics&) override;

    void resized() override;

    void mouseEnter(const MouseEvent &event) override;
    void mouseExit (const MouseEvent &event) override;

    /** You can assign a lambdas to this callback object to have it called when the component's focus changes. */
    //NOTE: no enter or exit is triggered if the mouse is down while entering
    std::function<void()> onMouseEnter;
    std::function<void()> onMouseExit ;

    int getNumRadialComponents() const;

    //    const std::map<const ComponentType, Component> &getComponents() const;
    //    void setComponents(const std::map<const ComponentType, Component> &newComponents);

    const std::map<const ComponentType, std::function<void> *> &getComponentsActions() const;
    void setComponentsActions(const std::map<const ComponentType, std::function<void> *> &newComponentsActions);

protected:

    SliderAdaptive testSlider2;

    //std::map<const ComponentType, Component> components;
    std::map<const uint, Component*> components;
    std::map<const ComponentType, std::function<void(uint)>&> componentsActions; // pensare a come gestire componenti che hanno più funzionalità

    // Usando queste misure, si ritrova un non parallelismo tra i lati degli slider, mentre con un metodo tau/NUM_COMP e poi spingendo i componenti verso l'esterno, si ottiene una sezione "centrale" non perfettamente circolare.
    float getComponentSeparationAngle() { return (MathConstants<float>::twoPi / getNumRadialComponents()) * SEPARATION_TO_COMPONENT_DIMENSION_RATIO; }
    float getComponentAngle()           { return (MathConstants<float>::twoPi - (getComponentSeparationAngle () * getNumRadialComponents()))
                / getNumRadialComponents() ;}

private:
uint numComponents = 0;

// static constexpr auto tau = MathConstants<float>::twoPi;
// static constexpr auto componentSeparationAngle = (tau / NUM_COMPONENTS) * SEPARATION_TO_COMPONENT_DIMENSION_RATIO;
// static constexpr auto componentAngle = (tau - (componentSeparationAngle*(NUM_COMPONENTS-1)))/NUM_COMPONENTS

JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)

};

