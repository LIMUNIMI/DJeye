#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
//#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

#include "Parameters.h"
#include "Components/Controller.h"

//==============================================================================


class MainComponent  : public juce::Component/*: public juce::AnimatedAppComponent*/
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    //void update() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    Controller controller;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
