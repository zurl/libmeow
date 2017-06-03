//
// Created by 张程易 on 03/06/2017.
//

#ifndef MEOW_STRINGUTIL_H
#define MEOW_STRINGUTIL_H

#include<sstream>
namespace zcy {
    inline int stoi(const std::string &str) {
        std::istringstream is(str);
        int i;
        is >> i;
        return i;
    }

    inline std::string itos(int i) {
        std::ostringstream os;
        os << i;
        return os.str();
    }
}


#endif //MEOW_STRINGUTIL_H
