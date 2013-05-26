#include "message.h"
#include "objects/nxtrigger.h"
#include "objects/nxcursor.h"
#include "objects/nxcurve.h"

Message::Message() {
    type = MessagesTypeDirect;
    hasAdd = false;
    messageScriptEngine = 0;
    isTransportMessage = false;
}

void Message::setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine, const QHash<QString,UiString> &aliases) {
    messageScriptEngine = _messageScriptEngine;
    messageScriptValue = messageScriptEngine->globalObject();
    hasAdd = false;
    urlMessage = url;

    QString scheme = urlMessage.scheme().toLower();

    if(aliases.contains(urlMessage.host().toLower()))
        urlMessage.setHost(qPrintable(aliases.value(urlMessage.host().toLower()).val().replace(" ", "_").replace("/", "_").toLower().trimmed()));
    urlMessageString = qPrintable(urlMessage.toString());
    address.clear();
    typetag.clear();
    arguments.clear();
    asciiMessage.clear();

    if(scheme == "osc") {
        type = MessagesTypeOsc;
        host = urlMessage.host().toLower();
        port = urlMessage.port();
        address += urlMessage.path();
        address += (char)0;
        pad(address);
        typetag += ',';
    }
    else if(scheme == "http") {
        type = MessagesTypeHttp;
    }
    else if(scheme == "tcp") {
        type = MessagesTypeTcp;
        address += urlMessage.authority() + urlMessage.path();
    }
    else if(scheme == "udp") {
        type = MessagesTypeUdp;
        host = urlMessage.host();
        port = urlMessage.port();
    }
    else if(scheme == "serial") {
        type = MessagesTypeSerial;
    }
    else if(scheme == "direct") {
        type = MessagesTypeDirect;
    }
    else if(scheme == "midi") {
        type = MessagesTypeMidi;
        midiPort = urlMessage.host().toLower();
        midiCommand = urlMessage.path().toLower();
    }
}


