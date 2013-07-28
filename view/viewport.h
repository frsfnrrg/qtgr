#ifndef VIEW_VIEW_H
#define VIEW_VIEW_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

/**
 * @brief The ViewView class
 *
 *
 */
class ViewView : public Dialog
{
    Q_OBJECT
public:
    explicit ViewView(MainWindow *parent);
    


private:
    QComboBox* snapSize;
    QDoubleSpinBox* xn;
    QDoubleSpinBox* xx;
    QDoubleSpinBox* yn;
    QDoubleSpinBox* yx;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
    
};

#endif // VIEW_VIEW_H