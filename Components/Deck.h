#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"
#include "SliderAdaptive.h"
#include "DrawableButtonAdaptive.h"

/**
 * @brief The Deck class contains sliders and buttons
 */
class Deck : public juce::Component/*, public juce::AudioProcessorValueTreeState::Listener*/
{

public:    
    //TODO: utilizzare la funzione isRadialComponent ?
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
    /**
     * @brief Deck
     * @param ComponentList: the list of Deck::ComponentTypes the Deck will hold. note that all radial components are inserted
     *                       clockwise in the order of declaration
     */
    Deck(const std::vector<Deck::ComponentType> ComponentList);
    ~Deck();

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

    /**
     * @brief setComponentOnValueChange
     * @param componentType: ComponentType for which to set the lambda
     * @param newComponentOnValueChange: lambda function to set the antion to
     */
    void setComponentOnValueChange(const ComponentType componentType, std::function<void (const int val)> newComponentOnValueChange);

    /**
     * @brief set the component lambda to execute whene it is clicked
     * @param componentType: ComponentType for which to set the lambda
     * @param newComponentOnValueChange: lambda function to set the action to
     * NOTE: for sliders it is actually assigned to onMouseUp()
     */
    void setComponentOnClick(const ComponentType componentType, std::function<void ()> newComponentOnClick);

    /**
    * @brief returns if the given component type is a radial component
    * @param componentType the component type to check
    */
    const bool isRadialComponent(const ComponentType componentType) const;

protected:

    std::map<const uint, std::unique_ptr<Component>> components;
    std::map<const ComponentType, std::function<void()>&> componentsOnValueChange;
    std::map<const ComponentType, std::function<void()>&> componentsOnClick;

    /**
     * @brief returns the angle in between the radial components
     * NOTE: Usando queste misure, si ritrova un non parallelismo tra i lati degli slider,
     * mentre con un metodo tau/NUM_COMP e poi spingendo i componenti verso l'esterno,
     * si ottiene una sezione "centrale" non perfettamente circolare.
     */
    float getComponentSeparationAngle() {
        return (MathConstants<float>::twoPi / getNumRadialComponents()) * SEPARATION_TO_COMPONENT_DIMENSION_RATIO;
    }
    /**
     * @brief returns the angle in of the radial components
     * @see getComponentSeparationAngle
     */
    float getComponentAngle(){
        return (MathConstants<float>::twoPi - (getComponentSeparationAngle () * getNumRadialComponents()))
                / getNumRadialComponents() ;
    }

private:
    uint numComponents = 0;

    // static constexpr auto tau = MathConstants<float>::twoPi;
    // static constexpr auto componentSeparationAngle = (tau / NUM_COMPONENTS) * SEPARATION_TO_COMPONENT_DIMENSION_RATIO;
    // static constexpr auto componentAngle = (tau - (componentSeparationAngle*(NUM_COMPONENTS-1)))/NUM_COMPONENTS

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)

};

