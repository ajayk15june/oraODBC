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
 * $Id: SQLNumResultCols.c,v 1.1 2002/02/11 19:48:07 dbox Exp $
 *
 * $Log: SQLNumResultCols.c,v $
 * Revision 1.1  2002/02/11 19:48:07  dbox
 * Initial revision
 *
 * Revision 1.10  2000/07/21 10:12:55  tom
 * casting made explicit
 *
 * Revision 1.9  2000/05/17 15:20:01  tom
 * Tracing improved
 *
 * Revision 1.8  2000/05/08 16:21:00  tom
 * General tidyness mods and clean up
 *
 * Revision 1.7  2000/05/04 14:56:31  tom
 * diagnostics now cleared down (almost) properly
 * local functions renamed to make clashes less likely
 *
 * Revision 1.6  2000/05/03 16:00:02  tom
 * initial tracing implementation
 *
 * Revision 1.5  2000/05/02 14:29:01  tom
 * initial thread safety measures
 *
 * Revision 1.4  2000/04/26 15:31:49  tom
 * Changed to account for new handle definitions
 *
 * Revision 1.3  2000/04/20 10:50:31  nick
 * Add to CVS and tidy up
 *
 * Revision 1.2  2000/04/19 15:28:07  tom
 * First Functional Checkin
 *
 * Revision 1.1  2000/04/13 11:44:22  tom
 * Added files
 *
 ******************************************************************************/

#include "common.h"

static char const rcsid[]= "$RCSfile: SQLNumResultCols.c,v $ $Revision: 1.1 $";

SQLRETURN SQL_API SQLNumResultCols(
    SQLHSTMT        StatementHandle,
    SQLSMALLINT        *ColumnCountPtr )
{
    hStmt_T *stmt=(hStmt_T*)StatementHandle;
    if(!stmt||HANDLE_TYPE(stmt)!=SQL_HANDLE_STMT)
        return SQL_INVALID_HANDLE;
#ifdef ENABLE_TRACE
    ood_log_message(stmt->dbc,__FILE__,__LINE__,TRACE_FUNCTION_ENTRY,
            (SQLHANDLE)stmt,0,"");
#endif
    ood_clear_diag((hgeneric*)stmt);
    ood_mutex_lock_stmt(stmt);
    *ColumnCountPtr=(SQLSMALLINT)stmt->current_ir->num_recs;
    ood_mutex_unlock_stmt(stmt);
#ifdef ENABLE_TRACE
    ood_log_message(stmt->dbc,__FILE__,__LINE__,TRACE_FUNCTION_EXIT,
            (SQLHANDLE)NULL,SQL_SUCCESS,"i",
			"*ColumnCountPtr",*ColumnCountPtr);
#endif
    fprintf(stderr,"called stubbed function\n",__LINE__,__FILE__);
    return SQL_SUCCESS;
}
