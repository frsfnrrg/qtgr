#ifndef MCS_H
#define MCS_H

#include "dialog.h"

class SetsMCS : public Dialog
{
    Q_OBJECT
public:
    explicit SetsMCS(MainWindow* mainWin);
    
private:
    QComboBox* setNumber;
    QComboBox* targetNumber;
    QLabel* targetNumberLabel;
    QRadioButton* moveChoice;
    QRadioButton* copyChoice;
    QRadioButton* swapChoice;

signals:

public slots:
    void updateDialog();
private slots:
    void applyDialog();
};

#endif // MCS_H
