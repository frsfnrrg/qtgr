#include "graphwidget.h"
#include "mainwindow.h"
#include "base/globals.h"
#include "view.h"
#include "choosers.h"
#include "util.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QStatusBar>
#include <QGraphicsTextItem>

#if QT_VERSION < 0x040400
#include <QMouseEvent>
#endif

const double FONT_BASE_SIZE = 14.0;

static MainWindow* mainWindow;
static qreal dpiInvScale = 1.0;

static GraphWidget* myGraphWidget;

GraphicsScene::GraphicsScene(MainWindow* mwin)
    : QGraphicsScene()
{
    mainWindow = mwin;
    // no direct interaction with the graph,
    this->setItemIndexMethod(QGraphicsScene::NoIndex);

    this->setSceneRect(0, 0, 800, 600);
    this->setBackgroundBrush(Qt::white);

    rec = NULL;

    cancelRectSelect = createQAction(tr("Cancel rect select"),
        tr("Stop the process of choosing a rectangle"),
        "",
        this);
    connect(cancelRectSelect, SIGNAL(triggered()), this, SLOT(cancelRect()));
}

void GraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu menu(event->widget());
    if (rec != NULL) {
        menu.addAction(cancelRectSelect);
        menu.addSeparator();
    }

    mainWindow->viewMenu->populateMenu(&menu);
    menu.exec(event->screenPos());
}

void GraphicsScene::drawForeground(QPainter* painter, const QRectF& /*exposed*/)
{
    if (rec == NULL || stage != Dragging)
        return;

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(QPen(Qt::black, 0.5));
    painter->setBrush(QBrush());

    double w = this->width();
    double h = this->height();
    QRectF target(x1 * w, (1.0 - y1) * h, (x2 - x1) * w, (y1 - y2) * h);
    painter->drawRect(target);
}

void GraphicsScene::startRect(RectReceiver* r)
{
    this->rec = r;
    stage = Picking;
    update();
}

void GraphicsScene::updateMouse(double x, double y)
{
    if (this->rec != NULL && stage == Dragging) {
        if (x != this->x2 || y != this->y2) {
            this->x2 = x;
            this->y2 = y;
            update();
        }
    }
}

void GraphicsScene::clickMouse(double x, double y)
{
    if (rec == NULL)
        return;

    if (stage == Picking) {
        x1 = x2 = x;
        y1 = y2 = y;
        stage = Dragging;
    }
    else {
        x2 = x;
        y2 = y;

        double tmp;
        if (x1 > x2) {
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        if (y1 > y2) {
            tmp = y2;
            y2 = y1;
            y1 = tmp;
        }

        rec->finishRect(x1, x2, y1, y2);
        rec = NULL;
    }
    update();
}

void GraphicsScene::cancelRect()
{
    rec = NULL;
    update();
}

GraphWidget::GraphWidget(MainWindow* mwin)
    : QGraphicsView(mscene = new GraphicsScene(mwin), mwin)
{
    myGraphWidget = this;
    GraphWidget::pen = new QPen();
    GraphWidget::patnum = 0;
    GraphWidget::fontnum = 0;

#if QT_VERSION >= 0x040300
    // Our side manages the painter state
    this->setOptimizationFlag(QGraphicsView::DontSavePainterState);
    // Moving antialiased objects leaves traces. But nothing is moved.
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
#endif
    // required for context menu to work
    this->setInteractive(true);

    // Normally, X=Y.
    dpiInvScale = 96.0 / qreal(this->logicalDpiX());

    mainWindow = mwin;
    PatternComboBox::initializePatterns();
    FontComboBox::initializeFonts();
    mouseClickCall = NULL;
    mouseDoubleCall = NULL;
    drawing_line = false;
    point_state = ptNot;
}

void GraphWidget::mouseMoveEvent(QMouseEvent* event)
{
    QString message;
    QPointF pt = mapToScene(event->pos());
    double vx = pt.x() / mscene->width();
    double vy = 1.0 - pt.y() / mscene->height();
    double wx, wy;

    // cursor is used by other function
    if (mouseClickCall != NULL) {
        return;
    }

    //  mouse within data rect
    if (vx > g[cg].v.xv1 && vx < g[cg].v.xv2 && vy > g[cg].v.yv1 && vy < g[cg].v.yv2) {
        view2world(vx, vy, &wx, &wy);
        this->setCursor(Qt::WhatsThisCursor);
        message = "[x,y] = " + QString::number(wx, 'f', 6) + "," + QString::number(wy, 'f', 6);
        mainWindow->statusBar()->showMessage(message, 5000);
    }
    else {
        this->setCursor(Qt::ArrowCursor);
        mainWindow->statusBar()->clearMessage();
    }

    mscene->updateMouse(vx, vy);
}

void GraphWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        // left click is for handlers
        QPointF pt = mapToScene(event->pos());
        double vx = pt.x() / mscene->width();
        double vy = 1.0 - pt.y() / mscene->height();
        if (mouseClickCall != NULL) {
            mouseClickCall->mouse(vx, vy);
        }
        else {
            mscene->clickMouse(vx, vy);
        }
        event->accept();
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPointF pt = mapToScene(event->pos());
    double vx = pt.x() / mscene->width();
    double vy = 1.0 - pt.y() / mscene->height();
    if (mouseDoubleCall != NULL) {
        mouseDoubleCall->mouse(vx, vy);
    }
}

