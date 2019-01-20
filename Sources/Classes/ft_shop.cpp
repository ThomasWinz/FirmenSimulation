#include "ft_shop.h"

FT_Shop::FT_Shop(int32_t accountIndex_Umsatzerloese,
                 int32_t accountIndex_Warenlager,
                 int32_t accountIndex_Bank,
                 int32_t accountIndex_Verbindlichkeiten,
                 QObject *parent) : QObject(parent)
{
  m_accountIndex_Umsatzerloese = accountIndex_Umsatzerloese;
  m_accountIndex_Warenlager = accountIndex_Warenlager;
  m_accountIndex_Bank = accountIndex_Bank;
  m_accountIndex_Verbindlichkeiten = accountIndex_Verbindlichkeiten;

  return;
}

void FT_Shop::Slot_SellProduct()
{
  /** @note Produkt ins Warenlager kaufen */
  emit Signal_SendFromTo(m_accountIndex_Warenlager,
                         m_accountIndex_Verbindlichkeiten,
                         m_materialCostPerProduct_Cents);

  /** @note Produkt aus Warenlager verkaufen */
  emit Signal_SendFromTo(m_accountIndex_Umsatzerloese,
                         m_accountIndex_Warenlager,
                         m_materialCostPerProduct_Cents);

  /** @note Umsatzerloese auf Bankkonto buchen */
  emit Signal_SendFromTo(m_accountIndex_Bank,
                         m_accountIndex_Umsatzerloese,
                         m_productPrice_Cents);

  emit Signal_ProductSold(m_productPrice_Cents);
}

void FT_Shop::Slot_SetMaterialCosts(uint32_t valueCents)
{
  m_materialCostPerProduct_Cents = valueCents;
}

void FT_Shop::Slot_SetProductPrice(uint32_t valueCents)
{
  m_productPrice_Cents = valueCents;
}

void FT_Shop::Slot_SetMaterialCosts(double valueEuro)
{
  m_materialCostPerProduct_Cents = 100.0 * valueEuro;
}

void FT_Shop::Slot_SetProductPrice(double valueEuro)
{
  m_productPrice_Cents = 100.0 * valueEuro;
}
