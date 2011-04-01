/*	SCCS Id: @(#)pcsys.c	3.4	2002/01/22		  */
/* NetHack may be freely redistributed.  See license for details. */

/*
 *  System related functions for OS/2, TOS, and Windows NT
 */

#define NEED_VARARGS
#include "hack.h"
#include "wintty.h"

#include <ctype.h>
#include <fcntl.h>
#include <process.h>

#ifdef __GO32__
#define P_WAIT		0
#define P_NOWAIT	1
#endif
#ifdef TOS
#include <osbind.h>
#endif

#if defined(WIN32)
void FDECL(nethack_exit,(int));
#else
#define nethack_exit exit
#endif
static void NDECL(msexit);


#ifdef WIN32CON
extern int GUILaunched;    /* from nttty.c */
#endif

#if defined(WIN32)

void
flushout()
{
	(void) fflush(stdout);
	return;
}

static const char *COMSPEC =
# ifdef TOS
"SHELL";
# else
"COMSPEC";
# endif

#define getcomspec() nh_getenv(COMSPEC)

# ifdef SHELL
int
dosh()
{
	extern char orgdir[];
	char *comspec;
# ifndef __GO32__
	int spawnstat;
# endif
	if ((comspec = getcomspec())) {
#  ifndef TOS	/* TOS has a variety of shells */
		suspend_nhwindows("To return to NetHack, enter \"exit\" at the system prompt.\n");
#  else
		suspend_nhwindows((char *)0);
#  endif /* TOS */
#  ifndef NOCWD_ASSUMPTIONS
		chdirx(orgdir, 0);
#  endif
#  ifdef __GO32__
		if (system(comspec) < 0) {  /* wsu@eecs.umich.edu */
#  else
		spawnstat = spawnl(P_WAIT, comspec, comspec, (char *)0);

		if ( spawnstat < 0) {
#  endif
			raw_printf("Can't spawn \"%s\"!", comspec);
			getreturn("to continue");
		}
#  ifdef TOS
/* Some shells (e.g. Gulam) turn the cursor off when they exit */
		if (iflags.BIOS)
			(void)Cursconf(1, -1);
#  endif
#  ifndef NOCWD_ASSUMPTIONS
		chdirx(hackdir, 0);
#  endif
		get_scr_size(); /* maybe the screen mode changed (TH) */
		resume_nhwindows();
	} else
		pline("Can't find %s.",COMSPEC);
	return 0;
}
# endif /* SHELL */

# ifdef TOS
#define comspec_exists() 1
# endif

#endif /* WIN32 */

/*
 * Add a backslash to any name not ending in /, \ or :	 There must
 * be room for the \
 */
void
append_slash(name)
char *name;
{
	char *ptr;

	if (!*name)
		return;
	ptr = name + (strlen(name) - 1);
	if (*ptr != '\\' && *ptr != '/' && *ptr != ':') {
		*++ptr = '\\';
		*++ptr = '\0';
	}
	return;
}

#ifdef WIN32
boolean getreturn_enabled;
#endif

void
getreturn(str)
const char *str;
{
#ifdef WIN32
	if (!getreturn_enabled) return;
#endif
#ifdef TOS
	msmsg("Hit <Return> %s.", str);
#else
	msmsg("Hit <Enter> %s.", str);
#endif
	while (Getchar() != '\n') ;
	return;
}

#ifndef WIN32CON
void
msmsg VA_DECL(const char *, fmt)
	VA_START(fmt);
	VA_INIT(fmt, const char *);
	Vprintf(fmt, VA_ARGS);
	flushout();
	VA_END();
	return;
}
#endif

/*
 * Follow the PATH, trying to fopen the file.
 */
#ifdef TOS
# ifdef __MINT__
#define PATHSEP ':'
# else
#define PATHSEP ','
# endif
#else
#define PATHSEP ';'
#endif

FILE *
fopenp(name, mode)
const char *name, *mode;
{
	char buf[BUFSIZ], *bp, *pp, lastch = 0;
	FILE *fp;

	/* Try the default directory first.  Then look along PATH.
	 */
	(void) strncpy(buf, name, BUFSIZ - 1);
	buf[BUFSIZ-1] = '\0';
	if ((fp = fopen(buf, mode)))
		return fp;
	else {
		int ccnt = 0;
		pp = getenv("PATH");
		while (pp && *pp) {
			bp = buf;
			while (*pp && *pp != PATHSEP) {
				lastch = *bp++ = *pp++;
				ccnt++;
			}
			if (lastch != '\\' && lastch != '/') {
				*bp++ = '\\';
				ccnt++;
			}
			(void) strncpy(bp, name, (BUFSIZ - ccnt) - 2);
			bp[BUFSIZ - ccnt - 1] = '\0';
			if ((fp = fopen(buf, mode)))
				return fp;
			if (*pp)
				pp++;
		}
	}
	return (FILE *)0;
}

#if defined(WIN32)
void nethack_exit(code)
int code;
{
	msexit();
	exit(code);
}

/* Chdir back to original directory
 */
#ifdef TOS
extern boolean run_from_desktop;	/* set in pcmain.c */
#endif

static void msexit()
{
#ifdef CHDIR
	extern char orgdir[];
#endif

	flushout();
#ifndef TOS
# ifndef WIN32
	enable_ctrlP(); 	/* in case this wasn't done */
# endif
#endif
#if defined(CHDIR) && !defined(NOCWD_ASSUMPTIONS)
	chdir(orgdir);		/* chdir, not chdirx */
	chdrive(orgdir);
#endif
#ifdef TOS
	if (run_from_desktop)
	    getreturn("to continue"); /* so the user can read the score list */
# ifdef TEXTCOLOR
	if (colors_changed)
		restore_colors();
# endif
#endif
#ifdef WIN32CON
	/* Only if we started from the GUI, not the command prompt,
	 * we need to get one last return, so the score board does
	 * not vanish instantly after being created.
	 * GUILaunched is defined and set in nttty.c.
	 */
	synch_cursor();
	if (GUILaunched) getreturn("to end");
	synch_cursor();
#endif
	return;
}
#endif /* WIN32 */
