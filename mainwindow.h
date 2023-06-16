#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accountcontainer.h"
#include "jsonhandler.h"
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTreeView>
#include <QBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Classe MainWindow per l'interfaccia principale dell'applicazione
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Costruttore e distruttore
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot per la gestione dei segnali dell'interfaccia utente
    void on_accountListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionExit_triggered();
    void on_actionAdd_Account_triggered();
    void on_actionAdd_Expense_triggered();
    void on_actionAdd_Income_triggered();
    void on_actionAdd_Loan_triggered();
    void on_actionRemove_Account_triggered();
    void on_actionEdit_Account_triggered();
    void on_actionRemove_Transaction_triggered();
    void on_actionEdit_Transaction_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;  // Layout principale della finestra

    // Contenitori di dati e gestore di file JSON
    AccountContainer accountContainer;
    JsonHandler jsonHandler;
    QString currentFilePath;  // Percorso del file attualmente aperto

    // Widget per visualizzare gli account e le transazioni
    QListWidget* accountListWidget;
    QListWidget* transactionListWidget;

    // Etichette per bilancio e widget
    QLabel *balanceLabel;
    QLabel *accountListWidgetLabel;
    QLabel *transactionListWidgetLabel;

    // Creazione delle componenti dell'interfaccia utente
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();

    // Menù e sottomenù
    QMenu *fileMenu;
    QMenu *editMenu;

    // Azioni disponibili nei menù
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *addAccountAction;
    QAction *addExpenseAction;
    QAction *addIncomeAction;
    QAction *addLoanAction;
    QAction *removeAccountAction;
    QAction *editAccountAction;
    QAction *removeTransactionAction;
    QAction *editTransactionAction;

    // Barre degli strumenti
    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    // Metodi di supporto per aprire e salvare file, e aggiornare l'interfaccia utente
    void openFile(const QString &filePath);
    void saveFile(const QString &filePath);
    void updateAccountList();
    void updateTransactionList(int accountIndex);
    void updateBalance();
};
#endif // MAINWINDOW_H
