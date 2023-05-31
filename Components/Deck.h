#pragma once

#include "ConfigurableContainer.h"
#include "../MyLookAndFeel_loop.h"
/**
 * @brief Deck contains some ConfigurableContainer::ComponentType components
 * it arranges the radial components in a circle, equally spacing between them.
 * NOTE: not all ConfigurableContainer::ComponentType are supported for now
 */
class Deck : public ConfigurableContainer{
public:
    /**
     * @brief Deck
     * @param ComponentList
     * radialComponents will be arranged in a clockwise manner following the order given in ComponentList
     */
    Deck(const std::vector<ConfigurableContainer::ComponentType> ComponentList);
    ~Deck(){};

    void resized() override;

    void paint(juce::Graphics &) override;

    const bool isRadialComponent(const ComponentType componentType) const override;

protected:

private:
    MyLookAndFeelLoop laf_loop;// this is kind of bad but forn now it works
};
