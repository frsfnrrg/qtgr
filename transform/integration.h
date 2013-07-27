#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class TransformIntegration : public Dialog
{
    Q_OBJECT
public:
    explicit TransformIntegration(MainWindow* mainWin);

private:
    QComboBox* integrationType;
    QLabel* result;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // INTEGRATION_H
