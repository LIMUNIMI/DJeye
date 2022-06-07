#include "SliderAdapted.h"

SliderAdapted::SliderAdapted()/*:Slider::Slider()*/
{
    //ResizeBoundingBoxToFit ();
}
void SliderAdapted::resizeBoundingBoxToFit (){

    auto rotParams = getRotaryParameters();
    Path slice;
    /*slice.addPieSegment (getBounds ().toFloat (),
                         rotParams.startAngleRadians + (rotParams.startAngleRadians * COMPONENT_ACCURACY_PADDING_RATIO),
                         rotParams.endAngleRadians - (rotParams.endAngleRadians * COMPONENT_ACCURACY_PADDING_RATIO),
                         SLIDER_TO_INNER_CIRCLE_RATIO + ( SLIDER_TO_INNER_CIRCLE_RATIO * COMPONENT_ACCURACY_PADDING_RATIO));*/
    slice.addPieSegment (getBounds ().toFloat (),
                         rotParams.startAngleRadians,
                         rotParams.endAngleRadians,
                         SLIDER_TO_INNER_CIRCLE_RATIO);
    setBoundingBox (slice);
}


void SliderAdapted::setRotaryParameters(RotaryParameters p) noexcept
{
    Slider::setRotaryParameters (p);
    resizeBoundingBoxToFit ();
};

void SliderAdapted::setRotaryParameters(float startAngleRadians, float endAngleRadians, bool stopAtEnd) noexcept{
    Slider::setRotaryParameters (startAngleRadians,endAngleRadians,stopAtEnd);
    resizeBoundingBoxToFit ();
}


bool SliderAdapted::hitTest(int x, int y)
{
    return boundingBox.contains (x,y,0.1f);
}

void SliderAdapted::resized()
{
    Slider::resized ();
    resizeBoundingBoxToFit ();
}

void SliderAdapted::setBoundingBox(Path newBoundingBox)
{
    boundingBox = newBoundingBox;
}

Path SliderAdapted::getBoundingBox(){
    return boundingBox;
};
