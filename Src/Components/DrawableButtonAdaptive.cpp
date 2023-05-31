#include "DrawableButtonAdaptive.h"

DrawableButtonAdaptive::DrawableButtonAdaptive(const String &buttonName, ButtonStyle buttonStyle):
    DrawableButton::DrawableButton(buttonName,buttonStyle)
{
#if JUCE_DEBUG
    addAndMakeVisible (HitBox);
#else
    addChildComponent (HitBox);
#endif
}

bool DrawableButtonAdaptive::hitTest(int x, int y)
{
    return HitBox.getPath ().contains (x,y/*,0.1f*/);
}

void DrawableButtonAdaptive::resized()
{
    DrawableButton::resized ();

    updateHitBoxBounds();
}

Path DrawableButtonAdaptive::getHitBox() const noexcept
{
    return HitBox.getPath ();
}

void DrawableButtonAdaptive::setHitBox(const Path& newHitBox)
{
    HitBox.setPath (newHitBox);
    updateHitBoxBounds();
}

void DrawableButtonAdaptive::setHitBox(const Path&& newHitBox)
{
    HitBox.setPath (std::move(newHitBox));
    updateHitBoxBounds();
}

float DrawableButtonAdaptive::getAccuracyPaddingRatio() const
{
    return accuracyPaddingRatio;
}

void DrawableButtonAdaptive::setAccuracyPaddingRatio(float newAccuracyPaddingRatio)
{
    accuracyPaddingRatio = newAccuracyPaddingRatio;
    updateHitBoxBounds();
}

void DrawableButtonAdaptive::updateHitBoxBounds()
{
    /* NOTE: quando si lavora con i drawables si dovrebbe solo modificare il transform e non i bounds
 * https://forum.juce.com/t/drawablecomposite-resets-coordinates-when-inserting-drawableimage/25851/4*/
    auto mindim = jmin(getLocalBounds ().getHeight (),getLocalBounds ().getWidth ());

    Path p = HitBox.getPath (); //get current path (usually new path)
    HitBox.setTransformToFit (getLocalBounds().toFloat ().reduced(mindim*accuracyPaddingRatio),juce::RectanglePlacement::fillDestination);
    p.applyTransform (HitBox.getTransform ());
    HitBox.setPath(p);
}

