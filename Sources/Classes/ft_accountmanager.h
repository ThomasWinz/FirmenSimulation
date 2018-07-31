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

  enum en_bookingType {
    en_bookingType_standard = 0,
    en_bookingType_guv,
  };

  struct st_booking {
    QString m_accountNameSource;
    QString m_accountNameTarget;
    double m_valueEuro;
    uint32_t m_id;
    en_bookingType m_type = en_bookingType::en_bookingType_standard;
  };

public slots:
  void Slot_RegisterAccount(const QString& accountName,
                            const QString& leftText,
                            const QString& rightText,
                            FT_Account::en_AccountTypes accountType);
  void Slot_SendFromTo(const st_booking &booking);
  void Slot_SendFromTo(const QString& accountNameSource,
                       const QString& accountNameTarget,
                       double valueEuro);
  void Slot_Finish(double valueLeft,
                   double valueRight);
  void Slot_TriggerFinish(void);

#ifdef UNITTESTS
public:
#else
private:
#endif
  QList<FT_Account*> m_AccountList;
  uint32_t m_currentID = 0;

private slots:
  void Slot_SendFromTo_Add(const st_booking &booking,
                           int32_t indexSource,
                           int32_t indexTarget);
};

#endif // FT_ACCOUNTMANAGER_H
