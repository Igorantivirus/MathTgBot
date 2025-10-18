#pragma once

#define SQL_GENERATE_TABLE ("CREATE TABLE IF NOT EXISTS USERS ("\
                            "ID            INTEGER PRIMARY KEY NOT NULL, "\
                            "NUMBER_TYPE   INT                 NOT NULL, "\
                            "NANGLE_TYPE   INT                 NOT NULL, "\
                            "PRECESSION    INT                 NOT NULL"\
                            ");")

#define SELECT_BY_ID      "SELECT * FROM USERS WHERE ID = ?;"
#define INSERT_USER       "INSERT INTO USERS (ID, NUMBER_TYPE, NANGLE_TYPE, PRECESSION) VALUES (?, ?, ?, ?);"
#define UPDATE_PRECESSION "UPDATE USERS SET PRECESSION = ? WHERE ID = ?;"
#define UPDATE_NUMBER     "UPDATE USERS SET NUMBER_TYPE = ? WHERE ID = ?;"
#define UPDATE_ANGLE      "UPDATE USERS SET NANGLE_TYPE = ? WHERE ID = ?;"
