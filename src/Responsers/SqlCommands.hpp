#pragma once

#define SQL_GENERATE_TABLE ("CREATE TABLE IF NOT EXISTS USERS ("\
                            "ID             INT PRIMARY KEY NOT NULL"\
                            "NUMBER_TYPE    INT             NOT NULL"\
                            "NANGLE_TYPE    INT             NOT NULL"\
                            "PRECESSION     INT             NOT NULL)")

#define SELECT_BY_ID "SELECT * FROM USERS WHERE ID = ?;"