#include <stdio.h>
#include <sqlite3.h>

#include "config.h"


static int callback_get_status(void *data, int argc, char **argv, char **azColName){
  int i;
  int* status = (int*)data;
  *status = atoi(argv[0]);
  return 0;
}

int
main (int argc, char *argv[])
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;
  int status = 0;
  char *config_file;

  if (argc == 1)
    config_file = CONFIG_FILE;
  else
    config_file = argv[1];

  rc = sqlite3_open(config_file, &db);
  if( rc )
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return(1);
  }
/*  else
  {
    fprintf(stdout, "Opened database successfully\n");
  }
*/
  /* Create SQL statement */
  sql = "CREATE TABLE IF NOT EXISTS info("
        "STATUS INT NOT NULL"
	");";

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
  fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
/*  else
  {
    fprintf(stdout, "Table created successfully\n");
  }
*/
  /* Create SQL statement */
  sql = "SELECT * from info";

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, callback_get_status, (void*)&status, &zErrMsg);
  if( rc != SQLITE_OK )
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
/*  else
  {
    fprintf(stdout, "Operation done successfully\n");
  }
*/
printf("STATUS = %i\n", status);
  sqlite3_close(db);
}
