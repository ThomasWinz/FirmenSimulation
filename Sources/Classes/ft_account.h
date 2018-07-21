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
  QString Get_Title(void);

  enum en_AccountTypes{
    en_AccountType_Bilanz,
    en_AccountType_Activa,
    en_AccountType_Passiva,
    en_AccountType_Aufwandskonto,
    en_AccountType_Erloeskonto
  };

  enum en_Columns {
    Column_Left = 0,
    Column_Right,
    sizeof_en_Columns
  };
signals:
  void Signal_AccountSumChanged(double valueEuro,
                                en_Columns column);
public slots:
  void Slot_SetTitles(const QString& titleTop,
                      const QString& titleLeft,
                      const QString& titleRight);

  void Slot_AddLeft(const QString& title,
                    double valueEuro);
  void Slot_AddRight(const QString& title,
                     double valueEuro);
  void Slot_SetAccountType(en_AccountTypes type);

  void Slot_AccountSumChanged(double valueEuro,
                              en_Columns column);


#ifdef UNITTESTS
  virtual
#else
private slots:
#endif
  void Slot_AddValue(const QString& title,
                     double valueEuro,
                     en_Columns column);
  void on_pushButton_enterLeft_clicked();

#ifdef UNITTESTS
public:
#else

private:
#endif
  Ui::FT_Account *ui;

  const QString m_ColumnNames[en_Columns::sizeof_en_Columns] = {
    "Name",
    "Wert"
  };

  QRgb m_ColorGreen = 0xC2D299;
  QRgb m_ColorRed = 0xDD9D92;
  QString m_stylesheetTable = QString("QTableWidget { background-color: #%1; }");
  en_AccountTypes m_MyType = en_AccountType_Bilanz;

  QTableWidget* m_tables[en_Columns::sizeof_en_Columns];
  QLineEdit* m_lineEdits[en_Columns::sizeof_en_Columns];

};

#endif // FT_ACCOUNT_H