bool Message::parse(const QVector<QByteArray> & patternItems, const MessageManagerDestination &destination) {
    bool suppressSend = false;
    midiValues   .clear();
    asciiMessage .clear();
    verboseValues.clear();
    verboseValues.reserve(patternItems.count());
    buffer       .clear();
    hasAdd = false;

    if(patternItems.count() >= 2) {
        //Messages
        for(quint16 patternIndex = 1 ; patternIndex < patternItems.count() ; patternIndex++) {
            QByteArray patternArgument = patternItems.at(patternIndex);
            bool found = false;

            if((patternArgument.at(0) == '{') && (messageScriptEngine)) {
                patternArgument = patternArgument.trimmed().remove(0, 1);
                patternArgument.chop(1);

                if(((NxTrigger*)destination.trigger)) {
                    if(patternArgument.contains("trigger_id"))
                        messageScriptValue.setProperty("trigger_id", ((NxTrigger*)destination.trigger)->getId());
                    if(patternArgument.contains("trigger_group_id"))
                        messageScriptValue.setProperty("trigger_group_id", ((NxTrigger*)destination.trigger)->getGroupId());
                    if(patternArgument.contains("trigger_label"))
                        messageScriptValue.setProperty("trigger_label", ((NxTrigger*)destination.trigger)->getLabel());
                    if(patternArgument.contains("trigger_xPos"))
                        messageScriptValue.setProperty("trigger_xPos", ((NxTrigger*)destination.trigger)->getPos().x());
                    if(patternArgument.contains("trigger_yPos"))
                        messageScriptValue.setProperty("trigger_yPos", ((NxTrigger*)destination.trigger)->getPos().y());
                    if(patternArgument.contains("trigger_zPos"))
                        messageScriptValue.setProperty("trigger_zPos", ((NxTrigger*)destination.trigger)->getPos().z());
                    if((patternArgument.contains("trigger_value_x")) && (((NxCursor*)destination.cursor)))
                        messageScriptValue.setProperty("trigger_value_x", ((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).x());
                    if((patternArgument.contains("trigger_value_y")) && (((NxCursor*)destination.cursor)))
                        messageScriptValue.setProperty("trigger_value_y", ((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).y());
                    if((patternArgument.contains("trigger_value_z")) && (((NxCursor*)destination.cursor)))
                        messageScriptValue.setProperty("trigger_value_z", ((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).z());
                    if(patternArgument.contains("trigger_value"))
                        messageScriptValue.setProperty("trigger_value", ((NxTrigger*)destination.trigger)->getTrigged());
                    if((patternArgument.contains("trigger_distance")) && (((NxCursor*)destination.cursor))) {
                        NxPoint cursorPosDelta = ((NxTrigger*)destination.trigger)->getPos() - ((NxCursor*)destination.cursor)->getCurrentPos();
                        messageScriptValue.setProperty("trigger_distance", qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()));
                    }
                    if((patternArgument.contains("trigger_side")) && (((NxCursor*)destination.cursor))) {
                        qreal cursorAngle = fmod(((NxCursor*)destination.cursor)->getCurrentAngle().z(), 360);
                        float side = 0;
                        if(cursorAngle == 90) //cursor going straight up
                            side = (((NxTrigger*)destination.trigger)->getPos().x() > ((NxCursor*)destination.cursor)->getCurrentPos().x()) ? 1:0;
                        else if (cursorAngle == 270) //cursor going straight down
                            side = (((NxTrigger*)destination.trigger)->getPos().x() > ((NxCursor*)destination.cursor)->getCurrentPos().x()) ? 0:1;
                        else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                            side = (((NxTrigger*)destination.trigger)->getPos().y() > ((NxCursor*)destination.cursor)->getCurrentPos().y()) ? 1:0;
                        else //cursor going to right
                            side = (((NxTrigger*)destination.trigger)->getPos().y() > ((NxCursor*)destination.cursor)->getCurrentPos().y()) ? 0:1;
                        messageScriptValue.setProperty("trigger_side", side);
                    }
                    if(patternArgument.contains("trigger_message_id"))
                        messageScriptValue.setProperty("trigger_message_id", (quint32)((NxTrigger*)destination.trigger)->getMessageId());
                }
                if(((NxCursor*)destination.cursor)) {
                    if(patternArgument.contains("cursor_id"))
                        messageScriptValue.setProperty("cursor_id", ((NxCursor*)destination.cursor)->getId());
                    if(patternArgument.contains("cursor_group_id"))
                        messageScriptValue.setProperty("cursor_group_id", ((NxCursor*)destination.cursor)->getGroupId());
                    if(patternArgument.contains("cursor_label"))
                        messageScriptValue.setProperty("cursor_label", ((NxCursor*)destination.cursor)->getLabel());

                    if(patternArgument.contains("cursor_xPos"))
                        messageScriptValue.setProperty("cursor_xPos", ((NxCursor*)destination.cursor)->getCurrentPos().x());
                    if(patternArgument.contains("cursor_yPos"))
                        messageScriptValue.setProperty("cursor_yPos", ((NxCursor*)destination.cursor)->getCurrentPos().y());
                    if(patternArgument.contains("cursor_zPos"))
                        messageScriptValue.setProperty("cursor_zPos", ((NxCursor*)destination.cursor)->getCurrentPos().z());
                    if(patternArgument.contains("cursor_sxPos"))
                        messageScriptValue.setProperty("cursor_sxPos", ((NxCursor*)destination.cursor)->getCurrentPos().sx());
                    if(patternArgument.contains("cursor_syPos"))
                        messageScriptValue.setProperty("cursor_syPos", ((NxCursor*)destination.cursor)->getCurrentPos().sy());
                    if(patternArgument.contains("cursor_szPos"))
                        messageScriptValue.setProperty("cursor_szPos", ((NxCursor*)destination.cursor)->getCurrentPos().sz());
                    if(patternArgument.contains("cursor_value_x"))
                        messageScriptValue.setProperty("cursor_value_x", ((NxCursor*)destination.cursor)->getCurrentValue().x());
                    if(patternArgument.contains("cursor_value_y"))
                        messageScriptValue.setProperty("cursor_value_y", ((NxCursor*)destination.cursor)->getCurrentValue().y());
                    if(patternArgument.contains("cursor_value_z"))
                        messageScriptValue.setProperty("cursor_value_z", ((NxCursor*)destination.cursor)->getCurrentValue().z());
                    if(patternArgument.contains("cursor_value_sx"))
                        messageScriptValue.setProperty("cursor_value_sx", ((NxCursor*)destination.cursor)->getCurrentValue().sx());
                    if(patternArgument.contains("cursor_value_sy"))
                        messageScriptValue.setProperty("cursor_value_sy", ((NxCursor*)destination.cursor)->getCurrentValue().sy());
                    if(patternArgument.contains("cursor_value_sz"))
                        messageScriptValue.setProperty("cursor_value_sz", ((NxCursor*)destination.cursor)->getCurrentValue().sz());
                    if(patternArgument.contains("cursor_time"))
                        messageScriptValue.setProperty("cursor_time", ((NxCursor*)destination.cursor)->getTimeLocal());
                    if(patternArgument.contains("cursor_time_percent"))
                        messageScriptValue.setProperty("cursor_time_percent", ((NxCursor*)destination.cursor)->getTimeLocalPercent());
                    if(patternArgument.contains("cursor_angle"))
                        messageScriptValue.setProperty("cursor_angle", fmod(((NxCursor*)destination.cursor)->getCurrentAngle().z(), 360));

                    if(patternArgument.contains("cursor_xPos_delta"))
                        messageScriptValue.setProperty("cursor_xPos_delta",     ((NxCursor*)destination.cursor)->getCurrentPos().x()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().x());
                    if(patternArgument.contains("cursor_yPos_delta"))
                        messageScriptValue.setProperty("cursor_yPos_delta",     ((NxCursor*)destination.cursor)->getCurrentPos().y()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().y());
                    if(patternArgument.contains("cursor_zPos_delta"))
                        messageScriptValue.setProperty("cursor_zPos_delta",     ((NxCursor*)destination.cursor)->getCurrentPos().z()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().z());
                    if(patternArgument.contains("cursor_sxPos_delta"))
                        messageScriptValue.setProperty("cursor_sxPos_delta",    ((NxCursor*)destination.cursor)->getCurrentPos().sx()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sx());
                    if(patternArgument.contains("cursor_syPos_delta"))
                        messageScriptValue.setProperty("cursor_syPos_delta",    ((NxCursor*)destination.cursor)->getCurrentPos().sy()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sy());
                    if(patternArgument.contains("cursor_szPos_delta"))
                        messageScriptValue.setProperty("cursor_szPos_delta",    ((NxCursor*)destination.cursor)->getCurrentPos().sz()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sz());
                    if(patternArgument.contains("cursor_value_x_delta"))
                        messageScriptValue.setProperty("cursor_value_x_delta",  ((NxCursor*)destination.cursor)->getCurrentValue().x()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().x());
                    if(patternArgument.contains("cursor_value_y_delta"))
                        messageScriptValue.setProperty("cursor_value_y_delta",  ((NxCursor*)destination.cursor)->getCurrentValue().y()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().y());
                    if(patternArgument.contains("cursor_value_z_delta"))
                        messageScriptValue.setProperty("cursor_value_z_delta",  ((NxCursor*)destination.cursor)->getCurrentValue().z()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().z());
                    if(patternArgument.contains("cursor_value_sx_delta"))
                        messageScriptValue.setProperty("cursor_value_sx_delta", ((NxCursor*)destination.cursor)->getCurrentValue().sx() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sx());
                    if(patternArgument.contains("cursor_value_sy_delta"))
                        messageScriptValue.setProperty("cursor_value_sy_delta", ((NxCursor*)destination.cursor)->getCurrentValue().sy() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sy());
                    if(patternArgument.contains("cursor_value_sz_delta"))
                        messageScriptValue.setProperty("cursor_value_sz_delta", ((NxCursor*)destination.cursor)->getCurrentValue().sz() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sz());
                    if(patternArgument.contains("cursor_time_delta"))
                        messageScriptValue.setProperty("cursor_time_delta",         ((NxCursor*)destination.cursor)->getTimeLocal()        - ((NxCursor*)destination.cursor)->getTimeLocalLastSend());
                    if(patternArgument.contains("cursor_time_percent_delta"))
                        messageScriptValue.setProperty("cursor_time_percent_delta", ((NxCursor*)destination.cursor)->getTimeLocalPercent() - ((NxCursor*)destination.cursor)->getTimeLocalPercentLastSend());
                    if(patternArgument.contains("cursor_angle_delta"))
                        messageScriptValue.setProperty("cursor_angle_delta",        ((NxCursor*)destination.cursor)->getCurrentAngle().z() - ((NxCursor*)destination.cursor)->getCurrentAngleLastSend().z());

                    if(patternArgument.contains("cursor_nb_loop"))
                        messageScriptValue.setProperty("cursor_nb_loop", ((NxCursor*)destination.cursor)->getNbLoop());
                    if(patternArgument.contains("cursor_message_id"))
                        messageScriptValue.setProperty("cursor_message_id", (quint32)((NxCursor*)destination.cursor)->getMessageId());
                }
                if(((NxCurve*)destination.curve)) {
                    if(patternArgument.contains("curve_id"))
                        messageScriptValue.setProperty("curve_id", ((NxCurve*)destination.curve)->getId());
                    if(patternArgument.contains("curve_group_id"))
                        messageScriptValue.setProperty("curve_group_id", ((NxCurve*)destination.curve)->getGroupId());
                    if(patternArgument.contains("curve_label"))
                        messageScriptValue.setProperty("curve_label", ((NxCurve*)destination.curve)->getLabel());
                    if(patternArgument.contains("curve_xPos"))
                        messageScriptValue.setProperty("curve_xPos", ((NxCurve*)destination.curve)->getPos().x());
                    if(patternArgument.contains("curve_yPos"))
                        messageScriptValue.setProperty("curve_yPos", ((NxCurve*)destination.curve)->getPos().y());
                    if(patternArgument.contains("curve_zPos"))
                        messageScriptValue.setProperty("curve_zPos", ((NxCurve*)destination.curve)->getPos().z());
                }
                if(((NxCurve*)destination.collisionCurve)) {
                    if(patternArgument.contains("collision_curve_id"))
                        messageScriptValue.setProperty("collision_curve_id", ((NxCurve*)destination.collisionCurve)->getId());
                    if(patternArgument.contains("collision_curve_group_id"))
                        messageScriptValue.setProperty("collision_curve_group_id", ((NxCurve*)destination.collisionCurve)->getGroupId());
                    if(patternArgument.contains("collision_curve_label"))
                        messageScriptValue.setProperty("collision_curve_label", ((NxCurve*)destination.collisionCurve)->getLabel());
                    if(patternArgument.contains("collision_curve_xPos"))
                        messageScriptValue.setProperty("collision_curve_xPos", ((NxCurve*)destination.collisionCurve)->getPos().x());
                    if(patternArgument.contains("collision_curve_yPos"))
                        messageScriptValue.setProperty("collision_curve_yPos", ((NxCurve*)destination.collisionCurve)->getPos().y());
                    if(patternArgument.contains("collision_curve_zPos"))
                        messageScriptValue.setProperty("collision_curve_zPos", ((NxCurve*)destination.collisionCurve)->getPos().z());
                    if(patternArgument.contains("collision_xPos"))
                        messageScriptValue.setProperty("collision_xPos", destination.collisionPoint.x());
                    if(patternArgument.contains("collision_yPos"))
                        messageScriptValue.setProperty("collision_yPos", destination.collisionPoint.y());
                    if(patternArgument.contains("collision_value_x"))
                        messageScriptValue.setProperty("collision_value_x", destination.collisionValue.x());
                    if(patternArgument.contains("collision_value_y"))
                        messageScriptValue.setProperty("collision_value_y", destination.collisionValue.y());
                    if((patternArgument.contains("collision_distance")) && (((NxCursor*)destination.cursor))) {
                        NxPoint cursorPosDelta = (((NxCursor*)destination.cursor))?(destination.collisionPoint - ((NxCursor*)destination.cursor)->getCurrentPos()):(NxPoint());
                        messageScriptValue.setProperty("collision_distance", qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()));
                    }
                }
                {
                    if(patternArgument.contains("status")) {
                        messageScriptValue.setProperty("status", destination.status.status);
                        isTransportMessage = true;
                    }
                    if(patternArgument.contains("nb_triggers"))
                        messageScriptValue.setProperty("nb_triggers", destination.status.nbTriggers);
                    if(patternArgument.contains("nb_cursors"))
                        messageScriptValue.setProperty("nb_cursors", destination.status.nbCursors);
                    if(patternArgument.contains("nb_curves"))
                        messageScriptValue.setProperty("nb_curves", destination.status.nbCurves);
                    if(patternArgument.contains("global_time"))
                        messageScriptValue.setProperty("global_time", Transport::timeLocal);
                    if(patternArgument.contains("global_time_verbose"))
                        messageScriptValue.setProperty("global_time_verbose", Transport::getTimeLocalStr());
                }

                messageScriptResult = messageScriptEngine->evaluate(patternArgument);
                if(messageScriptResult.isError())
                    addString("**error**", patternArgument, patternIndex);
                else if(messageScriptResult.isString()) {
                    if(messageScriptResult.toString() == "suppress")
                        suppressSend = true;
                    else
                        found = addString(messageScriptResult.toString(), QString("script %1").arg(patternIndex), patternIndex);
                }
                else
                    found = addFloat(messageScriptResult.toNumber(), QString("script %1").arg(patternIndex), patternIndex);


            }
            else {
                if(((NxTrigger*)destination.trigger)) {
                    if(patternArgument == "trigger_id")
                        found = addFloat(((NxTrigger*)destination.trigger)->getId(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_group_id")
                        found = addString(((NxTrigger*)destination.trigger)->getGroupId(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_label")
                        found = addString(((NxTrigger*)destination.trigger)->getLabel(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_xPos")
                        found = addFloat(((NxTrigger*)destination.trigger)->getPos().x(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_yPos")
                        found = addFloat(((NxTrigger*)destination.trigger)->getPos().y(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_zPos")
                        found = addFloat(((NxTrigger*)destination.trigger)->getPos().z(), patternArgument, patternIndex);
                    else if((patternArgument == "trigger_value_x") && (((NxCursor*)destination.cursor)))
                        found = addFloat(((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).x(), patternArgument, patternIndex);
                    else if((patternArgument == "trigger_value_y") && (((NxCursor*)destination.cursor)))
                        found = addFloat(((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).y(), patternArgument, patternIndex);
                    else if((patternArgument == "trigger_value_z") && (((NxCursor*)destination.cursor)))
                        found = addFloat(((NxCursor*)destination.cursor)->getCursorValue(((NxTrigger*)destination.trigger)->getPos()).z(), patternArgument, patternIndex);
                    else if(patternArgument == "trigger_value")
                        found = addFloat(((NxTrigger*)destination.trigger)->getTrigged(), patternArgument, patternIndex);
                    else if((patternArgument == "trigger_distance") && (((NxCursor*)destination.cursor))) {
                        NxPoint cursorPosDelta = ((NxTrigger*)destination.trigger)->getPos() - ((NxCursor*)destination.cursor)->getCurrentPos();
                        found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                    }
                    else if(patternArgument == "trigger_message_id")
                        found = addFloat(((NxTrigger*)destination.trigger)->getMessageId(), patternArgument, patternIndex);
                    else if((patternArgument == "trigger_side") && (((NxCursor*)destination.cursor))) {
                        qreal cursorAngle = fmod(((NxCursor*)destination.cursor)->getCurrentAngle().z(), 360);
                        float side = 0;
                        if(cursorAngle == 90 ) //cursor going straight up
                            side = (((NxTrigger*)destination.trigger)->getPos().x() > ((NxCursor*)destination.cursor)->getCurrentPos().x()) ? 1:0;
                        else if (cursorAngle == 270) //cursor going straight down
                            side = (((NxTrigger*)destination.trigger)->getPos().x() > ((NxCursor*)destination.cursor)->getCurrentPos().x()) ? 0:1;
                        else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                            side = (((NxTrigger*)destination.trigger)->getPos().y() > ((NxCursor*)destination.cursor)->getCurrentPos().y()) ? 1:0;
                        else //cursor going to right
                            side = (((NxTrigger*)destination.trigger)->getPos().y() > ((NxCursor*)destination.cursor)->getCurrentPos().y()) ? 0:1;
                        found = addFloat(side, patternArgument, patternIndex);
                    }
                }
                if(((NxCursor*)destination.cursor)) {
                    if(patternArgument == "cursor_id")
                        found = addFloat(((NxCursor*)destination.cursor)->getId(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_group_id")
                        found = addString(((NxCursor*)destination.cursor)->getGroupId(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_label")
                        found = addString(((NxCursor*)destination.cursor)->getLabel(), patternArgument, patternIndex);

                    else if(patternArgument == "cursor_xPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().x(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_yPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().y(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_zPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().z(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_sxPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sx(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_syPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sy(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_szPos")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sz(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_x")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().x(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_y")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().y(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_z")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().z(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sx")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sx(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sy")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sy(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sz")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sz(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_time")
                        found = addFloat(((NxCursor*)destination.cursor)->getTimeLocal(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_time_percent")
                        found = addFloat(((NxCursor*)destination.cursor)->getTimeLocalPercent(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_angle")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentAngle().z(), patternArgument, patternIndex);

                    else if(patternArgument == "cursor_xPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().x()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().x(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_yPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().y()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().y(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_zPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().z()    - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().z(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_sxPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sx()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sx(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_syPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sy()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sy(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_szPos_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentPos().sz()   - ((NxCursor*)destination.cursor)->getCurrentPosLastSend().sz(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_x_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().x()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().x(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_y_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().y()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().y(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_z_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().z()  - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().z(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sx_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sx() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sx(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sy_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sy() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sy(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_value_sz_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentValue().sz() - ((NxCursor*)destination.cursor)->getCurrentValueLastSend().sz(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_time_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getTimeLocal()         - ((NxCursor*)destination.cursor)->getTimeLocalLastSend(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_time_percent_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getTimeLocalPercent()  - ((NxCursor*)destination.cursor)->getTimeLocalPercentLastSend(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_angle_delta")
                        found = addFloat(((NxCursor*)destination.cursor)->getCurrentAngle().z()  - ((NxCursor*)destination.cursor)->getCurrentAngleLastSend().z(), patternArgument, patternIndex);

                    else if(patternArgument == "cursor_nb_loop")
                        found = addFloat(((NxCursor*)destination.cursor)->getNbLoop(), patternArgument, patternIndex);
                    else if(patternArgument == "cursor_message_id")
                        found = addFloat(((NxCursor*)destination.cursor)->getMessageId(), patternArgument, patternIndex);
                }
                if(((NxCurve*)destination.curve)) {
                    if(patternArgument == "curve_id")
                        found = addFloat(((NxCurve*)destination.curve)->getId(), patternArgument, patternIndex);
                    else if(patternArgument == "curve_group_id")
                        found = addString(((NxCurve*)destination.curve)->getGroupId(), patternArgument, patternIndex);
                    else if(patternArgument == "curve_label")
                        found = addString(((NxCurve*)destination.curve)->getLabel(), patternArgument, patternIndex);
                    else if(patternArgument == "curve_xPos")
                        found = addFloat(((NxCurve*)destination.curve)->getPos().x(), patternArgument, patternIndex);
                    else if(patternArgument == "curve_yPos")
                        found = addFloat(((NxCurve*)destination.curve)->getPos().y(), patternArgument, patternIndex);
                    else if(patternArgument == "curve_zPos")
                        found = addFloat(((NxCurve*)destination.curve)->getPos().z(), patternArgument, patternIndex);
                }
                if(((NxCurve*)destination.collisionCurve)) {
                    if(patternArgument == "collision_curve_id")
                        found = addFloat(((NxCurve*)destination.collisionCurve)->getId(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_curve_group_id")
                        found = addString(((NxCurve*)destination.collisionCurve)->getGroupId(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_curve_label")
                        found = addString(((NxCurve*)destination.collisionCurve)->getLabel(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_curve_xPos")
                        found = addFloat(((NxCurve*)destination.collisionCurve)->getPos().x(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_curve_yPos")
                        found = addFloat(((NxCurve*)destination.collisionCurve)->getPos().y(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_curve_zPos")
                        found = addFloat(((NxCurve*)destination.collisionCurve)->getPos().z(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_xPos")
                        found = addFloat(destination.collisionPoint.x(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_yPos")
                        found = addFloat(destination.collisionPoint.y(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_value_x")
                        found = addFloat(destination.collisionValue.x(), patternArgument, patternIndex);
                    else if(patternArgument == "collision_value_y")
                        found = addFloat(destination.collisionValue.y(), patternArgument, patternIndex);
                    else if((patternArgument == "collision_distance") && (((NxCursor*)destination.cursor))) {
                        NxPoint cursorPosDelta = destination.collisionPoint - ((NxCursor*)destination.cursor)->getCurrentPos();
                        found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                    }
                }
                {
                    if(patternArgument == "timetag")
                        found = addTimeTag(generateTimeTag(), patternArgument, patternIndex);
                    else if(patternArgument == "status") {
                        found = addString(destination.status.status, patternArgument, patternIndex);
                        isTransportMessage = true;
                    }
                    else if(patternArgument == "nb_triggers")
                        found = addFloat(destination.status.nbTriggers, patternArgument, patternIndex);
                    else if(patternArgument == "nb_cursors")
                        found = addFloat(destination.status.nbCursors, patternArgument, patternIndex);
                    else if(patternArgument == "nb_curves")
                        found = addFloat(destination.status.nbCurves, patternArgument, patternIndex);
                    else if(patternArgument == "global_time")
                        found = addFloat(Transport::timeLocal, patternArgument, patternIndex);
                    else if(patternArgument == "global_time_verbose")
                        found = addString(Transport::getTimeLocalStr(), patternArgument, patternIndex);
                }
            }

            if(!found) {
                if(patternArgument.startsWith("collision_"))
                    suppressSend = true;
                else if(Help::keywords.contains(patternArgument))
                    addFloat(-1, patternArgument, patternIndex);
                else {
                    //If value is not a keyword, add raw value
                    bool ok = false;
                    qreal val = patternArgument.toDouble(&ok);
                    if(ok)
                        found = addFloat(val, QString("custom %1").arg(patternIndex), patternIndex);
                    else
                        found = addString(patternArgument, QString("custom %1").arg(patternIndex), patternIndex);
                }
            }
        }


        if(type == MessagesTypeOsc) {
            buffer += address;
            buffer += typetag;
            buffer += (char)0;
            pad(buffer);
            buffer += arguments;
        }
        else if((type == MessagesTypeTcp) || (type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
            asciiMessage = asciiMessage.trimmed();
        }
    }

    return (hasAdd && !suppressSend);
}

const QByteArray Message::getVerboseMessage(bool) const {
    if(type == MessagesTypeHttp)
        return qPrintable(urlMessage.toString());
    else {
        QByteArray retour = urlMessageString;
        foreach(const QVariant &verboseValue, verboseValues)
            retour += "\t" + verboseValue.toByteArray();
        return retour;
    }
}


qint64 Message::generateTimeTag() const {
    const qint64 january_1_1900 = -2208988800000ll;
    qint64 ntpMSecs = QDateTime::currentMSecsSinceEpoch() - january_1_1900;
    union { quint32 i[2]; qint64 t; } u;
    u.i[1] = ntpMSecs / 1000;
    u.i[0] = 0x100000000ll * (ntpMSecs % 1000) / 1000;
    return u.t;
}
/*
void Message::addInt(int i, const char *name, quint16) {
        union { int i; char ch[4]; } u;
        u.i = i;
        arguments += u.ch[3];
        arguments += u.ch[2];
        arguments += u.ch[1];
        arguments += u.ch[0];
        typetag += 'i';
}
*/
bool Message::addString(QString str, const QString & name, quint16) {
    str = str.replace("_", " ");
    verboseValues << str;
    hasAdd = true;
    if(type == MessagesTypeOsc) {
        arguments += str;
        arguments += (char)0;
        pad(arguments);
        typetag += 's';
        return true;
    }
    else if(type == MessagesTypeHttp) {
#ifdef QT4
        urlMessage.addQueryItem(name, str);
        return true;
#else
        return false;
#endif
    }
    else if(type == MessagesTypeTcp) {
        asciiMessage = asciiMessage + qPrintable("<ARGUMENT TYPE=\"s\" VALUE=\"" + str + "\"/>");
        return true;
    }
    else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
        asciiMessage = asciiMessage + " " + qPrintable(str);
        return true;
    }
    return true;
}
bool Message::addFloat(float f, const QString & name, quint16) {
    verboseValues << f;
    hasAdd = true;
    if(type == MessagesTypeOsc) {
        union { float f; char ch[4]; } u;
        u.f = f;
        arguments += u.ch[3];
        arguments += u.ch[2];
        arguments += u.ch[1];
        arguments += u.ch[0];
        typetag += 'f';
        return true;
    }
    else if(type == MessagesTypeHttp) {
#ifdef QT4
        urlMessage.addQueryItem(name, QString::number(f));
        return true;
#else
        return false;
#endif
    }
    else if(type == MessagesTypeTcp) {
        asciiMessage = asciiMessage + qPrintable("<ARGUMENT TYPE=\"f\" VALUE=\"" + QString::number(f) + "\"/>");
        return true;
    }
    else if(type == MessagesTypeMidi) {
        midiValues.append(f);
        return true;
    }
    else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
        asciiMessage = asciiMessage + " " + QByteArray::number(f);
        return true;
    }
    return true;
}
bool Message::addTimeTag(qint64 t, const QString & name, quint16) {
    verboseValues << t;
    hasAdd = true;
    if(type == MessagesTypeOsc) {
        union { qint64 t; char ch[8]; } u;
        u.t = t;
        arguments += u.ch[7];
        arguments += u.ch[6];
        arguments += u.ch[5];
        arguments += u.ch[4];
        arguments += u.ch[3];
        arguments += u.ch[2];
        arguments += u.ch[1];
        arguments += u.ch[0];
        typetag += 't';
        return true;
    }
    else if(type == MessagesTypeHttp) {
#ifdef QT4
        urlMessage.addQueryItem(name, QString::number(t));
        return true;
#else
        return false;
#endif
    }
    else if(type == MessagesTypeTcp) {
        asciiMessage = asciiMessage + qPrintable("<ARGUMENT TYPE=\"t\" VALUE=\"" + QString::number(t) + "\"/>");
        return true;
    }
    else if(type == MessagesTypeMidi) {
        return true;
    }
    else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
        asciiMessage = asciiMessage + " " + QByteArray::number(t);
        return true;
    }
    return true;
}
