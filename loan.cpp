#include "loan.h"

// Implementazione del costruttore di Loan
Loan::Loan(const QString &description, double amount, const QDate &date, int duration, double interestRate, bool isPaid)
    : Finance(description, amount, date), duration(duration), interestRate(interestRate), isPaid(isPaid) {
}

// Implementazione del distruttore di Loan
Loan::~Loan() {
}

// Implementazione dei getter per la durata, tasso d'interesse e stato del prestito
int Loan::getDuration() const {
    return duration;
}

double Loan::getInterestRate() const {
    return interestRate;
}

bool Loan::isLoanPaid() const {
    return isPaid;
}

// Implementazione dei setter per la durata, tasso d'interesse e stato del prestito
void Loan::setDuration(int duration) {
    this->duration = duration;
}

void Loan::setInterestRate(double interestRate) {
    this->interestRate = interestRate;
}

void Loan::setLoanPaid(bool isPaid) {
    this->isPaid = isPaid;
}

// Implementazione del metodo per ottenere il tipo di transazione finanziaria
QString Loan::getType() const {
    return "Loan";
}
