#include "prop.h"

WorldDimProp* WorldDimProp::me = NULL;

WorldDimProp::WorldDimProp() :
    QObject()
{
}

void WorldDimProp::send() {
    if (me == NULL) {
        me = new WorldDimProp();
    }
    me->prop();
}

void WorldDimProp::add(QObject* receiver) {
    if (me == NULL) {
        me = new WorldDimProp();
    }
    connect(me, SIGNAL(dimensionUpdate()), receiver, SLOT(updateWorldDimensions()));
}

void WorldDimProp::prop() {
    emit dimensionUpdate();
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
