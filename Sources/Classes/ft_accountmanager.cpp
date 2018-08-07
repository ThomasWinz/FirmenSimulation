
#include <QDebug>

#include "ui_ft_accountmanager.h"
#include "ft_accountmanager.h"

FT_AccountManager::FT_AccountManager(QWidget *parent) : QWidget(parent),
  ui(new Ui::FT_AccountManager)
{
  ui->setupUi(this);

  m_layoutLeft = ui->verticalLayout;
  m_layoutRight = ui->verticalLayout_2;

  connect(ui->pushButton_finish, &QPushButton::clicked,
          this, &FT_AccountManager::Slot_TriggerFinish);
}

void FT_AccountManager::resizeEvent(QResizeEvent *event)
{
  if (-1 != m_indexesShown[0])
  {
    m_AccountList[m_indexesShown[0]]->setGeometry(QRect(0, 0, ui->widget_contentLeft->geometry().width(), ui->widget_contentLeft->geometry().height()));
  }
  if (-1 != m_indexesShown[1])
  {
    m_AccountList[m_indexesShown[1]]->setGeometry(QRect(0, 0, ui->widget_contentRight->geometry().width(), ui->widget_contentRight->geometry().height()));
  }
}

void FT_AccountManager::Slot_RegisterAccount(const QString &accountName,
                                             const QString &leftText,
                                             const QString &rightText,
                                             FT_Account::en_AccountTypes accountType, FT_Account *bilanzAccount)
{

  FT_Account* newAccount = new FT_Account();

  newAccount->Slot_SetTitles(accountName,
                             leftText,
                             rightText);

  newAccount->Slot_SetAccountType(accountType);

  connect(newAccount, &FT_Account::Signal_Finish,
          this, &FT_AccountManager::Slot_Finish);

  m_AccountList.append(newAccount);

  Slot_UpdateCombobox(ui->comboBox_accountLeft,
                      accountName);
  Slot_UpdateCombobox(ui->comboBox_accountRight,
                      accountName);

  if (NULL == bilanzAccount)
  {

  }
  else
  {
    switch (accountType)
    {
      case FT_Account::en_AccountType_Activa:
      case FT_Account::en_AccountType_Passiva:
        connect(newAccount, &FT_Account::Signal_AccountSumChanged,
                bilanzAccount, &FT_Account::Slot_AccountSumChanged);
        break;
      default:
        break;
    }
  }
}

void FT_AccountManager::Slot_SendFromTo(const FT_AccountManager::st_booking& booking)
{
  int32_t indexSource = -1;
  int32_t indexTarget = -1;

  for (int32_t i = 0; m_AccountList.count() > i; i++) {
    QString accountName = m_AccountList[i]->Get_Title();
    if (booking.m_accountNameSource == accountName) {
      indexSource = i;
    }
    if (booking.m_accountNameTarget == accountName) {
      indexTarget = i;
    }
  }

  bool failure = false;
  if (-1 == indexSource) {
    /** @note Source not found */
    qDebug() << "Did not find source" << booking.m_accountNameSource;
    failure = true;
  }
  if (-1 == indexTarget) {
    qDebug() << "Did not find target" << booking.m_accountNameTarget;
    failure = true;
  }

  if (true == failure) {

  } else {
    Slot_SendFromTo_Add(booking,
                        indexSource,
                        indexTarget);
  }
}

void FT_AccountManager::Slot_SendFromTo(const QString &accountNameSource,
                                        const QString &accountNameTarget,
                                        double valueEuro)
{
  st_booking booking;

  booking.m_accountNameSource = accountNameSource;
  booking.m_accountNameTarget = accountNameTarget;
  booking.m_valueEuro = valueEuro;

  Slot_SendFromTo(booking);
}

void FT_AccountManager::Slot_SendFromTo(int32_t indexSource,
                                        int32_t indexTarget,
                                        double valueEuro)
{
  st_booking booking;

  booking.m_accountNameSource = m_AccountList[indexSource]->Get_Title();
  booking.m_accountNameTarget = m_AccountList[indexTarget]->Get_Title();
  booking.m_valueEuro = valueEuro;

  Slot_SendFromTo_Add(booking,
                      indexSource,
                      indexTarget);
  return;
}

