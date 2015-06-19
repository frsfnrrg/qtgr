#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "dialog.h"
#include "overlay.h"

class ViewDimensions : public Dialog, RectReceiver
{
    Q_OBJECT
public:
    explicit ViewDimensions(MainWindow* mainWin);

    void finishRect(double x1, double x2, double y1, double y2);

private:
    DoubleSpinBox* viewXMin;
    DoubleSpinBox* viewXMax;
    DoubleSpinBox* viewYMin;
    DoubleSpinBox* viewYMax;

    QLineEdit* worldXMin;
    QLineEdit* worldXMax;
    QLineEdit* worldYMin;
    QLineEdit* worldYMax;

    QPushButton* viewSelect;
    QPushButton* rescaleAxes;
    QComboBox* worldType;

public slots:
    void updateDialog();
    void updateWorldDimensions(QObject*);

private slots:
    void applyDialog();

    void updateScale();
    void rescaleTicks();

    void viewRect();
    void readjXMin();
    void readjXMax();
    void readjYMin();
    void readjYMax();
};

#endif // DIMENSIONS_H
