#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>

class Account;

class EditAccountDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditAccountDialog(Account *accountToEdit, QWidget *parent = nullptr);

    QString getAccountName() const;
    QString getAccountDescription() const;

public slots:
    void accept() override;

private:
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QDialogButtonBox *buttonBox;

    Account *account;
};

#endif // EDITACCOUNTDIALOG_H
