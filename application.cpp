#include "funcs.h"

std::map<std::string, std::vector<Password>> Application::categories;
std::string Application::mainPassword = "qwerty123";
char Application::key = 'B';

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

    if(categories.find(category) != categories.end()) {
        Application::categories[category].push_back(password);
    }else{
        Application::categories["None"].push_back(password);

    }
}

void Application::changePassword() {
    std::cout << "Please, provide me a name of the password that you want to change." << std::endl;
    std::string inputStr;
    int inputInt;
    std::getline(std::cin, inputStr);
    bool flag = true;
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            if(itr->second[i].getName() == inputStr){
                std::cout << "We've found it! Now, tell me what do you want to change." << std::endl;
                std::cout << "Do you want to change the name? 1 - yes\n";
                std::cin >> inputInt;
                std::cin.ignore();
                if(inputInt == 1){
                    std::cout << "Please, provide a new one:\n";
                    std::getline(std::cin, inputStr);
                    if(inputStr.empty()){
                        std::cout << "There is no time for jokes, please next time provide normally.\n";
                    }else {
                        flag = true;
                        for (auto it = Application::categories.begin(); it != Application::categories.end(); it++) {
                            for (int i = 0; i < it->second.size(); i++) {
                                if (it->second[i].getName() == inputStr) {
                                    flag = false;
                                    break;
                                }
                            }
                            if (!flag) {
                                break;
                            }
                        }
                        if(!flag){
                            std::cout << "There was already a password like that, please, next time check more carefully." << std::endl;
                        }else {
                            itr->second[i].setName(inputStr);
                        }
                    }
                }
                std::cout << "Do you want to change the password? 1 - yes\n";
                std::cin >> inputInt;
                std::cin.ignore();
                if(inputInt == 1){
                    std::cout << "Maybe you want to generate a new one? 1 - yes\n";
                    std::cin >> inputInt;
                    std::cin.ignore();
                    if(inputInt == 1){
                        bool forWhile = true;
                        while(forWhile) {
                            int input;
                            auto uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                            auto lowers = "abcdefghijklmnopqrstuvwxyz";
                            auto symbols = "!?(){}[]*&$#@-_+*";
                            std::string pw = "0123456789";

                            fmt::print("\nGive me a number of characters (5 - 20): ");
                            std::cin >> input;
                            std::cin.ignore();

                            if (input < 5 || input > 20) {
                                fmt::print(
                                        "\nGive me a normal number of characters, please\n1- retry\nGive me an answer: ");
                                std::cin >> input;
                                std::cin.ignore();
                                if (input == 1) {
                                    continue;
                                }else{
                                    break;
                                }
                            }
                            int size = input;
                            fmt::print("\nType 1 if you want to use Uppers: ");
                            std::cin >> input;
                            std::cin.ignore();
                            if (input == 1) {
                                pw += uppers;
                            }
                            fmt::print("\nType 1 if you want to use Lowers: ");
                            std::cin >> input;
                            std::cin.ignore();
                            if (input == 1) {
                                pw += lowers;
                            }
                            fmt::print("\nType 1 if you want to use Puncts: ");
                            std::cin >> input;
                            std::cin.ignore();
                            if (input == 1) {
                                pw += symbols;
                            }
                            std::string returner;
                            for (int i = 0; i < size; i++) {
                                int random = rand() % pw.size();
                                returner += pw[random];
                            }
                            std::cout << "\nHere is your password: " << returner << std::endl;
                            fmt::print("If you want to try again, type 1\n");
                            fmt::print("Type here: ");
                            std::cin >> input;
                            std::cin.ignore();
                            if (input == 1) {
                                continue;
                            }
                            itr->second[i].setPassword(returner);
                            forWhile = false;
                        }
                    }else {
                        std::cout << "Please, provide a new one:\n";
                        std::getline(std::cin, inputStr);
                        if (inputStr.empty()) {
                            std::cout << "There is no time for jokes, please next time provide normally.\n";
                        } else {
                            flag = true;
                            for (auto it = Application::categories.begin(); it != Application::categories.end(); it++) {
                                for (int i = 0; i < it->second.size(); i++) {
                                    if (it->second[i].getPassword() == inputStr) {
                                        flag = false;
                                        break;
                                    }
                                }
                                if (!flag) {
                                    break;
                                }
                            }
                            if (!flag) {
                                std::cout
                                        << "There was already a password like that, please, next time check more carefully."
                                        << std::endl;
                            } else {
                                itr->second[i].setPassword(inputStr);
                            }
                        }
                    }
                }
                std::cout << "Do you want to change the login? 1 - yes\n";
                std::cin >> inputInt;
                std::cin.ignore();
                if(inputInt == 1){
                    std::cout << "Please, provide a new one:\n";
                    std::getline(std::cin, inputStr);
                    itr->second[i].setLogin(inputStr);
                }
                std::cout << "Do you want to change the website? 1 - yes\n";
                std::cin >> inputInt;
                std::cin.ignore();
                if(inputInt == 1){
                    std::cout << "Please, provide a new one:\n";
                    std::getline(std::cin, inputStr);
                    itr->second[i].setWebsite(inputStr);
                }
            }
        }
    }
}

