#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include "accountcontainer.h"

// Classe JsonHandler per gestire le operazioni di lettura e scrittura su file JSON
class JsonHandler {
public:
    // Costruttori
    JsonHandler();
    explicit JsonHandler(const QString &filePath);

    // Legge i dati dell'applicazione da un file JSON, ritorna 'true' in caso di successo
    bool readJson(const QString &filePath, AccountContainer &accountContainer);

    // Scrive i dati dell'applicazione in un file JSON, ritorna 'true' in caso di successo
   bool writeJson(const QString &filePath, const AccountContainer &accountContainer);


private:
    QString filePath; // Percorso del file JSON

    // Converte un AccountContainer in un oggetto QJsonArray
    QJsonArray accountContainerToJsonArray(const AccountContainer &accountContainer) const;

    // Converte un oggetto QJsonArray in un AccountContainer
    bool jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer);
};

#endif // JSONHANDLER_H
