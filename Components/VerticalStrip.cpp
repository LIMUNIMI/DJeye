#include "VerticalStrip.h"

VerticalStrip::VerticalStrip(const std::vector<ConfigurableContainer::ComponentType> ComponentList) :
    ConfigurableContainer{ComponentList}
{
    componentList = ComponentList;
}

void VerticalStrip::resized()
{
    //Component::resized();
    //crossfader.setBounds    (area.removeFromBottom (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));
    //browserButton.setBounds (area.removeFromTop    (getHeight()*0.4).reduced (getWidth()*0.05,getHeight()*0.1));

    auto numComponents = getNumComponents () + getNumSpacers ();

    if(numComponents){
        auto remainingBounds = getLocalBounds ();
        int singleComponentHeight = remainingBounds.getHeight () / (int) numComponents;

        for (auto type : componentList)
        {
            if(type != ConfigurableContainer::Spacer) // un pò un accrocchio ma ok
                components[type]->setBounds (remainingBounds.removeFromTop (singleComponentHeight));
            else
                remainingBounds.removeFromTop (singleComponentHeight);
        }

    }
}

void VerticalStrip::paint(Graphics &g)
{
    g.fillAll (Colours::aliceblue);
}

const bool VerticalStrip::isRadialComponent(const ComponentType /*componentType*/) const
{
    return false;
}

const uint VerticalStrip::getNumSpacers() const
{
    return std::count(componentList.begin(),componentList.end(),ConfigurableContainer::Spacer);
}
