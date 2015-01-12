/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * IanniX Interface
 * Object to create an interface with IanniX
 * The following line is mandatory to interface with IanniX
 */
IanniX iannix;


void setup() {
  //Screen size and display setup
  size(640, 640);
  noStroke();
  smooth();

  /*
   * IanniX Interface
   * Connection with IanniX
   * Syntax : new IanniX(this, <IP where IanniX runs>, <OSC port in of IanniX>, <OSC port out of IanniX>); 
   * The following line is mandatory to interface with IanniX
   */
  iannix = new IanniX(this, "127.0.0.1", 1234, 57120);
  /*
   * IanniX Interface
   * Transport control
   */
  iannix.scoreRewind();
  iannix.scoreStart();
}


void draw() {
  //Black-translucent background
  fill(0, 0, 0, 5);
  rect(0, 0, width, height);


  /*
   * IanniX Interface
   * Asynchronous messages reception (in drawing loop only)
   * The following lines are optional depending on your Processing sketch needs
   */
  //Score rewinded
  if (iannix.hasScoreRewinded())
    background(0);

  //Cursors coords
  while (iannix.hasReceivedCursorsMessages ()) {
    IanniXMessage cursor = iannix.getReceivedCursorsMessages();
    if (cursor != null) {
      fill(255,  80,  30);
      ellipse(cursor.coord.x * width, height - cursor.coord.y * height, 10, 10);
    }
  }

  //Triggers fired
  while (iannix.hasReceivedTriggersMessages ()) {
    IanniXMessage trigger = iannix.getReceivedTriggersMessages();
    if (trigger != null) {
      fill(0, 185, 255, 200);
      ellipse(trigger.coord.x * width, height - trigger.coord.y * height, 40, 40);
    }
  }

  //Curves intersections
  while (iannix.hasReceivedCurvesMessages ()) {
    IanniXMessage curve = iannix.getReceivedCurvesMessages();
    if (curve != null) {
      fill(115, 159,  89);
      ellipse(curve.coord.x * width, height - curve.coord.y * height, 7, 7);
    }
  }
}


void mouseMoved() {
  /*
   * IanniX Interface
   * Send messages to IanniX
   * Syntax : iannix.send(<command>, <argument1>, <argument2>, ...);
   */
  //X mouse coordinate is mapped on score speed
  iannix.send("speed", map(mouseX, 0, width, 0.1, 2.0));
  //X-Y mouse coordinates are mapped on score center
  //iannix.send("center", map(mouseX, 0, width, 5.0, -5.0), map(mouseY, 0, height, -5.0, 5.0));
}


void mousePressed() {
   /*
   * IanniX Interface
   * Transport control
   */
  //Double-click = rewind score
  if (mouseEvent.getClickCount() == 2)
    iannix.scoreRewind();
  //Simple-click = start / stop score
  else if (iannix.isPlaying())
    iannix.scoreStop();
  else
    iannix.scoreStart();
}



/*
 * IanniX Interface
 * Event-driven messages reception (no drawing allowed !!)
 * The following lines are optional depending on your Processing sketch needs
 */
//Cursors coords
void cursorsFromIanniX(IanniXMessage message) {
  println("Received from IanniX a message from " + message.type + " of ID : " + message.object.id + " (" + message.object.groupId + ") is at (" + message.coord.x + ", " + message.coord.y + ", " + message.coord.z + ") or (" + message.absoluteCoord.x + ", " + message.absoluteCoord.y + ", " + message.absoluteCoord.z + ")");
} 

//Triggers fired
void triggersFromIanniX(IanniXMessage message) {
  println("Received from IanniX a message from " + message.type + " of ID : " + message.object.id + " (" + message.object.groupId + ") is at (" + message.coord.x + ", " + message.coord.y + ", " + message.coord.z + ") or (" + message.absoluteCoord.x + ", " + message.absoluteCoord.y + ", " + message.absoluteCoord.z + ") hit by cursor ID" + message.cursor.id + " (" + message.cursor.groupId + ")");
}

//Curves intersections
void curvesFromIanniX(IanniXMessage message) {
  println("Received from IanniX a message from " + message.type + " of ID : " + message.object.id + " (" + message.object.groupId + ") is at (" + message.coord.x + ", " + message.coord.y + ", " + message.coord.z + ") or (" + message.absoluteCoord.x + ", " + message.absoluteCoord.y + ", " + message.absoluteCoord.z + ")");
} 

//Score played
void scoreStarted(Float time, String timeStr) {
  println("IanniX score started @ " + time + "s. / " + timeStr + " !");
}

//Score stopped
void scoreStopped(Float time, String timeStr) {
  println("IanniX score stopped @ " + time + "s. / " + timeStr + " !");
}

//Score rewinded
void scoreRewinded(Float time, String timeStr) {
  println("IanniX score rewinded @ " + time + "s. / " + timeStr + " !");
}

