#pragma once
# include "ConfigurableContainer.h"
#include "DrawableButtonAdaptive.h"
#include "SliderAdaptive.h"

/**
 * @brief The VerticalStrip class is a component container which arranges components vertically.
 * note: not all components are supported yet
 */
class VerticalStrip : public ConfigurableContainer
{
public:
    /**
     * @brief VerticalStrip
     * @param ComponentList
     * components will be arranged in a top->bottom manner following the order given in ComponentList
     */
    VerticalStrip(const std::vector<ConfigurableContainer::ComponentType> ComponentList);
    ~VerticalStrip(){};

    void resized() override;

    void paint (Graphics &g) override;

    const bool isRadialComponent(const ComponentType componentType) const override;

    const uint getNumSpacers() const;

private:
    //devo mantenerla per poter posizionare i componenti in ordine, non co se è la best practice ma per ora lascio così
    std::vector<ConfigurableContainer::ComponentType> componentList;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalStrip)
};

