#ifndef EVALUATE_H
#define EVALUATE_H

#include <QtGui>
#include "dialog.h"

class TransformEvaluate : public Dialog
{
    Q_OBJECT
public:
    explicit TransformEvaluate(MainWindow* mainWin);
    
private:

    QComboBox* setNumber;
    QComboBox* destination;
    QLineEdit* formulaBox;


signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // EVALUATE_H
