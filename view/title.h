#ifndef TITLE_H
#define TITLE_H

#include "dialog.h"

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
    DoubleSpinBox* ssize;
    QComboBox* sfont;
    QComboBox* scolor;

    QLineEdit* ttext;
    DoubleSpinBox* tsize;
    QComboBox* tfont;
    QComboBox* tcolor;

signals:

public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // TITLE_H
