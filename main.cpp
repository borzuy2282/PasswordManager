#include "funcs.h"

/**
 * \brief Here is the main function of a project.
 * @return
 */


auto main() -> int{
    Application::initCategories();
    Password::create();
    Application::printInfo();
    Application::changePassword();
    Application::printInfo();
    return 0;
}