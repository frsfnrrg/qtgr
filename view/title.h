#ifndef TITLE_H
#define TITLE_H

#include <QtGui>
#include "dialog.h"
#include "fontcombobox.h"

// TODO:
//
//  title ----------------------
//  size ## color XX font ======
// dual dialog sucks.
class ViewTitle : public Dialog
{
    Q_OBJECT
public:
    explicit ViewTitle(MainWindow* mainWin);

private:
    QLineEdit* stext;
    QDoubleSpinBox* ssize;
    FontComboBox* sfont;
    QComboBox* scolor;

    QLineEdit* ttext;
    QDoubleSpinBox* tsize;
    FontComboBox* tfont;
    QComboBox* tcolor;

signals:

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // TITLE_H
