#ifndef FRAME_H
#define FRAME_H

#include <QtGui>
#include "dialog.h"

class ViewFrame : public Dialog
{
    Q_OBJECT
public:
    explicit ViewFrame(MainWindow* mainWin);

private:
    QComboBox* graphType;
    QComboBox* lineColor;
    QComboBox* lineWidth;
    QComboBox* lineStyle;
    QCheckBox* fillBG;
    QComboBox* fillColor;
    
signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
    void setFillOpt(int);
    
};

#endif // FRAME_H
