#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtGui>
#include "dialog.h"

class ToolsOptions : public Dialog
{
    Q_OBJECT
public:
    explicit ToolsOptions(MainWindow* mainWin);

    bool isRescaleOnLoad();
    bool isRescaleOnTransform();
private:
    QSettings settings;
    QCheckBox* rescaleOnLoad;
    QCheckBox* rescaleOnTransform;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // OPTIONS_H
