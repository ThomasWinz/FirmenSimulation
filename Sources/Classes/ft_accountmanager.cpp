
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

  m_AccountList.append(newAccount);
}

void FT_AccountManager::Slot_SendFromTo(const QString &accountNameSource,
                                        const QString &accountNameTarget,
                                        double valueEuro)
{
  int32_t indexSource = -1;
  int32_t indexTarget = -1;

  for (int32_t i = 0; m_AccountList.count() > i; i++) {
    QString accountName = m_AccountList[i]->Get_Title();
    if (accountNameSource == accountName) {
      indexSource = i;
    }
    if (accountNameTarget == accountName) {
      indexTarget = i;
    }
  }

  bool failure = false;
  if (-1 == indexSource) {
    /** @note Source not found */
    qDebug() << "Did not find source" << accountNameSource;
    failure = true;
  }
  if (-1 == indexTarget) {
    qDebug() << "Did not find target" << accountNameTarget;
    failure = true;
  }

  if (true == failure) {

  } else {
    /** @todo Column depending on accountType! */
    m_AccountList[indexSource]->Slot_AddValue(accountNameTarget,
                                              valueEuro,
                                              FT_Account::en_Columns::Column_Left);

    m_AccountList[indexTarget]->Slot_AddValue(accountNameSource,
                                              valueEuro,
                                              FT_Account::en_Columns::Column_Left);
  }
}
