#ifndef SETCOMBOBOX_H
#define SETCOMBOBOX_H

#include <QtGui>

class SetComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SetComboBox(bool and_all_active = false);

signals:

public slots:
    void updateSets();

private:
    int add;
};


#endif // SETCOMBOBOX_H
