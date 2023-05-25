
#include "funcs.h"


Password::Password(std::string n, std::string p){
    name = std::move(n);
    password = std::move(p);
}


std::string Password::getName() {
    return Password::name;
}


void Password::create() {
    std::string name;
    std::cout << "So, first i need a name for your password, please enter it: " << std::endl;
    std::getline(std::cin, name);
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
    bool arr[4] = {true, true, true, true};

    for(char i : pw){
        uniq.insert(i);
        if(std::isdigit(i) && arr[0]){
            security += 5;
            arr[0] = false;
        }
        else if(std::islower(i) && arr[1]){
            security += 5;
            arr[1] = false;
        }
        else if(std::isupper(i) && arr[2]){
            security += 5;
            arr[2] = false;
        }else if(std::ispunct(i) && arr[3]){
            security += 5;
            arr[3] = false;
        }
    }
    if(uniq.size() >= 6){
        security += 10;
    }
    if(pw.size() > 8){
        security += 10;
    }
    std::string power;
    if(security <= 20){
        power = "weak";
    } else if(security <= 40){
        power = "normal";
    } else if(security <= 50){
        power = "strong";
    } else {
        power = "very strong";
    }
    bool checker = true;
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
        std::cout << "\nThere already was a password like that, you need to came up with another one"<<std::endl;
        Password::create();
        return;
    }

    std::cout << "Your name is: " << name << std::endl;
    std::cout << "Your password is: " << pw << std::endl;
    std::cout << "It is a " << power << " one!" << std::endl;
    fmt::print("Do you want to confirm this password?\n1 - yes.\nType your answer: ");
    std::cin >> input;
    std::cin.ignore();
    if(input != 1){
        Password::create();
    }
    std::cout << "\n";
    Password p(name, pw);
    std::cout << "Do you want to add it to some category? 1 - yes: ";
    std::cin >> input;
    std::cin.ignore();
    if(input == 1) {
        bool checker = true;
        while (checker) {
            std::string cname;
            std::cout << "\nPlease, provide category's name: " << std::endl;
            std::getline(std::cin, cname);
            if (Application::getCategories().find(cname) != Application::getCategories().end()) {
                Application::addPassword(cname, p);
                checker = false;
            }else{
                std::cout << "\nThere are no category like that, let's try again? 1 - yes" << std::endl;
                std::cin >> input;
                std::cin.ignore();
                if(input != 1){
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

void Password::setPassword(std::string &p) {
    password = std::move(p);
}

std::ostream &operator<<(std::ostream &os, const Password &pw) {
    return os << "Your name is: " << pw.name << "\nYour password is: " << pw.password << "\n";
}
