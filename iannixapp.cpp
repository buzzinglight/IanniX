/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "iannixapp.h"
#include "help.h"

IanniXApp::IanniXApp(int &argc, char **argv) :
    QApplication(argc, argv) {
}

void IanniXApp::launch(int &argc, char **argv) {
    setHelp();

    if(QApplication::applicationDirPath().startsWith("/Users/Guillaume/Documents/buzzinglight/Projets"))
        generateHelp();

    bool forceSettings = false;
    QString project = "";
    if(argc >= 2) {
        QString argument(argv[1]);
        if(argument == "reset")
            forceSettings = true;
        else
            project = argv[1];
    }

    iannix = new IanniX(0, forceSettings);
    if(!project.isEmpty())
        iannix->loadProject(project);
}

bool IanniXApp::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::FileOpen:
        iannix->loadProject(static_cast<QFileOpenEvent*>(event)->file());
        return true;
    default:
        return QApplication::event(event);
    }
}

void IanniXApp::setHelp() {
    Help::categories["protocols"].category = tr("Messages protocols");
    Help::categories["protocols"].infos << HelpInfo(QString("osc"),                tr("OpenSoundControl message"));
    Help::categories["protocols"].infos << HelpInfo(QString("direct"),             tr("Recursive/loopback message (sent directly to IanniX)"));
    Help::categories["protocols"].infos << HelpInfo(QString("midi"),               tr("MIDI message (control change, note on/off or program change)"));
    Help::categories["protocols"].infos << HelpInfo(QString("serial"),             tr("Serial message (UART/RS232)"));
    Help::categories["protocols"].infos << HelpInfo(QString("http"),               tr("HTTP request to a webpage/webservice (GET)"));
    Help::categories["protocols"].infos << HelpInfo(QString("udp"),                tr("Raw UDP message (compatible with PureData)"));
    Help::categories["protocols"].infos << HelpInfo(QString("tcp"),                tr("XML over TCP message (compatible with Flash/Director)"));

    Help::categories["hostIp"].category = tr("Messages IP");
    Help::categories["hostIp"].infos << HelpInfo(QString("ip_out"),                tr("Destination is the default IP set in \"Network\" tab"));
    Help::categories["hostIp"].infos << HelpInfo(QString("127.0.0.1"),             tr("Destination is your own computer"));

    Help::categories["hostMidi"].category = tr("Messages MIDI devices");
    Help::categories["hostMidi"].infos << HelpInfo(QString("midi_out"),            tr("Destination is the default MIDI device set in \"Network\" tab"));
    Help::categories["hostMidi"].infos << HelpInfo(QString("IanniX_Out"),          tr("MIDI device created by IanniX (Mac & Linux only)"));

    Help::categories["port"].category = tr("Messages IP ports");
    Help::categories["port"].infos << HelpInfo(QString("57120"),                   tr("Default port used by IanniX"));
    Help::categories["port"].infos << HelpInfo(QString("1234"),                    tr("IanniX OSC default input"));

    Help::categories["addressOsc"].category = tr("Messages OSC addresses");
    Help::categories["addressOsc"].infos << HelpInfo(QString("/trigger"),          tr("Default address used for triggers"));
    Help::categories["addressOsc"].infos << HelpInfo(QString("/cursor"),           tr("Default address used for cursors"));
    Help::categories["addressOsc"].infos << HelpInfo(QString("/transport"),        tr("Default address used for transport messages"));
    Help::categories["addressOsc"].infos << HelpInfo(QString("/iannix"),           tr("Default address used to reach IanniX"));

    Help::categories["addressMidi"].category = tr("Messages MIDI controls");
    Help::categories["addressMidi"].infos << HelpInfo(QString("/cc"),              tr("Send a control change"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/bend"),            tr("Send a bend"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/pgm"),             tr("Send a program change"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/note"),            tr("Send a note"));

    Help::categories["values"].category = tr("Messages values");
    Help::categories["values"].infos << HelpInfo(QString("trigger_id"),            tr("ID of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_group_id"),	   tr("Group name of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_document_id"),   tr("Document name of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_label"),         tr("Label of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_xPos"),          tr("x coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_yPos"),          tr("y coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_zPos"),          tr("z coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_value_x"),	   tr("x mapped coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_value_y"),	   tr("y mapped coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_value_z"),	   tr("z mapped coordinate of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_value"),         tr("When trigger off-time is set, returns 127 when the trigger is trigged and 0 when the trigger is released"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_distance"),	   tr("Distance between the triggered trigger and the cursor that triggers the trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_side"),          tr("0 if trigger is triggered from left to right and 1 for the other side"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_message_id"),	   tr("ID of the message (each message generates an ascending ID)"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_id"),             tr("ID of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_group_id"),	   tr("Group name of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_document_id"),	   tr("Document name of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_label"),          tr("Label of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_xPos"),           tr("x coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_yPos"),           tr("y coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_zPos"),           tr("z coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_x"),        tr("x mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_y"),        tr("y mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_z"),        tr("z mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_time"),           tr("Current progression of the cursor on the curve (in seconds)"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_time_percent"),   tr("Current progression of the cursor on the curve (in percentages, from 0.0 to 1.0)"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_angle"),          tr("Angle of the cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_nb_loop"),        tr("Number of loops done by the cursor on the curve"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_message_id"),	   tr("ID of the message (each message generates an ascending ID)"));
    Help::categories["values"].infos << HelpInfo(QString("curve_id"),              tr("ID of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_group_id"),        tr("Group name of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_document_id"),	   tr("Document name of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_label"),           tr("Label of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_xPos"),            tr("x coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_yPos"),            tr("y coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_zPos"),            tr("z coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_id"),           tr("ID of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_group_id"),	  tr("Group name of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_document_id"),  tr("Document name of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_label"),        tr("Label of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_xPos"),         tr("x coordinate of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_yPos"),         tr("y coordinate of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_zPos"),         tr("z coordinate of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_xPos"),        tr("x coordinate of the collision between the cursor and the curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_yPos"),        tr("y coordinate of the collision between the cursor and the curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_value_x"),	   tr("x mapped coordinate of the collision between the cursor and the curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_value_y"),	   tr("y mapped coordinate of the collision between the cursor and the curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_distance"),	   tr("Distance between the collision and the cursor"));
    Help::categories["values"].infos << HelpInfo(QString("timetag"),               tr("Set an OSC Timetag (compliant with Internet NTP timestamps) to message"));
    Help::categories["values"].infos << HelpInfo(QString("status"),                tr("Playback status of score (\"play\"), \"stop\" or \"fastrewind\")"));
    Help::categories["values"].infos << HelpInfo(QString("nb_triggers"),           tr("Number of triggers in the current score"));
    Help::categories["values"].infos << HelpInfo(QString("nb_cursors"),            tr("Number of cursors in the current score"));
    Help::categories["values"].infos << HelpInfo(QString("nb_curves"),             tr("Number of curves in the current score"));
    Help::categories["values"].infos << HelpInfo(QString("global_time"),           tr("Elapsed time in seconds"));
    Help::categories["values"].infos << HelpInfo(QString("global_time_verbose"),   tr("Elapsed time as displayed in Transport bar"));

    Help::categories["javascript"].category = tr("JavaScript useful functions");
    Help::categories["javascript"].infos << HelpInfo(QString("abs(x)"), 	tr("Absolute value of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("acos(x)"), 	tr("Arccosine of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("asin(x)"), 	tr("Arcsine of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("atan(x)"), 	tr("Arctangent of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("atan2(x,y)"), tr("Arctangent of x divided by y"));
    Help::categories["javascript"].infos << HelpInfo(QString("ceil(x)"), 	tr("Next higher integer above x"));
    Help::categories["javascript"].infos << HelpInfo(QString("cos(x)"), 	tr("Cosine of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("exp(x)"), 	tr("e to the power x"));
    Help::categories["javascript"].infos << HelpInfo(QString("floor(x)"), 	tr("Next lower integer below x"));
    Help::categories["javascript"].infos << HelpInfo(QString("log(x)"), 	tr("Logarithm to the base 2 of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("min(x,y)"), 	tr("Minimum of x and y"));
    Help::categories["javascript"].infos << HelpInfo(QString("max(x,y)"), 	tr("Maximum of x and y"));
    Help::categories["javascript"].infos << HelpInfo(QString("pow(x,y)"), 	tr("x raised to the power y"));
    Help::categories["javascript"].infos << HelpInfo(QString("round(x)"), 	tr("x rounded nearest integer, higher or lower"));
    Help::categories["javascript"].infos << HelpInfo(QString("sin(x)"), 	tr("Sine of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("sqrt(x)"), 	tr("Square root of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("sq(x)"), 		tr("x squared"));
    Help::categories["javascript"].infos << HelpInfo(QString("tan(x)"), 	tr("Tangent of x"));
    Help::categories["javascript"].infos << HelpInfo(QString("degrees(x)"),                      tr("Radian angle x converted into degrees"));
    Help::categories["javascript"].infos << HelpInfo(QString("radians(x)"),                      tr("Degree angle x converted into radians"));
    Help::categories["javascript"].infos << HelpInfo(QString("random(low, high)"),               tr("Random number between low and high"));
    Help::categories["javascript"].infos << HelpInfo(QString("constrain(x, min, max)"),          tr("Values of x below min and above max are discarded"));
    Help::categories["javascript"].infos << HelpInfo(QString("dist(x1, y1, z1, x2, y2, z2)"), 	 tr("Distance between the points (x1, y1, z1) and (x2, y2, z2)"));
    Help::categories["javascript"].infos << HelpInfo(QString("angle(x1, y1, x2, y2)"),           tr("Angle between the points (x1, y1) and (x2, y2)"));
    Help::categories["javascript"].infos << HelpInfo(QString("norm(x, low, high)"),              tr("Scale x to cover the range from low to high, assuming x ranges between 0.0 and 1.0:"));
    Help::categories["javascript"].infos << HelpInfo(QString("rangeMid(x, low, mid, high)"), 	 tr("Scale x to cover the range from low to high, assuming x ranges between 0.0 and 1.0, with mid being returned as the value for x=0.5"));
    Help::categories["javascript"].infos << HelpInfo(QString("map(x, low1, high1, low2, high2)"),tr("Scale x to cover the range from low2 to high2, assuming x ranges between low1 and high1"));
    Help::categories["javascript"].infos << HelpInfo(QString("E"),          tr("Mathematical constant e"));
    Help::categories["javascript"].infos << HelpInfo(QString("LN2"), 		tr("Natural logarithm of 2"));
    Help::categories["javascript"].infos << HelpInfo(QString("LN10"), 		tr("Natural logarithm of 10"));
    Help::categories["javascript"].infos << HelpInfo(QString("LOG2E"), 		tr("Base 2 logarithm of e"));
    Help::categories["javascript"].infos << HelpInfo(QString("LOG10E"), 	tr("Logarithm to the base 10 of e"));
    Help::categories["javascript"].infos << HelpInfo(QString("PI"),         tr("Constant PI"));
    Help::categories["javascript"].infos << HelpInfo(QString("TWO_PI"), 	tr("Two times PI"));
    Help::categories["javascript"].infos << HelpInfo(QString("THIRD_PI"), 	tr("PI over 3"));
    Help::categories["javascript"].infos << HelpInfo(QString("QUARTER_PI"), tr("PI over 4"));
    Help::categories["javascript"].infos << HelpInfo(QString("HALF_PI"), 	tr("PI over 2"));
    Help::categories["javascript"].infos << HelpInfo(QString("SQRT1_2"), 	tr("One over the square root of two"));
    Help::categories["javascript"].infos << HelpInfo(QString("SQRT2"), 		tr("Square root of two"));

    Help::categories["commands"].category = tr("IanniX Commands");
    Help::categories["commands"].infos << HelpInfo(QString("add"),
                                                   tr("Add an object"),
                                                   tr("Adds an object on the score. The keyword auto automatically assigns an ID to your object."),
                                                   tr("add <trigger|curve|cursor> <id>\nadd <trigger|curve|cursor> auto"),
                                                   QString("add trigger 1"),
                                                   QString("add trigger 1\nadd cursor auto"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("remove"),
                                                   tr("Remove an object"),
                                                   tr("Removes an object in the score thanks to its ID."),
                                                   tr("remove <id>"),
                                                   QString("remove 1"),
                                                   QString("add trigger 1\nsetPos current 1 2 0\nremove 1"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("trig"),
                                                   tr("Force object to send its message(s)"),
                                                   tr("Forces an object to send its message(s)."),
                                                   tr("trig <target>"),
                                                   QString("trig 1"),
                                                   QString("add trigger 1\ntrig 1"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("clear"),
                                                   tr("Erase a score"),
                                                   tr("Erase all objects into the score"),
                                                   tr("clear"),
                                                   QString("clear"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setGroup"),
                                                   tr("Defining a group"),
                                                   tr("Groups are identified by a word you are free to choose. Objects are not required to be part of a group."),
                                                   tr("setGroup <target> <group name>"),
                                                   QString("setGroup current triggers"),
                                                   QString("add trigger 1\nsetGroup current triggers"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setActive"),
                                                   tr("Enable/disable an object"),
                                                   tr("An object is enable by default, but you can disable it. Disabled objects will not send messages."),
                                                   tr("setActive <target> <0|1>"),
                                                   QString("setActive 1 0"),
                                                   QString("add trigger 1\nsetActive current 0"),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setTriggerOff"),
                                                   tr("Time before release (note off) of a trigger"),
                                                   tr("When a note is played thanks to a trigger, you can configure it to turn the note off automatically after a configurable delay. The time before release should normally be set to zero when note-off time is not being sent in the messages of this trigger."),
                                                   tr("setTriggerOff <target> <delay>"),
                                                   QString("add trigger 1\nsetTriggerOff current 0.5"),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setCurve"),
                                                   tr("Assign a cursor to a curve"),
                                                   tr("After creating your cursor, make sure you have assigned the curve you want it to follow. You can use the keyword lastCurve to designate the last curve added."),
                                                   tr("setCurve <cursor target> <curve target>"),
                                                   QString("setCurve 2 lastCurve"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 2\nadd cursor 2\nsetCurve 2 lastCurve"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setWidth"),
                                                   tr("Width of the cursor play head"),
                                                   tr("You can edit in real time the width of a cursor in order to enable or disable triggers nearby."),
                                                   tr("setWidth <target> <width>"),
                                                   QString("setWidth current 3.5"),
                                                   QString("add cursor 1\nsetWidth current 3.5"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setDepth"),
                                                   tr("Depth of the cursor play head"),
                                                   tr("You can edit in real time the depth of a cursor in order to enable or disable triggers nearby."),
                                                   tr("setDepth <target> <depth>"),
                                                   QString("setDepth current 3.5"),
                                                   QString("add cursor 1\nsetDepth current 3.5"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPattern"),
                                                   tr("Cursor loop pattern"),
                                                   tr("This parameter refers to the direction and the number of cycles. For example, with 1 1 0, the cursor will perform two cycles in the positive direction before stopping."),
                                                   tr("setPattern <target> <easing> 0 <pattern>"),
                                                   QString("setPattern current 0 0 1 -1"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 2\nsetPos current 0 0 0\nadd cursor 10\nsetCurve 10 1\nsetPattern current 0 0 1 -1"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setSpeed"),
                                                   tr("Speed of a cursor"),
                                                   tr("Cursors have a speed factor independent of each other. The travel time of a curve is also configurable. The cursor will evolve in the negative direction if the speed is negative, but time will continue to flow naturally."),
                                                   tr("setSpeed <target> auto <duration>\n") +
                                                   tr("setSpeed <target> <speed factor>"),
                                                   QString("setSpeed current 4"),
                                                   QString("add curve 1\nsetPointsEllipse current 1 1\nsetPos current -1 0 0\nadd cursor 10\nsetCurve 10 1\n\nadd curve 2\nsetPointsEllipse current 1 1\nsetPos current 1 0 0\nadd cursor 11\nsetCurve 11 2\nsetSpeed 11 4"),
                                                   QString("Visuel"));

    Help::categories["commands"].infos << HelpInfo(QString("setSpeedf"),
                                                   tr("Instantaneous speed of a cursor"),
                                                   tr("Cursors have an instantaneous speed factor independent, very useful for real-time performances. As setSpeed, a negative speed is possible without affecting the global speed of the score."),
                                                   tr("setSpeedF <target> <speed factor>"),
                                                   QString("setSpeedF 11 1"),
                                                   QString("add curve 2\nsetPointsEllipse current 1 1\nsetPos current 1 0 0\nadd cursor 11\nsetCurve 11 2\nsetPattern current 0 0 1\n\nadd curve 1\nsetPointAt current 1 0 4\nsetPos current -1 0 0\nadd cursor 10\nsetCurve 10 1\nsetMessage current 20, direct:// setSpeedF 11 cursor_yPos"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setOffset"),
                                                   tr("Cursor offsets"),
                                                   tr("You can choose to start your cursor at a certain point of the curve (marked in seconds) and limit it between certain values (also in seconds).\nFor example, the 2 4 6 offset means that your cursor will start your curve at the position t=2s then will travel to point t=6s to start again at the point t=4s."),
                                                   tr("setOffset <target> <initial> <start> <end>"),
                                                   QString("setOffset current 3 1 7"),
                                                   QString("add curve 1\nsetPointAt current 1 6 6\nsetPos current -3 -3 0\nadd cursor 10\nsetCurve 10 1\nsetPattern current 0 0 1\nsetOffset current 3 1 7"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTime"),
                                                   tr("Instantaneous position (in seconds)"),
                                                   tr("The position of a cursor can be modified in real time. This instruction does not work if you include it directly in your script, because at each execution, IanniX does a fastrewind."),
                                                   tr("setTime <target> <time>"),
                                                   QString("setTime 11 0"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 2\nsetPos current 0 0 0\n\nadd cursor 11\nsetCurve 11 1\n\nadd trigger 21\nsetPos current -2 0 0\nsetMessage current 10, direct:// setTime 11 0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTimePercent"),
                                                   tr("Instantaneous position (in percentages)"),
                                                   tr("The position of a cursor can be modified in real time. This instruction does not work if you include it directly in your script, because at each execution, IanniX does a fastrewind."),
                                                   tr("setTimePercent <target> <time>"),
                                                   QString("setTime 11 0"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 2\nsetPos current 0 0 0\n\nadd cursor 11\nsetCurve 11 1\n\nadd trigger 21\nsetPos current -2 0 0\nsetMessage current 10, direct:// setTime 11 0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setBoundsSource"),
                                                   tr("Mapping values"),
                                                   tr("You can set your cursor to send values within a chosen interval. For example, if it is operating in a 3x3 square, it can still send coordinates as values between 0 and 1.\nUse setBoundsSource to indicate to IanniX the interval in which your cursor is located and setBoundsTarget to set the range of your sent values. Generally BoundsSource is correctly set by default.\nYou must use the variables cursor_value_x, cursor_value_y, trigger_value_x, trigger_value_y, collison_value_x or collison_value_y that values sent are those of boundsTarget."),
                                                   tr("setBoundsSource <target> <x-top-left-corner> <y-top-left-corner> <x-bottom-right-corner> <y-bottom-right-corner>\n") +
                                                   tr("setBoundsTarget <target> <x-top-left-value>  <y-top-left-value>  <x-bottom-right-value> <y-bottom-right-value>"),
                                                   QString("setBoundsSource 2 0 3 3 0\nsetBoundsTarget 2 0 1 1 0"),
                                                   QString("add curve 1\nsetPointAt 1 1 3 3\nadd cursor 2\nsetCurve 2 1\nsetBoundsSource 2 0 3 3 0\nsetBoundsTarget 2 0 1 1 0\nsetMessage 2 250, direct:// cursor_value_x cursor_value_y"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setBoundsTarget"),
                                                   tr("Mapping values"),
                                                   tr("You can set your cursor to send values within a chosen interval. For example, if it is operating in a 3x3 square, it can still send coordinates as values between 0 and 1.\nUse setBoundsSource to indicate to IanniX the interval in which your cursor is located and setBoundsTarget to set the range of your sent values. Generally BoundsSource is correctly set by default.\nYou must use the variables cursor_value_x, cursor_value_y, trigger_value_x, trigger_value_y, collison_value_x or collison_value_y that values sent are those of boundsTarget."),
                                                   tr("setBoundsSource <target> <x-top-left-corner> <y-top-left-corner> <x-bottom-right-corner> <y-bottom-right-corner>\n") +
                                                   tr("setBoundsTarget <target> <x-top-left-value>  <y-top-left-value>  <x-bottom-right-value> <y-bottom-right-value>"),
                                                   QString("setBoundsSource 2 0 3 3 0\nsetBoundsTarget 2 0 1 1 0"),
                                                   QString("add curve 1\nsetPointAt 1 1 3 3\nadd cursor 2\nsetCurve 2 1\nsetBoundsSource 2 0 3 3 0\nsetBoundsTarget 2 0 1 1 0\nsetMessage 2 250, direct:// cursor_value_x cursor_value_y"),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("shiftPoints"),
                                                   tr("Shifting points of a curve"),
                                                   tr("Shfit points from left to right or right to left"),
                                                   tr("shiftPoints <target> <start point index> <-1|1>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("translatePoints"),
                                                   tr("Translating a curve"),
                                                   tr("Translates a curve"),
                                                   tr("translatePoints <target> <dX> <dY> <dZ>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("translatePoint"),
                                                   tr("Translating a point of a curve"),
                                                   tr("Translates a point of a curve"),
                                                   tr("translatePoint <target> <point index> <dX> <dY> <dZ>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointAt"),
                                                   tr("Setting or modifying points of a curve (straight or Bezier)"),
                                                   tr("A curve must be defined by a sequence of points. The points index starts at 0."),
                                                   tr("setPointAt <target> <point index> <x> <y>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <c1x> <c1y> <c2x> <c2y>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <z>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <z> <c1x> <c1y> <c1z> <c2x> <c2y> <c2z>"),
                                                   QString("setPointAt current 1 3 3"),
                                                   QString("add curve 1\nsetPos current -1 -1 0\nsetPointAt current 0 0 0\nsetPointAt current 1 3 3"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setSmoothPointAt"),
                                                   tr("Setting or modifying points of a curve (with automatic smoothing)"),
                                                   tr("A curve must be defined by a sequence of points. The points index starts at 0."),
                                                   tr("setSmoothPointAt <target> <point index> <x> <y>\n") +
                                                   tr("setSmoothPointAt <target> <point index> <x> <y> <z>"),
                                                   QString("setSmoothPointAt current 1 3 3"),
                                                   QString("add curve 1\nsetPos current -1 -1 0\nsetSmoothPointAt current 0 0 0\nsetSmoothPointAt current 1 3 3\nsetSmoothPointAt current 2 0 -2"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointXAt"),
                                                   tr("Modifying x-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointXAt <target> <point index> <x>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointYAt"),
                                                   tr("Modifying y-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointYAt <target> <point index> <y>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointZat"),
                                                   tr("Modifying z-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointZAt <target> <point index> <z>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("removePointAt"),
                                                   tr("Removing a point of a curve"),
                                                   tr("Description"),
                                                   tr("removePointAt <point index>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsTxt"),
                                                   tr("Text curves"),
                                                   tr("A character can also be played like a curve."),
                                                   tr("setPointsTxt <target> <scaling> <font> <text>"),
                                                   QString("setPointsTxt current 0.1 Arial a"),
                                                   QString("add curve 1\nsetPointsTxt current 0.1 Arial a"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsPath"),
                                                   tr("Manual SVG curve — cubic path"),
                                                   tr("A SVG curve is defined by a path that you can directly import from another software by copy / paste."),
                                                   tr("setPointsPath <target> <scale> <svg path>"),
                                                   QString("setPointsPath current 0.01 M637.599,1569.972c0,0,89.127,0,222.818,0c8.913,0,18.023,0,27.381,0.113C901,1570,913,1573,926,1576c67,15,128,43,198,28c9-2,17.833-4.277,26.554-6.685c8.72-2.407,17.255-5.074,25.247-8.562C1224,1567,1239,1514,1256,1469c18-48,69-29,101-9c81.375,48.125,161.219,103.141,254.032,110.08c13.259,0.991,26.782,1.001,40.616-0.129C1716,1574,1788,1562,1842,1606c39,32,62,97,119,90c44-6,70-47,101.551-72.846"),
                                                   QString("add curve auto\nsetPointsPath current 0.01 M637.599,1569.972c0,0,89.127,0,222.818,0c8.913,0,18.023,0,27.381,0.113C901,1570,913,1573,926,1576c67,15,128,43,198,28c9-2,17.833-4.277,26.554-6.685c8.72-2.407,17.255-5.074,25.247-8.562C1224,1567,1239,1514,1256,1469c18-48,69-29,101-9c81.375,48.125,161.219,103.141,254.032,110.08c13.259,0.991,26.782,1.001,40.616-0.129C1716,1574,1788,1562,1842,1606c39,32,62,97,119,90c44-6,70-47,101.551-72.846\nsetPos current -14 15 0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsLines"),
                                                   tr("Manual SVG curve — polylines"),
                                                   tr("The SVG path of these curves is simply a set of points ."),
                                                   tr("setPointsLines <target> <scale> <svg polyline>"),
                                                   QString("setPointsLines current 1  1,1 1,2 -1,2 -1,-2 -2,0"),
                                                   QString("add curve auto\nsetPointsLines current 1  1,1 1,2 -1,2 -1,-2 -2,0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsImg"),
                                                   tr("Automatic vectorization"),
                                                   tr("A curve can be directly constructed from an image by an automatic vectorization."),
                                                   tr("setPointsImg <target> <scaling> <filename>"),
                                                   QString("setPointsImg current 0.1 ./Examples/trigger_speaker.png"),
                                                   QString("add curve 1\nsetPointsImg current 0.1 ./Examples/trigger_speaker.png"),
                                                   QString("Visuel"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsEllipse"),
                                                   tr("Elliptical or circular curves"),
                                                   tr("Ellipses are defined by a major axis and a minor axis. To construct circles, the two axes must have the same value."),
                                                   tr("setPointsEllipse <target> <width> <height>"),
                                                   QString("setPointsEllipse current 2 1"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 1\nsetPos current 1 1 0"),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setSize"),
                                                   tr("Size of objects"),
                                                   tr("This function modifies the thickness of a curve or a cursor and the size of a trigger."),
                                                   tr("setSize <target> <size>"),
                                                   QString("setSize 1 10"),
                                                   QString("add curve 1\nadd trigger 2\nadd cursor 3\nsetCurve 3 1\nsetPos 2 1.5 1.5 0\nsetPointsEllipse 1 2 2\nsetSize 1 10\nsetSize 2 5\nsetSize 3 7"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setResize"),
                                                   tr("Curve size (width/height)"),
                                                   tr("The size of objects can be changed directly."),
                                                   tr("setResize <target> <width> <height>"),
                                                   QString("setResize current 2 1"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 1\nsetPos current 1 1 0\nsetResize current 2 1"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setResizeF"),
                                                   tr("Curve size (scale factor)"),
                                                   tr("The size of objects can be changed directly."),
                                                   tr("setResizeF <target> <scale factor>"),
                                                   QString("setResizeF current 0.5"),
                                                   QString("add curve 1\nsetPointsEllipse current 2 1\nsetPos current 1 1 0\nsetResizeF current 0.5"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setLine"),
                                                   tr("Paths format"),
                                                   tr("Sets a style dotted with dash pattern which must be a sequence of 0 and 1, dash style defines the space between each dot."),
                                                   tr("setLine <target> <dash style> <dash pattern>"),
                                                   QString("setLine 1 2000 1"),
                                                   QString("add curve 1\nsetPointsEllipse 1 2.5 2.5\nsetLine 1 2000 1"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setPos"),
                                                   tr("Space position"),
                                                   tr("Sets an object on the score via the coordinates (x, y, z)."),
                                                   tr("setPos <target> <x> <y> <z>"),
                                                   QString("setPos 1 1 2 0"),
                                                   QString("add trigger 1\nsetPos current 1 2 0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setLabel"),
                                                   tr("Adding text"),
                                                   tr("You can add a text description of your items on the score."),
                                                   tr("setLabel <target> <label>"),
                                                   QString("setLabel current Hello World !"),
                                                   QString("add trigger auto\nsetLabel current Hello World !"),
                                                   QString(""));



    Help::categories["commands"].infos << HelpInfo(QString("setMessage"),
                                                   tr("Assigning a message"),
                                                   tr("This command sets the message that an object must send (please refer to Messages Syntax help)."),
                                                   tr("setMessage <target> <period>, <message1> <variables>, <message2>,message2, message3, …"),
                                                   QString("setMessage current 1, osc://127.0.0.1:57120/trigger trigger_id"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("sendOsc"),
                                                   tr("Send a message"),
                                                   tr("You can send manually a message (please refer to Messages Syntax help)."),
                                                   tr("sendOsc <message>"),
                                                   QString("sendOsc osc://127.0.0.1:57120/trigger 1 2 3"),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("solo"),
                                                   tr("Solo/un-solo"),
                                                   tr("Solo/un-solo an object or a group (exactly like in Objects of inspector tab)"),
                                                   tr("solo <target> <0|1>\n") +
                                                   QString("solo myGroup 1"),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("mute"),
                                                   tr("Mute/un-mute"),
                                                   tr("Mute/un-mute an object or a group (exactly like in Objects of inspector tab)"),
                                                   tr("mute <target> <1|0>\n") +
                                                   QString("mute myGroup 0"),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("registerTexture"),
                                                   tr("Creating a variable texture"),
                                                   tr("Save your texture as a variable. If you are using the following variables, the display is directly modified because native textures are saved under those variables. Use the tool \"restore triggers original shapes\" from the inspector \"scripts & styles\" to find the original textures."),
                                                   tr("registerTexture <variable> <x-top-left-corner> <y-top-left-corner> <x-bottom-right-corner> <y-bottom-right-corner> <file name>"),
                                                   QString("registerTexture trigger_active_message -1 1 1 -1 ./Examples/trigger_triangle.png"),
                                                   QString("registerTexture trigger_active_message -1 1 1 -1 ./Examples/trigger_triangle.png\nadd trigger 1\nadd trigger 2\nadd trigger 3\nsetPos 1 1 1 0\nsetPos 3 -1 -1 0\nsetActive 3 0\nsetLabel 1 1\nsetLabel 2 2\nsetLabel 3 3"),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setTexture"),
                                                   tr("Texture of an object"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTexture <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureActive"),
                                                   tr("Texture of an active object that does not send any messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureActive <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureInactive"),
                                                   tr("Texture of an inactive object that does not send any messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureInactive <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureActiveMessage"),
                                                   tr("Texture of an active object that send messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureActiveMessage <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureInactiveMessage"),
                                                   tr("Texture of an inactive object that send messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureInactiveMessage <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));



    Help::categories["commands"].infos << HelpInfo(QString("registerColor"),
                                                   tr("Creating a variable color (RGB)"),
                                                   tr("IanniX can also save a color as a variable for reusing it more easily."),
                                                   tr("registerColor <variable> <r> <g> <b> <a>"),
                                                   QString("registerColor rougeRGB 255 0 0 255"),
                                                   QString("registerColor rougeRGB 255 0 0 255\nadd trigger auto\nsetColor current rougeRGB"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("registerColorHue"),
                                                   tr("Creating a variable color (HSB)"),
                                                   tr("IanniX can also save a color as a variable for reusing it more easily."),
                                                   tr("registerColor <variable> <h> <s> <b> <a>"),
                                                   QString("registerColorHue orangeHUE 32 255 255 255"),
                                                   QString("registerColorHue orangeHUE 32 255 255 255\nadd trigger auto\nsetColor current orangeHUE"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColor"),
                                                   tr("Color of an object (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColor <target> <r> <g> <b> <a>\n") +
                                                   tr("setColor <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorHue"),
                                                   tr("Color of an object (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorHue <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setColorActive"),
                                                   tr("Color of an active object that does not send any messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActive <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorActive <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactive"),
                                                   tr("Color of an inactive object that does not send any messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactive <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorInactive <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorActiveMessage"),
                                                   tr("Color of an active object that send messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActiveMessage <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorActiveMessage <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactiveMessage"),
                                                   tr("Color of an inactive object that send messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactiveMessage <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorInactiveMessage <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("setColorActiveHue"),
                                                   tr("Color of an active object that does not send any messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActiveHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorActiveHue <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactiveHue"),
                                                   tr("Color of an inactive object that send messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactiveHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorInactiveHue <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorActiveMessageHue"),
                                                   tr("Color of an inactive object that does not send any messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActiveMessageHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorActiveMessageHue <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactiveMessageHue"),
                                                   tr("Color of an inactive object that send messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactiveMessageHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorInactiveMessageHue <target> <variable>"),
                                                   QString(""),
                                                   QString(""),
                                                   QString(""));



    Help::categories["commands"].infos << HelpInfo(QString("autoSize"),
                                                   tr("Resizing objects regardless of zoom"),
                                                   tr("Enabled by default, can automatically increase or decrease the size of the triggers and cursors when you zoom in / out the score in order to facilitate reading. Only the visual aspect is affected, the actual size of the objects is not changed."),
                                                   tr("autoSize <0|1>"),
                                                   QString("autoSize 0"),
                                                   QString("add trigger 1\nzoom 200\nautosize 0"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("zoom"),
                                                   tr("Zoom in score"),
                                                   tr("Adjust the zoom using the script. The factor is in percent. e.g. A factor of 200 doubles the size of the display area."),
                                                   tr("zoom <zoom factor>"),
                                                   QString("zoom 200"),
                                                   QString("add trigger 1\nzoom 200"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("center"),
                                                   tr("Center score"),
                                                   tr("Placing the point (x,y) in the center of the workspace"),
                                                   tr("center <x> <y>"),
                                                   QString("center 2 2 "),
                                                   QString("add trigger 1\nzoom 200\ncenter 2 2"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("viewport"),
                                                   tr("Resize the viewport"),
                                                   tr("Resize the viewport"),
                                                   tr("viewport <width> <height>"),
                                                   QString("viewport 400 400"),
                                                   QString(""),
                                                   QString(""));


    Help::categories["commands"].infos << HelpInfo(QString("snapshot"),
                                                   tr("Export as an image snapshot"),
                                                   tr("Make a snapshot of current score"),
                                                   tr("snapshot <scale> <filename,optional>"),
                                                   QString("snapshot 4"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("rotate"),
                                                   tr("Rotate score"),
                                                   tr("Rotate the view about the x, y and z axes"),
                                                   tr("rotate <x-axis> <y-axis> <z-axis>"),
                                                   QString("rotate 45 0 0"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("rotate"),
                                                   tr("Rotate score"),
                                                   tr("Rotate the view about the x, y and z axes"),
                                                   tr("rotate <x-axis> <y-axis> <z-axis>"),
                                                   QString("rotate 45 0 0"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("play"),
                                                   tr("Playing the score"),
                                                   tr("Enabling the playback"),
                                                   tr("play <score speed>"),
                                                   QString("play 1"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("stop"),
                                                   tr("Stopping the score"),
                                                   tr("Disabling the playback"),
                                                   tr("stop"),
                                                   QString("stop"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("fastrewind"),
                                                   tr("Fastrewinding the score"),
                                                   tr("Go back to the begging of score"),
                                                   tr("fastrewind"),
                                                   QString("fastrewind"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("speed"),
                                                   tr("Speed of the score"),
                                                   tr("You can set the global speed of the score. A negative speed will evolve over time in the negative direction."),
                                                   tr("speed <speed>"),
                                                   QString("speed 5"),
                                                   QString("add curve auto\nsetPointsEllipse current 1 1\nsetPos current 1 0 0\nadd cursor auto\nsetCurve current lastCurve\nspeed 5"),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("load"),
                                                   tr("Load a score or a script"),
                                                   tr("Load a score or a script of the current project folder"),
                                                   tr("load <score name>"),
                                                   QString("load Script sample - IanniX logo"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("log"),
                                                   tr("Log information to console"),
                                                   tr("Log information to IanniX console (network tab)"),
                                                   tr("log <text>"),
                                                   QString("log is really useful to debug"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("goto"),
                                                   tr("Go to a specific timecode"),
                                                   tr("Go to a specific timecode in seconds"),
                                                   tr("goto <time in seconds>"),
                                                   QString("goto 4.5"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("mouse"),
                                                   tr("Control mouse"),
                                                   tr("Enable to move cursor of the mouse"),
                                                   tr("mouse <x> <y>"),
                                                   QString("mouse 50 50"),
                                                   QString(""),
                                                   QString(""));



    Help::categories["commands"].infos << HelpInfo(QString("title"),
                                                   tr("Get IanniX window title"),
                                                   tr("Returns IanniX window title (scripts only)"),
                                                   tr("title"),
                                                   QString("title"),
                                                   QString(""),
                                                   QString(""));

    Help::categories["commands"].infos << HelpInfo(QString("sleep"),
                                                   tr("Make IanniX script sleeping (scripts only)"),
                                                   tr("Set a sleep time. BE CAREFUL, IanniX will not respond during sleeping"),
                                                   tr("sleep <duration>"),
                                                   QString("sleep 5"),
                                                   QString(""),
                                                   QString(""));


    foreach(const HelpInfo &info, Help::categories["values"].infos)
        Help::keywords.append(qPrintable(info.keyword));
}

void IanniXApp::generateHelp() {
    qDebug("GÉNÉRATION DES FICHIERS D'AIDE");

    QDir().mkpath("Documentation/" + tr("EN"));

    QString header, footer;
    QFile headerFile("Documentation_template/header.html"), footerFile("Documentation_template/footer.html");
    if(headerFile.open(QFile::ReadOnly)) {
        header = headerFile.readAll();
        header = header.arg(tr("Introduction")).arg(tr("Main<br/>elements")).arg(tr("Scripts")).arg(tr("Reference"));
        headerFile.close();
    }
    if(footerFile.open(QFile::ReadOnly)) {
        footer = footerFile.readAll();
        footerFile.close();
    }

    QString referenceHeader, referenceFooter;
    QFile referenceHeaderFile("Documentation_template/referenceHeader.html"), referenceFooterFile("Documentation_template/referenceFooter.html");
    if(referenceHeaderFile.open(QFile::ReadOnly)) {
        referenceHeader = referenceHeaderFile.readAll();
        referenceHeaderFile.close();
    }
    if(referenceFooterFile.open(QFile::ReadOnly)) {
        referenceFooter = referenceFooterFile.readAll();
        referenceFooterFile.close();
    }
    QFile referenceFile("Documentation/" + tr("EN") + "/reference.html");
    if(referenceFile.open(QFile::WriteOnly)) {
        referenceFile.write(qPrintable(header));
        referenceFile.write(qPrintable(referenceHeader
                                       .arg(tr("Documentation"))
                                       .arg(tr("IanniX commands must specify a target at each execution:"))
                                       .arg(tr("<li><code class='target'>id</code> refers to a specific object.<br/>Example: <span class='api'><code>remove <span class= 'target'>2</span></code></span></li><li><code class='target'>group_id</code> refers to the entire group that can be a word.<br/>Example: <span class='api'><code>remove <span class= 'target'>toto</span></code></span></li><li><code class='target'>all</code> refers to all objects.<br/>Example: <span class='api'><code>remove <span class= 'target'>all</span></code></span></li><li><code class='target'>current</code> refers to the last created object.<br/>Example: <span class='api'><code>remove <span class= 'target'>current</span></code></span></li>"))));

        QString content;
        content += QString("<hr/><h2>%1</h2>").arg(Help::categories["commands"].category);
        foreach(const HelpInfo &info, Help::categories["commands"].infos) {
            QString description = info.description, snippet = info.snippet, syntax = info.syntax, example = info.example;
            content += QString("\n<div id='%1' class='fonction'>").arg(info.keyword);
            content += QString("\n	<h3>%1 &mdash; %2</h3>").arg(info.keyword).arg(info.title);
            content += QString("\n	<div class='roll'>");
            if(!description.isEmpty())
                content += QString("\n		<p>%1<br/><br/>").arg(description.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>"));
            if(!syntax.isEmpty())
                content += QString("\n		<span class='api'>%1</span><br/><br/>").arg(syntax.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>"));
            if(!example.isEmpty())
                content += QString("\n		<span class='titre'>%1 <code>%2</code></span></p>").arg(tr("Example:")).arg(example.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>"));
            content += QString("\n		<table class='exemple' summary=''>");
            content += QString("\n			<tr>");
            if(QFile("Documentation/Common/img/" + info.keyword + ".png").exists())
                content += QString("\n				<td><img src='../Common/img/%1.png' alt='setGroup' /></td>").arg(info.keyword);
            else if(QFile("Documentation/Common/img/" + info.keyword + ".swf").exists())
                content += QString("\n				<td><img src='../Common/img/%1.png' alt='setGroup' /></td>").arg(info.keyword);
            if(!snippet.isEmpty()) {
                content += QString("\n				<td>");
                content += QString("\n					<div class='copypaste'>%1</div>").arg(tr("Copy / paste this example in IanniX to understand how the code works!"));
                content += QString("\n					<div class='code'><code>%1</code></div>").arg(snippet.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>"));
                content += QString("\n				</td>");
            }
            content += QString("\n			</tr>");
            content += QString("\n		</table>");
            content += QString("\n	</div>");
            content += QString("\n</div>");
            content += QString("\n");
        }

        content += QString("<hr/><h2>%1</h2>").arg(Help::categories["values"].category);
        foreach(const HelpInfo &info, Help::categories["values"].infos) {
            content += QString("\n<div id='%1' class='fonction'>").arg(info.keyword);
            content += QString("\n	<h3>%1</h3><div class='roll'></div>").arg(info.keyword);
            content += QString("\n	<p>%1<br/>").arg(info.title);
            content += QString("\n</div>");
            content += QString("\n");
        }

        content += QString("<hr/><h2>%1</h2>").arg(Help::categories["javascript"].category);
        foreach(const HelpInfo &info, Help::categories["javascript"].infos) {
            content += QString("\n<div id='%1' class='fonction'>").arg(info.keyword);
            content += QString("\n	<h3>%1</h3><div class='roll'></div>").arg(info.keyword);
            content += QString("\n	<p>%1<br/>").arg(info.title);
            content += QString("\n</div>");
            content += QString("\n");
        }
        referenceFile.write(qPrintable(content));
        referenceFile.write(qPrintable(referenceFooter));
        referenceFile.write(qPrintable(footer));
        referenceFile.close();
    }


    QString indexHeader, indexFooter;
    QFile indexHeaderFile("Documentation_template/indexHeader.html"), indexFooterFile("Documentation_template/indexFooter.html");
    if(indexHeaderFile.open(QFile::ReadOnly)) {
        indexHeader = indexHeaderFile.readAll();
        indexHeaderFile.close();
    }
    if(indexFooterFile.open(QFile::ReadOnly)) {
        indexFooter = indexFooterFile.readAll();
        indexFooterFile.close();
    }
    QFile indexFile("Documentation/" + tr("EN") + "/index.html");
    if(indexFile.open(QFile::WriteOnly)) {
        indexFile.write(qPrintable(header));
        indexFile.write(qPrintable(indexHeader
                                   .arg(tr("Welcome and thank you for downloading IanniX!"))
                                   .arg(tr("IanniX is a graphical open-source sequencer, based on Iannis Xenakis works, for digital art. IanniX syncs via Open Sound Control (OSC) events and curves to your real-time environment (PureData, C-Sound, SuperCollider, openFramework, Processing, vvvv, Live, Max/MSP/Jitter… and many others from our <a href='http://www.iannix.org/EN/links.php' target='_blank'>links</a> section)!"))
                                   .arg(tr("Feel free to suscribe to our <a href='http://iannix.org/EN/community.php' target='_blank'>forum</a>. Post your problems or tips to make live our community!"))));
        indexFile.write(qPrintable(indexFooter));
        indexFile.write(qPrintable(footer));
        indexFile.close();
    }


    QString introHeader, introFooter, releaseNotesRaw;
    QFile introHeaderFile("Documentation_template/introHeader.html"), introFooterFile("Documentation_template/introFooter.html"), releaseNotesFile("Documentation_template/releaseNotes.txt");
    if(introHeaderFile.open(QFile::ReadOnly)) {
        introHeader = introHeaderFile.readAll();
        introHeaderFile.close();
    }
    if(introFooterFile.open(QFile::ReadOnly)) {
        introFooter = introFooterFile.readAll();
        introFooterFile.close();
    }
    if(releaseNotesFile.open(QFile::ReadOnly)) {
        releaseNotesRaw = releaseNotesFile.readAll();
        releaseNotesFile.close();
        QFile macReleaseFile  ("../Release/iannix_mac__"     + QCoreApplication::applicationVersion().toLower().replace(" ", "_").replace(".", "_") + ".txt");
        QFile winReleaseFile  ("../Release/iannix_windows__" + QCoreApplication::applicationVersion().toLower().replace(" ", "_").replace(".", "_") + ".txt");
        QFile linuxReleaseFile("../Release/iannix_linux__"   + QCoreApplication::applicationVersion().toLower().replace(" ", "_").replace(".", "_") + ".txt");
        if(macReleaseFile.open(QFile::WriteOnly)) {
            macReleaseFile.write(qPrintable(releaseNotesRaw));
            macReleaseFile.close();
        }
        if(winReleaseFile.open(QFile::WriteOnly)) {
            winReleaseFile.write(qPrintable(releaseNotesRaw));
            winReleaseFile.close();
        }
        if(linuxReleaseFile.open(QFile::WriteOnly)) {
            linuxReleaseFile.write(qPrintable(releaseNotesRaw));
            linuxReleaseFile.close();
        }
    }
    QFile introFile("Documentation/" + tr("EN") + "/intro.html");
    if(introFile.open(QFile::WriteOnly)) {
        introFile.write(qPrintable(header));
        QString content = "";
        QStringList releaseNotes = releaseNotesRaw.split("\n");
        foreach(const QString releaseNote, releaseNotes) {
            if(releaseNote.startsWith("-")) content += "\n<li>"     + releaseNote.mid(2, releaseNote.length()-2) + "</li>";
            else                            content += "\n</ul><p>" + releaseNote                                + "</p><ul>";
        }

        introFile.write(qPrintable(introHeader
                                   .arg(tr("Installation"))
                                   .arg(tr("IanniX is compatible with Linux, Mac OS X 10.6+ and Windows and does not require any particular installation.<br/>For Linux users of IanniX who do not build from source, we have included a compiled version that you can run by launching the file <code>IanniX.sh</code>."))
                                   .arg(tr("Open Sound Control"))
                                   .arg(tr("Open Sound Control is a communication protocol that operates over the IP network (i.e. Ethernet, Wi-Fi, Internet). It is recognized by all operating systems and requires no drivers or network configuration. Some knowledge of networking is needed to more advanced uses.<br /> <br /> The golden rule about OSC is to match IP addresses and ports: a message sent by IanniX to <code>127.0.0.1:57120</code> means that it is sent to the local machine on port &nbsp;57120. The software that has to receive this message will have to open port 57120."))
                                   .arg(tr("MIDI"))
                                   .arg(tr("In order to remain compatible with the MIDI stations, we have integrated the MIDI protocol natively.<br/> For Windows users who do not have MIDI hardware devices, you must install a virtual MIDI device such as <a href='http://www.nerds.de/data/setuploopbe1.exe'>LoopBe</a>."))
                                   .arg(tr("Software &amp; interfaces"))
                                   .arg(tr("We have made available patches/interfaces for commonly used software that we have tested. Click on 'Open Patches Folder' from the IanniX toolbar to discover them.<br/> This is very simple examples that illustrate the principle of communication between IanniX and other software; we invite you to modify them and get inspired for your projects."))
                                   .arg(tr("Bugs"))
                                   .arg(tr("IanniX is still on beta-testing, some bugs are still present but most features can be used properly. You can report errors in the 'Bugs' section of our <a href='http://iannix.org/EN/community.php'>forum</a>."))
                                   .arg(tr("Version tracking"))
                                   .arg(content)));
        introFile.write(qPrintable(introFooter));
        introFile.write(qPrintable(footer));
        introFile.close();
    }



    QString objetsHeader, objetsFooter;
    QFile objetsHeaderFile("Documentation_template/objetsHeader.html"), objetsFooterFile("Documentation_template/objetsFooter.html");
    if(objetsHeaderFile.open(QFile::ReadOnly)) {
        objetsHeader = objetsHeaderFile.readAll();
        objetsHeaderFile.close();
    }
    if(objetsFooterFile.open(QFile::ReadOnly)) {
        objetsFooter = objetsFooterFile.readAll();
        objetsFooterFile.close();
    }
    QFile objetsFile("Documentation/" + tr("EN") + "/objets.html");
    if(objetsFile.open(QFile::WriteOnly)) {
        objetsFile.write(qPrintable(header));
        objetsFile.write(qPrintable(objetsHeader
                                    .arg(tr("Objects"))
                                    .arg(tr("A IanniX score is composed of three main elements:"))
                                    .arg(tr("<li><b>a trigger</b> is a momentary event set in space; it is activated when <b>a cursor</b> goes past it;</li><li><b>a curve</b> is a series of points set in space; it defines a trajectory&nbsp;;</li><li><b>a cursor</b> is similar to a tape head. It triggers discrete events (<b>triggers</b>) or continuous (values). It can follow <b>a curve</b> or be completely free (controlled by the mouse, a graphic tablet or by another software).</li>"))
                                    .arg(tr("Add objects"))
                                    .arg(tr("To set an object in space, you have three methods:"))
                                    .arg(tr("<li><b>the graphic interface</b> thanks to the toolbar;</li><li><b>software interfaces</b> controlling IanniX via Open Sound Control for example, through <a href='reference.html'>IanniX commands</a>;</li><li><b>scripts</b> that create generative scores via <a href='script.html'>scripted commands</a>.</li>"))
                                    .arg(tr("Basic vocabulary"))
                                    .arg(tr("A few simple concepts will enable you to understand the mechanisms of IanniX:"))
                                    .arg(tr("<li><b>the identifier (ID)</b>: each object (trigger, curve or cursor) has an unique identifier;</li><li><b>the group</b>: objects can be grouped under a group name, allowing control of multiple objects at once.</li>"))
                                    .arg(tr("Messages"))
                                    .arg(tr("Message handling is the main function of IanniX. They can be sent by <b>cursors</b> and <b>triggers</b>."))
                                    .arg(tr("To see if the messages are actually sent or received, IanniX displays a trace in the 'Messages' section of inspector."))
                                    .arg(tr("<b>Triggers</b> usually send one only message when a cursor goes past them. IanniX is limited to sending one message per millisecond maximum.<br/>"))
                                    .arg(tr("<b>Cursors</b>, by default, generate messages every 20&nbsp;ms (but you can change this time)."))
                                    .arg(tr("To edit the message that a element has to send, click on 'Edit' in the inspector after having selected the object or double-click on the object itself to display this window:"))
                                    .arg(tr("Recursion"))
                                    .arg(tr("IanniX can be controlled by IanniX itself (!). You can use all the protocols described above, but we recommend using OSC to communicate between two IanniX applications on network computers and use the <code>direct</code> command to send messages inside one IanniX application.<br/><br /><span class='titre'>Example:&nbsp;</span>"))
                                    .arg(tr("Copy / paste this example in Iannix to understand how the code works!"))));
        objetsFile.write(qPrintable(objetsFooter));
        objetsFile.write(qPrintable(footer));
        objetsFile.close();
    }



    QString scriptHeader, scriptFooter;
    QFile scriptHeaderFile("Documentation_template/scriptHeader" + tr("EN") + ".html"), scriptFooterFile("Documentation_template/scriptFooter" + tr("EN") + ".html");
    if(scriptHeaderFile.open(QFile::ReadOnly)) {
        scriptHeader = scriptHeaderFile.readAll();
        scriptHeaderFile.close();
    }
    if(scriptFooterFile.open(QFile::ReadOnly)) {
        scriptFooter = scriptFooterFile.readAll();
        scriptFooterFile.close();
    }
    QFile scriptFile("Documentation/" + tr("EN") + "/script.html");
    if(scriptFile.open(QFile::WriteOnly)) {
        scriptFile.write(qPrintable(header));
        scriptFile.write(qPrintable(scriptHeader));
        scriptFile.write(qPrintable(scriptFooter));
        scriptFile.write(qPrintable(footer));
        scriptFile.close();
    }

}


int main(int argc, char *argv[]) {
    IanniXApp iannixApp(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load("Translation_" + locale, "Tools");
    iannixApp.installTranslator(&translator);

    QString appName    = "IanniX ";
    QString appVersion = "0.8.45";
    qDebug("%s", qPrintable(QApplication::applicationDirPath()));

#ifdef Q_OS_MAC
    appName += "Mac";
    qDebug("Command line syntax : ./IanniX.app/Contents/MacOS/IanniX <file path>");
#endif
#ifdef Q_OS_WIN
    appName += "Windows";
    qDebug("Command line syntax : IanniX.exe <file path>");
#endif
#ifdef Q_OS_LINUX
    appName += "Linux";
    qDebug("Command line syntax : ./IanniX <file path>");
#endif

    QCoreApplication::setApplicationName(appName);
    QCoreApplication::setApplicationVersion(appVersion);
    QCoreApplication::setOrganizationName("IanniX");
    QCoreApplication::setOrganizationDomain("org.iannix");

    iannixApp.launch(argc, argv);

    return iannixApp.exec();
}


