#ifndef FT_LIQUIDITY_H
#define FT_LIQUIDITY_H

#include <inttypes.h>
#include <QDate>
#include <QObject>

class ft_liquidity : public QObject
{
  Q_OBJECT
public:
  ft_liquidity();
  void EnterBankMonth(QDate date, uint64_t moneyCent);

  struct Entry
  {
    QDate m_date;
    uint64_t m_moneyCent = 0;
    uint64_t m_bezahlteRechnungenCent = 0;
  };
  QList<Entry>* GetEntryList(void);

public slots:
  void Slot_ProductSold(uint64_t valueCents);
private:
  QList<Entry> m_EntryList;
};

#endif // FT_LIQUIDITY_H
