/* $Id: getparms.c,v 1.6 91/12/08 15:34:38 pturner Exp Locker: pturner $
 *
 * Read a parameter file
 */
#include <stdio.h>
#include <string.h>
#include "globals.h"

static char readbuf[512];


void scanner(char *, double *, double *, int, double *, double *, double *, double *, int, int, int, int*); 


int getparms(int gno, char *plfile)
{
    int linecount = 0, icheck, ptype, errpos = 0, errcnt = 0;
    char s[256];
    FILE *pp;
    double a, b, c, d, x, y;

    if ((pp = fopen(plfile, "r")) == NULL) {
	sprintf(readbuf, "Can't open parameter file %s", plfile);
	errwin(readbuf);
	return 0;
    } else {
	errcnt = 0;
	while (fgets(readbuf, 511, pp) != NULL) {
	    linecount++;
	    if (readbuf[0] == '#') {
		continue;
	    }
	    if (strlen(readbuf) <= 1) {
		continue;
	    }
	    lowtoupper(readbuf);
	    if (debuglevel == 1) {
		printf(readbuf);
	    }
	    errpos = 0;
	    scanner(readbuf, &x, &y, 1, &a, &b, &c, &d, 1, 0, 0, &errpos);
	    if (errpos) {
		printf("Error at line %d: %s\n", linecount, readbuf);
		errcnt++;
		if (errcnt > 5) {
		    if (yesno("Lots of errors, abort?", "Press YES or NO", "YES", "NO")==1) {
			fclose(pp);
			return 0;
		    } else {
			errcnt = 0;
		    }
		}
	    }
	}
	fclose(pp);
    }
    return 1;
}

void read_param(char *pbuf)
{
    int icheck, ptype, errpos = 0;
    double a, b, c, d, x, y;

    if (pbuf[0] == '#') {
	return;
    }
    lowtoupper(pbuf);
    scanner(pbuf, &x, &y, 1, &a, &b, &c, &d, 1, 0, 0, &errpos);
}
