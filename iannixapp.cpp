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

IanniXApp::IanniXApp(int &argc, char **argv) :
    QApplication(argc, argv) {
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    /*
    QTranslator translator;
    translator.load("iannix");
    installTranslator(&translator);
    */

    QString appName = "IanniX ";
    QString appVersion = "0.8.4";

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

    QString appPackage = (appName + "__" + appVersion).toLower().replace(" ", "_").replace(".", "_");
    qDebug("Starting %s %s (%s)", qPrintable(appName), qPrintable(appVersion), qPrintable(appPackage));

    QCoreApplication::setApplicationName(appName);
    QCoreApplication::setApplicationVersion(appVersion);
    QCoreApplication::setOrganizationName("IanniX");
    QCoreApplication::setOrganizationDomain("org.iannix");

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


int main(int argc, char *argv[]) {
    IanniXApp iannixApp(argc, argv);

    return iannixApp.exec();
}

