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
    QDoubleSpinBox* xn;
    QDoubleSpinBox* xx;
    QDoubleSpinBox* yn;
    QDoubleSpinBox* yx;
    QPushButton* useRect;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();

    void doRect();
    
};

#endif // VIEW_VIEW_H
