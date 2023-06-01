#ifndef LOAN_H
#define LOAN_H

#include "finance.h"

class Loan : public Finance {
public:
    // Costruttore della classe Loan
    Loan(const QString &description, double amount, const QDate &date, int duration = 0, double interestRate = 0.0, bool isPaid = false);

    // Distruttore della classe Loan
    ~Loan();

    // Metodi getter per i nuovi attributi
    int getDuration() const;
    double getInterestRate() const;
    bool isLoanPaid() const;

    // Metodi setter per i nuovi attributi
    void setDuration(int duration);
    void setInterestRate(double interestRate);
    void setLoanPaid(bool isPaid);

    // Implementazione del metodo getType()
    QString getType() const override;

private:
    int duration; // durata del prestito in mesi
    double interestRate; // tasso di interesse del prestito
    bool isPaid; // stato del pagamento del prestito
};

#endif // LOAN_H
