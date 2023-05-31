#include "DrawableButtonAdapted.h"

DrawableButtonAdapted::DrawableButtonAdapted(const String &buttonName, ButtonStyle buttonStyle):
    DrawableButton::DrawableButton(buttonName,buttonStyle)
{
    addChildComponent (HitBox);
    //addAndMakeVisible (HitBox);
}

bool DrawableButtonAdapted::hitTest(int x, int y)
{
    return HitBox.getPath ().contains (x,y/*,0.1f*/);
}

void DrawableButtonAdapted::resized()
{

    /* NOTE: quando si lavora con i drawables si dovrebbe solo modificare il transform e non i bounds
     * https://forum.juce.com/t/drawablecomposite-resets-coordinates-when-inserting-drawableimage/25851/4
*/
    DrawableButton::resized ();

    auto mindim = jmin(getLocalBounds ().getHeight (),getLocalBounds ().getWidth ());

    HitBox.setTransformToFit (getLocalBounds().toFloat ().reduced (mindim*ComponentActualAccuracyPaggingRatio),juce::RectanglePlacement::centred);

    Path p = HitBox.getPath ();
    p.applyTransform (HitBox.getTransform ());
    HitBox.setPath(p);

}


Path DrawableButtonAdapted::getHitBox()
{
    return HitBox.getPath ();
}

void DrawableButtonAdapted::setHitBox(const Path& newHitBox)
{
    HitBox.setPath (newHitBox);
}

void DrawableButtonAdapted::setHitBox(const Path&& newHitBox)
{
    HitBox.setPath (std::move(newHitBox));
}

