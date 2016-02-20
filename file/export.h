#ifndef SAVEAS_H
#define SAVEAS_H

#include <QFileDialog>

class QFrame;
class QSpinBox;
class QLabel;
class QGraphicsScene;
class MainWindow;

class FileExport : public QFileDialog
{
    Q_OBJECT
public:
    typedef enum {PNG, JPG, TIFF, BMP, SVG, PDF} ImageType;

    explicit FileExport(MainWindow *mwin);
    MainWindow* mainWindow;

    static void exportImage(ImageType t, QString target, QGraphicsScene* s, int width, int height);
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
