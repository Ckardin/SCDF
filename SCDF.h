/*
---------------------------------------------
|    ____                                   |
|   /\  _`\                                 |
|   \ \ \L\_\ __    ___   __  __   __  _    |
|    \ \  _\/'__`\/' _ `\/\ \/\ \ /\ \/'\   |
|     \ \ \/\  __//\ \/\ \ \ \_\ \\/>  </   |
|      \ \_\ \____\ \_\ \_\/`____ \/\_/\_\  |
|       \/_/\/____/\/_/\/_/`/___/> \//\/_/  |
|                             /\___/        |
|                             \/__/         |
|                                           |
---------------------------------------------
*/

/// @file SCDF.h
/// @brief Header de SCDF
/// @author F&nµx
/// @version 1.0
/// @date 11/03/2023

#ifndef SCDF_H
#define SCDF_H

#include <regex>
#include <fstream>

class SCDFFile
{
public:
    SCDFFile();

    bool Read(std::string filen);
    bool Write(std::string filen);

    bool GetData(std::string g, std::string k, std::string &d);
    bool SetData(std::string g, std::string k, std::string d);

    bool IsExistG(std::string g);
    bool IsExistK(std::string k);

    ~SCDFFile();

private:
    bool FindKey(std::string k);
    uint32_t next;

    std::map<uint32_t, std::pair<std::string, std::map<std::string, std::string>>> data;
};

#endif // SCDF_H
