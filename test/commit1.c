/*test function: SQLExecDirect  to insert a row into table 'some_types'*/
#include "test_defs.h"
#include <stdio.h>
#include <assert.h>
#ifdef WIN32
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>



int main()
{
    // Declare The Local Memory Variables
    #define MAX_LEN 100
    SQLRETURN   rc = SQL_SUCCESS;
    SQLCHAR     twoTask[MAX_LEN];
    SQLCHAR     *userName = "scott";
    SQLCHAR     *pswd = "tiger";
    SQLHANDLE    EnvHandle;
    SQLHANDLE    ConHandle;
    HSTMT    StmtHandle;
    SQLCHAR  SQLStmt[255];
    
    if(getenv("TWO_TASK") && strlen((const char*)getenv("TWO_TASK"))<MAX_LEN)
      sprintf(twoTask,"%s",getenv("TWO_TASK"));
    else{
      fprintf(stderr,"Error: TWO_TASK env variable must be set\n");
      exit(-1);
    }
      
    VERBOSE("calling SQLAllocHandle(EnvHandle) \n");

    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &EnvHandle);
    assert(rc == SQL_SUCCESS);
    assert(EnvHandle != (SQLHANDLE)NULL);


   
    rc = SQLSetEnvAttr(EnvHandle, SQL_ATTR_ODBC_VERSION, 
		       (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_UINTEGER);

    assert(rc == SQL_SUCCESS);
        
    VERBOSE("calling SQLAllocHandle(ConHandle) \n");

    rc = SQLAllocHandle(SQL_HANDLE_DBC, EnvHandle, &ConHandle);
    assert(ConHandle != (SQLHANDLE)NULL);
    assert(rc == SQL_SUCCESS);
   
    rc = SQLConnect(ConHandle, twoTask, SQL_NTS, 
		    (SQLCHAR *)userName , SQL_NTS, (SQLCHAR *) pswd, SQL_NTS);
    assert(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO );

    VERBOSE("connected to  database %s\n",twoTask);

   

    rc = SQLAllocStmt(ConHandle, &StmtHandle);
    assert(rc == SQL_SUCCESS);

 
    sprintf(SQLStmt,"insert into some_numeric_types values( ");
    strcat(SQLStmt," 2,2,2,2.0,2.0,2.0,2.0,2.0 ) ");
    
    rc = SQLExecDirect(StmtHandle, SQLStmt, SQL_NTS);
    VERBOSE("executing statement: %s \n", SQLStmt);

    assert(rc == SQL_SUCCESS);
    VERBOSE("success: executed statement\n");


    VERBOSE("WELL!!! rolling it back anyway\n");
    rc = SQLEndTran(SQL_HANDLE_DBC, ConHandle, SQL_COMMIT);
    assert(rc == SQL_SUCCESS);


    VERBOSE("calling SQLFreeStmt\n");
    if (StmtHandle != NULL)
      rc=SQLFreeStmt(StmtHandle, SQL_DROP);
    assert(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO);





    rc = SQLDisconnect(ConHandle);
    assert(rc == SQL_SUCCESS);
    VERBOSE("disconnected from  database\n");
    

    VERBOSE("calling SQLFreeHandle(ConHandle) \n");

    assert (ConHandle != (SQLHANDLE)NULL);
    rc = SQLFreeHandle(SQL_HANDLE_DBC, ConHandle);
    assert(rc == SQL_SUCCESS);
   
    VERBOSE("calling SQLFreeHandle(EnvHandle) \n");

    assert (EnvHandle != (SQLHANDLE)NULL);
    rc = SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
    assert(rc == SQL_SUCCESS);
   

    return(rc);
}