#ifndef FINANCE_H
#define FINANCE_H

#include <QString>
#include <QDate>

// Classe astratta base Finance
class Finance {
public:
    // Costruttore
    Finance(const QString &description, double amount, const QDate &date);

    // Distruttore virtuale
    virtual ~Finance();

    // Getter per la descrizione, l'importo e la data
    QString getDescription() const;
    double getAmount() const;
    QDate getDate() const;

    // Setter per la descrizione, l'importo e la data
    void setDescription(const QString &description);
    void setAmount(double amount);
    void setDate(const QDate &date);

    // Metodo virtuale puro per ottenere il tipo di transazione finanziaria
    virtual QString getType() const = 0;

private:
    QString description; // Descrizione dell'operazione finanziaria
    double amount; // Importo dell'operazione finanziaria
    QDate date; // Data dell'operazione finanziaria
};

#endif // FINANCE_H
