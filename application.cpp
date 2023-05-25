#include "funcs.h"

std::map<std::string, std::vector<Password>> Application::categories;

void Application::initCategories() {
    categories.insert(std::make_pair("None", std::vector<Password>()));
}

void Application::addCategory() {
    std::string name;
    std::cout << "Please, pass me the name of the category you want to create: ";
    std::cin >> name;
    std::cin.ignore();
    if(categories.find(name) == categories.end()){
        categories.insert(std::make_pair(name, std::vector<Password>()));
        std::cout << "\nCategory was created!" << std::endl;
    }else{
        int input;
        std::cout << "\nThis name was already used, want to try again?" << std::endl;
        std::cout << "Type 1 if so"<<std::endl;
        std::cin >> input;
        std::cin.ignore();
        if(input == 1){
            addCategory();
            return;
        }
    }
}

void Application::addPassword(const std::string &category, const Password &password) {
    Application::categories[category].push_back(password);
}


