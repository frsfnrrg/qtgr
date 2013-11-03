
# line 2 "pars.yacc"

/* $Id: pars.c,v 1.3 1993/03/10 16:33:22 pturner Exp pturner $
 * 
 * evaluate expressions, commands, parameter files
 * 
 */

#define PARS			/* to overide some defines in defines.h */


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "globals.h"

#ifndef M_PI
#     define M_PI  3.14159265358979323846
#endif

#ifndef TRUE
#     define TRUE 1
#endif

#ifndef FALSE
#     define FALSE 0
#endif

double result, resx, resy;	/* return value if expression */
double nonl_parms[10];

double drand48();
long lrand48();

double rnorm(), fx(), normp(), invnorm(), invt();
void yyerror();

static int interr;

static double *freelist[100]; 	/* temporary vectors */
static int fcnt;		/* number allocated */

int naxis = 0;	/* current axis */
int curline, curbox, curstring, curleg, curgrid;

int gotbatch, gotparams, gotread; /* these guys attempt to avoid reentrancy problems */
int readtype, readsrc;
char batchfile[256], paramfile[256], readfile[256];

static char f_string[512];	/* buffer for string to parse */
static int pos = 0;
static double *aa, *bb, *cc, *dd, *xx, *yy;
static int setindex, lxy, ls;
static int setsetno;
static int whichgraph;
static int whichset;

extern int change_gno;
extern int change_type;


# line 63 "pars.yacc"
typedef union  {
    double val;
    int ival;
    double *ptr;
    int func;
    int pset;
    char *str;
} YYSTYPE;
# define ABS 257
# define ACOS 258
# define ASIN 259
# define ATAN 260
# define ATAN2 261
# define CEIL 262
# define COS 263
# define DEG 264
# define DX 265
# define DY 266
# define ERF 267
# define ERFC 268
# define EXP 269
# define FLOOR 270
# define HYPOT 271
# define INDEX 272
# define INT 273
# define INVN 274
# define INVT 275
# define IRAND 276
# define LGAMMA 277
# define LN 278
# define LOG 279
# define LOGISTIC 280
# define MAXP 281
# define MINP 282
# define MOD 283
# define NORM 284
# define NORMP 285
# define PI 286
# define RAD 287
# define RAND 288
# define RNORM 289
# define SETNO 290
# define SIN 291
# define SQR 292
# define SQRT 293
# define TAN 294
# define INUM 295
# define VX1 296
# define VX2 297
# define VY1 298
# define VY2 299
# define WX1 300
# define WX2 301
# define WY1 302
# define WY2 303
# define DELAYP 304
# define DOUBLEBUFFER 305
# define DOWN 306
# define ABSOLUTE 307
# define ABORT 308
# define ACTIVATE 309
# define ACTIVE 310
# define ALT 311
# define ALTERNATE 312
# define ALTXAXIS 313
# define ALTYAXIS 314
# define ANGLE 315
# define ANNOTATE 316
# define APPEND 317
# define AREA 318
# define ARROW 319
# define AUTO 320
# define AUTOSCALE 321
# define AUTOTICKS 322
# define AVG 323
# define AXIS 324
# define AXES 325
# define BACKBUFFER 326
# define BACKGROUND 327
# define BAR 328
# define BATCH 329
# define BLOCK 330
# define BIN 331
# define BOTH 332
# define BOTTOM 333
# define BOX 334
# define CELLS 335
# define CENTER 336
# define CHAR 337
# define CHRSTR 338
# define CLEAR 339
# define CLICK 340
# define CMAP 341
# define COLOR 342
# define COMMENT 343
# define COPY 344
# define CYCLE 345
# define DECIMAL 346
# define DEF 347
# define DEFAULT 348
# define DELETE 349
# define DEVICE 350
# define DFT 351
# define DIFFERENCE 352
# define DISK 353
# define DRAW2 354
# define DXDX 355
# define DXP 356
# define DYDY 357
# define DYP 358
# define ECHO 359
# define EDIT 360
# define ELSE 361
# define END 362
# define ERRORBAR 363
# define EXIT 364
# define EXPONENTIAL 365
# define FALSEP 366
# define FFT 367
# define FILEP 368
# define FILL 369
# define FIND 370
# define FIXEDPOINT 371
# define FLUSH 372
# define FOCUS 373
# define FOLLOWS 374
# define FONTP 375
# define FOREGROUND 376
# define FORMAT 377
# define FRONTBUFFER 378
# define FRAMEP 379
# define GETP 380
# define GRAPH 381
# define GRAPHNO 382
# define GRAPHS 383
# define GRAPHTYPE 384
# define GRID 385
# define HARDCOPY 386
# define HBAR 387
# define HGAP 388
# define HIDDEN 389
# define HORIZONTAL 390
# define HPGLL 391
# define HPGLP 392
# define HISTO 393
# define IF 394
# define IGNORE 395
# define IHL 396
# define IN 397
# define INIT 398
# define INITGRAPHICS 399
# define INOUT 400
# define INTEGRATE 401
# define INTERP 402
# define INVDFT 403
# define INVFFT 404
# define JUST 405
# define KILL 406
# define LABEL 407
# define LAYOUT 408
# define LEAVE 409
# define LEAVEGRAPHICS 410
# define LEFT 411
# define LEGEND 412
# define LENGTH 413
# define LEVEL 414
# define LEVELS 415
# define LINE 416
# define LINESTYLE 417
# define LINETO 418
# define LINEWIDTH 419
# define LINK 420
# define LOAD 421
# define LOCATOR 422
# define LOCTYPE 423
# define LOGX 424
# define LOGY 425
# define LOGXY 426
# define MAJOR 427
# define MIFL 428
# define MIFP 429
# define MINOR 430
# define MISSINGP 431
# define MOVE 432
# define MOVE2 433
# define MOVETO 434
# define NEGATE 435
# define NO 436
# define NONE 437
# define NORMAL 438
# define NXY 439
# define OFF 440
# define OFFSETX 441
# define OFFSETY 442
# define ON 443
# define OP 444
# define ORIENT 445
# define OUT 446
# define PAGE 447
# define PARA 448
# define PARALLEL 449
# define PARAMETERS 450
# define PARAMS 451
# define PATTERN 452
# define PERIMETER 453
# define PERP 454
# define PERPENDICULAR 455
# define PIE 456
# define PIPE 457
# define PLACE 458
# define POINT 459
# define POLAR 460
# define POWER 461
# define PREC 462
# define PREPEND 463
# define PRINT 464
# define PS 465
# define PSCOLORP 466
# define PSMONOP 467
# define PSCOLORL 468
# define PSMONOL 469
# define PUSH 470
# define POP 471
# define PUTP 472
# define READ 473
# define REDRAW 474
# define REGRESS 475
# define REGNUM 476
# define REGIONS 477
# define RENDER 478
# define REVERSE 479
# define RIGHT 480
# define RISER 481
# define ROT 482
# define RUNAVG 483
# define RUNMED 484
# define RUNSTD 485
# define RUNMIN 486
# define RUNMAX 487
# define SAMPLE 488
# define SCALE 489
# define SCIENTIFIC 490
# define SET 491
# define SETNUM 492
# define SETS 493
# define SIGN 494
# define SIZE 495
# define SKIP 496
# define SLEEP 497
# define SLICE 498
# define SOURCE 499
# define SPEC 500
# define SPECIFIED 501
# define SPECTRUM 502
# define STACK 503
# define STACKEDBAR 504
# define STACKEDHBAR 505
# define STACKEDLINE 506
# define STAGGER 507
# define START 508
# define STARTTYPE 509
# define STATUS 510
# define STOP 511
# define STRING 512
# define SUBTITLE 513
# define SWAPBUFFER 514
# define SYMBOL 515
# define TICK 516
# define TICKLABEL 517
# define TICKMARKS 518
# define TITLE 519
# define TO 520
# define TOP 521
# define TRUEP 522
# define TYPE 523
# define UP 524
# define VELOCITY 525
# define VERTICAL 526
# define VGAP 527
# define VIEW 528
# define WITH 529
# define WORLD 530
# define WRITE 531
# define X1 532
# define X2 533
# define X3 534
# define X4 535
# define X5 536
# define XAXES 537
# define XAXIS 538
# define XCOR 539
# define XMAX 540
# define XMIN 541
# define XY 542
# define XYARC 543
# define XYBOX 544
# define XYFIXED 545
# define XYHILO 546
# define XYRT 547
# define XYSEG 548
# define XYSTRING 549
# define XYDX 550
# define XYDY 551
# define XYDXDX 552
# define XYDYDY 553
# define XYDXDY 554
# define XYX2Y2 555
# define XYXX 556
# define XYYY 557
# define XYZ 558
# define XYZW 559
# define XYUV 560
# define Y1 561
# define Y2 562
# define Y3 563
# define Y4 564
# define Y5 565
# define YAXES 566
# define YAXIS 567
# define YES 568
# define YMAX 569
# define YMIN 570
# define ZEROXAXIS 571
# define ZEROYAXIS 572
# define ABOVE 573
# define BELOW 574
# define POLYI 575
# define POLYO 576
# define GENERAL 577
# define DDMMYY 578
# define MMDDYY 579
# define MMYY 580
# define MMDD 581
# define MONTHDAY 582
# define DAYMONTH 583
# define MONTHS 584
# define MONTHL 585
# define DAYOFWEEKS 586
# define DAYOFWEEKL 587
# define DAYOFYEAR 588
# define HMS 589
# define MMDDHMS 590
# define MMDDYYHMS 591
# define DEGREESLON 592
# define DEGREESMMLON 593
# define DEGREESMMSSLON 594
# define MMSSLON 595
# define DEGREESLAT 596
# define DEGREESMMLAT 597
# define DEGREESMMSSLAT 598
# define MMSSLAT 599
# define DOT 600
# define STAR 601
# define PLUS 602
# define CROSS 603
# define CIRCLE 604
# define SQUARE 605
# define DIAMOND 606
# define TRIANGLE1 607
# define TRIANGLE2 608
# define TRIANGLE3 609
# define TRIANGLE4 610
# define SPLINE 611
# define SVAR 612
# define VAR 613
# define X 614
# define Y 615
# define NUMBER 616
# define FITPARM 617
# define OR 618
# define AND 619
# define GT 620
# define LT 621
# define LE 622
# define GE 623
# define EQ 624
# define NE 625
# define UMINUS 626
# define NOT 627
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
typedef int yytabelem;
# define YYERRCODE 256

# line 3387 "pars.yacc"


void fixupstr(val)
    char *val;
{
    int vl = strlen(val);
    lowtoupper(val);
    val[vl + 1] = 0;
    val[vl] = '\n';
}

void scanner(s, x, y, len, a, b, c, d, lenscr, i, setno, errpos)
    char s[];
    double *x, *y, *a, *b, *c, *d;
    int i, len, lenscr, setno, *errpos;

{
    interr = 0;
    whichgraph = cg;
    whichset = setno;
    if (s[0] == '#') {
	return;
    }
    pos = 0;
    aa = a;
    bb = b;
    cc = c;
    dd = d;
    xx = x;
    yy = y;
    lxy = len;
    ls = lenscr;
    setindex = i + 1;
    curset = setsetno = setno;
    strcpy(f_string, s);
    fcnt = 0;
    yyparse();
    *errpos = interr;
    for (i = 0; i < fcnt; i++) {
	cfree(freelist[i]);
	freelist[i] = NULL;
    }
}

void runbatch(bfile)
char *bfile;
{
    double x, y, a, b, c, d;
    int i, setno, errpos, lcnt = 1;
    char stext[256];
    FILE *fp;
    if (strcmp("stdin", bfile)) {
	fp = fopen(bfile, "r");
    }
    else {
	fp = stdin;
    }
    if (fp == NULL) {
        fprintf(stderr, "Error opening batch file \"%s\"\n", bfile);
        exit(1);
    }
    while(fgets(stext, 255, fp) != NULL) {
        if (stext[0] == '#') {
            continue;
        }
        lowtoupper(stext);
/* TODO check on 0, 0 here for index and setno */
        scanner(stext, &x, &y, 1, ax, bx, cx, dx, 1, 0, 0, &errpos);
        stext[0] = 0;
        if (gotparams && paramfile[0]) {
            if (!getparms(cg, paramfile)) {
            }
            gotparams = 0;
        } else if (gotread && readfile[0]) {
            if (getdata(cg, readfile, readsrc, readtype)) {
                drawgraph();
            }
            gotread = 0;
        }
    }
    if (fp != stdin) {
	fclose(fp);
    }
}

#define MAXFUN 371

int maxparms = MAXFUN;
int maxfunc = MAXFUN;

symtab_entry key[] = {
	"A", VAR,
	"A0", FITPARM,
	"A1", FITPARM,
	"A2", FITPARM,
	"A3", FITPARM,
	"A4", FITPARM,
	"A5", FITPARM,
	"A6", FITPARM,
	"A7", FITPARM,
	"A8", FITPARM,
	"A9", FITPARM,
	"ABORT", ABORT,
	"ABOVE", ABOVE,
	"ABS", ABS,
	"ABSOLUTE", ABSOLUTE,
	"ACOS", ACOS,
	"ACTIVATE", ACTIVATE,
	"ACTIVE", ACTIVE,
	"ALT", ALT,
	"ALTERNATE", ALTERNATE,
	"ALTXAXIS", ALTXAXIS,
	"ALTYAXIS", ALTYAXIS,
	"AND", AND,
	"ANGLE", ANGLE,
	"ANNOTATE", ANNOTATE,
	"APPEND", APPEND,
	"AREA", AREA,
	"ARROW", ARROW,
	"ASIN", ASIN,
	"ATAN", ATAN,
	"ATAN2", ATAN2,
	"AUTO", AUTO,
	"AUTOSCALE", AUTOSCALE,
	"AUTOTICKS", AUTOTICKS,
	"AVG", AVG,
	"AXES", AXES,
	"AXIS", AXIS,
	"B", VAR,
	"BACKBUFFER", BACKBUFFER,
	"BACKGROUND", BACKGROUND,
	"BAR", BAR,
	"BATCH", BATCH,
	"BELOW", BELOW,
	"BIN", BIN,
	"BLOCK", BLOCK,
	"BOTH", BOTH,
	"BOTTOM", BOTTOM,
	"BOX", BOX,
	"C", VAR,
	"CEIL", CEIL,
	"CELLS", CELLS,
	"CENTER", CENTER,
	"CHAR", CHAR,
	"CHRSTR", CHRSTR,
	"CLEAR", CLEAR,
	"CLICK", CLICK,
	"CMAP", CMAP,
	"CO", COLOR,
	"COLOR", COLOR,
	"COMMENT", COMMENT,
	"COPY", COPY,
	"COS", COS,
	"CYCLE", CYCLE,
	"D", VAR,
	"DAYMONTH", DAYMONTH,
	"DAYOFWEEKL", DAYOFWEEKL,
	"DAYOFWEEKS", DAYOFWEEKS,
	"DAYOFYEAR", DAYOFYEAR,
	"DDMMYY", DDMMYY,
	"DECIMAL", DECIMAL,
	"DEF", DEF,
	"DEFAULT", DEFAULT,
	"DEG", DEG,
	"DEGREESLAT", DEGREESLAT,
	"DEGREESLON", DEGREESLON,
	"DEGREESMMLAT", DEGREESMMLAT,
	"DEGREESMMLON", DEGREESMMLON,
	"DEGREESMMSSLAT", DEGREESMMSSLAT,
	"DEGREESMMSSLON", DEGREESMMSSLON,
	"DELAY", DELAYP,
	"DELETE", DELETE,
	"DEVICE", DEVICE,
	"DFT", DFT,
	"DIFF", DIFFERENCE,
	"DIFFERENCE", DIFFERENCE,
	"DISK", DISK,
	"DOUBLEBUFFER", DOUBLEBUFFER,
	"DOWN", DOWN,
	"DRAW2", DRAW2,
	"DX", DX,
	"DXDX", DXDX,
	"DY", DY,
	"DYDY", DYDY,
	"ECHO", ECHO,
	"EDIT", EDIT,
	"ELSE", ELSE,
	"END", END,
	"EQ", EQ,
	"ER", ERRORBAR,
	"ERF", ERF,
	"ERFC", ERFC,
	"ERRORBAR", ERRORBAR,
	"EXIT", EXIT,
	"EXP", EXP,
	"EXPONENTIAL", EXPONENTIAL,
	"FALSE", FALSEP,
	"FFT", FFT,
	"FILE", FILEP,
	"FILL", FILL,
	"FIND", FIND,
	"FIXEDPOINT", FIXEDPOINT,
	"FLOOR", FLOOR,
	"FLUSH", FLUSH,
	"FOCUS", FOCUS,
	"FOLLOWS", FOLLOWS,
	"FONT", FONTP,
	"FOREGROUND", FOREGROUND,
	"FORMAT", FORMAT,
	"FRAME", FRAMEP,
	"FRONTBUFFER", FRONTBUFFER,
	"GE", GE,
	"GENERAL", GENERAL,
	"GETP", GETP,
	"GRAPH", GRAPH,
	"GRAPHS", GRAPHS,
	"GRAPHTYPE", GRAPHTYPE,
	"GRID", GRID,
	"GT", GT,
	"HARDCOPY", HARDCOPY,
	"HBAR", HBAR,
	"HGAP", HGAP,
	"HIDDEN", HIDDEN,
	"HISTO", HISTO,
	"HMS", HMS,
	"HORIZONTAL", HORIZONTAL,
	"HPGLL", HPGLL,
	"HPGLP", HPGLP,
	"HYPOT", HYPOT,
	"IF", IF,
	"IGNORE", IGNORE,
	"IHL", IHL,
	"IN", IN,
	"INDEX", INDEX,
	"INIT", INIT,
	"INITGRAPHICS", INITGRAPHICS,
	"INOUT", INOUT,
	"INT", INT,
	"INTEGRATE", INT,
	"INTERP", INTERP,
	"INUM", INUM,
	"INVDFT", INVDFT,
	"INVFFT", INVFFT,
	"INVN", INVN,
	"INVT", INVT,
	"IRAND", IRAND,
	"JUST", JUST,
	"KILL", KILL,
	"LABEL", LABEL,
	"LAYOUT", LAYOUT,
	"LE", LE,
	"LEAVE", LEAVE,
	"LEAVEGRAPHICS", LEAVEGRAPHICS,
	"LEFT", LEFT,
	"LEGEND", LEGEND,
	"LENGTH", LENGTH,
	"LEVEL", LEVEL,
	"LEVELS", LEVELS,
	"LGAMMA", LGAMMA,
	"LINE", LINE,
	"LINESTYLE", LINESTYLE,
	"LINETO", LINETO,
	"LINEWIDTH", LINEWIDTH,
	"LINK", LINK,
	"LN", LN,
	"LOAD", LOAD,
	"LOCATOR", LOCATOR,
	"LOCTYPE", LOCTYPE,
	"LOG", LOG,
	"LOGISTIC", LOGISTIC,
	"LOGX", LOGX,
	"LOGXY", LOGXY,
	"LOGY", LOGY,
	"LS", LINESTYLE,
	"LT", LT,
	"LW", LINEWIDTH,
	"MAJOR", MAJOR,
	"MAX", MAXP,
	"MIFL", MIFL,
	"MIFP", MIFP,
	"MIN", MINP,
	"MINOR", MINOR,
	"MISSING", MISSINGP,
	"MMDD", MMDD,
	"MMDDHMS", MMDDHMS,
	"MMDDYY", MMDDYY,
	"MMDDYYHMS", MMDDYYHMS,
	"MMSSLAT", MMSSLAT,
	"MMSSLON", MMSSLON,
	"MMYY", MMYY,
	"MOD", MOD,
	"MONTHDAY", MONTHDAY,
	"MONTHL", MONTHL,
	"MONTHS", MONTHS,
	"MOVE", MOVE,
	"MOVE2", MOVE2,
	"MOVETO", MOVETO,
	"NE", NE,
	"NEGATE", NEGATE,
	"NO", NO,
	"NONE", NONE,
	"NORM", NORM,
	"NORMAL", NORMAL,
	"NORMP", NORMP,
	"NOT", NOT,
	"NUMBER", NUMBER,
	"NXY", NXY,
	"OFF", OFF,
	"OFFSETX", OFFSETX,
	"OFFSETY", OFFSETY,
	"ON", ON,
	"OP", OP,
	"OR", OR,
	"ORIENT", ORIENT,
	"OUT", OUT,
	"PAGE", PAGE,
	"PARA", PARA,
	"PARALLEL", PARALLEL,
	"PARAMETERS", PARAMETERS,
	"PARAMS", PARAMS,
	"PATTERN", PATTERN,
	"PERIMETER", PERIMETER,
	"PERP", PERP,
	"PERPENDICULAR", PERPENDICULAR,
	"PI", PI,
	"PIE", PIE,
	"PIPE", PIPE,
	"PLACE", PLACE,
	"POINT", POINT,
	"POLAR", POLAR,
	"POLYI", POLYI,
	"POLYO", POLYO,
	"POP", POP,
	"POWER", POWER,
	"PREC", PREC,
	"PREPEND", PREPEND,
	"PRINT", PRINT,
	"PS", PS,
	"PSCOLORL", PSCOLORL,
	"PSCOLORP", PSCOLORP,
	"PSMONOL", PSMONOL,
	"PSMONOP", PSMONOP,
	"PUSH", PUSH,
	"PUTP", PUTP,
	"RAD", RAD,
	"RAND", RAND,
	"READ", READ,
	"REDRAW", REDRAW,
	"REGRESS", REGRESS,
	"RENDER", RENDER,
	"REVERSE", REVERSE,
	"RIGHT", RIGHT,
	"RISER", RISER,
	"RNORM", RNORM,
	"ROT", ROT,
	"RUNAVG", RUNAVG,
	"RUNMAX", RUNMAX,
	"RUNMED", RUNMED,
	"RUNMIN", RUNMIN,
	"RUNSTD", RUNSTD,
	"SAMPLE", SAMPLE,
	"SCALE", SCALE,
	"SCIENTIFIC", SCIENTIFIC,
	"SET", SET,
	"SETNO", SETNO,
	"SETS", SETS,
	"SIGN", SIGN,
	"SIN", SIN,
	"SIZE", SIZE,
	"SKIP", SKIP,
	"SLEEP", SLEEP,
	"SLICE", SLICE,
	"SOURCE", SOURCE,
	"SPEC", SPEC,
	"SPECIFIED", SPECIFIED,
	"SPECTRUM", SPECTRUM,
	"SPLINE", SPLINE,
	"SQR", SQR,
	"SQRT", SQRT,
	"STACK", STACK,
	"STACKEDBAR", STACKEDBAR,
	"STACKEDHBAR", STACKEDHBAR,
	"STACKEDLINE", STACKEDLINE,
	"STAGGER", STAGGER,
	"START", START,
	"STARTTYPE", STARTTYPE,
	"STATUS", STATUS,
	"STOP", STOP,
	"STRING", STRING,
	"SUBTITLE", SUBTITLE,
	"SVAR", SVAR,
	"SWAPBUFFER", SWAPBUFFER,
	"SYMBOL", SYMBOL,
	"TAN", TAN,
	"TICK", TICK,
	"TICKLABEL", TICKLABEL,
	"TICKMARKS", TICKMARKS,
	"TITLE", TITLE,
	"TO", TO,
	"TOP", TOP,
	"TRUE", TRUEP,
	"TYPE", TYPE,
	"UP", UP,
	"VAR", VAR,
	"VELOCITY", VELOCITY,
	"VERTICAL", VERTICAL,
	"VGAP", VGAP,
	"VIEW", VIEW,
	"VX1", VX1,
	"VX2", VX2,
	"VY1", VY1,
	"VY2", VY2,
	"WITH", WITH,
	"WORLD", WORLD,
	"WRITE", WRITE,
	"WX1", WX1,
	"WX2", WX2,
	"WY1", WY1,
	"WY2", WY2,
	"X", SVAR,
	"X1", X1,
	"X2", X2,
	"X3", X3,
	"X4", X4,
	"X5", X5,
	"XAXES", XAXES,
	"XAXIS", XAXIS,
	"XCOR", XCOR,
	"XMAX", XMAX,
	"XMIN", XMIN,
	"XY", XY,
	"XYARC", XYARC,
	"XYBOX", XYBOX,
	"XYDX", XYDX,
	"XYDXDX", XYDXDX,
	"XYDXDY", XYDXDY,
	"XYDY", XYDY,
	"XYDYDY", XYDYDY,
	"XYFIXED", XYFIXED,
	"XYHILO", XYHILO,
	"XYRT", XYRT,
	"XYSEG", XYSEG,
	"XYSTRING", XYSTRING,
	"XYUV", XYUV,
	"XYX2Y2", XYX2Y2,
	"XYXX", XYXX,
	"XYYY", XYYY,
	"XYZ", XYZ,
	"XYZW", XYZW,
	"Y", SVAR,
	"Y1", Y1,
	"Y2", Y2,
	"Y3", Y3,
	"Y4", Y4,
	"Y5", Y5,
	"YAXES", YAXES,
	"YAXIS", YAXIS,
	"YES", YES,
	"YMAX", YMAX,
	"YMIN", YMIN,
	"ZEROXAXIS", ZEROXAXIS,
	"ZEROYAXIS", ZEROYAXIS,
};

int findf(key, s, tlen)
    symtab_entry key[];
    char *s;
    int tlen;
{

    int low, high, mid;

    low = 0;
    high = tlen - 1;
    while (low <= high) {
	mid = (low + high) / 2;
	if (strcmp(s, key[mid].s) < 0) {
	    high = mid - 1;
	} else {
	    if (strcmp(s, key[mid].s) > 0) {
		low = mid + 1;
	    } else {
		return (mid);
	    }
	}
    }
    return (-1);
}

int getcharstr()
{
    if (pos >= strlen(f_string))
	 return EOF;
    return (f_string[pos++]);
}

void ungetchstr()
{
    if (pos > 0)
	pos--;
}

int yylex()
{
    int c, i;
    int found;
    static char s[256];
    char sbuf[256];

    while ((c = getcharstr()) == ' ' || c == '\t');
    if (c == EOF) {
	return (0);
    }

    if (c == '"') {
	i = 0;
	while ((c = getcharstr()) != '"' && c != EOF) {
	    if (c == '\\') {
		int ctmp;
		ctmp = getcharstr();
		if (ctmp != '"') {
		    ungetchstr();
		}
		else {
		    c = ctmp;
		}
	    }
	    s[i] = c;
	    i++;
	}
	if (c == EOF) {
	    sprintf(sbuf, "Nonterminating string\n");
	    yyerror(sbuf);
	    return 0;
	}
	s[i] = '\0';
	yylval.str = s;
	return CHRSTR;
    }
    if (c == '.' || isdigit(c)) {
	char stmp[80];
	double d;
	int i, gotdot = 0;

	i = 0;
	while (c == '.' || isdigit(c)) {
	    if (c == '.') {
		if (gotdot) {
		    yyerror("Reading number, too many dots");
	    	    return 0;
		} else {
		    gotdot = 1;
		}
	    }
	    stmp[i++] = c;
	    c = getcharstr();
	}
	if (c == 'E' || c == 'e') {
	    stmp[i++] = c;
	    c = getcharstr();
	    if (c == '+' || c == '-') {
		stmp[i++] = c;
		c = getcharstr();
	    }
	    while (isdigit(c)) {
		stmp[i++] = c;
		c = getcharstr();
	    }
	}
	if (gotdot && i == 1) {
	    ungetchstr();
	    return '.';
	}
	stmp[i] = '\0';
	ungetchstr();
	sscanf(stmp, "%lf", &d);
	yylval.val = d;
	return NUMBER;
    }
/* graphs, sets, regions resp. */
    if (c == 'G' || c == 'S' || c == 'R') {
	char stmp[80];
	double d;
	int i = 0, ctmp = c, gn, sn, rn;
	c = getcharstr();
	while (isdigit(c)) {
	    stmp[i++] = c;
	    c = getcharstr();
	}
	if (i == 0) {
	    c = ctmp;
	    ungetchstr();
	} else {
	    ungetchstr();
	    if (ctmp == 'G') {
	        stmp[i] = '\0';
		gn = atoi(stmp);
		if (gn >= 0 && gn < maxgraph) {
		    yylval.ival = gn;
		    whichgraph = gn;
		    return GRAPHNO;
		}
	    } else if (ctmp == 'S') {
	        stmp[i] = '\0';
		sn = atoi(stmp);
		if (sn >= 0 && sn < g[cg].maxplot) {
		    lxy = getsetlength(cg, sn);
		    yylval.ival = sn;
		    whichset = sn;
		    return SETNUM;
		}
	    } else if (ctmp == 'R') {
	        stmp[i] = '\0';
		rn = atoi(stmp);
		if (rn >= 0 && rn < MAXREGION) {
		    yylval.ival = rn;
		    return REGNUM;
		}
	    }
	}
    }
    if (isalpha(c)) {
	char *p = sbuf;
	int gno = -1, setno = -1, xy = -1, elno = -1;

	do {
	    *p++ = c;
	} while ((c = getcharstr()) != EOF && isalnum(c));
	ungetchstr();
	*p = '\0';
	
        if (debuglevel == 2) {
	    printf("->%s<-\n", sbuf);
	}
	
	if ((found = findf(key, sbuf, MAXFUN)) >= 0) {
	    if (key[found].type == VAR) {
		switch (sbuf[0]) {
		case 'A':
		    yylval.ptr = aa;
		    return VAR;
		case 'B':
		    yylval.ptr = bb;
		    return VAR;
		case 'C':
		    yylval.ptr = cc;
		    return VAR;
		case 'D':
		    yylval.ptr = dd;
		    return VAR;
		}
	    }
	    else if (key[found].type == SVAR) {
		switch (sbuf[0]) {
		case 'X':
		    yylval.ptr = xx;
		    return SVAR;
		case 'Y':
		    yylval.ptr = yy;
		    return SVAR;
		}
	    }
	    else if (key[found].type == FITPARM) {
		int index = sbuf[1] - '0';
		yylval.val = nonl_parms[index];
		return FITPARM;
	    }
	    else { /* set up special cases */
		switch (key[found].type) {
		case XAXIS:
		    naxis = 0;
		    break;
		case YAXIS:
		    naxis = 1;
		    break;
		case ZEROXAXIS:
		    naxis = 2;
		    break;
		case ZEROYAXIS:
		    naxis = 3;
		    break;
		case ALTXAXIS:
		    naxis = 4;
		    break;
		case ALTYAXIS:
		    naxis = 5;
		    break;
		case AXES:
		    naxis = 6;
		    break;
		case XAXES:
		    naxis = 7;
		    break;
		case YAXES:
		    naxis = 8;
		    break;
		case GRAPHS:
		    yylval.ival = -1;
		    whichgraph = -1;
		    return GRAPHS;
		    break;
		case SETS:
		    yylval.ival = -1;
		    whichset = -1;
		    return SETS;
		    break;
		default:
		    break;
		}
	    }
	    yylval.func = key[found].type;
	    return key[found].type;
	} else {
	    strcat(sbuf, ": No such function or variable");
	    yyerror(sbuf);
	    return 0;
	}
    }
    switch (c) {
    case '>':
	return follow('=', GE, GT);
    case '<':
	return follow('=', LE, LT);
    case '=':
	return follow('=', EQ, '=');
    case '!':
	return follow('=', NE, NOT);
    case '|':
	return follow('|', OR, '|');
    case '&':
	return follow('&', AND, '&');
    case '\n':
	return '\n';
    default:
	return c;
    }
}

