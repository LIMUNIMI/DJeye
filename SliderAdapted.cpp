#include "SliderAdapted.h"

SliderAdapted::SliderAdapted()/*:Slider::Slider()*/
{
    addChildComponent (HitBox);
    //addAndMakeVisible (HitBox);
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
    slice.addPieSegment (rectToFitIn/*.reduced (paddingTopBottom)*/,
                         rotParams.startAngleRadians + paddingSides,
                         rotParams.endAngleRadians - paddingSides,
                         INNER_CIRCLE_TO_SLIDER_RATIO + paddingTopBottom);

    //slice.applyTransform (AffineTransform::translation ())
    return slice;
}

void SliderAdapted::resizeHitBoxToFitRotaryParameters (){
    auto rotParams = getRotaryParameters();

    auto padding = std::abs(rotParams.startAngleRadians - rotParams.endAngleRadians)*ComponentActualAccuracyPaggingRatio;
    auto slice = MakeSlice(getLocalBounds ().toFloat ().reduced(SLIDER_PADDING),padding,padding*0.5f);
    //NB: questo approccio riduce tutti i margini eccetto quello del cerchio più esterno
    //inoltre non è accurato aggiungere al cerchio interno un padding relativo al raggio
    setHitBox (slice);
}

void SliderAdapted::setRotaryParameters(RotaryParameters p) noexcept
{
    Slider::setRotaryParameters (p);
    resizeHitBoxToFitRotaryParameters ();
};

void SliderAdapted::setRotaryParameters(float startAngleRadians, float endAngleRadians, bool stopAtEnd) noexcept{
    Slider::setRotaryParameters (startAngleRadians,endAngleRadians,stopAtEnd);
    resizeHitBoxToFitRotaryParameters ();
}

bool SliderAdapted::hitTest(int x, int y)
{
    return HitBox.getPath ().contains (x,y/*,0.1f*/);
}

void SliderAdapted::paint(Graphics& g)
{
    Slider::paint (g);
    //display bounding box
    g.setColour (juce::Colours::green);
    //g.fillPath (HitBox.getPath ());


    g.setColour (juce::Colours::red);
    //g.drawRect (MakeSlice (getLocalBounds ().toFloat ()).getBounds ());
    g.setColour (juce::Colours::blue);
    //g.drawRect ( getLocalBounds ().toFloat ());
}

void SliderAdapted::resized()
{
    Slider::resized ();
    resizeHitBoxToFitRotaryParameters ();

    if (image != nullptr){
        auto localBounds = getLocalBounds ().toFloat ();
        auto rotParams = getRotaryParameters();
        auto minDim = jmin(localBounds.getWidth (),localBounds.getHeight());

        //find center point
        auto raggioEsterno = minDim*0.5f - SLIDER_PADDING;
        auto raggioInterno = INNER_CIRCLE_TO_SLIDER_RATIO*raggioEsterno;
        auto raggio = raggioInterno + (raggioEsterno - raggioInterno)*0.5f;

        auto angoloCentro = rotParams.startAngleRadians +
                /*std::abs*/(rotParams.endAngleRadians - rotParams.startAngleRadians)*0.5f;

        auto centre = localBounds.getCentre ().getPointOnCircumference (raggio,angoloCentro);

        //create square to fit image
        auto vertex = raggio / MathConstants<float>::sqrt2;
        auto boundsToContainImg = Rectangle<float>(vertex,vertex).reduced (vertex*0.25f);
        boundsToContainImg.setCentre (centre);

        image->setTransformToFit (boundsToContainImg,juce::RectanglePlacement::centred);
    }

}
//JUCE sembra fregarsene
void SliderAdapted::setHitBox(const Path& newHitBox)
{
    HitBox.setPath (newHitBox);
}

void SliderAdapted::setHitBox(const Path&& newHitBox)
{
    HitBox.setPath (std::move(newHitBox));
}
Path SliderAdapted::getHitBox() const {
    return HitBox.getPath ();
};

void SliderAdapted::setImage (const Drawable* newImage)
{//TODO: usare i maledetti unique ptrs che non riesco a far funzionare
    jassert (newImage != nullptr);
    image = newImage->createCopy();
    addAndMakeVisible (*image);
    resized();
}

void SliderAdapted::mouseUp(const MouseEvent& me)
{
    if (me.mouseWasClicked () && onMouseUp !=nullptr){
        onMouseUp();
    }
}

//void SliderAdapted::setEdgeIndent (const int numPixelsIndent)
//{
//    edgeIndent = numPixelsIndent;
//    repaint();
//    resized();
//}
