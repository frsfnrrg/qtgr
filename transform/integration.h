#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "dialog.h"

class TransformIntegration : public Dialog
{
    Q_OBJECT
public:
    explicit TransformIntegration(MainWindow* mainWin);

private:
    QComboBox* setNumber;
    QComboBox* integrationType;
    QLabel* resultL;
    QLabel* resultLabel;
    QLabel* typeLabel;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // INTEGRATION_H
