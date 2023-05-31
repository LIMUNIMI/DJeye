#include "SliderAdapted.h"

SliderAdapted::SliderAdapted()/*:Slider::Slider()*/
{
    addChildComponent (boundingBox);
    //addAndMakeVisible (boundingBox);
}

Path SliderAdapted::MakeSlice(const Rectangle<float>& rectToFitIn,
                              const float paddingSides,
                              const float paddingTopBottom) const
{
    auto rotParams = getRotaryParameters();

    Path slice;
    /* getlocalBounds() restuisce un rettangolo con dimensioni del componente che lo chiama posizionato a 0,0. usalo per impostare i parametri dei componenti figliù
     * è equivalente ad un rect<> (0, 0, getWidth(), getHeight())
     * getBounds() stessa roba ma le coordinate sono relative al componente padre*/
    slice.addPieSegment (rectToFitIn/*.reduced (paddingTopBottom *0.5)*/,
                         rotParams.startAngleRadians + paddingSides*0.5f,
                         rotParams.endAngleRadians - paddingSides*0.5f,
                         SLIDER_TO_INNER_CIRCLE_RATIO + paddingTopBottom*0.5f);

    //slice.applyTransform (AffineTransform::translation ())
    return slice;
}

void SliderAdapted::resizeBoundingBoxToFitRotaryParameters (){
    auto rotParams = getRotaryParameters();

    auto padding = std::abs(rotParams.startAngleRadians - rotParams.endAngleRadians)*COMPONENT_ACCURACY_PADDING_RATIO*2;
    auto slice = MakeSlice(getLocalBounds ().toFloat (),padding,padding);
    //NB: questo approccio riduce tutti i margini eccetto quello del cerchio più esterno
    //inoltre non è accurato aggiungere al cerchio interno un padding relativo al raggio
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

void SliderAdapted::paint(Graphics& g)
{
    Slider::paint (g);
    //display bounding box
    g.setColour (juce::Colours::green);
    //g.fillPath (boundingBox.getPath ());


    g.setColour (juce::Colours::red);
    //g.drawRect (MakeSlice (getLocalBounds ().toFloat ()).getBounds ());
    g.setColour (juce::Colours::blue);
    //g.drawRect ( getLocalBounds ().toFloat ());
}

void SliderAdapted::resized()
{
    Slider::resized ();
    resizeBoundingBoxToFitRotaryParameters ();

    if (currentImage != nullptr){
        auto localBounds = getLocalBounds ().toFloat ();
        auto rotParams = getRotaryParameters();

        //find center point
        auto raggioEsterno = localBounds.getWidth ()*0.5f;
        auto raggioInterno = SLIDER_TO_INNER_CIRCLE_RATIO*raggioEsterno;
        auto raggio = raggioInterno + (raggioEsterno - raggioInterno)*0.5f;

        auto angoloCentro = rotParams.startAngleRadians +
                /*std::abs*/(rotParams.endAngleRadians - rotParams.startAngleRadians)*0.5f;

        auto centre = localBounds.getCentre ().getPointOnCircumference (raggio,angoloCentro);

        //create square to fit image
        auto vertex = raggio / MathConstants<float>::sqrt2;
        auto boundsToContainImg = Rectangle<float>(vertex,vertex).reduced (vertex*0.25f);
        boundsToContainImg.setCentre (centre);

        currentImage->setTransformToFit (boundsToContainImg,juce::RectanglePlacement::centred);
    }

}


void SliderAdapted::setBoundingBox(const Path& newBoundingBox)
{
    boundingBox.setPath (newBoundingBox);
}


Path SliderAdapted::getBoundingBox() const {
    return boundingBox.getPath ();
};

void SliderAdapted::setImage (const Drawable* newImage)
{//TODO: far diventare tutto constreference e avere solo una variabile immagine
    jassert (newImage != nullptr);

    normalImage = newImage->createCopy();
    currentImage = normalImage.get ();
    //image = std::move(newImage);
    //image->setTransformToFit (boundingBox.getBounds ().reduced (10).toFloat (),juce::RectanglePlacement::centred);
    //image->setInterceptsMouseClicks (false, false);//needed?
    addAndMakeVisible (currentImage);
}

void SliderAdapted::mouseUp(const MouseEvent &)
{

}

//void SliderAdapted::setEdgeIndent (const int numPixelsIndent)
//{
//    edgeIndent = numPixelsIndent;
//    repaint();
//    resized();
//}
