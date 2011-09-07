/* cleanup tables from other tests
 * author: Dennis Box, dbox@fnal.gov
 * $Id: cleanup.c,v 1.1 2005/11/21 23:51:34 dbox Exp $
 */

#include "test_defs.h"
#include <stdio.h>
#include <assert.h>
#ifdef WIN32
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>

char *cmds[] = { "drop table some_types",
	"drop table some_numeric_types",
	"drop table some_types2",
	"drop table int_table",
	"drop table float_table",
	"drop table date_table",
	"drop table some_char_types"
};

int main()
{
	int i;
	int sz = sizeof(cmds) / sizeof(*cmds);

	if (getenv("NO_CLEANUP"))
		return 0;

	GET_LOGIN_VARS();
	VERBOSE("calling SQLAllocHandle(EnvHandle) \n");

	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &EnvHandle);
	assert(rc == SQL_SUCCESS);
	assert(EnvHandle != (SQLHANDLE) NULL);

	rc = SQLSetEnvAttr(EnvHandle, SQL_ATTR_ODBC_VERSION,
			   (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_UINTEGER);

	assert(rc == SQL_SUCCESS);

	VERBOSE("calling SQLAllocHandle(ConHandle) \n");

	rc = SQLAllocHandle(SQL_HANDLE_DBC, EnvHandle, &ConHandle);
	assert(ConHandle != (SQLHANDLE) NULL);
	assert(rc == SQL_SUCCESS);

	if (dsn[0])
		rc = SQLDriverConnect(ConHandle, NULL, dsn,
				      SQL_NTS, NULL, 0, NULL,
				      SQL_DRIVER_NOPROMPT);
	else
		rc = SQLConnect(ConHandle, twoTask, SQL_NTS,
				(SQLCHAR *) userName, SQL_NTS, (SQLCHAR *) pswd,
				SQL_NTS);
	assert(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO);

	VERBOSE("connected to  database %s\n", twoTask);

	rc = SQLAllocStmt(ConHandle, &StmtHandle);
	assert(rc == SQL_SUCCESS);

	for (i = 0; i < sz; i++) {
		VERBOSE("executing statement: %s \n", cmds[i]);
		rc = SQLExecDirect(StmtHandle, cmds[i], SQL_NTS);
	}

	VERBOSE("calling SQLFreeStmt\n");
	if (StmtHandle != NULL)
		rc = SQLFreeHandle(SQL_HANDLE_STMT, StmtHandle);
	assert(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO);

	rc = SQLDisconnect(ConHandle);
	assert(rc == SQL_SUCCESS);
	VERBOSE("disconnected from  database\n");

	VERBOSE("calling SQLFreeHandle(ConHandle) \n");

	assert(ConHandle != (SQLHANDLE) NULL);
	rc = SQLFreeHandle(SQL_HANDLE_DBC, ConHandle);
	assert(rc == SQL_SUCCESS);

	VERBOSE("calling SQLFreeHandle(EnvHandle) \n");

	assert(EnvHandle != (SQLHANDLE) NULL);
	rc = SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
	assert(rc == SQL_SUCCESS);

	return (rc);
}