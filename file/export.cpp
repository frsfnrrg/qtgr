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
    connect(widthBox, SIGNAL(valueChanged(int)), this, SLOT(updateHeightBox(int)));

    heightBox = new QSpinBox();
    heightBox->setMinimum(1);
    heightBox->setMaximum(24000);
    heightBox->setValue(1800);
    heightBox->setSingleStep(150);
    connect(heightBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidthBox(int)));

    widthBoxLabel = makeQLabel(this, "Width");
    heightBoxLabel = makeQLabel(this, "Height");

#if QT_VERSION >= 0x040300
        connect(this,SIGNAL(filterSelected(QString)),
                this,SLOT(updateBoxes(QString)));
#endif

    options = new QFrame();

    QLayout* orig = this->layout();
    QGridLayout* layout = qobject_cast<QGridLayout*>(orig);

    if (!layout) return;

    layout->addWidget(widthBoxLabel, 4, 0);
    layout->addWidget(widthBox, 4, 1);
    layout->addWidget(heightBoxLabel, 5, 0);
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
    QImage image(width, height, QImage::Format_RGB32);
    if (image.isNull()) {
        qDebug("Could not create image. Are the dimensions off?");
        return;
    }
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();
    image.save(target);
}

void save_pdf(QGraphicsScene* scene, QString target) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(target);
    printer.setFullPage(true);
    printer.setColorMode(QPrinter::Color);
#if QT_VERSION >= 0x040400
    printer.setPaperSize(QSize(100, 75), QPrinter::Millimeter);
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

    ImageType types[] = {
        PNG,
        JPG,
        JPG,
        TIFF,
        BMP,
        SVG,
        PDF
    };
    exportImage(types[index], target, this->mainWindow->gwidget->scene(), width, height);
}

void FileExport::exportImage(FileExport::ImageType t, QString target, QGraphicsScene* scene, int width, int height) {
    switch (t) {
    case PNG:
    case JPG:
    case TIFF:
    case BMP:
        save_pixel(scene, target, width, height);
        break;
    case SVG:
        save_svg(scene, target, width, height);
        break;
    case PDF:
        save_pdf(scene, target);
        break;
    default:
        //printf("Save type not implemented yet\n");
        return;
    }
}

void FileExport::updateHeightBox(int val) {
    heightBox->blockSignals(true);
    heightBox->setValue((val * 3) / 4);
    heightBox->blockSignals(false);
}

void FileExport::updateWidthBox(int val) {
    widthBox->blockSignals(true);
    widthBox->setValue((val * 4) / 3);
    widthBox->blockSignals(false);
}

void FileExport::updateBoxes(QString s) {
    // Values restricted to those provided in FILE_TYPES
    bool ispdf = s.endsWith(".pdf");
    heightBox->setEnabled(!ispdf);
    widthBox->setEnabled(!ispdf);
    heightBoxLabel->setEnabled(!ispdf);
    widthBoxLabel->setEnabled(!ispdf);
}
