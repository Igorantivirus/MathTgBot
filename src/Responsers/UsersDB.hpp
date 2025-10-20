#pragma once

// #include <format>
#include <fstream>
#include <memory>
#include <string_view>

#include <sqlite3.h>

#include <ServiceLocator/ExternService.hpp>

#include "MathWorker/StringConvert/ComplexStringConverter.hpp"
#include "OutputSettings.hpp"
#include "SqlCommands.hpp"

class UsersDB
{
public:
    UsersDB() = default;
    UsersDB(const std::string_view fileName)
    {
        openFile(fileName);
    }

    bool createFile(const std::string_view fileName)
    {
        void(std::ofstream{fileName.data()});
        if (!openFile(fileName))
            return false;

        if (sqlite3_exec(DB_.get(), SQL_GENERATE_TABLE, nullptr, 0, &messageError_))
        {
            close();
            service::log(messageError_, LogLevel::Error);
            sqlite3_free(messageError_);
            return false;
        }
        return true;
    }

    bool openFile(const std::string_view fileName)
    {
        sqlite3 *DB;
        if (sqlite3_open(fileName.data(), &DB) == SQLITE_OK)
            DB_.reset(DB);
        else
        {
            close();
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
        }
        return static_cast<bool>(DB_.get());
    }

    void close()
    {
        DB_.reset();
    }

    bool isOpen() const
    {
        return static_cast<bool>(DB_.get());
    }

    OutputSettings getUserById(const std::size_t id)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (getUserById).", LogLevel::Error);
            return {};
        }
        sqlite3_stmt *stmt = nullptr;

        const char *sql = "SELECT * FROM USERS WHERE ID = ?;";

        if (sqlite3_prepare_v2(DB_.get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return {};
        }
        sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(id));
        OutputSettings res;
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int userId = sqlite3_column_int(stmt, 0);
            int numberType = sqlite3_column_int(stmt, 1);
            int nangleType = sqlite3_column_int(stmt, 2);
            int prec = sqlite3_column_int(stmt, 3);

            res.complexType = static_cast<mathWorker::ComplexOutputType>(numberType);
            res.angleType = static_cast<mathWorker::AngleOutputType>(nangleType);
            res.precession = static_cast<unsigned char>(prec);
        }
        else
            service::log(std::string("No user with ID = {}") + std::to_string(id), LogLevel::Warning);
        sqlite3_finalize(stmt);
        return res;
    }

    bool addUserByID(const std::size_t id, const OutputSettings &settings)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (addUserByID).", LogLevel::Error);
            return false;
        }

        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(DB_.get(), INSERT_USER, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }

        sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(id));
        sqlite3_bind_int(stmt, 2, static_cast<int>(settings.complexType));
        sqlite3_bind_int(stmt, 3, static_cast<int>(settings.angleType));
        sqlite3_bind_int(stmt, 4, static_cast<int>(settings.precession));

        const int rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }
        return true;
    }
    bool changeUserPrecession(const std::size_t id, const unsigned char precession)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (changeUserPrecession).", LogLevel::Error);
            return false;
        }
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(DB_.get(), UPDATE_PRECESSION, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }

        sqlite3_bind_int(stmt, 1, static_cast<int>(precession));
        sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));
        sqlite3_bind_int(stmt, 3, static_cast<int>(precession));

        const int rc = sqlite3_step(stmt);
        const bool changed = (rc == SQLITE_DONE) && sqlite3_changes(DB_.get()) > 0;
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }
        return changed;
    }
    bool addToPrecession(const std::size_t id, const unsigned char add)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (addToPrecession).", LogLevel::Error);
            return false;
        }

        sqlite3_stmt *stmt = nullptr;
        const char *sql = "UPDATE USERS SET PRECESSION = PRECESSION + ? WHERE ID = ?;";

        if (sqlite3_prepare_v2(DB_.get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }

        sqlite3_bind_int(stmt, 1, static_cast<int>(add));
        sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));

        const int rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }
        return true;
    }
    bool changeUserNumberType(const std::size_t id, const mathWorker::ComplexOutputType type)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (changeUserNumberType).", LogLevel::Error);
            return false;
        }
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(DB_.get(), UPDATE_NUMBER, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }

        sqlite3_bind_int(stmt, 1, static_cast<int>(type));
        sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));
        sqlite3_bind_int(stmt, 3, static_cast<int>(type));

        const int rc = sqlite3_step(stmt);
        const bool changed = (rc == SQLITE_DONE) && sqlite3_changes(DB_.get()) > 0;
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }
        return changed;
    }
    bool changeUserAngleType(const std::size_t id, const mathWorker::AngleOutputType type)
    {
        if (!id || !isOpen())
        {
            service::log("Trying to work with an empty file or empty id (changeUserAngleType).", LogLevel::Error);
            return false;
        }
        sqlite3_stmt *stmt = nullptr;
        const char *sql = UPDATE_ANGLE;

        if (sqlite3_prepare_v2(DB_.get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }

        sqlite3_bind_int(stmt, 1, static_cast<int>(type));
        sqlite3_bind_int64(stmt, 2, static_cast<sqlite3_int64>(id));
        sqlite3_bind_int(stmt, 3, static_cast<int>(type));

        const int rc = sqlite3_step(stmt);
        const bool changed = (rc == SQLITE_DONE) && sqlite3_changes(DB_.get()) > 0;
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            service::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return false;
        }
        return changed;
    }
    
private:
    struct SqlDataBaseDestroyer
    {
        void operator()(sqlite3 *db)
        {
            sqlite3_close(db);
        }
    };

private:
    std::unique_ptr<sqlite3, SqlDataBaseDestroyer> DB_;
    char *messageError_;
};
