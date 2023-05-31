#include "loan.h"

// Costruttore della classe Loan
Loan::Loan(const QString &description, double amount, const QDate &date, int duration, double interestRate, bool isPaid)
    : Finance(description, amount, date), duration(duration), interestRate(interestRate), isPaid(isPaid) {
}

// Distruttore della classe Loan
Loan::~Loan() {
}

// Metodi getter per i nuovi attributi
int Loan::getDuration() const {
    return duration;
}

double Loan::getInterestRate() const {
    return interestRate;
}

bool Loan::isLoanPaid() const {
    return isPaid;
}

// Metodi setter per i nuovi attributi
void Loan::setDuration(int duration) {
    this->duration = duration;
}

void Loan::setInterestRate(double interestRate) {
    this->interestRate = interestRate;
}

void Loan::setLoanPaid(bool isPaid) {
    this->isPaid = isPaid;
}

// Implementazione del metodo getType()
QString Loan::getType() const {
    return "Loan";
}
