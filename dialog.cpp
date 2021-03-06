#include "dialog.h"
#include "base/globals.h"
#include "prop.h"
#include "choosers.h"
#include "mainwindow.h"
#include "util.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>

// nefarious idea: make dialog a "base" class,
// have three near equivalent subclasses:
// TransformDialog
// AutoUpdateDialog
// StandardDialog
// to reduce duplication etc.

bool Dialog::auto_update = false;

Dialog::Dialog(MainWindow* mainWin, const char* title, bool autoenabled) :
    QDialog(mainWin)
{
    this->setWindowTitle(tr(title));
    this->mainWindow = mainWin;
    layout = new QVBoxLayout();

    apply = new QPushButton(tr("Apply"));
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

    layout->addStretch(0);
    layout->addSpacing(12);
    layout->addLayout(base);

    this->setLayout(layout);

    autoen = autoenabled;
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
    layout->insertLayout(0, lt, 10);
}

void Dialog::doneDialog() {
    if (!autoen && !auto_update){
        applyDialog();
    }
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

void Dialog::setTip(QWidget* a, const char* text) {
    QString tip = tr(text);
    a->setStatusTip(tip);
    a->setToolTip(tip);
}

void Dialog::setTip(QWidget* a, QWidget* b, const char* text) {
    QString tip = tr(text);
    a->setStatusTip(tip);
    a->setToolTip(tip);
    b->setStatusTip(tip);
    b->setToolTip(tip);
}

void Dialog::setTip(QWidget* a, QWidget* b, QWidget* c, const char* text) {
    QString tip = tr(text);
    a->setStatusTip(tip);
    a->setToolTip(tip);
    b->setStatusTip(tip);
    b->setToolTip(tip);
    c->setStatusTip(tip);
    c->setToolTip(tip);
}

void Dialog::autoHook(QComboBox* q) {
    // this still sends when the value is the same, but that makes little
    // difference. The problem with value-changed is that it triggers
    // on programmatic setting. This is a ridiculously minor issue.
    connect(q, SIGNAL(activated(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QLineEdit* q) {
    connect(q, SIGNAL(textEdited(QString)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(DoubleSpinBox* q) {
    connect(q, SIGNAL(valueChanged(double)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(IntegerSpinBox* q) {
    connect(q, SIGNAL(valueChanged(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QCheckBox* q) {
    connect(q, SIGNAL(clicked()), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QRadioButton* q) {
    connect(q, SIGNAL(stateChanged(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(Slider* q) {
    connect(q, SIGNAL(valueChanged(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(IntegerRangeSelector* q) {
    connect(q, SIGNAL(userChangedValue(int)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(DoubleRangeSelector* q) {
    connect(q, SIGNAL(userChangedValue(double)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(QGroupBox* q) {
    connect(q, SIGNAL(clicked(bool)), this, SLOT(autoUpdate()));
}

void Dialog::autoHook(LongTextEdit* q) {
   connect(q, SIGNAL(textChanged()), this, SLOT(autoUpdate()));
}

QLabel* Dialog::makeLabel(const char* text, Qt::Alignment align) {
    return makeQLabel(this, text, align);
}

QLabel* Dialog::makeLabel(const char* text, QWidget* tipgiver, Qt::Alignment align) {
    QLabel* q = makeQLabel(this, text, align);
    q->setToolTip(tipgiver->toolTip());
    q->setStatusTip(tipgiver->statusTip());
    return q;
}

QGroupBox* Dialog::makeGroupBox(const char* text, bool checkable) {
    QGroupBox* q = makeQGroupBox(this, text);
    q->setCheckable(checkable);
    return q;
}

void Dialog::setAutoUpdate(bool on) {
    auto_update = on;
    AutoDisabler::send(on);
}

void Dialog::deactivate(bool block_apply) {
    apply->setDisabled(block_apply);
}
