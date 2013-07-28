#ifndef VIEW_GRAPHTYPE_H
#define VIEW_GRAPHTYPE_H

#include <QtGui>
#include "dialog.h"

class ViewGraphType : public Dialog
{
    Q_OBJECT
public:
    explicit ViewGraphType(MainWindow* mainWin);
private:
    QComboBox* setNumbers;
    QComboBox* graphTypes;

signals:
    
public slots:
    void updateDialog();

private slots:
    void applyDialog();
};

#endif // VIEW_GRAPHTYPE_H
