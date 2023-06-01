#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    // Costruttore di default
    Account();

    // Costruttore con parametri
    Account(const std::string &name, const std::string &description);

    // Getter e setter per il nome dell'account
    std::string getName() const;
    void setName(const std::string &newName);

    // Getter e setter per la descrizione dell'account
    std::string getDescription() const;
    void setDescription(const std::string &newDescription);

private:
    std::string name;
    std::string description;
};

#endif // ACCOUNT_H
