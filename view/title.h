#ifndef TITLE_H
#define TITLE_H

#include <QtGui>
#include "dialog.h"

class ViewTitle : public Dialog
{
    Q_OBJECT
public:
    explicit ViewTitle(MainWindow* mainWin);

private:
    QLineEdit* titleField;
    QLineEdit* subtitleField;
    QPushButton* propertiesButton;

    Dialog* propertiesDialog;

signals:

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void properties();
};

class ViewTitleProperties : public Dialog {

Q_OBJECT
public:
    explicit ViewTitleProperties(MainWindow* mw);

private:
    QDoubleSpinBox* ssize;
    QComboBox* sfont;
    QComboBox* scolor;

    QDoubleSpinBox* tsize;
    QComboBox* tfont;
    QComboBox* tcolor;

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};


#endif // TITLE_H
