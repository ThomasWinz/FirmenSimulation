#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "Classes/ft_account.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_StepTimer = new QTimer();
  m_StepTimer->setInterval(1000);
  connect(m_StepTimer, &QTimer::timeout,
          this, &MainWindow::Slot_StepTimer);

  QPixmap pixmap(":/General/logo.PNG");

  ui->label_logo->setPixmap(pixmap);

  m_Settings = new QSettings("filderTechnologie.ini");
  ui->doubleSpinBox_reassurance->setValue(m_Settings->value("doubleSpinBox_reassurance", 0).toDouble());
  ui->doubleSpinBox_salary->setValue(m_Settings->value("doubleSpinBox_salary", 0).toDouble());
  ui->doubleSpinBox_fulfilment->setValue(m_Settings->value("doubleSpinBox_fulfilment", 0).toDouble());
  ui->doubleSpinBox_materialCostPerProduct->setValue(m_Settings->value("doubleSpinBox_materialCostPerProduct", 0).toDouble());
  ui->doubleSpinBox_productPrice->setValue(m_Settings->value("doubleSpinBox_productPrice", 0).toDouble());
  ui->doubleSpinBox_aboPricePerMonth->setValue(m_Settings->value("doubleSpinBox_aboPricePerMonth", 0).toDouble());
  ui->doubleSpinBox_deliveryTime->setValue(m_Settings->value("doubleSpinBox_deliveryTime", 0).toDouble());

  ui->doubleSpinBox_acquisitionTime->setValue(m_Settings->value("doubleSpinBox_acquisitionTime", 0).toDouble());
  ui->doubleSpinBox_supportTimePerCustomerPerMonth->setValue(m_Settings->value("doubleSpinBox_supportTimePerCustomerPerMonth", 0).toDouble());
  ui->doubleSpinBox_startupCash->setValue(m_Settings->value("doubleSpinBox_startupCash", 0).toDouble());

  ui->spinBox_numOfCustomers->setValue(m_Settings->value("spinBox_numOfCustomers", 0).toInt());
  ui->spinBox_deliveriesPerMonth->setValue(m_Settings->value("spinBox_deliveriesPerMonth", 0).toInt());
  ui->spinBox_newCustomersPerMonth->setValue(m_Settings->value("spinBox_newCustomersPerMonth", 0).toInt());
  ui->spinBox_abonnents->setValue(m_Settings->value("spinBox_abonnents", 0).toInt());

  on_pushButton_reset_clicked();

  m_accountBilanz = new FT_Account(NULL);
  m_accountBilanz->show();

  m_accountBilanz->Slot_SetTitles("Bilanz",
                                "Activa",
                                "Passiva");

  for (uint32_t i = 0; en_Accounts::sizeof_en_Accounts > i; i++)
  {
    m_accountManager.Slot_RegisterAccount(m_Accounts[i].m_name,
                                           "Soll",
                                           "Haben",
                                          m_Accounts[i].m_type,
                                          m_accountBilanz);
  }

  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_BueroGeschAusst,
                                   en_Accounts::en_Account_Verbindlichkeiten,
                                   50.0);
  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Loehne,
                                   en_Accounts::en_Account_Bank,
                                   30.0);
  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Miete,
                                   en_Accounts::en_Account_Bank,
                                   20.0);
  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Bank,
                                   en_Accounts::en_Account_Umsatzerloese,
                                   90.0);

  m_accountManager.Slot_SetEBK(en_Accounts::en_Account_Eigenkapital,
                               2000.0);

  m_accountManager.Slot_SetEBK(en_Accounts::en_Account_Bank,
                               2000.0);

  m_accountManager.show();

  m_accountManager.Slot_Init();
}


