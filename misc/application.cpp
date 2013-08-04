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
UiBool  Render::paintThisGroup         = false;
UiBool  Render::forceLists             = false;
UiBool  Render::forceTexture           = false;
UiBool  Render::forceFrustumInInit     = false;
UiReal  Application::followId               = 9999;
qreal   Render::objectSize             = 1;
qreal   Render::zoomValue              = 1;
qreal   Render::zoomLinear             = 1;
qreal   Render::zoomLinearDest         = 1;
qreal   Render::axisGrid               = 1;
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
        return render->grabFrameBuffer();
    else
        return QImage();
}