int follow(expect, ifyes, ifno)
{
    int c = getcharstr();

    if (c == expect) {
	return ifyes;
    }
    ungetchstr();
    return ifno;
}

void yyerror(s)
    char *s;
{
    int i;
    char buf[256];
    sprintf(buf, "Error: %s: %s", s, f_string);
    i = strlen(buf);
    buf[i - 1] = 0;
    errwin(buf);
    interr = 1;
}

#define C1 0.1978977093962766
#define C2 0.1352915131768107

double rnorm(mean, sdev)
    double mean, sdev;
{
    double u = drand48();

    return mean + sdev * (pow(u, C2) - pow(1.0 - u, C2)) / C1;
}

double fx(x)
    double x;
{
    return 1.0 / sqrt(2.0 * M_PI) * exp(-x * x * 0.5);
}

double normp(b, s)
    double b, *s;
{
    double sum, dx, a = -8.0, fx();
    int i, n = 48;

    sum = fx(a) + fx(b);
    dx = (b - a) / n;
    for (i = 1; i <= ((n - 1) / 2); i++)
	sum = sum + 4.0 * fx(a + (2.0 * i - 1.0) * dx) + 2.0 * fx(a + 2.0 * i * dx);
    sum = sum + 4.0 * fx(b - dx);
    *s = fx(b);
    return sum * dx / 3.0;
}

double invnorm(p)
    double p;
{
    double s, x, z, temp, normp();

    if (p > 0.5)
	x = 1.0 - p;
    else
	x = p;
    s = sqrt(-2.0 * log(x));
    x = ((-7.49101 * s - 448.047) * s - 1266.846);
    x = x / (((s + 109.8371) * s + 748.189) * s + 498.003) + s;
    if (p < 0.5)
	x = -x;
    z = p - normp(x, &s);
    z = z / s;
    s = x * x;
    return (((((((((720.0 * s + 2556.0) * s + 1740.0) * s + 127.0) * z / 7.0 +
		 ((120.0 * s + 326.0) * s + 127.0) * x) * z / 6.0 + (24 * s + 46.0) * s + 7.0) * z / 40.0 +
	       (0.75 * s + 0.875) * x) * z + s + 0.5) * z / 3.0 + x * 0.5) * z + 1.0) * z + x + 0.832e-24 * x;
}

double invt(p, n)
    double p;

    int n;
{
    double sign, temp, a, b, c, d, x, y;

    sign = 1.0;
    if (p < 0.5) {
	p = 1.0 - p;
	sign = -1.0;
    }
    p = (1 - p) * 2;
    if (n == 2) {
	temp = sqrt(2.0 / (p * (2.0 - p)) - 2.0);
	temp = sign * temp;
	return temp;
    } else if (n == 1) {
	p = p * M_PI / 2.0;
	return sign * cos(p) / sin(p);
    } else {
	a = 1.0 / (n - 0.5);
	b = 48.0 / (a * a);
	c = ((20700 * a / b - 98.0) * a - 16.0) * a + 96.36;
	d = ((94.5 / (b + c) - 3.0) / b + 1.0) * sqrt(a * M_PI / 2.0) * n;
	x = d * p;
	y = exp((2.0 / n) * log(x));
	if (y > (0.05 + a)) {
	    x = invnorm(p * 0.5);
	    y = x * x;
	    if (n < 5)
		c = c + 0.3 * (n - 4.5) * (x + 0.6);
	    c = (((0.05 * d * x - 5.0) * x - 7.0) * x - 2.0) * x + b + c;
	    y = (((((0.4 * y + 6.3) * y + 36.0) * y + 94.5) / c - y - 3.0) / b + 1.0) * x;
	    y = a * y * y;
	    if (y > 0.002)
		y = exp(y) - 1.0;
	    else
		y = 0.5 * y * y + y;
	} else
	    y = ((1.0 / (((n + 0.6) / (n * y) - 0.089 * d - 0.822) * (n + 2.0) * 3.0) + 0.5 / (n + 4.0)) * y - 1.0) * (n + 1.0) / (n + 2.0) + 1.0 / y;
	return sign * sqrt(n * y);
    }
}
yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 29,
	37, 592,
	-2, 519,
-1, 30,
	37, 593,
	-2, 520,
-1, 31,
	37, 594,
	-2, 521,
-1, 45,
	37, 616,
	-2, 530,
-1, 46,
	37, 617,
	-2, 531,
-1, 60,
	37, 631,
	-2, 546,
-1, 61,
	37, 632,
	-2, 547,
-1, 62,
	37, 633,
	-2, 548,
-1, 248,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 648,
-1, 258,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 650,
-1, 530,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 491,
-1, 532,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 495,
-1, 534,
	37, 581,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 499,
-1, 536,
	37, 582,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 503,
-1, 538,
	37, 584,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 507,
-1, 542,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 640,
-1, 543,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 641,
-1, 544,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 642,
-1, 545,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 643,
-1, 546,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 644,
-1, 547,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 645,
-1, 551,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 494,
-1, 553,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 498,
-1, 555,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 502,
-1, 557,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 506,
-1, 558,
	10, 490,
	44, 490,
	41, 490,
	58, 490,
	-2, 509,
-1, 562,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 558,
-1, 563,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 559,
-1, 564,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 560,
-1, 565,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 561,
-1, 566,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 562,
-1, 567,
	620, 0,
	621, 0,
	622, 0,
	623, 0,
	624, 0,
	625, 0,
	-2, 563,
-1, 991,
	37, 585,
	-2, 511,
-1, 1022,
	37, 621,
	-2, 536,
-1, 1334,
	37, 599,
	-2, 529,
-1, 1335,
	37, 620,
	-2, 534,
-1, 1348,
	37, 634,
	-2, 552,
	};
# define YYNPROD 651
# define YYLAST 7178
yytabelem yyact[]={

   561,     5,   274,   915,  1157,   951,  1179,   844,   172,   170,
   867,   171,   796,   173,   780,  1415,   344,   944,   946,  1203,
  1414,  1401,  1370,  1365,   952,  1351,  1325,  1317,  1316,   175,
  1315,  1312,  1305,   159,  1304,  1303,  1302,  1300,   727,   725,
  1426,   726,   781,   728,  1299,  1298,  1297,  1296,   159,  1283,
   943,   579,  1280,   727,   725,  1424,   726,  1279,   728,   160,
   174,  1278,  1257,  1256,  1232,  1226,  1225,  1223,  1222,   248,
   256,   258,  1220,  1219,   160,  1218,  1216,  1214,  1213,  1212,
  1211,  1210,  1209,   277,   278,  1208,  1199,  1198,   281,  1197,
   729,   159,  1195,  1194,  1184,  1183,   727,   725,  1422,   726,
  1178,   728,   343,  1170,  1165,   729,  1156,  1155,  1154,  1152,
  1131,  1129,   653,     6,   351,   404,   413,   160,   428,   434,
  1127,  1126,  1125,   461,  1121,  1118,  1117,  1116,  1115,   795,
  1113,  1112,  1096,   916,   953,   779,  1079,  1078,  1056,   986,
   985,   983,   968,   967,   966,   965,   964,   954,   729,   948,
   914,   908,   917,   907,   906,   530,   532,   534,   536,   538,
   540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
   904,   551,   553,   555,   557,   558,   945,   947,   581,   580,
   840,   247,   255,   257,   839,   838,   837,   836,   835,   834,
   833,   832,   570,   572,   573,   575,   576,   822,   821,  1204,
   820,   819,   815,   595,   596,   814,   813,   583,   582,   812,
   811,   950,   810,   809,   624,   625,   808,   807,   628,   631,
   633,   635,   637,   639,   641,   643,   645,   647,   649,   651,
   654,   656,   657,   806,   661,   663,   665,   667,   669,   671,
   673,   675,   677,   679,   681,   683,   685,   687,   918,   805,
  1080,   804,   159,   793,   298,   792,   791,   727,   725,   788,
   726,   787,   728,   786,   785,   784,   778,   531,   533,   535,
   537,   539,   777,   776,   735,   734,   733,   710,   160,   705,
   704,   703,   702,   550,   552,   554,   556,   559,   560,   562,
   563,   564,   565,   566,   567,   568,   569,   942,   949,   699,
   579,   697,   659,   623,   622,   571,   621,   574,   518,   729,
   280,   279,   262,  1362,  1349,  1205,  1249,  1242,  1055,   626,
   732,   400,   731,   910,   579,  1276,   401,   276,  1275,   276,
   629,   630,   632,   634,   636,   638,   640,   642,   644,   646,
   648,   650,   617,   655,   658,   722,   660,   662,   664,   666,
   668,   670,   672,   674,   676,   678,   680,   682,   684,   686,
   307,   708,   706,   700,   919,   920,   921,   922,   923,   924,
   925,   926,   927,   928,   929,   930,   931,   932,   933,   934,
   935,   936,   937,   938,   939,   940,   941,   172,   170,  1041,
   171,  1175,   173,   508,   521,  1207,  1196,   969,   831,   797,
   771,   772,   773,  1172,   794,   305,   317,   789,   175,   816,
   159,   618,   198,   208,   613,   727,   725,  1311,   726,   293,
   728,  1403,   291,   215,  1402,  1061,   449,   581,   580,  1060,
   799,   800,   801,   802,   306,   159,   160,  1059,  1058,   174,
   727,   725,  1406,   726,  1309,   728,   716,   715,   425,   714,
   713,   581,   580,   424,  1162,  1159,   583,   582,   142,   143,
  1168,   160,   712,   829,   830,   711,  1413,   729,  1163,   159,
   146,   980,   627,   289,   727,   725,  1405,   726,   259,   728,
   583,   582,   273,   275,   594,   275,   426,  1215,  1353,   315,
  1202,   979,   729,   196,   913,   160,  1201,   308,   310,  1054,
   477,  1177,   960,  1352,   615,   616,   619,   620,   349,   402,
   411,   272,   952,   341,   342,   730,  1188,   454,   470,   482,
  1057,   207,   491,   577,   206,   519,   729,  1176,   422,   292,
   423,   955,   290,  1160,   842,   958,   261,   957,   361,   362,
   363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
   373,   374,   375,   376,   378,   379,   380,   381,   382,   383,
   384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
   394,   377,   395,   396,   397,   398,   609,    37,    38,    39,
    40,    41,    42,    43,    44,   182,   176,   177,   178,   179,
   180,   181,  1182,   316,   593,   296,   297,  1310,   608,   959,
   409,   159,  1161,   314,    21,   602,   727,   725,  1404,   726,
   346,   728,   984,   982,   168,   167,   161,   162,   163,   164,
   165,   166,   953,   408,  1308,   737,   427,   160,   410,   168,
   167,   161,   162,   163,   164,   165,   166,   453,   452,   207,
  1169,   956,   206,  1158,  1189,  1313,  1231,  1187,  1164,  1174,
  1173,   981,  1130,  1069,   696,   719,   962,   961,   729,   790,
   721,   610,   718,   403,   603,   717,   283,  1181,   701,   282,
   315,   260,   168,   167,   161,   162,   163,   164,   165,   166,
   125,   124,   147,   140,  1229,  1324,  1228,  1379,  1273,  1051,
  1052,   952,   347,   654,   520,   689,   688,   160,   407,   481,
   406,   599,   600,   601,   405,   294,   295,   207,   160,   175,
   206,   148,   141,   175,  1411,  1323,   144,   145,   267,   210,
   739,   207,   612,  1371,   206,  1072,  1073,  1074,  1075,  1076,
  1077,  1420,  1236,  1235,   989,   738,  1180,   606,  1383,   729,
   174,   611,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,
  1089,  1090,  1091,  1092,  1093,  1094,  1095,   254,  1097,  1098,
  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,
  1109,  1110,  1382,   360,   316,  1111,  1285,   286,   480,   345,
  1015,   604,   605,  1114,   160,   691,   977,   159,   348,   207,
  1272,   444,   206,   213,   211,   447,   212,   194,   723,  1119,
   159,   953,   451,   450,  1120,   727,   725,  1397,   726,   270,
   728,   207,   265,   160,   206,   158,   976,   207,   740,   598,
   206,   709,   607,   269,   707,   284,   160,   193,   445,  1128,
  1124,   192,   693,   168,   167,   161,   162,   163,   164,   165,
   166,   691,   528,   529,   158,   482,   690,  1134,  1141,  1147,
  1148,  1132,  1150,  1151,  1381,   823,   901,   729,   271,   287,
  1314,   191,  1274,  1244,  1200,  1166,  1068,  1067,  1066,  1065,
   841,  1064,   448,   845,   868,  1171,   900,  1167,  1123,   905,
  1063,   439,  1190,  1192,  1185,   442,  1062,   478,   479,   990,
   476,   698,   268,   359,   358,  1419,  1418,    19,    20,   912,
   209,  1206,  1390,   963,   978,   474,   195,  1360,   399,   585,
   586,   587,   588,   589,   590,   591,   592,  1357,   440,   214,
  1356,   775,   970,  1355,   197,  1336,  1335,  1328,   770,   172,
   783,   902,   475,   903,   173,   285,   266,   585,   586,   587,
   588,   589,   590,   591,   592,   720,  1290,  1217,   446,  1022,
   175,   817,   769,   768,   207,   288,  1221,   206,   767,   766,
   765,  1224,   443,   183,   182,   176,   177,   178,   179,   180,
   181,   818,  1233,   190,   764,   763,  1237,  1238,  1240,  1241,
   472,   174,   473,   762,   761,   760,  1243,   759,  1246,  1247,
  1248,   168,   167,   161,   162,   163,   164,   165,   166,   758,
   757,  1251,   756,   207,   909,   755,   206,   754,   753,   752,
   751,   750,   749,   748,  1253,  1255,   168,   167,   161,   162,
   163,   164,   165,   166,   747,   746,   745,   744,   264,   189,
  1258,  1259,   743,  1261,   742,  1263,   741,  1265,   441,   159,
   692,   304,  1267,  1269,   727,   725,   303,   726,   302,   728,
   168,   167,   161,   162,   163,   164,   165,   166,  1347,   172,
   170,   301,   171,  1277,   173,   160,   300,  1281,  1282,   299,
   517,  1284,   585,   586,   587,   588,   589,   590,   591,   592,
   175,   246,   245,   244,   243,  1234,   471,   242,   516,   241,
  1239,   240,   239,   515,   514,  1396,   729,   188,   238,   172,
   170,   237,   171,   236,   173,  1071,   235,   234,   159,   233,
   232,   174,  1250,   727,   725,  1394,   726,   231,   728,   517,
   175,   230,   229,   228,   227,   226,  1252,  1254,   225,  1295,
   513,   512,   313,  1053,   160,   159,   224,   516,   187,   223,
   727,   222,   515,   514,  1260,   728,  1262,   221,  1264,   220,
   219,   174,   159,   218,  1266,  1268,  1399,   727,   725,   204,
   726,   160,   728,   217,   216,   729,   312,  1307,   186,   510,
   185,   511,   184,   152,   309,   151,   150,   899,   160,   513,
   512,   890,   168,   167,   161,   162,   163,   164,   165,   166,
   159,   866,   729,   843,  1398,   727,   725,   911,   726,   200,
   728,   490,  1345,   172,   170,    12,   171,   159,   173,   729,
    11,     9,   727,   725,  1393,   726,   160,   728,   510,  1122,
   511,     1,   509,   578,   175,    69,    97,    96,   736,   489,
    70,  1318,   207,   160,   497,   206,  1319,  1320,   845,     7,
    10,  1133,  1140,   159,   127,  1149,  1326,   729,   156,   203,
  1153,   597,   487,   157,   614,   174,     8,   263,  1186,   854,
     4,   868,     3,     2,   729,     0,     0,   201,   584,   160,
     0,     0,     0,     0,  1350,   825,   895,   891,     0,     0,
     0,   897,     0,   311,     0,   199,     0,  1363,     0,  1364,
     0,   159,  1366,  1367,  1368,  1369,   727,   725,  1392,   726,
   158,   728,   824,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   896,     0,     0,   160,   207,     0,
     0,   206,   484,  1372,  1373,  1375,   526,   486,  1376,   485,
     0,   522,     0,   488,     0,   159,     0,     0,  1377,  1378,
   727,   725,  1388,   726,   894,   728,     0,   892,   729,     0,
   826,     0,   827,     0,  1227,  1384,     0,     0,   898,  1385,
  1386,   160,  1387,     0,   525,     0,     0,     0,     0,     0,
     0,   205,  1395,   207,   527,     0,   206,     0,     0,     0,
  1400,   168,   167,   161,   162,   163,   164,   165,   166,  1407,
     0,     0,   729,  1408,  1409,  1410,     0,   893,  1412,   483,
     0,   202,     0,     0,     0,     0,   524,  1416,   523,     0,
     0,     0,  1417,     0,     0,     0,     0,     0,     0,     0,
     0,  1421,     0,  1423,     0,  1425,     0,  1427,     0,   207,
     0,     0,   206,     0,     0,     0,     0,  1374,     0,     0,
     0,    13,    22,    23,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    45,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    60,    61,    62,    63,    46,    64,    65,    66,    67,
     0,    37,    38,    39,    40,    41,    42,    43,    44,    84,
    79,     0,     0,    85,    89,     0,     0,     0,   142,   143,
     0,     0,     0,     0,     0,    72,   101,     0,    21,     0,
   146,    81,    74,     0,     0,   107,     0,   159,     0,   113,
     0,  1391,   727,   725,   112,   726,    75,   728,     0,    90,
   110,     0,     0,   116,  1301,   129,   136,   100,     0,     0,
     0,  1306,     0,   160,    73,     0,     0,     0,     0,    76,
     0,     0,   137,     0,     0,     0,     0,    93,   103,     0,
     0,     0,     0,    80,   123,    86,     0,    17,   121,     0,
     0,   130,     0,     0,   729,     0,   159,     0,    99,     0,
     0,   727,   725,     0,   726,     0,   728,     0,   138,   139,
     0,    92,     0,     0,     0,     0,     0,   122,   400,     0,
     0,   114,   160,   401,     0,    78,    94,   102,   159,     0,
     0,     0,  1389,   727,   725,     0,   726,    91,   728,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,    77,   729,   160,   183,   182,   176,   177,   178,
   179,   180,   181,     0,     0,     0,     0,     0,     0,   128,
     0,     0,     0,     0,     0,   108,   109,    87,   106,    71,
    95,    18,     0,     0,     0,   729,     0,     0,   131,   133,
   132,   135,   134,     0,     0,   159,     0,    16,   149,     0,
   727,   725,    83,   726,   104,   728,     0,     0,   111,   168,
   167,   161,   162,   163,   164,   165,   166,   115,   120,    82,
     0,   160,     0,     0,   119,     0,     0,     0,   105,     0,
   126,     0,     0,   118,    88,   117,     0,     0,     0,     0,
     0,     0,   147,   140,     0,     0,     0,     0,     0,     0,
     0,  1380,   729,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   148,   141,     0,     0,     0,   144,   145,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,   183,
   182,   176,   177,   178,   179,   180,   181,     0,   168,   167,
   161,   162,   163,   164,   165,   166,    98,    15,    14,     0,
     0,    19,    20,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    68,     0,     0,   361,   362,   363,   364,   365,
   366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
   376,   378,   379,   380,   381,   382,   383,   384,   385,   386,
   387,   388,   389,   390,   391,   392,   393,   394,   377,   395,
   396,   397,   398,     0,    37,    38,    39,    40,    41,    42,
    43,    44,   172,   170,  1035,   171,     0,   173,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
   159,    21,     0,   175,     0,   727,   725,  1361,   726,     0,
   728,     0,   460,     0,     0,   464,     0,     0,     0,   159,
   468,     0,     0,   400,   727,   725,   160,   726,   401,   728,
     0,     0,     0,     0,   174,     0,   168,   167,   161,   162,
   163,   164,   165,   166,     0,   160,     0,     0,     0,     0,
     0,     0,     0,   465,     0,     0,     0,   729,     0,     0,
   433,     0,   159,     0,     0,     0,   458,   727,   725,  1359,
   726,     0,   728,   159,     0,     0,   729,     0,   727,   725,
  1358,   726,     0,   728,     0,     0,   456,     0,   160,     0,
     0,   459,     0,     0,     0,   466,     0,   467,   159,   160,
     0,   455,     0,   727,   725,  1354,   726,     0,   728,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   207,   729,
     0,   206,     0,   159,   160,     0,     0,  1348,   156,   154,
   729,   155,   159,   157,     0,     0,  1346,   156,   154,     0,
   155,     0,   157,     0,     0,     0,     0,   172,   170,   160,
   171,     0,   173,     0,   254,   729,     0,     0,   160,   159,
     0,     0,     0,  1344,   727,   725,     0,   726,   175,   728,
   360,   159,     0,     0,     0,  1342,   727,   725,   159,   726,
   158,   728,     0,   727,   725,   160,   726,     0,   728,   158,
   469,     0,     0,     0,     0,     0,     0,   160,     0,   174,
     0,     0,     0,     0,   160,   457,     0,     0,     0,     0,
   462,     0,     0,     0,     0,     0,   729,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,   729,     0,
     0,     0,     0,     0,     0,   729,     0,     0,     0,   463,
   361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
   371,   372,   373,   374,   375,   376,   378,   379,   380,   381,
   382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
   392,   393,   394,   377,   395,   396,   397,   398,     0,    37,
    38,    39,    40,    41,    42,    43,    44,   400,     0,     0,
   359,   358,   401,     0,    19,    20,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   399,    21,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,     0,   159,     0,
   420,     0,  1340,   727,   725,   416,   726,   159,   728,     0,
   421,     0,   727,   725,  1338,   726,     0,   728,     0,     0,
     0,  1343,   172,   170,   160,   171,     0,   173,     0,     0,
     0,     0,     0,   160,     0,     0,     0,     0,   418,     0,
     0,   159,     0,   175,     0,   412,   727,   725,  1337,   726,
     0,   728,     0,     0,     0,   729,   168,   167,   161,   162,
   163,   164,   165,   166,   729,   159,     0,   160,   419,  1334,
   156,   154,     0,   155,   174,   157,     0,     0,     0,     0,
     0,     0,   415,     0,     0,     0,   414,     0,     0,   159,
     0,   160,     0,  1332,   156,   154,     0,   155,   729,   157,
     0,     0,     0,   207,     0,     0,   206,     0,   159,     0,
     0,     0,  1330,   727,   725,   160,   726,     0,   728,     0,
     0,   159,   158,     0,     0,     0,   727,   725,  1327,   726,
     0,   728,     0,     0,   160,     0,     0,     0,     0,   254,
     0,     0,     0,     0,     0,   417,   158,   160,     0,     0,
     0,     0,     0,     0,     0,   360,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   729,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   729,     0,
     0,     0,     0,     0,   361,   362,   363,   364,   365,   366,
   367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
   378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
   388,   389,   390,   391,   392,   393,   394,   377,   395,   396,
   397,   398,     0,    37,    38,    39,    40,    41,    42,    43,
    44,   400,     0,     0,     0,     0,   401,     0,   183,   182,
   176,   177,   178,   179,   180,   181,   159,     0,     0,     0,
    21,   727,   725,  1322,   726,     0,   728,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,   355,
     0,     0,   160,     0,   357,   359,   358,     0,     0,    19,
    20,   167,   161,   162,   163,   164,   165,   166,     0,     0,
   399,     0,     0,     0,   159,     0,   356,     0,     0,   727,
   725,  1294,   726,   729,   728,     0,     0,     0,     0,   350,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   160,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,   353,     0,   354,     0,     0,     0,
   352,   729,     0,     0,     0,     0,     0,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,   207,     0,     0,
   206,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,   254,     0,   176,   177,   178,   179,   180,
   181,     0,     0,     0,     0,     0,     0,     0,     0,   360,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   161,   162,   163,   164,   165,   166,     0,   361,   362,
   363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
   373,   374,   375,   376,   378,   379,   380,   381,   382,   383,
   384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
   394,   377,   395,   396,   397,   398,     0,    37,    38,    39,
    40,    41,    42,    43,    44,   400,     0,     0,     0,     0,
   401,     0,   159,     0,     0,     0,     0,   727,   725,     0,
   726,   159,   728,     0,    21,     0,   727,   725,  1293,   726,
     0,   728,     0,     0,     0,     0,     0,     0,   160,     0,
     0,     0,     0,  1143,     0,     0,     0,   160,     0,   359,
   358,     0,     0,    19,    20,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   399,     0,     0,     0,  1321,   729,
     0,     0,     0,     0,     0,     0,     0,     0,   729,     0,
     0,     0,     0,   433,     0,     0,  1146,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,   183,   182,
   176,   177,   178,   179,   180,   181,   159,     0,  1145,     0,
  1144,   727,   725,  1292,   726,     0,   728,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   207,   160,     0,   206,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   168,   167,   161,   162,
   163,   164,   165,   166,   159,     0,     0,     0,  1050,   727,
   725,     0,   726,   729,   728,     0,     0,   254,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
   160,     0,     0,   360,     0,     0,  1142,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   729,   361,   362,   363,   364,   365,   366,   367,   368,
   369,   370,   371,   372,   373,   374,   375,   376,   378,   379,
   380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
   390,   391,   392,   393,   394,   377,   395,   396,   397,   398,
     0,    37,    38,    39,    40,    41,    42,    43,    44,   400,
     0,     0,     0,     0,   401,     0,   159,     0,     0,     0,
  1048,   727,   725,     0,   726,     0,   728,     0,    21,   159,
     0,     0,     0,  1046,   727,   725,     0,   726,     0,   728,
   159,     0,   160,     0,  1044,   727,   725,  1136,   726,     0,
   728,     0,     0,   359,   358,   160,     0,    19,    20,     0,
   339,   340,   337,     0,     0,     0,   160,     0,   399,   338,
  1341,   172,   170,   729,   171,     0,   173,   168,   167,   161,
   162,   163,   164,   165,   166,   337,   729,   433,     0,     0,
  1139,     0,   175,   159,     0,     0,     0,   729,   727,   725,
  1291,   726,     0,   728,     0,     0,     0,   159,     0,     0,
     0,  1040,   727,   725,     0,   726,     0,   728,     0,   160,
     0,     0,  1138,   174,  1137,   168,   167,   161,   162,   163,
   164,   165,   166,   160,     0,   400,     0,  1339,   172,   170,
   401,   171,     0,   173,     0,   207,     0,     0,   206,     0,
   729,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     0,     0,     0,     0,   729,     0,     0,     0,     0,     0,
   336,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   254,     0,     0,     0,     0,     0,     0,     0,     0,
   174,     0,     0,   336,     0,     0,     0,   360,     0,     0,
  1135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   361,   362,   363,   364,
   365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
   375,   376,   378,   379,   380,   381,   382,   383,   384,   385,
   386,   387,   388,   389,   390,   391,   392,   393,   394,   377,
   395,   396,   397,   398,     0,    37,    38,    39,    40,    41,
    42,    43,    44,   318,   319,   320,     0,   321,   322,   323,
   324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
   334,   335,    21,     0,     0,     0,   318,   319,   320,     0,
   321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
   331,   332,   333,   334,   335,     0,     0,   359,   358,     0,
     0,    19,    20,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   399,   168,   167,   161,   162,   163,   164,   165,
   166,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   433,   361,   362,   363,   364,   365,   366,   367,   368,
   369,   370,   371,   372,   373,   374,   375,   376,   378,   379,
   380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
   390,   391,   392,   393,   394,   377,   395,   396,   397,   398,
     0,    37,    38,    39,    40,    41,    42,    43,    44,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
     0,     0,     0,  1038,   727,   725,     0,   726,    21,   728,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   160,     0,   168,   167,   161,
   162,   163,   164,   165,   166,   254,   159,     0,     0,     0,
     0,   727,   725,  1036,   726,     0,   728,   159,     0,     0,
     0,   360,   727,   725,  1034,   726,   729,   728,     0,     0,
     0,     0,   160,     0,     0,     0,     0,   433,     0,     0,
     0,     0,     0,   160,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   729,     0,     0,   400,     0,     0,   436,
   435,   401,     0,     0,   729,   159,     0,     0,     0,     0,
   727,   725,  1032,   726,     0,   728,   159,     0,     0,     0,
     0,   727,   725,  1030,   726,     0,   728,   159,   438,   437,
     0,   160,   727,   725,  1289,   726,     0,   728,     0,   159,
     0,     0,   160,  1028,   727,   725,     0,   726,     0,   728,
     0,     0,     0,   160,     0,     0,     0,     0,     0,     0,
     0,   254,   729,   400,     0,   160,     0,     0,   401,     0,
     0,   359,   358,   729,     0,    19,    20,   360,     0,     0,
     0,     0,     0,     0,   729,     0,   399,   168,   167,   161,
   162,   163,   164,   165,   166,     0,   729,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,     0,     0,     0,     0,   430,   429,     0,     0,     0,
   400,     0,     0,     0,     0,   401,     0,   183,   182,   176,
   177,   178,   179,   180,   181,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   432,   431,     0,     0,     0,     0,
     0,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   359,   358,     0,
     0,    19,    20,     0,   183,   182,   176,   177,   178,   179,
   180,   181,   399,   361,   362,   363,   364,   365,   366,   367,
   368,   369,   370,   371,   372,   373,   374,   375,   376,   378,
   379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
   389,   390,   391,   392,   393,   394,   377,   395,   396,   397,
   398,     0,    37,    38,    39,    40,    41,    42,    43,    44,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
   361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
   371,   372,   373,   374,   375,   376,   378,   379,   380,   381,
   382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
   392,   393,   394,   377,   395,   396,   397,   398,     0,    37,
    38,    39,    40,    41,    42,    43,    44,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   433,     0,
     0,     0,     0,     0,     0,     0,    21,   361,   362,   363,
   364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
   374,   375,   376,   378,   379,   380,   381,   382,   383,   384,
   385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
   377,   395,   396,   397,   398,     0,    37,    38,    39,    40,
    41,    42,    43,    44,   159,     0,     0,     0,  1026,   727,
   725,     0,   726,     0,   728,   433,     0,     0,     0,     0,
     0,   159,     0,    21,     0,  1024,   727,   725,     0,   726,
   160,   728,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   254,     0,     0,    69,     0,   160,     0,     0,
    70,     0,     0,     0,     0,     0,     0,     0,   360,   159,
     0,   729,     0,  1019,   727,   725,     0,   726,     0,   728,
     0,     0,     0,     0,     0,     0,     0,     0,   729,     0,
     0,     0,   433,     0,     0,   160,     0,     0,     0,  1193,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   254,
     0,     0,    69,     0,     0,     0,   729,    70,     0,     0,
     0,     0,     0,     0,     0,   360,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   159,     0,     0,
     0,  1017,   727,   725,     0,   726,  1191,   728,   159,     0,
     0,     0,     0,   727,   725,  1288,   726,     0,   728,     0,
     0,     0,     0,   160,     0,     0,   254,     0,   359,   358,
     0,     0,    19,    20,   160,     0,     0,     0,     0,     0,
     0,     0,   360,   399,     0,     0,   168,   167,   161,   162,
   163,   164,   165,   166,   729,     0,     0,   168,   167,   161,
   162,   163,   164,   165,   166,   729,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,     0,     0,   359,   358,     0,     0,    19,
    20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   399,     0,    22,    23,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    45,   253,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    60,    61,    62,    63,    46,    64,    65,    66,    67,
     0,    37,    38,    39,    40,    41,    42,    43,    44,     0,
     0,     0,   359,   358,     0,     0,    19,    20,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   399,    21,    22,
    23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
    33,    34,    35,    36,    45,   253,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    46,    64,    65,    66,    67,     0,    37,    38,
    39,    40,    41,    42,    43,    44,   159,     0,     0,     0,
  1012,   727,   725,     0,   726,     0,   728,   251,   159,     0,
     0,     0,  1010,   727,   725,    21,   726,     0,   728,   159,
     0,     0,   160,  1008,   727,   725,     0,   726,     0,   728,
     0,   159,     0,     0,   160,  1006,   727,   725,     0,   726,
     0,   728,   159,     0,     0,   160,  1004,   727,   725,     0,
   726,     0,   728,   729,   159,     0,     0,   160,  1002,   727,
   725,     0,   726,     0,   728,   729,     0,     0,   160,     0,
     0,     0,     0,     0,   251,     0,   729,   159,     0,     0,
   160,     0,   727,   725,  1000,   726,   159,   728,   729,     0,
   998,   727,   725,     0,   726,     0,   728,     0,     0,   729,
   159,   254,     0,   160,   996,   727,   725,     0,   726,     0,
   728,   729,   160,     0,   159,     0,     0,   252,   994,   727,
   725,     0,   726,   159,   728,     0,   160,  1287,   727,   725,
     0,   726,     0,   728,   729,     0,     0,     0,     0,     0,
   160,     0,     0,   729,     0,     0,   159,     0,     0,   160,
     0,   727,   725,  1286,   726,     0,   728,   729,     0,   159,
     0,     0,     0,     0,   727,   725,     0,   726,   254,   728,
     0,   729,   160,   159,     0,     0,     0,   695,   727,   725,
   729,   726,     0,   728,   652,   160,     0,   159,     0,     0,
     0,     0,   727,   725,     0,   726,     0,   728,     0,   160,
     0,     0,     0,   729,     0,   168,   167,   161,   162,   163,
   164,   165,   166,   160,     0,  1271,   729,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
   729,     0,     0,     0,     0,     0,     0,   250,   249,     0,
     0,    19,    20,  1270,   729,     0,     0,     0,     0,   159,
     0,     0,    68,     0,   727,   725,  1245,   726,     0,   728,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,   159,     0,     0,     0,   160,   727,   725,  1230,   726,
     0,   728,     0,     0,   159,     0,     0,     0,     0,   727,
   725,  1070,   726,     0,   728,     0,     0,   160,     0,     0,
     0,     0,     0,     0,   250,   249,   729,     0,    19,    20,
   160,     0,   159,     0,     0,     0,  1050,   156,   154,    68,
   155,   159,   157,     0,     0,  1048,   156,   154,   729,   155,
     0,   157,     0,     0,     0,     0,     0,     0,   160,     0,
     0,   729,     0,     0,     0,     0,     0,   160,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,   159,     0,   158,
     0,  1046,   156,   154,     0,   155,   159,   157,   158,     0,
  1044,   156,   154,     0,   155,     0,   157,     0,     0,   159,
     0,     0,     0,   160,   156,   154,  1042,   155,     0,   157,
   159,     0,   160,     0,  1040,   156,   154,     0,   155,     0,
   157,     0,   159,     0,     0,   160,  1038,   156,   154,     0,
   155,     0,   157,     0,   158,     0,   160,     0,     0,   159,
     0,     0,     0,   158,   156,   154,  1036,   155,   160,   157,
     0,     0,   159,     0,     0,     0,   158,   156,   154,  1034,
   155,     0,   157,   159,     0,   160,     0,   158,   156,   154,
  1032,   155,     0,   157,     0,   159,     0,     0,   160,   158,
   156,   154,  1030,   155,     0,   157,     0,   159,     0,   160,
     0,  1028,   156,   154,     0,   155,   158,   157,   159,     0,
     0,   160,  1026,   156,   154,     0,   155,     0,   157,   158,
     0,   159,     0,   160,     0,  1024,   156,   154,     0,   155,
   158,   157,     0,   159,   160,     0,     0,     0,   156,   154,
  1020,   155,   158,   157,     0,     0,     0,   160,     0,     0,
   159,     0,     0,     0,   158,   156,   154,  1014,   155,   160,
   157,     0,   159,     0,     0,   158,  1019,   156,   154,     0,
   155,     0,   157,     0,     0,     0,   160,     0,   158,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   160,     0,
   158,     0,     0,     0,     0,     0,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,   158,     0,   168,
   167,   161,   162,   163,   164,   165,   166,     0,     0,   158,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,     0,     0,     0,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
     0,   159,     0,     0,     0,  1017,   156,   154,     0,   155,
   159,   157,     0,     0,  1012,   156,   154,     0,   155,     0,
   157,     0,     0,   159,     0,     0,     0,   160,   156,   154,
  1000,   155,     0,   157,     0,     0,   160,   159,     0,     0,
     0,  1010,   156,   154,     0,   155,     0,   157,     0,   160,
   168,   167,   161,   162,   163,   164,   165,   166,   158,     0,
     0,     0,     0,   160,     0,     0,     0,   158,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
   158,     0,     0,     0,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,   158,   159,     0,     0,     0,  1008,
   156,   154,     0,   155,     0,   157,     0,     0,     0,     0,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,   160,   168,   167,   161,   162,   163,   164,   165,   166,
   159,     0,     0,     0,  1006,   156,   154,     0,   155,     0,
   157,   159,     0,     0,     0,  1004,   156,   154,     0,   155,
     0,   157,   158,     0,     0,     0,   160,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   160,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,   158,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,   158,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,   168,   167,   161,   162,
   163,   164,   165,   166,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,   168,
   167,   161,   162,   163,   164,   165,   166,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,   159,     0,     0,     0,  1002,   156,   154,     0,   155,
   159,   157,     0,     0,   998,   156,   154,     0,   155,     0,
   157,     0,     0,     0,   159,     0,     0,   160,   996,   156,
   154,     0,   155,   159,   157,     0,   160,   994,   156,   154,
     0,   155,     0,   157,     0,     0,     0,   159,     0,     0,
   160,   991,   156,   154,     0,   155,   159,   157,   158,   160,
     0,   727,   725,   988,   726,     0,   728,   158,     0,   159,
     0,     0,     0,   160,   727,   725,   987,   726,     0,   728,
     0,   158,   160,     0,     0,     0,   159,     0,     0,     0,
   158,   727,   725,   975,   726,   160,   728,   159,     0,     0,
     0,     0,   727,   725,   158,   726,     0,   728,     0,   159,
     0,     0,   160,   729,   727,   725,     0,   726,     0,   728,
     0,     0,     0,   160,   159,     0,   729,     0,     0,   727,
   725,     0,   726,     0,   728,   160,     0,     0,     0,     0,
     0,   159,     0,   729,     0,   971,   727,   725,   828,   726,
   160,   728,   159,   974,   729,     0,     0,   727,   725,   803,
   726,     0,   728,   159,     0,   973,   729,   160,   727,   725,
   798,   726,     0,   728,     0,     0,     0,     0,   160,     0,
     0,   729,     0,     0,     0,     0,     0,     0,     0,   160,
     0,     0,     0,     0,     0,   159,     0,     0,   729,     0,
   727,   725,   782,   726,     0,   728,     0,     0,     0,   729,
   172,   170,  1033,   171,     0,   173,     0,     0,     0,     0,
   729,   160,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   175,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,     0,   729,     0,   168,   167,   161,   162,   163,   164,
   165,   166,   174,     0,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   159,     0,     0,
     0,     0,   727,   725,   774,   726,   159,   728,     0,     0,
     0,   727,   725,   724,   726,     0,   728,     0,     0,   159,
     0,     0,     0,   160,   727,   725,     0,   726,     0,   728,
     0,     0,   160,   159,     0,     0,     0,   695,   156,   154,
     0,   155,     0,   157,     0,   160,   168,   167,   161,   162,
   163,   164,   165,   166,   729,     0,     0,     0,     0,   160,
     0,     0,     0,   729,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   153,     0,     0,   729,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
   158,     0,   168,   167,   161,   162,   163,   164,   165,   166,
   159,     0,     0,     0,     0,   156,   154,     0,   155,   159,
   157,     0,     0,     0,   156,   154,     0,   155,     0,   157,
     0,  1333,   172,   170,     0,   171,   160,   173,     0,     0,
  1331,   172,   170,     0,   171,   160,   173,     0,  1329,   172,
   170,     0,   171,   175,   173,     0,     0,  1049,   172,   170,
     0,   171,   175,   173,     0,     0,     0,   158,     0,     0,
   175,     0,     0,     0,     0,     0,   158,     0,     0,   175,
     0,  1047,   172,   170,   174,   171,     0,   173,     0,     0,
  1045,   172,   170,   174,   171,     0,   173,     0,  1043,   172,
   170,   174,   171,   175,   173,     0,     0,  1039,   172,   170,
   174,   171,   175,   173,     0,  1037,   172,   170,     0,   171,
   175,   173,     0,     0,     0,   172,   170,  1031,   171,   175,
   173,     0,     0,     0,   174,     0,     0,   175,     0,     0,
     0,     0,     0,   174,     0,     0,   175,     0,     0,     0,
     0,   174,   172,   170,  1029,   171,     0,   173,     0,     0,
   174,     0,     0,     0,     0,     0,     0,     0,   174,     0,
     0,     0,     0,   175,     0,     0,     0,   174,  1027,   172,
   170,     0,   171,     0,   173,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   175,     0,     0,     0,   174,     0,     0,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,   168,   167,   161,   162,   163,   164,   165,   166,     0,
     0,   174,     0,     0,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,   168,   167,   161,   162,   163,   164,
   165,   166,     0,     0,     0,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,   168,   167,
   161,   162,   163,   164,   165,   166,     0,     0,     0,     0,
   168,   167,   161,   162,   163,   164,   165,   166,     0,     0,
     0,     0,     0,     0,     0,   168,   167,   161,   162,   163,
   164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   168,   167,   161,   162,   163,   164,   165,   166,
     0,     0,     0,   168,   167,   161,   162,   163,   164,   165,
   166,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,  1025,   172,   170,     0,   171,     0,   173,     0,
     0,     0,  1023,   172,   170,     0,   171,     0,   173,     0,
     0,     0,     0,     0,   175,     0,   168,   167,   161,   162,
   163,   164,   165,   166,   175,     0,   183,   182,   176,   177,
   178,   179,   180,   181,     0,   172,   170,  1021,   171,     0,
   173,     0,  1018,   172,   170,   174,   171,     0,   173,     0,
     0,     0,     0,     0,     0,   174,   175,     0,     0,     0,
     0,     0,     0,     0,   175,     0,  1016,   172,   170,     0,
   171,     0,   173,     0,     0,     0,   172,   170,  1013,   171,
     0,   173,     0,     0,     0,     0,     0,   174,   175,     0,
     0,     0,     0,     0,     0,   174,     0,   175,   168,   167,
   161,   162,   163,   164,   165,   166,     0,   168,   167,   161,
   162,   163,   164,   165,   166,     0,     0,     0,     0,   174,
   168,   167,   161,   162,   163,   164,   165,   166,   174,     0,
     0,     0,     0,     0,   168,   167,   161,   162,   163,   164,
   165,   166,  1011,   172,   170,     0,   171,     0,   173,     0,
     0,     0,     0,     0,     0,     0,  1009,   172,   170,     0,
   171,     0,   173,     0,   175,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   175,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   174,     0,     0,     0,     0,
     0,   168,   167,   161,   162,   163,   164,   165,   166,   174,
   168,   167,   161,   162,   163,   164,   165,   166,   183,   182,
   176,   177,   178,   179,   180,   181,     0,   183,   182,   176,
   177,   178,   179,   180,   181,   183,   182,   176,   177,   178,
   179,   180,   181,     0,   183,   182,   176,   177,   178,   179,
   180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   183,   182,
   176,   177,   178,   179,   180,   181,     0,   183,   182,   176,
   177,   178,   179,   180,   181,   183,   182,   176,   177,   178,
   179,   180,   181,     0,   183,   182,   176,   177,   178,   179,
   180,   181,   183,   182,   176,   177,   178,   179,   180,   181,
   916,   183,   182,   176,   177,   178,   179,   180,   181,     0,
     0,     0,     0,     0,  1007,   172,   170,     0,   171,   917,
   173,     0,     0,     0,     0,     0,     0,     0,   183,   182,
   176,   177,   178,   179,   180,   181,   175,     0,     0,     0,
     0,  1005,   172,   170,     0,   171,     0,   173,     0,     0,
     0,     0,     0,     0,     0,   183,   182,   176,   177,   178,
   179,   180,   181,   175,  1003,   172,   170,   174,   171,     0,
   173,     0,     0,  1001,   172,   170,     0,   171,     0,   173,
     0,     0,   172,   170,   999,   171,   175,   173,     0,     0,
     0,     0,     0,     0,   174,   175,   997,   172,   170,     0,
   171,     0,   173,   175,     0,   995,   172,   170,     0,   171,
     0,   173,     0,     0,     0,   918,     0,   174,   175,   993,
   172,   170,     0,   171,   169,   173,   174,   175,     0,   992,
   172,   170,     0,   171,   174,   173,     0,     0,     0,   172,
   170,   175,   171,     0,   173,     0,   694,   172,   170,   174,
   171,   175,   173,     0,     0,   972,   172,   170,   174,   171,
   175,   173,     0,     0,   172,   170,     0,   171,   175,   173,
     0,     0,   174,     0,     0,     0,     0,   175,     0,     0,
     0,     0,   174,     0,     0,   175,     0,     0,     0,     0,
     0,   174,     0,     0,     0,     0,     0,     0,     0,   174,
     0,     0,     0,     0,     0,     0,     0,     0,   174,     0,
     0,     0,     0,     0,     0,     0,   174,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   919,   920,   921,   922,   923,   924,   925,   926,   927,
   928,   929,   930,   931,   932,   933,   934,   935,   936,   937,
   938,   939,   940,   941,     0,     0,     0,     0,     0,   183,
   182,   176,   177,   178,   179,   180,   181,     0,     0,   183,
   182,   176,   177,   178,   179,   180,   181,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   183,   182,   176,   177,   178,   179,   180,   181,   183,
   182,   176,   177,   178,   179,   180,   181,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   875,   855,
   872,   852,   851,   183,   182,   176,   177,   178,   179,   180,
   181,     0,   183,   182,   176,   177,   178,   179,   180,   181,
   885,     0,     0,     0,     0,   887,     0,     0,     0,     0,
     0,   850,   506,   502,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   865,   500,     0,     0,     0,     0,   886,   498,
   871,     0,   857,     0,     0,   505,     0,   495,   853,     0,
     0,   884,     0,     0,     0,     0,     0,     0,     0,   183,
   182,   176,   177,   178,   179,   180,   181,     0,   876,     0,
     0,   874,     0,   183,   182,   176,   177,   178,   179,   180,
   181,     0,   888,     0,     0,     0,     0,   503,     0,   504,
     0,     0,     0,     0,     0,     0,     0,   863,     0,     0,
     0,   493,     0,   207,     0,     0,   206,   879,     0,     0,
   207,     0,     0,   206,     0,     0,     0,     0,     0,   858,
     0,     0,     0,     0,     0,   870,   873,   846,     0,     0,
   847,     0,   494,     0,     0,     0,     0,     0,     0,     0,
   207,   848,   849,   206,   859,     0,   864,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   880,     0,   877,
     0,     0,     0,     0,     0,   507,   499,     0,     0,     0,
   878,   881,     0,     0,   882,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   496,   869,     0,     0,     0,
   883,     0,     0,   492,     0,   856,     0,     0,     0,     0,
   861,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   860,     0,     0,     0,     0,   501,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   183,   182,   176,   177,   178,   179,   180,   181,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   183,   182,
   176,   177,   178,   179,   180,   181,     0,     0,     0,   889,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   183,   182,   176,   177,   178,   179,   180,   181,     0,
   183,   182,   176,   177,   178,   179,   180,   181,   183,   182,
   176,   177,   178,   179,   180,   181,   862,     0,     0,     0,
     0,     0,     0,   183,   182,   176,   177,   178,   179,   180,
   181,     0,   183,   182,   176,   177,   178,   179,   180,   181,
     0,     0,     0,     0,     0,     0,   183,   182,   176,   177,
   178,   179,   180,   181,     0,     0,   183,   182,   176,   177,
   178,   179,   180,   181,     0,   183,   182,   176,   177,   178,
   179,   180,   181,   183,   182,   176,   177,   178,   179,   180,
   181,     0,   183,   182,   176,   177,   178,   179,   180,   181,
   183,   182,   176,   177,   178,   179,   180,   181 };
