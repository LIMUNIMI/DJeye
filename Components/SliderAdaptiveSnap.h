#pragma once
#include "SliderAdaptive.h"
/**
 * @brief Simply a sliderAdapted with a custom snapping which snaps on the middle
 */
class SliderAdaptiveSnap : public SliderAdaptive
{
public:
    SliderAdaptiveSnap();

private:
    /**
     * @brief snapValue note that it snaps only when using velocitydrag, otherwise (like scrolling with mousewheel) it wouldn't move after snapping
     */
    double snapValue(double attemptedValue, DragMode dragMode) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdaptiveSnap)

};

