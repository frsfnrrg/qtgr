#ifndef KAD_H
#define KAD_H

#include <QtGui>
#include "dialog.h"

class SetsKAD : public Dialog
{
    Q_OBJECT
public:
    explicit SetsKAD(MainWindow* mainWin);
private:
    QComboBox* setNumber;
    QRadioButton* adChoice;
    QRadioButton* killChoice;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // KAD_H
