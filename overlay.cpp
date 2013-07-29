#include "overlay.h"

void RectReceiver::finishRect(double x1, double x2, double y1, double y2) {

}

Overlay::Overlay(QWidget* parent) :
    QWidget(parent)
{
    this->setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    rec = NULL;
    x = 0;
    y = 0;
}

void Overlay::startRect(RectReceiver* r) {
    stage = 0;
    this->rec = r;
}

void Overlay::updateMouse(int x, int y, int w, int h) {
    if (this->rec != NULL && (x != this->x || y != this->y)) {
        this->x = x;
        this->y = y;
        update();
    }
}

void Overlay::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    painter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);
    painter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);
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
        if (x1 > x2) {
            lx1 = double(x2) / w;
            lx2 = double(x1) / w;
        } else {
            lx1 = double(x2) / w;
            lx2 = double(x1) / w;
        }

        if (y1 > y2) {
            ly1 = 1.0 - double(y2) / h;
            ly2 = 1.0 - double(y1) / h;
        } else {
            ly1 = 1.0 - double(y2) / h;
            ly2 = 1.0 - double(y1) / h;
        }

        rec->finishRect(lx1, lx2, ly1, ly2);
        rec = NULL;
    }
    update();
}
