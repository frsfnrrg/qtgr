#include "dialog.h"
#include "base/globals.h"
#include "prop.h"

bool Dialog::auto_update = false;

// todo: hide/disable all cancel/apply buttons

Dialog::Dialog(MainWindow* mainWin, const char* title, bool autoen) :
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

    if (autoen) {
        AutoDisabler::add(apply);
        AutoDisabler::add(cancel);
        if (auto_update) {
            apply->hide();
            cancel->hide();
        }
    }
}

QPushButton* Dialog::makeButton(const char* text, const char* slot) {
    QPushButton* f = new QPushButton(tr(text));
    connect(f, SIGNAL(clicked()), this, slot);
    return f;
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

void Dialog::autoUpdate() {
    if (auto_update) {
        applyDialog();
    }
}

void Dialog::autoHook(QComboBox* q) {
    connect(q, SIGNAL(currentIndexChanged(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QLineEdit* q) {
    connect(q, SIGNAL(editingFinished()), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QAbstractSpinBox* q) {
    connect(q, SIGNAL(editingFinished()), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QCheckBox* q) {
    connect(q, SIGNAL(toggled(bool)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QRadioButton* q) {
    connect(q, SIGNAL(toggled(bool)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QSlider* q) {
    connect(q, SIGNAL(valueChanged(int)), this, SLOT(autoUpdate()));
}

QLabel* Dialog::makeLabel(const char* text, Qt::Alignment align) {
    return makeQLabel(this, text, align);
}

void Dialog::setAutoUpdate(bool on) {
    auto_update = on;
    AutoDisabler::send(on);
}
