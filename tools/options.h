#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtGui>
#include "dialog.h"

class ToolsOptions : public Dialog
{
    Q_OBJECT
public:
    static ToolsOptions* getOptionsDialog(MainWindow*);

    static bool isRescaleOnLoad();
    static bool isRescaleOnTransform();
    static bool isAutoUpdate();
private:
    static ToolsOptions* me;
    static QSettings* settings;

    explicit ToolsOptions(MainWindow* mainWin);
    QCheckBox* rescaleOnLoad;
    QCheckBox* rescaleOnTransform;
    QCheckBox* autoUpdate;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // OPTIONS_H
