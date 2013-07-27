#include "dialog.h"

Dialog::Dialog(MainWindow* mainWin) :
    QDialog(mainWin)
{
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

    layout->addWidget(new QLabel("Replace Me!"));
    layout->addStretch();
    layout->addLayout(base);

    QDialog::setLayout(layout);
}

void Dialog::setLayout(QLayout* lt) {
    layout->insertLayout(1, lt);
}

void Dialog::doneDialog() {
    applyDialog();
    this->setVisible(false);
}

void Dialog::cancelDialog() {
    this->setVisible(false);
}
