#ifndef LOAN_H
#define LOAN_H

#include "finance.h"

// Classe Loan che estende Finance
class Loan : public Finance {
public:
    // Costruttore
    Loan(const QString &description, double amount, const QDate &date, int duration = 0, double interestRate = 0.0, bool isPaid = false);

    // Distruttore
    ~Loan();

    // Getter per la durata, tasso d'interesse e stato del prestito
    int getDuration() const;
    double getInterestRate() const;
    bool isLoanPaid() const;

    // Setter per la durata, tasso d'interesse e stato del prestito
    void setDuration(int duration);
    void setInterestRate(double interestRate);
    void setLoanPaid(bool isPaid);

    // Implementazione del metodo per ottenere il tipo di transazione finanziaria
    QString getType() const override;

private:
    int duration; // Durata del prestito in mesi
    double interestRate; // Tasso di interesse del prestito
    bool isPaid; // Indica se il prestito è stato pagato
};

#endif // LOAN_H
