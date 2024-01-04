#ifndef LOCAL_EXCEPTION_H
#define LOCAL_EXCEPTION_H

#include <stdexcept>
#include <string>


class LocalException : public std::runtime_error {
public:
    LocalException(const std::string &message) : std::runtime_error(message) {}
};

#endif