#ifndef UTIL_H
#define UTIL_H

#include <QtGui>

class Dialog;

void loadDialog(Dialog*);

bool showDialog(Dialog*);

const Qt::Alignment ALIGN_FORM_LABEL = Qt::AlignVCenter | Qt::AlignRight;

QLabel* makeQLabel(QWidget* parent, const char* text, Qt::Alignment align = Qt::AlignCenter);

QAction* createQAction(const QString &name, const QString &explained, const QString &shortcut, QObject* parent);

bool leVal(QLineEdit* l, double* d);

void addPair(QGridLayout* layout, int line, QWidget* f, QWidget* s);


#endif // UTIL_H
