#pragma once
#include <JuceHeader.h>

class DrawableButtonAdapted : public DrawableButton
{
public:
    DrawableButtonAdapted();
    ~DrawableButtonAdapted{};

private:
    bool hitTest(int x, int y) override;

};


