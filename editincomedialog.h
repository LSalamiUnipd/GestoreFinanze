#ifndef EDITINCOMEDIALOG_H
#define EDITINCOMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <income.h>

// Classe EditIncomeDialog per la modifica di un oggetto Income
class EditIncomeDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditIncomeDialog(Income& income, QWidget *parent = nullptr); // Costruttore

    // Getter per l'Income modificato e i suoi campi
    Income getModifiedIncome() const;
    QString getIncomeDescription() const;
    double getIncomeAmount() const;
    QDate getIncomeDate() const;

private slots:
    void accept() override; // Slot di accettazione del dialogo

private:
    // Riferimenti all'Income originale e a una copia modificabile dello stesso
    Income &originalIncome;
    Income modifiedIncome;

    // Widget di input
    QLineEdit* descriptionEdit;
    QDoubleSpinBox* amountEdit;
    QDateEdit* dateEdit;
    QDialogButtonBox* buttonBox;
};

#endif // EDITINCOMEDIALOG_H
