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
    void on_actionRemove_Account_triggered();
    void on_actionEdit_Account_triggered();
    void on_actionRemove_Transaction_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;

    AccountContainer accountContainer;
    JsonHandler jsonHandler;
    QString currentFilePath;
    QListWidget* accountListWidget;   // List widget for accounts
    QListWidget* transactionListWidget;   // List widget for transactions (expenses and incomes)
    QLabel *balanceLabel;
    QLabel *accountListWidgetLabel;
    QLabel *transactionListWidgetLabel;
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *addAccountAction;
    QAction *addExpenseAction;
    QAction *addIncomeAction;
    QAction *removeAccountAction;
    QAction *editAccountAction;
    QAction *removeTransactionAction;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    // Metodi di supporto
    void openFile(const QString &filePath);
    void saveFile(const QString &filePath);
    void updateAccountList();
    void updateExpenseIncomeList(int accountIndex);
    void updateBalance();
};
#endif // MAINWINDOW_H
