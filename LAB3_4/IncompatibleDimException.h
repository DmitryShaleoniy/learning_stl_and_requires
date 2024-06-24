#ifndef INCOMPATIBLERANGEEXCEPTION_H
#define INCOMPATIBLERANGEEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;
class IncompatibleDimException : exception {
    string m_err;
public:
    IncompatibleDimException();

    const char* what() const noexcept override;
};

#endif