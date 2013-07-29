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

