#include "util.h"
#include "dialog.h"

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