void GraphWidget::resizeEvent(QResizeEvent* r)
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatioByExpanding);
    QGraphicsView::resizeEvent(r);
}

void GraphWidget::startRect(RectReceiver* r)
{
    myGraphWidget->mscene->startRect(r);
}

void GraphWidget::getcanvas(int* win_w, int* win_h)
{

    *win_w = scene()->width();
    *win_h = scene()->height();
    //      printf("GraphWidget::getcanvas %i %i\n",*win_w,*win_h);
}

void GraphWidget::paint(int x, int y, int mode)
{
    //qDebug("%d %d %d %d",x,y,mode,point_state);
    QPointF pt(x, y);
    if (mode) { // continue drawing line
        if (!drawing_line) {
            qCritical("Incorrect command order; something happened.");
        }
        else {
            // dense curves have lots of duplicate points
            if (currentTrace.last() != pt) {
                currentTrace.append(pt);
                point_state = ptNot;
            }
            else if (point_state == ptOne) {
                point_state = ptNot;
            }
            else if (point_state == ptTwo) {
                point_state = ptThree;
            }
        }
    }
    else {
        // If points were piled up, requesting a jump
        if (currentTrace.size() > 0 && pt != currentTrace.last()) {
            commitTrace();
            point_state = ptNot;
        }

        if (drawing_line && pt == currentTrace.last()) {
            // do nothing; the last line coincides with this one
            if (point_state == ptOne) {
                point_state = ptTwo;
            }
            else {
                point_state = ptNot;
            }
        }
        else {
            // starting a new line segment
            currentTrace.append(pt);
            point_state = ptOne;
        }
        drawing_line = true;
    }
}

void GraphWidget::linew(int w)
{
    if (drawing_line) {
        commitTrace();
    }
    pen->setWidth(w);
}

void GraphWidget::lines(int s)
{
    if (drawing_line) {
        commitTrace();
    }
    pen->setStyle((Qt::PenStyle)s);
}

void GraphWidget::linec(int c)
{
    if (drawing_line) {
        commitTrace();
    }
    pen->setColor(ColorComboBox::getColor(c));
}

QMap<QString, QString> tex2html;

QMap<QString, QString> texmapping()
{
    QMap<QString, QString> map;
    typedef struct {
        const char* tex;
        const char* html;
    } ppair;

    const ppair th[] = {
        { "\\alpha", "&alpha;" },
        { "\\beta", "&beta;" },
        { "\\gamma", "&gamma;" },
        { "\\delta", "&delta;" },
        { "\\epsilon", "&epsilon;" },

        { "\\zeta", "&zeta;" },
        { "\\eta", "&eta;" },
        { "\\theta", "&theta;" },
        { "\\iota", "&iota;" },
        { "\\kappa", "&kappa;" },

        { "\\lambda", "&lambda;" },
        { "\\mu", "&mu;" },
        { "\\nu", "&nu;" },
        { "\\xi", "&xi;" },
        { "\\omicron", "&omicron;" },

        { "\\pi", "&pi;" },
        { "\\rho", "&rho;" },
        { "\\sigma", "&sigma;" },
        { "\\tau", "&tau;" },
        { "\\upsilon", "&upsilon;" },

        { "\\phi", "&phi;" },
        { "\\chi", "&chi;" },
        { "\\psi", "&psi;" },
        { "\\omega", "&omega;" },

        // Note: \varepsilon -> &vepsilon and like
        // are in XVGR, but not in QT
        // Therefore, we italicize, with all its problems

        { "\\varepsilon", "<i>&epsilon;</i>" },
        { "\\vartheta", "<i>&theta;</i>" },
        { "\\varpi", "<i>&pi;</i>" },
        { "\\varrho", "<i>&rho;</i>" },
        { "\\varsigma", "<i>&sigma;</i>" },
        { "\\varphi", "<i>&phi;</i>" },

        // Auxiliary

        { "\\S", "<sup>" },
        { "\\N", "</sup>" }
    };

    int i;
    for (i = 0; i < (int)(sizeof(th) / sizeof(ppair)); i++) {
        map.insert(th[i].tex, th[i].html);
    }

    return map;
}

