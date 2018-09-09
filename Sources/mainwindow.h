#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>

#include "Classes/ft_account.h"
#include "Classes/ft_accountmanager.h"
#include "Classes/ft_shop.h"
#include "Classes/ft_customer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();
    void Slot_StepTimer(void);

    void on_pushButton_stop_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_finish_clicked();

    void on_pushButton_carryForward_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* m_StepTimer = NULL;
    uint32_t m_numOfDays = 0;
    double m_cashVirtual = 0.0;
    int32_t m_month = -1;
    const double m_weeksPerMonth = 4.0;
    const double m_daysPerWeek = 30.0;
    QSettings* m_Settings = NULL;

    FT_Account* m_accountBilanz = NULL;
    FT_AccountManager m_accountManager;
    FT_Shop* m_shop = NULL;
    QList<FT_Customer*> m_CustomerList;

    enum en_Accounts
    {
      en_Account_Loehne = 0,
      en_Account_Miete,
      en_Account_BueroGeschAusst,
      en_Account_Bank,
      en_Account_Eigenkapital,
      en_Account_Verbindlichkeiten,
      en_Account_Umsatzerloese,
      en_Account_GUV,
      en_Account_Warenlager,
      en_Account_SBK,
      en_Account_Versicherungen,
      sizeof_en_Accounts
    };

    struct st_Accounts
    {
      const QString m_name;
      FT_Account::en_AccountTypes m_type;
    };

    st_Accounts m_Accounts[en_Accounts::sizeof_en_Accounts] =
    {
      {  // en_Account_Loehne
        "Löhne",
        FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto
      },
      {  // en_Account_Miete
        "Miete",
        FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto
      },
      {  // en_Account_BueroGeschAusst
        "Büro- und Geschäftsausstattung",
        FT_Account::en_AccountTypes::en_AccountType_Activa
      },
      {  // en_Account_Bank
        "Bank",
        FT_Account::en_AccountTypes::en_AccountType_Activa
      },
      {  // en_Account_Eigenkapital
        "Eigenkapital",
        FT_Account::en_AccountTypes::en_AccountType_Passiva
      },
      {  // en_Account_Verbindlichkeiten
        "Verbindlichkeiten",
        FT_Account::en_AccountTypes::en_AccountType_Passiva
      },
      {  // en_Account_Umsatzerloese
        "Umsatzerlöse",
        FT_Account::en_AccountTypes::en_AccountType_Ertragskonto
      },
      {  // en_Account_GUV
        "GUV",
        FT_Account::en_AccountTypes::en_AccountType_Abschlusskonto
      },
      {  // en_Account_Warenlager
        "Warenlager",
         FT_Account::en_AccountTypes::en_AccountType_Activa
      },
      {  // en_Account_SBK
        "Schlussbilanzkonto",
        FT_Account::en_AccountTypes::en_AccountType_Abschlusskonto
      },
      {  // en_Account_Versicherungen
        "Versicherungen",
        FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto
      },
    };
};

#endif // MAINWINDOW_H
