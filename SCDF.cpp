/// English version
/*
Copyright (C) 2023 BOUCARD NICOLLE Jody

This file is part of LibSCDF.

LibSCDF is free library: you can redistribute it and/or modify it under the terms of the GNU General 
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

LibSCDF est une bibliothèque libre; vous pouvez la redistribuer ou la modifier suivant les termes de la GNU General 
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

/// @file SCDF.cpp
/// @brief Source de SCDF
/// @author F&nµx
/// @version 1.0
/// @date 17/06/2023

#include "SCDF.h"

namespace Fenyx
{

/// @brief TrimStr - Enlève les espaces en début/fin de string
///
/// @param str: string à traiter
///
/// @return Une chaine de caractères, avec les espaces de début/fin supprimés.
std::string TrimStr(std::string str)
{
    auto ltrim = [](std::string l_str) -> std::string {
        size_t s = l_str.find_first_not_of(Spaces);
        return (s == std::string::npos) ? "" : l_str.substr(s);
    };

    auto rtrim = [](std::string r_str) -> std::string {
        size_t s = r_str.find_last_not_of(Spaces);
        return (s == std::string::npos) ? "" : r_str.substr(0, s + 1);
    };

    return rtrim(ltrim(str));
}

/// @brief SCDFTabToS - Créer une représentation d'un vector, dans une string, pour SCDF data
///
/// @param d_tab: Tableau de données
///
/// @return Une chaine de caractères, sous forme de tableau SCDF.
std::string SCDFTabToS(std::vector<std::string> d_tab)
{
    std::string ret = "[";

    for(auto i = d_tab.begin(); i != d_tab.end(); i++)
    {
        ret += *i; 
        ret += ", ";
    }

    ret.erase(std::prev(ret.end())); ret.erase(std::prev(ret.end()));
    ret += "]";

    return ret;
}

/// @brief SCDFFile - Constructeur
///
/// Constructeur de la classe SCDFFile.
SCDFFile::SCDFFile()
{
    for(auto i = data.begin(); i != data.end(); i = i++) i->second.clear();

    data.clear();
    params = "TCF";
}

/// @brief Read - Lit un fichier .scdf
///
/// @param filen: Fichier à lire
/// @param syntax: [true] si syntax ok, [false] sinon
///
/// @return [true] si la lecture a réussi, [false] sinon.
///
/// /!\ Utilise des expressions régulières, fonction assez lente. Privilégiez une seule instance à la fois.
bool SCDFFile::Read(std::string filen, bool &syntax)
{
    std::string l = "";
    std::string a_cat = "";

    auto Parse_kv = [](std::string L, std::string &k, std::string &v) -> void {
        std::stringstream sstr(L);

        getline(sstr, k, '=');
        getline(sstr, v, '=');

        k = TrimStr(k);
        v = TrimStr(v);
    };

    for(auto i = data.begin(); i != data.end(); i = i++) i->second.clear();
    data.clear();

    std::ifstream file(filen + ".scdf");
    if(file.is_open())
    {
        getline(file, l);

        if(std::regex_match(l, beg_scdf))
        {
            l.erase(0, 1);
            params = l;
        }
        else
        {
            syntax = false; file.close();
            return false;
        }

        std::string K = "", V = "";

        while(getline(file, l))
        {
            if(std::regex_match(l, cat_scdf))
            {
                l.erase(0, 1); l.erase(std::prev(l.end()));
                data[l].clear();

                a_cat = l;
            }
            else if(params.at(2) == 'f' && std::regex_match(l, keys_tf))
            {
                Parse_kv(l, K, V);

                data[a_cat][K].first  = false;
                data[a_cat][K].second = V;
            }
            else if(params.at(2) == 'F' && std::regex_match(l, keys_tF))
            {
                Parse_kv(l, K, V);

                data[a_cat][K].first  = false;
                data[a_cat][K].second = V;
            }
            else if(params.at(0) == 'T' && params.at(2) == 'f' && std::regex_match(l, keys_Tf))
            {
                Parse_kv(l, K, V);

                data[a_cat][K].first  = true;
                data[a_cat][K].second = V;
            }
            else if(params.at(0) == 'T' && params.at(2) == 'F' && std::regex_match(l, keys_TF))
            {
                Parse_kv(l, K, V);

                data[a_cat][K].first  = true;
                data[a_cat][K].second = V;
            }
            else if(std::regex_match(l, com_scdf) || std::regex_match(l, std::regex("^$"))) continue;
            else
            {
                syntax = false; file.close();
                return false;
            }
        }
    }
    else return false;

    file.close();

    syntax = true;
    return true;
}

/// @brief Write - Écrit dans un fichier .scdf
///
/// @param filen: Nom du fichier
///
/// @return [true] si l'écriture a réussi, [false] sinon.
bool SCDFFile::Write(std::string filen)
{
    std::ofstream file(filen + ".scdf");

    if(file.is_open())
    {
        file << "-" << params <<std::endl;
        if(params.at(2) == 'F') file << "" <<std::endl;

        for(auto i = data.begin(); i != data.end(); i++)
        {
            file << "{" << i->first << "}" <<std::endl;

            for(auto j = i->second.begin(); j != i->second.end(); j++)
            {
                if(params.at(2) == 'F') file << "\t" << j->first << " = " << j->second.second <<std::endl;
                else                    file << j->first << "=" << j->second.second <<std::endl;
            }
        }
    }
    else return false;

    file.close();

    return true;
}

/// @brief GetData - Récupères la valeur contenue dans g/k
///
/// @param g: Groupe
/// @param k: Clé
/// @param d: Valeur de g/k
///
/// @return [true] si réussi, [false] sinon.
///
/// /!\ Ne permets pas de récupérer une valeur dans un tableau.
bool SCDFFile::GetData(std::string g, std::string k, std::string &d)
{
    if(FindGrp(g))
    {
        if(FindKey(g, k))
        {
            if(data[g][k].first && params.at(0) == 'T') return false;
            d = data[g][k].second;
        }
        else return false;
    }
    else return false;

    return true;
}

/// @brief GetTData - Récupères la valeur contenue dans g/k[p]
///
/// @param g: Groupe
/// @param k: Clé
/// @param d: Valeur de g/k[p]
/// @param p: Position de la valeur, dans le tableau k
///
/// @return [true] si réussi, [false] sinon.
///
/// /!\ Ne permets pas de récupérer une valeur simple.
bool SCDFFile::GetTData(std::string g, std::string k, std::string &d, uint32_t p)
{
    if(params.at(0) == 't') return false;

    if(FindGrp(g))
    {
        if(FindKey(g, k))
        {
            if(!data[g][k].first) return false;

            std::vector<std::string> t_tab;
            TDtoTab(g, k, t_tab);

            if(p >= t_tab.size()) return false;
            t_tab[p] = TrimStr(t_tab[p]);

            d = t_tab[p];
        }
        else return false;
    }
    else return false;

    return true;
}

/// @brief GetTSize - Récupères la taille du tableau g/k[]
///
/// @param g: Groupe
/// @param k: Clé
/// @param s: Taille du tableau g/k[]
///
/// @return [true] si réussi, [false] sinon.
///
/// Renvoie [false] si g/k n'est pas un tableau.
bool SCDFFile::GetTSize(std::string g, std::string k, uint32_t &s)
{
    if(params.at(0) == 't') return false;

    if(FindGrp(g))
    {
        if(FindKey(g, k))
        {
            if(!data[g][k].first) return false;

            std::vector<std::string> t_tab;
            TDtoTab(g, k, t_tab);

            s = t_tab.size();
        }
        else return false;
    }
    else return false;

    return true;
}

/// @brief SetData - Mets à jour la valeur de g/k
///
/// @param g: Groupe
/// @param k: Clé
/// @param d: Valeur à mettre dans g/k
///
/// @return [true] si réussi, [false] sinon.
///
/// Si d contient un tableau, alors g/k deviendra g/k[], et le cas échéant, le paramètre UseTabs sera activé.
bool SCDFFile::SetData(std::string g, std::string k, std::string d)
{
    if(std::regex_match(d, d_tab))
    {
        data[g][k].first = true;
        if(params.at(0) == 't') params.replace(0, 1, "T");
    }
    else if(std::regex_match(d, d_val)) data[g][k].first = false;
    else return false;

    data[g][k].second = d;

    return true;
}

/// @brief GetPValue - Récupères la valeur d'un paramètre
///
/// @param tparam: Nom du paramètre concerné
/// @param v: Valeur du paramètre
///
/// @return [true] si réussi, [false] sinon.
bool SCDFFile::GetPValue(std::string tparam, bool &v)
{
    if(tparam == "UseTabs")
    {
        v = (params.at(0) == 't') ? false : true;
    }
    else if(tparam == "UseColors")
    {
        v = (params.at(1) == 'c') ? false : true;
    }
    else if(tparam == "Formating")
    {
        v = (params.at(2) == 'f') ? false : true;
    }
    else
    {
        v = false;
        return false;
    }

    return true;
}

/// @brief SetPValue - Modifie la valeur d'un paramètre
///
/// @param tparam: Nom du paramètre concerné
/// @param v: [true] pour activer la paramètre, [false] pour le désactiver
///
/// @return [true] si réussi, [false] sinon.
bool SCDFFile::SetPValue(std::string tparam, bool v)
{
    uint8_t pos;
    std::string c;

    if(tparam == "UseTabs")
    {
        pos = 0; c = (v) ? "T" : "t";
    }
    else if(tparam == "UseColors")
    {
        pos = 1; c = (v) ? "C" : "c";
    }
    else if(tparam == "Formating")
    {
        pos = 2; c = (v) ? "F" : "f";
    }
    else return false;

    params.replace(pos, 1, c);

    return true;
}

/// @brief Validate - Vérifie si le fichier chargé possède une structure définie
///
/// @param validr: Structure définie
///
/// @return [true] si la structure du fichier est ok, [false] sinon.
///
/// [validr] est une unordered_map entre le nom d'un groupe, et une autre unordered_map qui entre le nom de la clé et le type de valeur.
bool SCDFFile::Validate(std::unordered_map<std::string, std::unordered_map<std::string, bool>> validr)
{
    for(auto itg = validr.begin(); itg != validr.end(); ++itg)
    {
        if(!FindGrp(itg->first)) return false;

        for(auto itk = itg->second.begin(); itk != itg->second.end(); ++itk)
        {
            if(!FindKey(itg->first, itk->first))                  return false;
            if(data[itg->first][itk->first].first != itk->second) return false;
        }
    }

    return true;
}

/// @brief IsExistG - Vérifie si un groupe existe dans les données
///
/// @param g: Groupe
///
/// @return [true] si g existe, [false] sinon.
bool SCDFFile::IsExistG(std::string g)
{
    return FindGrp(g);
}

/// @brief IsExistK - Vérifie si une clé existe dans les données, pour un groupe spécifique
///
/// @param g: Groupe
/// @param k: Clé
///
/// @return [true] si g/k existe, [false] sinon.
bool SCDFFile::IsExistK(std::string g, std::string k)
{
    return FindKey(g, k);
}

/// @brief SCDFFile - Destructeur
///
/// Destructeur de la classe SCDFFile.
SCDFFile::~SCDFFile()
{
    for(auto i = data.begin(); i != data.end(); i++) i->second.clear();

    data.clear();
    params = "";
}


bool SCDFFile::FindKey(std::string g, std::string k)
{
    if(FindGrp(g))
    {
        for(auto i = data[g].begin(); i != data[g].end(); i++)
        {
            if(i->first == k) return true;
        }
    }

    return false;
}

bool SCDFFile::FindGrp(std::string g)
{
    for(auto i = data.begin(); i != data.end(); i++)
    {
        if(i->first == g) return true;
    }

    return false;
}

void SCDFFile::TDtoTab(std::string g, std::string k, std::vector<std::string> &tmp_t)
{
    std::string t_str;
    tmp_t.clear();

    t_str = data[g][k].second;
    t_str.erase(0, 1); t_str.erase(std::prev(t_str.end()));

    std::stringstream sstr(t_str);
    std::string str_t;
    while(getline(sstr, str_t, ',')) tmp_t.push_back(str_t);
}

}

