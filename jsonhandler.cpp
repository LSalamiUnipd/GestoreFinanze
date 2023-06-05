#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include "jsonhandler.h"
#include "expense.h"
#include "income.h"
#include "loan.h"

JsonHandler::JsonHandler() {
}

// Costruttore della classe JsonHandler
JsonHandler::JsonHandler(const QString &filePath)
    : filePath(filePath) {
}

// Metodo per leggere i dati dell'applicazione da un file JSON
bool JsonHandler::readJson(QFile &file, AccountContainer &accountContainer) {
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = jsonDocument.array();

    jsonArrayToAccountContainer(jsonArray, accountContainer);
    return true;
}

// Metodo per scrivere i dati dell'applicazione su un file JSON
bool JsonHandler::writeJson(QFile &file, const AccountContainer &accountContainer) {
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonArray jsonArray = accountContainerToJsonArray(accountContainer);
    QJsonDocument jsonDocument(jsonArray);

    file.write(jsonDocument.toJson());
    file.close();
    return true;
}


// Method to convert an AccountContainer to a QJsonArray
QJsonArray JsonHandler::accountContainerToJsonArray(const AccountContainer &accountContainer) const {
    QJsonArray jsonArray;

    for (int i = 0; i < accountContainer.getAccounts().size(); i++) {
        const Account &account = accountContainer.getAccount(i);
        QJsonObject accountObject;

        accountObject["name"] = account.getName();
        accountObject["description"] = account.getDescription();

        QJsonArray transactionsArray;
        for (const Finance* transaction : accountContainer.getTransactions(i)) {
            QJsonObject transactionObject;

            transactionObject["description"] = transaction->getDescription();
            transactionObject["amount"] = transaction->getAmount();
            transactionObject["date"] = transaction->getDate().toString(Qt::ISODate);
            transactionObject["type"] = transaction->getType();

            if (transaction->getType() == "Loan") {
                const Loan* loan = static_cast<const Loan*>(transaction);
                transactionObject["duration"] = loan->getDuration();
                transactionObject["interestRate"] = loan->getInterestRate();
                transactionObject["isPaid"] = loan->isLoanPaid();
            }

            transactionsArray.append(transactionObject);
        }

        accountObject["transactions"] = transactionsArray;
        jsonArray.append(accountObject);
    }

    return jsonArray;
}



// Method to convert a QJsonArray to an AccountContainer
void JsonHandler::jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer) {
    for (const QJsonValue &value : jsonArray) {
        QJsonObject accountObject = value.toObject();

        QString accountName = accountObject["name"].toString();
        QString accountDescription = accountObject["description"].toString();
        Account account(accountName, accountDescription);

        QJsonArray transactionsArray = accountObject["transactions"].toArray();
        for (const QJsonValue &transactionValue : transactionsArray) {
            QJsonObject transactionObject = transactionValue.toObject();

            QString description = transactionObject["description"].toString();
            double amount = transactionObject["amount"].toDouble();
            QDate date = QDate::fromString(transactionObject["date"].toString(), Qt::ISODate);
            QString type = transactionObject["type"].toString();

            if (type == "Expense") {
                Expense* expense = new Expense(description, amount, date);
                accountContainer.addTransactionToAccount(accountContainer.findAccount(accountName), *expense);
            } else if (type == "Income") {
                Income* income = new Income(description, amount, date);
                accountContainer.addTransactionToAccount(accountContainer.findAccount(accountName), *income);
            } else if (type == "Loan") {
                int duration = transactionObject["duration"].toInt();
                double interestRate = transactionObject["interestRate"].toDouble();
                bool isPaid = transactionObject["isPaid"].toBool();

                Loan* loan = new Loan(description, amount, date, duration, interestRate, isPaid);
                accountContainer.addTransactionToAccount(accountContainer.findAccount(accountName), *loan);
            }
        }

        if (!accountContainer.getAccount(accountContainer.findAccount(accountName)).getName().isEmpty()) {
            accountContainer.addAccount(account);
        }
    }
}
