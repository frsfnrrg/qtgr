#include "tools/options.h"

ToolsOptions* ToolsOptions::me = NULL;
QSettings* ToolsOptions::settings = NULL;

ToolsOptions* ToolsOptions::getOptionsDialog(MainWindow* mainWin) {
    if (me == NULL) {
        me = new ToolsOptions(mainWin);
    }
    return me;
}

ToolsOptions::ToolsOptions(MainWindow* mwin) :
    Dialog(mwin, "Options")
{
    rescaleOnLoad = new QCheckBox();
    rescaleOnTransform = new QCheckBox();
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Autoscale on load")), 0,0);
    layout->addWidget(rescaleOnLoad, 0, 1);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("Autoscale on transforms")), 2,0);
    layout->addWidget(rescaleOnTransform, 2, 1);

    layout->setColumnMinimumWidth(1, 150);

    this->setDialogLayout(layout);

    if (settings == NULL) {
        settings = new QSettings("QTGR","QTGR");
    }
}

bool ToolsOptions::isRescaleOnLoad() {
    if (settings == NULL) {
        settings = new QSettings("QTGR","QTGR");
    }

    return settings->value("rescale_on_load", QVariant(true)).toBool();
}

bool ToolsOptions::isRescaleOnTransform() {
    return settings->value("rescale_on_transform", QVariant(false)).toBool();
}

void ToolsOptions::updateDialog() {
    rescaleOnLoad->setChecked(isRescaleOnLoad());
    rescaleOnTransform->setChecked(isRescaleOnTransform());
}

void ToolsOptions::applyDialog() {
    settings->setValue("rescale_on_load",
                      QVariant(rescaleOnLoad->isChecked()));
    settings->setValue("rescale_on_transform",
                      QVariant(rescaleOnTransform->isChecked()));
}
