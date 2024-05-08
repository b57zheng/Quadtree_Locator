#include <iostream>

class Illegal_Exception : public std::exception {
public:
    const char* what () const noexcept override;
};