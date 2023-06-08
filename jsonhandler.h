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

    // Legge i dati dell'applicazione da un file JSON.
    // Restituisce 'true' se l'operazione ha successo, 'false' in caso contrario.
    bool readJson(const QString &filePath, AccountContainer &accountContainer);

    // Scrive i dati dell'applicazione in un file JSON.
    // Restituisce 'true' se l'operazione ha successo, 'false' in caso contrario.
    bool writeJson(const QString &filePath, const AccountContainer &accountContainer);


private:
    QString filePath; // Percorso del file JSON

    // Metodo per convertire un AccountContainer in un oggetto QJsonArray
    QJsonArray accountContainerToJsonArray(const AccountContainer &accountContainer) const;

    // Metodo per convertire un oggetto QJsonArray in un AccountContainer
    bool jsonArrayToAccountContainer(const QJsonArray &jsonArray, AccountContainer &accountContainer);
};

#endif // JSONHANDLER_H
