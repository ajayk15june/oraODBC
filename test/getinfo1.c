/*      test following functions:                                  */
/*              SQLAllocHandle()                                   */
/*              SQLConnect()                                       */      
/*              SQLDisconnect()                                    */
/*              SQLFreeHandle()                                    */
/*              SQLSetEnvAttr()                                    */


#include <stdio.h>
#include <assert.h>
#ifdef WIN32
#include <windows.h>
#endif

#include <sql.h>
#include <sqlext.h>
#include "SQLGetInfoIn.h"
#include "test_defs.h"
#include <mem_functions.h>
#include <common.h>


int main()
{
    SQLUSMALLINT  result;
    SQLSMALLINT some_val;
    int i;
    
    GET_LOGIN_VARS();
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
    T_ASSERT3(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO,
	     userName, pswd, " login must exist on TWO_TASK database " );

    VERBOSE("connected to  database %s\n",twoTask);

    for(i=0; i< getInfoOptsSIZE; i++){
      VERBOSE("checking index=%d infotype=%d name=%s\n",i,getInfoOpts[i],
				sql_get_info_type(getInfoOpts[i]));
      rc = SQLGetInfo(ConHandle,getInfoOpts[i],(void*)&result,
		      sizeof(result),&some_val);
      assert(rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO);
    }
    result = 0;
    rc = SQLGetInfo(ConHandle,SQL_TXN_CAPABLE,&result,
		    sizeof(result),&some_val);
    T_ASSERT(result!=0, "Oops, doesnt report transactions correctly");

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
