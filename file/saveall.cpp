#include "file/saveall.h"

FileSaveAll::FileSaveAll(MainWindow *mwin) :
    QFileDialog(mwin, tr("Save all data"), QDir::currentPath(), "*")
{
    mainWindow = mwin;

    this->setOptions(QFileDialog::DontUseNativeDialog);
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setFileMode(QFileDialog::AnyFile);
}

void FileSaveAll::accept() {
    QFileDialog::accept();
    QStringList files = this->selectedFiles();
    if (files.size() == 0) return;
}
