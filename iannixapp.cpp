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
#include "gui/uisplashscreen.h"



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
    QString appVersion = "0.9.1";

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
    iannix = 0;
}

void IanniXApp::launch(int &argc, char **argv) {
    //Display splash
    Application::splash = new UiSplashScreen(QPixmap(":/general/res_splash.png"));

    //Start
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
    if(Global::pathApplication.absoluteFilePath().endsWith("/IanniX-build/release"))
        Global::pathApplication = QFileInfo(Global::pathApplication.absoluteFilePath().remove("-build/release"));
    if(Global::pathApplication.absoluteFilePath().endsWith("/IanniX-build"))
        Global::pathApplication = QFileInfo(Global::pathApplication.absoluteFilePath().remove("-build"));

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

    quint16 indexArgument = 1;
#ifdef Q_OS_WIN
    //TOTO
    indexArgument = 0;
#endif
    if(argc > indexArgument)
        project = QFileInfo(Global::pathCurrent.absoluteFilePath() + "/" + argv[indexArgument]);

    //Add font
    if(QFontDatabase::addApplicationFont(Global::pathApplication.absoluteFilePath() + "/Tools/Museo.ttf"))
        qDebug("Loading IanniX font failed : %s", qPrintable(Global::pathApplication.absoluteFilePath() + "/Tools/Museo.ttf"));
    //List of fonts
    if(false) {
        qDebug("[FONTS]");
        QFontDatabase fontDb;
        QStringList fontList = fontDb.families();
        foreach(const QString &font, fontList) {
            qDebug("\tFamille : %s", qPrintable(font));
            if(true) {
                qDebug("\t\tFont : %s", qPrintable(font));
                QStringList styleList = fontDb.styles(font);
                foreach(const QString &style, styleList) {
                    int weight = fontDb.weight(font, style);
                    qDebug("\t\t\t > Style / Graisse %s %d", qPrintable(style), weight);
                }
            }
        }
    }

    if(project.exists()) {
        qDebug("Loading project %s", qPrintable(project.absoluteFilePath()));
        iannix = new IanniX(project.absoluteFilePath());
    }
    else
        iannix = new IanniX();
}

