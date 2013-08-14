#include "view/viewport.h"
#include "base/globals.h"

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
    Dialog(parent, "Viewport", true)
{
    useRect = new QPushButton(tr("Rect Select"));
    connect(useRect, SIGNAL(clicked()), this, SLOT(doRect()));

    QVBoxLayout* over = new QVBoxLayout();

    QGridLayout* layout = new QGridLayout();
    over->addLayout(layout);

    xn = getUnitDoubleSpinBox();
    xx = getUnitDoubleSpinBox();
    yn = getUnitDoubleSpinBox();
    yx = getUnitDoubleSpinBox();
    autoHook(xn);
    autoHook(xx);
    autoHook(yn);
    autoHook(yx);

    layout->addWidget(new QLabel(tr("Viewport settings (from 0.0 to 1.0)")), 0,0,2,0);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(new QLabel(tr("X min")), 2,0);
    layout->addWidget(xn, 2, 1);

    layout->addWidget(new QLabel(tr("X max")), 3,0);
    layout->addWidget(xx, 3, 1);

    layout->addWidget(new QLabel(tr("Y min")), 4,0);
    layout->addWidget(yn, 4, 1);

    layout->addWidget(new QLabel(tr("Y max")), 5,0);
    layout->addWidget(yx, 5, 1);

    over->addSpacing(8);
    over->addWidget(useRect);

    this->setDialogLayout(over);
}

void ViewView::updateDialog() {
    int gno = cg;

    double xnv = g[gno].v.xv1;
    double xxv = g[gno].v.xv2;

    double ynv = g[gno].v.yv1;
    double yxv = g[gno].v.yv2;

    printf("Viewport: %f %f %f %f\n",xnv,xxv,ynv,yxv);

    xn->setValue(xnv);
    xx->setValue(xxv);
    yn->setValue(ynv);
    yx->setValue(yxv);
}

void ViewView::applyDialog() {
    finishRect(xn->value(),xx->value(),yn->value(),yx->value());
}

void ViewView::doRect() {
    GraphWidget::startRect(this);
    this->setVisible(false);
}

void ViewView::finishRect(double x1, double x2, double y1, double y2) {
    printf("Viewport: %f %f %f %f\n",x1,x2,y1,y2);

    int gno = cg;
    g[gno].v.xv1 = x1;
    g[gno].v.xv2 = x2;
    g[gno].v.yv1 = y1;
    g[gno].v.yv2 = y2;

    drawgraph();
}
