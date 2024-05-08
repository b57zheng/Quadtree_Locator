#include "Illegal_Exception.hpp"

const char* Illegal_Exception::what () const noexcept {
        return "illegal argument";
}
