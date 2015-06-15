#include <QtGui>

#include "graphwidget.h"
#include "mainwindow.h"
#include "base/globals.h"
#include "view.h"
#include "choosers.h"

const double FONT_BASE_SIZE = 14.0;

MainWindow *mainWindow;

GraphWidget* GraphWidget::myGraphWidget;

GraphicsScene::GraphicsScene(MainWindow* mwin) :
    QGraphicsScene()
{
    mainWindow = mwin;
}

void GraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu(event->widget());
    if (mainWindow->gwidget->overlay->isRectSelecting()) {
        menu.addAction(mainWindow->gwidget->overlay->cancelRectSelect);
        menu.addSeparator();
    }

    mainWindow->viewMenu->populateMenu(&menu);
    menu.exec(event->screenPos());
}

GraphWidget::GraphWidget(QGraphicsScene *s, MainWindow *mwin)
    : QGraphicsView(s,mwin)
{
    GraphWidget::myGraphWidget = this;
    GraphWidget::pen = new QPen();
    GraphWidget::patnum = 0;
    GraphWidget::fontnum = 0;

    mainWindow = mwin;
    PatternComboBox::initializePatterns();
    FontComboBox::initializeFonts();
    mouseClickCall = NULL;
    mouseDoubleCall = NULL;
    overlay = new Overlay(this);
    overlay->setMouseTracking(true);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    QString message;
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    double vx = double(event->x())/scene->width();
    double vy = 1.0-double(event->y())/scene->height();
    double wx,wy;
    
    // cursor is used by other function
    if (mouseClickCall != NULL) {
        return;
    }

    //  mouse within data rect
    if (vx > g[cg].v.xv1 && vx < g[cg].v.xv2 && vy > g[cg].v.yv1 && vy < g[cg].v.yv2 ) {
        view2world(vx,vy,&wx,&wy);
        this->setCursor(Qt::WhatsThisCursor);
        message = "[x,y] = " + QString::number(wx,'f',6) + "," + QString::number(wy,'f',6);
        mainWindow->statusBar()->showMessage(message, 5000);
    } else {
        this->setCursor(Qt::ArrowCursor);
        mainWindow->statusBar()->clearMessage();
    }
    //     printf("mouseMove %i %i %f %f\n",event->x(),event->y(),scene->height(),scene->width());

    overlay->updateMouse(event->x(),event->y(),scene->width(),scene->height());
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    // Graph is strictly interacted with using left click
    if (!(event->buttons() & Qt::LeftButton)) {
        event->ignore();
        return;
    }

    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    //    printf("mouseClick %i %i %f %f\n",event->x(),event->y(),scene->height(),scene->width());
    if (mouseClickCall != NULL) {
        mouseClickCall->mouse(event->x(),event->y(),scene->width(),scene->height());
    }
    overlay->clickMouse(event->x(),event->y(),scene->width(),scene->height());
    event->accept();
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    //    printf("mouseDoubleClick %i %i %f %f\n",event->x(),event->y(),scene->height(),scene->width());
    if (mouseDoubleCall != NULL) {
        mouseDoubleCall->mouse(event->x(),event->y(),scene->width(),scene->height());
    }
}

void GraphWidget::resizeEvent(QResizeEvent *r) {
    overlay->resize(this->size());
    QGraphicsView::resizeEvent(r);
}

void GraphWidget::startRect(RectReceiver* r) {
    GraphWidget::myGraphWidget->overlay->startRect(r);
}

void GraphWidget::getcanvas(int* win_w, int* win_h)
{

    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    *win_w = scene->width();
    *win_h = scene->height();
    //      printf("GraphWidget::getcanvas %i %i\n",*win_w,*win_h);
}

void GraphWidget::paint(int x1, int y1, int x2, int y2)
{
    //     printf("GraphWidget::test %i %i %i %i\n",x1,y1,x2,y2);
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    QPen* pen = GraphWidget::myGraphWidget->pen;
    scene->addLine(x1,y1,x2,y2,*pen);
}

void GraphWidget::linew(int w)
{
    QPen* pen = GraphWidget::myGraphWidget->pen;
    pen->setWidth(w);
}

void GraphWidget::lines(int s)
{
    QPen* pen = GraphWidget::myGraphWidget->pen;
    pen->setStyle((Qt::PenStyle)s);
}

void GraphWidget::linec(int c)
{
    QPen* pen = GraphWidget::myGraphWidget->pen;
    pen->setColor(  ColorComboBox::getColor(c));
}

QMap<QString, QString> tex2html;

