#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class DoubleSpinBox;
class IntegerSpinBox;
class Slider;
class LongTextEdit;
class IntegerRangeSelector;
class DoubleRangeSelector;
class MainWindow;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QGroupBox;
class QLabel;

class QRadioButton;
class QVBoxLayout;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(MainWindow* mainWin, const char* title, bool auto_enabled=false);
    MainWindow* mainWindow;

    void setDialogLayout(QLayout* layout);

    static void setAutoUpdate(bool on);

    void autoHook(QComboBox*);
    void autoHook(QLineEdit*);
    void autoHook(DoubleSpinBox*);
    void autoHook(IntegerSpinBox*);
    void autoHook(QCheckBox*);
    void autoHook(QRadioButton*);
    void autoHook(Slider*);
    void autoHook(IntegerRangeSelector*);
    void autoHook(DoubleRangeSelector*);
    void autoHook(QGroupBox*);
    void autoHook(LongTextEdit*);

protected:
    QLabel* makeLabel(const char* text, Qt::Alignment align = Qt::AlignVCenter | Qt::AlignRight);
    QLabel* makeLabel(const char* text, QWidget* tipgiver, Qt::Alignment align = Qt::AlignVCenter | Qt::AlignRight);
    QPushButton* makeButton(const char* text, const char* slot);
    QGroupBox* makeGroupBox(const char* text, bool checkable=false);

    void setTip(QWidget*, const char* text);
    void setTip(QWidget*, QWidget*, const char* text);
    void setTip(QWidget*, QWidget*, QWidget*, const char* text);

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
