About IanniX
============
IanniX is a graphical open-source sequencer, based on Iannis Xenakis works, for digital art. IanniX syncs via Open Sound Control (OSC) events and curves to your real-time environment.

Build IanniX
============

All platforms
-------------
- Download Qt 4.8 for your plateform (http://qt-project.org/downloads) (4.7 is also compatible)
- Download Qt Creator (http://qt-project.org/downloads)
- Open IanniX.pro and build!

Mac OS X specific
-----------------
- Download Syphon Framework (http://syphon-framework.googlecode.com/) and add it to /Library/Frameworks folder
- If you want to build IanniX with Kinect support, you'll need libfreenect (http://openkinect.org/wiki/Getting_Started)

Linux
-----
- You'll need to build Qt before building IanniX
- Some libraries are needed for Qt building
     - sudo apt-get install g++
     - sudo apt-get install libfreetype6-dev
     - sudo apt-get install libglib2.0-dev
     - sudo apt-get install libsm-dev
     - sudo apt-get install libxrender-dev
     - sudo apt-get install mesa-common-dev
     - sudo apt-get install libglu1-mesa-dev
     - sudo apt-get install libasound2-dev
     - sudo apt-get install gtk2-engines-pixbuf
     - sudo apt-get install fontconfig
- If opengl is slow, check Graphical Card drivers.