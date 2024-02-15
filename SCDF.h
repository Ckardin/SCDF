/// English version
/*
Copyright (C) 2023 BOUCARD NICOLLE Jody

This file is part of LibSCDF.

LibSCDF is free software: you can redistribute it and/or modify it under the terms of the GNU General 
Public License as published by the Free Software Foundation, either version 3 of the License, or (at your 
option) any later version.

LibSCDF is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
General Public License for more details.

You should have received a copy of the GNU General Public License along with LibSCDF. If not, see 
<https://www.gnu.org/licenses/>.
*/

/// Version française
/*
Copyright (C) 2023 BOUCARD NICOLLE Jody

Ce fichier fait partie de LibSCDF.

LibSCDF est une bilbiothèque libre; vous pouvez la redistribuer ou la modifier suivant les termes de la GNU General 
Public License telle que publiée par la Free Software Foundation, soit la version 3 de la licence, soit (à votre 
gré) toute version ultérieure.

LibSCDF est distribuée dans l'espoir qu'elle sera utile, mais SANS AUCUNE GARANTIE; sans même la 
garantie tacite de QUALITÉ MARCHANDE ou d'ADÉQUATION À UN BUT PARTICULIER. Consultez la GNU 
General Public License pour plus de détails.

Vous devez avoir reçu une copie de la GNU General Public License en même temps que LibSCDF. Si ce n'est pas le cas, consultez 
<http://www.gnu.org/licenses>.
*/

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
/// @date 17/06/2023

#ifndef SCDF_H
#define SCDF_H

#include <unordered_map>
#include <regex>
#include <fstream>
#include <iostream>

namespace Fenyx
{

const std::regex beg_scdf("^-[tT][cC][fF]$", std::regex::optimize | std::regex::extended);
const std::regex cat_scdf("^[\{][a-zA-Z]{1}[a-zA-Z_]*[}]$", std::regex::optimize | std::regex::extended);
const std::regex com_scdf("^;[ \t]*[0-9a-zA-Zà-ż*/+=*&%@!.,_ -]*[ \t]*$", std::regex::optimize | std::regex::extended);
const std::regex keys_tf("^[ \t]*[a-zA-Z]{1}[a-zA-Z_]*[ ]*=[ ]*'*[a-zA-Zà-ż0-9_-]+'*[ \t]*$", std::regex::optimize | std::regex::extended);
const std::regex keys_Tf("^[ \t]*[a-zA-Z]{1}[a-zA-Z_]*[ ]*=[ ]*\[[a-zA-Zà-ż0-9_, -]*][ \t]*$", std::regex::optimize | std::regex::extended);
const std::regex keys_tF("^[ \t]+[a-zA-Z]{1}[a-zA-Z_]* = '*[a-zA-Zà-ż0-9_-]+'*$", std::regex::optimize | std::regex::extended);
const std::regex keys_TF("^[ \t]+[a-zA-Z]{1}[a-zA-Z_]* = \[[a-zA-Zà-ż0-9_, -]*]$", std::regex::optimize | std::regex::extended);
const std::regex d_tab("^\[[a-zA-Z0-9_, ]*]$", std::regex::optimize | std::regex::extended);
const std::regex d_val("^'*[a-zA-Z0-9_]+'*$", std::regex::optimize | std::regex::extended);
const std::string Spaces = " \n\r\t\f\v";

std::string TrimStr(std::string str);
std::string SCDFTabToS(std::vector<std::string> d_tab);

/// @brief SCDFFile - Classe qui permets de parser/écrire les fichiers .scdf
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

    bool GetPValue(std::string tparam, bool &v);
    bool SetPValue(std::string tparam, bool v = true);

    bool Validate(std::unordered_map<std::string, std::unordered_map<std::string, bool>> validr);

    bool IsExistG(std::string g);
    bool IsExistK(std::string g, std::string k);

    ~SCDFFile();

private:
    bool FindKey(std::string g, std::string k);
    bool FindGrp(std::string g);
    void TDtoTab(std::string g, std::string k, std::vector<std::string> &tmp_t);

    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<bool, std::string>>> data;
    std::string params;
};

}

#endif // SCDF_H
