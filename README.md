# Djeye-controller
Djeye-controller is a MIDI controller which interface is thought to be easy to use through input coming from an eye tracker.
It is written in c++ using the [JUCE](https://github.com/juce-framework/JUCE) library.
To use the eye-tracker see [Tobii-eye-interface](https://gitlab.com/djeyes/tobii-eye-interface).
</br>
[djeye-interface-video](./Assets/Media/djeye-demo.webm)

## Building
Use CMake, pretty much the [JUCE](https://github.com/juce-framework/JUCE/tree/master/examples/CMake) base examples.

## Monitoring MIDI messages from terminal emulator
Show port list:
~`aconnect -iol`

Dump port messages
~`aseqdump -p <#port>`

## MIXXX setup
Install MIXXX from [flathub](https://flathub.org/apps/details/org.mixxx.Mixxx).

### MIDI mappings
Copy the provided mapping (`Mappings/djeye.midi.xml`) and script (`Mappings/djeye-scripts.js`) in this location:
`~home/.var/app/org.mixxx.Mixxx/.mixxx/controllers/`

### Preferences
0. Launch djeye-controller.
0. Open MIXXX preferences (`ctrl+p`) 
	a. Go to Controllers, select "DJEYE" and select from the "Load Mapping" dropdown the "djeye" mapping, should be first on the list.
	b. Go to Library and set library row height to 70px.

0. Activate [master sync](https://manual.mixxx.org/2.0/en/chapters/djing_with_mixxx.html#master-sync) on both decks, holding down the sync button. (this implies you should play tracks which are similar BPM)
0. enable fullscreen (`F11`).
0. Enable "big library" from the button on the top-left.
0. Put djeye-controller and MIXXX in the same desktop, so that MIXXX is "under" the controller.

# TODO (in order of priority)
- [x] insert headphone preview button
- [ ] interface controls values syncronization with MIXXX controls (eg. track position must be syncronized)
- [ ] display track name
- [ ] Implement playlist controls instead of library controls, to avoid atefacts in the browser code

# Limitations
The gaze-based interaction introduces some limitations in the expressive possibilities of the controller:
- simultaneous controls manipulation is not possible.
- due to the extension of graphic targets the number of controls which is possible to display simultaneously is not high.
- headphones volume is not modifiable.

# Architecture
The configuration of the controller is quite easy to modify, just change the initializer list's parameters.
![UML diagram](./Assets/Media/uml_djeye_controller.svg)
