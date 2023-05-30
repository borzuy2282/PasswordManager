#include "funcs.h"

/**
 * \mainpage Here is an information about the project.
 * I am doing a project for PJC classes(C++, tbc).
 * At this project I need to create a password manager, which will be able to encrypt and decrypt the info which it accepts.
 * IMHO, it is the hardest part of it.
 * But I am sure, that it will be fun, at least.
 * Oh, and of course: Hello, Professor!
 */

auto main() -> int{
    Application::initCategories();
    Password::create();
    Application::printInfo();
    Application::changePassword();
    Application::printInfo();
    return 0;
}