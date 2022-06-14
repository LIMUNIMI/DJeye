#include "SliderAdapted.h"

/*nn utilizzo un oggetto di tipo drawableShape per mantenere il path
 * perchè credo che aggiunga un livello di complicazione inutile.
*/
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
    slice.addPieSegment (getLocalBounds ().toFloat (),
                         rotParams.startAngleRadians,
                         rotParams.endAngleRadians,
                         SLIDER_TO_INNER_CIRCLE_RATIO);
    //TODO: getlocalBounds o getBounds() o getScreenBounds ()?
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
    //resizeBoundingBoxToFit ();
    return boundingBox.contains (x,y/*,0.1f*/);
}

void SliderAdapted::resized()
{
    Slider::resized ();
    resizeBoundingBoxToFit ();
}
void SliderAdapted::moved()
{
    Slider::moved ();
    //resizeBoundingBoxToFit ();
}

void SliderAdapted::setBoundingBox(Path newBoundingBox) //protected?
{
    boundingBox = newBoundingBox;
}

Path SliderAdapted::getBoundingBox(){
    return boundingBox;
};
