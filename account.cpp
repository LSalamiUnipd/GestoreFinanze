#include "account.h"

// Costruttore di default
Account::Account() : name(""), description("") {}

// Costruttore della classe Account
Account::Account(const QString &name, const QString &description)
    : name(name), description(description) {
}

// Getter e setter per il nome dell'account
QString Account::getName() const {
    return name;
}

void Account::setName(const QString &newName) {
    name = newName;
}

// Getter e setter per la descrizione dell'account
QString Account::getDescription() const {
    return description;
}

void Account::setDescription(const QString &newDescription) {
    description = newDescription;
}
