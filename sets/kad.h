#ifndef KAD_H
#define KAD_H

#include "dialog.h"

class SetsKAD : public Dialog
{
    Q_OBJECT
public:
    explicit SetsKAD(MainWindow* mainWin);
private:
    QComboBox* setNumber;
    QRadioButton* actChoice;
    QRadioButton* deactChoice;
    QRadioButton* killChoice;

signals:
    
public slots:
    void updateSets();
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // KAD_H
