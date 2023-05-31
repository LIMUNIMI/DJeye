#pragma once
#include <JuceHeader.h>
#include "Parameters.h"
#include "MyLookAndFeel.h"
#include "SliderAdapted.h"
#include "SliderAdaptedSnap.h"
#include "DrawableButtonAdapted.h"


/*deck must be square*/
class Deck : public juce::Component
{

public:
    Deck();
    ~Deck();

    void paint (juce::Graphics&) override;

    void resized() override;

    void mouseEnter(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;

    /** You can assign a lambdas to this callback object to have it called when the component's focus changes. */
    //NOTE: no enter o exuit is triggered if the mouse is down while entering
    std::function<void()> onMouseEnter;
    std::function<void()> onMouseExit;



protected:
    SliderAdapted testSlider1;
    SliderAdaptedSnap testSlider2;
    DrawableButtonAdapted testButton;

    MyLookAndFeel laf;

private:
    // TODO: meglio di un define in questo caso siccome c'è una divisione?
    static constexpr auto tau = MathConstants<float>::twoPi;
    static constexpr auto componentSeparationAngle = (tau / NUM_COMPONENTS) * SEPARATION_TO_COMPONENT_DIMENSION_RATIO;
    static constexpr auto componentAngle = (tau - (componentSeparationAngle*(NUM_COMPONENTS-1)))/NUM_COMPONENTS;
    //usando queste misure, si ritrova un nun parallelismo tra i lati degli slider, mentre con un metodo tau/NUM_COMP e poi spingendo i componenti verso l'esterno, si ottiene una sezione "centrale" non perfettamente circolare.
Array<float> ciaone;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)

};

