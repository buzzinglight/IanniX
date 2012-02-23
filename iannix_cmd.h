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

#ifndef IANNIX_CMD_H
#define IANNIX_CMD_H


#define COMMAND_END_BYTE                    '\n'
#define COMMAND_END                         QString(COMMAND_END_BYTE)
#define COMMAND_ADD                         QString("add")
#define COMMAND_REMOVE                      QString("remove")
#define COMMAND_CLEAR                       QString("clear")
#define COMMAND_GROUP                       QString("setgroup")
#define COMMAND_ACTIVE                      QString("setactive")

#define COMMAND_TRIGGER_OFF                 QString("settriggeroff")

#define COMMAND_CURSOR_CURVE                QString("setcurve")
#define COMMAND_CURSOR_WIDTH                QString("setwidth")
#define COMMAND_CURSOR_START                QString("setpattern")
#define COMMAND_CURSOR_SPEED                QString("setspeed")
#define COMMAND_CURSOR_SPEEDF               QString("setspeedf")
#define COMMAND_CURSOR_OFFSET               QString("setoffset")
#define COMMAND_CURSOR_BOUNDS_SOURCE        QString("setboundssource")
#define COMMAND_CURSOR_BOUNDS_TARGET        QString("setboundstarget")
#define COMMAND_CURSOR_TIME                 QString("settime")

#define COMMAND_CURVE_POINT                 QString("setpointat")
#define COMMAND_CURVE_POINT_SMOOTH          QString("setsmoothpointat")
#define COMMAND_CURVE_POINT_RMV             QString("removepointat")
#define COMMAND_CURVE_TXT                   QString("setpointstxt")
#define COMMAND_CURVE_SVG                   QString("setpointssvg")
#define COMMAND_CURVE_SVG2                  QString("setpointssvg2")
#define COMMAND_CURVE_PATH                  QString("setpointspath")
#define COMMAND_CURVE_LINES                 QString("setpointslines")
#define COMMAND_CURVE_IMG                   QString("setpointsimg")
#define COMMAND_CURVE_ELL                   QString("setpointsellipse")

#define COMMAND_SIZE                        QString("setsize")
#define COMMAND_RESIZE                      QString("setresize")
#define COMMAND_RESIZEF                     QString("setresizef")
#define COMMAND_LINE                        QString("setline")
#define COMMAND_POS                         QString("setpos")
#define COMMAND_LABEL                       QString("setlabel")

#define COMMAND_MESSAGE                     QString("setmessage")
#define COMMAND_MESSAGE_SEND                QString("sendosc")


#define COMMAND_TEXTURE                     QString("registertexture")

#define COMMAND_TEXTURE_GLOBAL              QString("settexture")
#define COMMAND_TEXTURE_ACTIVE              QString("settextureactive")
#define COMMAND_TEXTURE_INACTIVE            QString("settextureinactive")
#define COMMAND_TEXTURE_ACTIVE_MESSAGE      QString("settextureactivemessage")
#define COMMAND_TEXTURE_INACTIVE_MESSAGE    QString("settextureinactivemessage")


#define COMMAND_GLOBAL_COLOR                QString("registercolor")
#define COMMAND_GLOBAL_COLOR2               QString("registercolor2")
#define COMMAND_GLOBAL_COLOR_HUE            QString("registercolorhue")

#define COMMAND_COLOR_GLOBAL                QString("setcolor")
#define COMMAND_COLOR_GLOBAL2               QString("setcolor2")
#define COMMAND_COLOR_GLOBAL_HUE            QString("setcolorhue")

#define COMMAND_COLOR_ACTIVE                QString("setcoloractive")
#define COMMAND_COLOR_INACTIVE              QString("setcolorinactive")
#define COMMAND_COLOR_ACTIVE_MESSAGE        QString("setcoloractivemessage")
#define COMMAND_COLOR_INACTIVE_MESSAGE      QString("setcolorinactivemessage")

#define COMMAND_COLOR_ACTIVE2               QString("setcoloractive2")
#define COMMAND_COLOR_INACTIVE2             QString("setcolorinactive2")
#define COMMAND_COLOR_ACTIVE_MESSAGE2       QString("setcoloractivemessage2")
#define COMMAND_COLOR_INACTIVE_MESSAGE2     QString("setcolorinactivemessage2")
#define COMMAND_COLOR_ACTIVE_HUE            QString("setcoloractivehue")
#define COMMAND_COLOR_INACTIVE_HUE          QString("setcolorinactivehue")
#define COMMAND_COLOR_ACTIVE_MESSAGE_HUE    QString("setcoloractivemessagehue")
#define COMMAND_COLOR_INACTIVE_MESSAGE_HUE  QString("setcolorinactivemessagehue")

#define COMMAND_AUTOSIZE                    QString("autosize")
#define COMMAND_ZOOM                        QString("zoom")
#define COMMAND_CENTER                      QString("center")
#define COMMAND_ROTATE                      QString("rotate")
#define COMMAND_PLAY                        QString("play")
#define COMMAND_STOP                        QString("stop")
#define COMMAND_FF                          QString("fastrewind")
#define COMMAND_SPEED                       QString("speed")
#define COMMAND_LOG                         QString("log")
#define COMMAND_GOTO                        QString("goto")
#define COMMAND_TITLE                       QString("title")
#define COMMAND_SLEEP                       QString("sleep")

#define COMMAND_SNAP_PUSH                   QString("pushsnapshot")
#define COMMAND_SNAP_POP                    QString("popsnapshot")

#endif // IANNIX_CMD_H
