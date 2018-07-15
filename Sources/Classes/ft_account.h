#ifndef FT_ACCOUNT_H
#define FT_ACCOUNT_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QRgb>

namespace Ui {
class FT_Account;
}

class FT_Account : public QWidget
{
  Q_OBJECT

public:
  explicit FT_Account(QWidget *parent = 0);
  ~FT_Account();
  Ui::FT_Account* Get_ui(void);

public slots:
  void Slot_SetTitles(const QString& titleTop,
                      const QString& titleLeft,
                      const QString& titleRight);

  void Slot_AddLeft(const QString& title,
                    double valueEuro);
  void Slot_AddRight(const QString& title,
                     double valueEuro);

#ifdef UNITTESTS
  virtual
#else
private slots:
#endif
  void Slot_AddValue(QTableWidget* table,
                     QLineEdit* lineEdit,
                     const QString& title,
                     double valueEuro);

#ifdef UNITTESTS
public:
#else
private:
#endif
  Ui::FT_Account *ui;
  enum en_Columns {
    Column_Left = 0,
    Column_Right,
    sizeof_en_Columns
  };
  const QString m_ColumnNames[en_Columns::sizeof_en_Columns] = {
    "Name",
    "Wert"
  };
//  QString stylesheeetLeft = "QTableWidget { background-color: rgb(194, 210, 153); }";
//  ui->tableWidget_left->setStyleSheet(stylesheeetLeft);
//  QString stylesheeetRight = "QTableWidget { background-color: rgb(221, 157, 146); }";

  QRgb m_ColorGreen = 0xC2D299;
  QRgb m_ColorRed = 0xDD9D92;
  QString m_stylesheetTable = QString("QTableWidget { background-color: #%1; }");


};

#endif // FT_ACCOUNT_H
