#pragma once

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fmt/ranges.h>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>



class Password {
    std::string name;
    std::string password;
    std::string login;
    std::string website;
public:

    /**
     * \brief constructor of Password object.
     * Creates an object of type class.
     *
     * @param name will be a name.
     * @param password will be a password itself.
     */
    Password(std::string name, std::string password);

    /**
     * \brief gets a name.
     *
     * @return name
     *
    */
    const std::string &getName() const;

    /**
     * \brief gets a password.
     *
     * @return password
     */
    const std::string &getPassword() const;

    /**
     * \brief gets a login.
     *
     * @return login
     */
    const std::string &getLogin() const;

    /**
     * \brief gets a website.
     *
     * @return website
     */
    const std::string &getWebsite() const;

    /**
     * \brief sets a name manually.
     *
     * @param name
     */
    void setName(const std::string &name);

    /**
    * \brief sets a password manually.
    *
    * @param password
    *
    */
    void setPassword(std::string &password);

    /**
     * \brief sets a login manually.
     *
     * @param login
     */
    void setLogin(std::string &login);

    /**
     * \brief sets a website manually.
     *
     * @param website
     */
    void setWebsite(std::string &website);

    /**
     * \brief creates a password.
     * Function creates a password in two ways: user's own and generated by the program.
     *
    */
    static void create();

    /**
     * \brief generates a password.
     * Function generates a password, asking a user about filters for generation.
     *
     * @return generated password
     *
    */
    static std::string generate();

    /**
     * \brief analog of toString().
     * Function helps us to write an info about a password.
     *
     * @param password gives a password to print.
     * @param ostream gives an output stream.
     */
    friend std::ostream &operator<<(std::ostream &, const Password &);
};

struct Application{

    /**
     * \var is a map of categories.
     * We are storing an information about passwords in a specific categories.
     */
     static std::map<std::string, std::vector<Password>> categories;

     /**
      * \var main password.
      * We are storing here a password to log in to application.
      */
     static std::string mainPassword;

     /**
      * \var key for crypt.
      * This is a key to encrypt and decrypt data.
      */
     static char key;

public:

    /**
     * \brief adds a category.
     * Creates a new category and adds it to a map.
     */
    static void addCategory();

    /**
     * \brief adds a password to a category.
     * Adds a password to a specific category.
     * @param category is a category which we want to fill with a password.
     * @param password is a password which we want to add.
     */
    static void addPassword(const std::string &category, const Password &password);

    /**
     * \brief changes password.
     * Finds a password by a name and propose to change all its info(optional, user can even change nothing).
     */
    static void changePassword();

    /**
     * \brief prints info.
     * Prints all information about all categories and all information about passwords in them.
     */
    static void printInfo();
    /**
     * \brief searches by name.
     * Searches a password's information by a name.
     */
    static void searchName();
    /**
     * \brief searches by password.
     * Searches a password's information by a password.
     */
    static void searchPass();
    /**
     * \brief searching function.
     * Uses other searching functions, adds an interface to interact with a user.
     */
    static void search();

    /**
     * \brief writes data.
     * Writes a data in a file(already encrypted).
     * @param path is a path to a file
     */
    static void writeIn(const std::string& path);

    /**
     * \brief reads a data.
     * Reads a datat from a file(already decrypted).
     * @param path is a path to a file
     */
    static void readOut(const std::string& path);

    //todo: func for main password
};