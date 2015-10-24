#include "file/export.h"
#include "util.h"
#include "mainwindow.h"
#include "graphwidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrinter>
#else
#include <QPrinter>
#endif
#if QT_VERSION >= 0x040300
#include <QSvgGenerator>
#endif

const int FILE_TYPES = 6;
QString filetype[FILE_TYPES] = {
    "*.png",
    "*.jpg",
    "*.tiff",
    "*.bmp",
    "*.svg",
    "*.pdf",
};

const int MATCH_TYPES = 7;
QString matchtype[MATCH_TYPES] = {
    ".png",
    ".jpg",
    ".jpeg",
    ".tiff",
    ".bmp",
    ".svg",
    ".pdf"
};

FileExport::FileExport(MainWindow *mwin) :
    QFileDialog(mwin, tr("Export"), QDir::currentPath())
{
    mainWindow = mwin;

#if QT_VERSION >= 0x040500
    this->setOptions(QFileDialog::DontUseNativeDialog);
#endif
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setFileMode(QFileDialog::AnyFile);
    this->setModal(true);

    QStringList filters;
    for (int i=0;i<FILE_TYPES;i++) {
        filters.append(filetype[i]);
    }
#if QT_VERSION >= 0x040400
    this->setNameFilters(filters);
#else
    this->setFilters(filters);
#endif

    widthBox = new QSpinBox();
    // use a sizepolicy
    widthBox->setMinimum(1);
    widthBox->setMaximum(32000);
    widthBox->setValue(2400);
    widthBox->setSingleStep(200);

    heightBox = new QSpinBox();
    heightBox->setMinimum(1);
    heightBox->setMaximum(24000);
    heightBox->setValue(1800);
    heightBox->setSingleStep(200);

    options = new QFrame();

    QLayout* orig = this->layout();
    QGridLayout* layout = qobject_cast<QGridLayout*>(orig);

    if (!layout) return;

    layout->addWidget(makeQLabel(this, "Width"), 4, 0);
    layout->addWidget(widthBox, 4, 1);
    layout->addWidget(makeQLabel(this, "Height"), 5, 0);
    layout->addWidget(heightBox, 5, 1);

    this->setLayout(layout);
}

void save_svg(QGraphicsScene* scene, QString target, int width, int height) {
#if QT_VERSION >= 0x040300
    QSvgGenerator gen;
    gen.setFileName(target);
    gen.setSize(QSize(width, height));
    gen.setViewBox(QRect(0,0,width, height));
    QPainter painter(&gen);
    scene->render(&painter);
    painter.end();
#endif
}

void save_pixel(QGraphicsScene* scene, QString target, int width, int height) {
    QPixmap image(width, height);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();
    image.save(target);
}

void save_pdf(QGraphicsScene* scene, QString target, int width, int height) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(target);
    printer.setFullPage(true);
    printer.setColorMode(QPrinter::Color);
#if QT_VERSION >= 0x040400
    printer.setPaperSize(QSize(width, height), QPrinter::Point);
#else
    printer.setPageSize(QPrinter::A5);
    printer.setOrientation(QPrinter::Landscape);
#endif

    QPainter painter(&printer);
    scene->render(&painter);
    painter.end();
}

void FileExport::accept() {
    // There are two sources for accept(); a buttonbox, and the filechooser
    // frame. We do not want to accept on frame click. Keypresses take buttons
    if (sender()->inherits("QFrame")) {
        return;
    }
    QFileDialog::accept();
    mainWindow->setLastDirectory(directory());

    QStringList targets = this->selectedFiles();
    if (targets.size() == 0) return;

    int width = widthBox->value();
    int height = heightBox->value();
    QString target = targets.at(0);

#if QT_VERSION >= 0x040400
    QString type = this->selectedNameFilter();
#else
    QString type = this->selectedFilter();
#endif

    int index = -1;
    for (int i=0;i<MATCH_TYPES;i++) {
        QString ending = matchtype[i];
        if (target.endsWith(ending, Qt::CaseInsensitive)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        for (int i=0;i<MATCH_TYPES;i++) {
            QString ending = matchtype[i];
            if (type.endsWith(ending, Qt::CaseInsensitive)) {
                index = i;
                target += ending;
                break;
            }
        }
    }
    //printf("type found: %i\n", index);

    QGraphicsScene* scene = this->mainWindow->gwidget->scene();

    switch (index) {

    case 0:// png
    case 1:// jpg
    case 2:// jpeg
    case 3:// tiff
    case 4:// bmp
        save_pixel(scene, target, width, height);
        break;
    case 5:// svg
        save_svg(scene, target,width, height);
        break;
    case 6:// pdf
        save_pdf(scene, target, width, height);
        break;
    default:
        //printf("Save type not implemented yet\n");
        return;
    }
}

