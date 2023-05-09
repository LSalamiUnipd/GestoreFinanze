#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include "jsonhandler.h"

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



// Metodo per convertire un AccountContainer in un oggetto QJsonArray
QJsonArray JsonHandler::accountContainerToJsonArray(const AccountContainer &accountContainer) const {
    QJsonArray jsonArray;

    for (const Account &account : accountContainer.getAccounts()) {
        QJsonObject accountObject;
        accountObject["name"] = account.getName();

        QJsonArray expensesArray;
        for (const Expense &expense : account.getExpenses()) {
            QJsonObject expenseObject;
            expenseObject["description"] = expense.getDescription();
            expenseObject["amount"] = expense.getAmount();
            expenseObject["date"] = expense.getDate().toString(Qt::ISODate);
            expensesArray.append(expenseObject);
        }
        accountObject["expenses"] = expensesArray;

        QJsonArray incomesArray;
        for (const Income &income : account.getIncomes()) {
            QJsonObject incomeObject;
            incomeObject["description"] = income.getDescription();
            incomeObject["amount"] = income.getAmount();
            incomeObject["date"] = income.getDate().toString(Qt::ISODate);
            incomesArray.append(incomeObject);
        }
        accountObject["incomes"] = incomesArray;

        jsonArray.append(accountObject);
    }

    return jsonArray;
}


// Metodo per convertire un oggetto QJsonArray in un AccountContainer
void JsonHandler::jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer) {
    for (const QJsonValue &value : jsonArray) {
        QJsonObject accountObject = value.toObject();

        QString accountName = accountObject["name"].toString();
        Account account(accountName);

        QJsonArray expensesArray = accountObject["expenses"].toArray();
        for (const QJsonValue &expenseValue : expensesArray) {
            QJsonObject expenseObject = expenseValue.toObject();

            QString description = expenseObject["description"].toString();
            double amount = expenseObject["amount"].toDouble();
            QDate date = QDate::fromString(expenseObject["date"].toString(), Qt::ISODate);

            Expense expense(description, amount, date);
            account.addExpense(expense);
        }

        QJsonArray incomesArray = accountObject["incomes"].toArray();
        for (const QJsonValue &incomeValue : incomesArray) {
            QJsonObject incomeObject = incomeValue.toObject();

            QString description = incomeObject["description"].toString();
            double amount = incomeObject["amount"].toDouble();
            QDate date = QDate::fromString(incomeObject["date"].toString(), Qt::ISODate);

            Income income(description, amount, date);
            account.addIncome(income);
        }

        accountContainer.addAccount(account);
    }
}
