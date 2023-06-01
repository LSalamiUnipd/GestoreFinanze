#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account {
public:
    // Costruttore di default
    Account();

    // Costruttore con parametri
    Account(const QString &name, const QString &description);

    // Getter e setter per il nome dell'account
    QString getName() const;
    void setName(const QString &newName);

    // Getter e setter per la descrizione dell'account
    QString getDescription() const;
    void setDescription(const QString &newDescription);

private:
    QString name;
    QString description;
};

#endif // ACCOUNT_H
