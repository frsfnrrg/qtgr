#include "prop.h"

WorldDimProp* WorldDimProp::me = NULL;

WorldDimProp::WorldDimProp() :
    QObject()
{
}

void WorldDimProp::send(QObject* sender) {
    if (me == NULL) {
        me = new WorldDimProp();
    }
    me->prop(sender);
}

void WorldDimProp::add(QObject* receiver) {
    if (me == NULL) {
        me = new WorldDimProp();
    }
    connect(me, SIGNAL(dimensionUpdate(QObject*)), receiver, SLOT(updateWorldDimensions(QObject*)));
}

void WorldDimProp::prop(QObject* sender) {
    emit dimensionUpdate(sender);
}



SetsSender* SetsSender::me = NULL;

SetsSender::SetsSender() :
    QObject()
{
}

void SetsSender::send() {
    if (me == NULL) {
        me = new SetsSender();
    }
    me->prop();
}

void SetsSender::add(QObject* receiver) {
    if (me == NULL) {
        me = new SetsSender();
    }
    connect(me, SIGNAL(setsUpdate()), receiver, SLOT(updateSets()));
}

void SetsSender::prop() {
    emit setsUpdate();
}

AutoDisabler* AutoDisabler::me = NULL;

AutoDisabler::AutoDisabler() :
    QObject()
{
}

void AutoDisabler::send(bool e) {
    if (me == NULL) {
        me = new AutoDisabler();
    }
    me->prop(e);
}

void AutoDisabler::add(QWidget* receiver) {
    if (me == NULL) {
        me = new AutoDisabler();
    }
    connect((QObject*)me, SIGNAL(autoChangeDisable()), (QObject*)receiver, SLOT(hide()));
    connect((QObject*)me, SIGNAL(autoChangeEnable()), (QObject*)receiver, SLOT(show()));
}

void AutoDisabler::prop(bool on) {
    if (on) {
        emit autoChangeDisable();
    } else {
        emit autoChangeEnable();
    }
}
