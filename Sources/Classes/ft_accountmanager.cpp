
#include <QDebug>

#include "ft_accountmanager.h"

FT_AccountManager::FT_AccountManager(QObject *parent) : QObject(parent)
{

}

void FT_AccountManager::Slot_RegisterAccount(const QString &accountName,
                                             const QString &leftText,
                                             const QString &rightText,
                                             FT_Account::en_AccountTypes accountType)
{

  FT_Account* newAccount = new FT_Account();

  newAccount->Slot_SetTitles(accountName,
                             leftText,
                             rightText);

  newAccount->Slot_SetAccountType(accountType);

  newAccount->show();

  connect(newAccount, &FT_Account::Signal_Finish,
          this, &FT_AccountManager::Slot_Finish);

  m_AccountList.append(newAccount);
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
