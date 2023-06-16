#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include "jsonhandler.h"
#include "expense.h"
#include "income.h"
#include "loan.h"

JsonHandler::JsonHandler() {
}

// Costruttore di JsonHandler
JsonHandler::JsonHandler(const QString &filePath)
    : filePath(filePath) {
    QFile file(filePath);
    qDebug() << "File path: " << filePath;
}

// Legge i dati dell'applicazione da un file JSON
bool JsonHandler::readJson(const QString &filePath, AccountContainer &accountContainer) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Non è possibile aprire il file" << filePath << "per la lettura:" << file.errorString();
        return false;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCritical() << "Errore durante il parsing del file JSON:" << parseError.errorString();
        return false;
    }

    if (!jsonDocument.isArray()) {
        qCritical() << "Il file JSON non ha la struttura prevista.";
        return false;
    }

    QJsonArray jsonArray = jsonDocument.array();

    if (!jsonArrayToAccountContainer(jsonArray, accountContainer)) {
        qCritical() << "Errore durante la conversione del file JSON in AccountContainer.";
        return false;
    }

    return true;
}

// Scrive i dati dell'applicazione in un file JSON
bool JsonHandler::writeJson(const QString &filePath, const AccountContainer &accountContainer) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Non è possibile aprire il file" << filePath << "per la scrittura:" << file.errorString();
        return false;
    }

    QJsonArray jsonArray = accountContainerToJsonArray(accountContainer);
    QJsonDocument jsonDocument(jsonArray);
    file.write(jsonDocument.toJson());
    if (file.error() != QFile::NoError) {
        qCritical() << "Errore nella scrittura sul file" << filePath << ":" << file.errorString();
        return false;
    }
    return true;
}



// Converte un AccountContainer in un oggetto QJsonArray
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



// Converte un oggetto QJsonArray in un AccountContainer
bool JsonHandler::jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer) {
    for (const QJsonValue &value : jsonArray) {
        QJsonObject accountObject = value.toObject();

        QString accountName = accountObject["name"].toString();
        QString accountDescription = accountObject["description"].toString();
        Account account(accountName, accountDescription);

        int index = accountContainer.findAccount(accountName);
        if (index == -1) {
            // Se l'account non esiste ancora, aggiungilo
            accountContainer.addAccount(account);
            index = accountContainer.findAccount(accountName);
        }

        QJsonArray transactionsArray = accountObject["transactions"].toArray();
        for (const QJsonValue &transactionValue : transactionsArray) {
            QJsonObject transactionObject = transactionValue.toObject();

            QString description = transactionObject["description"].toString();
            double amount = transactionObject["amount"].toDouble();
            QDate date = QDate::fromString(transactionObject["date"].toString(), Qt::ISODate);
            QString type = transactionObject["type"].toString();

            if (type == "Expense") {
                Expense* expense = new Expense(description, amount, date);
                accountContainer.addTransactionToAccount(index, *expense);
            } else if (type == "Income") {
                Income* income = new Income(description, amount, date);
                accountContainer.addTransactionToAccount(index, *income);
            } else if (type == "Loan") {
                int duration = transactionObject["duration"].toInt();
                double interestRate = transactionObject["interestRate"].toDouble();
                bool isPaid = transactionObject["isPaid"].toBool();

                Loan* loan = new Loan(description, amount, date, duration, interestRate, isPaid);
                accountContainer.addTransactionToAccount(index, *loan);
            }
        }
    }

    return true;
}
