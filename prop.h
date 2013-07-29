#ifndef PROP_H
#define PROP_H

/*
 The purpose of this file is to host all n:m propagation
 classes, for when multiple locations change the same thing.

 */


#include <QObject>

/*
  Requires an updateWorldDimensions(); slot
 */
class WorldDimProp : public QObject
{
    Q_OBJECT
public:
    static void send();

    static void add(QObject* reciever);

private:
    explicit WorldDimProp();
    static WorldDimProp* me;
    void prop();

signals:
    void dimensionUpdate();

public slots:
};

#endif // WORLDDIMPROP_H
