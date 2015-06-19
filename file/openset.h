#ifndef OPENSET_H
#define OPENSET_H

#include <QFileDialog>

class QComboBox;
class QRadioButton;
class MainWindow;

class FileOpenSet : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileOpenSet(MainWindow *mwin);
    MainWindow* mainWindow;
    void setAdoptName(bool);

private:
    QComboBox* fileType;
    QComboBox* graphNum;
    QRadioButton* fromFile;
    QRadioButton* fromPipe;
    bool adoptingName;

public slots:
    void accept();
};

#endif // OPENSET_H