yytabelem yypact[]={

  1185, -1000,  1166,  1165,  1163,  5703,  6544,  1162,  1160,  1158,
  1128,  1087,  1019,   963,   770,   736,   447,   878,   377, -1000,
 -1000,  1124,  1123,  1113,  1110,  1109,  1107,  1101,  1099, -1000,
 -1000, -1000,  1096,  1088,  1085,  1084,  1083, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000,  1082,  1081,  1077,
  1070,  1069,  1067,  1066,  1063,  1061,  1058,  1052,  1051,  1049,
 -1000, -1000, -1000,  1047,  1044,  1043,  1042,  1041,  3855,  3855,
  3855, -1000,     4,   333,   194,  -304, -1000,   412,    35,   -37,
   -37,   -37, -1000,  -305,  -306,   -37,   331,   328,   443,   -19,
    40,    37,   213, -1000,  -359,  1029,  1026,  1021,  1008,  1006,
  1001,  -132,    81,   792,   136,  2704,  2681,  2704, -1000, -1000,
 -1000,  -514,   276,  2127,   281,  1863,   111,  3045,  2919,   543,
   453,   145,  1558,   563,   371, -1000,   910,  6450,   702,  -308,
   175, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,   989,   989,   989, -1000,
 -1000, -1000, -1000, -1000,  3855,  3855,  3855,  3855,  3855,  3550,
  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550, -1000,
  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3855,
  3855,  3855,  3855,  3855, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000,  3550,  3855,  3550,  3855,  3550,   -89,   776, -1000,    81,
   -39,   -37,   277,   199,   -79, -1000, -1000, -1000, -1000,   -69,
  -310,  -312,  -313,  3550,  3550,  -293,   -20,  3855,  3855,  3855,
  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3855,  3922,
  3855,  3855,  -314,  3855,  3855,  3855,  3855,  3855,  3855,  3855,
  3855,  3855,  3855,  3855,  3855,  3855,  3855,   650,   634,   605,
   604,   800,   795,  1000,   786,  6535,  5636,   650,   634,    81,
 -1000,  -315,   847, -1000, -1000,  -317, -1000, -1000, -1000, -1000,
 -1000, -1000,  -157,    81, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  -334,  -335,  -336,  -337,
  -158,   778,  -159,   775, -1000, -1000, -1000, -1000,  -339,   -27,
   -30,   -42,   -43,   -45,   -46, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   327,
   324,   317,   322, -1000,  3550, -1000, -1000, -1000, -1000, -1000,
   752,  5609,  -208,  -340,  -341,  -342,   283, -1000,   605,   604,
   772,   996,   994,   992,   987,   986,   985,   984, -1000, -1000,
 -1000,   973,   972,   971,   970,   969, -1000, -1000,   968,   967,
   965,   962,   960,   959,   947,   945,   944,   943,   935,   934,
   920, -1000, -1000, -1000,   919,   918,   913,   912,   888,  3550,
  3550,  3550, -1000,   752,  5600,  -208,  -343,  -344,  -350,  -481,
 -1000, -1000,   752,  5518,  -208,  -351,  -352,  -353,  -355,  -357,
   -88,   321,  -360,  -361,  -363,   -91,  -487,   -96,  5486,  3550,
  3550,  3550,  3550,   752,  5475,  -365,  -367,  -383,  -399, -1000,
  -400,  -403,  -404,  -406, -1000,  -407,  -410,  -411,  -414,   -84,
   371, -1000, -1000, -1000, -1000,  -208,  -415,  -416,  -418,  -419,
   933,  5464,  3550,  3550,   -97,  -425,  -426,  -427,  -428,  -429,
 -1000,  -430,  -431,  -432,  -436,    81,   192, -1000,  6480,  6443,
   939,   514, -1000,  -446,    81,  -462,  -463,  -465,  -208,  -200,
 -1000, -1000,  2704,  3550,  -466,  6084,  -319,  -467,  -318,  -469,
   118,  3550,   319, -1000, -1000, -1000, -1000, -1000,   318,   751,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -470,
 -1000, -1000,  -471,  -472,  -473,  -474,   -98,    81, -1000, -1000,
  1206,   887,  1206,   887,   721,   646,   721,   646,   721,   646,
   645,  5447,  1539,  1539,  1539,  1539,  1539,  1539,  2021,  1862,
   887,  1206,   887,  1206,   646,   750,   646,   750,   750,   646,
  6527,  5712,  1057,  1057,  1057,  1057,  1057,  1057,  1985,   -34,
  5432,  6552,  5712,  5420,  6552,  5712,  5409,   725, -1000, -1000,
 -1000, -1000, -1000, -1000,   445, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000,   151, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  6084,
  -475,  3550,  -476,  -477, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000,  5392,  5379,   673,   845,  5370,  6518,
  6508,  5356,  6494,  5347,  6485,  5333,  6470,  4996,  6462,  5324,
  6453,  5114,  6430,  5103,  6403,  5068,  6235,  5010,  6221,  4983,
  6154,  4723,   739,  6145,  4974,  6121,  4735,  4706,  6113,   908,
  6081,  4694,  6071,  4681,  5867,  4670,  5840,  4658,  5813,  4646,
  5528,  4635,  1820,  4622,  5804,  4605,  5796,  4593,   345,  4582,
  5787,  4569,  5779,  4560,  5770,  4514,  5746,  4505,  3550,  3550,
   641,  -113,  3855,  -294, -1000, -1000, -1000, -1000,  -478, -1000,
   138, -1000, -1000, -1000, -1000, -1000,   -54,   -55,   -63,   -67,
   842,   836,   827,   825,   824,   823,   822, -1000, -1000, -1000,
   315, -1000,  4477,   613,  3550,  3550,  3550,  3550,  3550,  3550,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -479,  -480, -1000,
  -362,  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,
  3550,  3550,  3550,  3550,  3550,  3550,  -484,  3550,  3550,  3550,
  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,  3550,
  3550,   634,  4366,   634,  3550, -1000, -1000, -1000, -1000, -1000,
  -485,  -486,  3550, -1000, -1000, -1000, -1000, -1000, -1000,  -488,
 -1000, -1000, -1000, -1000,  -489, -1000,  -490,  -491,  3550,  5622,
  5622,  5622,  5622,  3550, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  -492, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000,   349,  -494,  -495,  -496,  3550,  5622,
  5622,  -505, -1000, -1000, -1000, -1000,   314, -1000, -1000, -1000,
 -1000, -1000,  -506,  6480, -1000, -1000,  2655,  2391,  3550,  3550,
    81,  3550,  3550,  -507, -1000,    81,  -508,  -509,  -510,   122,
   148,  -512,   821, -1000, -1000, -1000,  6443, -1000, -1000,   140,
  -513,  -213,   312,   311,     1,  -516,   256,  -521,  -522,   122,
   209,  3483,  3416,  -523,  -524,   -99,  -527,  -529,  -530,   820,
 -1000, -1000,    42,  -301,   256,  -100,  -531,  -534,  -535, -1000,
 -1000,  -536,  -537,  -538, -1000, -1000, -1000, -1000, -1000, -1000,
  -539,    92, -1000,  5622, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000,  -540,   -37,  -541,  -543,  -544, -1000, -1000,
   170,  -548, -1000, -1000, -1000,  -549,   122,  -550,  -551,   267,
  4464, -1000, -1000,   308, -1000, -1000, -1000, -1000, -1000,  -552,
 -1000,  3550,  3855,   672,   671,  3550,  3550,  3855,  3550,  -295,
 -1000, -1000,  6084,   819,  4442, -1000, -1000,  3550,  3550,  3550,
  -296, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  3855,
  3550, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000,  3855,  3855, -1000, -1000, -1000, -1000, -1000,
  -553,  -554, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  3550,
  3550,  3855,  3550,  3855,  3550,  3855,  3550, -1000, -1000, -1000,
 -1000,  3855,  3855, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000,  4380,  4352,   744,   597, -1000,   818, -1000, -1000,  -192,
 -1000,  -195,  3550,  -555,  -559,  -564,  3550,  3550,  -567, -1000,
  3550,   730,  4339,  1098,  1098,   645,   645,   645, -1000, -1000,
   597,  4316,  4307,  4293,  4279,  4270,  4247,  4235,  4224,  4212,
  4201,  4189,  3971,  3960,  3872,  3450,   905,  3834,  3817,  3462,
  3439,  3428,  3370,  3359,  3322,  3020,  3006,  2953,  2942,  2929,
  2817,  2769, -1000, -1000,  5622, -1000, -1000, -1000, -1000,  2674,
  2457, -1000, -1000,   170,  -569, -1000, -1000, -1000,  5622, -1000,
 -1000, -1000, -1000, -1000,  5622,  -570,  -571,  -572,  -579,    81,
 -1000,  5622,  -580,  -581,  -582,  -584,    81,  5622,  5622, -1000,
  5622,  5622, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  3550, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
  5622,   124,  5622,    97, -1000, -1000,  -585, -1000, -1000, -1000,
   307, -1000, -1000, -1000, -1000,   816, -1000,  -586, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,  -588,  -589,
  3550, -1000, -1000,  5622,  6552,  3550,  3550,  5622,  2665,  6552,
  5712,  2409,   624, -1000,  -590,  3550,  2284,  5622,  5622,   886,
  5737,  2271,  5729,  2252,  5720,  2228,   885,   884,  2204,  2170,
  3046,  2161,  2979,  2014,  2180,  2002,  1161,  1975,  1017,  1966,
 -1000, -1000,  -298,  3550,  -591,   121,   106,  1941,   882,   879,
   876,  1916,  1905,   866,  1843,  -299,  3550, -1000,  3550,  -593,
 -1000,  3550,  3550,  3550,  3550, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000,  5622, -1000, -1000,
 -1000, -1000, -1000, -1000,  -594, -1000, -1000, -1000,  5622,  5622,
  5622,   662,  3550,  3550,  3855, -1000,  5622,  3550, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000,  3550,  3550, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,   596,
  1638,   810,   726,   692,  3550, -1000, -1000, -1000,  3550,  3550,
 -1000,  3550,   596,  1298,  1571,   861,  1480,  1254,  1170,  1071,
 -1000,  3550,  5622,  1002,  6552,  5712,   763,  1153,  1115,  3550,
 -1000,  -595,   -68,   -71,  5622,   564,   432,   398,  3550, -1000,
 -1000, -1000,  3550,  3550,  3550,  5622,   653,  3550, -1000, -1000,
   373, -1000, -1000, -1000,  -596,  -601,  3550,  5622,  5622,  5622,
  5622,  3550,  5622, -1000,   855,   854,   215,  5622, -1000, -1000,
  3550,    54,  3550,    11,  3550,    -4,  3550,  5622 };
yytabelem yypgo[]={

     0,     0,   112,  1263,  1262,  1260,   394,     5,     2,   515,
     3,  1259,  1258,     6,     4,  1257,   393,  1256,  1254,  1251,
  1244,  1240,  1239,  1234,  1228,   603,   406,  1227,  1226,  1223,
  1221,  1211,  1210,  1205,  1201,  1197,   681,   500,   680,   694,
  1193,  1191,  1181,  1177,     7,    10 };
yytabelem yyr1[]={

     0,    30,    30,    30,    30,    30,    30,    30,    30,    30,
    30,    30,    30,    30,    33,    33,    33,    33,    33,    33,
    16,    16,    16,    16,    16,    16,    16,    16,    17,    17,
    17,    17,    17,    17,    17,    17,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    22,    22,    22,    22,    22,    22,    22,
    22,    22,    22,    21,    21,    21,    21,    21,    21,    21,
    26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
    26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
    19,    19,    19,    19,    19,    19,    19,    19,    19,    19,
    18,    18,    18,    18,    18,    18,    32,    35,    34,    34,
    34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
    34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
    34,    34,    34,    31,    31,    31,    31,    31,    31,    36,
    36,    36,    36,    36,    36,    38,    38,    38,    39,    39,
    39,    39,    39,    39,    39,    37,    37,    37,    37,    37,
    40,    40,    44,    44,    44,    44,    44,    44,    44,    44,
    44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
    44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
    44,    44,    44,    41,    41,    45,    45,    45,    45,    45,
    45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
    45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
    45,    45,    45,    45,    45,    42,    42,    42,    42,    42,
    42,    42,    42,    42,    42,    42,    43,    43,    43,    43,
    20,    20,    20,    20,    20,    20,    23,    23,    23,    23,
    23,     6,     6,     7,     7,    27,    27,    27,    27,    27,
    28,    28,    28,    28,    25,    25,    24,    24,    24,    14,
    14,    14,    14,    14,    13,    13,    13,    29,    29,    29,
    29,     8,     8,    11,    11,    11,    10,    10,    10,    10,
    10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
    10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
    10,    10,    12,    12,    12,    15,    15,    15,    15,    15,
    15,     9,     9,     3,     3,     3,     3,     5,     4,     4,
     4,     4,     4,     4,     4,     4,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1 };
