#ifndef SAVEAS_H
#define SAVEAS_H

#include <QFileDialog>

class QFrame;
class QSpinBox;
class QLabel;
class MainWindow;

class FileExport : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileExport(MainWindow *mwin);
    MainWindow* mainWindow;

private:
    QFrame* options;
    QSpinBox* heightBox;
    QSpinBox* widthBox;
    QLabel* heightBoxLabel;
    QLabel* widthBoxLabel;
public slots:
    void accept();

private slots:
    void updateHeightBox(int);
    void updateWidthBox(int);
    void updateBoxes(QString);
};

#endif // SAVEAS_H
