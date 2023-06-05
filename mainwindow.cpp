#include "mainwindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTreeView>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout> // Include this for the vertical box layout
#include <QListWidget> // Include this for the list widget
#include "addaccountdialog.h"
#include "addexpensedialog.h"
#include "addincomedialog.h"
#include "addloandialog.h"
#include "editaccountdialog.h"
#include "expense.h"
#include "income.h"
#include "loan.h"
#include <QLabel>

// Costruttore
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    resize(800, 600);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createCentralWidget();
    connect(accountListWidget, &QListWidget::currentItemChanged, this, &MainWindow::on_accountListWidget_currentItemChanged);
}

// Distruttore
MainWindow::~MainWindow() {
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Apri"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::on_actionOpen_triggered);

    saveAction = new QAction(tr("&Salva"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);

    saveAsAction = new QAction(tr("&Salva con nome..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::on_actionSave_As_triggered);

    exitAction = new QAction(tr("&Esci"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    addAccountAction = new QAction(tr("&Aggiungi Account"), this);
    connect(addAccountAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Account_triggered);

    addExpenseAction = new QAction(tr("&Aggiungi Spesa"), this);
    connect(addExpenseAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Expense_triggered);

    addIncomeAction = new QAction(tr("&Aggiungi Entrata"), this);
    connect(addIncomeAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Income_triggered);

    addLoanAction = new QAction(tr("&Aggiungi Prestito"), this);
    connect(addLoanAction, &QAction::triggered, this, &MainWindow::on_actionAdd_Loan_triggered);

    removeAccountAction = new QAction(tr("&Rimuovi Account"), this);
    connect(removeAccountAction, &QAction::triggered, this, &MainWindow::on_actionRemove_Account_triggered);

    editAccountAction = new QAction(tr("&Modifica Account"), this);
    connect(editAccountAction, &QAction::triggered, this, &MainWindow::on_actionEdit_Account_triggered);

    removeTransactionAction = new QAction(tr("&Rimuovi Transazione"), this);
    connect(removeTransactionAction, &QAction::triggered, this, &MainWindow::on_actionRemove_Transaction_triggered);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Modifica"));
    editMenu->addAction(addAccountAction);
    editMenu->addAction(addIncomeAction);
    editMenu->addAction(addExpenseAction);
    editMenu->addAction(addLoanAction);
    editMenu->addSeparator();
    editMenu->addAction(removeAccountAction);
    editMenu->addAction(editAccountAction);
    editMenu->addAction(removeTransactionAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = addToolBar(tr("Modifica"));
    editToolBar->addAction(addAccountAction);
    editToolBar->addAction(addIncomeAction);
    editToolBar->addAction(addExpenseAction);
    editToolBar->addAction(addLoanAction);
    editToolBar->addAction(removeAccountAction);
    editToolBar->addAction(editAccountAction);
    editToolBar->addAction(removeTransactionAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Pronto"));
}

void MainWindow::createCentralWidget()
{
    accountListWidget = new QListWidget(this);
    transactionListWidget = new QListWidget(this);

    // Create labels
    accountListWidgetLabel = new QLabel(tr("Account"), this);
    transactionListWidgetLabel = new QLabel(tr("Transazioni"), this);
    balanceLabel = new QLabel(this);

    // Create a layout and add widgets to it
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(accountListWidgetLabel);
    layout->addWidget(accountListWidget);
    layout->addWidget(transactionListWidgetLabel);
    layout->addWidget(transactionListWidget);
    layout->addWidget(balanceLabel);


    // Create a central widget and set the layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    // Set the central widget
    setCentralWidget(centralWidget);
}

void MainWindow::on_accountListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    // Get the index of the selected account
    int selectedIndex = accountListWidget->row(current);

    // Update the transaction list for this account
    updateTransactionList(selectedIndex);
    updateBalance();
}


// Slot per aprire un file JSON
void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        openFile(filePath);
    }
}

// Slot per salvare il file JSON corrente
void MainWindow::on_actionSave_triggered() {
    if (currentFilePath.isEmpty()) {
        on_actionSave_As_triggered();
    } else {
        saveFile(currentFilePath);
    }
}

// Slot per salvare il file JSON con un nuovo nome
void MainWindow::on_actionSave_As_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File As"), QString(), tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        saveFile(filePath);
    }
}

// Slot per uscire dall'applicazione
void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

// Slot per aggiungere un nuovo account
void MainWindow::on_actionAdd_Account_triggered() {
    AddAccountDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Account newAccount(dialog.getAccountName(), dialog.getAccountDescription());
        accountContainer.addAccount(newAccount);
        updateAccountList();
    }
    updateBalance();
}


// Slot per aggiungere una nuova spesa
void MainWindow::on_actionAdd_Expense_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getExpenseDescription();
        double amount = dialog.getExpenseAmount();
        QDate date = dialog.getExpenseDate();

        Expense newExpense(description, amount, date);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newExpense);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Error adding expense: " << e.what();
            QMessageBox::warning(this, tr("Error"), tr("Failed to add expense."));
        }
    }
    updateBalance();
}


