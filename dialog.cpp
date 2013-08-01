#include "dialog.h"
#include "base/globals.h"

Dialog::Dialog(MainWindow* mainWin, const char* title) :
    QDialog(mainWin)
{
    this->setWindowTitle(tr(title));
    this->mainWindow = mainWin;
    layout = new QVBoxLayout();

    QPushButton* apply = new QPushButton(tr("Apply"));
    apply->setToolTip(tr("Apply dialog values."));
    connect(apply, SIGNAL(clicked()), this, SLOT(applyDialog()));

    QPushButton* done = new QPushButton(tr("Done"));
    done->setToolTip(tr("Apply values and close dialog."));
    done->setDefault(true);
    connect(done, SIGNAL(clicked()), this, SLOT(doneDialog()));

    QPushButton* cancel = new QPushButton(tr("Cancel"));
    cancel->setToolTip(tr("Close dialog, without applying values."));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelDialog()));

    QHBoxLayout* base = new QHBoxLayout();
    base->addWidget(cancel);
    base->addStretch();
    base->addWidget(apply);
    base->addWidget(done);

    layout->addStretch();
    layout->addSpacing(12);
    layout->addLayout(base);

    this->setLayout(layout);
}

/**
 * Please don't call this more than once;
 * @brief Dialog::setDialogLayout
 * @param lt
 */
void Dialog::setDialogLayout(QLayout* lt) {
    layout->insertLayout(0, lt);
}

void Dialog::doneDialog() {
    applyDialog();
    this->setVisible(false);
}

void Dialog::cancelDialog() {
    this->setVisible(false);
}
