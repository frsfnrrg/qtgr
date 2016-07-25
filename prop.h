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
    static void send(QObject* sender);

    static void add(QObject* reciever);

private:
    explicit WorldDimProp();
    static WorldDimProp* me;
    void prop(QObject* sender);

signals:
    void dimensionUpdate(QObject* sender);

public slots:
};


/*
 Requires an updateSets slot;
 To be used whenever a
 set is killed, added, or its
 legend is changed
 */
class SetsSender : public QObject
{
    Q_OBJECT
public:
    static void send();
    static void add(QObject* reciever);
    static void addViaDialog(QObject* reciever);

private:
    explicit SetsSender();
    static SetsSender* me;
    void prop();

signals:
    void setsUpdate();

public slots:

};

class AutoDisabler : public QObject
{
    Q_OBJECT
public:
    static void send(bool on);
    static void add(QWidget* reciever);

private:
    explicit AutoDisabler();
    static AutoDisabler* me;
    void prop(bool);

signals:
    void autoChangeDisable();
    void autoChangeEnable();

};

#endif // WORLDDIMPROP_H
