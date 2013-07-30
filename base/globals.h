/* $Id: globals.h,v 1.34 1993/02/06 04:48:55 pturner Exp pturner $
 *
 * Global variables for gr
 *
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __cplusplus 
extern "C" {
#endif

#include <stdlib.h>

//#ifndef XVGR_DEFINES_INCLUDED

#include "defines.h"

//#endif

/*
 * following for hardcopy device drivers
 */
extern int noerase;
extern char hp_prstr1[], hp_prstr2[], ps_prstr[], mif_prstr[], leaf_prstr[], noprint[];

extern int maxparms, maxfunc; /* declared in pars.y - symbol table lengths */
extern symtab_entry key[];

#ifdef MAIN

#ifdef XVIEW
char version[] = "Xvgr version 2.10a - PJ Turner OGI-ESE";
#endif
#ifdef MOTIF
char version[] = "Xmgr version 2.10 - PJ Turner OGI-ESE";
#endif

int debuglevel = 0;

int maxplot = MAXPLOT;
int maxarr = MAXARR;
int maxgraph = MAXGRAPH;
int maxcolors = MAXCOLORS;

int ptofile = 0;                /* flag to indicate destination of hardcopy
                                 * output, ptofile = 0 means print to printer
                                 * non-zero print to file */
char printstr[128] = "pout.dat";/* hardcopy to this file */

double *ax, *bx, *cx, *dx;	/* scratch arrays used in scanner */

int hardcopyflag = FALSE;	/* TRUE if printing out a hardcopy */

int inplotter = FALSE;		/* TRUE if plotting the current graph */

int showdefault = TRUE;		/* display the default graph */
int labeldefault = FALSE;	/* label the default graph */

char currentdir[1024];		/* current directory */

/*
 * scroll amount
 */
int scrolling_islinked = 0;	/* linked scroll */
double scrollper = 0.05;	/* scroll fraction */
double shexper = 0.05;		/* expand/shrink fraction */

char plfile[MAX_STRING_LENGTH];	/* load parameters file name */
char fname[MAX_STRING_LENGTH];	/* last data file read */

int device;			/* graphics device */
int tdevice = TDEV;		/* default devices */
int hdevice = HDEV;

int use_colors;			/* number of bitplanes */
int monomode = 0;		/* set mono mode */
int invert = 0;			/* use GXxor or GXinvert for xor'ing */
int backingstore = 0;		/* do backing store if requested */
int redraw_now = 0;		/* hack for no refresh on startup */
int autoscale_onread = 0;	/* autoscale after reading data from fileswin.c */
int allow_refresh = 1;		/* if no backing store, then redraw to refresh */

int erronread = FALSE;		/* in startup code was there an error on
				 * reading a data file, assume not  */
char progname[MAX_STRING_LENGTH];	/* our name */

int gflag = FALSE;		/* hacks for generic graphics drivers */
char gfile[MAX_STRING_LENGTH];	/* used if gflag set to true on command line */
char resfile[MAX_STRING_LENGTH];/* results to file resfile */
FILE *resfp;			/* file for results */

int inwin = FALSE;		/* true if running X */

int auto_redraw = TRUE;		/* if true, redraw graph each time action is
				 * performed */
int force_redraw = 0;		/* if no auto draw and re-draw pressed */

char buf[1024];			/* a string used here and there */

char *curprint;			/* the default printer */

int verify_action = 0;		/* request verification of actions if TRUE */
int allow_dc = 1;		/* allow double click ops */

/* graph definition */
graph *g;
int cg = 0;			/* the current graph */
int cset = 0;			/* the current set csto*/


/* region definition */
region rg[MAXREGION];
int nr = 0;			/* the current region */

plotstr pstr[MAXSTR];       /* strings */
boxtype boxes[MAXBOXES];    /* boxes */
linetype lines[MAXLINES];   /* lines */

/* lines and boxes flags */
int box_color = 1;
int box_lines = 1;
int box_linew = 1;
int box_fill = NONE;
int box_fillpat = 1;
int box_fillcolor = 1;
int box_loctype = VIEW;

int line_color = 1;
int line_arrow = 0;
int line_lines = 1;
int line_linew = 1;
int line_loctype = VIEW;
double line_asize = 1.0;
int line_atype = 0;

/* default string parameters */
int string_color = 1;
int string_linew = 1;
int string_font = 4;
int string_rot = 0;
int string_just = 0;
int string_fill = NONE;
int string_fillpat = 1;
int string_fillcolor = 1;
int string_loctype = VIEW;
double string_size = 1.0;

int curset, curaxis;
int focus_policy = CLICK;

int use_defaultcmap = 1;
int revflag = 0;

int draw_focus_flag = ON;

int graph_focus = 0;

int slice_grid = 0;
int slice_graph = 0;
int slice_setno = 0;
int slicepath_setno = 0;
int slice_load = 0;
int slice_npts = 0;
int slice_first = TRUE;

int page_layout = FREE;

plotstr timestamp;       /* timestamp */

/*
 * for the status popup
 */
int cur_statusitem = SETS;

/*
 * used in the parser
 */
int cursource = DISK, curtype = XY;

int format_types[] = { DECIMAL, EXPONENTIAL, POWER, GENERAL,
			DDMMYY, MMDDYY, MMYY, MMDD,
        		MONTHDAY, DAYMONTH, MONTHS, MONTHL, DAYOFWEEKS,
        		DAYOFWEEKL, DAYOFYEAR, HMS, MMDDHMS, MMDDYYHMS,
        		DEGREESLON, DEGREESMMLON, DEGREESMMSSLON, MMSSLON,
        		DEGREESLAT, DEGREESMMLAT, DEGREESMMSSLAT, MMSSLAT, 0};
			
