#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

# ifdef __cplusplus 

#include <QtGui>
#include "mousecall.h"
#include "overlay.h"

class MainWindow;

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphicsScene(MainWindow*);
protected slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    MainWindow* mainWindow;
};

class GraphWidget : public QGraphicsView
{
    Q_OBJECT
    static GraphWidget *myGraphWidget;

public:
    GraphWidget(QGraphicsScene *, QWidget *parent = 0);
    static void paint(int x1, int y1, int x2, int y2); 
    static void linew(int w);
    static void lines(int s);
    static void linec(int s);
    static void text(int x, int y, int rot, char* c, int just);
    static void arc(int x, int y, int r, int fill);
    static void fillcolor (int n, int px[], int py[]);
    static void clear();
    static void update();
    static void getcanvas(int* win_w, int* win_h);
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
   Overlay* overlay;
   QPen *pen;
   void initialize_cms_data();  
   
};

#endif // __cplusplus

# ifdef __cplusplus 
extern "C"
{
#endif // __cplusplus
  void qtview_paint(int x1, int y1, int x2, int y2);
  void qtview_linew(int w);
  void qtview_lines(int s);
  void qtview_linec(int c);
  void qtview_text (int x, int y, int rot, char* c, int just);
  void qtview_arc (int x, int y, int r, int fill);
  void qtview_fillcolor (int n, int px[], int py[]);
  void qtview_clear();
  void qtview_update();
  void qtview_getcanvas(int* win_w, int* win_h);
  

# ifdef __cplusplus 
}
#endif // __cplusplus


#endif
