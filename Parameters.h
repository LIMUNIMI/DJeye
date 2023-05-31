#pragma once
#define NUM_COMPONENTS 7
//lo spazio di separazione tra i componenti è SEPARATION_TO_COMPONENT_RATIO * loro dimensione
#define SEPARATION_TO_COMPONENT_DIMENSION_RATIO 0.15f
#define INNER_CIRCLE_TO_SLIDER_RATIO 0.55f
//quanto restringere le hitbox dei componenti in relazione alla loro grandezza 0=nessuna restrizione, 1 = restrizione completa
#define COMPONENT_ACCURACY_PADDING_RATIO 0.2f
//TODO: meglio constexpr o un'altra define?
constexpr float ComponentActualAccuracyPaddingRatio = COMPONENT_ACCURACY_PADDING_RATIO * 0.5f;
#define COMPONENT_CORNER_ROUNDING 5.0f
#define DECK_PADDING 5.0f
#define DECK_MARGIN 10.0f
#define SLIDER_PADDING 2.5f //gli slider verranno disegnati rientrati di questo amount rispetto ai propri bounds
