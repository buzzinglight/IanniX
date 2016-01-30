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

#include "application.h"

Render*             Application::render = 0;
ApplicationCurrent* Application::current = 0;
void*               Application::synchroLoopGuard = 0;
QWidget*            Application::splash = 0;
QFileInfo           Application::pathApplication;
QFileInfo           Application::pathDocuments;
QFileInfo           Application::pathCurrent;

UiString Application::defaultMessageTrigger   = QString("osc://ip_out:port_out/trigger trigger_id trigger_group_id trigger_value_x trigger_value_y trigger_value_z trigger_xPos trigger_yPos trigger_zPos cursor_id cursor_group_id, midi://midi_out/notef 1 trigger_value_y trigger_value_x trigger_duration, tcp:// trigger trigger_id trigger_group_id trigger_value_x trigger_value_y trigger_value_z trigger_xPos trigger_yPos trigger_zPos cursor_id cursor_group_id");
UiString Application::defaultMessageCursor    = QString("osc://ip_out:port_out/cursor cursor_id cursor_group_id cursor_value_x cursor_value_y cursor_value_z cursor_xPos cursor_yPos cursor_zPos, tcp:// cursor cursor_id cursor_group_id cursor_value_x cursor_value_y cursor_value_z cursor_xPos cursor_yPos cursor_zPos");
UiString Application::defaultMessageCurve     = QString("osc://ip_out:port_out/curve collision_curve_id collision_curve_group_id collision_value_x collision_value_y 0 collision_xPos collision_yPos 0, tcp:// curve collision_curve_id collision_curve_group_id collision_value_x collision_value_y 0 collision_xPos collision_yPos 0");
UiString Application::defaultMessageTransport = QString("osc://ip_out:port_out/transport status global_time global_time_verbose nb_triggers nb_cursors nb_curves, tcp:// transport status nb_triggers nb_cursors nb_curves");
UiString Application::defaultMessageSync      = QString("osc://ip_out:port_out/iannix/ status");
UiString Application::defaultMessage          = QString("osc://ip_out:port_out/object trigger_id trigger_group_id cursor_id cursor_group_id");

QFont   Application::renderFont;
UiBool  Application::paintAxisGrid          = true;
UiBool  Application::paintCurvesOpacity     = false;
UiBool  Application::paintLabel             = true;
UiBool  Application::allowSelection         = false;
UiBool  Application::allowSelectionCursors  = true;
UiBool  Application::allowSelectionCurves   = true;
UiBool  Application::allowSelectionTriggers = true;
UiBool  Application::allowPlaySelected      = false;
UiBool  Application::colorTheme             = true;
UiBool  Application::allowLockPos           = false;
UiBool  Application::mouseSnapX             = false;
UiBool  Application::mouseSnapY             = false;
UiBool  Application::mouseSnapZ             = false;
UiReal  Application::objectsAutosize        = 0;



QMap<QString, QColor> Render::defaultColors;
UiTextureItems* Render::textures;
UiColorItems*   Render::colors;
NxRect  Render::selectionArea;
NxRect  Render::axisArea;
NxPoint Render::axisCenter;
NxPoint Render::axisCenterDest;
NxPoint Render::rotation;
NxPoint Render::rotationDest;
NxPoint Render::rotationCenter;
NxPoint Render::rotationCenterDest;
UiBool  Render::paintThisGroup         = false;
UiBool  Render::forceLists             = false;
UiBool  Render::forceTexture           = false;
UiBool  Render::forceFrustumInInit     = false;
UiReal  Application::followId          = 9999;
UiBool  Application::enableMiniLog     = true;
qreal   Render::objectSize             = 1;
qreal   Render::zoomValue              = 1;
qreal   Render::zoomLinear             = 1;
qreal   Render::zoomLinearDest         = 1;
UiReal  Render::axisGrid               = 1;
EditingMode Render::editingMode        = EditingModeFree;
bool    Render::editing                = false;
bool    Render::editingFirstPoint      = false;




void Application::setInterfaces(ApplicationCurrent *_current, Render *_render) {
    if(_current) {
        current = _current;
        ApplicationExecute::current = current;
    }
    if(_render)
        render  = _render;
}

QImage Application::takeScreenshot() {
    if(render)
#ifdef USE_GLWIDGET
        return render->grabFrameBuffer();
#else
        return render->grabFramebuffer();
#endif
    else
        return QImage();
}