void FT_AccountManager::Slot_Finish(double valueLeft, double valueRight)
{
  st_booking booking;
  double difference = valueLeft - valueRight;
  difference = fabs(difference);
  if (valueLeft > valueRight) {
    /** @note Buchung links nach rechts */
    booking.m_accountNameSource = "GUV";
    booking.m_accountNameTarget = reinterpret_cast<FT_Account*>(sender())->Get_Title();
    booking.m_valueEuro = difference;
    booking.m_type = en_bookingType::en_bookingType_guv;
    Slot_SendFromTo(booking);
  } else if (valueRight > valueLeft) {
    /** @note Buchung rechts nach links */
    booking.m_accountNameSource = reinterpret_cast<FT_Account*>(sender())->Get_Title();
    booking.m_accountNameTarget = "GUV";
    booking.m_valueEuro = difference;
    booking.m_type = en_bookingType::en_bookingType_guv;
    Slot_SendFromTo(booking);
  } else {
    /** keine Buchung */
  }
}

void FT_AccountManager::Slot_TriggerFinish()
{
  for (int32_t i = 0; m_AccountList.count() > i; i++) {
    switch (m_AccountList[i]->Get_Type()) {
    case FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto:
    case FT_Account::en_AccountTypes::en_AccountType_Ertragskonto:
      m_AccountList[i]->Slot_Finish();
      break;
    default:
      break;
    }
  }
}

void FT_AccountManager::Slot_Init()
{
  on_comboBox_accountLeft_activated(0);
  on_comboBox_accountRight_activated(1);
}

void FT_AccountManager::Slot_SendFromTo_Add(const FT_AccountManager::st_booking &booking, int32_t indexSource, int32_t indexTarget)
{
  QString textSource = "";
  QString textTarget = "";
  switch(booking.m_type) {
  case en_bookingType::en_bookingType_guv:
    textSource = booking.m_accountNameSource;
    textTarget = booking.m_accountNameTarget;
    break;
  default:
    m_currentID++;
    textSource = QString::number(m_currentID);
    textTarget = QString::number(m_currentID);
    break;
  }


  /** @todo Column depending on accountType! */
  m_AccountList[indexSource]->Slot_AddValue(textTarget,
                                            booking.m_valueEuro,
                                            FT_Account::en_Columns::Column_Left);

  m_AccountList[indexTarget]->Slot_AddValue(textSource,
                                            booking.m_valueEuro,
                                            FT_Account::en_Columns::Column_Right);
}

void FT_AccountManager::Slot_ShowInWidget(QWidget* widget, int32_t index)
{
  for (int32_t i = 0; m_AccountList.count() > i; i++)
  {
    if (m_indexesShown[0] == i || m_indexesShown[1] == i)
    {

    }
    else
    {
      m_AccountList[i]->hide();
    }
  }
  m_AccountList[index]->setParent(widget);
  int32_t width = widget->geometry().width();
  int32_t height = widget->geometry().height();
  m_AccountList[index]->setGeometry(QRect(0, 0, width, height));
  m_AccountList[index]->show();
}

void FT_AccountManager::Slot_UpdateCombobox(QComboBox* combobox,
                                            const QString& title)
{
  combobox->insertItem(combobox->count(), title);
}


void FT_AccountManager::on_comboBox_accountLeft_activated(int index)
{
  if (m_indexesShown[1] == index)
  {
    m_indexesShown[1] = -1;
  }
  m_indexesShown[0] = index;
  Slot_ShowInWidget(ui->widget_contentLeft,
                    index);
}

void FT_AccountManager::on_comboBox_accountRight_activated(int index)
{
  if (m_indexesShown[0] == index)
  {
    m_indexesShown[0] = -1;
  }
  m_indexesShown[1] = index;
  Slot_ShowInWidget(ui->widget_contentRight,
                    index);
}


void FT_AccountManager::on_pushButton_toLeft_clicked()
{
  Slot_SendFromTo(ui->comboBox_accountRight->currentIndex(),
                  ui->comboBox_accountLeft->currentIndex(),
                  ui->doubleSpinBox_value->value());
}

void FT_AccountManager::on_pushButton_toRight_clicked()
{
  Slot_SendFromTo(ui->comboBox_accountLeft->currentIndex(),
                  ui->comboBox_accountRight->currentIndex(),
                  ui->doubleSpinBox_value->value());
}
