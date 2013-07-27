#include "view_view.h"

ViewView::ViewView(MainWindow *parent) :
    Dialog(parent, tr("Viewport"))
{
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel(tr("Viewport settings (from 0.0 to 1.0)")), 0,0,2,1);

    layout->addWidget(new QLabel(tr("X min")), 1,0);

    layout->addWidget(new QLabel(tr("X max")), 2,0);

    layout->addWidget(new QLabel(tr("Y min")), 3,0);

    layout->addWidget(new QLabel(tr("Y max")), 4,0);

    layout->addWidget(new QLabel(tr("Snap")), 5,0);


    this->setDialogLayout(layout);
}

void ViewView::applyDialog() {

}

void ViewView::updateDialog() {

}