yytabelem yyr2[]={

     0,     0,     4,     4,     4,     5,     5,     4,     4,     4,
     4,     4,     4,     5,     7,     9,     7,     5,     7,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     5,     7,
     7,     7,     7,    19,    11,     9,     3,     7,     5,     7,
    17,     3,     5,     5,     7,     7,     5,     5,     5,     3,
     5,     5,     5,     5,     5,     5,     5,     7,    11,    15,
     9,    17,     9,    17,     5,     5,     5,     5,     3,    15,
    13,    13,    13,    21,    21,    13,     9,     3,     5,     5,
     5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
     7,     7,     7,     7,     9,     3,     3,     3,     5,    35,
     5,     5,     5,     7,     5,     5,    17,     7,     7,     7,
     7,     7,     9,     9,     5,     5,     7,     5,     5,     5,
    17,     7,     7,     7,     7,     7,     9,     9,     5,     5,
     5,     7,     5,     5,     9,     7,     7,     7,     7,     7,
     7,     9,     7,     7,     7,     7,     9,     7,     9,     9,
    17,     7,     7,     7,     7,    17,     7,     7,     7,     7,
     5,     7,     7,     7,     7,     5,     7,     7,     7,     7,
     9,     5,     7,     7,     7,     7,     7,     7,     9,    11,
    11,     9,     9,     9,     9,     7,     7,     9,     7,     7,
     7,     7,     9,     5,     7,     7,     7,     7,     7,     9,
     5,     7,     9,     9,     7,     7,     7,     7,    11,    13,
    13,     9,     9,     7,     7,     7,     7,     7,     7,     9,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     2,     2,     2,     2,     2,     2,     4,     1,     7,     5,
     5,     5,     5,     5,     7,     7,     7,     7,     7,     5,
     5,     7,     7,     5,     7,     7,     7,     7,     7,     9,
     9,     9,     5,     2,     4,     2,     4,     6,     4,     2,
     2,     2,     2,     2,     2,     4,     4,     4,     3,     5,
     5,     5,     5,     7,     5,     4,     4,     4,     4,     3,
     2,     4,     3,     5,     5,     5,     5,     5,     5,     5,
     5,     5,     5,     3,     5,     5,     7,     7,     5,     5,
     7,     7,     7,     7,     7,     7,     7,     7,     5,     5,
     5,     5,     7,     2,     4,     3,     5,     5,     5,     5,
     5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
     5,     5,     5,     5,     7,     7,     7,     7,     5,     5,
     7,     5,     5,     5,     7,     3,     5,     5,     5,     5,
     9,     5,     7,     5,     5,     5,     3,     5,     5,     5,
     7,     3,     3,     5,     5,     5,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,    13,    13,    17,    21,    11,     7,     7,
    11,    15,     7,     7,    11,    15,     3,     3,    11,     7,
     3,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     7,     9,     9,     9,     9,     9,    13,     9,     9,     3,
     3,     3,     9,     9,     9,     9,    13,    13,    13,    13,
     3,     3,     9,     9,    13,    13,     9,     9,     9,     9,
    17,    13,    13,    13,     9,     9,     3,     3,     3,    13,
    13,    13,    13,     9,     9,     9,     9,    11,     7,     7,
     7,     7,     7,     7,     7,     7,     5,     7,     5,     2,
     3,     9,     9,     7,    13,     7,     7,    13,    17,     7,
     7,     7,     7,     7,     7,     9,     9,     9,     9,    13,
     9,     9,     3,     3,     3,     9,     9,     9,     9,    13,
     7,     7,     7,     7,     7,     7,     7,     7,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     9,     9,
    13,     9,     9,     9,     9,    17,    13,    13,    13,     9,
     9,     3,     3,     3,    13,     9,     9,     9,     9,    11,
     7,     7,     7,     7,     7,     7,     7,     7,     5,     7,
     5 };
yytabelem yychk[]={

 -1000,   -30,    -3,    -4,    -5,    -1,    -2,   -22,   -17,   -31,
   -21,   -32,   -33,   256,   613,   612,   492,   382,   476,   616,
   617,   323,   257,   258,   259,   260,   261,   262,   263,   264,
   265,   266,   267,   268,   269,   270,   271,   296,   297,   298,
   299,   300,   301,   302,   303,   272,   290,   273,   274,   275,
   276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
   286,   287,   288,   289,   291,   292,   293,   294,   627,    40,
    45,   474,   320,   359,   327,   341,   364,   447,   420,   305,
   378,   326,   514,   497,   304,   308,   380,   472,   529,   309,
   344,   432,   406,   372,   421,   475,   -27,   -28,   611,   393,
   352,   321,   422,   373,   499,   523,   473,   330,   470,   471,
   345,   503,   339,   334,   416,   512,   348,   530,   528,   519,
   513,   383,   412,   379,   -36,   -38,   525,   -20,   464,   350,
   386,   483,   485,   484,   487,   486,   351,   367,   403,   404,
   538,   567,   313,   314,   571,   572,   325,   537,   566,   493,
    10,    10,    10,    10,    43,    45,    42,    47,    94,    37,
    63,   620,   621,   622,   623,   624,   625,   619,   618,    10,
    43,    45,    42,    47,    94,    63,   620,   621,   622,   623,
   624,   625,   619,   618,    10,    10,    10,    10,    10,    10,
    10,    91,    61,    91,    61,   459,    46,    46,    -6,   407,
   321,   389,   523,   371,   281,   493,   443,   440,    -6,   523,
   342,   417,   419,   416,   542,    46,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    -2,    -1,   613,
   612,   382,   492,   273,   476,    -2,    -1,    -2,    -1,   474,
   338,   342,   616,   -15,   616,   400,   524,   306,   480,   411,
   397,   446,   476,   447,    -8,   522,   366,    -8,    -8,   616,
   616,    -8,   338,   338,   382,   492,   334,   416,   512,   492,
   492,   382,   492,   382,   492,   493,   382,   383,   613,    40,
    40,    40,    40,    40,    40,   537,   566,   492,    -6,   382,
    -6,   491,   374,   340,   -25,   353,   457,   -26,   542,   543,
   544,   546,   547,   548,   549,   550,   551,   552,   553,   554,
   555,   556,   557,   558,   559,   560,   439,   331,   338,   329,
   330,   -26,   -26,   616,   530,   503,   334,   416,   512,    -6,
   382,    -1,   423,   417,   419,   342,   369,   347,   613,   612,
   492,   257,   258,   259,   260,   261,   262,   263,   264,   265,
   266,   267,   268,   269,   270,   271,   272,   290,   273,   274,
   275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
   285,   286,   287,   288,   289,   291,   292,   293,   294,   627,
    40,    45,    -6,   382,    -1,   423,   419,   417,   342,   319,
   347,    -6,   382,    -1,   423,   419,   342,   482,   375,   405,
   337,   347,   417,   419,   342,   337,   375,   515,    -1,   541,
   540,   570,   569,   382,    -1,   541,   540,   570,   569,   338,
   375,   495,   342,   419,   338,   375,   495,   342,   419,   281,
   -36,   -38,   493,   492,    -6,   423,   408,   527,   388,   413,
   334,    -1,   532,   561,   337,   375,   417,   419,   342,   512,
    -6,   523,   417,   419,   342,   369,   327,   -37,   516,   517,
   407,   328,    -6,   489,   412,   419,   417,   342,   423,   319,
   -34,    -6,   523,   431,   462,   377,   515,   -23,   369,   496,
   363,   558,   343,   417,   419,   375,   342,   495,   -16,   520,
   467,   469,   429,   428,   392,   391,   386,   368,   616,   350,
   -39,    -6,   342,   419,   417,   375,   337,   385,   -39,   -39,
    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -1,    -2,
    -2,    -1,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
    -1,    -2,    -1,    -1,    -2,    -1,    -1,   612,   -29,   413,
   541,   540,   570,   569,   492,   296,   297,   298,   299,   300,
   301,   302,   303,    -6,   523,    -8,    -8,   -19,   542,   424,
   425,   426,   328,   387,   504,   505,   460,   545,    -6,   377,
   462,   542,   523,   493,   -18,   573,   574,   411,   480,   575,
   576,   616,   616,   616,    -1,    -1,   612,   492,    -1,    -2,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,
    -2,    -1,   492,    -2,    -1,    -2,    -1,    -1,    -2,   616,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    91,    91,
    46,    46,    40,    46,    41,    41,    -6,   616,    44,   616,
   520,    -6,   616,   616,   616,   616,   520,    46,   520,    46,
   616,   492,   492,   492,   492,   492,   492,   338,   338,   338,
   -25,   338,    -1,    46,    44,    43,    45,    42,    47,    94,
    -9,   530,   528,   616,   616,   616,   -24,   342,   452,   437,
    46,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
    40,    -1,    -1,    -1,    44,    -9,   616,   616,   616,   616,
   495,   523,    44,    -9,   616,   616,   616,   616,   616,   495,
   338,   616,   616,   616,   495,   616,   499,   495,    44,    -1,
    -1,    -1,    -1,    44,   616,   616,   616,   616,   616,   616,
   616,   616,   616,   616,   616,   616,   493,   -37,    -9,   616,
   616,   616,   616,    -6,   369,   342,   417,   419,    44,    -1,
    -1,   495,   616,   616,   616,   616,   616,   616,   616,   616,
   616,    -6,   342,   -40,   -44,    -6,   427,   430,   441,   442,
   311,   282,   281,   348,   -11,   279,   495,   342,   419,   444,
   523,   500,   616,   397,   446,   332,   -41,   -45,    -6,   523,
   462,   377,   317,   463,   408,   315,   405,   496,   507,   444,
   494,   508,   511,   527,   388,   337,   375,   342,   419,   616,
   -42,   338,   408,   458,   405,   337,   375,   342,   419,   -43,
    -6,   342,   417,   419,   616,    -6,   616,   616,   616,    -9,
   523,   -35,   -26,    -1,   616,   -10,   346,   365,   461,   577,
   578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
   588,   589,   590,   591,   592,   593,   594,   595,   596,   597,
   598,   599,   616,   369,   336,   495,   337,   496,   616,   616,
   529,    -7,   342,   452,   616,   413,   523,   419,   417,   481,
    -1,   338,   338,   -16,   616,   616,   616,   616,   616,   495,
    -6,    58,    58,    93,    93,    44,    91,    61,   459,    46,
   320,   500,   -10,   616,    -1,   616,   616,    44,    44,    61,
    44,    41,    41,    41,    41,    41,    41,    41,    41,    44,
    44,    41,    41,    41,    41,    41,    41,    41,    41,    41,
    41,    41,    41,    44,    44,    41,    41,    41,    41,    41,
    44,    44,    41,    41,    41,    41,    41,    41,    41,    44,
    44,    44,    44,    44,    44,    44,    44,    41,    41,    41,
    41,    44,    44,    41,    41,    41,    41,    41,    41,    41,
    41,    -1,    -1,   492,   612,   612,   616,   382,   492,   492,
   492,   492,    44,    44,    44,    44,    44,    44,    44,   338,
    44,   492,    -1,    -1,    -1,    -1,    -1,    -1,   616,   616,
   612,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   616,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   616,   616,    -1,   616,   616,   616,   616,    -1,
    -1,   616,    -6,   529,    -7,   616,   616,   616,    -1,   616,
   338,   616,   -44,    -6,    -1,   495,   342,   419,   417,   385,
    -6,    -1,   495,   342,   419,   417,   385,    -1,    -1,    -6,
    -1,    -1,   616,    -6,   616,   616,   616,   -14,   521,   333,
   411,   480,   332,   320,   500,   616,    44,   -45,   320,   500,
   616,   -10,   616,   338,   338,   390,   526,   500,   616,   -13,
   480,   411,   336,   616,   616,   -14,   -12,   438,   307,   435,
    -1,   523,    -1,   523,   616,   616,   495,   616,   616,   616,
    44,   454,   448,   320,   500,   616,   -13,   495,   616,   616,
   616,   616,   616,   616,   616,   395,   616,    -8,   616,   616,
   616,    -7,   616,   616,   -14,   616,   616,    -6,   419,   417,
    44,   338,   616,    -1,    -2,    61,    61,    -1,    -1,    -2,
    -1,    -1,   612,   -10,    44,    44,    -1,    -1,    -1,   612,
    -2,    -1,    -2,    -1,    -2,    -1,   616,   616,    -1,    -1,
    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,    -2,    -1,
    93,    93,    46,    91,    44,   520,   520,    -1,   616,   616,
   616,    -1,    -1,   616,    -1,    46,    44,    41,    44,    44,
    41,    44,    44,    44,    44,    -7,   616,   616,   616,   616,
   616,    -6,   616,   616,   616,   616,    -6,    -1,   500,   320,
   500,   320,   616,   338,    44,   616,   616,   616,    -1,    -1,
    -1,    93,    44,    91,    61,   616,    -1,    44,    41,    41,
    41,    41,    41,    41,    41,    41,    41,    44,    44,    41,
    41,    41,    41,    41,    41,    41,    41,    41,    41,   612,
    -1,   616,   382,   382,    44,    41,    41,    41,    44,    44,
    41,    44,   612,    -1,    -1,   616,    -1,    -1,    -1,    -1,
   616,    61,    -1,    -1,    -2,    -1,    -1,    -1,    -1,    91,
    93,    44,    46,    46,    -1,    -1,    -1,    -1,    44,    41,
    41,    41,    44,    44,    44,    -1,    93,    44,    41,    41,
    -1,   616,   492,   492,    44,    44,    44,    -1,    -1,    -1,
    -1,    61,    -1,    93,   616,   616,    -1,    -1,    41,    41,
   516,    -1,    44,    -1,    44,    -1,    44,    -1 };
