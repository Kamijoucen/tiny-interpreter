
#ifndef LLANGUAGE_ENVIRONMENT_H
#define LLANGUAGE_ENVIRONMENT_H

#include <string>
#include <map>
#include "value.h"

namespace lr
{

    class GlobalEnvironment;

    class Environment
    {
    public:
        ValuePtr get() const;

        void     put(std::string key, ValuePtr val);
    protected:
        std::map<std::string, ValuePtr> envs;
    };


    class GlobalEnvironment : public Environment
    {

    };

}


#endif //LLANGUAGE_ENVIRONMENT_H
