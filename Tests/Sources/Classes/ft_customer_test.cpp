#include <QString>

#include "ft_customer_test.h"
#include "ui_ft_account.h"

Ft_Customer_Test::Ft_Customer_Test() {

}


TEST_F(Ft_Customer_Test, Calc_ProductBuyDays) {
  struct st_Test {
    QDate m_dateGiven;
    uint32_t m_numOfProductsPerMonthGiven;
    int32_t m_numOfProductsPerMonthExpected;
  };

  const uint32_t numOfTests = 1;
  st_Test tests[numOfTests];

  /** @note Test 0 */
  tests[0].m_dateGiven.setDate(2018, 8, 30);
  tests[0].m_numOfProductsPerMonthGiven = 5;
  tests[0].m_numOfProductsPerMonthExpected = tests[0].m_numOfProductsPerMonthGiven;

  for (uint32_t i = 0; numOfTests > i; i++)
  {
    this->m_customer.m_numOfProductsPerMonth = tests[i].m_numOfProductsPerMonthGiven;
    m_customer.Calc_ProductBuyDays(tests[i].m_dateGiven);

    EXPECT_EQ(this->m_customer.m_ProductBuyDays.count(),
              tests[i].m_numOfProductsPerMonthExpected);

    for (int32_t m = 0; this->m_customer.m_ProductBuyDays.count() > m; m++)
    {
      EXPECT_GE(5,
                this->m_customer.m_ProductBuyDays[m].dayOfWeek());
    }
  }
}

TEST_F(Ft_Customer_Test, Slot_SetDate) {
  struct st_Test {
    QDate m_dateGiven;
    uint32_t m_numOfProductsPerMonthGiven;
    int32_t m_numOfProductsPerMonthExpected;
    QList<QDate> m_buyDateListGiven;
    uint32_t m_callBuyExpected;
  };

  const uint32_t numOfTests = 2;
  st_Test tests[numOfTests];

  /** @note Test 0 */
  tests[0].m_dateGiven.setDate(2018, 8, 30);
  tests[0].m_numOfProductsPerMonthGiven = 5;
  tests[0].m_numOfProductsPerMonthExpected = tests[0].m_numOfProductsPerMonthGiven;
  tests[0].m_buyDateListGiven.append(QDate(2018, 8, 30));
  tests[0].m_callBuyExpected = 1;

  /** @note Test 0 */
  tests[1].m_dateGiven.setDate(2018, 8, 29);
  tests[1].m_numOfProductsPerMonthGiven = 5;
  tests[1].m_numOfProductsPerMonthExpected = tests[0].m_numOfProductsPerMonthGiven;
  tests[1].m_buyDateListGiven.append(QDate(2018, 8, 30));
  tests[1].m_callBuyExpected = 0;

  m_customer.connect(&m_customer, &FT_Customer::Signal_BuyProduct,
                     this, &Ft_Customer_Test::Mock_BuyProduct);

  for (uint32_t i = 0; numOfTests > i; i++)
  {
    m_customer.m_ProductBuyDays.clear();
    m_customer.m_ProductBuyDays.append(tests[i].m_buyDateListGiven);

    EXPECT_CALL(*this,
                Mock_BuyProduct).Times(tests[i].m_callBuyExpected);

    m_customer.Slot_SetDate(tests[i].m_dateGiven);


  }
}
