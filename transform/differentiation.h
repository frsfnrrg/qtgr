#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include "dialog.h"

class TransformDifferentiation : public Dialog
{
    Q_OBJECT
public:
    explicit TransformDifferentiation(MainWindow* mainWin);
    
private:
    QComboBox* setNumber;
    QComboBox* destination;
    QComboBox* diffType;
    QLabel* diffTypeLabel;
    QLabel* destinationLabel;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // DIFFERENTIATION_H