QMap<QString, QString> texmapping() {
    QMap<QString, QString> map;
    typedef struct {const char* tex;
                    const char* html;} ppair;

    const ppair th[] = {
        {"\\alpha", "&alpha;"},
        {"\\beta", "&beta;"},
        {"\\gamma", "&gamma;"},
        {"\\delta", "&delta;"},
        {"\\epsilon", "&epsilon;"},

        {"\\zeta", "&zeta;"},
        {"\\eta", "&eta;"},
        {"\\theta", "&theta;"},
        {"\\iota", "&iota;"},
        {"\\kappa", "&kappa;"},

        {"\\lambda", "&lambda;"},
        {"\\mu", "&mu;"},
        {"\\nu", "&nu;"},
        {"\\xi", "&xi;"},
        {"\\omicron", "&omicron;"},

        {"\\pi", "&pi;"},
        {"\\rho", "&rho;"},
        {"\\sigma", "&sigma;"},
        {"\\tau", "&tau;"},
        {"\\upsilon", "&upsilon;"},

        {"\\phi", "&phi;"},
        {"\\chi", "&chi;"},
        {"\\psi", "&psi;"},
        {"\\omega", "&omega;"},

        // Note: \varepsilon -> &vepsilon and like
        // are in XVGR, but not in QT
        // Therefore, we italicize, with all its problems

        {"\\varepsilon", "<i>&epsilon;</i>"},
        {"\\vartheta", "<i>&theta;</i>"},
        {"\\varpi", "<i>&pi;</i>"},
        {"\\varrho", "<i>&rho;</i>"},
        {"\\varsigma", "<i>&sigma;</i>"},
        {"\\varphi", "<i>&phi;</i>"},

        // Auxiliary

        {"\\S", "<sup>"},
        {"\\N", "</sup>"}
    };

    int i;
    for (i=0;i<(int)(sizeof(th) / sizeof(ppair));i++) {
        map.insert(th[i].tex, th[i].html);
    }

    return map;
}

QString texconvert(char* s, int slen)
{
    char s1[1024];
    char *s_tmp;

    QString s_html;

    int  i,k,l;

    // initialize tex2html map
    i=0;
    if (tex2html.isEmpty()) {
        tex2html = texmapping();
    }

    s_tmp = s1;
    bool sup = false;
    bool sub = false;

    for (i = 0; i < slen; i++) {

        if (sup && s[i]=='}') {
            s_html += "</sup>";
            sup = false;
            continue;
        }

        if (sub && s[i]=='}') {
            s_html += "</sub>";
            sub = false;
            continue;
        }

        //      superscript
        if (s[i] == '^') {
            s_html += "<sup>";
            i += 1;
            if (s[i]=='{')  {
                sup = true;
            } else {
                s_html += s[i];
                s_html += "</sup>";
            }
            continue;
        }

        //	subscript
        if (s[i] == '_') {
            s_html += "<sub>";
            i += 1;
            if (s[i]=='{')  {
                sub = true;
            } else {
                s_html += s[i];
                s_html += "</sub>";
            }
            continue;
        }

        // 	special character
        if (s[i] == '\\') {
            l=i; k=0;
            do {
                s_tmp[k] = s[l];
                k++; l++;
            } while( ((int) s[l]>= (int) 'a' && (int) s[l]<= (int) 'z') ||
                     ((int) s[l]>= (int) 'A' && (int) s[l]<= (int) 'Z'));

            s_tmp[k] = '\0';
            //  	    printf("test %s ",s_tmp);
            if (tex2html.contains(s_tmp)) {
                // 	      printf("test %s ",tex2html.value(s_tmp).toAscii().data());
                s_html += tex2html.value(s_tmp);
                i = l;
            } else {
                s_html += s[i];
            }
            continue;
        }

        s_html += s[i];
    }
    //printf("texconvert: %s|%s\n",s,s_html.toAscii().data());
    return s_html;
}

void GraphWidget::text(int x, int y, int rot, char* s, int just)
{
    //printf("GraphWidget: text %i %i %i %s %i\n",x,y,rot,s,just);

    if (charsize == 0.0) {
        return;
    }

    double fontsize = FONT_BASE_SIZE * charsize;

    QFont font = FontComboBox::getFont(GraphWidget::myGraphWidget->fontnum);
    font.setPointSizeF(fontsize);

    QGraphicsScene* gscene = GraphWidget::myGraphWidget->scene();
    QGraphicsTextItem* text = gscene->addText("");
    text->setHtml(texconvert(s,strlen(s)));
    text->setFont(font);
    text->setDefaultTextColor(GraphWidget::myGraphWidget->pen->color());
    QRectF bRect = text->boundingRect();

    qreal width,height,xoff, yoff;
    width = bRect.width();
    height = bRect.height();

    switch (just) {
    case 0: // left
        xoff = 0;
        yoff = height / 2;
        break;
    case 1: // right
        xoff = width;
        yoff = height / 2;
        break;
    case 2: // centered
        xoff = width  / 2;
        yoff = height / 2;
        break;
    }

    text->setTransformOriginPoint(xoff,yoff);
    text->setPos(x-xoff,y-yoff);
    text->setRotation(-rot);
}

