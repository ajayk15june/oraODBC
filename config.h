/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if lex declares yytext as a char * by default, not a char[].  */
#define YYTEXT_POINTER 1

/*******************************************************************************
 *
 * Copyright (c) 2000 Easysoft Ltd
 *
 * The contents of this file are subject to the Easysoft Public License 
 * Version 1.0 (the "License"); you may not use this file except in compliance 
 * with the License. 
 *
 * You may obtain a copy of the License at http://www.easysoft.org/EPL.html 
 *
 * Software distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for 
 * the specific language governing rights and limitations under the License. 
 *
 * The Original Code was created by Easysoft Limited and its successors. 
 *
 * Contributor(s): Tom Fosdick (Easysoft) 
 *
 *******************************************************************************
 *
 * $Id: config.h,v 1.1 2002/02/11 19:48:06 dbox Exp $
 *
 * $Log: config.h,v $
 * Revision 1.1  2002/02/11 19:48:06  dbox
 * Initial revision
 *
 * Revision 1.5  2000/07/07 07:47:56  tom
 * Changes for user catalog
 *
 * Revision 1.4  2000/06/05 15:48:34  tom
 * Fix for oratypes for Linux (to get ub8 type)
 *
 * Revision 1.3  2000/05/16 08:59:38  tom
 * More library version tweaks
 *
 * Revision 1.2  2000/05/16 07:54:09  tom
 * Library version fixes
 *
 * Revision 1.1  2000/05/03 16:00:23  tom
 * Init Ver
 *
 *
 ******************************************************************************/
/*
 * User catalog
 */
/* #undef ENABLE_USER_CATALOG */
/*
 * Tracing
 */
/* #undef ENABLE_TRACE */
/*
 * Symbol hack
 */
/* #undef EXPORT_SLPMPRODSTAB */
/*
 * libclntsh.so version switching
 */
#define LIBCLNTSH8 1
/*
 * There is an oddity in oratypes.h; it expects LINUX to be
 * defined on linux systems... but most compilers define 
 * __linux__
 */
#if defined (__linux__) || defined (__linux) && !defined(LINUX)
#define LINUX 1
#endif

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the pthread library (-lpthread).  */
#define HAVE_LIBPTHREAD 1

/* Name of package */
#define PACKAGE "oracle"

/* Version number of package */
#define VERSION "0.4.0pre1"

