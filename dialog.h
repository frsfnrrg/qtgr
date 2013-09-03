#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui>
#include "mainwindow.h"
#include "util.h"

class DoubleSpinBox;
class IntegerSpinBox;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(MainWindow* mainWin, const char* title, bool auto_enabled=false);
    MainWindow* mainWindow;

    void setDialogLayout(QLayout* layout);

    static void setAutoUpdate(bool on);
protected:
    QLabel* makeLabel(const char* text, Qt::Alignment align = Qt::AlignLeft | Qt::AlignVCenter);
    QPushButton* makeButton(const char* text, const char* slot);

    void autoHook(QComboBox*);
    void autoHook(QLineEdit*);
    void autoHook(DoubleSpinBox*);
    void autoHook(IntegerSpinBox*);
    void autoHook(QCheckBox*);
    void autoHook(QRadioButton*);
    void autoHook(QSlider*);

private:
    static bool auto_update;
    bool autoen;

    QVBoxLayout* layout;
signals:
    
public slots:
    virtual void updateDialog() = 0;
    virtual void applyDialog() = 0;

private slots:
    void autoUpdate();
    void doneDialog();
    void cancelDialog();
};

#endif // DIALOG_H
