#ifndef OUTOFRANGEEXEPTION_H
#define OUTOFRANGEEXEPTION_H

#include <exception>
#include <iostream>

using namespace std;
class OutOfRangeException : public exception {
    string m_err;
public:
    OutOfRangeException();

    const char* what() const noexcept override;
};

#endif // !OUTOFRANGEEXEPTION_H
