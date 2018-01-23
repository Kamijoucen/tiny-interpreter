
#include "../include/GlobalScope.h"

namespace cen
{
    std::map<std::string, ValuePtr> GlobalScope::vars;

    void GlobalScope::put(const std::string &name, ValuePtr val) {
    }

    ValuePtr GlobalScope::get(const std::string &name) {
        return cen::ValuePtr();
    }
}