QString texconvert(char* s, int slen)
{
    char s1[1024];
    char* s_tmp;

    QString s_html;

    int i, k, l;

    // initialize tex2html map
    i = 0;
    if (tex2html.isEmpty()) {
        tex2html = texmapping();
    }

    s_tmp = s1;
    bool sup = false;
    bool sub = false;

    for (i = 0; i < slen; i++) {

        if (sup && s[i] == '}') {
            s_html += "</sup>";
            sup = false;
            continue;
        }

        if (sub && s[i] == '}') {
            s_html += "</sub>";
            sub = false;
            continue;
        }

        //      superscript
        if (s[i] == '^') {
            s_html += "<sup>";
            i += 1;
            if (s[i] == '{') {
                sup = true;
            }
            else {
                s_html += s[i];
                s_html += "</sup>";
            }
            continue;
        }

        //	subscript
        if (s[i] == '_') {
            s_html += "<sub>";
            i += 1;
            if (s[i] == '{') {
                sub = true;
            }
            else {
                s_html += s[i];
                s_html += "</sub>";
            }
            continue;
        }

        // 	special character
        if (s[i] == '\\') {
            l = i;
            k = 0;
            do {
                s_tmp[k] = s[l];
                k++;
                l++;
            } while (((int)s[l] >= (int)'a' && (int)s[l] <= (int)'z') || ((int)s[l] >= (int)'A' && (int)s[l] <= (int)'Z'));

            s_tmp[k] = '\0';
            //  	    printf("test %s ",s_tmp);
            if (tex2html.contains(s_tmp)) {
                // 	      printf("test %s ",tex2html.value(s_tmp).toAscii().data());
                s_html += tex2html.value(s_tmp);
                i = l;
            }
            else {
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
    if (drawing_line) {
        commitTrace();
    }
    //printf("GraphWidget: text %i %i %i %s %i\n",x,y,rot,s,just);

    if (charsize == 0.0) {
        return;
    }

    double fontsize = FONT_BASE_SIZE * charsize;

    QFont font = FontComboBox::getFont(fontnum);
    // Avoid double dpi scaling
    font.setPointSizeF(fontsize * dpiInvScale);

    QGraphicsTextItem* text = scene()->addText("");
    text->setHtml(texconvert(s, strlen(s)));
    text->setFont(font);
    text->setDefaultTextColor(pen->color());
    QRectF bRect = text->boundingRect();

    qreal width, height, xoff, yoff;
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
        xoff = width / 2;
        yoff = height / 2;
        break;
    }
#if QT_VERSION >= 0x040600
    text->setTransformOriginPoint(xoff, yoff);
    text->setRotation(-rot);
#else
    text->translate(xoff, yoff);
    text->rotate(-rot);
    text->translate(-xoff, -yoff);
#endif
    text->setPos(x - xoff, y - yoff);
}

void GraphWidget::arc(int x, int y, int r, int fill)
{
    if (drawing_line) {
        commitTrace();
    }
    if (r == 0) {
        drawPoint(x, y);
        return;
    }
    QBrush brush = QBrush();
    if (fill == 1) {
        brush = QBrush(pen->color());
    }

    scene()->addEllipse(QRectF(x - r, y - r, 2 * r, 2 * r), *pen, brush);
}

void GraphWidget::fillcolor(int n, int px[], int py[])
{
    if (drawing_line) {
        commitTrace();
    }
    QBrush brush = QBrush(pen->color(), Qt::SolidPattern);
    QVector<QPointF> path;
    for (int i = 0; i < n; i++) {
        path.append(QPointF(px[i], py[i]));
    }
    scene()->addPolygon(QPolygonF(path), *pen, brush);
}

void GraphWidget::fill(int n, int px[], int py[])
{
    if (drawing_line) {
        commitTrace();
    }
    QBrush brush = QBrush();
    QVector<QPointF> path;

    brush.setTexture(PatternComboBox::getPattern(patnum));

    for (int i = 0; i < n; i++) {
        path.append(QPointF(px[i], py[i]));
    }
    scene()->addPolygon(QPolygonF(path), *pen, brush);
}

void GraphWidget::ellipse(int x, int y, int xm, int ym)
{
    if (drawing_line) {
        commitTrace();
    }
    if (xm == 0 && ym == 0) {
        drawPoint(x, y);
        return;
    }
    QBrush brush = QBrush();
    int h = scene()->height();
    scene()->addEllipse(QRectF(x - xm / 2, h - y - ym / 2, xm, ym), *pen, brush);
}

void GraphWidget::fillellipse(int x, int y, int xm, int ym)
{
    if (drawing_line) {
        commitTrace();
    }
    if (xm == 0 && ym == 0) {
        drawPoint(x, y);
        return;
    }

    QBrush brush = QBrush(pen->color());
    int h = scene()->height();
    scene()->addEllipse(QRectF(x - xm / 2, h - y - ym / 2, xm, ym), *pen, brush);
}

int GraphWidget::stringextentx(double scale, char* str)
{
    QFont font = FontComboBox::getFont(fontnum);
    font.setPointSizeF(FONT_BASE_SIZE * scale * dpiInvScale);
    QFontMetrics metric(font);
    int w = metric.boundingRect(str).width();
    // fudge factor.... (y axis labels)
    // could also be linked to devcharsize as exported by the driver.
    //
    return (int)((double)w * 1.9);
}

int GraphWidget::stringextenty(double scale, char* str)
{
    QFont font = FontComboBox::getFont(fontnum);
    font.setPointSizeF(FONT_BASE_SIZE * scale * dpiInvScale);
    QFontMetrics metric(font);
    int h = metric.boundingRect(str).height();
    return (int)((double)h * 1.1);
}

int GraphWidget::setpattern(int num)
{
    if (drawing_line) {
        commitTrace();
    }

    patnum = num;
    return 0;
}

void GraphWidget::clear()
{
    if (drawing_line) {
        drawing_line = false;
    }

#if QT_VERSION >= 0x040400
    scene()->clear();
#else
    QList<QGraphicsItem*> items = scene()->items();
    while (items.size()) {
        scene()->removeItem(items.last());
        // removing the item transfers
        // ownership..
        delete items.last();
        items.pop_back();
    }
#endif
}

void GraphWidget::update()
{
    if (drawing_line) {
        commitTrace();
    }
    scene()->update();
}

void GraphWidget::setfont(int num)
{
    if (drawing_line) {
        commitTrace();
    }

    fontnum = num;
}

void GraphWidget::drawPoint(int x, int y)
{
    // not external; no drawing_line check (may be
    // called by that fn. anyway
    qreal size = 0.5;
    scene()->addEllipse(QRectF(x - size, y - size, 2 * size, 2 * size), QPen(pen->color()), QBrush(pen->color()));
}

void GraphWidget::commitTrace()
{
    QPainterPath p;
    int max = currentTrace.size();
    if (point_state == ptThree) {
        drawPoint(currentTrace.last().x(), currentTrace.last().y());
    }
    else if (max >= 2) {
        for (int i = 0; i < max - 1; i++) {
            // If you skips the moveTo's at each step, performance tanks because
            // the system plans to polygon fill the path, and does N^2
            // intersection calculations.
            p.moveTo(currentTrace[i]);
            p.lineTo(currentTrace[i + 1]);
        }
        scene()->addPath(p, *pen);
    }
    currentTrace = QPolygonF();

    drawing_line = false;
}

extern "C" {

void qtview_getcanvas(int* win_w, int* win_h)
{
    myGraphWidget->getcanvas(win_w, win_h);
}

void qtview_paint(int x, int y, int mode)
{
    myGraphWidget->paint(x, y, mode);
}

void qtview_linew(int w)
{
    myGraphWidget->linew(w);
}

void qtview_lines(int w)
{
    myGraphWidget->lines(w);
}

void qtview_linec(int c)
{
    myGraphWidget->linec(c);
}

void qtview_text(int x, int y, int rot, char* c, int just)
{
    myGraphWidget->text(x, y, rot, c, just);
}

void qtview_arc(int x, int y, int r, int fill)
{
    myGraphWidget->arc(x, y, r, fill);
}

void qtview_fillcolor(int n, int px[], int py[])
{
    myGraphWidget->fillcolor(n, px, py);
}

void qtview_fill(int n, int px[], int py[])
{
    myGraphWidget->fill(n, px, py);
}

void qtview_clear()
{
    myGraphWidget->clear();
}

void qtview_update()
{
    myGraphWidget->update();
}

int qtview_stringextentx(double scale, char* str)
{
    return myGraphWidget->stringextentx(scale, str);
}

int qtview_stringextenty(double scale, char* str)
{
    return myGraphWidget->stringextenty(scale, str);
}

int qtview_setpattern(int num)
{
    return myGraphWidget->setpattern(num);
}

void qtview_drawellipse(int x, int y, int xm, int ym)
{
    myGraphWidget->ellipse(x, y, xm, ym);
}

void qtview_fillellipse(int x, int y, int xm, int ym)
{
    myGraphWidget->fillellipse(x, y, xm, ym);
}

void qtview_setfont(int n)
{
    myGraphWidget->setfont(n);
}
}
