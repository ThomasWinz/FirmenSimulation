#ifndef FT_CUSTOMER_TEST_H
#define FT_CUSTOMER_TEST_H

#include <QObject>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Sources/Classes/ft_customer.h"



class Ft_Customer_Test : public QObject, public ::testing::Test
{
  Q_OBJECT
 public:

  Ft_Customer_Test();
  FT_Customer m_customer;
 public:
  MOCK_METHOD0(Mock_BuyProduct, void());

};


#endif  // FT_CUSTOMER_TEST_H
