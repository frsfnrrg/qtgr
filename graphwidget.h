#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

# ifdef __cplusplus 

#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow;

class MouseCallBack
{
public:
    virtual void mouse( double, double ) = 0;
};

class RectReceiver {
public:
    virtual void finishRect(double , double , double , double ) = 0;
};

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphicsScene(MainWindow*);
    ~GraphicsScene();

    void startRect(RectReceiver* r);
    void updateMouse(double x, double y);
    void clickMouse(double x, double y);
protected slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private slots:
    void cancelRect();
protected:
    virtual void drawForeground(QPainter*, const QRectF &);
private:
    MainWindow* mainWindow;
    double x1,x2,y1,y2;
    enum {Picking, Dragging} stage;
    RectReceiver* rec;
    QAction* cancelRectSelect;
};

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(MainWindow *);
    void paint(int x,int y, int mode);
    void linew(int w);
    void lines(int s);
    void linec(int s);
    void text(int x, int y, int rot, char* c, int just);
    void arc(int x, int y, int r, int fill);
    void fillcolor (int n, int px[], int py[]);
    void fill(int n, int px[], int py[]);
    void clear();
    void update();
    void getcanvas(int* win_w, int* win_h);
    int stringextentx(double scale, char* str);
    int stringextenty(double scale, char* str);
    int setpattern(int num);
    void ellipse(int x, int y, int xm, int ym);
    void fillellipse(int x, int y, int xm, int ym);
    void setfont(int num);
    QColor cmscolors[16];
    MouseCallBack *mouseClickCall;
    MouseCallBack *mouseDoubleCall;

    static void startRect(RectReceiver* r);
public slots:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* r);

private slots:

private:
    void drawPoint(int x, int y);
    void commitTrace();

    QPen pen;
    int fontnum;
    int patnum;
    int colornum;
    GraphicsScene* mscene;
    QPolygonF currentTrace;
    bool drawing_line;
    enum { ptNot, ptOne, ptTwo, ptThree } point_state;
};

#endif // __cplusplus

# ifdef __cplusplus 
extern "C"
{
#endif // __cplusplus

void qtview_paint(int x, int y, int mode);
void qtview_linew(int w);
void qtview_lines(int s);
void qtview_linec(int c);
void qtview_text(int x, int y, int rot, char* c, int just);
void qtview_arc(int x, int y, int r, int fill);
void qtview_fillcolor(int n, int px[], int py[]);
void qtview_fill(int n, int px[], int py[]);
void qtview_clear();
void qtview_update();
void qtview_getcanvas(int* win_w, int* win_h);
int qtview_stringextentx(double scale, char* str);
int qtview_stringextenty(double scale, char* str);
int qtview_setpattern(int n);
void qtview_drawellipse(int x, int y, int xm, int ym);
void qtview_fillellipse(int x, int y, int xm, int ym);
void qtview_setfont(int k);
int qtview_getsymsize();

# ifdef __cplusplus 
}
#endif // __cplusplus


#endif
