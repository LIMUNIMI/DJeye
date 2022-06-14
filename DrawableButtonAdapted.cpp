#include "DrawableButtonAdapted.h"

DrawableButtonAdapted::DrawableButtonAdapted(const String &buttonName, ButtonStyle buttonStyle):
    DrawableButton::DrawableButton(buttonName,buttonStyle)
{
}

bool DrawableButtonAdapted::hitTest(int x, int y)
{
    return boundingBox.getPath ().contains (x,y/*,0.1f*/);
}
