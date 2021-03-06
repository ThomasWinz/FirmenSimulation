#include <QRandomGenerator>

#include "ft_customer.h"
#include "ui_ft_customer.h"

FT_Customer::FT_Customer(int32_t numOfProductsPerMonth, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ft_customer)
{
  ui->setupUi(this);
  m_numOfProductsPerMonth = numOfProductsPerMonth;
}

FT_Customer::~FT_Customer()
{
  delete ui;
}

void FT_Customer::Slot_SetDate(QDate currentDate)
{
  if (1 == currentDate.day())
  {
    Calc_ProductBuyDays(currentDate);
  }

  if (m_ProductBuyDays.contains(currentDate))
  {
    emit Signal_BuyProduct();
  }
}

void FT_Customer::Calc_ProductBuyDays(QDate currentDate)
{
  m_ProductBuyDays.clear();
  while (m_ProductBuyDays.count() < m_numOfProductsPerMonth)
  {
    int32_t daysInMonth = currentDate.daysInMonth();
    int32_t day = QRandomGenerator::global()->bounded(1, daysInMonth);

    QDate newDate;
    newDate.setDate(currentDate.year(),
                    currentDate.month(),
                    day);
    /** @note monday to friday? */
    if (6 > newDate.dayOfWeek())
    {
      m_ProductBuyDays.append(newDate);
    }
    else
    {
      /** @note saturday and sunday invalid */
      qt_noop();
    }
  }
}
