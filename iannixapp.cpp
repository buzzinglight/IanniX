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

#include <QFontDatabase>
#include "iannixapp.h"
#include "misc/help.h"



int main(int argc, char *argv[]) {
    IanniXApp iannixApp(argc, argv);

#ifdef QT4
    QTextCodec::setCodecForTr      (QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale  (QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    QString locale = QLocale::system().name();
    //QTranslator translator;
    //translator.load("Translation_" + locale, "Tools");
    //iannixApp.installTranslator(&translator);

    QString appName    = "IanniX ";
    QString appVersion = "0.9";

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

    QCoreApplication::setApplicationName   (appName);
    QCoreApplication::setApplicationVersion(appVersion);
    QCoreApplication::setOrganizationName  ("IanniX");
    QCoreApplication::setOrganizationDomain("org.iannix");

    iannixApp.launch(argc, argv);

    return iannixApp.exec();
}



IanniXApp::IanniXApp(int &argc, char **argv) :
    QApplication(argc, argv) {
}

void IanniXApp::launch(int &argc, char **argv) {
    setHelp();

    QDir pathApplicationDir = QDir(QCoreApplication::applicationDirPath()).absolutePath();
#ifdef Q_OS_MAC
    pathApplicationDir.cdUp();
    pathApplicationDir.cdUp();
    pathApplicationDir.cdUp();
#endif
#ifdef QT4
    Global::pathDocuments   = QFileInfo(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + "/IanniX");
#else
    UiRenderOptions::pathDocuments   = QFileInfo(QStandardPaths::DocumentsLocation + "/IanniX");
#endif
    Global::pathApplication = QFileInfo(pathApplicationDir.absolutePath());
    Global::pathCurrent     = QFileInfo(QDir::currentPath());
    if((Global::pathApplication.absoluteFilePath().endsWith("/IanniX-build-64")) || (Global::pathApplication.absoluteFilePath().endsWith("/IanniX-build-32")))
        Global::pathApplication = QFileInfo(Global::pathApplication.absoluteFilePath().remove("-build-64").remove("-build-32"));

    qDebug("Pathes");
    qDebug("\tDocuments  : %s", qPrintable(Global::pathDocuments  .absoluteFilePath()));
    qDebug("\tApplication: %s", qPrintable(Global::pathApplication.absoluteFilePath()));
    qDebug("\tCurrent    : %s", qPrintable(Global::pathCurrent    .absoluteFilePath()));
    qDebug("Arguments");
    for(quint16 i = 0 ; i < argc ; i++) {
        qDebug("\t%2d=\t%s", i, argv[i]);
    }
    /*
    if(Global::pathCurrent.absoluteFilePath().startsWith("/Users/Guillaume/Documents/buzzinglight/Projets/Coduys/IanniX/IanniX"))
        generateHelp();
    */

    QFileInfo project;
    quint16 indexArgument = 1;
#ifdef Q_OS_WIN
 //TOTO
    indexArgument = 0;
#endif
    if(argc > indexArgument)
        project = QFileInfo(Global::pathCurrent.absoluteFilePath() + "/" + argv[indexArgument]);

    if(QFontDatabase::addApplicationFont(Global::pathApplication.absoluteFilePath() + "/Tools/Museo.ttf"))
        qDebug("Loading IanniX font failed");

    iannix = new IanniX();
    if(project.exists()) {
        qDebug("Loading project %s", qPrintable(project.absoluteFilePath()));
        iannix->loadProject(project.absoluteFilePath());
    }
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
    Help::categories["hostMidi"].infos << HelpInfo(QString("from_IanniX"),         tr("MIDI device created by IanniX (Mac & Linux only)"));

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
    Help::categories["addressMidi"].infos << HelpInfo(QString("/ccf"),             tr("Send a control change (value as a float value between 0. and 1.)"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/note"),            tr("Send a note"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/notef"),           tr("Send a note (note and velocity as a float values between 0. and 1.)"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/bend"),            tr("Send a bend"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/bendf"),           tr("Send a bend (value as a float value between 0. and 1.)"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/pgm"),             tr("Send a program change"));
    Help::categories["addressMidi"].infos << HelpInfo(QString("/pgmf"),            tr("Send a program change (program as a float value between 0. and 1.)"));

    Help::categories["values"].category = tr("Messages values");
    Help::categories["values"].infos << HelpInfo(QString("trigger_id"),            tr("ID of the triggered trigger"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_group_id"),	   tr("Group name of the triggered trigger"));
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

    Help::categories["values"].infos << HelpInfo(QString("cursor_xPos_delta"),         tr("Variation of x coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_yPos_delta"),         tr("Variation of y coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_zPos_delta"),         tr("Variation of z coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_x_delta"),      tr("Variation of x mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_y_delta"),      tr("Variation of y mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_value_z_delta"),      tr("Variation of z mapped coordinate of the running cursor"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_time_delta"),         tr("Variation of current progression of the cursor on the curve (in seconds)"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_time_percent_delta"), tr("Variation of current progression of the cursor on the curve (in percentages, from 0.0 to 1.0)"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_angle_delta"),        tr("Variation of angle of the cursor"));

    Help::categories["values"].infos << HelpInfo(QString("cursor_nb_loop"),        tr("Number of loops done by the cursor on the curve"));
    Help::categories["values"].infos << HelpInfo(QString("cursor_message_id"),	   tr("ID of the message (each message generates an ascending ID)"));
    Help::categories["values"].infos << HelpInfo(QString("curve_id"),              tr("ID of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_group_id"),        tr("Group name of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_label"),           tr("Label of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_xPos"),            tr("x coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_yPos"),            tr("y coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("curve_zPos"),            tr("z coordinate of curve where the cursor runs on"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_id"),           tr("ID of the collided curve"));
    Help::categories["values"].infos << HelpInfo(QString("collision_curve_group_id"),	  tr("Group name of the collided curve"));
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
                                                   tr("add <trigger|curve|cursor> <id>\nadd <trigger|curve|cursor> auto"));

    Help::categories["commands"].infos << HelpInfo(QString("remove"),
                                                   tr("Remove an object"),
                                                   tr("Removes an object in the score thanks to its ID."),
                                                   tr("remove <id>"));

    Help::categories["commands"].infos << HelpInfo(QString("trig"),
                                                   tr("Force object to send its message(s)"),
                                                   tr("Forces an object to send its message(s)."),
                                                   tr("trig <target>"));

    Help::categories["commands"].infos << HelpInfo(QString("clear"),
                                                   tr("Erase a score"),
                                                   tr("Erase all objects into the score"),
                                                   tr("clear"));

    Help::categories["commands"].infos << HelpInfo(QString("setGroup"),
                                                   tr("Defining a group"),
                                                   tr("Groups are identified by a word you are free to choose. Objects are not required to be part of a group."),
                                                   tr("setGroup <target> <group name>"));

    Help::categories["commands"].infos << HelpInfo(QString("setActive"),
                                                   tr("Enable/disable an object"),
                                                   tr("An object is enable by default, but you can disable it. Disabled objects will not send messages."),
                                                   tr("setActive <target> <0|1>"));


    Help::categories["commands"].infos << HelpInfo(QString("setTriggerOff"),
                                                   tr("Time before release (note off) of a trigger"),
                                                   tr("When a note is played thanks to a trigger, you can configure it to turn the note off automatically after a configurable delay. The time before release should normally be set to zero when note-off time is not being sent in the messages of this trigger."),
                                                   tr("setTriggerOff <target> <delay>"));


    Help::categories["commands"].infos << HelpInfo(QString("setCurve"),
                                                   tr("Assign a cursor to a curve"),
                                                   tr("After creating your cursor, make sure you have assigned the curve you want it to follow. You can use the keyword lastCurve to designate the last curve added."),
                                                   tr("setCurve <cursor target> <curve target>"));

    Help::categories["commands"].infos << HelpInfo(QString("setWidth"),
                                                   tr("Width of the cursor play head"),
                                                   tr("You can edit in real time the width of a cursor in order to enable or disable triggers nearby."),
                                                   tr("setWidth <target> <width>"));

    Help::categories["commands"].infos << HelpInfo(QString("setDepth"),
                                                   tr("Depth of the cursor play head"),
                                                   tr("You can edit in real time the depth of a cursor in order to enable or disable triggers nearby."),
                                                   tr("setDepth <target> <depth>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPattern"),
                                                   tr("Cursor loop pattern"),
                                                   tr("This parameter refers to the direction and the number of cycles. For example, with 1 1 0, the cursor will perform two cycles in the positive direction before stopping."),
                                                   tr("setPattern <target> <easing> 0 <pattern>"));

    Help::categories["commands"].infos << HelpInfo(QString("setSpeed"),
                                                   tr("Speed of a cursor"),
                                                   tr("Cursors have a speed factor independent of each other. The travel time of a curve is also configurable. The cursor will evolve in the negative direction if the speed is negative, but time will continue to flow naturally."),
                                                   tr("setSpeed <target> auto <duration>\n") +
                                                   tr("setSpeed <target> <speed factor>"));

    Help::categories["commands"].infos << HelpInfo(QString("setSpeedf"),
                                                   tr("Instantaneous speed of a cursor"),
                                                   tr("Cursors have an instantaneous speed factor independent, very useful for real-time performances. As setSpeed, a negative speed is possible without affecting the global speed of the score."),
                                                   tr("setSpeedF <target> <speed factor>"));

    Help::categories["commands"].infos << HelpInfo(QString("setOffset"),
                                                   tr("Cursor offsets"),
                                                   tr("You can choose to start your cursor at a certain point of the curve (marked in seconds) and limit it between certain values (also in seconds).\nFor example, the 2 4 6 offset means that your cursor will start your curve at the position t=2s then will travel to point t=6s to start again at the point t=4s."),
                                                   tr("setOffset <target> <initial> <start> <end>"));

    Help::categories["commands"].infos << HelpInfo(QString("setTime"),
                                                   tr("Instantaneous position (in seconds)"),
                                                   tr("The position of a cursor can be modified in real time. This instruction does not work if you include it directly in your script, because at each execution, IanniX does a fastrewind."),
                                                   tr("setTime <target> <time>"));

    Help::categories["commands"].infos << HelpInfo(QString("setTimePercent"),
                                                   tr("Instantaneous position (in percentages)"),
                                                   tr("The position of a cursor can be modified in real time. This instruction does not work if you include it directly in your script, because at each execution, IanniX does a fastrewind."),
                                                   tr("setTimePercent <target> <time>"));

    //TOTO  setBoundsSourceMode
    Help::categories["commands"].infos << HelpInfo(QString("setBoundsSource"),
                                                   tr("Mapping values"),
                                                   tr("You can set your cursor to send values within a chosen interval. For example, if it is operating in a 3x3 square, it can still send coordinates as values between 0 and 1.\nUse setBoundsSource to indicate to IanniX the interval in which your cursor is located and setBoundsTarget to set the range of your sent values. Generally BoundsSource is correctly set by default.\nYou must use the variables cursor_value_x, cursor_value_y, trigger_value_x, trigger_value_y, collison_value_x or collison_value_y that values sent are those of boundsTarget."),
                                                   tr("setBoundsSource <target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>\n") +
                                                   tr("setBoundsTarget <target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>"));

    Help::categories["commands"].infos << HelpInfo(QString("setBoundsTarget"),
                                                   tr("Mapping values"),
                                                   tr("You can set your cursor to send values within a chosen interval. For example, if it is operating in a 3x3 square, it can still send coordinates as values between 0 and 1.\nUse setBoundsSource to indicate to IanniX the interval in which your cursor is located and setBoundsTarget to set the range of your sent values. Generally BoundsSource is correctly set by default.\nYou must use the variables cursor_value_x, cursor_value_y, trigger_value_x, trigger_value_y, collison_value_x or collison_value_y that values sent are those of boundsTarget."),
                                                   tr("setBoundsSource <target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>\n") +
                                                   tr("setBoundsTarget <target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>"));


    Help::categories["commands"].infos << HelpInfo(QString("shiftPoints"),
                                                   tr("Shifting points of a curve"),
                                                   tr("Shfit points from left to right or right to left"),
                                                   tr("shiftPoints <target> <start point index> <-1|1>"));

    Help::categories["commands"].infos << HelpInfo(QString("translatePoints"),
                                                   tr("Translating a curve"),
                                                   tr("Translates a curve"),
                                                   tr("translatePoints <target> <dX> <dY> <dZ>"));

    Help::categories["commands"].infos << HelpInfo(QString("translatePoint"),
                                                   tr("Translating a point of a curve"),
                                                   tr("Translates a point of a curve"),
                                                   tr("translatePoint <target> <point index> <dX> <dY> <dZ>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointAt"),
                                                   tr("Setting or modifying points of a curve (straight or Bezier)"),
                                                   tr("A curve must be defined by a sequence of points. The points index starts at 0."),
                                                   tr("setPointAt <target> <point index> <x> <y>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <c1x> <c1y> <c2x> <c2y>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <z>\n") +
                                                   tr("setPointAt <target> <point index> <x> <y> <z> <c1x> <c1y> <c1z> <c2x> <c2y> <c2z>"));

    Help::categories["commands"].infos << HelpInfo(QString("setSmoothPointAt"),
                                                   tr("Setting or modifying points of a curve (with automatic smoothing)"),
                                                   tr("A curve must be defined by a sequence of points. The points index starts at 0."),
                                                   tr("setSmoothPointAt <target> <point index> <x> <y>\n") +
                                                   tr("setSmoothPointAt <target> <point index> <x> <y> <z>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointXAt"),
                                                   tr("Modifying x-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointXAt <target> <point index> <x>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointYAt"),
                                                   tr("Modifying y-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointYAt <target> <point index> <y>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointZat"),
                                                   tr("Modifying z-coordinate of a point of a curve"),
                                                   tr("Description"),
                                                   tr("setPointZAt <target> <point index> <z>"));

    Help::categories["commands"].infos << HelpInfo(QString("removePointAt"),
                                                   tr("Removing a point of a curve"),
                                                   tr("Description"),
                                                   tr("removePointAt <point index>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPointsEllipse"),
                                                   tr("Elliptical or circular curves"),
                                                   tr("Ellipses are defined by a major axis and a minor axis. To construct circles, the two axes must have the same value."),
                                                   tr("setPointsEllipse <target> <width> <height>"));


    Help::categories["commands"].infos << HelpInfo(QString("setSize"),
                                                   tr("Size of objects"),
                                                   tr("This function modifies the thickness of a curve or a cursor and the size of a trigger."),
                                                   tr("setSize <target> <size>"));

    Help::categories["commands"].infos << HelpInfo(QString("setResize"),
                                                   tr("Curve size (width/height)"),
                                                   tr("The size of objects can be changed directly."),
                                                   tr("setResize <target> <width> <height>"));

    Help::categories["commands"].infos << HelpInfo(QString("setResizeF"),
                                                   tr("Curve size (scale factor)"),
                                                   tr("The size of objects can be changed directly."),
                                                   tr("setResizeF <target> <scale factor>"));

    Help::categories["commands"].infos << HelpInfo(QString("setLine"),
                                                   tr("Paths format"),
                                                   tr("Sets a style dotted with dash pattern which must be a sequence of 0 and 1, dash style defines the space between each dot."),
                                                   tr("setLine <target> <dash style> <dash pattern>"));

    Help::categories["commands"].infos << HelpInfo(QString("setPos"),
                                                   tr("Space position"),
                                                   tr("Sets an object on the score via the coordinates (x, y, z)."),
                                                   tr("setPos <target> <x> <y> <z>"));

    Help::categories["commands"].infos << HelpInfo(QString("setLabel"),
                                                   tr("Adding text"),
                                                   tr("You can add a text description of your items on the score."),
                                                   tr("setLabel <target> <label>"));



    Help::categories["commands"].infos << HelpInfo(QString("setMessage"),
                                                   tr("Assigning a message"),
                                                   tr("This command sets the message that an object must send (please refer to Messages Syntax help)."),
                                                   tr("setMessage <target> <period>, <message1> <variables>, <message2>,message2, message3, …"));

    Help::categories["commands"].infos << HelpInfo(QString("sendOsc"),
                                                   tr("Send a message"),
                                                   tr("You can send manually a message (please refer to Messages Syntax help)."));


    Help::categories["commands"].infos << HelpInfo(QString("solo"),
                                                   tr("Solo/un-solo"),
                                                   tr("Solo/un-solo an object or a group (exactly like in Objects of inspector tab)"),
                                                   tr("solo <target> <0|1>\n"));


    Help::categories["commands"].infos << HelpInfo(QString("mute"),
                                                   tr("Mute/un-mute"),
                                                   tr("Mute/un-mute an object or a group (exactly like in Objects of inspector tab)"),
                                                   tr("mute <target> <1|0>\n"));


    Help::categories["commands"].infos << HelpInfo(QString("registerTexture"),
                                                   tr("Creating a variable texture"),
                                                   tr("Save your texture as a variable. If you are using the following variables, the display is directly modified because native textures are saved under those variables. Use the tool \"restore triggers original shapes\" from the inspector \"scripts & styles\" to find the original textures."),
                                                   tr("registerTexture <variable> <x-top-left-corner> <y-top-left-corner> <x-bottom-right-corner> <y-bottom-right-corner> <file name>"));


    Help::categories["commands"].infos << HelpInfo(QString("setTexture"),
                                                   tr("Texture of an object"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTexture <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureActive"),
                                                   tr("Texture of an active object that does not send any messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureActive <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setTextureInactive"),
                                                   tr("Texture of an inactive object that does not send any messages"),
                                                   tr("Modify the texture of an object or a group with a preloaded texture (refer to registerTexture)."),
                                                   tr("setTextureInactive <target> <variable>"));


    Help::categories["commands"].infos << HelpInfo(QString("registerColor"),
                                                   tr("Creating a variable color (RGB)"),
                                                   tr("IanniX can also save a color as a variable for reusing it more easily."),
                                                   tr("registerColor <variable> <r> <g> <b> <a>"));

    Help::categories["commands"].infos << HelpInfo(QString("registerColorHue"),
                                                   tr("Creating a variable color (HSB)"),
                                                   tr("IanniX can also save a color as a variable for reusing it more easily."),
                                                   tr("registerColor <variable> <h> <s> <b> <a>"));

    Help::categories["commands"].infos << HelpInfo(QString("setColor"),
                                                   tr("Color of an object (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColor <target> <r> <g> <b> <a>\n") +
                                                   tr("setColor <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setColorHue"),
                                                   tr("Color of an object (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorHue <target> <variable>"));


    Help::categories["commands"].infos << HelpInfo(QString("setColorActive"),
                                                   tr("Color of an active object that does not send any messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActive <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorActive <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactive"),
                                                   tr("Color of an inactive object that does not send any messages (RGB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactive <target> <r> <g> <b> <a>\n") +
                                                   tr("setColorInactive <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setColorActiveHue"),
                                                   tr("Color of an active object that does not send any messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorActiveHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorActiveHue <target> <variable>"));

    Help::categories["commands"].infos << HelpInfo(QString("setColorInactiveHue"),
                                                   tr("Color of an inactive object that send messages (HSB)"),
                                                   tr("Modify the color of an object or a group with a specific color or a preloaded color (refer to registerColor or registerColorHur)."),
                                                   tr("setColorInactiveHue <target> <h> <s> <b> <a>\n") +
                                                   tr("setColorInactiveHue <target> <variable>"));


    Help::categories["commands"].infos << HelpInfo(QString("zoom"),
                                                   tr("Zoom in score"),
                                                   tr("Adjust the zoom using the script. The factor is in percent. e.g. A factor of 200 doubles the size of the display area."),
                                                   tr("zoom <zoom factor>"));

    Help::categories["commands"].infos << HelpInfo(QString("center"),
                                                   tr("Center score"),
                                                   tr("Placing the point (x,y) in the center of the workspace"),
                                                   tr("center <x> <y>"));

    Help::categories["commands"].infos << HelpInfo(QString("viewport"),
                                                   tr("Resize the viewport"),
                                                   tr("Resize the viewport"),
                                                   tr("viewport <width> <height>"));


    Help::categories["commands"].infos << HelpInfo(QString("snapshot"),
                                                   tr("Export as an image snapshot"),
                                                   tr("Make a snapshot of current score"),
                                                   tr("snapshot <scale> <filename,optional>"));

    Help::categories["commands"].infos << HelpInfo(QString("rotate"),
                                                   tr("Rotate score"),
                                                   tr("Rotate the view about the x, y and z axes"),
                                                   tr("rotate <x-axis> <y-axis> <z-axis>"));

    Help::categories["commands"].infos << HelpInfo(QString("rotate"),
                                                   tr("Rotate score"),
                                                   tr("Rotate the view about the x, y and z axes"),
                                                   tr("rotate <x-axis> <y-axis> <z-axis>"));

    Help::categories["commands"].infos << HelpInfo(QString("play"),
                                                   tr("Playing the score"),
                                                   tr("Enabling the playback"),
                                                   tr("play <score speed>"));

    Help::categories["commands"].infos << HelpInfo(QString("stop"),
                                                   tr("Stopping the score"),
                                                   tr("Disabling the playback"),
                                                   tr("stop"));

    Help::categories["commands"].infos << HelpInfo(QString("fastrewind"),
                                                   tr("Fastrewinding the score"),
                                                   tr("Go back to the begging of score"),
                                                   tr("fastrewind"));

    Help::categories["commands"].infos << HelpInfo(QString("speed"),
                                                   tr("Speed of the score"),
                                                   tr("You can set the global speed of the score. A negative speed will evolve over time in the negative direction."),
                                                   tr("speed <speed>"));

    Help::categories["commands"].infos << HelpInfo(QString("load"),
                                                   tr("Load a score or a script"),
                                                   tr("Load a score or a script of the current project folder"),
                                                   tr("load <score name>"));

    Help::categories["commands"].infos << HelpInfo(QString("log"),
                                                   tr("Log information to console"),
                                                   tr("Log information to IanniX console (network tab)"),
                                                   tr("log <text>"));

    Help::categories["commands"].infos << HelpInfo(QString("goto"),
                                                   tr("Go to a specific timecode"),
                                                   tr("Go to a specific timecode in seconds"),
                                                   tr("goto <time in seconds>"));

    Help::categories["commands"].infos << HelpInfo(QString("mouse"),
                                                   tr("Control mouse"),
                                                   tr("Enable to move cursor of the mouse"),
                                                   tr("mouse <x> <y>"));



    Help::categories["commands"].infos << HelpInfo(QString("title"),
                                                   tr("Get IanniX window title"),
                                                   tr("Returns IanniX window title (scripts only)"),
                                                   tr("title"));

    Help::categories["commands"].infos << HelpInfo(QString("sleep"),
                                                   tr("Make IanniX script sleeping (scripts only)"),
                                                   tr("Set a sleep time. BE CAREFUL, IanniX will not respond during sleeping"),
                                                   tr("sleep <duration>"));


    foreach(const HelpInfo &info, Help::categories["values"].infos)
        Help::keywords.append(qPrintable(info.keyword));
}
