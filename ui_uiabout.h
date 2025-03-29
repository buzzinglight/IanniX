/********************************************************************************
** Form generated from reading UI file 'uiabout.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIABOUT_H
#define UI_UIABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiAbout
{
public:
    QLabel *picture;
    QTextEdit *credits;
    QLabel *version;
    QTextEdit *header;

    void setupUi(QWidget *UiAbout)
    {
        if (UiAbout->objectName().isEmpty())
            UiAbout->setObjectName(QString::fromUtf8("UiAbout"));
        UiAbout->resize(348, 598);
        UiAbout->setMinimumSize(QSize(348, 598));
        UiAbout->setMaximumSize(QSize(348, 598));
        UiAbout->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	font: 				12px \"Museo Sans\", \"Museo Sans 500\", \"Arial\";;\n"
"	color: 				rgba(255, 255, 255, 220);\n"
"}\n"
"QWidget#version {\n"
"	color: 				rgba(255, 255, 255, 128);\n"
"}\n"
"\n"
"QTextEdit {\n"
"	background: 	transparent;\n"
"	border: 			0px solid transparent;\n"
"}"));
        picture = new QLabel(UiAbout);
        picture->setObjectName(QString::fromUtf8("picture"));
        picture->setGeometry(QRect(0, 0, 350, 600));
        picture->setMinimumSize(QSize(350, 600));
        picture->setMaximumSize(QSize(350, 600));
        picture->setPixmap(QPixmap(QString::fromUtf8(":/general/res_about.png")));
        picture->setScaledContents(true);
        credits = new QTextEdit(UiAbout);
        credits->setObjectName(QString::fromUtf8("credits"));
        credits->setGeometry(QRect(10, 155, 326, 336));
        credits->setFocusPolicy(Qt::NoFocus);
        credits->setReadOnly(true);
        credits->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        version = new QLabel(UiAbout);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(185, 125, 146, 26));
        version->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        header = new QTextEdit(UiAbout);
        header->setObjectName(QString::fromUtf8("header"));
        header->setGeometry(QRect(180, 20, 151, 86));
        header->setFocusPolicy(Qt::NoFocus);
        header->setReadOnly(true);
        header->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        QWidget::setTabOrder(header, credits);

        retranslateUi(UiAbout);

        QMetaObject::connectSlotsByName(UiAbout);
    } // setupUi

    void retranslateUi(QWidget *UiAbout)
    {
        UiAbout->setWindowTitle(QCoreApplication::translate("UiAbout", "About IanniX", nullptr));
        picture->setText(QString());
        credits->setHtml(QCoreApplication::translate("UiAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Museo Sans,Museo Sans 500,Arial'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">CURRENT TEAM</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Thierry Coduys (project manager)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Guillaume Jacqu"
                        "emin (software developer)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Mattieu Ranc (association management)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600; color:#ffffff;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">IDEATION</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Thierry Coduys</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-righ"
                        "t:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Adrien Lefevre</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Gerard Pape (CCMIX)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic; color:#ffffff;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">IANNIX DEVELOPERS </span><span style=\" font-size:12px; font-weight:600; font-style:italic; color:#ffffff;\">(FORMER VERSIONS)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text"
                        "-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Adrien Lefevre </span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\">(v0.54)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Guillaume Ferry </span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\">(v0.6xx)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Pierre Jullian de la Fuente &amp; Cyrill Duneau </span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\">(v0.6xx)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Matthieu Ranc &amp; Guillaume Ja"
                        "cquemin </span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\">(v0.66)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Guillaume Jacquemin </span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\">(v0.8, v0.9)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic; color:#ffffff;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">CONTRIBUTORS</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; "
                        "color:#ffffff;\">Christopher Graham</span><span style=\" font-size:12px; font-style:italic; color:#ffffff;\"><br /></span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">TESTERS &amp; EXTERNAL CONTRIBUTORS</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Jean Bresson (OpenMusic)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Paul Crabbe (SuperCollider)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\""
                        ">Francesco (C-Sound)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Cyrille Henry</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Thomas Thiery (PureData)</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Romain Vuillet</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Hannes Fritz </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0"
                        "; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">uml\303\244ute</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">VirtualTam</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Alexandros Drymonitis</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">IOhannes m zm\303\266lnig</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-style:italic; color:#ffffff;\"><br /></span></p>\n"
"<p align=\"center\" style=\" margin-t"
                        "op:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600; color:#ffffff;\">THANKS TO</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Etienne Math\303\251 (documentation), Joachim Montessuis, Manuel Deneu and all users for their observations and suggestions and AFIM (Association Fran\303\247aise d'Informatique Musicale).</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; color:#ffffff;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; color:#ffffff;\">Visit </span><a href=\"http://www.iannix.org\"><span style=\" fon"
                        "t-size:12px; text-decoration: underline; color:#ffffff;\">http://www.iannix.org</span></a><span style=\" font-size:12px; color:#ffffff;\"> for more information !</span></p></body></html>", nullptr));
        version->setText(QCoreApplication::translate("UiAbout", "version", nullptr));
        header->setHtml(QCoreApplication::translate("UiAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Museo Sans,Museo Sans 500,Arial'; font-size:12px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px; font-weight:600;\">PROJECT MANAGER</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px;\">Thierry Coduys</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        "><span style=\" font-size:12px; font-weight:600;\">DEVELOPPEMENT</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12px;\">Guillaume Jacquemin</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiAbout: public Ui_UiAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIABOUT_H
