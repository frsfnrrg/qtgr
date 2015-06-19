#ifndef SETS_EDIT_H
#define SETS_EDIT_H

#include "dialog.h"

class SetsEdit : public Dialog
{
    Q_OBJECT
public:
    explicit SetsEdit(MainWindow*);
private:
    QComboBox* setNumber;

signals:
    
public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // SETS_EDIT_H
