#include "tools/options.h"
#include "choosers.h"

ToolsOptions* ToolsOptions::me = NULL;
QSettings* ToolsOptions::settings = NULL;

ToolsOptions* ToolsOptions::getOptionsDialog(MainWindow* mainWin) {
    if (me == NULL) {
        me = new ToolsOptions(mainWin);
    }
    return me;
}

ToolsOptions::ToolsOptions(MainWindow* mwin) :
    Dialog(mwin, "Options", true)
{
    if (settings == NULL) {
        settings = new QSettings("QTGR","QTGR");
    }

    rescaleOnLoad = makeQCheckBox(this, "Autoscale on load");
    rescaleOnTransform = makeQCheckBox(this, "Autoscale on transforms");
    autoUpdate = makeQCheckBox(this, "Automatically apply updates");

    rescaleOnLoad->setChecked(isRescaleOnLoad());
    rescaleOnTransform->setChecked(isRescaleOnTransform());
    autoUpdate->setChecked(isAutoUpdate());

    autoHook(rescaleOnLoad);
    autoHook(rescaleOnTransform);
    autoHook(autoUpdate);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(rescaleOnLoad, 0, 0);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(rescaleOnTransform, 2, 0);

    layout->setRowMinimumHeight(3, 8);

    layout->addWidget(autoUpdate, 4, 0);

    this->setDialogLayout(layout);


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

bool ToolsOptions::isAutoUpdate() {
    return settings->value("auto_update", QVariant(true)).toBool();
}

void ToolsOptions::updateDialog() {
    rescaleOnLoad->setChecked(isRescaleOnLoad());
    rescaleOnTransform->setChecked(isRescaleOnTransform());
    autoUpdate->setChecked(isAutoUpdate());
}

void ToolsOptions::applyDialog() {
    settings->setValue("rescale_on_load",
                      QVariant(rescaleOnLoad->isChecked()));
    settings->setValue("rescale_on_transform",
                      QVariant(rescaleOnTransform->isChecked()));
    settings->setValue("auto_update",
                       QVariant(autoUpdate->isChecked()));
    Dialog::setAutoUpdate(autoUpdate->isChecked());
}
