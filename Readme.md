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
     - sudo apt-get install g++ libfreetype6-dev libfontconfig1-dev libfontconfig-dev libglib2.0-dev libsm-dev libgtk2.0-dev libxrender-dev libsqlite3-dev libglu1-mesa-dev libasound2-dev mesa-common-dev gtk2-engines-pixbuf libjpeg62‑dev libtiff4‑dev libpng12‑dev 