# Djeye-controller
Djeye-controller is a MIDI controller designed to be used with your eyes only.
<br>
[djeye-interface-video](./Assets/Media/djeye-demo.webm)
<br>
[![video demo on youtube](https://img.youtube.com/vi/-bs08Ohdr7w/0.jpg)](https://www.youtube.com/watch?v=-bs08Ohdr7w)
***

# Installation
The controller works on Linux, Windows and MacOS.

We developed some software to use the eye-tracker to emulate mouse input for Linux (Debian based) (see [tobii-eye-interface](https://gitlab.com/djeyes/tobii-eye-interface)) and for Windows (see [DJEye_EyeLayer_Windows](https://github.com/LIMUNIMI/DJEye_EyeLayer_Windows)).

## Linux
Go to the [releases page](https://github.com/LIMUNIMI/DJeye/releases/latest) and download the executable file for Linux (flatpack coming).

If you are interested in using the eye tracker go to the eye-tracker wrapper [release page](https://github.com/LIMUNIMI/tobii-eye-interface/releases/latest) and download the executable. See the [readme](https://github.com/LIMUNIMI/tobii-eye-interface) for info on usage 

### MIXXX setup
- Install MIXXX from [flathub](https://flathub.org/apps/details/org.mixxx.Mixxx)
- Copy the provided mapping (`Mappings/djeye.midi.xml`) and script (`Mappings/djeye-scripts.js`) in: `~/.var/app/org.mixxx.Mixxx/.mixxx/controllers/`.

## Windows
Go to the [releases page](https://github.com/LIMUNIMI/DJeye/releases/latest) and download the executable file for Windows (installer coming).

If you are interested in using the eye tracker go to the eye-tracker wrapper [release page](https://github.com/LIMUNIMI/DJEye_EyeLayer_Windows/releases/latest) and download the executable. 

### MIXXX setup
- Install MIXXX from their [official website](https://mixxx.org/download/).
- Copy the provided mapping (`Mappings/djeye.midi.xml`) and script (`Mappings/djeye-scripts.js`) in: `C:\Program Files\Mixxx\controllers\`.

### Virtual MIDI port software
Since windows has no easy way to open virtual midi ports, you will need to install a vitrual midi port driver like [loopmidi](https://www.tobias-erichsen.de/software/loopmidi.html) and create a port called DJEYE.
You have to open this port **before** launching DJeye.
	
# Tweak MIXXX Preferences
0. Launch djeye-controller.
0. Open MIXXX preferences (`ctrl+p`)
    - Go to Controllers, select "DJEYE" and select from the "Load Mapping" dropdown the "djeye" mapping (should be first on the list).
    - Go to Library and set library row height to 70px.
0. Activate [master sync](https://manual.mixxx.org/2.0/en/chapters/djing_with_mixxx.html#master-sync) on both decks, holding down the sync button. (this implies you should play tracks which are similar BPM)
0. enable fullscreen (`F11`).
0. Enable "big library" from the button on the top-left.
0. Put djeye-controller and MIXXX in the same desktop, so that MIXXX is "under" the controller.

***

# Roadmap
- [ ] interface controls values syncronization with MIXXX controls (eg. track position must be syncronized)
- [ ] display track name

# Limitations
The gaze-based interaction introduces some limitations in the expressive possibilities of the controller:
- simultaneous controls manipulation is not possible.
- due to the extension of graphic targets the number of controls which is possible to display simultaneously is not high.
- headphones volume is not modifiable.

# Architecture
The configuration of the controller is quite easy to modify, just change the initializer list's parameters.
![UML diagram](./Assets/Media/uml_djeye_controller.svg)

## Building
Use CMake, pretty much the [JUCE](https://github.com/juce-framework/JUCE/tree/master/examples/CMake) base examples.

### Monitoring MIDI messages from terminal emulator
Show port list:
~`aconnect -iol`

Dump port messages
~`aseqdump -p <#port>`