yytabelem yydef[]={

     1,    -2,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   486,   487,   391,     0,     0,   569,
   570,     0,     0,     0,     0,     0,     0,     0,     0,    -2,
    -2,    -2,     0,     0,     0,     0,     0,   608,   609,   610,
   611,   612,   613,   614,   615,    -2,    -2,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -2,    -2,    -2,     0,     0,     0,     0,     0,     0,     0,
     0,    36,     0,     0,     0,     0,    41,     0,     0,     0,
     0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
     0,    77,     0,     0,     0,     0,     0,     0,    95,    96,
    97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   283,   285,     0,     0,     0,     0,
    19,   405,   406,   407,   408,   409,   410,   411,   412,   413,
   289,   290,   291,   292,   293,   294,     0,     0,     0,   392,
     2,     3,     4,     5,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     7,     8,     9,    10,    11,    12,
    13,     0,     0,     0,     0,     0,     0,     0,   200,     0,
     0,     0,     0,     0,     0,   393,   401,   402,    28,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   566,    -2,   486,
   487,     0,     0,     0,     0,     0,     0,   568,    -2,     0,
    38,     0,     0,    42,    43,     0,   465,   466,   467,   468,
   469,   470,     0,     0,    46,   431,   432,    47,    48,    50,
    51,    52,    53,    54,    55,    56,   102,   115,   130,     0,
     0,     0,     0,     0,    64,    65,    66,    67,     0,     0,
     0,     0,     0,     0,     0,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,   414,   415,    88,   220,   221,
   222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
   232,   233,   234,   235,   236,   237,   238,   239,    89,     0,
     0,     0,     0,    98,     0,   100,   101,   117,   129,   104,
   105,     0,     0,     0,     0,     0,     0,   114,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   592,   593,
   594,     0,     0,     0,     0,     0,   616,   617,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   631,   632,   633,     0,     0,     0,     0,     0,     0,
     0,     0,   118,   119,     0,     0,     0,     0,     0,     0,
   128,   132,   133,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   160,
     0,     0,     0,     0,   165,     0,     0,     0,     0,     0,
   286,   288,   394,   395,   171,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   193,     0,     0,     0,     0,     0,     0,   284,     0,     0,
     0,     0,   309,     0,     0,     0,     0,     0,     0,     0,
   256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   396,   397,   398,   399,   400,     0,     0,
    20,    21,    22,    23,    24,    25,    26,    27,    17,     0,
   295,   298,     0,     0,     0,     0,     0,     0,   296,   297,
    -2,   493,    -2,   497,    -2,   501,    -2,   505,    -2,   508,
   583,     0,    -2,    -2,    -2,    -2,    -2,    -2,   646,   647,
   492,    -2,   496,    -2,   500,    -2,   504,    -2,    -2,   510,
     0,   490,    -2,    -2,    -2,    -2,    -2,    -2,   564,   565,
     0,   478,   482,     0,   479,   483,     0,   489,   575,   576,
   427,   428,   429,   430,   390,   600,   601,   602,   603,   604,
   605,   606,   607,   201,     0,   204,   205,   206,   240,   241,
   242,   243,   244,   245,   246,   247,   248,   249,   207,     0,
     0,     0,     0,     0,    29,   250,   251,   252,   253,   254,
   255,    30,    31,    32,     0,     0,   573,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   567,   649,    37,    39,     0,    44,
     0,    45,   103,   116,   131,    57,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    90,    91,    93,
     0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
   107,   471,   472,   108,   109,   110,   111,   417,   416,   418,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   648,     0,   650,     0,   121,   122,   123,   124,   125,
     0,     0,     0,   135,   136,   137,   138,   139,   140,     0,
   142,   143,   144,   145,     0,   147,     0,     0,     0,   151,
   152,   153,   154,     0,   156,   157,   158,   159,   161,   162,
   163,   164,   166,   167,   168,   169,     0,   287,   172,   173,
   174,   175,   176,   177,     0,     0,     0,     0,     0,   185,
   186,     0,   188,   189,   190,   191,     0,   194,   195,   196,
   197,   198,     0,   305,   310,   312,     0,     0,     0,     0,
     0,     0,     0,     0,   323,     0,     0,     0,     0,     0,
     0,     0,     0,   433,   434,   435,   306,   343,   345,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   307,   375,     0,     0,     0,     0,     0,     0,     0,   308,
   386,     0,     0,     0,   213,   214,   215,   216,   217,   218,
     0,     0,   259,   260,   261,   262,   436,   437,   438,   439,
   440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
   450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
   460,   461,   263,     0,     0,     0,     0,     0,   269,   270,
     0,     0,   403,   404,   273,     0,     0,     0,     0,     0,
     0,   282,    14,    16,    18,   299,   300,   301,   302,     0,
   304,     0,     0,   571,   572,     0,     0,     0,     0,     0,
   202,   203,     0,     0,     0,   211,   212,     0,     0,     0,
     0,    -2,   512,   513,   586,   514,   587,   515,   588,     0,
     0,   517,   590,   518,   591,   522,   595,   523,   596,   524,
   597,   525,   598,     0,     0,    76,   532,   618,   533,   619,
     0,     0,    -2,   537,   622,   538,   623,   539,   624,     0,
     0,     0,     0,     0,     0,     0,     0,   544,   629,   545,
   630,     0,     0,   553,   635,   554,   636,   555,   637,   556,
   638,     0,     0,     0,   489,   573,     0,    35,    60,     0,
    62,     0,     0,     0,     0,     0,     0,     0,     0,    94,
     0,     0,     0,   579,   580,   581,   582,   584,   112,   113,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   126,   127,   134,   141,   146,   148,   149,     0,
     0,   170,   178,     0,     0,   181,   182,   183,   184,   187,
   192,   199,   311,   313,   315,     0,     0,     0,     0,     0,
   314,   316,     0,     0,     0,     0,     0,   317,   318,   319,
   320,   321,   322,   324,   325,   328,   329,   338,   419,   420,
   421,   422,   423,   339,   340,   341,     0,   344,   346,   347,
   348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
   424,   425,   426,   358,   359,   360,   361,   462,   463,   464,
   362,     0,   363,     0,   368,   369,     0,   371,   372,   373,
     0,   376,   377,   378,   379,     0,   381,     0,   383,   384,
   385,   387,   388,   389,   219,   258,   264,   265,   266,   267,
   268,   271,   272,   274,   275,   276,   277,   278,     0,     0,
     0,    15,   303,   639,   557,     0,     0,    58,     0,   480,
   484,     0,   488,   208,     0,     0,     0,    34,   477,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   571,   572,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   585,     0,     0,
   621,     0,     0,     0,     0,   179,   180,   326,   330,   332,
   334,   336,   327,   331,   333,   335,   337,   342,   364,   365,
   366,   367,   370,   374,     0,   382,   279,   280,   281,   473,
   474,   574,     0,     0,     0,   209,   210,     0,   577,   516,
   589,   526,   528,   527,    -2,    -2,   535,     0,     0,   541,
   626,   542,   627,   543,   628,   549,   551,   550,    -2,   488,
     0,     0,     0,     0,     0,    70,    71,    72,     0,     0,
    75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   380,     0,    59,     0,   481,   485,     0,     0,     0,     0,
   574,     0,     0,     0,    69,     0,     0,     0,     0,   599,
   620,   634,     0,     0,     0,   475,   578,     0,   540,   625,
     0,    40,    61,    63,     0,     0,     0,   106,   120,   150,
   155,     0,    33,   578,     0,     0,     0,   476,    73,    74,
     0,     0,     0,     0,     0,     0,     0,    99 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	1	/* allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"ABS",	257,
	"ACOS",	258,
	"ASIN",	259,
	"ATAN",	260,
	"ATAN2",	261,
	"CEIL",	262,
	"COS",	263,
	"DEG",	264,
	"DX",	265,
	"DY",	266,
	"ERF",	267,
	"ERFC",	268,
	"EXP",	269,
	"FLOOR",	270,
	"HYPOT",	271,
	"INDEX",	272,
	"INT",	273,
	"INVN",	274,
	"INVT",	275,
	"IRAND",	276,
	"LGAMMA",	277,
	"LN",	278,
	"LOG",	279,
	"LOGISTIC",	280,
	"MAXP",	281,
	"MINP",	282,
	"MOD",	283,
	"NORM",	284,
	"NORMP",	285,
	"PI",	286,
	"RAD",	287,
	"RAND",	288,
	"RNORM",	289,
	"SETNO",	290,
	"SIN",	291,
	"SQR",	292,
	"SQRT",	293,
	"TAN",	294,
	"INUM",	295,
	"VX1",	296,
	"VX2",	297,
	"VY1",	298,
	"VY2",	299,
	"WX1",	300,
	"WX2",	301,
	"WY1",	302,
	"WY2",	303,
	"DELAYP",	304,
	"DOUBLEBUFFER",	305,
	"DOWN",	306,
	"ABSOLUTE",	307,
	"ABORT",	308,
	"ACTIVATE",	309,
	"ACTIVE",	310,
	"ALT",	311,
	"ALTERNATE",	312,
	"ALTXAXIS",	313,
	"ALTYAXIS",	314,
	"ANGLE",	315,
	"ANNOTATE",	316,
	"APPEND",	317,
	"AREA",	318,
	"ARROW",	319,
	"AUTO",	320,
	"AUTOSCALE",	321,
	"AUTOTICKS",	322,
	"AVG",	323,
	"AXIS",	324,
	"AXES",	325,
	"BACKBUFFER",	326,
	"BACKGROUND",	327,
	"BAR",	328,
	"BATCH",	329,
	"BLOCK",	330,
	"BIN",	331,
	"BOTH",	332,
	"BOTTOM",	333,
	"BOX",	334,
	"CELLS",	335,
	"CENTER",	336,
	"CHAR",	337,
	"CHRSTR",	338,
	"CLEAR",	339,
	"CLICK",	340,
	"CMAP",	341,
	"COLOR",	342,
	"COMMENT",	343,
	"COPY",	344,
	"CYCLE",	345,
	"DECIMAL",	346,
	"DEF",	347,
	"DEFAULT",	348,
	"DELETE",	349,
	"DEVICE",	350,
	"DFT",	351,
	"DIFFERENCE",	352,
	"DISK",	353,
	"DRAW2",	354,
	"DXDX",	355,
	"DXP",	356,
	"DYDY",	357,
	"DYP",	358,
	"ECHO",	359,
	"EDIT",	360,
	"ELSE",	361,
	"END",	362,
	"ERRORBAR",	363,
	"EXIT",	364,
	"EXPONENTIAL",	365,
	"FALSEP",	366,
	"FFT",	367,
	"FILEP",	368,
	"FILL",	369,
	"FIND",	370,
	"FIXEDPOINT",	371,
	"FLUSH",	372,
	"FOCUS",	373,
	"FOLLOWS",	374,
	"FONTP",	375,
	"FOREGROUND",	376,
	"FORMAT",	377,
	"FRONTBUFFER",	378,
	"FRAMEP",	379,
	"GETP",	380,
	"GRAPH",	381,
	"GRAPHNO",	382,
	"GRAPHS",	383,
	"GRAPHTYPE",	384,
	"GRID",	385,
	"HARDCOPY",	386,
	"HBAR",	387,
	"HGAP",	388,
	"HIDDEN",	389,
	"HORIZONTAL",	390,
	"HPGLL",	391,
	"HPGLP",	392,
	"HISTO",	393,
	"IF",	394,
	"IGNORE",	395,
	"IHL",	396,
	"IN",	397,
	"INIT",	398,
	"INITGRAPHICS",	399,
	"INOUT",	400,
	"INTEGRATE",	401,
	"INTERP",	402,
	"INVDFT",	403,
	"INVFFT",	404,
	"JUST",	405,
	"KILL",	406,
	"LABEL",	407,
	"LAYOUT",	408,
	"LEAVE",	409,
	"LEAVEGRAPHICS",	410,
	"LEFT",	411,
	"LEGEND",	412,
	"LENGTH",	413,
	"LEVEL",	414,
	"LEVELS",	415,
	"LINE",	416,
	"LINESTYLE",	417,
	"LINETO",	418,
	"LINEWIDTH",	419,
	"LINK",	420,
	"LOAD",	421,
	"LOCATOR",	422,
	"LOCTYPE",	423,
	"LOGX",	424,
	"LOGY",	425,
	"LOGXY",	426,
	"MAJOR",	427,
	"MIFL",	428,
	"MIFP",	429,
	"MINOR",	430,
	"MISSINGP",	431,
	"MOVE",	432,
	"MOVE2",	433,
	"MOVETO",	434,
	"NEGATE",	435,
	"NO",	436,
	"NONE",	437,
	"NORMAL",	438,
	"NXY",	439,
	"OFF",	440,
	"OFFSETX",	441,
	"OFFSETY",	442,
	"ON",	443,
	"OP",	444,
	"ORIENT",	445,
	"OUT",	446,
	"PAGE",	447,
	"PARA",	448,
	"PARALLEL",	449,
	"PARAMETERS",	450,
	"PARAMS",	451,
	"PATTERN",	452,
	"PERIMETER",	453,
	"PERP",	454,
	"PERPENDICULAR",	455,
	"PIE",	456,
	"PIPE",	457,
	"PLACE",	458,
	"POINT",	459,
	"POLAR",	460,
	"POWER",	461,
	"PREC",	462,
	"PREPEND",	463,
	"PRINT",	464,
	"PS",	465,
	"PSCOLORP",	466,
	"PSMONOP",	467,
	"PSCOLORL",	468,
	"PSMONOL",	469,
	"PUSH",	470,
	"POP",	471,
	"PUTP",	472,
	"READ",	473,
	"REDRAW",	474,
	"REGRESS",	475,
	"REGNUM",	476,
	"REGIONS",	477,
	"RENDER",	478,
	"REVERSE",	479,
	"RIGHT",	480,
	"RISER",	481,
	"ROT",	482,
	"RUNAVG",	483,
	"RUNMED",	484,
	"RUNSTD",	485,
	"RUNMIN",	486,
	"RUNMAX",	487,
	"SAMPLE",	488,
	"SCALE",	489,
	"SCIENTIFIC",	490,
	"SET",	491,
	"SETNUM",	492,
	"SETS",	493,
	"SIGN",	494,
	"SIZE",	495,
	"SKIP",	496,
	"SLEEP",	497,
	"SLICE",	498,
	"SOURCE",	499,
	"SPEC",	500,
	"SPECIFIED",	501,
	"SPECTRUM",	502,
	"STACK",	503,
	"STACKEDBAR",	504,
	"STACKEDHBAR",	505,
	"STACKEDLINE",	506,
	"STAGGER",	507,
	"START",	508,
	"STARTTYPE",	509,
	"STATUS",	510,
	"STOP",	511,
	"STRING",	512,
	"SUBTITLE",	513,
	"SWAPBUFFER",	514,
	"SYMBOL",	515,
	"TICK",	516,
	"TICKLABEL",	517,
	"TICKMARKS",	518,
	"TITLE",	519,
	"TO",	520,
	"TOP",	521,
	"TRUEP",	522,
	"TYPE",	523,
	"UP",	524,
	"VELOCITY",	525,
	"VERTICAL",	526,
	"VGAP",	527,
	"VIEW",	528,
	"WITH",	529,
	"WORLD",	530,
	"WRITE",	531,
	"X1",	532,
	"X2",	533,
	"X3",	534,
	"X4",	535,
	"X5",	536,
	"XAXES",	537,
	"XAXIS",	538,
	"XCOR",	539,
	"XMAX",	540,
	"XMIN",	541,
	"XY",	542,
	"XYARC",	543,
	"XYBOX",	544,
	"XYFIXED",	545,
	"XYHILO",	546,
	"XYRT",	547,
	"XYSEG",	548,
	"XYSTRING",	549,
	"XYDX",	550,
	"XYDY",	551,
	"XYDXDX",	552,
	"XYDYDY",	553,
	"XYDXDY",	554,
	"XYX2Y2",	555,
	"XYXX",	556,
	"XYYY",	557,
	"XYZ",	558,
	"XYZW",	559,
	"XYUV",	560,
	"Y1",	561,
	"Y2",	562,
	"Y3",	563,
	"Y4",	564,
	"Y5",	565,
	"YAXES",	566,
	"YAXIS",	567,
	"YES",	568,
	"YMAX",	569,
	"YMIN",	570,
	"ZEROXAXIS",	571,
	"ZEROYAXIS",	572,
	"ABOVE",	573,
	"BELOW",	574,
	"POLYI",	575,
	"POLYO",	576,
	"GENERAL",	577,
	"DDMMYY",	578,
	"MMDDYY",	579,
	"MMYY",	580,
	"MMDD",	581,
	"MONTHDAY",	582,
	"DAYMONTH",	583,
	"MONTHS",	584,
	"MONTHL",	585,
	"DAYOFWEEKS",	586,
	"DAYOFWEEKL",	587,
	"DAYOFYEAR",	588,
	"HMS",	589,
	"MMDDHMS",	590,
	"MMDDYYHMS",	591,
	"DEGREESLON",	592,
	"DEGREESMMLON",	593,
	"DEGREESMMSSLON",	594,
	"MMSSLON",	595,
	"DEGREESLAT",	596,
	"DEGREESMMLAT",	597,
	"DEGREESMMSSLAT",	598,
	"MMSSLAT",	599,
	"DOT",	600,
	"STAR",	601,
	"PLUS",	602,
	"CROSS",	603,
	"CIRCLE",	604,
	"SQUARE",	605,
	"DIAMOND",	606,
	"TRIANGLE1",	607,
	"TRIANGLE2",	608,
	"TRIANGLE3",	609,
	"TRIANGLE4",	610,
	"SPLINE",	611,
	"SVAR",	612,
	"VAR",	613,
	"X",	614,
	"Y",	615,
	"NUMBER",	616,
	"FITPARM",	617,
	"=",	61,
	"OR",	618,
	"AND",	619,
	"GT",	620,
	"LT",	621,
	"LE",	622,
	"GE",	623,
	"EQ",	624,
	"NE",	625,
	"+",	43,
	"-",	45,
	"*",	42,
	"/",	47,
	"%",	37,
	"^",	94,
	"UMINUS",	626,
	"NOT",	627,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
      "list : /* empty */",
      "list : asgn '\n'",
      "list : vasgn '\n'",
      "list : rasgn '\n'",
      "list : expr '\n'",
      "list : vexpr '\n'",
      "list : parmset '\n'",
      "list : regionset '\n'",
      "list : setaxis '\n'",
      "list : setvelocity '\n'",
      "list : set_setprop '\n'",
      "list : setprint '\n'",
      "list : error '\n'",
      "setprint : PRINT printer CHRSTR",
      "setprint : PRINT TO printer CHRSTR",
      "setprint : PRINT TO printer",
      "setprint : DEVICE NUMBER",
      "setprint : HARDCOPY DEVICE NUMBER",
      "setprint : HARDCOPY",
      "printer : PSMONOP",
      "printer : PSMONOL",
      "printer : MIFP",
      "printer : MIFL",
      "printer : HPGLP",
      "printer : HPGLL",
      "printer : HARDCOPY",
      "printer : FILEP",
      "regionset : REGNUM onoff",
      "regionset : REGNUM TYPE regiontype",
      "regionset : REGNUM COLOR NUMBER",
      "regionset : REGNUM LINESTYLE NUMBER",
      "regionset : REGNUM LINEWIDTH NUMBER",
      "regionset : REGNUM LINE expr ',' expr ',' expr ',' expr",
      "regionset : REGNUM XY expr ',' expr",
      "regionset : LINK REGNUM TO GRAPHNO",
      "parmset : REDRAW",
      "parmset : AUTO REDRAW onoff",
      "parmset : ECHO CHRSTR",
      "parmset : BACKGROUND COLOR NUMBER",
      "parmset : CMAP NUMBER ',' NUMBER ',' NUMBER ',' NUMBER",
      "parmset : EXIT",
      "parmset : PAGE direction",
      "parmset : PAGE NUMBER",
      "parmset : PAGE INOUT NUMBER",
      "parmset : LINK PAGE onoff",
      "parmset : DOUBLEBUFFER torf",
      "parmset : FRONTBUFFER torf",
      "parmset : BACKBUFFER torf",
      "parmset : SWAPBUFFER",
      "parmset : SLEEP NUMBER",
      "parmset : DELAYP NUMBER",
      "parmset : ABORT torf",
      "parmset : GETP CHRSTR",
      "parmset : PUTP CHRSTR",
      "parmset : WITH GRAPHNO",
      "parmset : WITH SETNUM",
      "parmset : ACTIVATE SETNUM NUMBER",
      "parmset : SETNUM POINT expr ',' expr",
      "parmset : GRAPHNO '.' SETNUM POINT expr ',' expr",
      "parmset : COPY SETNUM TO SETNUM",
      "parmset : COPY GRAPHNO '.' SETNUM TO GRAPHNO '.' SETNUM",
      "parmset : MOVE SETNUM TO SETNUM",
      "parmset : MOVE GRAPHNO '.' SETNUM TO GRAPHNO '.' SETNUM",
      "parmset : KILL SETNUM",
      "parmset : KILL SETS",
      "parmset : KILL GRAPHNO",
      "parmset : KILL GRAPHS",
      "parmset : FLUSH",
      "parmset : LOAD VAR NUMBER ',' expr ',' expr",
      "parmset : REGRESS '(' SETNUM ',' NUMBER ')'",
      "parmset : runtype '(' SETNUM ',' NUMBER ')'",
      "parmset : ffttype '(' SETNUM ',' NUMBER ')'",
      "parmset : SPLINE '(' SETNUM ',' expr ',' expr ',' NUMBER ')'",
      "parmset : HISTO '(' SETNUM ',' expr ',' expr ',' NUMBER ')'",
      "parmset : DIFFERENCE '(' SETNUM ',' NUMBER ')'",
      "parmset : INT '(' SETNUM ')'",
      "parmset : AUTOSCALE",
      "parmset : AUTOSCALE XAXES",
      "parmset : AUTOSCALE YAXES",
      "parmset : AUTOSCALE SETNUM",
      "parmset : LOCATOR onoff",
      "parmset : FOCUS GRAPHNO",
      "parmset : FOCUS onoff",
      "parmset : FOCUS SET",
      "parmset : FOCUS FOLLOWS",
      "parmset : FOCUS CLICK",
      "parmset : SOURCE sourcetype",
      "parmset : TYPE xytype",
      "parmset : READ CHRSTR",
      "parmset : READ BATCH CHRSTR",
      "parmset : READ BLOCK CHRSTR",
      "parmset : BLOCK xytype CHRSTR",
      "parmset : READ xytype CHRSTR",
      "parmset : READ xytype sourcetype CHRSTR",
      "parmset : PUSH",
      "parmset : POP",
      "parmset : CYCLE",
      "parmset : STACK NUMBER",
      "parmset : STACK WORLD expr ',' expr ',' expr ',' expr TICK expr ',' expr ',' expr ',' expr",
      "parmset : CLEAR STACK",
      "parmset : CLEAR BOX",
      "parmset : WITH BOX",
      "parmset : WITH BOX NUMBER",
      "parmset : BOX onoff",
      "parmset : BOX GRAPHNO",
      "parmset : BOX expr ',' expr ',' expr ',' expr",
      "parmset : BOX LOCTYPE worldview",
      "parmset : BOX LINESTYLE NUMBER",
      "parmset : BOX LINEWIDTH NUMBER",
      "parmset : BOX COLOR NUMBER",
      "parmset : BOX FILL filltype",
      "parmset : BOX FILL COLOR NUMBER",
      "parmset : BOX FILL PATTERN NUMBER",
      "parmset : BOX DEF",
      "parmset : WITH LINE",
      "parmset : WITH LINE NUMBER",
      "parmset : CLEAR LINE",
      "parmset : LINE onoff",
      "parmset : LINE GRAPHNO",
      "parmset : LINE expr ',' expr ',' expr ',' expr",
      "parmset : LINE LOCTYPE worldview",
      "parmset : LINE LINEWIDTH NUMBER",
      "parmset : LINE LINESTYLE NUMBER",
      "parmset : LINE COLOR NUMBER",
      "parmset : LINE ARROW NUMBER",
      "parmset : LINE ARROW SIZE NUMBER",
      "parmset : LINE ARROW TYPE NUMBER",
      "parmset : LINE DEF",
      "parmset : CLEAR STRING",
      "parmset : WITH STRING",
      "parmset : WITH STRING NUMBER",
      "parmset : STRING onoff",
      "parmset : STRING GRAPHNO",
      "parmset : STRING expr ',' expr",
      "parmset : STRING LOCTYPE worldview",
      "parmset : STRING LINEWIDTH NUMBER",
      "parmset : STRING COLOR NUMBER",
      "parmset : STRING ROT NUMBER",
      "parmset : STRING FONTP NUMBER",
      "parmset : STRING JUST NUMBER",
      "parmset : STRING CHAR SIZE NUMBER",
      "parmset : STRING DEF CHRSTR",
      "parmset : DEFAULT LINESTYLE NUMBER",
      "parmset : DEFAULT LINEWIDTH NUMBER",
      "parmset : DEFAULT COLOR NUMBER",
      "parmset : DEFAULT CHAR SIZE NUMBER",
      "parmset : DEFAULT FONTP NUMBER",
      "parmset : DEFAULT FONTP SOURCE NUMBER",
      "parmset : DEFAULT SYMBOL SIZE NUMBER",
      "parmset : WORLD expr ',' expr ',' expr ',' expr",
      "parmset : WORLD XMIN expr",
      "parmset : WORLD XMAX expr",
      "parmset : WORLD YMIN expr",
      "parmset : WORLD YMAX expr",
      "parmset : VIEW expr ',' expr ',' expr ',' expr",
      "parmset : VIEW XMIN NUMBER",
      "parmset : VIEW XMAX NUMBER",
      "parmset : VIEW YMIN NUMBER",
      "parmset : VIEW YMAX NUMBER",
      "parmset : TITLE CHRSTR",
      "parmset : TITLE FONTP NUMBER",
      "parmset : TITLE SIZE NUMBER",
      "parmset : TITLE COLOR NUMBER",
      "parmset : TITLE LINEWIDTH NUMBER",
      "parmset : SUBTITLE CHRSTR",
      "parmset : SUBTITLE FONTP NUMBER",
      "parmset : SUBTITLE SIZE NUMBER",
      "parmset : SUBTITLE COLOR NUMBER",
      "parmset : SUBTITLE LINEWIDTH NUMBER",
      "parmset : GRAPHS MAXP SETS NUMBER",
      "parmset : LEGEND onoff",
      "parmset : LEGEND LOCTYPE worldview",
      "parmset : LEGEND LAYOUT NUMBER",
      "parmset : LEGEND VGAP NUMBER",
      "parmset : LEGEND HGAP NUMBER",
      "parmset : LEGEND LENGTH NUMBER",
      "parmset : LEGEND BOX onoff",
      "parmset : LEGEND BOX FILL onoff",
      "parmset : LEGEND BOX FILL WITH colpat",
      "parmset : LEGEND BOX FILL colpat NUMBER",
      "parmset : LEGEND BOX COLOR NUMBER",
      "parmset : LEGEND BOX LINESTYLE NUMBER",
      "parmset : LEGEND BOX LINEWIDTH NUMBER",
      "parmset : LEGEND expr ',' expr",
      "parmset : LEGEND X1 expr",
      "parmset : LEGEND Y1 expr",
      "parmset : LEGEND CHAR SIZE NUMBER",
      "parmset : LEGEND FONTP NUMBER",
      "parmset : LEGEND LINESTYLE NUMBER",
      "parmset : LEGEND LINEWIDTH NUMBER",
      "parmset : LEGEND COLOR NUMBER",
      "parmset : LEGEND STRING NUMBER CHRSTR",
      "parmset : FRAMEP onoff",
      "parmset : FRAMEP TYPE NUMBER",
      "parmset : FRAMEP LINESTYLE NUMBER",
      "parmset : FRAMEP LINEWIDTH NUMBER",
      "parmset : FRAMEP COLOR NUMBER",
      "parmset : FRAMEP FILL onoff",
      "parmset : FRAMEP BACKGROUND COLOR NUMBER",
      "parmset : GRAPHNO onoff",
      "parmset : GRAPHNO LABEL onoff",
      "parmset : GRAPHNO AUTOSCALE TYPE AUTO",
      "parmset : GRAPHNO AUTOSCALE TYPE SPEC",
      "parmset : GRAPHNO AUTOSCALE torf",
      "parmset : GRAPHNO HIDDEN torf",
      "parmset : GRAPHNO TYPE graphtype",
      "parmset : GRAPHNO FIXEDPOINT onoff",
      "parmset : GRAPHNO FIXEDPOINT FORMAT formatchoice formatchoice",
      "parmset : GRAPHNO FIXEDPOINT PREC NUMBER ',' NUMBER",
      "parmset : GRAPHNO FIXEDPOINT XY expr ',' expr",
      "parmset : GRAPHNO FIXEDPOINT TYPE NUMBER",
      "parmset : GRAPHNO MAXP SETS NUMBER",
      "setvelocity : VELOCITY SCALE NUMBER",
      "setvelocity : VELOCITY LEGEND onoff",
      "setvelocity : VELOCITY LINEWIDTH NUMBER",
      "setvelocity : VELOCITY LINESTYLE NUMBER",
      "setvelocity : VELOCITY COLOR NUMBER",
      "setvelocity : VELOCITY LOCTYPE worldview",
      "setvelocity : VELOCITY ARROW TYPE NUMBER",
      "xytype : XY",
      "xytype : XYARC",
      "xytype : XYBOX",
      "xytype : XYHILO",
      "xytype : XYRT",
      "xytype : XYSEG",
      "xytype : XYSTRING",
      "xytype : XYDX",
      "xytype : XYDY",
      "xytype : XYDXDX",
      "xytype : XYDYDY",
      "xytype : XYDXDY",
      "xytype : XYX2Y2",
      "xytype : XYXX",
      "xytype : XYYY",
      "xytype : XYZ",
      "xytype : XYZW",
      "xytype : XYUV",
      "xytype : NXY",
      "xytype : BIN",
      "graphtype : XY",
      "graphtype : LOGX",
      "graphtype : LOGY",
      "graphtype : LOGXY",
      "graphtype : BAR",
      "graphtype : HBAR",
      "graphtype : STACKEDBAR",
      "graphtype : STACKEDHBAR",
      "graphtype : POLAR",
      "graphtype : XYFIXED",
      "regiontype : ABOVE",
      "regiontype : BELOW",
      "regiontype : LEFT",
      "regiontype : RIGHT",
      "regiontype : POLYI",
      "regiontype : POLYO",
      "set_setprop : selectsets setprop",
      "setprop : onoff",
      "setprop : onoff IGNORE",
      "setprop : TYPE xytype",
      "setprop : MISSINGP expr",
      "setprop : PREC NUMBER",
      "setprop : FORMAT formatchoice",
      "setprop : SYMBOL NUMBER",
      "setprop : SYMBOL FILL NUMBER",
      "setprop : SYMBOL CENTER torf",
      "setprop : SYMBOL SIZE NUMBER",
      "setprop : SYMBOL CHAR NUMBER",
      "setprop : SYMBOL SKIP NUMBER",
      "setprop : prop NUMBER",
      "setprop : FILL NUMBER",
      "setprop : FILL WITH colpat",
      "setprop : FILL colpat NUMBER",
      "setprop : SKIP NUMBER",
      "setprop : ERRORBAR LENGTH NUMBER",
      "setprop : ERRORBAR TYPE opchoice",
      "setprop : ERRORBAR LINEWIDTH NUMBER",
      "setprop : ERRORBAR LINESTYLE NUMBER",
      "setprop : ERRORBAR RISER onoff",
      "setprop : ERRORBAR RISER LINEWIDTH NUMBER",
      "setprop : ERRORBAR RISER LINESTYLE NUMBER",
      "setprop : XYZ expr ',' expr",
      "setprop : COMMENT CHRSTR",
      "setaxis : axis",
      "setaxis : axis axisfeature",
      "setaxis : allaxes",
      "setaxis : GRAPHS axis",
      "setaxis : GRAPHS axis axisfeature",
      "setaxis : GRAPHS allaxes",
      "axis : XAXIS",
      "axis : YAXIS",
      "axis : ALTXAXIS",
      "axis : ALTYAXIS",
      "axis : ZEROXAXIS",
      "axis : ZEROYAXIS",
      "allaxes : AXES axesprops",
      "allaxes : XAXES axesprops",
      "allaxes : YAXES axesprops",
      "axesprops : onoff",
      "axesprops : COLOR NUMBER",
      "axesprops : LINEWIDTH NUMBER",
      "axesprops : LINESTYLE NUMBER",
      "axesprops : FONTP NUMBER",
      "axesprops : CHAR SIZE NUMBER",
      "axesprops : GRID onoff",
      "axisfeature : TICK tickdesc",
      "axisfeature : TICKLABEL ticklabeldesc",
      "axisfeature : LABEL axislabeldesc",
      "axisfeature : BAR axisbardesc",
      "axisfeature : onoff",
      "tickdesc : tickattr",
      "tickdesc : tickdesc tickattr",
      "tickattr : onoff",
      "tickattr : MAJOR onoff",
      "tickattr : MINOR onoff",
      "tickattr : MAJOR expr",
      "tickattr : MINOR expr",
      "tickattr : OFFSETX expr",
      "tickattr : OFFSETY expr",
      "tickattr : ALT onoff",
      "tickattr : MINP expr",
      "tickattr : MAXP expr",
      "tickattr : DEFAULT NUMBER",
      "tickattr : inoutchoice",
      "tickattr : LOG onoff",
      "tickattr : SIZE NUMBER",
      "tickattr : MAJOR SIZE NUMBER",
      "tickattr : MINOR SIZE NUMBER",
      "tickattr : COLOR NUMBER",
      "tickattr : LINEWIDTH NUMBER",
      "tickattr : MAJOR COLOR NUMBER",
      "tickattr : MINOR COLOR NUMBER",
      "tickattr : MAJOR LINEWIDTH NUMBER",
      "tickattr : MINOR LINEWIDTH NUMBER",
      "tickattr : MAJOR LINESTYLE NUMBER",
      "tickattr : MINOR LINESTYLE NUMBER",
      "tickattr : MAJOR GRID onoff",
      "tickattr : MINOR GRID onoff",
      "tickattr : OP opchoice",
      "tickattr : TYPE AUTO",
      "tickattr : TYPE SPEC",
      "tickattr : SPEC NUMBER",
      "tickattr : NUMBER ',' expr",
      "ticklabeldesc : ticklabelattr",
      "ticklabeldesc : ticklabeldesc ticklabelattr",
      "ticklabelattr : onoff",
      "ticklabelattr : TYPE AUTO",
      "ticklabelattr : TYPE SPEC",
      "ticklabelattr : PREC NUMBER",
      "ticklabelattr : FORMAT formatchoice",
      "ticklabelattr : FORMAT NUMBER",
      "ticklabelattr : APPEND CHRSTR",
      "ticklabelattr : PREPEND CHRSTR",
      "ticklabelattr : LAYOUT HORIZONTAL",
      "ticklabelattr : LAYOUT VERTICAL",
      "ticklabelattr : LAYOUT SPEC",
      "ticklabelattr : ANGLE NUMBER",
      "ticklabelattr : JUST justchoice",
      "ticklabelattr : SKIP NUMBER",
      "ticklabelattr : STAGGER NUMBER",
      "ticklabelattr : OP opchoice",
      "ticklabelattr : SIGN signchoice",
      "ticklabelattr : START expr",
      "ticklabelattr : STOP expr",
      "ticklabelattr : START TYPE SPEC",
      "ticklabelattr : START TYPE AUTO",
      "ticklabelattr : STOP TYPE SPEC",
      "ticklabelattr : STOP TYPE AUTO",
      "ticklabelattr : VGAP NUMBER",
      "ticklabelattr : HGAP NUMBER",
      "ticklabelattr : CHAR SIZE NUMBER",
      "ticklabelattr : FONTP NUMBER",
      "ticklabelattr : COLOR NUMBER",
      "ticklabelattr : LINEWIDTH NUMBER",
      "ticklabelattr : NUMBER ',' CHRSTR",
      "axislabeldesc : CHRSTR",
      "axislabeldesc : LAYOUT PERP",
      "axislabeldesc : LAYOUT PARA",
      "axislabeldesc : PLACE AUTO",
      "axislabeldesc : PLACE SPEC",
      "axislabeldesc : PLACE NUMBER ',' NUMBER",
      "axislabeldesc : JUST justchoice",
      "axislabeldesc : CHAR SIZE NUMBER",
      "axislabeldesc : FONTP NUMBER",
      "axislabeldesc : COLOR NUMBER",
      "axislabeldesc : LINEWIDTH NUMBER",
      "axisbardesc : onoff",
      "axisbardesc : COLOR NUMBER",
      "axisbardesc : LINESTYLE NUMBER",
      "axisbardesc : LINEWIDTH NUMBER",
      "selectsets : GRAPHNO '.' SETNUM",
      "selectsets : SETNUM",
      "selectsets : SETS",
      "selectsets : GRAPHNO SETS",
      "selectsets : GRAPHS SETS",
      "selectsets : GRAPHS SETNUM",
      "prop : LINESTYLE",
      "prop : LINEWIDTH",
      "prop : FONTP",
      "prop : COLOR",
      "prop : SIZE",
      "onoff : ON",
      "onoff : OFF",
      "colpat : COLOR",
      "colpat : PATTERN",
      "runtype : RUNAVG",
      "runtype : RUNSTD",
      "runtype : RUNMED",
      "runtype : RUNMAX",
      "runtype : RUNMIN",
      "ffttype : DFT",
      "ffttype : FFT",
      "ffttype : INVDFT",
      "ffttype : INVFFT",
      "sourcetype : DISK",
      "sourcetype : PIPE",
      "filltype : PATTERN",
      "filltype : COLOR",
      "filltype : NONE",
      "opchoice : TOP",
      "opchoice : BOTTOM",
      "opchoice : LEFT",
      "opchoice : RIGHT",
      "opchoice : BOTH",
      "justchoice : RIGHT",
      "justchoice : LEFT",
      "justchoice : CENTER",
      "extremetype : XMIN",
      "extremetype : XMAX",
      "extremetype : YMIN",
      "extremetype : YMAX",
      "torf : TRUEP",
      "torf : FALSEP",
      "inoutchoice : IN",
      "inoutchoice : OUT",
      "inoutchoice : BOTH",
      "formatchoice : DECIMAL",
      "formatchoice : EXPONENTIAL",
      "formatchoice : POWER",
      "formatchoice : GENERAL",
      "formatchoice : DDMMYY",
      "formatchoice : MMDDYY",
      "formatchoice : MMYY",
      "formatchoice : MMDD",
      "formatchoice : MONTHDAY",
      "formatchoice : DAYMONTH",
      "formatchoice : MONTHS",
      "formatchoice : MONTHL",
      "formatchoice : DAYOFWEEKS",
      "formatchoice : DAYOFWEEKL",
      "formatchoice : DAYOFYEAR",
      "formatchoice : HMS",
      "formatchoice : MMDDHMS",
      "formatchoice : MMDDYYHMS",
      "formatchoice : DEGREESLON",
      "formatchoice : DEGREESMMLON",
      "formatchoice : DEGREESMMSSLON",
      "formatchoice : MMSSLON",
      "formatchoice : DEGREESLAT",
      "formatchoice : DEGREESMMLAT",
      "formatchoice : DEGREESMMSSLAT",
      "formatchoice : MMSSLAT",
      "signchoice : NORMAL",
      "signchoice : ABSOLUTE",
      "signchoice : NEGATE",
      "direction : UP",
      "direction : DOWN",
      "direction : RIGHT",
      "direction : LEFT",
      "direction : IN",
      "direction : OUT",
      "worldview : WORLD",
      "worldview : VIEW",
      "asgn : VAR '[' expr ']' '=' expr",
      "asgn : SVAR '[' expr ']' '=' expr",
      "asgn : SETNUM '.' SVAR '[' expr ']' '=' expr",
      "asgn : GRAPHNO '.' SETNUM '.' SVAR '[' expr ']' '=' expr",
      "rasgn : REGNUM '.' SVAR '=' expr",
      "vasgn : VAR '=' vexpr",
      "vasgn : SVAR '=' vexpr",
      "vasgn : SETNUM '.' SVAR '=' vexpr",
      "vasgn : GRAPHNO '.' SETNUM '.' SVAR '=' vexpr",
      "vasgn : VAR '=' expr",
      "vasgn : SVAR '=' expr",
      "vasgn : SETNUM '.' SVAR '=' expr",
      "vasgn : GRAPHNO '.' SETNUM '.' SVAR '=' expr",
      "vexpr : VAR",
      "vexpr : SVAR",
      "vexpr : GRAPHNO '.' SETNUM '.' SVAR",
      "vexpr : SETNUM '.' SVAR",
      "vexpr : expr",
      "vexpr : expr '+' expr",
      "vexpr : vexpr '+' vexpr",
      "vexpr : expr '+' vexpr",
      "vexpr : vexpr '+' expr",
      "vexpr : expr '-' expr",
      "vexpr : vexpr '-' vexpr",
      "vexpr : expr '-' vexpr",
      "vexpr : vexpr '-' expr",
      "vexpr : expr '*' expr",
      "vexpr : vexpr '*' vexpr",
      "vexpr : expr '*' vexpr",
      "vexpr : vexpr '*' expr",
      "vexpr : expr '/' expr",
      "vexpr : vexpr '/' vexpr",
      "vexpr : expr '/' vexpr",
      "vexpr : vexpr '/' expr",
      "vexpr : expr '^' expr",
      "vexpr : expr '^' vexpr",
      "vexpr : vexpr '^' expr",
      "vexpr : vexpr '^' vexpr",
      "vexpr : ABS '(' expr ')'",
      "vexpr : ABS '(' vexpr ')'",
      "vexpr : ACOS '(' vexpr ')'",
      "vexpr : ASIN '(' vexpr ')'",
      "vexpr : ATAN '(' vexpr ')'",
      "vexpr : ATAN2 '(' vexpr ',' vexpr ')'",
      "vexpr : CEIL '(' vexpr ')'",
      "vexpr : COS '(' vexpr ')'",
      "vexpr : DEG",
      "vexpr : DX",
      "vexpr : DY",
      "vexpr : ERF '(' vexpr ')'",
      "vexpr : ERFC '(' vexpr ')'",
      "vexpr : EXP '(' vexpr ')'",
      "vexpr : FLOOR '(' vexpr ')'",
      "vexpr : HYPOT '(' vexpr ',' vexpr ')'",
      "vexpr : HYPOT '(' expr ',' vexpr ')'",
      "vexpr : HYPOT '(' vexpr ',' expr ')'",
      "vexpr : HYPOT '(' expr ',' expr ')'",
      "vexpr : INDEX",
      "vexpr : SETNO",
      "vexpr : INT '(' vexpr ')'",
      "vexpr : INVN '(' vexpr ')'",
      "vexpr : INVT '(' expr ',' NUMBER ')'",
      "vexpr : INVT '(' vexpr ',' NUMBER ')'",
      "vexpr : IRAND '(' NUMBER ')'",
      "vexpr : LGAMMA '(' vexpr ')'",
      "vexpr : LN '(' vexpr ')'",
      "vexpr : LOG '(' vexpr ')'",
      "vexpr : LOGISTIC '(' vexpr ',' expr ',' expr ')'",
      "vexpr : MAXP '(' vexpr ',' vexpr ')'",
      "vexpr : MINP '(' vexpr ',' vexpr ')'",
      "vexpr : MOD '(' vexpr ',' vexpr ')'",
      "vexpr : NORM '(' vexpr ')'",
      "vexpr : NORMP '(' vexpr ')'",
      "vexpr : PI",
      "vexpr : RAD",
      "vexpr : RAND",
      "vexpr : RNORM '(' vexpr ',' vexpr ')'",
      "vexpr : RNORM '(' expr ',' vexpr ')'",
      "vexpr : RNORM '(' vexpr ',' expr ')'",
      "vexpr : RNORM '(' expr ',' expr ')'",
      "vexpr : SIN '(' vexpr ')'",
      "vexpr : SQR '(' vexpr ')'",
      "vexpr : SQRT '(' vexpr ')'",
      "vexpr : TAN '(' vexpr ')'",
      "vexpr : vexpr '?' vexpr ':' vexpr",
      "vexpr : vexpr GT vexpr",
      "vexpr : vexpr LT vexpr",
      "vexpr : vexpr LE vexpr",
      "vexpr : vexpr GE vexpr",
      "vexpr : vexpr EQ vexpr",
      "vexpr : vexpr NE vexpr",
      "vexpr : vexpr AND vexpr",
      "vexpr : vexpr OR vexpr",
      "vexpr : NOT vexpr",
      "vexpr : '(' vexpr ')'",
      "vexpr : '-' vexpr",
      "expr : NUMBER",
      "expr : FITPARM",
      "expr : VAR '[' expr ']'",
      "expr : SVAR '[' expr ']'",
      "expr : REGNUM '.' SVAR",
      "expr : SETNUM '.' SVAR '[' expr ']'",
      "expr : SETNUM '.' extremetype",
      "expr : SETNUM '.' LENGTH",
      "expr : AVG '(' SETNUM ',' SVAR ')'",
      "expr : GRAPHNO '.' SETNUM '.' SVAR '[' expr ']'",
      "expr : expr '+' expr",
      "expr : expr '-' expr",
      "expr : expr '*' expr",
      "expr : expr '/' expr",
      "expr : expr '%' expr",
      "expr : expr '^' expr",
      "expr : ABS '(' expr ')'",
      "expr : ACOS '(' expr ')'",
      "expr : ASIN '(' expr ')'",
      "expr : ATAN '(' expr ')'",
      "expr : ATAN2 '(' expr ',' expr ')'",
      "expr : CEIL '(' expr ')'",
      "expr : COS '(' expr ')'",
      "expr : DEG",
      "expr : DX",
      "expr : DY",
      "expr : ERF '(' expr ')'",
      "expr : ERFC '(' expr ')'",
      "expr : EXP '(' expr ')'",
      "expr : FLOOR '(' expr ')'",
      "expr : HYPOT '(' expr ',' expr ')'",
      "expr : GRAPHNO '.' VX1",
      "expr : GRAPHNO '.' VX2",
      "expr : GRAPHNO '.' VY1",
      "expr : GRAPHNO '.' VY2",
      "expr : GRAPHNO '.' WX1",
      "expr : GRAPHNO '.' WX2",
      "expr : GRAPHNO '.' WY1",
      "expr : GRAPHNO '.' WY2",
      "expr : VX1",
      "expr : VX2",
      "expr : VY1",
      "expr : VY2",
      "expr : WX1",
      "expr : WX2",
      "expr : WY1",
      "expr : WY2",
      "expr : INDEX",
      "expr : SETNO",
      "expr : INT '(' expr ')'",
      "expr : INVN '(' expr ')'",
      "expr : INVT '(' expr ',' NUMBER ')'",
      "expr : IRAND '(' NUMBER ')'",
      "expr : LGAMMA '(' expr ')'",
      "expr : LN '(' expr ')'",
      "expr : LOG '(' expr ')'",
      "expr : LOGISTIC '(' expr ',' expr ',' expr ')'",
      "expr : MAXP '(' expr ',' expr ')'",
      "expr : MINP '(' expr ',' expr ')'",
      "expr : MOD '(' expr ',' expr ')'",
      "expr : NORM '(' expr ')'",
      "expr : NORMP '(' expr ')'",
      "expr : PI",
      "expr : RAD",
      "expr : RAND",
      "expr : RNORM '(' expr ',' expr ')'",
      "expr : SIN '(' expr ')'",
      "expr : SQR '(' expr ')'",
      "expr : SQRT '(' expr ')'",
      "expr : TAN '(' expr ')'",
      "expr : expr '?' expr ':' expr",
      "expr : expr GT expr",
      "expr : expr LT expr",
      "expr : expr LE expr",
      "expr : expr GE expr",
      "expr : expr EQ expr",
      "expr : expr NE expr",
      "expr : expr AND expr",
      "expr : expr OR expr",
      "expr : NOT expr",
      "expr : '(' expr ')'",
      "expr : '-' expr",
};
#endif /* YYDEBUG */
/* @(#)27       1.7  com/cmd/lang/yacc/yaccpar, bos, bos320 8/12/91 16:09:43 */
/*
 * COMPONENT_NAME: (CMDLANG) Language Utilities
 *
 * FUNCTIONS: yyparse
 * ORIGINS: 03
 */
