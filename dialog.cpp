#include "dialog.h"

Dialog::Dialog(MainWindow* mainWin, QString title) :
    QDialog(mainWin)
{
    this->setWindowTitle("QTGR: " + title);
    this->mainWindow = mainWin;
    layout = new QVBoxLayout();

    QPushButton* apply = new QPushButton(tr("Apply"));
    connect(apply, SIGNAL(clicked()), this, SLOT(applyDialog()));

    QPushButton* done = new QPushButton(tr("Done"));
    connect(done, SIGNAL(clicked()), this, SLOT(doneDialog()));

    QPushButton* cancel = new QPushButton(tr("Cancel"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelDialog()));

    QHBoxLayout* base = new QHBoxLayout();
    base->addWidget(cancel);
    base->addStretch();
    base->addWidget(apply);
    base->addWidget(done);

    layout->addStretch();
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
