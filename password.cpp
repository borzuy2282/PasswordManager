
#include "funcs.h"


Password::Password(std::string n, std::string p){
    name = std::move(n);
    password = std::move(p);
}

void Password::create() {
    std::string name;
    std::cout << "So, first i need a name for your password, please enter it: " << std::endl;
    std::getline(std::cin, name);
    bool checker = true;
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            if(itr->second[i].name == name){
                checker = false;
                break;
            }
        }
        if(!checker){
            break;
        }
    }
    if(!checker){
        std::cout << "\nThere already was a password like that, you need to come up with another one"<<std::endl;
        Password::create();
        return;
    }
    int input;
    fmt::print("1 - create your own password.\n2 - generate a password.\n0 - exit.\nWhat will you choose: ");
    std::cin >> input;
    std::cin.ignore();
    std::string pw;
    switch(input){
        case 1:
            fmt::print("\nPass me your password, length must be 5 - 20 characters: \n");
            std::getline(std::cin, pw);
            if(pw.size() < 5 || pw.size() > 20){
                fmt::print("\nNot proper length.\n1 - restart a function.\n0 - back to menu.\nWhat will you choose: ");
                std::cin >> input;
                std::cin.ignore();
                std::cout << "\n";
                if(input == 1){
                    Password::create();
                }
                return;
            }
            break;
        case 2:
            pw = Password::generate();
            break;
        case 0:
            return;
        default:
            fmt::print("\nChoose more properly, please.\n1 - restart a function.\n0 - back to menu.\nWhat will you choose: ");
            std::cin >> input;
            std::cin.ignore();
            if(input == 1){
                Password::create();
            }
            return;

    }

    if(pw.empty()){
        fmt::print("\nPlease, type something next time.\n1 - restart a function.\n0 - back to menu.\nWhat will you choose: ");
        std::cin >> input;
        std::cin.ignore();
        if(input == 1){
            Password::create();
        }
        return;
    }

    int security = 0;

    std::set<char>uniq;
    bool lower = true;
    bool upper = true;
    bool punct = true;
    bool digit = true;
    for(char i : pw){
        uniq.insert(i);

        if(std::islower(i) && lower){
            security += 5;
            lower = false;
        }
        else if(std::isupper(i) && upper) {
            security += 5;
            upper = false;
        }
        else if(std::ispunct(i) && punct){
            security += 5;
            punct = false;
        }
        else if(std::isdigit(i) && digit){
            security += 5;
            digit = false;
        }
    }
    if(uniq.size() >= 6){
        security += 10;
    }
    if(pw.size() > 8){
        security += 10;
    }
    std::string power;
    if(security <= 10){
        power = "weak";
    } else if(security <= 20){
        power = "normal";
    } else if(security <= 30){
        power = "strong";
    } else {
        power = "very strong";
    }
    checker = true;
    for(auto itr = Application::categories.begin(); itr != Application::categories.end(); itr++){
        for(int i = 0; i < itr->second.size(); i++){
            if(itr->second[i].password == pw){
                checker = false;
                break;
            }
        }
        if(!checker){
            break;
        }
    }
    if(!checker){
        std::cout << "\nThere already was a password like that, you need to come up with another one"<<std::endl;
        Password::create();
        return;
    }
    std::string login = "None";
    std::string website = "None";
    std::cout << "Do you want to provide a login? 1- yes" << std::endl;
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        std::cout << "Provide it here, pls:" << std::endl;
        std::getline(std::cin, login);
        if(login.empty()){
            login = "None";
        }
    }
    std::cout << "\nDo you want to provide a website? 1- yes" << std::endl;
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        std::cout << "Provide it here, pls:" << std::endl;
        std::getline(std::cin, website);
        if(website.empty()){
            website = "None";
        }
    }
    std::cout << "Your name is: " << name << std::endl;
    std::cout << "Your password is: " << pw << std::endl;
    std::cout << "It is a " << power << " one!" << std::endl;
    std::cout << "Your login is: " << login << std::endl;
    std::cout << "Your website is: " << website << std::endl;
    fmt::print("Do you want to confirm this password?\n1 - yes.\nType your answer: ");
    std::cin >> input;
    std::cin.ignore();
    if(input != 1){
        Password::create();
    }
    std::cout << "\n";
    Password p(name, pw);
    p.setLogin(login);
    p.setWebsite(website);
    std::cout << "Do you want to add it to some category? 1 - yes: ";
    std::cin >> input;
    std::cin.ignore();
    if(input == 1) {
        checker = true;
        while (checker) {
            std::string cname;
            std::cout << "\nPlease, provide category's name: " << std::endl;
            std::getline(std::cin, cname);
            if (Application::categories.find(cname) != Application::categories.end()) {
                Application::addPassword(cname, p);
                checker = false;
            }else{
                std::cout << "\nThere are no category like that, do you want to create new? 1 - yes" << std::endl;
                std::cin >> input;
                std::cin.ignore();
                if(input != 1){
                    std::cout << "Then we add it to the None category." << std::endl;
                    Application::categories["None"].push_back(p);
                    checker = false;
                }else{
                    Application::categories.insert(std::make_pair(cname, std::vector<Password>()));
                    Application::categories[cname].push_back(p);
                    checker = false;
                }
            }
        }
    }else{
        Application::categories["None"].push_back(p);
    }
    std::cout << "\nYour password has been created!" << std::endl;

}
std::string Password::generate() {
    int input;
    auto uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    auto lowers = "abcdefghijklmnopqrstuvwxyz";
    auto symbols ="!?(){}[]*&$#@-_+*";
    std::string pw = "0123456789";

    fmt::print("\nGive me a number of characters (5 - 20): ");
    std::cin >> input;
    std::cin.ignore();

    if(input < 5 || input > 20){
        fmt::print("\nGive me a normal number of characters, please\n1- retry\nGive me an answer: ");
        std::cin >> input;
        std::cin.ignore();
        if(input == 1){
            Password::create();
        }
        return "";
    }
    int size = input;
    fmt::print("\nType 1 if you want to use Uppers: ");
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        pw += uppers;
    }
    fmt::print("\nType 1 if you want to use Lowers: ");
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        pw += lowers;
    }
    fmt::print("\nType 1 if you want to use Puncts: ");
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        pw += symbols;
    }
    std::string returner;
    for(int i = 0; i < size; i++){
        int random = rand() % pw.size();
        returner += pw[random];
    }
    std::cout << "\nHere is your password: " << returner << std::endl;
    fmt::print("If you want to try again, type 1\n");
    fmt::print("Type here: ");
    std::cin >> input;
    std::cin.ignore();
    if(input == 1){
        Password::create();
        return "";
    }
    return returner;
}
void Password::setName(const std::string &name) {
    Password::name = name;
}

void Password::setPassword(std::string &p) {
    this->password = p;
}

void Password::setLogin(std::string &login){
    this->login = login;
}

void Password::setWebsite(std::string &website) {
    this->website = website;
}
std::ostream &operator<<(std::ostream &os, const Password &pw) {
    return os << "Your name is: " << pw.name << "\nYour password is: " << pw.password << "\nYour login is: " << pw.login << "\nYour website is: " << pw.website << std::endl;
}

const std::string &Password::getName() const{
    return Password::name;
}

const std::string &Password::getPassword() const {
    return password;
}

const std::string &Password::getLogin() const {
    return login;
}

const std::string &Password::getWebsite() const {
    return website;
}
