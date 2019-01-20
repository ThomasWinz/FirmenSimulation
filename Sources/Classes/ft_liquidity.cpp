#include "ft_liquidity.h"

ft_liquidity::ft_liquidity() : QObject()
{

}

void ft_liquidity::EnterBankMonth(QDate date, uint64_t moneyCent)
{
  Entry entry;
  entry.m_date = date;
  entry.m_moneyCent = moneyCent;

  m_EntryList.append(entry);
}

QList<ft_liquidity::Entry> *ft_liquidity::GetEntryList()
{
  return &this->m_EntryList;
}

void ft_liquidity::Slot_ProductSold(uint64_t valueCents)
{
  if (0 < m_EntryList.count()) {
    m_EntryList.last().m_bezahlteRechnungenCent += valueCents;
  }
}
