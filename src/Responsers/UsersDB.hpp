#pragma once

#include <format>
#include <memory>
#include <string_view>
#include <fstream>

#include <sqlite3.h>

#include <ServiceLocator/ExternLog.hpp>

#include "MathWorker/StringConvert/ComplexStringConverter.hpp"
#include "SqlCommands.hpp"
#include "OutputSettings.hpp"

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
        void(std::ofstream{fileName.data()});//Создание файла
        if(openFile(fileName))
            return false;

        if(sqlite3_exec(DB_.get(), SQL_GENERATE_TABLE, nullptr, 0, &messageError_))
        {
            close();
            externLog::log(messageError_, LogLevel::Error);
            return false;
        }
        return true;
    }

    bool openFile(const std::string_view fileName)
    {
        sqlite3 *DB;
        if(sqlite3_open(fileName.data(), &DB))
            DB_.reset(DB);
        else
        {
            close();
            externLog::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
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
        if(!id || !isOpen())
            return OutputSettings{};
        sqlite3_stmt* stmt = nullptr;

        const char* sql = "SELECT * FROM USERS WHERE ID = ?;";

        if (sqlite3_prepare_v2(DB_.get(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            externLog::log(sqlite3_errmsg(DB_.get()), LogLevel::Error);
            return {};
        }
        // Привязываем параметр (подставляем значение вместо '?')
        sqlite3_bind_int64(stmt, 1, id);
        OutputSettings res;
        // Выполняем запрос
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
            externLog::log(std::format("No user with ID = {}", id), LogLevel::Error);
        sqlite3_finalize(stmt);
        return res;
    }

    bool addUserByID(const std::size_t id)
    {
        return false;
    }

private:

    struct SqlDataBaseDestroyer
    {
        void operator()(sqlite3* db)
        {
            sqlite3_close(db);
        }
    };

private:

    std::unique_ptr<sqlite3, SqlDataBaseDestroyer> DB_;
    char* messageError_;

};