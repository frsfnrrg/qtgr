#ifndef EVALUATE_H
#define EVALUATE_H

#include "dialog.h"

class TransformEvaluate : public Dialog
{
    Q_OBJECT
public:
    explicit TransformEvaluate(MainWindow* mainWin);

private:
    QComboBox* setNumber;
    QComboBox* destination;
    QLabel* formulaBoxLabel;
    QLabel* destinationLabel;
    QLineEdit* formulaBox;

public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // EVALUATE_H
