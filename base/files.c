/* $Id: files.c,v 1.28 1993/03/20 16:35:34 pturner Exp pturner $
 *
 * read data files
 *
 */

#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "globals.h"

int realtime = 0;
int change_gno;			/* if the graph number changes on read in */
static int cur_gno;		/* if the graph number changes on read in */
int change_type;		/* current set type */
static int cur_type;		/* current set type */

#define MAX_LINE_LEN 512

/*
 * number of doubles to allocate for each call to realloc
 */
#define BUFSIZE  512

static int readerror = 0;
int readxy(int gno, char *fn, FILE *fp, int readone);

int getdata(int gno, char* fn, int src, int type)
{
    FILE *fp = NULL;
    int retval;
    struct stat statb;
    
    printf("getdata %i %s %i %i \n",gno,fn,src,type);

    switch (src) {
    case DISK:
	/* check to make sure this is a file and not a dir */
	if (stat(fn, &statb)) {
	    break;		/* couldn't stat */
	}
	if (statb.st_mode & S_IFREG) {
	    fp = fopen(fn, "r");/* open if regular file */
	} else {
	    sprintf(buf, "File %s is not a regular file", fn);
	    errwin(buf);
	    return 0;
	}
	break;
    case PIPE:
	fp = popen(fn, "r");
	break;
    case 2:
	fp = stdin;
	break;
    }
    if (fp == NULL) {
	sprintf(buf, "Can't open file %s", fn);
	errwin(buf);
	return 0;
    }
    cur_gno = gno;
    change_type = cur_type = type;
    retval = -1;
    while (retval == -1) {
	retval = 0;
	switch (cur_type) {
	case XY:
	    retval = readxy(cur_gno, fn, fp, 0);
	    break;
	case NXY:
	    //csto retval = readnxy(cur_gno, fn, fp);
	    break;
	case IHL:
	    //csto retval = readihl(cur_gno, fn, fp);
	    break;
	case BIN:
	    //csto retval = readbinary(cur_gno, fn, fp);
	    break;
	case XYDX:
	case XYDY:
	case XYDXDX:
	case XYDYDY:
	case XYDXDY:
	case XYZ:
	case XYRT:
	case XYHILO:
	case XYUV:
	case XYBOX:
	    //csto retval = readxxyy(cur_gno, fn, fp, cur_type);
	    break;
	case XYSTRING:
	    //csto retval = readxystring(cur_gno, fn, fp);
	    break;
	case BLOCK:
	    //csto retval = readblockdata(cur_gno, fn, fp);
	    break;
	}
    }
    if (src == PIPE) {
	pclose(fp);
    } else {
	if (fp != stdin) {	/* leave stdin open */
	    fclose(fp);
	}
    }
    //csto update_status_popup();
    return retval;
}

int getdata_step(int gno, char* fn, int src, int type)
{
    static FILE *fp;
    int retval;

    if (fp == NULL) {
	switch (src) {
	case DISK:
	    fp = fopen(fn, "r");
	    break;
	case PIPE:
	    fp = popen(fn, "r");
	    break;
	case 2:
	    fp = stdin;
	    break;
	case 3:
	    if (fp) {
		if (src == PIPE) {
		    pclose(fp);
		} else {
		    if (fp != stdin) {	/* leave stdin open */
			fclose(fp);
		    }
		}
	    }
	    fp = NULL;
	    return -1;
	    break;
	}
    }
    if (fp == NULL) {
	sprintf(buf, "Can't open file %s", fn);
	errwin(buf);
	fp = NULL;
	return 0;
    }
    cur_gno = gno;
    change_type = cur_type = type;
    retval = -1;
    while (retval == -1) {
	retval = 0;
	switch (cur_type) {
	case XY:
	    retval = readxy(cur_gno, fn, fp, 1);
	    break;
	case NXY:
	    //csto retval = readnxy(cur_gno, fn, fp);
	    break;
	case IHL:
	    //csto retval = readihl(cur_gno, fn, fp);
	    break;
	case BIN:
	    //csto retval = readbinary(cur_gno, fn, fp);
	    break;
	case XYDX:
	case XYDY:
	case XYDXDX:
	case XYDYDY:
	case XYDXDY:
	case XYZ:
	case XYRT:
	case XYHILO:
	case XYBOX:
	    //csto retval = readxxyy(cur_gno, fn, fp, cur_type);
	    break;
	case XYSTRING:
	    //csto retval = readxystring(cur_gno, fn, fp);
	    break;
	case 5:
	    //csto retval = readblockdata(cur_gno, fn, fp);
	    break;
	}
    }
    if (retval != -2) {		/* means it returned because a single set was
				 * read */
	if (src == PIPE) {
	    pclose(fp);
	} else {
	    if (fp != stdin) {	/* leave stdin open */
		fclose(fp);
	    }
	}
    }
    return retval;
}


