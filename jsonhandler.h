#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include "accountcontainer.h"

// Dichiarazione della classe JsonHandler
class JsonHandler {
public:
    JsonHandler();
    // Costruttore
    explicit JsonHandler(const QString &filePath);

    // Metodo per leggere i dati dell'applicazione da un file JSON
    bool readJson(QFile &file, AccountContainer &accountContainer);

    // Metodo per scrivere i dati dell'applicazione su un file JSON
    bool writeJson(QFile &file, const AccountContainer &accountContainer);



private:
    QString filePath; // Percorso del file JSON

    // Metodo per convertire un AccountContainer in un oggetto QJsonArray
    QJsonArray accountContainerToJsonArray(const AccountContainer &accountContainer) const;

    // Metodo per convertire un oggetto QJsonArray in un AccountContainer
    void jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer);

};

#endif // JSONHANDLER_H