MainWindow::~MainWindow()
{
  m_Settings->setValue("doubleSpinBox_reassurance", ui->doubleSpinBox_reassurance->value());

  m_Settings->setValue("doubleSpinBox_salary", ui->doubleSpinBox_salary->value());
  m_Settings->setValue("doubleSpinBox_fulfilment", ui->doubleSpinBox_fulfilment->value());
  m_Settings->setValue("doubleSpinBox_materialCostPerProduct", ui->doubleSpinBox_materialCostPerProduct->value());
  m_Settings->setValue("doubleSpinBox_productPrice", ui->doubleSpinBox_productPrice->value());
  m_Settings->setValue("doubleSpinBox_aboPricePerMonth", ui->doubleSpinBox_aboPricePerMonth->value());
  m_Settings->setValue("doubleSpinBox_deliveryTime", ui->doubleSpinBox_deliveryTime->value());
  m_Settings->setValue("doubleSpinBox_acquisitionTime", ui->doubleSpinBox_acquisitionTime->value());
  m_Settings->setValue("doubleSpinBox_supportTimePerCustomerPerMonth", ui->doubleSpinBox_supportTimePerCustomerPerMonth->value());
  m_Settings->setValue("doubleSpinBox_startupCash", ui->doubleSpinBox_startupCash->value());
  m_Settings->setValue("spinBox_numOfCustomers", ui->spinBox_numOfCustomers->value());
  m_Settings->setValue("spinBox_deliveriesPerMonth", ui->spinBox_deliveriesPerMonth->value());
  m_Settings->setValue("spinBox_newCustomersPerMonth", ui->spinBox_newCustomersPerMonth->value());
  m_Settings->setValue("spinBox_abonnents", ui->spinBox_abonnents->value());

  delete ui;
}

void MainWindow::on_pushButton_start_clicked() {
  m_StepTimer->start();
}

void MainWindow::Slot_StepTimer() {
  QDate date = ui->calendarWidget->selectedDate();

  qDebug() << "Date" << date;
  date = date.addDays(1);
  ui->calendarWidget->setSelectedDate(date);
  m_numOfDays++;
  ui->lcdNumber_numberOfDays->display(QString::number(m_numOfDays));

  /** @note Versicherung */
  m_cashVirtual -= ui->doubleSpinBox_reassurance->value() / 365;


  /** @note Verwalte Anzahl Bestandskunden */
  if (date.month() != m_month) {
    m_month = date.month();
    ui->spinBox_numOfCustomers->setValue(ui->spinBox_numOfCustomers->value() + ui->spinBox_newCustomersPerMonth->value());


  }

  /** @note Akquise */
  ui->lcdNumber_neededTimeNewCustomers->display(static_cast<double>(ui->doubleSpinBox_acquisitionTime->value() * ui->spinBox_newCustomersPerMonth->value() / m_weeksPerMonth));

  /** @note Betreuung Bestandskunden */
  ui->lcdNumber_neededTimeCustomers->display(static_cast<double>(ui->doubleSpinBox_supportTimePerCustomerPerMonth->value() * ui->spinBox_numOfCustomers->value() / m_weeksPerMonth));

  /** @note Packen */
  ui->lcdNumber_neededTimeForPacking->display(static_cast<double>(ui->doubleSpinBox_deliveryTime->value() * ui->spinBox_deliveriesPerMonth->value() / m_weeksPerMonth));


  /** @note Gewinn */
  /** @note Kaufen eines Produktes */

  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Warenlager,
                                   en_Accounts::en_Account_Verbindlichkeiten,
                                   ui->doubleSpinBox_materialCostPerProduct->value());

  /** @note Verkaufen eines Produktes */

  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Umsatzerloese,
                                   en_Accounts::en_Account_Warenlager,
                                   ui->doubleSpinBox_materialCostPerProduct->value());
#if 1
  m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Bank,
                                   en_Accounts::en_Account_Umsatzerloese,
                                   ui->doubleSpinBox_productPrice->value());
#endif

  /** @note Versicherungen immer am 1. des Jahres */

  if ((1 == ui->calendarWidget->selectedDate().month())
      && (1 == ui->calendarWidget->selectedDate().day()))
  {
    m_accountManager.Slot_SendFromTo(en_Accounts::en_Account_Versicherungen,
                                     en_Accounts::en_Account_Bank,
                                     ui->doubleSpinBox_reassurance->value());
  }

  QString cashString = QString::number(m_cashVirtual, 'f', 2);
  ui->lcdNumber_cashVirtual->display(cashString);
}

void MainWindow::on_pushButton_stop_clicked()
{
  m_StepTimer->stop();
}

void MainWindow::on_pushButton_reset_clicked()
{
  m_cashVirtual = ui->doubleSpinBox_startupCash->value();
  ui->lcdNumber_cashVirtual->display(m_cashVirtual);

  ui->lcdNumber_cash->display(ui->doubleSpinBox_startupCash->value());
}

void MainWindow::on_pushButton_finish_clicked()
{
  m_accountManager.Slot_TriggerFinish();
}

void MainWindow::on_pushButton_carryForward_clicked()
{
  m_accountManager.Slot_CarryForward();
}