/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#ifdef YYSPLIT
#   define YYERROR      return(-2)
#else
#   define YYERROR      goto yyerrlab
#endif
#ifdef YACC_MSG
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <nl_types.h>
nl_catd catd;
#endif
#define YYACCEPT        return(0)
#define YYABORT         return(1)
#ifndef YACC_MSG
#define YYBACKUP( newtoken, newvalue )\
{\
        if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
        {\
                yyerror( "syntax error - cannot backup" );\
                YYERROR;\
        }\
        yychar = newtoken;\
        yystate = *yyps;\
        yylval = newvalue;\
        goto yynewstate;\
}
#else
#define YYBACKUP( newtoken, newvalue )\
{\
        if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
        {\
                catd=catopen("yacc_user.cat",0);\
                yyerror(catgets(catd,1,1,"syntax error - cannot backup" ));\
                YYERROR;\
        }\
        yychar = newtoken;\
        yystate = *yyps;\
        yylval = newvalue;\
        goto yynewstate;\
}
#endif
#define YYRECOVERING()  (!!yyerrflag)
#ifndef YYDEBUG
#       define YYDEBUG  1       /* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;                    /* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG          (-1000)

#ifdef YYSPLIT
#   define YYSCODE { \
                        extern int (*_yyf[])(); \
                        register int yyret; \
                        if (_yyf[yytmp]) \
                            if ((yyret=(*_yyf[yytmp])()) == -2) \
                                    goto yyerrlab; \
                                else if (yyret>=0) return(yyret); \
                   }
#endif

/*
** global variables used by the parser
*/
YYSTYPE yyv[ YYMAXDEPTH ];      /* value stack */
int yys[ YYMAXDEPTH ];          /* state stack */

YYSTYPE *yypv;                  /* top of value stack */
YYSTYPE *yypvt;                 /* top of value stack for $vars */
int *yyps;                      /* top of state stack */

int yystate;                    /* current state */
int yytmp;                      /* extra var (lasts between blocks) */

int yynerrs;                    /* number of errors */
int yyerrflag;                  /* error recovery flag */
int yychar;                     /* current input token number */


/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
        /*
        ** Initialize externals - yyparse may be called more than once
        */
        yypv = &yyv[-1];
        yyps = &yys[-1];
        yystate = 0;
        yytmp = 0;
        yynerrs = 0;
        yyerrflag = 0;
        yychar = -1;
#ifdef YACC_MSG
        catd=catopen("yacc_user.cat",0);
#endif
        goto yystack;
        {
                register YYSTYPE *yy_pv;        /* top of value stack */
                register int *yy_ps;            /* top of state stack */
                register int yy_state;          /* current state */
                register int  yy_n;             /* internal state number info */

                /*
                ** get globals into registers.
                ** branch to here only if YYBACKUP was called.
                */
        yynewstate:
                yy_pv = yypv;
                yy_ps = yyps;
                yy_state = yystate;
                goto yy_newstate;

                /*
                ** get globals into registers.
                ** either we just started, or we just finished a reduction
                */
        yystack:
                yy_pv = yypv;
                yy_ps = yyps;
                yy_state = yystate;

                /*
                ** top of for (;;) loop while no reductions done
                */
        yy_stack:
                /*
                ** put a state and value onto the stacks
                */
#if YYDEBUG
                /*
                ** if debugging, look up token value in list of value vs.
                ** name pairs.  0 and negative (-1) are special values.
                ** Note: linear search is used since time is not a real
                ** consideration while debugging.
                */
                if ( yydebug )
                {
                        register int yy_i;

                        printf( "State %d, token ", yy_state );
                        if ( yychar == 0 )
                                printf( "end-of-file\n" );
                        else if ( yychar < 0 )
                                printf( "-none-\n" );
                        else
                        {
                                for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
                                        yy_i++ )
                                {
                                        if ( yytoks[yy_i].t_val == yychar )
                                                break;
                                }
                                printf( "%s\n", yytoks[yy_i].t_name );
                        }
                }
#endif /* YYDEBUG */
                if ( ++yy_ps >= &yys[ YYMAXDEPTH ] )    /* room on stack? */
                {
#ifndef YACC_MSG
                        yyerror( "yacc stack overflow" );
#else
                        yyerror(catgets(catd,1,2,"yacc stack overflow" ));
#endif
                        YYABORT;
                }
                *yy_ps = yy_state;
                *++yy_pv = yyval;

                /*
                ** we have a new state - find out what to do
                */
        yy_newstate:
                if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
                        goto yydefault;         /* simple state */
#if YYDEBUG
                /*
                ** if debugging, need to mark whether new token grabbed
                */
                yytmp = yychar < 0;
#endif
                if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
                        yychar = 0;             /* reached EOF */
#if YYDEBUG
                if ( yydebug && yytmp )
                {
                        register int yy_i;

                        printf( "Received token " );
                        if ( yychar == 0 )
                                printf( "end-of-file\n" );
                        else if ( yychar < 0 )
                                printf( "-none-\n" );
                        else
                        {
                                for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
                                        yy_i++ )
                                {
                                        if ( yytoks[yy_i].t_val == yychar )
                                                break;
                                }
                                printf( "%s\n", yytoks[yy_i].t_name );
                        }
                }
#endif /* YYDEBUG */
                if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
                        goto yydefault;
                if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )  /*valid shift*/
                {
                        yychar = -1;
                        yyval = yylval;
                        yy_state = yy_n;
                        if ( yyerrflag > 0 )
                                yyerrflag--;
                        goto yy_stack;
                }

        yydefault:
                if ( ( yy_n = yydef[ yy_state ] ) == -2 )
                {
#if YYDEBUG
                        yytmp = yychar < 0;
#endif
                        if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
                                yychar = 0;             /* reached EOF */
#if YYDEBUG
                        if ( yydebug && yytmp )
                        {
                                register int yy_i;

                                printf( "Received token " );
                                if ( yychar == 0 )
                                        printf( "end-of-file\n" );
                                else if ( yychar < 0 )
                                        printf( "-none-\n" );
                                else
                                {
                                        for ( yy_i = 0;
                                                yytoks[yy_i].t_val >= 0;
                                                yy_i++ )
                                        {
                                                if ( yytoks[yy_i].t_val
                                                        == yychar )
                                                {
                                                        break;
                                                }
                                        }
                                        printf( "%s\n", yytoks[yy_i].t_name );
                                }
                        }
#endif /* YYDEBUG */
                        /*
                        ** look through exception table
                        */
                        {
                                register int *yyxi = yyexca;

                                while ( ( *yyxi != -1 ) ||
                                        ( yyxi[1] != yy_state ) )
                                {
                                        yyxi += 2;
                                }
                                while ( ( *(yyxi += 2) >= 0 ) &&
                                        ( *yyxi != yychar ) )
                                        ;
                                if ( ( yy_n = yyxi[1] ) < 0 )
                                        YYACCEPT;
                        }
                }

                /*
                ** check for syntax error
                */
                if ( yy_n == 0 )        /* have an error */
                {
                        /* no worry about speed here! */
                        switch ( yyerrflag )
                        {
                        case 0:         /* new error */
#ifndef YACC_MSG
                                yyerror( "syntax error" );
#else
                                yyerror(catgets(catd,1,3,"syntax error" ));
#endif
                                goto skip_init;
                        yyerrlab:
                                /*
                                ** get globals into registers.
                                ** we have a user generated syntax type error
                                */
                                yy_pv = yypv;
                                yy_ps = yyps;
                                yy_state = yystate;
                                yynerrs++;
                        skip_init:
                        case 1:
                        case 2:         /* incompletely recovered error */
                                        /* try again... */
                                yyerrflag = 3;
                                /*
                                ** find state where "error" is a legal
                                ** shift action
                                */
                                while ( yy_ps >= yys )
                                {
                                        yy_n = yypact[ *yy_ps ] + YYERRCODE;
                                        if ( yy_n >= 0 && yy_n < YYLAST &&
                                                yychk[yyact[yy_n]] == YYERRCODE)                                        {
                                                /*
                                                ** simulate shift of "error"
                                                */
                                                yy_state = yyact[ yy_n ];
                                                goto yy_stack;
                                        }
                                        /*
                                        ** current state has no shift on
                                        ** "error", pop stack
                                        */
#if YYDEBUG
#       define _POP_ "Error recovery pops state %d, uncovers state %d\n"
                                        if ( yydebug )
                                                printf( _POP_, *yy_ps,
                                                        yy_ps[-1] );
#       undef _POP_
#endif
                                        yy_ps--;
                                        yy_pv--;
                                }
                                /*
                                ** there is no state on stack with "error" as
                                ** a valid shift.  give up.
                                */
                                YYABORT;
                        case 3:         /* no shift yet; eat a token */
#if YYDEBUG
                                /*
                                ** if debugging, look up token in list of
                                ** pairs.  0 and negative shouldn't occur,
                                ** but since timing doesn't matter when
                                ** debugging, it doesn't hurt to leave the
                                ** tests here.
                                */
                                if ( yydebug )
                                {
                                        register int yy_i;

                                        printf( "Error recovery discards " );
                                        if ( yychar == 0 )
                                                printf( "token end-of-file\n" );
                                        else if ( yychar < 0 )
                                                printf( "token -none-\n" );
                                        else
                                        {
                                                for ( yy_i = 0;
                                                        yytoks[yy_i].t_val >= 0;
                                                        yy_i++ )
                                                {
                                                        if ( yytoks[yy_i].t_val
                                                                == yychar )
                                                        {
                                                                break;
                                                        }
                                                }
                                                printf( "token %s\n",
                                                        yytoks[yy_i].t_name );
                                        }
                                }
#endif /* YYDEBUG */
                                if ( yychar == 0 )      /* reached EOF. quit */
                                        YYABORT;
                                yychar = -1;
                                goto yy_newstate;
                        }
                }/* end if ( yy_n == 0 ) */
                /*
                ** reduction by production yy_n
                ** put stack tops, etc. so things right after switch
                */
#if YYDEBUG
                /*
                ** if debugging, print the string that is the user's
                ** specification of the reduction which is just about
                ** to be done.
                */
                if ( yydebug )
                        printf( "Reduce by (%d) \"%s\"\n",
                                yy_n, yyreds[ yy_n ] );
