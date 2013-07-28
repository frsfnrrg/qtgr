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

    QDialog* propertiesDialog;

signals:

public slots:
    void updateDialog();

private slots:
    void applyDialog();

    void properties();
    void updateProperties();
    void applyProperties();
    void doneProperties();
};

#endif // TITLE_H
