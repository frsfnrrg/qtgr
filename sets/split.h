#ifndef SPLIT_H
#define SPLIT_H

#include "dialog.h"

class QTableWidget;
class IntegerSpinBox;
class QSlider;
class SetsSplit : public Dialog
{
    Q_OBJECT
public:
    explicit SetsSplit(MainWindow* mainWin);
    
private:
    QComboBox* setNumber;
    IntegerSpinBox* position;
    QTableWidget* preview;
    QSlider* slider;
signals:

public slots:
    void updateDialog();
private slots:
    void applyDialog();
    void spinChange();
    void slideChange();
private:
    void setupPreview();
};

#endif // SPLIT_H