//defaults
extern void set_program_defaults();	// csto		

#endif

#ifndef MAIN

extern char *open_err_msg;

extern char version[];

extern int debuglevel;

extern int inwin;		/* true if running X */
extern int ispipe;		/* true if reading from stdin */

extern int maxarr, maxplot, maxgraph, maxcolors;
extern int ptofile;             /* set to TRUE if printing to a file */
extern char printstr[];         /* print to this file */

extern char plfile[], psfile[];
extern char resfile[];
extern FILE *resfp;

extern int device, tdevice, hdevice;
extern int hardcopyflag;

extern int use_colors;		/* number of bitplanes */
extern int monomode;		/* set mono mode */
extern int invert;		/* use GXxor or GXinvert for xor'ing */
extern int backingstore;	/* do backing store if requested */
extern int redraw_now;		/* hack for no refresh on startup */
extern int autoscale_onread;	/* autoscale after reading data from fileswin.c */
extern int allow_refresh;	/* if no backingstore, then redraw to refresh */

extern int inplotter;

extern int showdefault;
extern int labeldefault;

extern char currentdir[];	/* current directory */

extern int scrolling_islinked;	/* linked scroll */
extern double scrollper;	/* scroll fraction */
extern double shexper;		/* expand/shrink fraction */

extern double errbarper;

extern char fname[];
extern int nsets;
extern char buf[];

extern char *curprint;

extern int verify_action;	/* request verification of actions if TRUE */
extern int allow_dc;		/* allow double click ops */

extern double *ax, *bx, *cx, *dx;

/* graph definition */
extern graph *g;
extern int cg;
extern int cset;

/* region definition */
extern region rg[];
extern int nr;

extern plotstr pstr[];       /* strings */
extern boxtype boxes[];    /* boxes */
extern linetype lines[];   /* lines */

extern int box_color;
extern int box_lines;
extern int box_linew;
extern int box_fill;
extern int box_fillpat;
extern int box_fillcolor;
extern int box_loctype;

extern int line_color;
extern int line_arrow;
extern int line_lines;
extern int line_linew;
extern int line_loctype;
extern double line_asize;
extern int line_atype;

extern int string_color;
extern int string_linew;
extern int string_font;
extern int string_rot;
extern int string_just;
extern int string_fill;
extern int string_fillpat;
extern int string_fillcolor;
extern int string_loctype;
extern double string_size;

extern int auto_redraw;
extern int force_redraw;

extern double charsize, xlibcharsize;	/* declared in draw.c and xlib.c resp. */

extern int curset, curaxis;
extern int focus_policy;
extern int draw_focus_flag;
extern int graph_focus;
extern int use_defaultcmap;
extern int revflag;

extern plotstr timestamp;       /* timestamp */
extern int page_layout;

extern int slice_grid;
extern int slice_graph;
extern int slice_setno;
extern int slicepath_setno;
extern int slice_load;
extern int slice_npts;
extern int slice_first;

extern int cur_statusitem;

extern int cursource, curtype;
extern int format_types[];

extern void errwin(char *);
extern int yesno(const char *, const char *, const char *, const char *);
extern void cxfree(void *);
extern void lowtoupper(char *);
extern void convertchar(char *);
extern void read_param(char *);

//defaults
extern void set_default_graph(int gno);

//events
extern void drawgraph();

// draw
extern void view2world(double vx, double vy, double *wx, double *wy);

//drawutils
extern void autoscale_proc();


//files 
extern int getdata(int gno, char* fn, int src, int type);

//graphutils
extern void wipeout(int ask);
extern void set_graph_active(int gno);
extern void get_graph_legend(int gno, legend* leg);
extern void set_graph_legend(int gno, legend* leg);
extern int get_format_index(int f);
extern void default_axis(int gno, int method, int axis);

//setprops
extern void set_prop(int gno,...);

//setutils
extern int nextset(int);
extern void activateset(int , int );
extern void setcol(int gno, double *x, int setno, int len, int col);
extern void updatesetminmax(int gno, int setno);

//computils

extern double do_int(int setno, int itype);//integration
extern void do_compute(int setno, int loadto, int graphto, char* fstr);//expression
extern void do_digfilter(int set1, int set2);//digital filter
extern void do_linearc(int set1, int set2);// linear convolve
extern void do_xcor(int set1, int set2, int itype, int lag); // cross correlation (itype true false)
extern void do_spline(int set, double start, double stop, int n); // splines
extern void do_differ(int setno, int itype); // difference (0 forward, 1 back, 2 center)
extern void do_regress(int setno, int ideg, int iresid); // regression
extern void do_runavg(int setno, int runlen, int runtype); // 0 avg 1 median 2 min 3 max 4 stdev
extern void do_fourier(int fftflag,int setno, int load, int loadx, int invflag,
                       int type, int wind); // fourier
extern void do_window(int setno, int type, int wind); // window
extern void do_histo(int hset, double binw, double xmin, double xmax,
                     int hist_type); // histogram
extern void do_sample(int setno, int typeno, char* exprstr,
                      int startno, int stepno); // sample set

// utils

extern void fswap(double*, double*);

#endif

#ifdef __cplusplus 
} // extern C
#endif

#endif // GLOBALS_H