bool IanniXApp::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::FileOpen:
        project = QFileInfo(static_cast<QFileOpenEvent*>(event)->file());
        if(iannix) {
            if(iannix->projectIsLoaded)
                iannix->loadProject(project.absoluteFilePath());
            else
                iannix->projectToLoad = project.absoluteFilePath();
        }
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
    Help::categories["port"].infos << HelpInfo(QString("port_out"),                tr("Default port set in \"Network\" tab"));
    Help::categories["port"].infos << HelpInfo(QString("57120"),                   tr("Basic output port used by IanniX"));
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
    Help::categories["values"].infos << HelpInfo(QString("trigger_value"),         tr("When trigger duration is not null, returns 127 when the trigger is trigged and 0 when the trigger is released"));
    Help::categories["values"].infos << HelpInfo(QString("trigger_duration"),      tr("Trigger duration"));
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
    Help::categories["commands"].infos << HelpInfo(COMMAND_ADD						, tr("Objects instances"), tr("Adds an object to score"), tr("<trigger|curve|cursor> <id>\nadd <trigger|curve|cursor> auto"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_REMOVE					, tr("Objects instances"), tr("Removes an object from score"), tr("<id>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CLEAR					, tr("Objects instances"), tr("Clears the score (remove all objects)"), tr(""));
    Help::categories["commands"].infos << HelpInfo(COMMAND_ID						, tr(""), tr(""), tr("<old_id> <new_id>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_GROUP					, tr(""), tr(""), tr("<target> <group_id>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_TRIGGER_OFF				, tr(""), tr(""), tr("<target> <duration>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_ACTIVE					, tr(""), tr(""), tr("<target> <0|1>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_CURVE				, tr("Objects identification"), tr("Associates a cursor to a curve"), tr("<target> <curve_id>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_START				, tr(""), tr(""), tr("<target> <easing> <0> <loop_pattern>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_WIDTH				, tr(""), tr(""), tr("<target> <width>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_DEPTH				, tr(""), tr(""), tr("<target> <depth>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_SPEED				, tr(""), tr(""), tr("<target> <speed>\n<target> auto <duration>\n<target> lock <fixed_speed\n<target> autolock <fixed_duration>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_SPEEDF			, tr(""), tr(""), tr("<target> <speed_factor>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_BOUNDS_SOURCE		, tr(""), tr(""), tr("<target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_BOUNDS_SOURCE_MODE, tr(""), tr(""), tr("<target> <0|1|2|3>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_BOUNDS_TARGET		, tr(""), tr(""), tr("<target> <x-start> <x-end> <y-start> <y-end> <z-start> <z-end>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_OFFSET			, tr(""), tr(""), tr("<target> <initial> <loop-start> <loop-end>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_EDITOR				, tr("Objects and 3D space"), tr("Displays curve points editor"), tr(""));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_EQUATION			, tr(""), tr(""), tr("<target> cartesian <parametric_equation_for_x> <parametric_equation_for_y> <parametric_equation_for_z>\n<target> polar <parametric_equation_for_radius> <parametric_equation_for_phi> <parametric_equation_for_theta>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_EQUATION_POINTS	, tr(""), tr(""), tr("<target> <nb_of_points>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_ELL				, tr("Objects and 3D space"), tr("Defines a curve as an ellipse"), tr("<target> <width> <height>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT				, tr("Objects and 3D space"), tr("Defines point position of a curve"), tr("<target> <point_index> <x> <y> <z>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_SMOOTH		, tr("Objects and 3D space"), tr("Defines smoothed point position of a curve"), tr("<target> <point_index> <x> <y> <z>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_RMV			, tr("Objects and 3D space"), tr("Removes point from a curve"), tr("<target> <point_index>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_SIZE						, tr(""), tr(""), tr("<target> <size>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_POS						, tr("Objects and 3D space"), tr("Changes the absolute position of object"), tr("<target> <x> <y> <z>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_POS_TRANSLATE			, tr("Objects and 3D space"), tr("Translate position of object"), tr("<target> <dx> <dy> <dz>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_POS_X					, tr(""), tr(""), tr("<target> <x>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_POS_Y					, tr(""), tr(""), tr("<target> <y>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_POS_Z					, tr(""), tr(""), tr("<target> <z>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_MESSAGE					, tr(""), tr(""), tr("<target> <interval>, <message1>, <message1>, …"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_MESSAGE_INTERVAL			, tr(""), tr(""), tr("<target> <interval>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_LABEL					, tr(""), tr(""), tr("<target> <label>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_ZOOM						, tr("Score viewport"), tr("Changes current score zoom"), tr("<zoom>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_GOTO						, tr(""), tr(""), tr("<timecode>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_PLAY						, tr("Playback"), tr("Starts the playback"), tr("<speed (optional)>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_STOP						, tr("Playback"), tr("Stops the playback"), tr(""));
    Help::categories["commands"].infos << HelpInfo(COMMAND_FF						, tr(""), tr(""), tr(""));
    Help::categories["commands"].infos << HelpInfo(COMMAND_SPEED					, tr(""), tr(""), tr("<speed>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CENTER					, tr("Score viewport"), tr("Moves the center of the score"), tr("<x> <y>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_ROTATE					, tr("Score viewport"), tr("Rotates camera point of view"), tr("<angle_along_x-axis> <angle_along_y-axis> <angle_along_z-axis>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_TRIG						, tr("Objects and messages"), tr("Forces an object to send its messages"), tr("<target>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_GLOBAL_COLOR				, tr(""), tr(""), tr("<target> <color_name> <r> <g> <b> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_ACTIVE				, tr(""), tr(""), tr("<target> <color_name>\n<target> <r> <g> <b> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_INACTIVE			, tr(""), tr(""), tr("<target> <color_name>\n<target> <r> <g> <b> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_TEXTURE					, tr(""), tr(""), tr("<target> <texture_name> <x-top-left> <y-top-left> <x-bottom-right> <y-bottom-right> <texture_filename>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_TEXTURE_ACTIVE			, tr(""), tr(""), tr("<target> <texture_name>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_TEXTURE_INACTIVE			, tr(""), tr(""), tr("<target> <texture_name>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_SOLO						, tr("Objects identification"), tr("Switch an object or a group to solo mode"), tr("<target> <0|1>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_MUTE						, tr("Objects identification"), tr("Mutes an object or a group"), tr("<target> <0|1>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_TXT				, tr("Objects and 3D space"), tr(""), tr("See examples through GUI"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_PATH				, tr("Objects and 3D space"), tr(""), tr("See examples through GUI"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_RESIZE					, tr(""), tr(""), tr("<target> <width> <height>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_TIME_PERCENT		, tr("Objects and time"), tr("Sets cursors to a specific time on curve (as percentage of total duration)"), tr("<target> <percentage>"));

    Help::categories["commands"].infos << HelpInfo(COMMAND_TEXTURE_GLOBAL			, tr("Objects style"), tr("Changes the texture (image) of active and inactive objects"), tr("<target> <texture_name>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_GLOBAL_COLOR_HUE			, tr(""), tr(""), tr("<target> <color_name> <h> <s> <v> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_GLOBAL				, tr("Objects style"), tr("Changes the color of active and inactive objects by using a color in the palette or a custom color"), tr("<target> <color_name>\n<target> <r> <g> <b> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_GLOBAL_HUE			, tr("Objects style"), tr("Changes the color of active and inactive objects by using a color in the palette or a custom color"), tr("<target> <color_name>\n<target> <h> <s> <v> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_ACTIVE_HUE			, tr(""), tr(""), tr("<target> <color_name>\n<target> <h> <s> <v> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_COLOR_INACTIVE_HUE		, tr(""), tr(""), tr("<target> <color_name>\n<target> <h> <s> <v> <a>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURSOR_TIME				, tr("Objects and time"), tr("Sets cursors to a specific time on curve (absolute time)"), tr("<target> <time>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_LOG						, tr("IanniX actions"), tr("Logs information to IanniX messages log"), tr("<text>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_EQUATION_PARAM		, tr("Objects and 3D space"), tr("Sets a value to an equation parameter"), tr("<target> <param_name> <param_value>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_LINES				, tr("Objects style"), tr("Defines points of a curve as SVG polylines"), tr("See examples through GUI"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_LOAD						, tr("IanniX actions"), tr("Loads a specific score"), tr("<filename>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_MESSAGE_SEND				, tr("IanniX actions"), tr("Send a message (in IanniX format)"), tr("<message>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_MOUSE					, tr("IanniX actions"), tr("Sets mouse cursor position"), tr("<x> <y>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_SHIFT		, tr("Objects and 3D space"), tr("Shifts points of a curve in a direction"), tr("<target> <point_index> <-1|1>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_TRANSLATE	, tr("Objects and 3D space"), tr("Translates points of a curve"), tr("<target> <dx> <dy> <dz>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_TRANSLATE2	, tr("Objects and 3D space"), tr("Translates a point of a curve"), tr("<target> <point_index> <dx> <dy> <dz>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_X			, tr("Objects and 3D space"), tr("Defines point X-coordinate of a curve"), tr("<target> <point_index> <x>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_Y			, tr("Objects and 3D space"), tr("Defines point Y-coordinate of a curve"), tr("<target> <point_index> <y>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_CURVE_POINT_Z			, tr("Objects and 3D space"), tr("Defines point Z-coordinate of a curve"), tr("<target> <point_index> <z>"));
    Help::categories["commands"].infos << HelpInfo(COMMAND_RESIZEF					, tr("Objects and 3D space"), tr("Apply a scale factor on objects width and height"), tr("<target> <scale_factor>"));
    //Help::categories["commands"].infos << HelpInfo(COMMAND_LINE                   , tr("Objects style"), tr("Changes the way lines are drawn (dashed, plain…)"), tr("Not yet documented"));


    foreach(const HelpInfo &info, Help::categories["values"].infos)
        Help::keywords.append(qPrintable(info.keyword));
}
