#include "view/viewport.h"
#include "core/globals.h"

const double snap_sizes[] = {0.1, 0.05, 0.01, 0.005, 0.001};

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

    this->setDialogLayout(layout);
}

void ViewView::updateDialog() {
    int gno = cg;

    double xnv = g[gno].v.xv1;
    double xxv = g[gno].v.xv2;

    double ynv = g[gno].v.yv1;
    double yxv = g[gno].v.yv2;

    printf("Viewport: %f %f %f %f\n",xnv,xxv,ynv,yxv);

    xn->setValue(xnv);
    yn->setValue(ynv);
    xx->setValue(xxv);
    yx->setValue(yxv);
}

void ViewView::applyDialog() {
    // settings are applied to current graph
    int gno = cg;

    g[gno].v.xv1 = xn->value();
    g[gno].v.xv2 = xx->value();
    g[gno].v.yv1 = yn->value();
    g[gno].v.yv2 = yx->value();

    drawgraph();
}
