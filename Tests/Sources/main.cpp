#include <QApplication>

#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  int32_t testResult = RUN_ALL_TESTS();

  return testResult;
}
