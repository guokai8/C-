/***** eprintf.h **************************************************
 * Description: Header file for eprintf, which provides error-
 *              handling capabilities.
 * Author: Bernhard Haubold, bernhard.haubold@fh-weihenstephan.de
 * File created on Fri Dec 17 11:16:37 2004.
 *****************************************************************/
#include <stdio.h>
extern FILE *efopen(char *fname, char *mode); 
extern void eprintf(char *, ...);
extern char *estrdup (char *);
extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern char *progname(void);
extern void setprogname2(char *);
