#ifndef ERRORS_H
#define ERRORS_H
#include <string>
#include <stdexcept>
// base: everything Git-Lite throws
struct GitLiteError : std::runtime_error {
   explicit GitLiteError(const std::string& msg) : std::runtime_error(msg) {} 
};

// One subclass per failure kind
struct EmptyStackError : GitLiteError {
    explicit EmptyStackError(const std::string& msg) : GitLiteError(msg) {}
};

#endif
