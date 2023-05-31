#include "VerticalStrip.h"

VerticalStrip::VerticalStrip(const std::vector<ConfigurableContainer::ComponentType> ComponentList) :
    ConfigurableContainer{ComponentList}
{
    componentList = ComponentList;
}

void VerticalStrip::resized()
{
    auto numComponents = getNumComponents () + getNumSpacers ();//1 è quello che sta nei components

    if(numComponents > 0){
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

void VerticalStrip::paint(Graphics &/*g*/){}

const bool VerticalStrip::isRadialComponent(const ComponentType /*componentType*/) const
{
    return false;
}

const uint VerticalStrip::getNumSpacers() const
{
    return std::count(componentList.begin(),componentList.end(),ConfigurableContainer::Spacer);
}
