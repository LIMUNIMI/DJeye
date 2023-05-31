# Djeye-controller
Djeye-controller is a MIDI controller which interface is thought to be easy to use with input coming fom an eye tracker.
it is written in c++ using the JUCE library for midi and GUI creation.

## Building
use CMake, pretty much the [JUCE](https://github.com/juce-framework/JUCE/tree/master/examples/CMake) base examples

## Monitoringi MIDI messages from terminal
`~aconnect -iol` : visualize port list.

`~aseqdump -p [#porta]` : dump port messages.


## MIXX setup
install mixxx from [flathub](https://flathub.org/apps/details/org.mixxx.Mixxx)

### MIDI mappings
copy the provided mapping (djeye.midi.xml) in this location:
/home/fabio/.var/app/org.mixxx.Mixxx/.mixxx/controllers/

### Preferences
- After launching djeye-controller, go to preferences (ctrl+p) then to Controllers, select djeye controller and assign to it the "djeye" mapping, shoud be first on the list
- Go to Library -> Library row height and set it to 70px;
- Activate [master sync](https://manual.mixxx.org/2.0/en/chapters/djing_with_mixxx.html#master-sync) on both decks, holding down the sync button. this means you should play tracks which are similar BPM
- enable fullscreen (`F11`)
- djeye-controller and MIXXX should be in the same desktop
