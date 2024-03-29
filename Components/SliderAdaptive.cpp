﻿#include "SliderAdaptive.h"

SliderAdaptive::SliderAdaptive()/*:Slider::Slider()*/
{
    addChildComponent (HitBox);
    //addAndMakeVisible (HitBox);
}

Path SliderAdaptive::MakeSlice(const Rectangle<float>& rectToFitIn,
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

bool SliderAdaptive::getAutoFitHitBoxToRotaryParameters() const
{
    return autoFitHitBoxToRotaryParameters;
}

void SliderAdaptive::setAutoFitHitBoxToRotaryParameters(bool newAutoFitToRotaryParameters)
{
    autoFitHitBoxToRotaryParameters = newAutoFitToRotaryParameters;
    updateHitBoxBounds();
}

bool SliderAdaptive::getSnapToMiddleValue() const
{
    return snapToMiddleValue;
}

void SliderAdaptive::setSnapToMiddleValue(bool newSnapToMiddleValue)
{
    snapToMiddleValue = newSnapToMiddleValue;
}

void SliderAdaptive::resizeHitBoxToFitRotaryParameters (){
    //TODO: da fare solo se è rotary
    auto rotParams = getRotaryParameters();

    auto padding = std::abs(rotParams.startAngleRadians - rotParams.endAngleRadians)*accuracyPaddingRatio;
    auto slice = MakeSlice(getLocalBounds ().toFloat ().reduced(SLIDER_PADDING),padding,padding*0.5f);
    //NB: questo approccio riduce tutti i margini eccetto quello del cerchio più esterno
    //inoltre non è accurato aggiungere al cerchio interno un padding relativo al raggio
    setHitBox (slice);

    //forse verrà spostato
    if (image != nullptr){
        auto localBounds = getLocalBounds ().toFloat ();
        //auto rotParams = getRotaryParameters();
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

void SliderAdaptive::resizeHitBoxToFitBounds()
{//TODO: test
    /* NOTE: quando si lavora con i drawables si dovrebbe solo modificare il transform e non i bounds
 * https://forum.juce.com/t/drawablecomposite-resets-coordinates-when-inserting-drawableimage/25851/4*/

    auto mindim = jmin(getLocalBounds ().getHeight (),getLocalBounds ().getWidth ());

    HitBox.setTransformToFit (getLocalBounds().toFloat ().reduced (mindim*accuracyPaddingRatio),juce::RectanglePlacement::centred);

    Path p = HitBox.getPath ();
    p.applyTransform (HitBox.getTransform ());
    HitBox.setPath(p);
}

void SliderAdaptive::updateHitBoxBounds()
{
    //TODO: meglio usare getter oppure il parametro in sè?
    getAutoFitHitBoxToRotaryParameters ()? resizeHitBoxToFitRotaryParameters() : resizeHitBoxToFitBounds ();
}

void SliderAdaptive::setRotaryParameters(RotaryParameters p) noexcept
{
    Slider::setRotaryParameters (p);
    updateHitBoxBounds ();
};

void SliderAdaptive::setRotaryParameters(float startAngleRadians, float endAngleRadians, bool stopAtEnd) noexcept
{
    Slider::setRotaryParameters (startAngleRadians,endAngleRadians,stopAtEnd);
    updateHitBoxBounds ();
}

bool SliderAdaptive::hitTest(int x, int y)
{
    return HitBox.getPath ().contains (x,y/*,0.1f*/);
}

void SliderAdaptive::paint(Graphics& g)
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

void SliderAdaptive::resized()
{
    Slider::resized ();
    updateHitBoxBounds ();
}

void SliderAdaptive::setHitBox(const Path& newHitBox)
{
    HitBox.setPath (newHitBox);
}

void SliderAdaptive::setHitBox(const Path&& newHitBox)
{
    HitBox.setPath (std::move(newHitBox));
    updateHitBoxBounds();
}

Path SliderAdaptive::getHitBox() const {
    return HitBox.getPath ();
};

void SliderAdaptive::setImage (const Drawable* newImage)
{//TODO: usare i maledetti unique ptrs che non riesco a far funzionare
    jassert (newImage != nullptr);
    image = newImage->createCopy();
    addAndMakeVisible (*image);
    resized();
}

void SliderAdaptive::mouseUp(const MouseEvent& me)
{
    if (me.mouseWasClicked () && onMouseUp !=nullptr) onMouseUp();
}

double SliderAdaptive::snapValue(double attemptedValue, DragMode dragMode)
{
    if (getSnapToMiddleValue()){
        auto range = getRange ().getLength ();

        return (0.45f * range < attemptedValue &&
                attemptedValue < 0.55f * range &&
                dragMode == DragMode::absoluteDrag) ?  range*0.5f : attemptedValue;
    }else return attemptedValue;
}

int SliderAdaptive::getNumWheelTicksIgnored() const
{
    return numWheelTicksIgnored;
}

void SliderAdaptive::setNumWheelTicksIgnored(int newNumWheelTicksIgnored)
{
    jassert(newNumWheelTicksIgnored >= 0);
    numWheelTicksIgnored = newNumWheelTicksIgnored;
}

float SliderAdaptive::getAccuracyPaddingRatio() const
{
    return accuracyPaddingRatio;
}

void SliderAdaptive::setAccuracyPaddingRatio(float newAccuracyPaddingRatio)
{
    accuracyPaddingRatio = newAccuracyPaddingRatio;
    updateHitBoxBounds();
}

void SliderAdaptive::mouseWheelMove(const MouseEvent &e, const MouseWheelDetails &wheel)
{
    wheelTickCounter = (wheelTickCounter + 1) % (getNumWheelTicksIgnored() + 1);
    DBG(wheelTickCounter);
    if (wheelTickCounter == 0)
        Slider::mouseWheelMove(e,wheel);
}


