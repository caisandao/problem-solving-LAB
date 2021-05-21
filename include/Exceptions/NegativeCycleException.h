//
// Created by ASUS on 2021/5/21.
//

#ifndef GRAPHLIBRARY_NEGATIVECYCLEEXCEPTION_H
#define GRAPHLIBRARY_NEGATIVECYCLEEXCEPTION_H

#include <Exceptions/GLException.h>

class NegativeCycleException : public GLException {
public:
    NegativeCycleException(const std::string &s) : GLException(s) {

    };
    ~NegativeCycleException() = default;
};

#endif //GRAPHLIBRARY_NEGATIVECYCLEEXCEPTION_H
