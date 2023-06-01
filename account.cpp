#include "account.h"

// Costruttore di default
Account::Account() : name(""), description("") {}

// Costruttore della classe Account
Account::Account(const std::string &name, const std::string &description)
    : name(name), description(description) {
}

// Getter e setter per il nome dell'account
std::string Account::getName() const {
    return name;
}

void Account::setName(const std::string &newName) {
    name = newName;
}

// Getter e setter per la descrizione dell'account
std::string Account::getDescription() const {
    return description;
}

void Account::setDescription(const std::string &newDescription) {
    description = newDescription;
}
