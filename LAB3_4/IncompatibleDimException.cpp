#include "IncompatibleDimException.h"

IncompatibleDimException::IncompatibleDimException() : m_err("\nerror! bad size!\n") {};

const char* IncompatibleDimException::what() const noexcept {
	return m_err.c_str();
}
