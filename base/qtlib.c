/* $Id: xqtlib.c,v 0.1 26.12.2012 csto@lle.rochester.edu $
 *
 * driver for qtlib for gr
 *
 */

#include <stdio.h>
#include "externs.h"

//qtview interface methods
#include "graphwidget.h"

// text outputs
#include "transform/regression.h"

void stufftext(char* s) {
    qt_stufftext(s);
}

#include "tools/status.h"

void update_set_status(int graphno, int setno) {
    qt_update_set_status(graphno, setno);
}

static int save_images;

extern double devcharsize;
extern double charsize;
// 
// 
// #define MINCOLOR 0
#define MAXLINEW 15

// FIXME should be read from qt
#define maxcolors 256;
// 
// double devtoworldx(), devtoworldy();

static int qtliblinewidth = 0;
static int qtlibdmode;
static int qtlibfont = 0;
static int qtliblinestyle = 1;
static int qtdoublebuff = 0;	/* no double buffering by default */
int win_h, win_w;

// /*
//  * the following is a tunable parameter and may
//  * need to be adjusted
//  */
#ifdef HIRES
double qtlibcharsize = 0.80;
#else
double qtlibcharsize = 0.60;
#endif


//imported from draw.c FIXME?
double xconv(), yconv();

static void qtlibinit()
{
    double wx1, wx2, wy1, wy2;
    static int inc = 1;
    extern int invert, overlay, doclear, bgcolor;
    
    qtview_getcanvas(&win_w,&win_h);
    
    devwidth = win_w;
    devheight = win_h;
    qtview_clear();
}


static int npending;

void drawqtlib(int x, int y, int mode)
{
    // mode == 1 -> draw; mode == 0 -> move
    qtview_paint(x,win_h-y,mode);
}

// should be moved somewhere else depends on xconv in draw.c //FIXME
int qtlibconvx(double x) 
{
    return ((int) (win_w * xconv(x)));
}

// should be moved somewhere else depends on yconv in draw.c //FIXME
int qtlibconvy(double y) // should be moved somewhere else
{
    return ((int) (win_h * yconv(y)));
}


void qtlibsetfont(int n)
{
    qtview_setfont(n);
}

int qtlibsetlinewidth(int width)
{
    if (width) {
        width = width % MAXLINEW;
        if (width == 0)
            width = 1;
        if (qtliblinestyle == 1) {
            qtview_linew(width);
        }
    }
    return (qtliblinewidth = width);
}

int qtlibsetlinestyle(int style)
{
    if (style > 1 && qtliblinewidth) {
        qtview_lines(style);
    } else if (style == 1 && qtliblinewidth) {
        qtview_lines(style);
    }
    return (qtliblinestyle = style);
}

int qtlibsetcolor(int color)
{
    color = color % maxcolors;
    qtview_linec(color);
    return color;
}

void qtlibdrawtic(int x, int y, int dir, int updown)
{
    switch (dir) {
    case 0:
        switch (updown) {
        case 0:
            drawqtlib(x, y, 0);
            drawqtlib(x, y + devxticl, 1);
            break;
        case 1:
            drawqtlib(x, y, 0);
            drawqtlib(x, y - devxticl, 1);
            break;
        }
        break;
    case 1:
        switch (updown) {
        case 0:
            drawqtlib(x, y, 0);
            drawqtlib(x + devyticl, y, 1);
            break;
        case 1:
            drawqtlib(x, y, 0);
            drawqtlib(x - devyticl, y, 1);
            break;
        }
        break;
    }
}

void qtlibwritestr(int x, int y, int rot, char *s, int just, int fudge)
{
    qtview_text(x,win_h-y,rot,s,just);
}

int qtlibsetpat(int pattern) {
    qtview_setpattern(pattern);
    return 0;// no idea why this is an int
}

void qtlibfill(int n, int px[], int py[]) {
    int pyh[n];
    int i;
    for (i = 0; i < n; i++) {
        pyh[i] = win_h - py[i];
    }
    qtview_fill(n, px, pyh);
}

void qtlibfillcolor(int n, int px[], int py[])
{
    int pyh[n];
    int i;
    for (i = 0; i < n; i++) {
        pyh[i] = win_h - py[i];
    }
    qtview_fillcolor(n, px, pyh);
}

void qtlibdrawarc(int x, int y, int r)
{
    qtview_arc(x,win_h-y,r,0);
}

void qtlibfillarc(int x, int y, int r)
{
    qtview_arc(x,win_h-y,r,1);
}

void qtlibdrawellipse(int x, int y, int xm, int ym) {
    qtview_drawellipse(x,y,xm,ym);
}

void qtlibfillellipse(int x, int y, int xm, int ym) {
    qtview_fillellipse(x,y,xm,ym);
}

int stringextentx(double scale, char* str) {
    return qtview_stringextentx(scale, str);
}


int stringextenty(double scale, char* str) {
    return qtview_stringextenty(scale, str);
}

void qtlibleavegraphics()
{   
    save_images = 0;
    qtview_update();
}


int qtlibinitgraphics(int dmode)
{
    npending = 0;
    if (dmode > 1) {
        save_images = 1;
        dmode = 0;
    }
    qtlibdmode = dmode;
    qtlibinit();
    
    devorient = 1;
    devconvx = qtlibconvx;
    devconvy = qtlibconvy;
    vector = drawqtlib;
    devwritestr = qtlibwritestr;
    devsetcolor = qtlibsetcolor;
    devsetfont = qtlibsetfont;
    devsetline = qtlibsetlinestyle;
    devsetlinew = qtlibsetlinewidth;
    devdrawtic = qtlibdrawtic;
    devsetpat = qtlibsetpat;
    devdrawarc = qtlibdrawarc;
    devfillarc = qtlibfillarc;
    devdrawellipse = qtlibdrawellipse;
    devfillellipse = qtlibfillellipse;
    devfill = qtlibfill;
    devfillcolor = qtlibfillcolor;
    devleavegraphics = qtlibleavegraphics;
    devxticl = 12*qtview_getsymsize();;
    devyticl = 12*qtview_getsymsize();;
    devarrowlength = 12*qtview_getsymsize();;
    devsymsize = 6*qtview_getsymsize();
    devcharsize = qtlibcharsize;

    // default values.
    qtlibsetcolor (1);
    qtlibsetlinestyle(1);

    npending = 0;
    return 0;
}

