#include "util.h"
#include "dialog.h"

void loadDialog(Dialog* d) {
    d->show();
    d->raise();
    d->updateDialog();
}

bool showDialog(Dialog* d) {
    if (d) {
        d->setVisible(true);
        d->raise();
        d->updateDialog();
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