#endif
                yytmp = yy_n;                   /* value to switch over */
                yypvt = yy_pv;                  /* $vars top of value stack */
                /*
                ** Look in goto table for next state
                ** Sorry about using yy_state here as temporary
                ** register variable, but why not, if it works...
                ** If yyr2[ yy_n ] doesn't have the low order bit
                ** set, then there is no action to be done for
                ** this reduction.  So, no saving & unsaving of
                ** registers done.  The only difference between the
                ** code just after the if and the body of the if is
                ** the goto yy_stack in the body.  This way the test
                ** can be made before the choice of what to do is needed.
                */
                {
                        /* length of production doubled with extra bit */
                        register int yy_len = yyr2[ yy_n ];

                        if ( !( yy_len & 01 ) )
                        {
                                yy_len >>= 1;
                                yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
                                yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
                                        *( yy_ps -= yy_len ) + 1;
                                if ( yy_state >= YYLAST ||
                                        yychk[ yy_state =
                                        yyact[ yy_state ] ] != -yy_n )
                                {
                                        yy_state = yyact[ yypgo[ yy_n ] ];
                                }
                                goto yy_stack;
                        }
                        yy_len >>= 1;
                        yyval = ( yy_pv -= yy_len )[1]; /* $$ = $1 */
                        yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
                                *( yy_ps -= yy_len ) + 1;
                        if ( yy_state >= YYLAST ||
                                yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
                        {
                                yy_state = yyact[ yypgo[ yy_n ] ];
                        }
                }
                                        /* save until reenter driver code */
                yystate = yy_state;
                yyps = yy_ps;
                yypv = yy_pv;
        }
        /*
        ** code supplied by user is placed in this switch
        */
	

        switch(yytmp){

case 5:
# line 479 "pars.yacc"
{
	    result = yypvt[-1].val;
	} /*NOTREACHED*/ break;
case 6:
# line 482 "pars.yacc"
{
	    result = *yypvt[-1].ptr;
	} /*NOTREACHED*/ break;
case 13:
# line 491 "pars.yacc"
{
	    return 1;
	} /*NOTREACHED*/ break;
case 14:
# line 497 "pars.yacc"
{
	    if (yypvt[-1].pset == FILEP) {
		//csto set_printer(FILEP, yypvt[-0].pset);
	    }
	    else {
		//csto set_printer(yypvt[-1].pset, yypvt[-0].pset);
	    }
	} /*NOTREACHED*/ break;
case 15:
# line 505 "pars.yacc"
{
	    if (yypvt[-1].pset == FILEP) {
		//csto set_printer(FILEP, yypvt[-0].pset);
	    }
	    else {
		//csto set_printer(yypvt[-1].pset, yypvt[-0].pset);
	    }
	} /*NOTREACHED*/ break;
case 16:
# line 513 "pars.yacc"
{
	    if (yypvt[-0].pset == FILEP) {
		//csto set_printer(FILEP, NULL);
	    }
	    else {
		//csto set_printer(yypvt[-0].pset, NULL);
	    }
	} /*NOTREACHED*/ break;
case 17:
# line 521 "pars.yacc"
{
	    tdevice = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 18:
# line 524 "pars.yacc"
{
	    hdevice = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 19:
# line 527 "pars.yacc"
{
	    //csto do_hardcopy();
	} /*NOTREACHED*/ break;
case 20:
# line 533 "pars.yacc"
{ yyval.pset = GR_PS_P; } /*NOTREACHED*/ break;
case 21:
# line 534 "pars.yacc"
{ yyval.pset = GR_PS_L; } /*NOTREACHED*/ break;
case 22:
# line 535 "pars.yacc"
{ yyval.pset = GR_MIF_P; } /*NOTREACHED*/ break;
case 23:
# line 536 "pars.yacc"
{ yyval.pset = GR_MIF_L; } /*NOTREACHED*/ break;
case 24:
# line 537 "pars.yacc"
{ yyval.pset = GR_HPGL_P; } /*NOTREACHED*/ break;
case 25:
# line 538 "pars.yacc"
{ yyval.pset = GR_HPGL_L; } /*NOTREACHED*/ break;
case 26:
# line 539 "pars.yacc"
{ yyval.pset = hdevice; } /*NOTREACHED*/ break;
case 27:
# line 540 "pars.yacc"
{ yyval.pset = FILEP; } /*NOTREACHED*/ break;
case 28:
# line 544 "pars.yacc"
{
	    rg[yypvt[-1].pset].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 29:
# line 547 "pars.yacc"
{
	    rg[yypvt[-2].pset].type = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 30:
# line 550 "pars.yacc"
{
	    rg[yypvt[-2].pset].color = checkon(COLOR, rg[yypvt[-2].pset].color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 31:
# line 553 "pars.yacc"
{
	    rg[yypvt[-2].pset].lines = checkon(LINESTYLE, rg[yypvt[-2].pset].lines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 32:
# line 556 "pars.yacc"
{
	    rg[yypvt[-2].pset].linew = checkon(LINEWIDTH, rg[yypvt[-2].pset].linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 33:
# line 560 "pars.yacc"
{
	    rg[yypvt[-8].pset].x1 = yypvt[-6].val;
	    rg[yypvt[-8].pset].y1 = yypvt[-4].val;
	    rg[yypvt[-8].pset].x2 = yypvt[-2].val;
	    rg[yypvt[-8].pset].y2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 34:
# line 567 "pars.yacc"
{
	    if (rg[yypvt[-4].pset].x == NULL || rg[yypvt[-4].pset].n == 0) {
		rg[yypvt[-4].pset].n = 0;
		rg[yypvt[-4].pset].x = (double *) calloc(1, sizeof(double));
		rg[yypvt[-4].pset].y = (double *) calloc(1, sizeof(double));
	    } else {
		rg[yypvt[-4].pset].x = (double *) realloc(rg[yypvt[-4].pset].x, (rg[yypvt[-4].pset].n + 1) * sizeof(double));
		rg[yypvt[-4].pset].y = (double *) realloc(rg[yypvt[-4].pset].y, (rg[yypvt[-4].pset].n + 1) * sizeof(double));
	    }
	    rg[yypvt[-4].pset].x[rg[yypvt[-4].pset].n] = yypvt[-2].val;
	    rg[yypvt[-4].pset].y[rg[yypvt[-4].pset].n] = yypvt[-0].val;
	    rg[yypvt[-4].pset].n++;
	} /*NOTREACHED*/ break;
case 35:
# line 580 "pars.yacc"
{
	    rg[yypvt[-2].pset].linkto[yypvt[-0].pset] = TRUE;
	} /*NOTREACHED*/ break;
case 36:
# line 586 "pars.yacc"
{
	     drawgraph();
	} /*NOTREACHED*/ break;
case 37:
# line 589 "pars.yacc"
{
	    auto_redraw = (yypvt[-0].pset == ON);
	} /*NOTREACHED*/ break;
case 38:
# line 592 "pars.yacc"
{
	    if (inwin) {
		//csto set_left_footer(yypvt[-0].pset);
	    }
	    else {
		printf("%s\n", yypvt[-0].pset);
	    }
	} /*NOTREACHED*/ break;
case 39:
# line 600 "pars.yacc"
{
	    //csto setbgcolor((int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 40:
# line 603 "pars.yacc"
{
	    //csto xlibsetcmap((int) yypvt[-6].val, (int) yypvt[-4].val, (int) yypvt[-2].val, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 41:
# line 606 "pars.yacc"
{
	    exit(0);
	} /*NOTREACHED*/ break;
case 42:
# line 610 "pars.yacc"
{
	    switch (yypvt[-0].pset) {
	    case UP:
		//csto gwindup_proc();
		break;
	    case DOWN:
		//csto gwinddown_proc();
		break;
	    case RIGHT:
		//csto gwindright_proc();
		break;
	    case LEFT:
		//csto gwindleft_proc();
		break;
	    case IN:
		//csto gwindshrink_proc();
		break;
	    case OUT:
		//csto gwindexpand_proc();
		break;
	    }
	} /*NOTREACHED*/ break;
case 43:
# line 632 "pars.yacc"
{
	    //csto scroll_proc((int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 44:
# line 635 "pars.yacc"
{
	    //csto scrollinout_proc((int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 45:
# line 638 "pars.yacc"
{
	    //csto scrolling_islinked = yypvt[-0].pset == ON;
	} /*NOTREACHED*/ break;
case 46:
# line 641 "pars.yacc"
{
	    //csto my_doublebuffer(yypvt[-0].pset == TRUEP);
	} /*NOTREACHED*/ break;
case 47:
# line 644 "pars.yacc"
{
	    //csto my_frontbuffer(yypvt[-0].pset == TRUEP);
	} /*NOTREACHED*/ break;
case 48:
# line 647 "pars.yacc"
{
	    //csto my_backbuffer(yypvt[-0].pset == TRUEP);
	} /*NOTREACHED*/ break;
case 49:
# line 650 "pars.yacc"
{
	    //csto my_swapbuffer();
	} /*NOTREACHED*/ break;
case 50:
# line 653 "pars.yacc"
{
	    sleep((int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 51:
# line 656 "pars.yacc"
{	/* TODO add delay function */
	} /*NOTREACHED*/ break;
case 52:
# line 658 "pars.yacc"
{		/* TODO add abort flag and function */
	} /*NOTREACHED*/ break;
case 53:
# line 661 "pars.yacc"
{
	    gotparams = TRUE;
	    strcpy(paramfile, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 54:
# line 666 "pars.yacc"
{
//csto 	    if (!fexists((char *) yypvt[-0].pset)) {
// 		FILE *pp = fopen((char *) yypvt[-0].pset, "w");
// 		if (pp != NULL) {
// 		    putparms(cg, pp, 0);
// 		    fclose(pp);
// 		} else {
// 		    errwin("Unable to write parameter file");
// 		}
// 	    }
	} /*NOTREACHED*/ break;
case 55:
# line 677 "pars.yacc"
{
	    cg = (int) yypvt[-0].pset;
	    g[cg].parmsread = TRUE;
	    change_gno = cg;
	} /*NOTREACHED*/ break;
case 56:
# line 682 "pars.yacc"
{
	    curset = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 57:
# line 685 "pars.yacc"
{
	     do_activateset(cg, yypvt[-1].pset, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 58:
# line 688 "pars.yacc"
{
	     add_point(cg, yypvt[-4].pset, yypvt[-2].val, yypvt[-0].val, 0.0, 0.0, XY);
	} /*NOTREACHED*/ break;
case 59:
# line 691 "pars.yacc"
{
	     add_point(yypvt[-6].pset, yypvt[-4].pset, yypvt[-2].val, yypvt[-0].val, 0.0, 0.0, XY);
	} /*NOTREACHED*/ break;
case 60:
# line 694 "pars.yacc"
{
	    //csto do_copyset(cg, yypvt[-2].pset, cg, yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 61:
# line 697 "pars.yacc"
{
	    //csto do_copyset(yypvt[-6].pset, yypvt[-4].pset, yypvt[-2].pset, yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 62:
# line 700 "pars.yacc"
{
	    //csto do_moveset(cg, yypvt[-2].pset, cg, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 63:
# line 703 "pars.yacc"
{
	    //csto do_moveset(yypvt[-6].pset, yypvt[-4].pset, yypvt[-2].pset, yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 64:
# line 707 "pars.yacc"
{
	    killset(cg, yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 65:
# line 711 "pars.yacc"
{
	    int i;
	    for (i = 0; i < g[cg].maxplot; i++) {
		killset(cg, i);
	    }
	} /*NOTREACHED*/ break;
case 66:
# line 718 "pars.yacc"
{
	    //csto kill_graph(yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 67:
# line 722 "pars.yacc"
{
	    //csto kill_graph(MAXGRAPH);
	} /*NOTREACHED*/ break;
case 68:
# line 726 "pars.yacc"
{
	    wipeout(0);
	} /*NOTREACHED*/ break;
case 69:
# line 730 "pars.yacc"
{
	    int i;
	    for (i = 0; i < (int) yypvt[-4].val; i++) {
		yypvt[-5].ptr[i] = yypvt[-2].val + yypvt[-0].val * i;
	    }
	} /*NOTREACHED*/ break;
case 70:
# line 737 "pars.yacc"
{
	    int setno = yypvt[-3].pset, ideg = (int) yypvt[-1].val;
	    //csto do_regress(setno, ideg, 0);
	} /*NOTREACHED*/ break;
case 71:
# line 742 "pars.yacc"
{
	    //csto do_running_command(yypvt[-5].pset, yypvt[-3].pset, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 72:
# line 746 "pars.yacc"
{
	    //csto do_fourier_command(yypvt[-5].pset, yypvt[-3].pset, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 73:
# line 750 "pars.yacc"
{
	    //csto do_spline(yypvt[-7].pset, yypvt[-5].val, yypvt[-3].val, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 74:
# line 754 "pars.yacc"
{
	    //csto do_histo_command(yypvt[-7].pset, yypvt[-5].val, yypvt[-3].val, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 75:
# line 758 "pars.yacc"
{
	    //csto do_differ(yypvt[-3].pset, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 76:
# line 762 "pars.yacc"
{
	    //csto do_int(yypvt[-1].pset, 0);
	} /*NOTREACHED*/ break;
case 77:
# line 766 "pars.yacc"
{
	    if (activeset(cg)) {
		 defaultgraph(cg);
		 default_axis(cg, g[cg].auto_type, X_AXIS);
		 default_axis(cg, g[cg].auto_type, ZX_AXIS);
		 default_axis(cg, g[cg].auto_type, Y_AXIS);
		 default_axis(cg, g[cg].auto_type, ZY_AXIS);
		 //csto update_world(cg);
		 drawgraph();
	    } else {
		errwin("No active sets!");
	    }
	} /*NOTREACHED*/ break;
case 78:
# line 780 "pars.yacc"
{
	    if (activeset(cg)) {
		 defaultx(cg, -1);
		 default_axis(cg, g[cg].auto_type, X_AXIS);
		 default_axis(cg, g[cg].auto_type, ZX_AXIS);
		 //csto update_world(cg);
		 drawgraph();
	    } else {
		errwin("No active sets!");
	    }
	} /*NOTREACHED*/ break;
case 79:
# line 792 "pars.yacc"
{
	    if (activeset(cg)) {
		 defaulty(cg, -1);
		 default_axis(cg, g[cg].auto_type, Y_AXIS);
		 default_axis(cg, g[cg].auto_type, ZY_AXIS);
		 //csto update_world(cg);
		 drawgraph();
	    } else {
		errwin("No active sets!");
	    }
	} /*NOTREACHED*/ break;
case 80:
# line 804 "pars.yacc"
{
	    if (isactive_set(cg, yypvt[-0].pset)) {
		 defaultsetgraph(cg, yypvt[-0].pset);
		 default_axis(cg, g[cg].auto_type, X_AXIS);
		 default_axis(cg, g[cg].auto_type, ZX_AXIS);
		 default_axis(cg, g[cg].auto_type, Y_AXIS);
		 default_axis(cg, g[cg].auto_type, ZY_AXIS);
		 //csto update_world(cg);
		 drawgraph();
	    } else {
		errwin("Set not active");
	    }
	} /*NOTREACHED*/ break;
case 81:
# line 818 "pars.yacc"
{
	    //csto extern int go_locateflag;
	    //csto go_locateflag = (yypvt[-0].pset == ON);
	} /*NOTREACHED*/ break;
case 82:
# line 823 "pars.yacc"
{
	    //csto draw_focus(cg);
	    cg = (int) yypvt[-0].pset;
	    defineworld(g[cg].w.xg1, g[cg].w.yg1, g[cg].w.xg2, g[cg].w.yg2);
	    viewport(g[cg].v.xv1, g[cg].v.yv1, g[cg].v.xv2, g[cg].v.yv2);
	    //csto draw_focus(cg);
	    update_all(cg);
	} /*NOTREACHED*/ break;
case 83:
# line 831 "pars.yacc"
{
	    //csto draw_focus_flag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 84:
# line 834 "pars.yacc"
{
	    focus_policy = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 85:
# line 837 "pars.yacc"
{
	    focus_policy = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 86:
# line 840 "pars.yacc"
{
	    focus_policy = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 87:
# line 843 "pars.yacc"
{
	    cursource = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 88:
# line 846 "pars.yacc"
{
	    curtype = yypvt[-0].pset;
	    change_type = curtype;
	} /*NOTREACHED*/ break;
case 89:
# line 851 "pars.yacc"
{
	    gotread = TRUE;
	    readtype = curtype;
	    readsrc = cursource;
	    strcpy(readfile, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 90:
# line 858 "pars.yacc"
{
	    gotbatch = TRUE;
	    strcpy(batchfile, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 91:
# line 863 "pars.yacc"
{
	     //csto getdata_(cg, (char *) yypvt[-0].pset, DISK, BLOCK);
	} /*NOTREACHED*/ break;
case 92:
# line 867 "pars.yacc"
{
	     //csto create_set_fromblock(cg, yypvt[-1].pset, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 93:
# line 871 "pars.yacc"
{
	    gotread = TRUE;
	    readtype = yypvt[-1].pset;
	    readsrc = cursource;
	    strcpy(readfile, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 94:
# line 878 "pars.yacc"
{
	    gotread = TRUE;
	    strcpy(readfile, (char *) yypvt[-0].pset);
	    readtype = yypvt[-2].pset;
	    readsrc = yypvt[-1].pset;
	} /*NOTREACHED*/ break;
case 95:
# line 884 "pars.yacc"
{
	    //csto push_world();
	} /*NOTREACHED*/ break;
case 96:
# line 887 "pars.yacc"
{
	    //csto pop_world();
	} /*NOTREACHED*/ break;
case 97:
# line 890 "pars.yacc"
{
	    //csto cycle_world_stack();
	} /*NOTREACHED*/ break;
case 98:
# line 893 "pars.yacc"
{
	    // csto if ((int) yypvt[-0].val > 0)
		//show_world_stack((int) yypvt[-0].val - 1);
	} /*NOTREACHED*/ break;
case 99:
# line 898 "pars.yacc"
{
	    //csto add_world(cg, yypvt[-14].val, yypvt[-12].val, yypvt[-10].val, yypvt[-8].val, yypvt[-6].val, yypvt[-4].val, yypvt[-2].val, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 100:
# line 901 "pars.yacc"
{
	    //csto clear_world_stack();
	} /*NOTREACHED*/ break;
case 101:
# line 904 "pars.yacc"
{
	     do_clear_boxes();
	} /*NOTREACHED*/ break;
case 102:
# line 907 "pars.yacc"
{
	     curbox = next_box();
	} /*NOTREACHED*/ break;
case 103:
# line 910 "pars.yacc"
{
	    curbox = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 104:
# line 913 "pars.yacc"
{
	    boxes[curbox].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 105:
# line 916 "pars.yacc"
{
	    boxes[curbox].gno = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 106:
# line 920 "pars.yacc"
{
	    if (curbox >= 0 && curbox < MAXBOXES) {
		boxes[curbox].x1 = yypvt[-6].val;
		boxes[curbox].y1 = yypvt[-4].val;
		boxes[curbox].x2 = yypvt[-2].val;
		boxes[curbox].y2 = yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 107:
# line 928 "pars.yacc"
{
	    box_loctype = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 108:
# line 931 "pars.yacc"
{
	    box_lines = checkon(LINESTYLE, box_lines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 109:
# line 934 "pars.yacc"
{
	    box_linew = checkon(LINEWIDTH, box_linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 110:
# line 937 "pars.yacc"
{
	    box_color = checkon(COLOR, box_color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 111:
# line 940 "pars.yacc"
{
	    box_fill = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 112:
# line 943 "pars.yacc"
{
	    box_fillcolor = checkon(COLOR, box_fillcolor, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 113:
# line 946 "pars.yacc"
{
	    box_fillpat = checkon(PATTERN, box_fillpat, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 114:
# line 950 "pars.yacc"
{
	    if (curbox >= 0 && curbox < MAXBOXES) {
		boxes[curbox].lines = box_lines;
		boxes[curbox].linew = box_linew;
		boxes[curbox].color = box_color;
		boxes[curbox].fill = box_fill;
		boxes[curbox].fillcolor = box_fillcolor;
		boxes[curbox].fillpattern = box_fillpat;
		boxes[curbox].loctype = box_loctype;
	    }
	} /*NOTREACHED*/ break;
case 115:
# line 961 "pars.yacc"
{
	    curline = next_line();
	} /*NOTREACHED*/ break;
case 116:
# line 964 "pars.yacc"
{
	    curline = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 117:
# line 967 "pars.yacc"
{
	    do_clear_lines();
	} /*NOTREACHED*/ break;
case 118:
# line 970 "pars.yacc"
{
	    lines[curline].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 119:
# line 973 "pars.yacc"
{
	    lines[curline].gno = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 120:
# line 977 "pars.yacc"
{
	    lines[curline].x1 = yypvt[-6].val;
	    lines[curline].y1 = yypvt[-4].val;
	    lines[curline].x2 = yypvt[-2].val;
	    lines[curline].y2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 121:
# line 983 "pars.yacc"
{
	    line_loctype = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 122:
# line 986 "pars.yacc"
{
	    line_linew = checkon(LINEWIDTH, line_linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 123:
# line 989 "pars.yacc"
{
	    line_lines = checkon(LINESTYLE, line_lines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 124:
# line 992 "pars.yacc"
{
	    line_color = checkon(COLOR, line_color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 125:
# line 995 "pars.yacc"
{
	    line_arrow = checkon(ARROW, line_arrow, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 126:
# line 998 "pars.yacc"
{
	    line_asize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 127:
# line 1001 "pars.yacc"
{
	    line_atype = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 128:
# line 1005 "pars.yacc"
{
	    if (curline >= 0 && curline < MAXLINES) {
		lines[curline].lines = line_lines;
		lines[curline].linew = line_linew;
		lines[curline].color = line_color;
		lines[curline].arrow = line_arrow;
		lines[curline].asize = line_asize;
		lines[curline].atype = line_atype;
		lines[curline].loctype = line_loctype;
	    }
	} /*NOTREACHED*/ break;
case 129:
# line 1016 "pars.yacc"
{
	    do_clear_text();
	} /*NOTREACHED*/ break;
case 130:
# line 1019 "pars.yacc"
{
        curstring = next_string();
	} /*NOTREACHED*/ break;
case 131:
# line 1022 "pars.yacc"
{
	    curstring = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 132:
# line 1025 "pars.yacc"
{
	    pstr[curstring].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 133:
# line 1028 "pars.yacc"
{
	    pstr[curstring].gno = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 134:
# line 1032 "pars.yacc"
{
	    pstr[curstring].x = yypvt[-2].val;
	    pstr[curstring].y = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 135:
# line 1036 "pars.yacc"
{
	    string_loctype = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 136:
# line 1039 "pars.yacc"
{
	    string_linew = checkon(LINEWIDTH, string_linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 137:
# line 1042 "pars.yacc"
{
	    string_color = checkon(COLOR, string_color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 138:
# line 1045 "pars.yacc"
{
	    string_rot = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 139:
# line 1048 "pars.yacc"
{
	    string_font = checkon(FONTP, string_font, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 140:
# line 1051 "pars.yacc"
{
	    string_just = checkon(JUST, string_just, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 141:
# line 1054 "pars.yacc"
{
	    string_size = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 142:
# line 1058 "pars.yacc"
{
	    strcpy(pstr[curstring].s, (char *) yypvt[-0].pset);
	    pstr[curstring].linew = string_linew;
	    pstr[curstring].color = string_color;
	    pstr[curstring].font = string_font;
	    pstr[curstring].just = string_just;
	    pstr[curstring].loctype = string_loctype;
	    pstr[curstring].rot = string_rot;
	    pstr[curstring].charsize = string_size;
	} /*NOTREACHED*/ break;
case 143:
# line 1068 "pars.yacc"
{
	    g[cg].d.lines = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 144:
# line 1071 "pars.yacc"
{
	    g[cg].d.linew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 145:
# line 1074 "pars.yacc"
{
	    g[cg].d.color = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 146:
# line 1077 "pars.yacc"
{
	    g[cg].d.charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 147:
# line 1080 "pars.yacc"
{
	    g[cg].d.font = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 148:
# line 1083 "pars.yacc"
{
	    g[cg].d.fontsrc = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 149:
# line 1086 "pars.yacc"
{
	    g[cg].d.symsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 150:
# line 1090 "pars.yacc"
{
	    g[cg].w.xg1 = yypvt[-6].val;
	    g[cg].w.yg1 = yypvt[-4].val;
	    g[cg].w.xg2 = yypvt[-2].val;
	    g[cg].w.yg2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 151:
# line 1096 "pars.yacc"
{
	    g[cg].w.xg1 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 152:
# line 1099 "pars.yacc"
{
	    g[cg].w.xg2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 153:
# line 1102 "pars.yacc"
{
	    g[cg].w.yg1 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 154:
# line 1105 "pars.yacc"
{
	    g[cg].w.yg2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 155:
# line 1109 "pars.yacc"
{
	    g[cg].v.xv1 = yypvt[-6].val;
	    g[cg].v.yv1 = yypvt[-4].val;
	    g[cg].v.xv2 = yypvt[-2].val;
	    g[cg].v.yv2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 156:
# line 1115 "pars.yacc"
{
	    g[cg].v.xv1 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 157:
# line 1118 "pars.yacc"
{
	    g[cg].v.xv2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 158:
# line 1121 "pars.yacc"
{
	    g[cg].v.yv1 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 159:
# line 1124 "pars.yacc"
{
	    g[cg].v.yv2 = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 160:
# line 1127 "pars.yacc"
{
	    strcpy(g[cg].labs.title.s, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 161:
# line 1130 "pars.yacc"
{
	    g[cg].labs.title.font = checkon(FONTP, g[cg].labs.title.font, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 162:
# line 1133 "pars.yacc"
{
	    g[cg].labs.title.charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 163:
# line 1136 "pars.yacc"
{
	    g[cg].labs.title.color = checkon(COLOR, g[cg].labs.title.color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 164:
# line 1140 "pars.yacc"
{
	    g[cg].labs.title.linew = checkon(LINEWIDTH, g[cg].labs.title.linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 165:
# line 1143 "pars.yacc"
{
	    strcpy(g[cg].labs.stitle.s, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 166:
# line 1147 "pars.yacc"
{
	    g[cg].labs.stitle.font = checkon(FONTP, g[cg].labs.stitle.font, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 167:
# line 1150 "pars.yacc"
{
	    g[cg].labs.stitle.charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 168:
# line 1154 "pars.yacc"
{
	    g[cg].labs.stitle.color = checkon(COLOR, g[cg].labs.stitle.color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 169:
# line 1158 "pars.yacc"
{
	    g[cg].labs.stitle.linew = checkon(LINEWIDTH, g[cg].labs.stitle.color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 170:
# line 1161 "pars.yacc"
{
	    realloc_plots((int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 171:
# line 1164 "pars.yacc"
{
	    g[cg].l.active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 172:
# line 1167 "pars.yacc"
{
	    g[cg].l.loctype = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 173:
# line 1170 "pars.yacc"
{
	    g[cg].l.layout = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 174:
# line 1173 "pars.yacc"
{
	    g[cg].l.vgap = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 175:
# line 1176 "pars.yacc"
{
	    g[cg].l.hgap = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 176:
# line 1179 "pars.yacc"
{
	    g[cg].l.len = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 177:
# line 1182 "pars.yacc"
{
	    g[cg].l.box = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 178:
# line 1185 "pars.yacc"
{
	    g[cg].l.boxfill = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 179:
# line 1188 "pars.yacc"
{
	    g[cg].l.boxfillusing = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 180:
# line 1192 "pars.yacc"
{
	    if (yypvt[-1].pset == COLOR) {
		g[cg].l.boxfillcolor = (int) yypvt[-0].val;
	    } else {
		g[cg].l.boxfillpat = (int) yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 181:
# line 1199 "pars.yacc"
{
	    g[cg].l.boxlcolor = checkon(COLOR, g[cg].l.boxlcolor, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 182:
# line 1202 "pars.yacc"
{
	    g[cg].l.boxlines = checkon(LINESTYLE, g[cg].l.boxlines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 183:
# line 1205 "pars.yacc"
{
	    g[cg].l.boxlinew = checkon(LINEWIDTH, g[cg].l.boxlinew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 184:
# line 1208 "pars.yacc"
{
	    g[cg].l.legx = yypvt[-2].val;
	    g[cg].l.legy = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 185:
# line 1212 "pars.yacc"
{
	    g[cg].l.legx = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 186:
# line 1215 "pars.yacc"
{
	    g[cg].l.legy = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 187:
# line 1218 "pars.yacc"
{
	    g[cg].l.charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 188:
# line 1221 "pars.yacc"
{
	    g[cg].l.font = checkon(FONTP, g[cg].l.font, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 189:
# line 1224 "pars.yacc"
{
	    g[cg].l.lines = checkon(LINESTYLE, g[cg].l.lines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 190:
# line 1227 "pars.yacc"
{
	    g[cg].l.linew = checkon(LINEWIDTH, g[cg].l.linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 191:
# line 1230 "pars.yacc"
{
	    g[cg].l.color = checkon(COLOR, g[cg].l.color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 192:
# line 1233 "pars.yacc"
{
	    strcpy(g[cg].l.str[(int) yypvt[-1].val].s, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 193:
# line 1236 "pars.yacc"
{
	    g[cg].f.active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 194:
# line 1239 "pars.yacc"
{
	    g[cg].f.type = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 195:
# line 1242 "pars.yacc"
{
	    g[cg].f.lines = checkon(LINESTYLE, g[cg].f.lines, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 196:
# line 1245 "pars.yacc"
{
	    g[cg].f.linew = checkon(LINEWIDTH, g[cg].f.linew, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 197:
# line 1248 "pars.yacc"
{
	    g[cg].f.color = checkon(COLOR, g[cg].f.color, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 198:
# line 1251 "pars.yacc"
{
	    g[cg].f.fillbg = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 199:
# line 1254 "pars.yacc"
{
	    g[cg].f.bgcolor = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 200:
# line 1257 "pars.yacc"
{
	    g[yypvt[-1].pset].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 201:
# line 1260 "pars.yacc"
{
	    g[yypvt[-2].pset].label = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 202:
# line 1263 "pars.yacc"
{
	    g[yypvt[-3].pset].auto_type = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 203:
# line 1266 "pars.yacc"
{
	    g[yypvt[-3].pset].auto_type = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 204:
# line 1269 "pars.yacc"
{
	    g[yypvt[-2].pset].parmsread = (yypvt[-0].pset == FALSEP);
	} /*NOTREACHED*/ break;
case 205:
# line 1272 "pars.yacc"
{
	    g[yypvt[-2].pset].hidden = (yypvt[-0].pset == TRUEP);
	} /*NOTREACHED*/ break;
case 206:
# line 1275 "pars.yacc"
{
	    g[yypvt[-2].pset].type = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 207:
# line 1278 "pars.yacc"
{
	    g[yypvt[-2].pset].pointset = (yypvt[-0].pset == ON);
	} /*NOTREACHED*/ break;
case 208:
# line 1282 "pars.yacc"
{
	    g[yypvt[-4].pset].fx = yypvt[-1].pset;
	    g[yypvt[-4].pset].fy = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 209:
# line 1287 "pars.yacc"
{
	    g[yypvt[-5].pset].px = yypvt[-2].val;
	    g[yypvt[-5].pset].py = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 210:
# line 1292 "pars.yacc"
{
	    g[yypvt[-5].pset].dsx = yypvt[-2].val;
	    g[yypvt[-5].pset].dsy = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 211:
# line 1296 "pars.yacc"
{
	    g[yypvt[-3].pset].pt_type = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 212:
# line 1299 "pars.yacc"
{
	    realloc_graph_plots(yypvt[-3].pset, (int) yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 213:
# line 1305 "pars.yacc"
{ g[cg].vp.vscale = yypvt[-0].val; } /*NOTREACHED*/ break;
case 214:
# line 1306 "pars.yacc"
{ g[cg].vp.active = yypvt[-0].pset; } /*NOTREACHED*/ break;
case 215:
# line 1307 "pars.yacc"
{ g[cg].vp.linew = (int) yypvt[-0].val; } /*NOTREACHED*/ break;
case 216:
# line 1308 "pars.yacc"
{ g[cg].vp.lines = (int) yypvt[-0].val; } /*NOTREACHED*/ break;
case 217:
# line 1309 "pars.yacc"
{ g[cg].vp.color = (int) yypvt[-0].val; } /*NOTREACHED*/ break;
case 218:
# line 1310 "pars.yacc"
{ g[cg].vp.loctype = yypvt[-0].pset; } /*NOTREACHED*/ break;
case 219:
# line 1311 "pars.yacc"
{ g[cg].vp.arrowtype = (int) yypvt[-0].val; } /*NOTREACHED*/ break;
case 220:
# line 1315 "pars.yacc"
{
	    yyval.pset = XY;
	} /*NOTREACHED*/ break;
case 221:
# line 1318 "pars.yacc"
{
	    yyval.pset = XYARC;
	} /*NOTREACHED*/ break;
case 222:
# line 1321 "pars.yacc"
{
	    yyval.pset = XYBOX;
	} /*NOTREACHED*/ break;
case 223:
# line 1324 "pars.yacc"
{
	    yyval.pset = XYHILO;
	} /*NOTREACHED*/ break;
case 224:
# line 1327 "pars.yacc"
{
	    yyval.pset = XYRT;
	} /*NOTREACHED*/ break;
case 225:
# line 1330 "pars.yacc"
{
	    yyval.pset = XYSEG;
	} /*NOTREACHED*/ break;
case 226:
# line 1333 "pars.yacc"
{
	    yyval.pset = XYSTRING;
	} /*NOTREACHED*/ break;
case 227:
# line 1336 "pars.yacc"
{
	    yyval.pset = XYDX;
	} /*NOTREACHED*/ break;
case 228:
# line 1339 "pars.yacc"
{
	    yyval.pset = XYDY;
	} /*NOTREACHED*/ break;
case 229:
# line 1342 "pars.yacc"
{
	    yyval.pset = XYDXDX;
	} /*NOTREACHED*/ break;
case 230:
# line 1345 "pars.yacc"
{
	    yyval.pset = XYDYDY;
	} /*NOTREACHED*/ break;
case 231:
# line 1348 "pars.yacc"
{
	    yyval.pset = XYDXDY;
	} /*NOTREACHED*/ break;
case 232:
# line 1351 "pars.yacc"
{
	    yyval.pset = XYX2Y2;
	} /*NOTREACHED*/ break;
case 233:
# line 1354 "pars.yacc"
{
	    yyval.pset = XYXX;
	} /*NOTREACHED*/ break;
case 234:
# line 1357 "pars.yacc"
{
	    yyval.pset = XYYY;
	} /*NOTREACHED*/ break;
case 235:
# line 1360 "pars.yacc"
{
	    yyval.pset = XYZ;
	} /*NOTREACHED*/ break;
case 236:
# line 1363 "pars.yacc"
{
	    yyval.pset = XYZW;
	} /*NOTREACHED*/ break;
case 237:
# line 1366 "pars.yacc"
{
	    yyval.pset = XYUV;
	} /*NOTREACHED*/ break;
case 238:
# line 1369 "pars.yacc"
{
	    yyval.pset = NXY;
	} /*NOTREACHED*/ break;
case 239:
# line 1372 "pars.yacc"
{
	    yyval.pset = BIN;
	} /*NOTREACHED*/ break;
case 240:
# line 1378 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 241:
# line 1381 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 242:
# line 1384 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 243:
# line 1387 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 244:
# line 1390 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 245:
# line 1393 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 246:
# line 1396 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 247:
# line 1399 "pars.yacc"
{
	    yyval.pset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 248:
# line 1402 "pars.yacc"
{
	    yyval.pset = XY;		/* not active */
	} /*NOTREACHED*/ break;
case 249:
# line 1405 "pars.yacc"
{
	    yyval.pset = XY;		/* not active */
	} /*NOTREACHED*/ break;
case 257:
# line 1435 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ACTIVE, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 258:
# line 1438 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ACTIVE, yypvt[-2].pset, 0);
	} /*NOTREACHED*/ break;
case 259:
# line 1441 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, TYPE, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 260:
# line 1444 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, MISSINGP, yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 261:
# line 1447 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, PREC, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 262:
# line 1450 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, FORMAT, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 263:
# line 1453 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, TYPE, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 264:
# line 1456 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, FILL, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 265:
# line 1459 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, CENTER, (yypvt[-0].pset == TRUEP), 0);
	} /*NOTREACHED*/ break;
case 266:
# line 1462 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, SIZE, yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 267:
# line 1465 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, CHAR, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 268:
# line 1468 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SYMBOL, SKIP, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 269:
# line 1471 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, yypvt[-1].pset, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 270:
# line 1474 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, FILL, TYPE, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 271:
# line 1477 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, FILL, WITH, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 272:
# line 1480 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, FILL, yypvt[-1].pset, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 273:
# line 1483 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, SKIP, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 274:
# line 1486 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, LENGTH, yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 275:
# line 1489 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, TYPE, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 276:
# line 1492 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, LINEWIDTH, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 277:
# line 1495 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, LINESTYLE, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 278:
# line 1498 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, RISER, ACTIVE, yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 279:
# line 1501 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, RISER, LINEWIDTH, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 280:
# line 1504 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, ERRORBAR, RISER, LINESTYLE, (int) yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 281:
# line 1507 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, XYZ, yypvt[-2].val, yypvt[-0].val, 0);
	} /*NOTREACHED*/ break;
case 282:
# line 1510 "pars.yacc"
{
	     set_prop(whichgraph, SET, SETNUM, whichset, COMMENT, (char *) yypvt[-0].pset, 0);
	} /*NOTREACHED*/ break;
case 298:
# line 1540 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-0].pset, 0.0);
	} /*NOTREACHED*/ break;
case 299:
# line 1543 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-1].pset, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 300:
# line 1546 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-1].pset, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 301:
# line 1549 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-1].pset, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 302:
# line 1552 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-1].pset, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 303:
# line 1555 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-2].pset, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 304:
# line 1558 "pars.yacc"
{
	     set_axis_prop(whichgraph, naxis, yypvt[-1].pset, yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 309:
# line 1568 "pars.yacc"
{
	    g[cg].t[naxis].active = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 312:
# line 1580 "pars.yacc"
{
	    g[cg].t[naxis].t_flag = yypvt[-0].pset;
	    g[cg].t[naxis].t_mflag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 313:
# line 1584 "pars.yacc"
{
	    g[cg].t[naxis].t_flag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 314:
# line 1587 "pars.yacc"
{
	    g[cg].t[naxis].t_mflag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 315:
# line 1590 "pars.yacc"
{
	    g[cg].t[naxis].tmajor = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 316:
# line 1593 "pars.yacc"
{
	    g[cg].t[naxis].tminor = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 317:
# line 1596 "pars.yacc"
{
	    g[cg].t[naxis].offsx = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 318:
# line 1599 "pars.yacc"
{
	    g[cg].t[naxis].offsy = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 319:
# line 1602 "pars.yacc"
{
	    g[cg].t[naxis].alt = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 320:
# line 1605 "pars.yacc"
{
	    g[cg].t[naxis].tmin = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 321:
# line 1608 "pars.yacc"
{
	    g[cg].t[naxis].tmax = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 322:
# line 1611 "pars.yacc"
{
	    g[cg].t[naxis].t_num = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 323:
# line 1614 "pars.yacc"
{
	    g[cg].t[naxis].t_inout = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 324:
# line 1617 "pars.yacc"
{
	    g[cg].t[naxis].t_log = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 325:
# line 1620 "pars.yacc"
{
	    g[cg].t[naxis].t_size = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 326:
# line 1623 "pars.yacc"
{
	    g[cg].t[naxis].t_size = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 327:
# line 1626 "pars.yacc"
{
	    g[cg].t[naxis].t_msize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 328:
# line 1629 "pars.yacc"
{
	    g[cg].t[naxis].t_color = g[cg].t[naxis].t_mcolor = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 329:
# line 1632 "pars.yacc"
{
	    g[cg].t[naxis].t_linew = g[cg].t[naxis].t_mlinew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 330:
# line 1635 "pars.yacc"
{
	    g[cg].t[naxis].t_color = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 331:
# line 1638 "pars.yacc"
{
	    g[cg].t[naxis].t_mcolor = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 332:
# line 1641 "pars.yacc"
{
	    g[cg].t[naxis].t_linew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 333:
# line 1644 "pars.yacc"
{
	    g[cg].t[naxis].t_mlinew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 334:
# line 1647 "pars.yacc"
{
	    g[cg].t[naxis].t_lines = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 335:
# line 1650 "pars.yacc"
{
	    g[cg].t[naxis].t_mlines = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 336:
# line 1653 "pars.yacc"
{
	    g[cg].t[naxis].t_gridflag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 337:
# line 1656 "pars.yacc"
{
	    g[cg].t[naxis].t_mgridflag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 338:
# line 1659 "pars.yacc"
{
	    g[cg].t[naxis].t_op = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 339:
# line 1662 "pars.yacc"
{
	    g[cg].t[naxis].t_type = AUTO;
	} /*NOTREACHED*/ break;
case 340:
# line 1665 "pars.yacc"
{
	    g[cg].t[naxis].t_type = SPEC;
	} /*NOTREACHED*/ break;
case 341:
# line 1668 "pars.yacc"
{
	    g[cg].t[naxis].t_spec = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 342:
# line 1671 "pars.yacc"
{
	    g[cg].t[naxis].t_specloc[(int) yypvt[-2].val] = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 345:
# line 1682 "pars.yacc"
{
	    g[cg].t[naxis].tl_flag = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 346:
# line 1685 "pars.yacc"
{
	    g[cg].t[naxis].tl_type = AUTO;
	} /*NOTREACHED*/ break;
case 347:
# line 1688 "pars.yacc"
{
	    g[cg].t[naxis].tl_type = SPEC;
	} /*NOTREACHED*/ break;
case 348:
# line 1691 "pars.yacc"
{
	    g[cg].t[naxis].tl_prec = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 349:
# line 1694 "pars.yacc"
{
	    g[cg].t[naxis].tl_format = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 350:
# line 1697 "pars.yacc"
{
	    g[cg].t[naxis].tl_format = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 351:
# line 1700 "pars.yacc"
{
	    strcpy(g[cg].t[naxis].tl_appstr, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 352:
# line 1703 "pars.yacc"
{
	    strcpy(g[cg].t[naxis].tl_prestr, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 353:
# line 1706 "pars.yacc"
{
	    g[cg].t[naxis].tl_layout = HORIZONTAL;
	} /*NOTREACHED*/ break;
case 354:
# line 1709 "pars.yacc"
{
	    g[cg].t[naxis].tl_layout = VERTICAL;
	} /*NOTREACHED*/ break;
case 355:
# line 1712 "pars.yacc"
{
	    g[cg].t[naxis].tl_layout = SPEC;
	} /*NOTREACHED*/ break;
case 356:
# line 1715 "pars.yacc"
{
	    g[cg].t[naxis].tl_angle = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 357:
# line 1718 "pars.yacc"
{
	    g[cg].t[naxis].tl_just = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 358:
# line 1721 "pars.yacc"
{
	    g[cg].t[naxis].tl_skip = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 359:
# line 1724 "pars.yacc"
{
	    g[cg].t[naxis].tl_staggered = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 360:
# line 1727 "pars.yacc"
{
	    g[cg].t[naxis].tl_op = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 361:
# line 1730 "pars.yacc"
{
	    g[cg].t[naxis].tl_sign = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 362:
# line 1733 "pars.yacc"
{
	    g[cg].t[naxis].tl_start = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 363:
# line 1736 "pars.yacc"
{
	    g[cg].t[naxis].tl_stop = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 364:
# line 1739 "pars.yacc"
{
	    g[cg].t[naxis].tl_starttype = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 365:
# line 1742 "pars.yacc"
{
	    g[cg].t[naxis].tl_starttype = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 366:
# line 1745 "pars.yacc"
{
	    g[cg].t[naxis].tl_stoptype = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 367:
# line 1748 "pars.yacc"
{
	    g[cg].t[naxis].tl_stoptype = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 368:
# line 1751 "pars.yacc"
{
	    g[cg].t[naxis].tl_vgap = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 369:
# line 1754 "pars.yacc"
{
	    g[cg].t[naxis].tl_hgap = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 370:
# line 1757 "pars.yacc"
{
	    g[cg].t[naxis].tl_charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 371:
# line 1760 "pars.yacc"
{
	    g[cg].t[naxis].tl_font = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 372:
# line 1763 "pars.yacc"
{
	    g[cg].t[naxis].tl_color = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 373:
# line 1766 "pars.yacc"
{
	    g[cg].t[naxis].tl_linew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 374:
# line 1769 "pars.yacc"
{
	    strcpy(g[cg].t[naxis].t_speclab[(int) yypvt[-2].val].s, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 375:
# line 1775 "pars.yacc"
{
	    strcpy(g[cg].t[naxis].label.s, (char *) yypvt[-0].pset);
	} /*NOTREACHED*/ break;
case 376:
# line 1778 "pars.yacc"
{
	    g[cg].t[naxis].label_layout = PERP;
	} /*NOTREACHED*/ break;
case 377:
# line 1781 "pars.yacc"
{
	    g[cg].t[naxis].label_layout = PARA;
	} /*NOTREACHED*/ break;
case 378:
# line 1784 "pars.yacc"
{
	    g[cg].t[naxis].label_place = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 379:
# line 1787 "pars.yacc"
{
	    g[cg].t[naxis].label_place = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 380:
# line 1790 "pars.yacc"
{
	    g[cg].t[naxis].label.x = yypvt[-2].val;
	    g[cg].t[naxis].label.y = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 381:
# line 1794 "pars.yacc"
{
	    g[cg].t[naxis].label.just = (int) yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 382:
# line 1797 "pars.yacc"
{
	    g[cg].t[naxis].label.charsize = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 383:
# line 1800 "pars.yacc"
{
	    g[cg].t[naxis].label.font = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 384:
# line 1803 "pars.yacc"
{
	    g[cg].t[naxis].label.color = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 385:
# line 1806 "pars.yacc"
{
	    g[cg].t[naxis].label.linew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 386:
# line 1812 "pars.yacc"
{
	    g[cg].t[naxis].t_drawbar = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 387:
# line 1815 "pars.yacc"
{
	    g[cg].t[naxis].t_drawbarcolor = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 388:
# line 1818 "pars.yacc"
{
	    g[cg].t[naxis].t_drawbarlines = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 389:
# line 1821 "pars.yacc"
{
	    g[cg].t[naxis].t_drawbarlinew = (int) yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 390:
# line 1828 "pars.yacc"
{
	    whichgraph = yypvt[-2].pset;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 391:
# line 1833 "pars.yacc"
{
	    whichgraph = cg;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 392:
# line 1838 "pars.yacc"
{
	    whichgraph = cg;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 393:
# line 1843 "pars.yacc"
{
	    whichgraph = yypvt[-1].pset;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 394:
# line 1848 "pars.yacc"
{
	    whichgraph = yypvt[-1].pset;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 395:
# line 1853 "pars.yacc"
{
	    whichgraph = yypvt[-1].pset;
	    whichset = yypvt[-0].pset;
	} /*NOTREACHED*/ break;
case 396:
# line 1860 "pars.yacc"
{
            yyval.pset = yypvt[-0].pset;
        } /*NOTREACHED*/ break;
case 397:
# line 1863 "pars.yacc"
{
            yyval.pset = yypvt[-0].pset;
        } /*NOTREACHED*/ break;
case 398:
# line 1866 "pars.yacc"
{
            yyval.pset = yypvt[-0].pset;
        } /*NOTREACHED*/ break;
case 399:
# line 1869 "pars.yacc"
{
            yyval.pset = yypvt[-0].pset;
        } /*NOTREACHED*/ break;
case 400:
# line 1872 "pars.yacc"
{
            yyval.pset = yypvt[-0].pset;
        } /*NOTREACHED*/ break;
case 401:
# line 1878 "pars.yacc"
{
	    yyval.pset = ON;
	} /*NOTREACHED*/ break;
case 402:
# line 1881 "pars.yacc"
{
	    yyval.pset = OFF;
	} /*NOTREACHED*/ break;
case 403:
# line 1887 "pars.yacc"
{
	    yyval.pset = COLOR;
	} /*NOTREACHED*/ break;
case 404:
# line 1890 "pars.yacc"
{
	    yyval.pset = PATTERN;
	} /*NOTREACHED*/ break;
case 405:
# line 1896 "pars.yacc"
{
	    yyval.pset = RUNAVG;
	} /*NOTREACHED*/ break;
case 406:
# line 1899 "pars.yacc"
{
	    yyval.pset = RUNSTD;
	} /*NOTREACHED*/ break;
case 407:
# line 1902 "pars.yacc"
{
	    yyval.pset = RUNMED;
	} /*NOTREACHED*/ break;
case 408:
# line 1905 "pars.yacc"
{
	    yyval.pset = RUNMAX;
	} /*NOTREACHED*/ break;
case 409:
# line 1908 "pars.yacc"
{
	    yyval.pset = RUNMIN;
	} /*NOTREACHED*/ break;
case 410:
# line 1914 "pars.yacc"
{
	    yyval.pset = DFT;
	} /*NOTREACHED*/ break;
case 411:
# line 1917 "pars.yacc"
{
	    yyval.pset = FFT;
	} /*NOTREACHED*/ break;
case 412:
# line 1920 "pars.yacc"
{
	    yyval.pset = INVDFT;
	} /*NOTREACHED*/ break;
case 413:
# line 1923 "pars.yacc"
{
	    yyval.pset = INVFFT;
	} /*NOTREACHED*/ break;
case 414:
# line 1929 "pars.yacc"
{
	    yyval.pset = DISK;
	} /*NOTREACHED*/ break;
case 415:
# line 1932 "pars.yacc"
{
	    yyval.pset = PIPE;
	} /*NOTREACHED*/ break;
case 416:
# line 1938 "pars.yacc"
{
	    yyval.pset = PATTERN;
	} /*NOTREACHED*/ break;
case 417:
# line 1941 "pars.yacc"
{
	    yyval.pset = COLOR;
	} /*NOTREACHED*/ break;
case 418:
# line 1944 "pars.yacc"
{
	    yyval.pset = NONE;
	} /*NOTREACHED*/ break;
case 419:
# line 1950 "pars.yacc"
{
	    yyval.pset = TOP;
	} /*NOTREACHED*/ break;
case 420:
# line 1953 "pars.yacc"
{
	    yyval.pset = BOTTOM;
	} /*NOTREACHED*/ break;
case 421:
# line 1956 "pars.yacc"
{
	    yyval.pset = LEFT;
	} /*NOTREACHED*/ break;
case 422:
# line 1959 "pars.yacc"
{
	    yyval.pset = RIGHT;
	} /*NOTREACHED*/ break;
case 423:
# line 1962 "pars.yacc"
{
	    yyval.pset = BOTH;
	} /*NOTREACHED*/ break;
case 424:
# line 1968 "pars.yacc"
{
	    yyval.pset = RIGHT;
	} /*NOTREACHED*/ break;
case 425:
# line 1971 "pars.yacc"
{
	    yyval.pset = LEFT;
	} /*NOTREACHED*/ break;
case 426:
# line 1974 "pars.yacc"
{
	    yyval.pset = CENTER;
	} /*NOTREACHED*/ break;
case 427:
# line 1980 "pars.yacc"
{
	    yyval.pset = XMIN;
	} /*NOTREACHED*/ break;
case 428:
# line 1983 "pars.yacc"
{
	    yyval.pset = XMAX;
	} /*NOTREACHED*/ break;
case 429:
# line 1986 "pars.yacc"
{
	    yyval.pset = YMIN;
	} /*NOTREACHED*/ break;
case 430:
# line 1989 "pars.yacc"
{
	    yyval.pset = YMAX;
	} /*NOTREACHED*/ break;
case 431:
# line 1995 "pars.yacc"
{
	    yyval.pset = TRUEP;
	} /*NOTREACHED*/ break;
case 432:
# line 1998 "pars.yacc"
{
	    yyval.pset = FALSEP;
	} /*NOTREACHED*/ break;
case 433:
# line 2004 "pars.yacc"
{
	    yyval.pset = IN;
	} /*NOTREACHED*/ break;
case 434:
# line 2007 "pars.yacc"
{
	    yyval.pset = OUT;
	} /*NOTREACHED*/ break;
case 435:
# line 2010 "pars.yacc"
{
	    yyval.pset = BOTH;
	} /*NOTREACHED*/ break;
case 436:
# line 2016 "pars.yacc"
{
	    yyval.pset = DECIMAL;
	} /*NOTREACHED*/ break;
case 437:
# line 2019 "pars.yacc"
{
	    yyval.pset = EXPONENTIAL;
	} /*NOTREACHED*/ break;
case 438:
# line 2022 "pars.yacc"
{
	    yyval.pset = POWER;
	} /*NOTREACHED*/ break;
case 439:
# line 2025 "pars.yacc"
{
	    yyval.pset = GENERAL;
	} /*NOTREACHED*/ break;
case 440:
# line 2028 "pars.yacc"
{
	    yyval.pset = DDMMYY;
	} /*NOTREACHED*/ break;
case 441:
# line 2031 "pars.yacc"
{
	    yyval.pset = MMDDYY;
	} /*NOTREACHED*/ break;
case 442:
# line 2034 "pars.yacc"
{
	    yyval.pset = MMYY;
	} /*NOTREACHED*/ break;
case 443:
# line 2037 "pars.yacc"
{
	    yyval.pset = MMDD;
	} /*NOTREACHED*/ break;
case 444:
# line 2040 "pars.yacc"
{
	    yyval.pset = MONTHDAY;
	} /*NOTREACHED*/ break;
case 445:
# line 2043 "pars.yacc"
{
	    yyval.pset = DAYMONTH;
	} /*NOTREACHED*/ break;
case 446:
# line 2046 "pars.yacc"
{
	    yyval.pset = MONTHS;
	} /*NOTREACHED*/ break;
case 447:
# line 2049 "pars.yacc"
{
	    yyval.pset = MONTHL;
	} /*NOTREACHED*/ break;
case 448:
# line 2052 "pars.yacc"
{
	    yyval.pset = DAYOFWEEKS;
	} /*NOTREACHED*/ break;
case 449:
# line 2055 "pars.yacc"
{
	    yyval.pset = DAYOFWEEKL;
	} /*NOTREACHED*/ break;
case 450:
# line 2058 "pars.yacc"
{
	    yyval.pset = DAYOFYEAR;
	} /*NOTREACHED*/ break;
case 451:
# line 2061 "pars.yacc"
{
	    yyval.pset = HMS;
	} /*NOTREACHED*/ break;
case 452:
# line 2064 "pars.yacc"
{
	    yyval.pset = MMDDHMS;
	} /*NOTREACHED*/ break;
case 453:
# line 2067 "pars.yacc"
{
	    yyval.pset = MMDDYYHMS;
	} /*NOTREACHED*/ break;
case 454:
# line 2070 "pars.yacc"
{
	    yyval.pset = DEGREESLON;
	} /*NOTREACHED*/ break;
case 455:
# line 2073 "pars.yacc"
{
	    yyval.pset = DEGREESMMLON;
	} /*NOTREACHED*/ break;
case 456:
# line 2076 "pars.yacc"
{
	    yyval.pset = DEGREESMMSSLON;
	} /*NOTREACHED*/ break;
case 457:
# line 2079 "pars.yacc"
{
	    yyval.pset = MMSSLON;
	} /*NOTREACHED*/ break;
case 458:
# line 2082 "pars.yacc"
{
	    yyval.pset = DEGREESLAT;
	} /*NOTREACHED*/ break;
case 459:
# line 2085 "pars.yacc"
{
	    yyval.pset = DEGREESMMLAT;
	} /*NOTREACHED*/ break;
case 460:
# line 2088 "pars.yacc"
{
	    yyval.pset = DEGREESMMSSLAT;
	} /*NOTREACHED*/ break;
case 461:
# line 2091 "pars.yacc"
{
	    yyval.pset = MMSSLAT;
	} /*NOTREACHED*/ break;
case 462:
# line 2097 "pars.yacc"
{
	    yyval.pset = NORMAL;
	} /*NOTREACHED*/ break;
case 463:
# line 2100 "pars.yacc"
{
	    yyval.pset = ABSOLUTE;
	} /*NOTREACHED*/ break;
case 464:
# line 2103 "pars.yacc"
{
	    yyval.pset = NEGATE;
	} /*NOTREACHED*/ break;
case 465:
# line 2109 "pars.yacc"
{
	    yyval.pset = UP;
	} /*NOTREACHED*/ break;
case 466:
# line 2112 "pars.yacc"
{
	    yyval.pset = DOWN;
	} /*NOTREACHED*/ break;
case 467:
# line 2115 "pars.yacc"
{
	    yyval.pset = RIGHT;
	} /*NOTREACHED*/ break;
case 468:
# line 2118 "pars.yacc"
{
	    yyval.pset = LEFT;
	} /*NOTREACHED*/ break;
case 469:
# line 2121 "pars.yacc"
{
	    yyval.pset = IN;
	} /*NOTREACHED*/ break;
case 470:
# line 2124 "pars.yacc"
{
	    yyval.pset = OUT;
	} /*NOTREACHED*/ break;
case 471:
# line 2130 "pars.yacc"
{
	    yyval.pset = WORLD;
	} /*NOTREACHED*/ break;
case 472:
# line 2133 "pars.yacc"
{
	    yyval.pset = VIEW;
	} /*NOTREACHED*/ break;
case 473:
# line 2140 "pars.yacc"
{
	    int itmp = (int) yypvt[-3].val - 1;
	    if (itmp >= ls) {
		yyerror("subscript out of range");
		return 1;
	    } else {
		yypvt[-5].ptr[itmp] = yypvt[-0].val;
		result = yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 474:
# line 2151 "pars.yacc"
{
	    int itmp = (int) yypvt[-3].val - 1;
	    if (itmp >= lxy) {
		yyerror("subscript out of range");
		return 1;
	    } else {
		yypvt[-5].ptr[itmp] = yypvt[-0].val;
		result = yypvt[-0].val;
	    }
	    updatesetminmax(cg, curset);
        update_set_status(cg, curset);
	} /*NOTREACHED*/ break;
case 475:
# line 2164 "pars.yacc"
{
	    /*
	     * what is on the stack is a pointer to x we need a pointer to
	     * the set SETNUM x or y 
	     */
	    int itmp = (int) yypvt[-3].val - 1;
	    if (yypvt[-5].ptr == xx) {
		g[cg].p[yypvt[-7].pset].ex[0][itmp] = yypvt[-0].val;
	    } else {
		g[cg].p[yypvt[-7].pset].ex[1][itmp] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	    updatesetminmax(cg, yypvt[-7].pset);
        update_set_status(cg, yypvt[-7].pset);
	} /*NOTREACHED*/ break;
case 476:
# line 2180 "pars.yacc"
{
	    /*
	     * what is on the stack is a pointer to x we need a pointer to
	     * the set SETNUM x or y 
	     */
	    int itmp = (int) yypvt[-3].val - 1;
	    if (yypvt[-5].ptr == xx) {
		g[yypvt[-9].pset].p[yypvt[-7].pset].ex[0][itmp] = yypvt[-0].val;
	    } else if (yypvt[-5].ptr == yy) {
		g[yypvt[-9].pset].p[yypvt[-7].pset].ex[1][itmp] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	    updatesetminmax(yypvt[-9].pset, yypvt[-7].pset);
        update_set_status(yypvt[-9].pset, yypvt[-7].pset);
	} /*NOTREACHED*/ break;
case 477:
# line 2199 "pars.yacc"
{
	    if (yypvt[-2].ptr == xx) {
		*xx = yypvt[-0].val;
	    } else {
		*yy = yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 478:
# line 2210 "pars.yacc"
{
	    int i;
	    for (i = 0; i < lxy; i++) {
		yypvt[-2].ptr[i] = yypvt[-0].ptr[i];
	    }
	    result = yypvt[-0].ptr[0];
	} /*NOTREACHED*/ break;
case 479:
# line 2218 "pars.yacc"
{
	    int i;
	    for (i = 0; i < lxy; i++) {
		yypvt[-2].ptr[i] = yypvt[-0].ptr[i];
	    }
	    result = yypvt[-0].ptr[0];
	    updatesetminmax(cg, curset);
        update_set_status(cg, curset);
	} /*NOTREACHED*/ break;
case 480:
# line 2228 "pars.yacc"
{
	    int i;
	    double *tmp;
	    if (!isactive_set(cg, yypvt[-4].pset)) {
		activateset(cg, yypvt[-4].pset);
		setlength(cg, yypvt[-4].pset, lxy);
		setcomment(cg, yypvt[-4].pset, "Created");
	    }
	    if (yypvt[-2].ptr == xx) {
		tmp = g[cg].p[yypvt[-4].pset].ex[0];
	    } else {
		tmp = g[cg].p[yypvt[-4].pset].ex[1];
	    }
	    for (i = 0; i < lxy; i++) {
		tmp[i] = yypvt[-0].ptr[i];
	    }
	    result = yypvt[-0].ptr[0];
	    updatesetminmax(cg, yypvt[-4].pset);
        update_set_status(cg, yypvt[-4].pset);
	} /*NOTREACHED*/ break;
case 481:
# line 2249 "pars.yacc"
{
	    int i;
	    double *tmp;
	    if (!isactive_set(yypvt[-6].pset, yypvt[-4].pset)) {
		activateset(yypvt[-6].pset, yypvt[-4].pset);
		setlength(yypvt[-6].pset, yypvt[-4].pset, lxy);
		setcomment(yypvt[-6].pset, yypvt[-4].pset, "Created");
	    }
	    if (yypvt[-2].ptr == xx) {
		tmp = g[yypvt[-6].pset].p[yypvt[-4].pset].ex[0];
	    } else {
		tmp = g[yypvt[-6].pset].p[yypvt[-4].pset].ex[1];
	    }
	    for (i = 0; i < lxy; i++) {
		tmp[i] = yypvt[-0].ptr[i];
	    }
	    result = yypvt[-0].ptr[0];
	    updatesetminmax(yypvt[-6].pset, yypvt[-4].pset);
        update_set_status(yypvt[-6].pset, yypvt[-4].pset);
	} /*NOTREACHED*/ break;
case 482:
# line 2270 "pars.yacc"
{
	    int i;
	    for (i = 0; i < lxy; i++) {
		yypvt[-2].ptr[i] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 483:
# line 2278 "pars.yacc"
{
	    int i;
	    for (i = 0; i < lxy; i++) {
		yypvt[-2].ptr[i] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	    updatesetminmax(cg, curset);
        update_set_status(cg, curset);
	} /*NOTREACHED*/ break;
case 484:
# line 2288 "pars.yacc"
{
	    int i;
	    double *tmp;
	    if (yypvt[-2].ptr == xx) {
		tmp = g[cg].p[yypvt[-4].pset].ex[0];
	    } else {
		tmp = g[cg].p[yypvt[-4].pset].ex[1];
	    }
	    for (i = 0; i < lxy; i++) {
		tmp[i] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	    updatesetminmax(cg, yypvt[-4].pset);
        update_set_status(cg, yypvt[-4].pset);
	} /*NOTREACHED*/ break;
case 485:
# line 2304 "pars.yacc"
{
	    int i;
	    double *tmp;
	    if (yypvt[-2].ptr == xx) {
		tmp = g[yypvt[-6].pset].p[yypvt[-4].pset].ex[0];
	    } else {
		tmp = g[yypvt[-6].pset].p[yypvt[-4].pset].ex[1];
	    }
	    for (i = 0; i < lxy; i++) {
		tmp[i] = yypvt[-0].val;
	    }
	    result = yypvt[-0].val;
	    updatesetminmax(yypvt[-6].pset, yypvt[-4].pset);
        update_set_status(yypvt[-6].pset, yypvt[-4].pset);
	} /*NOTREACHED*/ break;
case 486:
# line 2323 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 487:
# line 2332 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 488:
# line 2341 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		if (yypvt[-0].ptr == xx) {
		    yyval.ptr[i] = g[yypvt[-4].pset].p[yypvt[-2].pset].ex[0][i];
		} else {
		    yyval.ptr[i] = g[yypvt[-4].pset].p[yypvt[-2].pset].ex[1][i];
		}
	    }
	} /*NOTREACHED*/ break;
case 489:
# line 2354 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		if (yypvt[-0].ptr == xx) {
		    yyval.ptr[i] = g[cg].p[yypvt[-2].pset].ex[0][i];
		} else {
		    yyval.ptr[i] = g[cg].p[yypvt[-2].pset].ex[1][i];
		}
	    }
	} /*NOTREACHED*/ break;
case 490:
# line 2367 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 491:
# line 2376 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val + yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 492:
# line 2385 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] + yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 493:
# line 2394 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val + yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 494:
# line 2403 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] + yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 495:
# line 2412 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val - yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 496:
# line 2421 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] - yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 497:
# line 2430 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val - yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 498:
# line 2439 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] - yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 499:
# line 2448 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val * yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 500:
# line 2457 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] * yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 501:
# line 2466 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val * yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 502:
# line 2475 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] * yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 503:
# line 2484 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    if (yypvt[-0].val == 0.0) {
		yyerror("Divide by Zero");
		return 1;
	    }
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val / yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 504:
# line 2497 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		if (yypvt[-0].ptr[i] == 0.0) {
		    yyerror("Divide by Zero");
		    return 1;
		}
	    }
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] / yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 505:
# line 2512 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		if (yypvt[-0].ptr[i] == 0.0) {
		    yyerror("Divide by Zero");
		    return 1;
		}
	    }
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].val / yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 506:
# line 2527 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    if (yypvt[-0].val == 0.0) {
		yyerror("Divide by Zero");
		return 1;
	    }
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] / yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 507:
# line 2540 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = pow(yypvt[-2].val, yypvt[-0].val);
	    }
	} /*NOTREACHED*/ break;
case 508:
# line 2549 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = pow(yypvt[-2].val, yypvt[-0].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 509:
# line 2558 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = pow(yypvt[-2].ptr[i], yypvt[-0].val);
	    }
	} /*NOTREACHED*/ break;
case 510:
# line 2567 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = pow(yypvt[-2].ptr[i], yypvt[-0].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 511:
# line 2576 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = fabs(yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 512:
# line 2585 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = fabs(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 513:
# line 2594 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = acos(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 514:
# line 2603 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = asin(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 515:
# line 2612 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = atan(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 516:
# line 2621 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = atan2(yypvt[-3].ptr[i], yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 517:
# line 2630 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = ceil(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 518:
# line 2639 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = cos(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 519:
# line 2648 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] *= M_PI / 180.0;
	    }
	} /*NOTREACHED*/ break;
case 520:
# line 2657 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = xx[i];
	    }
	} /*NOTREACHED*/ break;
case 521:
# line 2666 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yy[i];
	    }
	} /*NOTREACHED*/ break;
case 522:
# line 2675 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = erf(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 523:
# line 2684 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = erfc(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 524:
# line 2693 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = exp(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 525:
# line 2702 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = floor(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 526:
# line 2711 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = hypot(yypvt[-3].ptr[i], yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 527:
# line 2720 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = hypot(yypvt[-3].val, yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 528:
# line 2729 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = hypot(yypvt[-3].ptr[i], yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 529:
# line 2738 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = hypot(yypvt[-3].val, yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 530:
# line 2747 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = i + 1;
	    }
	} /*NOTREACHED*/ break;
case 531:
# line 2756 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-0].func;
	    }
	} /*NOTREACHED*/ break;
case 532:
# line 2765 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = (int) yypvt[-1].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 533:
# line 2774 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = invnorm(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 534:
# line 2783 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = invt(yypvt[-3].val, (int) yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 535:
# line 2792 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = invt(yypvt[-3].ptr[i], (int) yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 536:
# line 2801 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = lrand48() % (long) (yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 537:
# line 2810 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = lgamma(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 538:
# line 2819 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = log(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 539:
# line 2828 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = log10(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 540:
# line 2837 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = 1.0 / (1.0 + exp(-(yypvt[-5].ptr[i] - yypvt[-3].val)/ yypvt[-1].val));
	    }
	} /*NOTREACHED*/ break;
case 541:
# line 2846 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-3].ptr[i] >= yypvt[-1].ptr[i] ? yypvt[-3].ptr[i] : yypvt[-1].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 542:
# line 2855 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-3].ptr[i] <= yypvt[-1].ptr[i] ? yypvt[-3].ptr[i] : yypvt[-1].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 543:
# line 2864 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = fmod(yypvt[-3].ptr[i], yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 544:
# line 2873 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = fx(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 545:
# line 2882 "pars.yacc"
{
	    int i;
	    double tmp;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = normp(yypvt[-1].ptr[i], &tmp);
	    }
	} /*NOTREACHED*/ break;
case 546:
# line 2892 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = M_PI;
	    }
	} /*NOTREACHED*/ break;
case 547:
# line 2901 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = M_PI / 180.0;
	    }
	} /*NOTREACHED*/ break;
case 548:
# line 2910 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = (double) drand48();
	    }
	} /*NOTREACHED*/ break;
case 549:
# line 2919 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = rnorm(yypvt[-3].ptr[i], yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 550:
# line 2928 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = rnorm(yypvt[-3].val, yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 551:
# line 2937 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = rnorm(yypvt[-3].ptr[i], yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 552:
# line 2946 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = rnorm(yypvt[-3].val, yypvt[-1].val);
	    }
	} /*NOTREACHED*/ break;
case 553:
# line 2955 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = sin(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 554:
# line 2964 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-1].ptr[i] * yypvt[-1].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 555:
# line 2973 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = sqrt(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 556:
# line 2982 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = tan(yypvt[-1].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 557:
# line 2990 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
	        if ((int) yypvt[-4].ptr[i]) {
		    yyval.ptr[i] = yypvt[-2].ptr[i];
	        } else {
		    yyval.ptr[i] = yypvt[-0].ptr[i];
	        }
	    }
	} /*NOTREACHED*/ break;
case 558:
# line 3003 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] > yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 559:
# line 3012 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] < yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 560:
# line 3021 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] <= yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 561:
# line 3030 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] >= yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 562:
# line 3039 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] == yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 563:
# line 3048 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] != yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 564:
# line 3057 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] && yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 565:
# line 3066 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-2].ptr[i] || yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 566:
# line 3075 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = !(yypvt[-0].ptr[i]);
	    }
	} /*NOTREACHED*/ break;
case 567:
# line 3084 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = yypvt[-1].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 568:
# line 3092 "pars.yacc"
{
	    int i;
	    yyval.ptr = (double *) calloc(lxy, sizeof(double));
	    freelist[fcnt++] = yyval.ptr;
	    for (i = 0; i < lxy; i++) {
		yyval.ptr[i] = -yypvt[-0].ptr[i];
	    }
	} /*NOTREACHED*/ break;
case 570:
# line 3103 "pars.yacc"
{
	    yyval.val = yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 571:
# line 3106 "pars.yacc"
{
	    yyval.val = yypvt[-3].ptr[(int) yypvt[-1].val];
	} /*NOTREACHED*/ break;
case 572:
# line 3109 "pars.yacc"
{
	    yyval.val = yypvt[-3].ptr[(int) yypvt[-1].val - 1];
	} /*NOTREACHED*/ break;
case 573:
# line 3112 "pars.yacc"
{
	    yyval.val = (yypvt[-0].ptr == xx) ? *xx : *yy;
	} /*NOTREACHED*/ break;
case 574:
# line 3115 "pars.yacc"
{
	    if (yypvt[-3].ptr == xx) {
		yyval.val = g[cg].p[yypvt[-5].pset].ex[0][(int) yypvt[-1].val - 1];
	    } else if (yypvt[-3].ptr == yy) {
		yyval.val = g[cg].p[yypvt[-5].pset].ex[1][(int) yypvt[-1].val - 1];
	    }
	} /*NOTREACHED*/ break;
case 575:
# line 3122 "pars.yacc"
{
	    switch (yypvt[-0].pset) {
	    case XMIN:
		yyval.val = g[cg].p[yypvt[-2].pset].xmin;
		break;
	    case YMIN:
		yyval.val = g[cg].p[yypvt[-2].pset].ymin;
		break;
	    case XMAX:
		yyval.val = g[cg].p[yypvt[-2].pset].xmax;
		break;
	    case YMAX:
		yyval.val = g[cg].p[yypvt[-2].pset].ymax;
		break;
	    }
	} /*NOTREACHED*/ break;
case 576:
# line 3138 "pars.yacc"
{
	    yyval.val = g[cg].p[yypvt[-2].pset].len;
	} /*NOTREACHED*/ break;
case 577:
# line 3142 "pars.yacc"
{
	    double bar, sd;
	    if (yypvt[-1].ptr == xx) {
		stasum(getx(cg, yypvt[-3].pset), getsetlength(cg, yypvt[-3].pset), &bar, &sd, 0);
	    } else if (yypvt[-1].ptr == yy) {
		 stasum(gety(cg, yypvt[-3].pset), getsetlength(cg, yypvt[-3].pset), &bar, &sd, 0);
	    }
	    yyval.val = bar;
	} /*NOTREACHED*/ break;
case 578:
# line 3151 "pars.yacc"
{
	    if (yypvt[-3].ptr == xx) {
		yyval.val = g[yypvt[-7].pset].p[yypvt[-5].pset].ex[0][(int) yypvt[-1].val - 1];
	    } else if (yypvt[-3].ptr == yy) {
		yyval.val = g[yypvt[-7].pset].p[yypvt[-5].pset].ex[1][(int) yypvt[-1].val - 1];
	    }
	} /*NOTREACHED*/ break;
case 579:
# line 3158 "pars.yacc"
{
	    yyval.val = yypvt[-2].val + yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 580:
# line 3161 "pars.yacc"
{
	    yyval.val = yypvt[-2].val - yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 581:
# line 3164 "pars.yacc"
{
	    yyval.val = yypvt[-2].val * yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 582:
# line 3168 "pars.yacc"
{
	    if (yypvt[-0].val != 0.0) {
		yyval.val = yypvt[-2].val / yypvt[-0].val;
	    } else {
		yyerror("Divide by Zero");
		return 1;
	    }
	} /*NOTREACHED*/ break;
case 583:
# line 3176 "pars.yacc"
{
	    yyval.val = fmod(yypvt[-2].val, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 584:
# line 3179 "pars.yacc"
{
	    yyval.val = pow(yypvt[-2].val, yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 585:
# line 3182 "pars.yacc"
{
	    yyval.val = fabs(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 586:
# line 3185 "pars.yacc"
{
	    yyval.val = acos(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 587:
# line 3188 "pars.yacc"
{
	    yyval.val = asin(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 588:
# line 3191 "pars.yacc"
{
	    yyval.val = atan(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 589:
# line 3194 "pars.yacc"
{
	    yyval.val = atan2(yypvt[-3].val, yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 590:
# line 3197 "pars.yacc"
{
	    yyval.val = ceil(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 591:
# line 3200 "pars.yacc"
{
	    yyval.val = cos(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 592:
# line 3203 "pars.yacc"
{
	    yyval.val = 180.0 / M_PI;
	} /*NOTREACHED*/ break;
case 593:
# line 3206 "pars.yacc"
{
	    yyval.val = *xx;
	} /*NOTREACHED*/ break;
case 594:
# line 3209 "pars.yacc"
{
	    yyval.val = *yy;
	} /*NOTREACHED*/ break;
case 595:
# line 3212 "pars.yacc"
{
	    yyval.val = erf(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 596:
# line 3215 "pars.yacc"
{
	    yyval.val = erfc(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 597:
# line 3218 "pars.yacc"
{
	    yyval.val = exp(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 598:
# line 3221 "pars.yacc"
{
	    yyval.val = floor(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 599:
# line 3224 "pars.yacc"
{
	    yyval.val = hypot(yypvt[-3].val, yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 600:
# line 3227 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].v.xv1;
	} /*NOTREACHED*/ break;
case 601:
# line 3230 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].v.xv2;
	} /*NOTREACHED*/ break;
case 602:
# line 3233 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].v.yv1;
	} /*NOTREACHED*/ break;
case 603:
# line 3236 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].v.yv2;
	} /*NOTREACHED*/ break;
case 604:
# line 3239 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].w.xg1;
	} /*NOTREACHED*/ break;
case 605:
# line 3242 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].w.xg2;
	} /*NOTREACHED*/ break;
case 606:
# line 3245 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].w.yg1;
	} /*NOTREACHED*/ break;
case 607:
# line 3248 "pars.yacc"
{
	    yyval.val = g[yypvt[-2].pset].w.yg2;
	} /*NOTREACHED*/ break;
case 608:
# line 3251 "pars.yacc"
{
	    yyval.val = g[cg].v.xv1;
	} /*NOTREACHED*/ break;
case 609:
# line 3254 "pars.yacc"
{
	    yyval.val = g[cg].v.xv2;
	} /*NOTREACHED*/ break;
case 610:
# line 3257 "pars.yacc"
{
	    yyval.val = g[cg].v.yv1;
	} /*NOTREACHED*/ break;
case 611:
# line 3260 "pars.yacc"
{
	    yyval.val = g[cg].v.yv2;
	} /*NOTREACHED*/ break;
case 612:
# line 3263 "pars.yacc"
{
	    yyval.val = g[cg].w.xg1;
	} /*NOTREACHED*/ break;
case 613:
# line 3266 "pars.yacc"
{
	    yyval.val = g[cg].w.xg2;
	} /*NOTREACHED*/ break;
case 614:
# line 3269 "pars.yacc"
{
	    yyval.val = g[cg].w.yg1;
	} /*NOTREACHED*/ break;
case 615:
# line 3272 "pars.yacc"
{
	    yyval.val = g[cg].w.yg2;
	} /*NOTREACHED*/ break;
case 616:
# line 3275 "pars.yacc"
{
	    yyval.val = setindex;
	} /*NOTREACHED*/ break;
case 617:
# line 3278 "pars.yacc"
{
	    yyval.val = setsetno;
	} /*NOTREACHED*/ break;
case 618:
# line 3281 "pars.yacc"
{
	    yyval.val = (long) yypvt[-1].val;
	} /*NOTREACHED*/ break;
case 619:
# line 3284 "pars.yacc"
{
	    yyval.val = invnorm(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 620:
# line 3287 "pars.yacc"
{
	    yyval.val = invt(yypvt[-3].val, (int) yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 621:
# line 3290 "pars.yacc"
{
	    yyval.val = lrand48() % (long) (yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 622:
# line 3293 "pars.yacc"
{
	    yyval.val = lgamma(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 623:
# line 3296 "pars.yacc"
{
	    yyval.val = log(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 624:
# line 3299 "pars.yacc"
{
	    yyval.val = log10(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 625:
# line 3303 "pars.yacc"
{
	    yyval.val = 1.0 / (1.0 + exp(-(yypvt[-5].val - yypvt[-3].val)/ yypvt[-1].val));
	} /*NOTREACHED*/ break;
case 626:
# line 3306 "pars.yacc"
{
	    yyval.val = yypvt[-3].val >= yypvt[-1].val ? yypvt[-3].val : yypvt[-1].val;
	} /*NOTREACHED*/ break;
case 627:
# line 3309 "pars.yacc"
{
	    yyval.val = yypvt[-3].val <= yypvt[-1].val ? yypvt[-3].val : yypvt[-1].val;
	} /*NOTREACHED*/ break;
case 628:
# line 3312 "pars.yacc"
{
	    yyval.val = fmod(yypvt[-3].val, yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 629:
# line 3315 "pars.yacc"
{
	    yyval.val = fx(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 630:
# line 3318 "pars.yacc"
{
	    double tmp;
	    yyval.val = normp(yypvt[-1].val, &tmp);
	} /*NOTREACHED*/ break;
case 631:
# line 3322 "pars.yacc"
{
	    yyval.val = M_PI;
	} /*NOTREACHED*/ break;
case 632:
# line 3325 "pars.yacc"
{
	    yyval.val = M_PI / 180.0;
	} /*NOTREACHED*/ break;
case 633:
# line 3328 "pars.yacc"
{
	    yyval.val = (double) drand48();
	} /*NOTREACHED*/ break;
case 634:
# line 3331 "pars.yacc"
{
	    yyval.val = rnorm(yypvt[-3].val, yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 635:
# line 3334 "pars.yacc"
{
	    yyval.val = sin(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 636:
# line 3337 "pars.yacc"
{
	    yyval.val = pow(yypvt[-1].val, 2.0);
	} /*NOTREACHED*/ break;
case 637:
# line 3340 "pars.yacc"
{
	    yyval.val = sqrt(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 638:
# line 3343 "pars.yacc"
{
	    yyval.val = tan(yypvt[-1].val);
	} /*NOTREACHED*/ break;
case 639:
# line 3346 "pars.yacc"
{
	    if ((int) yypvt[-4].val) {
		yyval.val = yypvt[-2].val;
	    } else {
		yyval.val = yypvt[-0].val;
	    }
	} /*NOTREACHED*/ break;
case 640:
# line 3353 "pars.yacc"
{
	    yyval.val = yypvt[-2].val > yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 641:
# line 3356 "pars.yacc"
{
	    yyval.val = yypvt[-2].val < yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 642:
# line 3359 "pars.yacc"
{
	    yyval.val = yypvt[-2].val <= yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 643:
# line 3362 "pars.yacc"
{
	    yyval.val = yypvt[-2].val >= yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 644:
# line 3365 "pars.yacc"
{
	    yyval.val = yypvt[-2].val == yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 645:
# line 3368 "pars.yacc"
{
	    yyval.val = yypvt[-2].val != yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 646:
# line 3371 "pars.yacc"
{
	    yyval.val = yypvt[-2].val && yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 647:
# line 3374 "pars.yacc"
{
	    yyval.val = yypvt[-2].val || yypvt[-0].val;
	} /*NOTREACHED*/ break;
case 648:
# line 3377 "pars.yacc"
{
	    yyval.val = !(yypvt[-0].val);
	} /*NOTREACHED*/ break;
case 649:
# line 3380 "pars.yacc"
{
	    yyval.val = yypvt[-1].val;
	} /*NOTREACHED*/ break;
case 650:
# line 3383 "pars.yacc"
{
	    yyval.val = -yypvt[-0].val;
	} /*NOTREACHED*/ break;
}


        goto yystack;           /* reset registers in driver code */
}
