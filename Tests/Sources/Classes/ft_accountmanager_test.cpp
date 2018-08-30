#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <QString>

#include "../Sources/Classes/ft_accountmanager.h"
#include "ui_ft_account.h"

class Ft_AccountManager_Test : public ::testing::Test {
 public:
  Ft_AccountManager_Test() {

  }
  FT_AccountManager m_AccountManager;
};


TEST_F(Ft_AccountManager_Test, Slot_RegisterAccount) {

  struct st_Test {
    QString accountName;
    QString textLeft;
    QString textRight;
    FT_Account::en_AccountTypes type;
  };

  const uint32_t numOfTests = 5;
  st_Test tests[numOfTests] =
  {
    {
      "accountname4711",  // accountName
      "leftTextAnnoDazumal9321",  // leftText
      "Blablub",  // rightText
      FT_Account::en_AccountTypes::en_AccountType_Activa
    },
    {
      "accountname4711141414",  // accountName
      "leftTextAnnoDaz^1^31231umal9321",  // leftText
      "Bla1^34414blub",  // rightText
      FT_Account::en_AccountTypes::en_AccountType_Passiva
    },
    {
      "asdgsdgsgsgsgsdaccountname4711",  // accountName
      "adfsfleftTextAnnoDazumal9321",  // leftText
      "adfdsdfsBlablub",  // rightText
      FT_Account::en_AccountTypes::en_AccountType_Aufwandskonto
    },
    {
      "asgdsdgasaccountname4711",  // accountName
      "leftTextAnasdgsdgsdnoDazumal9321",  // leftText
      "asdgsdgBlablub",  // rightText
      FT_Account::en_AccountTypes::en_AccountType_Ertragskonto
    },
    {
      "accountngggsafgsdame4711",  // accountName
      "leftTeasdfsdfgxtAnnoDazumal9321",  // leftText
      "Blabasdfslubasdgdgsd",  // rightText
      FT_Account::en_AccountTypes::en_AccountType_Bilanz
    }
  };

  for (uint32_t i = 0; numOfTests > i; i++) {
    m_AccountManager.Slot_RegisterAccount(tests[i].accountName,
                                          tests[i].textLeft,
                                          tests[i].textRight,
                                          tests[i].type);
  }

  for (uint32_t i = 0; numOfTests > i; i++) {
    EXPECT_EQ(m_AccountManager.m_AccountList.at(i)->ui->label_titleTop->text(),
              tests[i].accountName);

    EXPECT_EQ(m_AccountManager.m_AccountList.at(i)->ui->label_titleLeft->text(),
              tests[i].textLeft);

    EXPECT_EQ(m_AccountManager.m_AccountList.at(i)->ui->label_titleRight->text(),
              tests[i].textRight);

    EXPECT_EQ(m_AccountManager.m_AccountList.at(i)->m_MyType,
              tests[i].type);
  }
}

TEST_F(Ft_AccountManager_Test, Slot_SendFromTo) {
  struct st_Test {
    QString accountNameSource;
    QString accountNameTarget;
    FT_Account::en_AccountTypes typeSource;
    FT_Account::en_AccountTypes typeTarget;
    double value;
  };

  const uint32_t numOfTests = 1;

  st_Test tests[numOfTests] = {
    "sourceTest1",  // accountNameSource
    "targetTest2",  // accountNameTarget
    FT_Account::en_AccountTypes::en_AccountType_Ertragskonto,  // typeSource
    FT_Account::en_AccountTypes::en_AccountType_Activa,  // typeTarget
    10.5
  };

  for (uint32_t i = 0; numOfTests > i; i++) {
    m_AccountManager.Slot_RegisterAccount(tests[i].accountNameSource,
                                          "",
                                          "",
                                          tests[i].typeSource);

    m_AccountManager.Slot_RegisterAccount(tests[i].accountNameTarget,
                                          "",
                                          "",
                                          tests[i].typeTarget);

    m_AccountManager.Slot_SendFromTo(tests[i].accountNameSource,
                                     tests[i].accountNameTarget,
                                     tests[i].value);

    /** @todo Missing expectations! */
  }
}
