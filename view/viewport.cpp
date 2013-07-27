#include "view/viewport.h"

const double snap_sizes[] = {0.0, 0.1, 0.05, 0.01, 0.05, 0.001};

inline QDoubleSpinBox* getUnitDoubleSpinBox() {
    QDoubleSpinBox* f = new QDoubleSpinBox();
    f->setMaximum(1.0);
    f->setMinimum(0.0);
    f->setDecimals(3);
    f->setSingleStep(0.05);
    return f;
}

ViewView::ViewView(MainWindow *parent) :
    Dialog(parent, tr("Viewport"))
{
    snapSize = new QComboBox();
    snapSize->addItem(tr("None"));
    for (int i=1;i<6;i++) {
        snapSize->addItem(QString::number(snap_sizes[i]));
    }

    QGridLayout* layout = new QGridLayout();

    xn = getUnitDoubleSpinBox();
    xx = getUnitDoubleSpinBox();
    yn = getUnitDoubleSpinBox();
    yx = getUnitDoubleSpinBox();

    layout->addWidget(new QLabel(tr("Viewport settings (from 0.0 to 1.0)")), 0,0,2,0);

    layout->addWidget(new QLabel(""), 1, 0);

    layout->addWidget(new QLabel(tr("X min")), 2,0);
    layout->addWidget(xn, 2, 1);

    layout->addWidget(new QLabel(tr("X max")), 3,0);
    layout->addWidget(xx, 3, 1);

    layout->addWidget(new QLabel(tr("Y min")), 4,0);
    layout->addWidget(yn, 4, 1);

    layout->addWidget(new QLabel(tr("Y max")), 5,0);
    layout->addWidget(yx, 5, 1);

    layout->addWidget(new QLabel(tr("Snap")), 6,0);
    layout->addWidget(snapSize, 6, 1);

    this->setDialogLayout(layout);
}

void ViewView::applyDialog() {

}

void ViewView::updateDialog() {

}
