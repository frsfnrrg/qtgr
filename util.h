#ifndef UTIL_H
#define UTIL_H

#include <qnamespace.h>

class Dialog;
class MainWindow;

class QLabel;
class QWidget;
class QAction;
class QLineEdit;
class QGridLayout;
class QGroupBox;
class QComboBox;
class QPushButton;
class QCheckBox;
class QObject;

void loadDialog(Dialog*);
bool showDialog(Dialog*);

// T must be a subclass of Dialog
template<class T>
void launchOrRelaunch(Dialog** d, MainWindow* m) {
    if (showDialog(*d)) return;
    *d = new T(m);
    loadDialog(*d);
}

QLabel* makeQLabel(QWidget* parent, const char* text, Qt::Alignment align = Qt::AlignCenter);

QAction* createQAction(const QString &name, const QString &explained, const QString &shortcut, QObject* parent);

bool leVal(QLineEdit* l, double* d);

void addPair(QGridLayout* layout, int line, QWidget* f, QWidget* s);

QGroupBox* makeQGroupBox(QWidget* parent, const char* text);

QGridLayout* makeBoxLayout(QGroupBox* p);

QComboBox* makeQComboBox(QWidget* parent, const char* textarray[], int len);

QCheckBox* makeQCheckBox(QWidget* parent, const char* text);

void setButtonBold(QPushButton* button);

#endif // UTIL_H
