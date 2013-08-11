#ifndef UTIL_H
#define UTIL_H

#include <QtGui>
#include "dialog.h"

class Dialog;

// todo: move to a seperate file
void loadDialog(Dialog*);

bool showDialog(Dialog*);

QLabel* makeQLabel(QWidget* parent, const char* text, Qt::Alignment align = Qt::AlignCenter);

QAction* createQAction(const QString &name, const QString &explained, const QString &shortcut, QObject* parent);

#endif // UTIL_H