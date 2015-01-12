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

#ifndef IANNIX_CMD_H
#define IANNIX_CMD_H


#define COMMAND_END_BYTE                    '\n'
#define COMMAND_END                         QString(COMMAND_END_BYTE)

// DOCUMENTED IN GUI
#define COMMAND_ADD                         "add"
#define COMMAND_REMOVE                      "remove"
#define COMMAND_CLEAR                       "clear"
#define COMMAND_ID                          "setid"
#define COMMAND_GROUP                       "setgroup"
#define COMMAND_TRIGGER_OFF                 "settriggeroff"
#define COMMAND_ACTIVE                      "setactive"
#define COMMAND_CURSOR_CURVE                "setcurve"
#define COMMAND_CURSOR_START                "setpattern"
#define COMMAND_CURSOR_WIDTH                "setwidth"
#define COMMAND_CURSOR_DEPTH                "setdepth"
#define COMMAND_CURSOR_SPEED                "setspeed"
#define COMMAND_CURSOR_SPEEDF               "setspeedf"
#define COMMAND_CURSOR_BOUNDS_SOURCE        "setboundssource"
#define COMMAND_CURSOR_BOUNDS_SOURCE_MODE   "setboundssourcemode"
#define COMMAND_CURSOR_BOUNDS_TARGET        "setboundstarget"
#define COMMAND_CURSOR_OFFSET               "setoffset"
#define COMMAND_CURVE_EDITOR                "displaycurveeditor"
#define COMMAND_CURVE_RESAMPLE              "displaycurveresample"
#define COMMAND_CURVE_EQUATION              "setequation"
#define COMMAND_CURVE_EQUATION_POINTS       "setequationnbpoints"
#define COMMAND_CURVE_ELL                   "setpointsellipse"
#define COMMAND_CURVE_POINT                 "setpointat"
#define COMMAND_CURVE_POINT_SMOOTH          "setsmoothpointat"
#define COMMAND_CURVE_POINT_RMV             "removepointat"
#define COMMAND_SIZE                        "setsize"
#define COMMAND_POS                         "setpos"
#define COMMAND_POS_TRANSLATE               "settranslate"
#define COMMAND_POS_X                       "setposx"
#define COMMAND_POS_Y                       "setposy"
#define COMMAND_POS_Z                       "setposz"
#define COMMAND_MESSAGE                     "setmessage"
#define COMMAND_MESSAGE_INTERVAL            "setmessageinterval"
#define COMMAND_LABEL                       "setlabel"
#define COMMAND_ZOOM                        "zoom"
#define COMMAND_GOTO                        "goto"
#define COMMAND_PLAY                        "play"
#define COMMAND_STOP                        "stop"
#define COMMAND_FF                          "fastrewind"
#define COMMAND_SPEED                       "speed"
#define COMMAND_CENTER                      "center"
#define COMMAND_ROTATE                      "rotate"
#define COMMAND_TRIG                        "trig"
#define COMMAND_GLOBAL_COLOR                "registercolor"
#define COMMAND_COLOR_ACTIVE                "setcoloractive"
#define COMMAND_COLOR_INACTIVE              "setcolorinactive"
#define COMMAND_COLOR_MULTIPLY              "setcolormultiply"
#define COMMAND_TEXTURE                     "registertexture"
#define COMMAND_TEXTURE_ACTIVE              "settextureactive"
#define COMMAND_TEXTURE_INACTIVE            "settextureinactive"
#define COMMAND_SOLO                        "setsolo"
#define COMMAND_MUTE                        "setmute"
#define COMMAND_CURVE_TXT                   "setpointstxt"
#define COMMAND_CURVE_PATH                  "setpointspath"
#define COMMAND_RESIZE                      "setresize"
#define COMMAND_CURSOR_TIME_PERCENT         "settimepercent"



// CLOSE TO OTHER FUNCTIONS
#define COMMAND_TEXTURE_GLOBAL              "settexture"
#define COMMAND_GLOBAL_COLOR_HUE            "registercolorhue"
#define COMMAND_COLOR_GLOBAL                "setcolor"
#define COMMAND_COLOR_GLOBAL_HUE            "setcolorhue"
#define COMMAND_COLOR_ACTIVE_HUE            "setcoloractivehue"
#define COMMAND_COLOR_INACTIVE_HUE          "setcolorinactivehue"
#define COMMAND_COLOR_MULTIPLY_HUE          "setcolormultiplyhue"
#define COMMAND_CURSOR_TIME                 "settime"


// DOCUMENTED IN SCRIPT TEMPLATE
#define COMMAND_LOG                         "log"
#define COMMAND_TITLE                       "title"


// SCRIPT SPECIFC
#define COMMAND_CURVE_EQUATION_PARAM        "setequationparam"
#define COMMAND_CURVE_LINES                 "setpointslines"
#define COMMAND_LOAD                        "load"
#define COMMAND_OPEN                        "open"
#define COMMAND_CLOSE                       "close"
#define COMMAND_CURVE_LENGTH                "setlength"
#define COMMAND_MESSAGE_SEND                "sendmessage"
#define COMMAND_MOUSE                       "mouse"
#define COMMAND_CURVE_POINT_SHIFT           "shiftpoints"
#define COMMAND_CURVE_POINT_TRANSLATE       "translatepoints"
#define COMMAND_CURVE_POINT_TRANSLATE2      "translatepoint"
#define COMMAND_CURVE_POINT_X               "setpointxat"
#define COMMAND_CURVE_POINT_Y               "setpointyat"
#define COMMAND_CURVE_POINT_Z               "setpointzat"
#define COMMAND_RESIZEF                     "setresizef"


// BETA FUNCTIONS
#define COMMAND_CURVE_INERTIE               "setelasticity"
#define COMMAND_LINE                        "setline"


// INTERNAL FUNCTIONS
#define COMMAND_SLEEP                       "sleep"
#define COMMAND_VIEWPORT                    "viewport"
#define COMMAND_SNAPSHOT                    "snapshot"

#endif // IANNIX_CMD_H
