#include "funcs.h"


Password::Password(std::string name){
    this->name = name;
}


std::string Password::getName() {
    return Password::name;
}


void Password::create() {
    int input;
    fmt::print("1 - create your own password.\n2 - generate a password.\n0 - exit.\nWhat will you choose: ");
    std::cin >> input;
    std::string pw = "";
    switch(input){
        case 1:
            fmt::print("\nPass me your password, length must be 5 - 20 characters: ");
            std::getline(std::cin, pw);
            if(pw.size() < 5 || pw.size() > 20){
                fmt::print("\nNot proper length.\n1 - restart a function.\n0 - back to menu.\nWhat will you choose: ");
                std::cin >> input;
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
            if(input == 1){
                Password::create();
            }
            return;

    }

    if(pw == ""){
        fmt::print("\nPlease, type something next time.\n1 - restart a function.\n0 - back to menu.\nWhat will you choose: ");
        std::cin >> input;
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
    fmt::print("Your password is: ", pw, " It is a ", power, " password.\n");
    fmt::print("Do you want to confirm this password?\n1 - yes.\nType your answer: ");
    std::cin >> input;
    if(input != 1){
        Password::create();
    }
    std::cout << "\n";
    return;
}
std::string Password::generate() {
    int input;
    auto uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    auto lowers = "abcdefghijklmnopqrstuvwxyz";
    auto symbols ="!?(){}[]*&$#@-_+*";
    std::string pw = "0123456789";

    fmt::print("\nGive me a number of characters (5 - 20): ");
    std::cin >> input;

    if(input < 5 || input > 20){
        fmt::print("\nGive me a normal number of characters, please\n1- retry\nGive me an answer: ");
        std::cin >> input;
        if(input == 1){
            Password::create();
        }
        return "";
    }
    int size = input;
    fmt::print("\nType 1 if you want to use Uppers: ");
    std::cin >> input;
    if(input == 1){
        pw += uppers;
    }
    fmt::print("\nType 1 if you want to use Lowers: ");
    std::cin >> input;
    if(input == 1){
        pw += lowers;
    }
    fmt::print("\nType 1 if you want to use Puncts: ");
    std::cin >> input;
    if(input == 1){
        pw += symbols;
    }
    std::string returner = "";
    for(int i = 0; i < size; i++){
        int random = rand() % pw.size();
        returner += pw[random];
    }
    fmt::print("\nHere is your password: ", returner);
    fmt::print("\nIf you want to try again, type 1\n");
    fmt::print("Type here: ");
    std::cin >> input;
    if(input == 1){
        Password::create();
        return "";
    }
    return returner;
}

void Password::setPassword(std::string password) {
    this->password = password;
}