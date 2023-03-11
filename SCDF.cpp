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
/// @date 11/03/2023

#include "SCDF.h"

namespace Fenyx
{

SCDFFile::SCDFFile()
{
    for(auto i = data.begin(); i != data.end(); i = i++) i->second.clear();

    data.clear();
    params = "TCF";
}


bool SCDFFile::Read(std::string filen, bool &syntax)
{
    std::ifstream file(filen);
    std::string l = "";
    std::string a_cat = "";
    std::cmatch mt;
    uint32_t n = 2;

    auto Parse_kv = [](std::string L, std::string &k, std::string &v) -> void {
        std::stringstream sstr(L);

        getline(sstr, k, '=');
        getline(sstr, v, '=');

        k.erase(std::remove_if(k.begin(), k.end(), isspace), k.end());
        v.erase(std::remove_if(v.begin(), v.end(), isspace), v.end());
    };

    for(auto i = data.begin(); i != data.end(); i = i++) i->second.clear();
    data.clear();

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
                std::string K = "", V = "";

                Parse_kv(l, K, V);

                data[a_cat][K].first  = false;
                data[a_cat][K].second = V;
            }
            else if(params.at(2) == 'F' && std::regex_match(l, keys_tF))
            {
                std::string K = "", V = "";

                Parse_kv(l, K, V);

                data[a_cat][K].first  = false;
                data[a_cat][K].second = V;
            }
            else if(params.at(0) == 'T' && params.at(2) == 'f' && std::regex_match(l, keys_Tf))
            {
                std::string K = "", V = "";

                Parse_kv(l, K, V);

                data[a_cat][K].first  = true;
                data[a_cat][K].second = V;
            }
            else if(params.at(0) == 'T' && params.at(2) == 'F' && std::regex_match(l, keys_TF))
            {
                std::string K = "", V = "";

                Parse_kv(l, K, V);

                data[a_cat][K].first  = true;
                data[a_cat][K].second = V;
            }
            else if(std::regex_match(l, com_scdf)) continue;
            else
            {
                syntax = false; file.close();
                return false;
            }
        }
    }
    else return false;

    file.close();

    return true;
}

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
            t_tab[p].erase(std::remove_if(t_tab[p].begin(), t_tab[p].end(), isspace), t_tab[p].end());

            d = t_tab[p];
        }
        else return false;
    }
    else return false;

    return true;
}

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
            t_str.erase(0, 1);
            t_str.erase(std::prev(t_str.end()));

            std::stringstream sstr(t_str);
            std::string str_t;
            while (getline(sstr, str_t, ',')) t_tab.push_back(str_t);

            s = t_tab.size();
        }
        else return false;
    }
    else return false;

    return true;
}

bool SCDFFile::SetData(std::string g, std::string k, std::string d)
{
    if(std::regex_match(d, d_tab))
    {
        data[g][k].first = true;
        if(params.at(0) == 't') params.replace(0, 1, "T");
    }
    else if (std::regex_match(d, d_val)) data[g][k].first = false;
    else return false;

    data[g][k].second = d;

    return true;
}

bool SCDFFile::IsExistG(std::string g)
{
    return FindGrp(g);
}

bool SCDFFile::IsExistK(std::string g, std::string k)
{
    return FindKey(g, k);
}


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
