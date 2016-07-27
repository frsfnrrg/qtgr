#ifndef JOIN_H
#define JOIN_H

#include "dialog.h"

class SetsJoin : public Dialog
{
    Q_OBJECT
public:
    explicit SetsJoin(MainWindow* mainWin);
    
private:
    QComboBox* setLeft;
    QComboBox* setRight;
    QRadioButton* mergeLeft;
    QRadioButton* mergeRight;
signals:

public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // JOIN_H
