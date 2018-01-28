
#include "../include/innerscope.h"
#include <iostream>

namespace cen
{
    std::map<std::string, std::map<std::string, GlobalExprASTPtr>> FileScope::funTable;

    using FunMap = std::map<std::string, GlobalExprASTPtr>;


    void FileScope::putFunction(const std::string &filename, const std::string &key, GlobalExprASTPtr ast)
    {

        auto fileIter = funTable.find(filename);
        if (fileIter != funTable.end()) {
            fileIter->second.insert(std::pair<std::string, GlobalExprASTPtr>(key, std::move(ast)));
        } else {
            FunMap funMap;
            funMap.insert(std::pair<std::string, GlobalExprASTPtr>(key, std::move(ast)));
            funTable.insert(std::pair<std::string, FunMap>(filename, std::move(funMap)));
        }
    }

    GlobalExprASTPtr FileScope::getFunction(const std::string &filename, const std::string &key)
    {
        auto funIter = funTable.find(filename);
        if (funIter != funTable.end())
        {
            FunMap &map = funIter->second;
            auto tableIter = map.find(key);
            if (tableIter != map.end())
            {
                return tableIter->second;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

}
