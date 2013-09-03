#ifndef VIEW_VIEW_H
#define VIEW_VIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"
#include "overlay.h"

/**
 * @brief The ViewView class
 *
 *
 */
class ViewView : public Dialog, RectReceiver
{
    Q_OBJECT
public:
    explicit ViewView(MainWindow *parent);

    void finishRect(double x1, double x2, double y1, double y2);

private:
    DoubleSpinBox* xn;
    DoubleSpinBox* xx;
    DoubleSpinBox* yn;
    DoubleSpinBox* yx;
    QPushButton* useRect;
    void setMinMax();

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();

    void doRect();

    void xminu();
    void xmaxd();
    void yminu();
    void ymaxd();
};

#endif // VIEW_VIEW_H

