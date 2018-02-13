# Pathfinder LabVIEW Library
This is a LabVIEW wrapper of the 'Pathfinder' motion profiling library. A few small changes were added to the Pathfinder-Core code to allow LabVIEW to wrap the key function calls properly.

## Installing
1. Follow the instructions to build the Pathfinder-Core, the output will be a .dll if running on Windows, or a .so for Linux (or for the roboRIO)
2. Run the gradle install, or copy the output .dll to a location in your PATH **Windows requires 32-bit**
    - Windows example: C:\Windows\SysWOW64\pathfinder.dll
    - Linux example: \usr\local\bin\pathfinder.so

## Using the Library
Add the Pathfinder-Lib to your code, the Pathfinder.lvproj and Tank.vi give an example using the FRC 2017 game.
