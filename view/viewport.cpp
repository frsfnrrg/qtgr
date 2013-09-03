#include "view/viewport.h"
#include "base/globals.h"
#include "choosers.h"

DoubleSpinBox* getUnitDoubleSpinBox() {
    DoubleSpinBox* f = new DoubleSpinBox();
    f->setMaximum(1.0);
    f->setMinimum(0.0);
    f->setDecimals(3);
    f->setSingleStep(0.05);
    f->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
    return f;
}

ViewView::ViewView(MainWindow *parent) :
    Dialog(parent, "Viewport", true)
{
    useRect = new QPushButton(tr("Rect Select"));
    useRect->setMinimumWidth(150);
    useRect->setStyleSheet("QPushButton { font-weight: bold }");
    connect(useRect, SIGNAL(clicked()), this, SLOT(doRect()));

    xn = getUnitDoubleSpinBox();
    xx = getUnitDoubleSpinBox();
    yn = getUnitDoubleSpinBox();
    yx = getUnitDoubleSpinBox();
    connect(xn, SIGNAL(valueChanged(double)), this, SLOT(xmaxd()));
    connect(xx, SIGNAL(valueChanged(double)), this, SLOT(xminu()));
    connect(yn, SIGNAL(valueChanged(double)), this, SLOT(ymaxd()));
    connect(yx, SIGNAL(valueChanged(double)), this, SLOT(yminu()));
    autoHook(xn);
    autoHook(xx);
    autoHook(yn);
    autoHook(yx);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(makeLabel("Viewport coordinates"), 0,0,2,0, Qt::AlignCenter);

    layout->setRowMinimumHeight(1, 8);

    layout->addWidget(makeLabel("X min:"), 2,0);
    layout->addWidget(xn, 2, 1);

    layout->addWidget(makeLabel("X max"), 3,0);
    layout->addWidget(xx, 3, 1);

    layout->addWidget(makeLabel("Y min"), 4,0);
    layout->addWidget(yn, 4, 1);

    layout->addWidget(makeLabel("Y max"), 5,0);
    layout->addWidget(yx, 5, 1);

    layout->setRowMinimumHeight(6, 8);
    layout->addWidget(useRect, 7, 0, 1, 2, Qt::AlignCenter);

    this->setDialogLayout(layout);
}

void ViewView::updateDialog() {
    int gno = cg;

    double xnv = g[gno].v.xv1;
    double xxv = g[gno].v.xv2;

    double ynv = g[gno].v.yv1;
    double yxv = g[gno].v.yv2;

    xn->setValue(xnv);
    xx->setValue(xxv);
    yn->setValue(ynv);
    yx->setValue(yxv);
    setMinMax();
}

void ViewView::applyDialog() {
    finishRect(xn->value(),xx->value(),yn->value(),yx->value());
}

void ViewView::doRect() {
    GraphWidget::startRect(this);
    this->setVisible(false);
}

void ViewView::finishRect(double x1, double x2, double y1, double y2) {
    int gno = cg;
    g[gno].v.xv1 = x1;
    g[gno].v.xv2 = x2;
    g[gno].v.yv1 = y1;
    g[gno].v.yv2 = y2;

    drawgraph();
}

void ViewView::setMinMax() {
    xn->setMaximum(xx->value());
    xx->setMinimum(xn->value());
    yn->setMaximum(yx->value());
    yx->setMinimum(yn->value());
}

void ViewView::xminu() {
    xn->setMaximum(xx->value());
}

void ViewView::xmaxd() {
    xx->setMinimum(xn->value());
}

void ViewView::yminu() {
    yn->setMaximum(yx->value());
}

void ViewView::ymaxd() {
    yx->setMinimum(yn->value());
}
