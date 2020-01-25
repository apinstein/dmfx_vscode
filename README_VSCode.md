# DreamMaker FX + VS Code

These instructions will help you get up and running with style using VS Code for your DMFX development. VS Code is a real IDE and is much easier to use for experienced devlopers than Arduino.

## Dependencies

1. Install [Arduino IDE](https://www.arduino.cc/en/Main/Software)
1. Install and Launch [VS Code](https://code.visualstudio.com)
    1. Open the Extensions manager 
    1. Search for the "Arduino for Visual Studio Code" extension (it has >1.5M downloads) and install it
1. Connect the DMFX pedal to your computer.

## Open DMFX Hello World Project

1. Open "DMFX Arduino.code-workspace" in VS Code "File > Open Workspace..."
1. Open "settings.json" in the project and configure `arduino.path` as appropriate for your machine.
1. Open the command palette and choose "Arduino: Select Serial Port" and choose the port that the DMFX is attached to; if you're lucky it will be labeled "Run Jump Labs"