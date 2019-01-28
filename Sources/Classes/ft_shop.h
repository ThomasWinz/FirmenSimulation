#ifndef FT_SHOP_H
#define FT_SHOP_H

#include <QObject>

class FT_Shop : public QObject
{
  Q_OBJECT
public:
  explicit FT_Shop(int32_t accountIndex_Umsatzerloese,
                   int32_t accountIndex_Warenlager,
                   int32_t accountIndex_Bank,
                   int32_t accountIndex_Verbindlichkeiten,
                   QObject *parent = nullptr);

signals:
  void Signal_SendFromTo(int32_t indexSource,
                         int32_t indexTarget,
                         uint32_t valueCents);
  void Signal_ProductSold(uint64_t valueCents);
  void Signal_Wareneinkauf(uint64_t valueCents);

public slots:
  void Slot_SellProduct(void);

  void Slot_SetMaterialCosts(uint32_t valueCents);
  void Slot_SetProductPrice(uint32_t valueCents);

  void Slot_SetMaterialCosts(double valueEuro);
  void Slot_SetProductPrice(double valueEuro);

private:
  uint32_t m_materialCostPerProduct_Cents = 0;
  uint32_t m_productPrice_Cents = 0;

  int32_t m_accountIndex_Umsatzerloese = -1;
  int32_t m_accountIndex_Warenlager = -1;
  int32_t m_accountIndex_Bank = -1;
  int32_t m_accountIndex_Verbindlichkeiten = -1;
};

#endif // FT_SHOP_H
