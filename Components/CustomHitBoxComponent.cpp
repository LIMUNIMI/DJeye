#include "CustomHitBoxComponent.h"

CustomHitBoxComponent::CustomHitBoxComponent(){}

void CustomHitBoxComponent::setHitBox(const Path& newHitBox)
{
    HitBox.setPath (newHitBox);
    updateHitBoxBounds();
}

void CustomHitBoxComponent::setHitBox(const Path&& newHitBox)
{
    setHitBox(newHitBox);
}

Path CustomHitBoxComponent::getHitBox() const {
    return HitBox.getPath ();
};

float CustomHitBoxComponent::getAccuracyPaddingRatio() const
{
    return accuracyPaddingRatio;
}

void CustomHitBoxComponent::setAccuracyPaddingRatio(float newAccuracyPaddingRatio)
{
    accuracyPaddingRatio = newAccuracyPaddingRatio;
    updateHitBoxBounds();
}

//bool CustomHitBoxComponent::hitTest(int x, int y)
//{
//    return HitBox.getPath ().contains (x,y);
//}