void GraphWidget::arc(int x, int y, int r, int fill)
{
    //      printf("GraphWidget::arc %i %i %i %i\n",x,y,r);
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    QPen* pen = GraphWidget::myGraphWidget->pen;
    QBrush brush = QBrush();
    
    if (fill == 1) {
        brush = QBrush(pen->color());
    }
    
    scene->addEllipse(x-r,y-r,2*r,2*r,*pen,brush);
}

void GraphWidget::fillcolor(int n, int px[], int py[])
{
    qDebug("GraphWidget::plaincolor %i %i %i",n, px[0], py[0]);
    QPen* pen = GraphWidget::myGraphWidget->pen;
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    QBrush brush = QBrush(pen->color(), Qt::SolidPattern);
    QVector<QPointF> path;
    for (int i = 0; i < n; i++) {
        path.append(QPointF(px[i],py[i]));
    }
    scene->addPolygon(QPolygonF(path),*pen,brush);
}

void GraphWidget::fill(int n, int px[], int py[]) {
    qDebug("GraphWidget::fillpattern %i %i %i",n, px[0], py[0]);
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    QPen* pen = GraphWidget::myGraphWidget->pen;
    QBrush brush = QBrush(pen->color());
    QVector<QPointF> path;

    int patnum = GraphWidget::myGraphWidget->patnum;

    brush.setTexture(PatternComboBox::getPattern(patnum));

    for (int i = 0; i < n; i++) {
        path.append(QPointF(px[i],py[i]));
    }
    scene->addPolygon(QPolygonF(path),*pen,brush);
}

void GraphWidget::ellipse(int x, int y, int xm, int ym) {
    // TODO
    printf("ELLIPSE DRAW CALLED: %d %d %d %d\n",x,y,xm,ym);
}

void GraphWidget::fillellipse(int x, int y, int xm, int ym) {
    printf("ELLIPSE FILL CALLED: %d %d %d %d\n",x,y,xm,ym);
}

int GraphWidget::stringextentx(double scale, char* str) {
    QFont font = FontComboBox::getFont(GraphWidget::myGraphWidget->fontnum);
    font.setPointSizeF(FONT_BASE_SIZE * scale);
    QFontMetrics metric(font);
    int w = metric.boundingRect(str).width();
    // fudge factor.... (y axis labels)
    // could also be linked to devcharsize as exported by the driver.
    //
    return (int)((double)w * 1.9);

}

int GraphWidget::stringextenty(double scale, char* str) {
    QFont font = FontComboBox::getFont(GraphWidget::myGraphWidget->fontnum);
    font.setPointSizeF(FONT_BASE_SIZE * scale);
    QFontMetrics metric(font);
    int h = metric.boundingRect(str).height();
    return (int)((double)h * 1.1);
}

int GraphWidget::setpattern(int num) {
    GraphWidget::myGraphWidget->patnum = num;
    return 0;
}

void GraphWidget::clear()
{
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    scene->clear();
}

void GraphWidget::update()
{
    QGraphicsScene* scene = GraphWidget::myGraphWidget->scene();
    scene->update();
}

void GraphWidget::setfont(int num) {
    GraphWidget::myGraphWidget->fontnum = num;
}

extern "C"
{

void qtview_getcanvas(int* win_w, int* win_h)
{
    GraphWidget::getcanvas(win_w, win_h);
    
}

void qtview_paint(int x1, int y1, int x2, int y2)
{
    GraphWidget::paint(x1,y1,x2,y2);
}

void qtview_linew(int w)
{
    GraphWidget::linew(w);
}

void qtview_lines(int w)
{
    GraphWidget::lines(w);
}

void qtview_linec(int c)
{
    GraphWidget::linec(c);
}

void qtview_text(int x, int y, int rot, char* c, int just)
{
    GraphWidget::text(x,y,rot,c,just);
}

void qtview_arc(int x, int y, int r, int fill)
{
    GraphWidget::arc(x,y,r,fill);
}

void qtview_fillcolor(int n, int px[], int py[])
{
    GraphWidget::fillcolor(n,px,py);
}

void qtview_fill(int n, int px[], int py[])
{
    GraphWidget::fill(n,px,py);
}

void qtview_clear()
{
    GraphWidget::clear();
}

void qtview_update()
{
    GraphWidget::update();
}

int qtview_stringextentx(double scale, char* str) {
    return GraphWidget::stringextentx(scale, str);
}

int qtview_stringextenty(double scale, char* str) {
    return GraphWidget::stringextenty(scale, str);
}

int qtview_setpattern(int num) {
    return GraphWidget::setpattern(num);
}

void qtview_drawellipse(int x, int y, int xm, int ym) {
    GraphWidget::ellipse(x,y,xm,ym);
}

void qtview_fillellipse(int x, int y, int xm, int ym) {
    GraphWidget::fillellipse(x,y,xm,ym);
}

void qtview_setfont(int n) {
    GraphWidget::setfont(n);
}
}

