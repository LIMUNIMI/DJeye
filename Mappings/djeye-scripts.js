var djeye = {};

djeye.init = function () {}
djeye.shutdown = function () {}

djeye.selectedHotCue   = {
  "[Channel1]" : 1,
  "[Channel2]" : 1
};
djeye.selectedLoopSize   = {
  "[Channel1]" : 4,
  "[Channel2]" : 4
};

var valueToLoopSizeMap = {
  0 : "0.125",
  1 : "0.25",
  2 : "0.5",
  3 : "1",
  4 : "2",
  5 : "4",
  6 : "8"
};

djeye.selectHotcue = function (channel, control, value, status, group) {
    djeye.selectedHotCue[group] = value;
    print("impostato " + group + " con val " + value );
}

djeye.activateSelectedHotCue  = function (channel, control, value, status, group) {
    engine.setValue(group, "hotcue_" + djeye.selectedHotCue[group] + "_activate", 1);    
    print("lanciato " + group + " hotcue number " + djeye.selectedHotCue[group]);
    // script.toggleControl(group,"hotcue_" + djeye.selectedHotCue[group] + "_activate");
}

djeye.selectLoopSize = function (channel, control, value, status, group) {
    djeye.selectedLoopSize[group] = valueToLoopSizeMap[value];
    engine.setValue(group, "beatloop_size", djeye.selectedLoopSize[group]);
}

djeye.activateSelectedLoopSize  = function (channel, control, value, status, group) {
    var looping = engine.getValue(group, "loop_enabled");    
    if(looping){
       engine.setValue(group, "reloop_toggle", 1);    
    }else{
       engine.setValue(group, "beatloop_activate", 1);    
     }
}