/*
 * read file type 0
 */
int readxy(int gno, char *fn, FILE *fp, int readone)
{
    int i = 0, j, pstat, readset = 0, ptype, retval = 0;
    double *x, *y;
    
    printf("readxy %i %s %i %i \n",gno,fn,fp,readone);

    x = (double *) calloc(BUFSIZE, sizeof(double));
    y = (double *) calloc(BUFSIZE, sizeof(double));
    if (x == NULL || y == NULL) {
	errwin("Insufficient memory for set");
	cxfree(x);
	cxfree(y);
	return (0);
    }
    while (fgets(buf, MAX_LINE_LEN, fp) != NULL) {

      if (buf[0] == '#') {
	    continue;
	}
	if (buf[0] == '@') {
	    change_gno = -1;
	    change_type = cur_type;
	    read_param(buf + 1);
	    if (change_gno >= 0) {
		cur_gno = gno = change_gno;
	    }
	    if (change_type != cur_type) {
		cur_type = change_type;
		retval = -1;
		break;		/* exit this module and store any set */
	    }
	    continue;
	}
	
	convertchar(buf);  // replaces  ',' with ' ' and  'd', 'D' with 'e'
	
	/* count the number of items scanned */
	if ((pstat = sscanf(buf, "%lf %lf", &x[i], &y[i])) >= 1) {
	    /* supply x if missing (y winds up in x) */
	    if (pstat == 1) {
		y[i] = x[i];
		x[i] = i;
	    }
	    if (realtime == 1 && inwin) {
		//drawpolysym(&x[i], &y[i], 1, 3, 0, 0, 1.0);
	    }
	    /* got x and y so increment */
	    i++;
	    if (i % BUFSIZE == 0) {
		x = (double *) realloc(x, (i + BUFSIZE) * sizeof(double));
		y = (double *) realloc(y, (i + BUFSIZE) * sizeof(double));
	    }
	} else {
	    if (i != 0) {
		if ((j = nextset(gno)) == -1) {
		    cxfree(x);
		    cxfree(y);
		    return (readset);
		}
		activateset(gno, j);
		settype(gno, j, XY);
		setcol(gno, x, j, i, 0);
		setcol(gno, y, j, i, 1);
		setcomment(gno, j, fn);
		updatesetminmax(gno, j);
		if (realtime == 2 && inwin) {
		    //drawsetxy(g[gno].p[j], j);
		}
		readset++;
	    } else {
		readerror++;
		if (readerror > 10) {
		    if (yesno("Lots of errors, abort?", "Press YES or NO", "YES", "NO")) {
			cxfree(x);
			cxfree(y);
			return (0);
		    } else {
			readerror = 0;
		    }
		}
	    }
	    i = 0;
	    x = (double *) calloc(BUFSIZE, sizeof(double));
	    y = (double *) calloc(BUFSIZE, sizeof(double));
	    if (x == NULL || y == NULL) {
		errwin("Insufficient memory for set");
		cxfree(x);
		cxfree(y);
		return (readset);
	    }
	    if (readone) {
		return (-2);
	    }
	}
    }
    //i = highest index
    
//     int k;
//     for (k=0; k<i; k++) {
//       printf("readxy xy %f %f\n",x[k],y[k]);
//     }
    
    if (i != 0) {		// found data in set; 
	if ((j = nextset(gno)) == -1) {
	    cxfree(x);
	    cxfree(y);
	    return (readset);
	}
	activateset(gno, j);
	settype(gno, j, XY);
	setcol(gno, x, j, i, 0);
	setcol(gno, y, j, i, 1);
	setcomment(gno, j, fn);
	updatesetminmax(gno, j);
	if (realtime == 2 && inwin) {
	    /*
	     * TODO ??? drawsetxy(g[gno].p[j]); 
	     */
	}
	readset++;
    } else {			// no data in set; 
	cxfree(x);
	cxfree(y);
    }
    if (retval == -1) {
	return retval;
    } else {
	return readset;
    }
}

