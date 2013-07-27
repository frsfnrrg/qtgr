#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QtGui>
#include "mainwindow.h"
#include "dialog.h"

class TransformIntegration : public Dialog
{
    Q_OBJECT
public:
    const static int maxsets = 16;

    explicit TransformIntegration(MainWindow* mainWin);

private:
    QComboBox* setNumber;
    QComboBox* integrationType;
    QLabel* resultL;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // INTEGRATION_H