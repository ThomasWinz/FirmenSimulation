#ifndef FT_CUSTOMER_H
#define FT_CUSTOMER_H

#include <QWidget>
#include <QDate>

namespace Ui {
class ft_customer;
}

class FT_Customer : public QWidget
{
  Q_OBJECT

public:
  explicit FT_Customer(int32_t numOfProductsPerMonth,
                       QWidget *parent = 0);
  ~FT_Customer();

public slots:
  void Slot_SetDate(QDate currentDate);

signals:
  void Signal_BuyProduct(void);
  void Signal_PayBill(uint32_t money_cents);

#ifdef UNITTESTS
public:
#else
private:
#endif
  Ui::ft_customer *ui;
  bool m_abo = false;
  QString m_name = "default name";
  uint32_t m_numOfProductsPerMonth = 0;

  QList<QDate> m_ProductBuyDays;
  void Calc_ProductBuyDays(QDate currentDate);
};

#endif // FT_CUSTOMER_H
