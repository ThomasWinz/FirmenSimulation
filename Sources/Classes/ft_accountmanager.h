#ifndef FT_ACCOUNTMANAGER_H
#define FT_ACCOUNTMANAGER_H

#include <QObject>
#include <QList>

#include "ft_account.h"


class FT_AccountManager : public QObject
{
  Q_OBJECT
public:
  explicit FT_AccountManager(QObject *parent = nullptr);

public slots:
  void Slot_RegisterAccount(const QString& accountName,
                            const QString& leftText,
                            const QString& rightText,
                            FT_Account::en_AccountTypes accountType);
  void Slot_SendFromTo(const QString& accountNameSource,
                       const QString& accountNameTarget,
                       double valueEuro);

#ifdef UNITTESTS
public:
#else
private:
#endif
  QList<FT_Account*> m_AccountList;
};

#endif // FT_ACCOUNTMANAGER_H