/*
//  * read IHL format
//  */
// int readihl(int gno, char* fn, FILE *fp)
// {
//     int i, j, pstat, npts;
//     double *x, *y, tmp;
// 
//     i = 0;
//     pstat = 0;
//     if ((j = nextset(gno)) == -1) {
// 	return 0;
//     }
//     if (fgets(buf, MAX_LINE_LEN, fp) == NULL) {
// 	errwin("Can't read from file");
// 	killset(gno, j);
// 	return 0;
//     }
//     pstat = sscanf(buf, "%d", &npts);
//     if (npts == 0) {
// 	errwin("Number of points = 0");
// 	killset(gno, j);
// 	return 0;
//     }
//     activateset(gno, j);
//     settype(gno, j, XY);
//     setlength(gno, j, npts);
//     setcomment(gno, j, fn);
//     x = getx(gno, j);
//     y = gety(gno, j);
//     for (i = 0; i < npts; i++) {
// 	if (fgets(buf, MAX_LINE_LEN, fp) == NULL) {
// 	    errwin("Premature EOF");
// 	    updatesetminmax(gno, j);
// 	    return 1;
// 	}
// 	convertchar(buf);
// 	pstat = sscanf(buf, "%lf %lf %lf", &tmp, &x[i], &y[i]);
//     }
//     updatesetminmax(gno, j);
//     return 1;
// }
// 
// /*
//  * read x1 y1 y2 ... y30 formatted files
//  * note that the maximum number of sets is 30
//  */
// #define MAXSETN 30
// 
// int readnxy(int gno, char *fn, FILE * fp)
// {
//     int i, j, pstat, rcnt, cnt, scnt[MAXSETN], setn[MAXSETN], ptype, retval = 0;
//     double /* atof(), */ *x[MAXSETN], *y[MAXSETN], xval, yr[MAXSETN];
//     char *s, *strtok(), buf[1024], tmpbuf[1024];
//     int readerror = 0;
//     int do_restart = 0;
// 
// /* if more than one set of nxy data is in the file,
//  * leap to here after each is read - the goto is at the
//  * bottom of this module.
//  */
// restart:;
// 
//     i = 0;
//     pstat = 0;
//     cnt = 0;
//     while ((fgets(buf, MAX_LINE_LEN, fp) != NULL) && ((buf[0] == '#') || (buf[0] == '@'))) {
// 	if (buf[0] == '@') {
// 	    read_param(buf + 1);
// 	}
//     }
//     convertchar(buf);
// 
//     /*
//      * count the columns 
//      */
//     strcpy(tmpbuf, buf);
//     s = tmpbuf;
//     while ((s = strtok(s, " \t\n")) != NULL) {
// 	cnt++;
// 	s = NULL;
//     }
//     if (cnt > MAXPLOT) {
// 	errwin("Maximum number of columns exceeded, reading first 31");
// 	cnt = 31;
//     }
//     s = buf;
//     s = strtok(s, " \t\n");
//     if (s == NULL) {
// 	errwin("Read ended by a blank line at or near the beginning of file");
// 	return 0;
//     }
//     pstat = sscanf(s, "%lf", &xval);
//     if (pstat == 0) {
// 	errwin("Read ended, non-numeric found on line at or near beginning of file");
// 	return 0;
//     }
//     s = NULL;
//     for (j = 0; j < cnt - 1; j++) {
// 	s = strtok(s, " \t\n");
// 	if (s == NULL) {
// 	    yr[j] = 0.0;
// 	    errwin("Number of items in column incorrect");
// 	} else {
// 	    yr[j] = atof(s);
// 	}
// 	s = NULL;
//     }
//     if (cnt > 1) {
// 	for (i = 0; i < cnt - 1; i++) {
// 	    if ((setn[i] = nextset(gno)) == -1) {
// 		for (j = 0; j < i; j++) {
// 		    killset(gno, setn[j]);
// 		}
// 		return 0;
// 	    }
// 	    activateset(gno, setn[i]);
// 	    settype(gno, setn[i], XY);
// 	    x[i] = (double *) calloc(BUFSIZE, sizeof(double));
// 	    y[i] = (double *) calloc(BUFSIZE, sizeof(double));
// 	    if (x[i] == NULL || y[i] == NULL) {
// 		errwin("Insufficient memory for set");
// 		cxfree(x[i]);
// 		cxfree(y[i]);
// 		for (j = 0; j < i + 1; j++) {
// 		    killset(gno, setn[j]);
// 		}
// 		return (0);
// 	    }
// 	    *(x[i]) = xval;
// 	    *(y[i]) = yr[i];
// 	    scnt[i] = 1;
// 	}
// 	while (!do_restart && (fgets(buf, MAX_LINE_LEN, fp) != NULL)) {
// 	    if (buf[0] == '#') {
// 		continue;
// 	    }
// 	    if (buf[0] == '@') {
// 		change_gno = -1;
// 		change_type = cur_type;
// 		read_param(buf + 1);
// 		if (change_gno >= 0) {
// 		    cur_gno = gno = change_gno;
// 		}
// 		if (change_type != cur_type) {
// 		    cur_type = change_type;
// 		    retval = -1;
// 		    break;	/* exit this module and store any set */
// 		}
// 		continue;
// 	    }
// 	    convertchar(buf);
// 	    s = buf;
// 	    s = strtok(s, " \t\n");
// 	    if (s == NULL) {
// 		continue;
// 	    }
// /* check for set separator */
// 	    pstat = sscanf(s, "%lf", &xval);
// 	    if (pstat == 0) {
// 		do_restart = 1;
// 		continue;
// 	    } else {
// 		s = NULL;
// 		for (j = 0; j < cnt - 1; j++) {
// 		    s = strtok(s, " \t\n");
// 		    if (s == NULL) {
// 			yr[j] = 0.0;
// 			errwin("Number of items in column incorrect");
// 		    } else {
// 			yr[j] = atof(s);
// 		    }
// 		    s = NULL;
// 		}
// 		for (i = 0; i < cnt - 1; i++) {
// 		    *(x[i] + scnt[i]) = xval;
// 		    *(y[i] + scnt[i]) = yr[i];
// 		    scnt[i]++;
// 		    if (scnt[i] % BUFSIZE == 0) {
// 			x[i] = (double *) realloc(x[i], (scnt[i] + BUFSIZE) * sizeof(double));
// 			y[i] = (double *) realloc(y[i], (scnt[i] + BUFSIZE) * sizeof(double));
// 		    }
// 		}
// 	    }
// 	}
// 	for (i = 0; i < cnt - 1; i++) {
// 	    setcol(gno, x[i], setn[i], scnt[i], 0);
// 	    setcol(gno, y[i], setn[i], scnt[i], 1);
// 	    setcomment(gno, setn[i], fn);
// 	    updatesetminmax(gno, setn[i]);
// 	}
// 	if (!do_restart) {
// 	    if (retval == -1) {
// 		return retval;
// 	    } else {
// 		return 1;
// 	    }
// 	} else {
// 	    do_restart = 0;
// 	    goto restart;
// 	}
//     }
//     return 0;
// }
// 
// int readbinary(int gno, char* fn, FILE *fp)
// {
//     int i, j, type, setn, nsets = 0, npts, n;
//     double *x, *y;
//     float *xf, *yf;
// 
// /*
//     fread(&type, sizeof(int), 1, fp);
// */
//     fread(&nsets, sizeof(int), 1, fp);
//     if (nsets > g[gno].maxplot) {
// 	sprintf(buf, "Not enough sets: have %d, need %d", g[gno].maxplot, nsets);
// 	errwin(buf);
// 	return 0;
//     }
//     for (i = 0; i < nsets; i++) {
// 	fread(&npts, sizeof(int), 1, fp);
// 	x = (double *) calloc(npts, sizeof(double));
// 	if (x == NULL) {
// 	    errwin("Can't calloc in readbinary");
// 	    return 0;
// 	}
// 	y = (double *) calloc(npts, sizeof(double));
// 	if (y == NULL) {
// 	    errwin("Can't calloc in readbinary");
// 	    cxfree(x);
// 	    return 0;
// 	}
// 	xf = (float *) calloc(npts, sizeof(float));
// 	if (xf == NULL) {
// 	    errwin("Can't calloc in readbinary");
// 	    return 0;
// 	}
// 	yf = (float *) calloc(npts, sizeof(float));
// 	if (yf == NULL) {
// 	    errwin("Can't calloc in readbinary");
// 	    cxfree(xf);
// 	    return 0;
// 	}
// 	fread(xf, sizeof(float), npts, fp);
// 	fread(yf, sizeof(float), npts, fp);
// 	for (j = 0; j < npts; j++) {
// 	    x[j] = xf[j];
// 	    y[j] = yf[j];
// 	}
// 	cfree(xf);
// 	cfree(yf);
// 	if ((setn = nextset(gno)) == -1) {
// 	    cxfree(x);
// 	    cxfree(y);
// 	    return 0;
// 	}
// 	activateset(gno, setn);
// 	settype(gno, setn, XY);
// 	setcol(gno, x, setn, npts, 0);
// 	setcol(gno, y, setn, npts, 1);
// 	setcomment(gno, setn, fn);
// 	updatesetminmax(gno, setn);
//     }
//     return 1;
// }
// 
// int readxystring()
// {
// }
// 
// /*
//  * read file types using dx and/or dy
//  */
// int readxxyy(int gno, char *fn, FILE *fp, int type)
// {
//     int i = 0, j, pstat, readset = 0, ptype, retval = 0;
//     double *x, *y, *dx, *dy, *dz;
//     double xtmp, ytmp, dxtmp, dytmp, dztmp;
// 
//     x = y = dx = dy = dz = NULL;
//     x = (double *) calloc(BUFSIZE, sizeof(double));
//     y = (double *) calloc(BUFSIZE, sizeof(double));
//     switch (type) {
//     case XYZ:
//     case XYRT:
//     case XYDX:
//     case XYDY:
// 	dx = (double *) calloc(BUFSIZE, sizeof(double));
// 	break;
//     case XYDXDX:
//     case XYDYDY:
//     case XYDXDY:
//     case XYUV:
// 	dx = (double *) calloc(BUFSIZE, sizeof(double));
// 	dy = (double *) calloc(BUFSIZE, sizeof(double));
// 	break;
//     case XYHILO:
//     case XYBOX:
// 	dx = (double *) calloc(BUFSIZE, sizeof(double));
// 	dy = (double *) calloc(BUFSIZE, sizeof(double));
// 	dz = (double *) calloc(BUFSIZE, sizeof(double));
// 	break;
//     default:
// 	dx = (double *) calloc(BUFSIZE, sizeof(double));
// 	dy = (double *) calloc(BUFSIZE, sizeof(double));
// 	break;
//     }
//     if (x == NULL || y == NULL) {
// 	errwin("Insufficient memory for set");
// 	cxfree(x);
// 	cxfree(y);
// 	cxfree(dx);
// 	cxfree(dy);
// 	cxfree(dz);
// 	return (0);
//     }
//     while (fgets(buf, MAX_LINE_LEN, fp) != NULL) {
// 	if (buf[0] == '#') {
// 	    continue;
// 	}
// 	if (buf[0] == '@') {
// 	    change_gno = -1;
// 	    change_type = cur_type;
// 	    read_param(buf + 1);
// 	    if (change_gno >= 0) {
// 		cur_gno = gno = change_gno;
// 	    }
// 	    if (change_type != cur_type) {
// 		if (change_type != cur_type) {
// 		    cur_type = change_type;
// 		    retval = -1;
// 		    break;	/* exit this module and store any set */
// 		}
// 	    }
// 	    continue;
// 	}
// 	convertchar(buf);
// 	/* count the number of items scanned */
// 	if ((pstat = sscanf(buf, "%lf %lf %lf %lf %lf", &xtmp, &ytmp, &dxtmp, &dytmp, &dztmp)) >= 1) {
// 	    /* got x and y so increment */
// 	    x[i] = xtmp;
// 	    y[i] = ytmp;
// 	    if (type == XYDX || type == XYDY || type == XYZ || type == XYRT) {
// 		dx[i] = dxtmp;
// 	    } else if (type == XYHILO || type == XYBOX) {
// 		dx[i] = dxtmp;
// 		dy[i] = dytmp;
// 		dz[i] = dztmp;
// 	    } else {
// 		dx[i] = dxtmp;
// 		dy[i] = dytmp;
// 	    }
// 	    i++;
// 	    if (i % BUFSIZE == 0) {
// 		x = (double *) realloc(x, (i + BUFSIZE) * sizeof(double));
// 		y = (double *) realloc(y, (i + BUFSIZE) * sizeof(double));
// 		switch (type) {
// 		case XYDX:
// 		case XYDY:
// 		case XYZ:
// 		case XYRT:
// 		    dx = (double *) realloc(dx, (i + BUFSIZE) * sizeof(double));
// 		    break;
// 		case XYDXDX:
// 		case XYDYDY:
// 		case XYDXDY:
// 		case XYUV:
// 		    dx = (double *) realloc(dx, (i + BUFSIZE) * sizeof(double));
// 		    dy = (double *) realloc(dy, (i + BUFSIZE) * sizeof(double));
// 		    break;
// 		case XYHILO:
// 		case XYBOX:
// 		    dx = (double *) realloc(dx, (i + BUFSIZE) * sizeof(double));
// 		    dy = (double *) realloc(dy, (i + BUFSIZE) * sizeof(double));
// 		    dz = (double *) realloc(dz, (i + BUFSIZE) * sizeof(double));
// 		    break;
// 		default:
// 		    dx = (double *) realloc(dx, (i + BUFSIZE) * sizeof(double));
// 		    dy = (double *) realloc(dy, (i + BUFSIZE) * sizeof(double));
// 		    break;
// 		}
// 	    }
// 	} else {
// 	    if (i != 0) {
// 		if ((j = nextset(gno)) == -1) {
// 		    cxfree(x);
// 		    cxfree(y);
// 		    cxfree(dx);
// 		    cxfree(dy);
// 		    cxfree(dz);
// 		    return readset;
// 		}
// 		activateset(gno, j);
// 		settype(gno, j, type);
// 		setcol(gno, x, j, i, 0);
// 		setcol(gno, y, j, i, 1);
// 		setcol(gno, dx, j, i, 2);
// 		setcol(gno, dy, j, i, 3);
// 		setcol(gno, dz, j, i, 4);
// 		setcomment(gno, j, fn);
// 		updatesetminmax(gno, j);
// 		readset++;
// 	    } else {
// 		readerror++;
// 		if (readerror > 10) {
// 		    if (yesno("Lots of errors, abort?", "Press YES or NO", "YES", "NO")) {
// 			cxfree(x);
// 			cxfree(y);
// 			cxfree(dx);
// 			cxfree(dy);
// 			cxfree(dz);
// 			return (0);
// 		    } else {
// 			readerror = 0;
// 		    }
// 		}
// 	    }
// 	    i = 0;
// 	    x = (double *) calloc(BUFSIZE, sizeof(double));
// 	    y = (double *) calloc(BUFSIZE, sizeof(double));
// 	    switch (type) {
// 	    case XYDX:
// 	    case XYZ:
// 	    case XYRT:
// 	    case XYDY:
// 		dx = (double *) calloc(BUFSIZE, sizeof(double));
// 		break;
// 	    case XYDXDX:
// 	    case XYDYDY:
// 	    case XYDXDY:
// 	    case XYUV:
// 		dx = (double *) calloc(BUFSIZE, sizeof(double));
// 		dy = (double *) calloc(BUFSIZE, sizeof(double));
// 		break;
// 	    case XYHILO:
// 	    case XYBOX:
// 		dx = (double *) calloc(BUFSIZE, sizeof(double));
// 		dy = (double *) calloc(BUFSIZE, sizeof(double));
// 		dz = (double *) calloc(BUFSIZE, sizeof(double));
// 		break;
// 	    default:
// 		dx = (double *) calloc(BUFSIZE, sizeof(double));
// 		dy = (double *) calloc(BUFSIZE, sizeof(double));
// 		break;
// 	    }
// 	    if (x == NULL || y == NULL) {
// 		errwin("Insufficient memory for set");
// 		cxfree(x);
// 		cxfree(y);
// 		cxfree(dx);
// 		cxfree(dy);
// 		cxfree(dz);
// 		killset(gno, j);
// 		return (readset);
// 	    }
// 	}
//     }
//     if (i != 0) {
// 	if ((j = nextset(gno)) == -1) {
// 	    cxfree(x);
// 	    cxfree(y);
// 	    cxfree(dx);
// 	    cxfree(dy);
// 	    cxfree(dz);
// 	    return readset;
// 	}
// 	activateset(gno, j);
// 	settype(gno, j, type);
// 	setcol(gno, x, j, i, 0);
// 	setcol(gno, y, j, i, 1);
// 	setcol(gno, dx, j, i, 2);
// 	setcol(gno, dy, j, i, 3);
// 	setcol(gno, dz, j, i, 4);
// 	setcomment(gno, j, fn);
// 	updatesetminmax(gno, j);
// 	readset++;
//     } else {
// 	cxfree(x);
// 	cxfree(y);
// 	cxfree(dx);
// 	cxfree(dy);
// 	cxfree(dz);
//     }
//     if (retval == -1) {
// 	return retval;
//     } else {
// 	return readset;
//     }
// }
// 
// double *blockdata[MAXPLOT];
// int blocklen;
// int blockncols;
// 
// /*
//  * read block data
//  */
// int readblockdata(int gno, char *fn, FILE* fp)
// {
//     int i = 0, j, k, gotcol, ncols, pstat, readset = 0, ptype, retval = 0;
//     int first = 1, readerror = 0;
//     double *data[MAXPLOT]; /*, atof(); */
//     char tmpbuf[1024], *s, *strtok();
// 
//     i = 0;
//     pstat = 0;
//     while ((s = fgets(buf, MAX_LINE_LEN, fp)) != NULL) {
// 	if (buf[0] == '#') {
// 	    continue;
// 	}
// 	if (buf[0] == '@') {
// 	    read_param(buf + 1);
// 	    continue;
// 	}
// 	if (strlen(buf) > 1) {
// 	    convertchar(buf);
// 	    if (first) {	/* count the number of columns */
// 		ncols = 0;
// 		strcpy(tmpbuf, buf);
// 		s = tmpbuf;
// 		while (*s == ' ' || *s == '\t' || *s == '\n')
// 		    s++;
// 		while ((s = strtok(s, " \t\n")) != NULL) {
// 		    ncols++;
// 		    s = NULL;
// 		}
// 		if (ncols < 1 || ncols > MAXPLOT) {
// 		    errwin("Column count incorrect");
// 		    return 0;
// 		}
// 		for (j = 0; j < MAXPLOT; j++) {
// 		    cxfree(blockdata[j]);
// 		    blockdata[j] = (double *) NULL;
// 		}
// 		for (j = 0; j < ncols; j++) {
// 		    data[j] = (double *) calloc(BUFSIZE, sizeof(double));
// 		    if (data[j] == NULL) {
// 			errwin("Insufficient memory for block data");
// 			for (k = 0; k < j; k++) {
// 			    cxfree(data[k]);
// 			}
// 			return 0;
// 		    }
// 		}
// 		first = 0;
// 	    }
// 	    s = buf;
// 	    while (*s == ' ' || *s == '\t' || *s == '\n')
// 		s++;
// 	    for (j = 0; j < ncols; j++) {
// 		s = strtok(s, " \t\n");
// 		if (s == NULL) {
// 		    data[j][i] = 0.0;
// 		    errwin("Number of items in column incorrect");
// 		    readerror++;
// 		    if (readerror > 10) {
// 			if (yesno("Lots of errors, abort?", "Press YES or NO", "YES", "NO")) {
// 			    for (k = 0; k < ncols; k++) {
// 				cxfree(data[k]);
// 			    }
// 			    return (0);
// 			} else {
// 			    readerror = 0;
// 			}
// 		    }
// 		} else {
// 		    data[j][i] = atof(s);
// 		}
// 		s = NULL;
// 	    }
// 	    i++;
// 	    if (i % BUFSIZE == 0) {
// 		for (j = 0; j < ncols; j++) {
// 		    data[j] = (double *) realloc(data[j], (i + BUFSIZE) * sizeof(double));
// 		    if (data[j] == NULL) {
// 			errwin("Insufficient memory for block data");
// 			for (k = 0; k < j; k++) {
// 			    cxfree(data[k]);
// 			}
// 			return 0;
// 		    }
// 		}
// 	    }
// 	}
//     }
//     for (j = 0; j < ncols; j++) {
// 	blockdata[j] = data[j];
//     }
//     blocklen = i;
//     blockncols = ncols;
//     return 1;
// }
// 
// void create_set_fromblock(int gno, int type, char* cols)
// 
// {
//     int i;
//     int setno, graphno;
//     int d1, cx, cy, c1, c2, c3;
//     double *tx, *ty, *t2, *t3, *t4;
//     int nc, coli[MAXPLOT];
//     char *s, buf[256], *strtok();;
//     strcpy(buf, cols);
//     s = buf;
//     nc = 0;
//     while ((s = strtok(s, ":")) != NULL) {
// 	coli[nc] = atoi(s);
// 	coli[nc]--;
// 	nc++;
// 	s = NULL;
//     }
//     if (nc == 0) {
// 	errwin("No columns scanned in column string");
// 	return;
//     }
//     for (i = 0; i < nc; i++) {
// 	if (coli[i] < 0 || coli[i] >= blockncols) {
// 	    errwin("Incorrect column specification");
// 	    return;
// 	}
//     }
// 
//     cx = coli[0];
//     cy = coli[1];
//     if (cx >= blockncols) {
// 	errwin("Column for X exceeds the number of columns in block data");
// 	return;
//     }
//     if (cy >= blockncols) {
// 	errwin("Column for Y exceeds the number of columns in block data");
// 	return;
//     }
//     switch (type) {
//     case XY:
// 	break;
//     case XYRT:
//     case XYDX:
//     case XYDY:
//     case XYZ:
// 	c1 = coli[2];
// 	if (c1 >= blockncols) {
// 	    errwin("Column for E1 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	break;
//     case XYDXDX:
//     case XYDYDY:
//     case XYDXDY:
// 	c1 = coli[2];
// 	c2 = coli[3];
// 	if (c1 >= blockncols) {
// 	    errwin("Column for E1 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	if (c2 >= blockncols) {
// 	    errwin("Column for E2 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	break;
//     case XYHILO:
//     case XYBOX:
// 	c1 = coli[2];
// 	c2 = coli[3];
// 	c3 = coli[4];
// 	if (c1 >= blockncols) {
// 	    errwin("Column for E1 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	if (c2 >= blockncols) {
// 	    errwin("Column for E2 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	if (c3 >= blockncols) {
// 	    errwin("Column for E3 exceeds the number of columns in block data");
// 	    return;
// 	}
// 	break;
//     }
//     setno = -1;
//     graphno = -1;
// 
//     if (graphno == -1) {
// 	graphno = cg;
//     }
//     if (setno == -1) {
// 	setno = nextset(graphno);
//     }
//     if (setno == -1) {
// 	return;
//     }
//     if (g[graphno].active == OFF) {
// 	set_graph_active(graphno);
//     }
//     activateset(graphno, setno);
//     settype(graphno, setno, type);
// 
//     tx = (double *) calloc(blocklen, sizeof(double));
//     ty = (double *) calloc(blocklen, sizeof(double));
//     for (i = 0; i < blocklen; i++) {
// 	tx[i] = blockdata[cx][i];
// 	ty[i] = blockdata[cy][i];
//     }
//     setcol(graphno, tx, setno, blocklen, 0);
//     setcol(graphno, ty, setno, blocklen, 1);
// 
//     switch (type) {
//     case XY:
// 	sprintf(buf, "Cols %d %d", cx + 1, cy + 1);
// 	break;
//     case XYRT:
//     case XYDX:
//     case XYDY:
//     case XYZ:
// 	sprintf(buf, "Cols %d %d %d", cx + 1, cy + 1, c1 + 1);
// 	t2 = (double *) calloc(blocklen, sizeof(double));
// 	for (i = 0; i < blocklen; i++) {
// 	    t2[i] = blockdata[c1][i];
// 	}
// 	setcol(graphno, t2, setno, blocklen, 2);
// 	break;
//     case XYDXDX:
//     case XYDYDY:
//     case XYDXDY:
// 	sprintf(buf, "Cols %d %d %d %d", cx + 1, cy + 1, c1 + 1, c2 + 1);
// 	t2 = (double *) calloc(blocklen, sizeof(double));
// 	t3 = (double *) calloc(blocklen, sizeof(double));
// 	for (i = 0; i < blocklen; i++) {
// 	    t2[i] = blockdata[c1][i];
// 	    t3[i] = blockdata[c2][i];
// 	}
// 	setcol(graphno, t2, setno, blocklen, 2);
// 	setcol(graphno, t3, setno, blocklen, 3);
// 	break;
//     case XYHILO:
//     case XYBOX:
// 	sprintf(buf, "Cols %d %d %d %d %d", cx + 1, cy + 1, c1 + 1, c2 + 1, c3 + 1);
// 	t2 = (double *) calloc(blocklen, sizeof(double));
// 	t3 = (double *) calloc(blocklen, sizeof(double));
// 	t4 = (double *) calloc(blocklen, sizeof(double));
// 	for (i = 0; i < blocklen; i++) {
// 	    t2[i] = blockdata[c1][i];
// 	    t3[i] = blockdata[c2][i];
// 	    t4[i] = blockdata[c3][i];
// 	}
// 	setcol(graphno, t2, setno, blocklen, 2);
// 	setcol(graphno, t3, setno, blocklen, 3);
// 	setcol(graphno, t4, setno, blocklen, 4);
// 	break;
//     }
// 
//     setcomment(graphno, setno, buf);
//     updatesetminmax(graphno, setno);
//     update_status_popup();
//     drawgraph();
// }
