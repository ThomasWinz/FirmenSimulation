#ifndef FT_ACCOUNTMANAGER_H
#define FT_ACCOUNTMANAGER_H

#include <QObject>
#include <QList>
#include <QtWidgets/QVBoxLayout>
#include <QComboBox>
#include <QDate>

#include "ft_account.h"

namespace Ui {
class FT_AccountManager;
}

class FT_AccountManager : public QWidget
{
  Q_OBJECT
public:
  explicit FT_AccountManager(QWidget *parent = nullptr);

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

  virtual void resizeEvent(QResizeEvent* event);

  FT_Account* GetAccountByIndex(int32_t index);

signals:
  void Signal_ActivePassivaChanged(double valueEuro,
                                FT_Account::en_Columns column);
public slots:
  void Slot_RegisterAccount(const QString& accountName,
                            const QString& leftText,
                            const QString& rightText,
                            FT_Account::en_AccountTypes accountType,
                            FT_Account* bilanzAccount = NULL);
  void Slot_SendFromTo(const st_booking &booking);
  void Slot_SendFromTo(const QString& accountNameSource,
                       const QString& accountNameTarget,
                       double valueEuro);
  void Slot_SendFromTo(int32_t indexSource,
                       int32_t indexTarget,
                       double valueEuro);
  void Slot_SendFromTo(int32_t indexSource,
                       int32_t indexTarget,
                       uint32_t valueCents);

  void Slot_SetDate(QDate currentDate);

  void Slot_Finish(double valueLeft,
                   double valueRight);

  void Slot_Finish_AufwandErtrag(double valueLeft,
                                 double valueRight);

  void Slot_Finish_Abschluss(double valueLeft,
                             double valueRight);


  void Slot_Finish_ActivaPassiva(double valueLeft,
                                 double valueRight);

  void Slot_SetEBK(int32_t index,
                   double value);


  void Slot_TriggerFinish(void);

  void Slot_CarryForward(void);

  void Slot_Init(void);

#ifdef UNITTESTS
public:
#else
private:
#endif
  FT_Account* m_bilanzAccount = NULL;
  Ui::FT_AccountManager* ui;
  QList<FT_Account*> m_AccountList;
  uint32_t m_currentID = 0;

  QVBoxLayout* m_layoutLeft = NULL;
  QVBoxLayout* m_layoutRight = NULL;
  int32_t m_indexesShown[2] = { -1, -1 };
  QDate m_currentDate;
private slots:
  void Slot_SendFromTo_Add(const st_booking &booking,
                           int32_t indexSource,
                           int32_t indexTarget);
  void Slot_ShowInWidget(QWidget* widget, int32_t index);
  void Slot_UpdateCombobox(QComboBox* combobox,
                           const QString& title);

  void on_comboBox_accountLeft_activated(int index);
  void on_comboBox_accountRight_activated(int index);
  void on_pushButton_toLeft_clicked();
  void on_pushButton_toRight_clicked();
};

#endif // FT_ACCOUNTMANAGER_H
