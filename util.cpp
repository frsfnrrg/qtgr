#include "util.h"
#include "dialog.h"

#include <QLabel>
#include <QAction>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>

void loadDialog(Dialog* d) {
    d->updateDialog();
    d->show();
    d->raise();
}

bool showDialog(Dialog* d) {
    if (d) {
        d->updateDialog();
        d->setVisible(true);
        d->raise();
        return true;
    } else {
        return false;
    }
}

QLabel* makeQLabel(QWidget* parent, const char* text, Qt::Alignment align) {
    QLabel* q = new QLabel(parent->tr(text));
    q->setAlignment(align);
    return q;
}

QAction* createQAction(const QString &name, const QString &explained, const QString &shortcut, QObject* parent)
{
   QAction* f = new QAction(name, parent);
   f->setToolTip(explained);
   f->setStatusTip(explained);
   f->setWhatsThis(explained);
   f->setShortcut(QKeySequence(shortcut));
   f->setShortcutContext(Qt::ApplicationShortcut);
   return f;
}

bool leVal(QLineEdit* l, double* d) {
    bool ok;
    double v = l->text().toDouble(&ok);
    if (ok) *d = v;
    return ok;
}

void addPair(QGridLayout* layout, int line, QWidget* f, QWidget* s) {
    layout->addWidget(f, line, 0);
    layout->addWidget(s, line, 1);
}

QGroupBox* makeQGroupBox(QWidget* parent, const char* text) {
    QGroupBox* q = new QGroupBox(parent->tr(text), parent);
    q->setFlat(false);
    q->setStyleSheet("");
    return q;
}

QGridLayout* makeBoxLayout(QGroupBox* p) {
    QGridLayout* f = new QGridLayout();
    f->setColumnStretch(0, 1);
    f->setColumnStretch(1, 3);
    p->setLayout(f);
    return f;
}

QComboBox* makeQComboBox(QWidget* parent, const char* textarray[], int len) {
    QComboBox* q = new QComboBox();
    for (int i=0;i<len;i++) {
        q->addItem(parent->tr(textarray[i]));
    }
    return q;
}

QCheckBox* makeQCheckBox(QWidget* parent, const char* text) {
    QCheckBox* q = new QCheckBox(parent->tr(text));
    q->setLayoutDirection(Qt::RightToLeft);
    return q;
}

void setButtonBold(QPushButton* button) {
    button->setStyleSheet("QPushButton { font-weight: bold }");
}
