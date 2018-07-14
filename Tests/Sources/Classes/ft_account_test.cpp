#include "gtest/gtest.h"
#include <QString>

#include "../Sources/Classes/ft_account.h"
#include "ui_ft_account.h"


class Ft_Account_Test : public ::testing::Test {
 public:
  Ft_Account_Test() {

  }
  FT_Account m_Account;
};

/** @note
* void FT_Account::Slot_SetTitles(const QString &titleTop,
*                                 const QString &titleLeft,
*                                 const QString &titleRight)
*/
TEST_F(Ft_Account_Test, Slot_SetTitles) {
  struct st_Test {
    QString titleTopGiven;
    QString titleLeftGiven;
    QString titleRightGiven;
  };

  const uint32_t numOfTests = 1;
  st_Test tests[numOfTests] = {
    {
      "12Testtitle!23",  /* titleTopGiven */
      "65Testtitle!45",  /* titleLeftGiven */
      "ayay12Testtitle!67",  /* titleRightGiven */
    }
  };

  for (uint32_t i = 0; numOfTests > i; i++) {
    QString titleTopGiven = tests[i].titleTopGiven;
    QString titleLeftGiven = tests[i].titleLeftGiven;
    QString titleRightGiven = tests[i].titleRightGiven;

    m_Account.Slot_SetTitles(titleTopGiven,
                             titleLeftGiven,
                             titleRightGiven);

    EXPECT_EQ(m_Account.Get_ui()->label_titleTop->text(),
              titleTopGiven);
  }
}