// Slot per aggiungere una nuova entrata
void MainWindow::on_actionAdd_Income_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    AddIncomeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getIncomeDescription();
        double amount = dialog.getIncomeAmount();
        QDate date = dialog.getIncomeDate();

        Income newIncome(description, amount, date);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newIncome);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Error adding income: " << e.what();
            QMessageBox::warning(this, tr("Error"), tr("Failed to add income."));
        }
    }
    updateBalance();
}

void MainWindow::on_actionAdd_Loan_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    AddLoanDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString description = dialog.getLoanDescription();
        double amount = dialog.getLoanAmount();
        QDate date = dialog.getLoanDate();
        int duration = dialog.getLoanDuration();
        double interestRate = dialog.getLoanInterestRate();
        bool isPaid = dialog.isLoanPaid();

        Loan newLoan(description, amount, date, duration, interestRate, isPaid);

        try {
            accountContainer.addTransactionToAccount(selectedIndex, newLoan);
            updateTransactionList(selectedIndex);
        } catch (const std::out_of_range& e) {
            qDebug() << "Error adding loan: " << e.what();
            QMessageBox::warning(this, tr("Error"), tr("Failed to add loan."));
        }
    }
    updateBalance();
}


// Slot per rimuovere un account
void MainWindow::on_actionRemove_Account_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account selected."));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Remove Account"), tr("Are you sure you want to remove the selected account?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        accountContainer.removeAccount(selectedIndex);
        updateAccountList();
    }
    updateBalance();
}

void MainWindow::on_actionEdit_Account_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("Nessun account selezionato."));
        return;
    }

    // Ottenere l'account corrente
    Account currentAccount = accountContainer.getAccount(selectedIndex);

    // Creare un dialogo di modifica account con le informazioni correnti precompilate.
    EditAccountDialog dialog(&currentAccount, this);

    // Se l'utente ha accettato il dialogo, aggiorna l'account nell'AccountContainer
    if (dialog.exec() == QDialog::Accepted) {
        accountContainer.setAccount(selectedIndex, currentAccount);
        updateAccountList();
    }
}



void MainWindow::on_actionRemove_Transaction_triggered() {
    int selectedIndex = accountListWidget->currentRow();
    int selectedTransactionIndex = transactionListWidget->currentRow();

    if (selectedIndex < 0 || selectedTransactionIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No account or transaction selected."));
        return;
    }

    // Remove the selected transaction.
    accountContainer.removeTransactionFromAccount(selectedIndex, selectedTransactionIndex);

    // Update the transaction list.
    updateTransactionList(selectedIndex);
    updateBalance();
}


// Metodo per aprire un file JSON
void MainWindow::openFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open file for reading."));
        return;
    }

    jsonHandler.readJson(file, accountContainer);
    file.close();

    currentFilePath = filePath;
    updateAccountList();
}




// Metodo per salvare un file JSON
void MainWindow::saveFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open file for writing."));
        return;
    }

    jsonHandler.writeJson(file, accountContainer);
    file.close();

    currentFilePath = filePath;
}


// Metodo per aggiornare la lista degli account
void MainWindow::updateAccountList() {
    accountListWidget->clear();

    for (const Account &account : accountContainer.getAccounts()) {
        QString accountDetails = account.getName() + " - " + account.getDescription();
        accountListWidget->addItem(accountDetails);
    }
}



// Method to update the transaction list
void MainWindow::updateTransactionList(int accountIndex) {
    transactionListWidget->clear();
    QList<Finance*> transactions = accountContainer.getTransactions(accountIndex);
    for (const Finance* transaction : transactions) {
        QString transactionStr;
        if (dynamic_cast<const Expense*>(transaction)) {
            transactionStr = " -" + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        } else if (dynamic_cast<const Income*>(transaction)) {
            transactionStr = " +" + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        } else if (dynamic_cast<const Loan*>(transaction)) {
            transactionStr = " Loan " + QString::number(transaction->getAmount()) + ": " + transaction->getDescription();
        }
        transactionListWidget->addItem(transactionStr);
    }
}

void MainWindow::updateBalance() {
    int selectedIndex = accountListWidget->currentRow();
    if (selectedIndex < 0) {
        return;
    }
    double balance = 0.0;
    QList<Finance*> transactions = accountContainer.getTransactions(selectedIndex);
    for (const Finance* transaction : transactions) {
        if (dynamic_cast<const Expense*>(transaction)) {
            balance -= transaction->getAmount();
        } else if (dynamic_cast<const Income*>(transaction)) {
            balance += transaction->getAmount();
        } else if (const Loan* loan = dynamic_cast<const Loan*>(transaction)) {
            // For the purpose of this example, a loan reduces the balance if it is not paid
            if (!loan->isLoanPaid()) {
                balance -= loan->getAmount();
            }
        }
    }
    balanceLabel->setText(tr("Balance: ") + QString::number(balance));
}


