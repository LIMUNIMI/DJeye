#pragma once
#include "SliderAdapted.h"
/**
 * @brief Simply a sliderAdapted with a custom snapping whoch snaps on th emiddle
 */
class SliderAdaptedSnap : public SliderAdapted
{
public:
    SliderAdaptedSnap();

private:
    /**
     * @brief snapValue note that it snaps only when using velocitydrag, otherwise (like scrolling with mousewheel) it wouldn't move after snapping
     */
    double snapValue(double attemptedValue, DragMode dragMode) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderAdaptedSnap)

};

