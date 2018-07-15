#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <QString>

#include "../Sources/Classes/ft_account.h"
#include "ui_ft_account.h"

class Ft_Account_Override : public FT_Account {
 public:
  MOCK_METHOD4(Slot_AddValue, void(
                             QTableWidget*,
                             QLineEdit*,
                             const QString&,
                             double));
};

class Ft_Account_Test : public ::testing::Test {
 public:
  Ft_Account_Test() {

  }
  FT_Account m_Account;
  Ft_Account_Override m_Account_Override;
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
    EXPECT_EQ(m_Account.Get_ui()->label_titleLeft->text(),
              titleLeftGiven);
    EXPECT_EQ(m_Account.Get_ui()->label_titleRight->text(),
              titleRightGiven);

    EXPECT_EQ(m_Account.windowTitle(),
              titleTopGiven);
  }
}

TEST_F(Ft_Account_Test, Slot_AddLeft) {
  QTableWidget* tableGiven = m_Account_Override.Get_ui()->tableWidget_left;
  QLineEdit* lineEditGiven = m_Account_Override.Get_ui()->lineEdit_sumLeft;
  QString titleGiven = "testTitleGiven1337";
  double valueEuroGiven = 126564235.123542;
  EXPECT_CALL(m_Account_Override,
              Slot_AddValue(tableGiven,
                            lineEditGiven,
                            titleGiven,
                            valueEuroGiven));
  m_Account_Override.Slot_AddLeft(titleGiven,
                                  valueEuroGiven);

}

TEST_F(Ft_Account_Test, Slot_AddRight) {
  QTableWidget* tableGiven = m_Account_Override.Get_ui()->tableWidget_right;
  QLineEdit* lineEditGiven = m_Account_Override.Get_ui()->lineEdit_sumRight;
  QString titleGiven = "testTitleGiven1337";
  double valueEuroGiven = 126564235.123542;
  EXPECT_CALL(m_Account_Override,
              Slot_AddValue(tableGiven,
                            lineEditGiven,
                            titleGiven,
                            valueEuroGiven));
  m_Account_Override.Slot_AddRight(titleGiven,
                                  valueEuroGiven);
}

/** @note
 *  void Slot_AddValue(QTableWidget* table,
                       QLineEdit* lineEdit,
                       const QString& title,
                       double valueEuro); */
TEST_F(Ft_Account_Test, Slot_AddValue) {
  QTableWidget* tableGiven = new QTableWidget(NULL);
  QLineEdit* lineEditGiven = new QLineEdit(NULL);
  QString titleGiven = "testTitleGiven1337";
  double valueEuroGiven = 126564235.123542;

  EXPECT_EQ(tableGiven->rowCount(),
            0);
  EXPECT_EQ(lineEditGiven->text().toDouble(),
            0.0);

  m_Account.Slot_AddValue(tableGiven,
                          lineEditGiven,
                          titleGiven,
                          valueEuroGiven);

  EXPECT_EQ(tableGiven->rowCount(),
            1);

  QString textCalculated = lineEditGiven->text();
  QString textExpected = "126564235.12";
  EXPECT_EQ(textCalculated,
              textExpected);
}
