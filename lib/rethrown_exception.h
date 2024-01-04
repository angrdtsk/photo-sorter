#ifndef RETHROWN_EXCEPTION_H
#define RETHROWN_EXCEPTION_H

#include <stdexcept>
#include <string>


class RethrownException : public std::runtime_error {
public:
    RethrownException(const std::string &message) : std::runtime_error(message) {}
};

#endif