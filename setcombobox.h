#ifndef SETCOMBOBOX_H
#define SETCOMBOBOX_H

#include <QtGui>


class LegendSender : public QObject
{
    Q_OBJECT
public:
    void sendUpdate();

signals:
    void updateLegends();

public slots:

};

class SetComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SetComboBox();

    static void sendUpdate();

signals:

public slots:
    void updateSetChooserLabels();

private:
    static LegendSender* legendSender;
};


#endif // SETCOMBOBOX_H
