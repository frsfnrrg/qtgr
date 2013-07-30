#ifndef OVERLAY_H
#define OVERLAY_H

#include <QtGui>

class RectReceiver {
public:
    virtual void finishRect(double , double , double , double ) {}
};

class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget* parent);

    void startRect(RectReceiver* r);

    void updateMouse(int x, int y, int w, int h);

    void clickMouse(int x, int y, int w, int h);

    void paintEvent(QPaintEvent *event);
private:
    int x,y,x1,x2,y1,y2;
    int stage;
    RectReceiver* rec;

signals:
    
public slots:
    
};

#endif // OVERLAY_H
