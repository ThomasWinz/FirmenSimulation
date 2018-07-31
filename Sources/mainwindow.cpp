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



  Slot_NewAccount_Active("Büro- und Geschäftsausstattung",
                         100.0);
  Slot_NewAccount_Active("Bank",
                         200.0);

  Slot_NewAccount_Passive("Eigenkapital",
                         140.0);

  Slot_NewAccount_Passive("Verbindlichkeiten",
                         160.0);

  Slot_NewAccount_Aufwand("Löhne",
                         140.0);

  Slot_NewAccount_Aufwand("Miete",
                         0.0);

  Slot_NewAccount_Ertrag("Umsatzerlöse",
                         0.0);

  /** Guv - Gewinn und Verlust */
  Slot_NewAccount_Abschluss("GUV",
                            0.0);

//  m_accountBilanz->Slot_AddRight("EK",
//                               140.0);
//  m_accountBilanz->Slot_AddRight("VB",
//                               160.0);

  m_accountManager.Slot_SendFromTo("Büro- und Geschäftsausstattung",
                                   "Verbindlichkeiten",
                                   50.0);
  m_accountManager.Slot_SendFromTo("Löhne",
                                   "Bank",
                                   30.0);
  m_accountManager.Slot_SendFromTo("Miete",
                                   "Bank",
                                   20.0);
  m_accountManager.Slot_SendFromTo("Bank",
                                   "Umsatzerlöse",
                                   90.0);
}

void MainWindow::Slot_NewAccount_Active(const QString& title,
                                        double value) {
  m_accountManager.Slot_RegisterAccount(title,
                                         "Soll",
                                         "Haben",
                                        FT_Account::en_AccountTypes::en_AccountType_Activa);
}

void MainWindow::Slot_NewAccount_Passive(const QString &title, double value) {
  m_accountManager.Slot_RegisterAccount(title,
                                         "Soll",
                                         "Haben",
                                        FT_Account::en_AccountTypes::en_AccountType_Passiva);
}

void MainWindow::Slot_NewAccount_Aufwand(const QString &title, double value) {
  m_accountManager.Slot_RegisterAccount(title,
                                         "Soll",
                                         "Haben",
                                         FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto);
}

void MainWindow::Slot_NewAccount_Ertrag(const QString &title, double value) {
  m_accountManager.Slot_RegisterAccount(title,
                                         "Soll",
                                         "Haben",
                                         FT_Account::en_AccountTypes::en_AccountType_Ertragskonto);
}

void MainWindow::Slot_NewAccount_Abschluss(const QString& title,
                               double value) {
  m_accountManager.Slot_RegisterAccount(title,
                                         "Soll",
                                         "Haben",
                                         FT_Account::en_AccountTypes::en_AccountType_Abschlusskonto);
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
  m_cashVirtual += ((ui->doubleSpinBox_productPrice->value() - ui->doubleSpinBox_materialCostPerProduct->value()) * ui->spinBox_deliveriesPerMonth->value()) / date.daysInMonth();


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
