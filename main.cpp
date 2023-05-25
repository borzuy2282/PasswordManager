#include "funcs.h"

/**
 * \brief Here is the main function of a project.
 * @return
 */


auto main() -> int{
    Application::initCategories();
    Password::create();
    std::cout << Application::categories["None"][0];

    return 0;
}