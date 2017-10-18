About IanniX
============
IanniX is a graphical open-source sequencer, based on Iannis Xenakis works, for digital art. IanniX syncs via Open Sound Control (OSC) events and curves to your real-time environment.

Build IanniX
============

All platforms
-------------
- Download Qt 5.x for your platform (http://qt-project.org/downloads) (4.8 and 4.7 are also compatible, especially for compilation on Mac 32 bits)
- Download Qt Creator (http://qt-project.org/downloads)
- Open IanniX.pro and build!

Mac OS X specific
-----------------
- Download Syphon Framework (http://syphon-framework.googlecode.com/) and add it to /Library/Frameworks folder
- If you want to build IanniX with Kinect support, you'll need libfreenect (http://openkinect.org/wiki/Getting_Started)

Linux
-----
- You'll need to build Qt before building IanniX
  - If your distribution supports it, you can also install Qt via the package
    manager, e.g.:

        aptitude install libqt4-dev libqt4-opengl-dev
