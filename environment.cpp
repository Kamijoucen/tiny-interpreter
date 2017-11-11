
#include "environment.h"

namespace lr
{



    void Environment::put(std::string key, ValuePtr val)
    {
        envs.insert({key, val});
    }

    ValuePtr Environment::get() const
    {
        return lr::ValuePtr();
    }

}