/* $Id: xqtlib.c,v 0.1 26.12.2012 csto@lle.rochester.edu $
 *
 * driver for qtlib for gr
 *
 */

#include <stdio.h>
#include "externs.h"

//qtview interface methods
#include "graphwidget.h"

// extern void qtview_getcanvas(int*, int*);
// extern void qtview_paint(int,int,int,int);
// extern void qtview_linew(int);
// extern void qtview_lines(int);
// extern void qtview_linec(int);
// extern void qtview_text(int,int,int,char*,int);
// extern void qtview_arc(int,int,int,int);
// extern void qtview_fillcolor(int,int[],int[]);
// extern void qtview_clear();
// extern void qtview_update();

/* external variables */
// extern int use_colors;
// extern int use_defaultcmap;
// extern int revflag;		/* defined in main.c */
// extern int inwin;
// 
static int save_images;
// char saveimage_prstr[256] = "ACEgr.xwd";
// 
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
// 
// static void flush_pending();
// 
static int qtlibcolor = 1;
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


//imported from draw FIXME
double xconv(), yconv();

static void qtlibinit()
{
    double wx1, wx2, wy1, wy2;
    static int inc = 1;
    extern int invert, overlay, doclear, bgcolor;
    
    qtview_getcanvas(&win_w,&win_h);
    //   printf("qtlibinit %i %i\n",win_w,win_h);

    
    devwidth = win_w;
    devheight = win_h;
    qtview_clear();

    // 	xlibinit_tiles();
    //     if (doclear && !overlay) {
    // 	xlibsetcolor(bgcolor);
    // 	XFillRectangle(disp, displaybuff, gc, 0, 0, win_w, win_h);
    // 	if (backingstore) {
    // 	    XFillRectangle(disp, backpix, gc, 0, 0, win_w, win_h);
    // 	}
    //     }
}


// /*
//  * fix for dotted/dashed linestyles
//  */
// #define MAXL 1024
static int npending;
// XPoint polypoints[MAXL];
// 
// static unsigned char solid[1] = {1};
// static unsigned char dotted[2] = {3, 1};
// static unsigned char shortdashed[2] = {3, 3};
// static unsigned char longdashed[2] = {7, 7};
// static unsigned char dot_dashed[4] = {1, 3, 7, 3};
// 
// static unsigned char *dash_list[] = {
// 				     solid,
// 				     dotted,
// 				     shortdashed,
// 				     longdashed,
// 				     dot_dashed
// };
// 
// static int dash_list_length[] = {1, 2, 2, 2, 4};
// 
// /* scrunch the array of XPoints */
// static void xlib_scrunch(p, n)
//     XPoint *p;
//     int *n;
// {
//     int i, cnt = 0;
//     if (*n > 3) {
// 	cnt = 0;
// 	for (i = 1; i < *n; i++) {
// 	    if (p[cnt].x == p[i].x && p[cnt].y == p[i].y) {
// 	    } else {
// 		cnt++;
// 		p[cnt] = p[i];
// 	    }
// 	}
// 	cnt++;
// 	p[cnt] = p[*n - 1];
// 	if (cnt <= 2) {
// 	    cnt = 2;
// 	    p[1] = p[*n - 1];
// 	}
//     } else {
// 	cnt = *n;
//     }
//     *n = cnt;
// }
// 


static int x1, y1;
// 
void drawqtlib(int x, int y, int mode)
{
    //printf("drawxlib %i %i %i\n",x,y,mode);
    // mode == 1 -> draw; mode == 0 -> move
    if (mode) {
        qtview_paint(x1,win_h-y1,x,win_h-y);
    }
    x1 = x;
    y1 = y;
}

// should be moved somewhere else depends on xconv in draw.c //FIXME
int qtlibconvx(double x) 
{
    //     printf("qtlibconvx %f %i %f\n",x,win_w,xconv(x));
    return ((int) (win_w * xconv(x)));
}

// should be moved somewhere else depends on yconv in draw.c //FIXME
int qtlibconvy(double y) // should be moved somewhere else
{
    //     printf("qtlibconvy %f %i %f\n",y,win_h,yconv(y));
    return ((int) (win_h * yconv(y)));
}


void qtlibsetfont(int n)
{
    x1 = y1 = 99999;
    // TODO
}


