# cpp-backend-template

This is a small C++ backend template that uses CMake as build system, vcpkg as dependency manager, Crow as web framework and features Docker and Docker compose support.
It also provides already defined Microsoft-like formatting options with clang-format.

## Dependencies

To use this template you need:

- a C++ compiler (C++23 is used out of box, edit [CMake config](CMakeLists.txt) if you want to use a different standard)
- CMake (3.14.0 >=)
- vcpkg
- Docker
- clang-format (optional)
