#include "overlay.h"
#include "mainwindow.h"
#include "util.h"

const int offset = 3;

Overlay::Overlay(QWidget* parent) :
    QWidget(parent)
{
    this->setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    rec = NULL;
    x = 0;
    y = 0;

    cancelRectSelect = createQAction(tr("Cancel rect select"),
                                     tr("Stop the process of choosing a rectangle"),
                                     "",
                                     this);
    connect(cancelRectSelect, SIGNAL(triggered()), this, SLOT(cancelRect()));
}

void Overlay::startRect(RectReceiver* r) {
    if (rec != NULL) {
        printf("Already processing a rectangle demand. Acquiescing, alas.");
    }
    this->rec = r;
    stage = 0;
    update();
}

void Overlay::updateMouse(int x, int y, int, int) {
    if (this->rec != NULL && (x != this->x || y != this->y)) {
        this->x = x;
        this->y = y;
        update();
    }
}

void Overlay::paintEvent(QPaintEvent*) {
    if (rec == NULL || stage != 1) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black));

    painter.drawLine(offset + x1, offset + y1, offset + x1,offset + y);
    painter.drawLine(offset + x1,offset +  y1,offset +  x,offset + y1);
    painter.drawLine(offset + x, offset + y1, offset + x, offset + y);
    painter.drawLine(offset + x1,offset +  y,offset +  x, offset + y);
}


void Overlay::clickMouse(int x, int y, int w, int h) {
    if (rec == NULL) return;

    stage++;
    if (stage == 1) {
        x1 = x;
        y1 = y;
    } else if (stage == 2) {
        x2 = x;
        y2 = y;

        double lx1, lx2, ly1, ly2;
        lx1 = double(x1) / w;
        lx2 = double(x2) / w;

        ly1 = 1.0 - double(y1) / h;
        ly2 = 1.0 - double(y2) / h;

        double tmp;
        if (lx1 > lx2) {
            tmp = lx2; lx2 = lx1; lx1 = tmp;
        }
        if (ly1 > ly2) {
            tmp = ly2; ly2 = ly1; ly1 = tmp;
        }

        rec->finishRect(lx1, lx2, ly1, ly2);
        rec = NULL;
    }
    update();
}

bool Overlay::isRectSelecting() {
    return rec != NULL;
}

void Overlay::cancelRect() {
    rec = NULL;
    update();
}