void Application::printInfo() {
    std::cout << "Here is all info about passwords we have:\n";
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr ++){
        std::cout << "Category: " << itr->first << std::endl;
        for(int i = 0; i < itr->second.size(); i++){
            std::cout << itr->second[i] << std::endl;
        }
    }
}

void Application::searchName() {
    std::cout << "Please, provide me a name of the password:\n";
    std::string name;
    bool flag = true;
    std::getline(std::cin, name);
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            if(name == itr->second[i].getName()){
                std::cout << "Here is an information about your password:\n" << itr->second[i] << std::endl;
                flag = false;
                break;
            }
        }
        if(!flag){
            break;
        }
    }
}

void Application::searchPass() {
    std::cout << "Please, provide me a password, that you want to find:\n";
    std::string pass;
    std::getline(std::cin, pass);
    bool flag = true;
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            if(pass == itr->second[i].getName()){
                std::cout << "Here is an information about your password:\n" << itr->second[i] << std::endl;
                flag = false;
                break;
            }
        }
        if(!flag){
            break;
        }
    }
}

void Application::search() {
    std::cout << "How do you want to find an information? 1 - by name, 2 - by password:\n";
    int input;
    std::cin >> input;
    std::cin.ignore();
    switch(input){
        case 1:
            searchName();
            break;
        case 2:
            searchPass();
            break;
        default:
            std::cout << "Something got wrong, do you want to try again? 1 - yes:\n";
            std::cin >> input;
            std::cin.ignore();
            if(input == 1){
                search();
                return;
            }
    }
}
void Application::writeIn(const std::string& path) {
    std::ofstream writing(path);
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            for(int j = 0; j < itr->first.size(); j++){
                char input = itr->first[j] ^ Application::key;
                writing << input;
            }
            writing << " ";
            for(int j = 0; j < itr->second[i].getName().size(); j++){
                char input = itr->second[i].getName()[j] ^ Application::key;
                writing << input;
            }
            writing << " ";
            for(int j = 0; j < itr->second[i].getPassword().size(); j++){
                char input = itr->second[i].getPassword()[j] ^ Application::key;
                writing << input;
            }
            writing << " ";
            for(int j = 0; j < itr->second[i].getLogin().size(); j++){
                char input = itr->second[i].getLogin()[j] ^ Application::key;
                writing << input;
            }
            writing << " ";
            for(int j = 0; j < itr->second[i].getWebsite().size(); j++){
                char input = itr->second[i].getWebsite()[j] ^ Application::key;
                writing << input;
            }
            writing << "\n";
        }
    }
    writing.close();
}

void Application::readOut(const std::string& path) {
    std::ifstream reading(path);
    std::string line;
    while(std::getline(reading, line)){
        std::vector<std::string> words;
        std::string word;
        std::istringstream iss(line);
        while(iss >> word){
            words.push_back(word);
        }
        std::string category;
        std::string name;
        std::string password;
        std::string login;
        std::string website;
        for(int i = 0; i < words[0].size(); i++){
            category += words[0][i] ^ Application::key;
        }
        for(int i = 0; i < words[1].size(); i++){
            name += words[1][i] ^ Application::key;
        }
        for(int i = 0; i < words[2].size(); i++){
            password += words[2][i] ^ Application::key;
        }
        for(int i = 0; i < words[3].size(); i++){
            login += words[3][i] ^ Application::key;
        }
        for(int i = 0; i < words[4].size(); i++){
            website += words[4][i] ^ Application::key;
        }
        Application::categories.insert(std::make_pair(category, std::vector<Password>()));
        Password p(name, password);
        p.setLogin(login);
        p.setWebsite(website);
        Application::categories[category].push_back(p);
        words.erase(words.begin(), words.end());
    }
}