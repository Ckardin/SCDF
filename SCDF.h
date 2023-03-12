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
#include <iostream>

namespace Fenyx
{

const std::regex beg_scdf("^-[tT][cC][fF]$", std::regex::optimize | std::regex::extended);
const std::regex cat_scdf("^[\{][a-zA-Z]{1}[a-zA-Z_]*[}]$", std::regex::optimize | std::regex::extended);
const std::regex com_scdf("^;[ \t]*[0-9a-zA-Z*/+=*&%@!.,_-]*[ \t]*", std::regex::optimize | std::regex::extended);
const std::regex keys_tf("^[ \t]*[a-zA-Z]{1}[a-zA-Z_]*[ ]*=[ ]*'*[a-zA-Z0-9_]+'*[ \t]*$", std::regex::optimize | std::regex::extended);
const std::regex keys_Tf("^[ \t]*[a-zA-Z]{1}[a-zA-Z_]*[ ]*=[ ]*\[(?:'*[a-zA-Z0-9_]*'*, )*(?:'*[a-zA-Z0-9_]*'*){1}][ \t]*$", std::regex::optimize | std::regex::extended);
const std::regex keys_tF("^\t[a-zA-Z]{1}[a-zA-Z_]* = '*[a-zA-Z0-9_]+'*$", std::regex::optimize | std::regex::extended);
const std::regex keys_TF("^\t[a-zA-Z]{1}[a-zA-Z_]* = \[(?:'*[a-zA-Z0-9_]*'*, )*(?:'*[a-zA-Z0-9_]*'*){1}]$", std::regex::optimize | std::regex::extended);
const std::regex d_tab("^\[(?:'*[a-zA-Z0-9_]*'*, )*(?:'*[a-zA-Z0-9_]*'*){1}]$", std::regex::optimize | std::regex::extended);
const std::regex d_val("^'*[a-zA-Z0-9_]+'*$", std::regex::optimize | std::regex::extended);

std::string SCDFTabToS(std::vector<std::string> d_tab);

class SCDFFile
{
public:
    SCDFFile();

    bool Read(std::string filen, bool &syntax);
    bool Write(std::string filen);

    bool GetData(std::string g, std::string k, std::string &d);
    bool GetTData(std::string g, std::string k, std::string &d, uint32_t p);
    bool GetTSize(std::string g, std::string k, uint32_t &s);
    bool SetData(std::string g, std::string k, std::string d);

    bool IsExistG(std::string g);
    bool IsExistK(std::string g, std::string k);

    ~SCDFFile();

private:
    bool FindKey(std::string g, std::string k);
    bool FindGrp(std::string g);

    std::map<std::string, std::map<std::string, std::pair<bool, std::string>>> data;
    std::string params;
};

}

#endif // SCDF_H
