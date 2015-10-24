#ifndef REGRESSION_H
#define REGRESSION_H

#ifdef __cplusplus

#include "dialog.h"

#if QT_VERSION >= 0x040400
class QPlainTextEdit;
#else
class QTextEdit;
typedef QTextEdit QPlainTextEdit;
#endif

class TransformRegression : public Dialog
{
    Q_OBJECT
public:
    explicit TransformRegression(MainWindow* mainWin);

    static void stufftext(char* s);


private:
    QComboBox* setNumber;

    QComboBox* degree;
    QComboBox* load;

    QLabel* outputLabel;
    QLabel* loadLabel;
    QLabel* degreeLabel;

    QPlainTextEdit* output;

    static TransformRegression* me;

public slots:
    void updateDialog();
private slots:
    void applyDialog();
    
};

extern "C"
{
#endif // __cplusplus

void qt_stufftext(char* s);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // REGRESSION_H
