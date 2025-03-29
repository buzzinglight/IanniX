/********************************************************************************
** Form generated from reading UI file 'uirender.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIRENDER_H
#define UI_UIRENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiRender
{
public:

    void setupUi(QWidget *UiRender)
    {
        if (UiRender->objectName().isEmpty())
            UiRender->setObjectName(QString::fromUtf8("UiRender"));
        UiRender->resize(556, 471);

        retranslateUi(UiRender);

        QMetaObject::connectSlotsByName(UiRender);
    } // setupUi

    void retranslateUi(QWidget *UiRender)
    {
        UiRender->setWindowTitle(QCoreApplication::translate("UiRender", "IanniX \342\200\224 Render", nullptr));
#if QT_CONFIG(statustip)
        UiRender->setStatusTip(QCoreApplication::translate("UiRender", "Score render|As you understood, IanniX is a graphical sequencer. It means that you'll have to draw a score using three main objects: triggers (events), curves (spatial trajectories) and cursors (playheads). The score rendering area is 3D space where you'll be able to manipulate these objects. By default, one grid unit represents one second.\\n\\n Here are some useful tips to navigate through your score:\\n - Click+mouse move allows you the scroll in the score\\n - Mouse wheel will zoom or unzoom\\n - Shift+click selects objects\\n - Alt+click+mouse move changes the camera point of view\\n - Alt+mouse wheel changes the camera distance\\n - Alt+double click resets the camera position if you're lost in 3D (this can happen)\\n\\n If an object is selected:\\n - Double click on the object allows you to edit its messages\\n - Shift+double click force the object to sent its messages (very useful while making your mappings/MIDI learnings)\\n - Control+alt+move enables grid snapping (Command key for Mac users)\\n\\n And"
                        " last thing, score edition is not possible if you're in 3D... So before trying to edit something, go back to 2D with Alt+double click.", nullptr));
#endif // QT_CONFIG(statustip)
    } // retranslateUi

};

namespace Ui {
    class UiRender: public Ui_UiRender {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIRENDER_H