// 
// /* NOTE: not called by xvgr */
// void xlibinitcmap()
// {
//     int i;
// 
//     ncolors = DisplayCells(disp, DefaultScreen(disp));
//     if (ncolors > 256) {
// 	ncolors = 256;
//     }
//     if (ncolors > 16) {
// 	cmap = DefaultColormap(disp, DefaultScreen(disp));
// 	for (i = 0; i < ncolors; i++) {
// 	    xc[i].pixel = i;
// 	    xc[i].flags = DoRed | DoGreen | DoBlue;
// 	}
// 	if (!use_defaultcmap) {
// 	    XQueryColors(disp, cmap, xc, ncolors);
// 	    mycmap = XCreateColormap(disp, xwin, DefaultVisual(disp, DefaultScreen(disp)), AllocAll);
// 	} else {
// 	    mycmap = cmap;
// 	}
// 	for (i = 2; i < maxcolors; i++) {
// 	    xc[i].red = red[i] << 8;
// 	    xc[i].green = green[i] << 8;
// 	    xc[i].blue = blue[i] << 8;
// 	    if (use_defaultcmap) {
// 		if (!XAllocColor(disp, cmap, &xc[i])) {
// 		    fprintf(stderr, " Can't allocate color\n");
// 		}
// 	    }
// 	    colors[i] = xc[i].pixel;
// 	}
// 	if (!use_defaultcmap) {
// 	    XStoreColors(disp, mycmap, xc, ncolors);
// 	}
//     }x
//     if (revflag) {
// 	colors[1] = WhitePixel(disp, DefaultScreen(disp));
// 	colors[0] = BlackPixel(disp, DefaultScreen(disp));
//     } else {
// 	colors[0] = WhitePixel(disp, DefaultScreen(disp));
// 	colors[1] = BlackPixel(disp, DefaultScreen(disp));
//     }
// }
// 
// void xlibsetcmap(i, r, g, b)
//     int i, r, g, b;
// {
//     XColor xct;
// 
//     red[i] = r;
//     green[i] = g;
//     blue[i] = b;
//     cmscolors[i].red = red[i];
//     cmscolors[i].green = green[i];
//     cmscolors[i].blue = blue[i];
//     if (inwin && use_colors > 4 && i >= 2) {
// 	xct.green = g << 8;
// 	xct.blue = b << 8;
// 	xct.red = r << 8;
// 	xct.flags = DoRed | DoGreen | DoBlue;
// 	xct.pixel = colors[i];
// 	xct.pad = 0;
// 
// #ifdef XVIEW
// 	xv_set(cms,
// 	       CMS_COLOR_COUNT, 1,
// 	       CMS_INDEX, i,
// 	       CMS_X_COLORS, &xct,
// 	       NULL);
// #endif
// #ifdef MOTIF
// 	XStoreColor(disp, mycmap, &xct);
// #endif
//     }
// }
// 
int qtlibsetlinewidth(int width)
{
    //      printf("qtlibsetlinewidth %i\n",w);
    x1 = y1 = 99999;
    if (width) {
        width = width % MAXLINEW;
        if (width == 0)
            width = 1;
        if (qtliblinestyle == 1) {
            qtview_linew(width);
        } else {
            //XSetLineAttributes(disp, gc, c - 1 == 0 ? 0 : c, LineOnOffDash, CapButt, JoinRound);
        }
    }
    return (qtliblinewidth = width);
}
// 
int qtlibsetlinestyle(int style)
{
    //      printf("qtlibsetlinestyle %i\n",style);
    x1 = y1 = 99999;
    if (style > 1 && qtliblinewidth) {
        // 	XSetLineAttributes(disp, gc, xliblinewidth - 1 ? 0 : xliblinewidth, LineOnOffDash, CapButt, JoinRound);
        // 	XSetDashes(disp, gc, 0, dash_list[style - 1], dash_list_length[style - 1]);
        qtview_lines(style);
    } else if (style == 1 && qtliblinewidth) {
        // 	XSetLineAttributes(disp, gc, xliblinewidth - 1 ? 0 : xliblinewidth, LineSolid, CapButt, JoinRound);
        qtview_lines(style);
    }
    return (qtliblinestyle = style);
}
// 
int qtlibsetcolor(int color)
{
    //     printf("qtlibsetcolor %i\n",color);
    x1 = y1 = 99999;
    color = color % maxcolors;
    qtview_linec(color);
    qtlibcolor = color;
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
{//csto 
    //     printf("qtlibwritestr %i %i %i %s %i \n",x, y, rot, s, just);
    x1 = y1 = 99999;
    //puthersh(x, y, qtlibcharsize * charsize, rot, just, qtlibcolor, drawqtlib, s);
    qtview_text(x,win_h-y,rot,s,just);
    x1 = y1 = 99999;
}

// #define MAXPATTERNS 16
// 
// static int patno = 0;
// x
// static Pixmap tiles[30];
// static Pixmap curtile;
// 
// void xlibinit_tiles()
// {
//     int i;
//     Pixmap ptmp;
// 
//     for (i = 0; i < MAXPATTERNS; i++) {
// 	tiles[i] = XCreatePixmap(disp, xwin, 16, 16, DisplayPlanes(disp, DefaultScreen(disp)));
//     }
//     for (i = 0; i < MAXPATTERNS; i++) {
// 	if (tiles[i] == NULL) {
// 	    printf("bad tile %d\n", i);
// 	} else {
// 	    XFillRectangle(disp, tiles[i], gcclr, 0, 0, 16, 16);
// 	}
//     }
//     ptmp = XCreateBitmapFromData(disp, xwin, pat0_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[0], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat1_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[1], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat2_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[2], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat3_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[3], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat4_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[4], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat5_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[5], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat6_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[6], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat7_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[7], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat8_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[8], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat9_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[97], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat10_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[10], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat11_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[11], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat12_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[12], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat13_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[173], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat14_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[14], gc, 0, 0, 16, 16, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, pat15_bits, 16, 16);
//     XCopyPlane(disp, ptmp, tiles[15], gc, 0, 0, 16, 16, 0, 0, 1);
// /*
//     ptmp = XCreateBitmapFromData(disp, xwin, bm17_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[16], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm18_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[17], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm19_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[18], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm20_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[19], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm21_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[20], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm22_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[21], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm23_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[22], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm24_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[23], gc, 0, 0, 6, 6, 0, 0, 1);
//     ptmp = XCreateBitmapFromData(disp, xwin, bm25_bits, 6, 6);
//     XCopyPlane(disp, ptmp, tiles[24], gc, 0, 0, 6, 6, 0, 0, 1);
// */
//     curtile = tiles[0];
// }
// 

int qtlibsetpat(int pattern) {
    qtview_setpattern(pattern);
    return 0;// no idea why this is an int
}

// int xlibsetpat(k)
//     int k;
// {
//     patno = k;
//     if (k > MAXPATTERNS) {
// 	k = 1;
//     }
//     if (patno != 0) {
// 	curtile = tiles[k - 1];
//     }
// }

void qtlibfill(int n, int px[], int py[]) {
    qtview_fill(n, px, py);
}

// void xlibfill(n, px, py)
//     int n;
//     int px[], py[];
// 
// {
//     int i, x, y;
//     XPoint *p;
// 
//     p = (XPoint *) calloc(n, sizeof(XPoint));
//     if (p == NULL) {
// 	return;
//     }
//     if (patno == 0) {
// 	return;
//     }
//     XSetFillStyle(disp, gc, FillTiled);
//     XSetTile(disp, gc, curtile);
//     for (i = 0; i < n; i++) {
// 	p[i].x = px[i];
// 	p[i].y = win_h - py[i];
//     }
//     XFillPolygon(disp, displaybuff, gc, p, n, Nonconvex, CoordModeOrigin);
//     if (backingstore) {
// 	XFillPolygon(disp, backpix, gc, p, n, Nonconvex, CoordModeOrigin);
//     }
//     XSetFillStyle(disp, gc, FillSolid);
//     cfree(p);
// }
// 
void qtlibfillcolor(int n, int px[], int py[])
{
    int i;

    //     printf("qtlibfillcolor %i %i %i \n",n, px[0], py[0]);
    for (i = 0; i < n; i++) {
        py[i] = win_h - py[i];
    }
    qtview_fillcolor(n, px, py);
}

void qtlibdrawarc(int x, int y, int r)
{
    //     printf("qtlibdrawarc %i %i %i \n",x, y, r);
    qtview_arc(x,win_h-y,r,0);
}

void qtlibfillarc(int x, int y, int r)
{
    //     printf("qtlibfillarc %i %i %i \n",x, y, r);
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
    //     printf("leavegraphics: start\n");
    x1 = y1 = 99999;
    save_images = 0;
    qtview_update();
}


int qtlibinitgraphics(int dmode)
{
    //     printf("initgraphics: start\n");
    npending = 0;
    x1 = 99999;
    y1 = 99999;
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
    devxticl = 12;
    devyticl = 12;
    devarrowlength = 12;
    devsymsize = 6;
    devcharsize = qtlibcharsize;
    //    (*devsetcolor) (1);
    //xlibsetlinestyle(1);
    //     printf("initgraphics: end\n");
    npending = 0;
    return 0;
}
// 
// /*
//  * cursors
//  */
// 
// #include <X11/cursorfont.h>
// 
// static Cursor wait_cursor;
// static Cursor line_cursor;
// static Cursor find_cursor;
// static Cursor move_cursor;
// static Cursor text_cursor;
// static Cursor kill_cursor;
// static int cur_cursor = -1;
// void set_cursor();
// 
// void set_wait_cursor(w)
// #ifdef MOTIF
//     Widget w;
// 
// #else
//     int w;
// 
// #endif
// {
//     XDefineCursor(disp, xwin, wait_cursor);
// #ifdef MOTIF
//     if (w != NULL) {
// 	XDefineCursor(disp, xwin, wait_cursor);
//     }
//     XtFlush();
// #endif
// }
// 
// void unset_wait_cursor(w)
// #ifdef MOTIF
//     Widget w;
// 
// #else
//     int w;
// 
// #endif
// {
//     if (cur_cursor == -1) {
// 	XUndefineCursor(disp, xwin);
// #ifdef MOTIF
// 	if (w != NULL) {
// 	    XUndefineCursor(disp, xwin);
// 	}
// #endif
//     } else {
// 	set_cursor(cur_cursor);
//     }
// }
// 
// void set_cursor(c)
//     int c;
// {
//     XUndefineCursor(disp, xwin);
//     cur_cursor = -1;
//     switch (c) {
//     case 0:
// 	XDefineCursor(disp, xwin, line_cursor);
// 	cur_cursor = 0;
// 	break;
//     case 1:
// 	XDefineCursor(disp, xwin, find_cursor);
// 	cur_cursor = 1;
// 	break;
//     case 2:
// 	XDefineCursor(disp, xwin, text_cursor);
// 	cur_cursor = 2;
// 	break;
//     case 3:
// 	XDefineCursor(disp, xwin, kill_cursor);
// 	cur_cursor = 3;
// 	break;
//     case 4:
// 	XDefineCursor(disp, xwin, move_cursor);
// 	cur_cursor = 4;
// 	break;
//     }
// }
// 
// void set_window_cursor(xwin, c)
//     Window xwin;
//     int c;
// {
//     XUndefineCursor(disp, xwin);
//     switch (c) {
//     case 0:
// 	XDefineCursor(disp, xwin, line_cursor);
// 	break;
//     case 1:
// 	XDefineCursor(disp, xwin, find_cursor);
// 	break;
//     case 2:
// 	XDefineCursor(disp, xwin, text_cursor);
// 	break;
//     case 3:
// 	XDefineCursor(disp, xwin, kill_cursor);
// 	break;
//     case 4:
// 	XDefineCursor(disp, xwin, move_cursor);
// 	break;
//     case 5:
// 	XDefineCursor(disp, xwin, wait_cursor);
// 	break;
//     }
// }
// 
// void init_cursors()
// {
//      wait_cursor = XCreateFontCursor(disp, XC_watch);
//     line_cursor = XCreateFontCursor(disp, XC_crosshair);
//     find_cursor = XCreateFontCursor(disp, XC_hand2);
//     text_cursor = XCreateFontCursor(disp, XC_xterm);
//     kill_cursor = XCreateFontCursor(disp, XC_pirate);
//     move_cursor = XCreateFontCursor(disp, XC_fleur);
//     cur_cursor = -1;
// }
