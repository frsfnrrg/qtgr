#ifndef TRANSFORMFOURIER_H
#define TRANSFORMFOURIER_H

#include "dialog.h"

class TransformFourier : public Dialog
{
    Q_OBJECT
public:
    explicit TransformFourier(MainWindow* mainWin);

private:
    QComboBox* setNumber;
//    QComboBox* destination;
//    QLabel* destinationLabel;

    QLabel* windowLabel;
    QLabel* loadLabel;
    QLabel* loadXLabel;
    QLabel* dataTypeLabel;
    QLabel* operationLabel;

    QComboBox* windowType;
    QComboBox* loadType;
    QComboBox* loadX;
    QComboBox* dataType;
    QComboBox* operation;

public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // TRANSFORMFOURIER_H
