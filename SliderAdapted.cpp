#include "SliderAdapted.h"

SliderAdapted::SliderAdapted()/*:Slider::Slider()*/
{
    addChildComponent (boundingBox);
}
void SliderAdapted::resizeBoundingBoxToFitRotaryParameters (){

    auto rotParams = getRotaryParameters();
    Path slice;

    //NB: questo approccio riduce tutti i margini eccetto quello del cerchio più esterno
    //inoltre non è accurato aggiungere un padding relativo al raggio al cerchio interno
    auto padding = std::abs(rotParams.startAngleRadians - rotParams.endAngleRadians)*COMPONENT_ACCURACY_PADDING_RATIO*2;//*2 perchè il padding viene tolto da entrambi i lati
    slice.addPieSegment (getLocalBounds ().toFloat (),
                         rotParams.startAngleRadians + padding,
                         rotParams.endAngleRadians - padding,
                         SLIDER_TO_INNER_CIRCLE_RATIO + padding);

    //getlocalBounds() restuisce un rettangolo con dimensioni del componente che lo chiama posizionato a 0,0. usalo per impostare i parametri dei componenti figliù
    // è equivalente ad un rect<> (0, 0, getWidth(), getHeight())
    //getBounds() stessa roba ma le coordinate sono relative al componente padre
    setBoundingBox (slice);
}


void SliderAdapted::setRotaryParameters(RotaryParameters p) noexcept
{
    Slider::setRotaryParameters (p);
    resizeBoundingBoxToFitRotaryParameters ();
};

void SliderAdapted::setRotaryParameters(float startAngleRadians, float endAngleRadians, bool stopAtEnd) noexcept{
    Slider::setRotaryParameters (startAngleRadians,endAngleRadians,stopAtEnd);
    resizeBoundingBoxToFitRotaryParameters ();
}

bool SliderAdapted::hitTest(int x, int y)
{
    return boundingBox.getPath ().contains (x,y/*,0.1f*/);
}

void SliderAdapted::resized()
{
    Slider::resized ();
    resizeBoundingBoxToFitRotaryParameters ();
}

void SliderAdapted::setBoundingBox(Path newBoundingBox) //protected?
{
    boundingBox.setPath (newBoundingBox);
}

Path SliderAdapted::getBoundingBox(){ //protected?
    return boundingBox.getPath ();
};
