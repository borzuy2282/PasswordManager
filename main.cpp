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
    Application::logIn();
    bool working = true;
    std::cout << "Please, pass me a path to your file:\n";
    std::string path;
    std::getline(std::cin, path);
    Application::readOut(path);
    while(working){
        std::cout << "1 - search password\n2 - add password\n3 - edit password\n4 - delete password" << std::endl;
        std::cout << "5 - add category\n6 - delete category\n7 - print all data\n0 - exit" << std::endl;
        std::cout << "So, please give me a number:\n";
        int input;
        std::cin >> input;
        std::cin.ignore();
        switch(input){
            case 1:
                Application::search();
                break;
            case 2:
                Password::create();
                break;
            case 3:
                Application::changePassword();
                break;
            case 4:
                Application::deletePassword();
                break;
            case 5:
                Application::addCategory();
                break;
            case 6:
                Application::deleteCategory();
                break;
            case 7:
                Application::printInfo();
                break;
            case 0:
                working = false;
                break;
            default:
                std::cout << "Try use right keys!\n";
        }
    }
    std::cout << "Please, pass me a path to your file:\n";
    std::getline(std::cin, path);
    Application::writeIn(path);
    std::cout << "See you next time!";
    return 0;
}