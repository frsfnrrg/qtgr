#ifndef SETS_EDIT_H
#define SETS_EDIT_H

#include <QtGui>
#include "dialog.h"

class SetsEdit : public Dialog
{
    Q_OBJECT
public:
    explicit SetsEdit(MainWindow*);
private:

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // SETS_EDIT_H
