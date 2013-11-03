#ifndef STATUS_H
#define STATUS_H


#ifdef __cplusplus

#include "dialog.h"

class ToolsStatus : public Dialog
{
    Q_OBJECT
public:
    explicit ToolsStatus(MainWindow* mainWin);
    
    static void update_set_status(int graphno, int setno);

private:
    QTableWidget* output;

    static ToolsStatus* me;

public slots:
    void updateDialog();
    void updateSets();
private slots:
    void applyDialog();
    void copySelected();
};


extern "C"
{
#endif // __cplusplus

void qt_update_set_status(int graphno, int setno);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // STATUS_H
