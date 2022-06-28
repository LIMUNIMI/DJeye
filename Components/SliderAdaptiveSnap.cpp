#include "SliderAdaptiveSnap.h"

SliderAdaptiveSnap::SliderAdaptiveSnap() {}

double SliderAdaptiveSnap::snapValue(double attemptedValue, DragMode dragMode)
{
    auto range = getRange ().getLength ();

    return (0.45f * range < attemptedValue &&
            attemptedValue < 0.55f * range &&
            dragMode == DragMode::absoluteDrag) ?  range*0.5f : attemptedValue;

}
