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
/// @return [true] si la lecture a réussi, [false] sinon.
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

/// @brief GetData - Récupères la valeur contenue g/k
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
            std::string t_str;
            t_tab.clear();

            t_str = data[g][k].second;
            t_str.erase(0, 1); t_str.erase(std::prev(t_str.end()));

            std::stringstream sstr(t_str);
            std::string str_t;
            while (getline(sstr, str_t, ',')) t_tab.push_back(str_t);

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
            std::string t_str;
            t_tab.clear();

            t_str = data[g][k].second;
            t_str.erase(0, 1); t_str.erase(std::prev(t_str.end()));

            std::stringstream sstr(t_str);
            std::string str_t;
            while(getline(sstr, str_t, ',')) t_tab.push_back(str_t);

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

/// @brief Validate - Vérifie sir le fichier chargé possède une structure définie
///
/// @param validr: Structure définie
///
/// @return [true] si la structure du fichier est ok, [false] sinon.
///
/// [validr] est une unordered_map entre le nom d'un groupe, et une autre unordered_map (entre le nom de la clé et le type de valeur).
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

}

