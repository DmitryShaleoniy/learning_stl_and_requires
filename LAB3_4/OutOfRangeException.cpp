#include "OutOfRangeException.h"

OutOfRangeException::OutOfRangeException() : m_err("\nerror! your index is out of dimension\n") {}

const char* OutOfRangeException::what() const throw() {
    return m_err.c_str();
}
