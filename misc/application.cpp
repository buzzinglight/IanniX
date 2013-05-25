#include "application.h"

Render*             Application::render = 0;
ApplicationCurrent* Application::current = 0;
void*               Application::synchroLoopGuard = 0;

void Application::setInterfaces(ApplicationCurrent *_current, Render *_render) {
    if(_current)
        current = _current;
    if(_render)
        render  = _render;
}

QImage Application::takeScreenshot() {
    if(render)
        return render->grabFrameBuffer();
    else
        return QImage();
}
