#include "tools/options.h"

/*
 Best would be to make this subclass QDialog,
 and automatically register its changes. _Apply_ is
 a slow way of doing things.
 */
ToolsOptions::ToolsOptions(MainWindow* mwin) :
    Dialog(mwin, "Options"),
    settings("QTGR", "QTGR")
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
}

bool ToolsOptions::isRescaleOnLoad() {
    return settings.value("rescale_on_load", QVariant(true)).toBool();
}

bool ToolsOptions::isRescaleOnTransform() {
    return settings.value("rescale_on_transform", QVariant(false)).toBool();
}

void ToolsOptions::updateDialog() {
    rescaleOnLoad->setChecked(isRescaleOnLoad());
    rescaleOnTransform->setChecked(isRescaleOnTransform());
}

void ToolsOptions::applyDialog() {
    settings.setValue("rescale_on_load",
                      QVariant(rescaleOnLoad->isChecked()));
    settings.setValue("rescale_on_transform",
                      QVariant(rescaleOnTransform->isChecked()));
}
