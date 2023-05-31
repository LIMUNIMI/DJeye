#pragma once
//#define NUM_COMPONENTS 7
//lo spazio di separazione tra i componenti è SEPARATION_TO_COMPONENT_RATIO * loro dimensione
#define SEPARATION_TO_COMPONENT_DIMENSION_RATIO 0.25f
#define INNER_CIRCLE_TO_SLIDER_RATIO 0.55f
//quanto restringere le hitbox dei componenti in relazione alla loro grandezza 0=nessuna restrizione, 1 = restrizione completa
#define COMPONENT_ACCURACY_PADDING_RATIO 0.01f
//TODO: meglio constexpr o un'altra define?
constexpr float ComponentActualAccuracyPaddingRatio = COMPONENT_ACCURACY_PADDING_RATIO * 0.5f;
#define COMPONENT_CORNER_ROUNDING 8.0f
#define DECK_PADDING 5.0f
#define DECK_MARGIN 10.0f
#define SLIDER_PADDING 2.5f //gli slider verranno disegnati rientrati di questo amount rispetto ai propri bounds
#define DISABLED_ALPHA 0.7f
#define CONTROLLLER_RECUCTION 75.0f //padding da applicare completamente al controller

/* TODOS
 *
 * PRIORITA 0:
 *  TODO: comprendere come beccarsi info da MIXXX per lo scorrimento della traccia
 * TODO: gestione browser
 *  -opz 1: minimizza il controller, mixx sarà sotto, quindi fai apparire un widget per lo scorrimento della lista
 *  -opz 2: fai apparire un visualizzatore di default di juce che punta ad una cartella di default (come farlo cross-patform?)

 * PRIORITA 1:
 * TODO: aggiungere widget popup  + e - che all'hover con cursore (o idealmente allo strizzamneot di occhio dx(possibilmente click destro) )
 * TODO: aggiungere ctr+q e ctrl+w
 * TODO: disegna icone

 * REFACTORING:
 * TODO: un modo decente per impostare il colore dello sfondo (forse Resizablewindow::Backgroundcolorid)?
 */


