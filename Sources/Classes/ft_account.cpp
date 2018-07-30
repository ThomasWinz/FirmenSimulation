#include "ft_account.h"
#include "ui_ft_account.h"

FT_Account::FT_Account(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FT_Account)
{
  ui->setupUi(this);

  for (uint32_t i = 0; en_Columns::sizeof_en_Columns > i; i++) {
    ui->tableWidget_left->horizontalHeaderItem(i)->setText(m_ColumnNames[i]);
    ui->tableWidget_right->horizontalHeaderItem(i)->setText(m_ColumnNames[i]);
  }

  ui->tableWidget_left->setStyleSheet(m_stylesheetTable.arg(QString::number(m_ColorGreen, 16)));
  ui->tableWidget_right->setStyleSheet(m_stylesheetTable.arg(QString::number(m_ColorRed, 16)));


  m_tables[en_Columns::Column_Left] = ui->tableWidget_left;
  m_tables[en_Columns::Column_Right] = ui->tableWidget_right;


  m_lineEdits[en_Columns::Column_Left] = ui->lineEdit_sumLeft;
  m_lineEdits[en_Columns::Column_Right] = ui->lineEdit_sumRight;

  return;
}

FT_Account::~FT_Account()
{
  delete ui;

  return;
}

Ui::FT_Account *FT_Account::Get_ui()
{
  return ui;
}

QString FT_Account::Get_Title()
{
  return ui->label_titleTop->text();
}

void FT_Account::Slot_SetTitles(const QString &titleTop,
                                const QString &titleLeft,
                                const QString &titleRight) {
  this->setWindowTitle(titleTop);
  ui->label_titleTop->setText(titleTop);
  ui->label_titleLeft->setText(titleLeft);
  ui->label_titleRight->setText(titleRight);

  int32_t width = ui->tableWidget_left->width();

  ui->tableWidget_left->setColumnWidth(en_Columns::Column_Left, width * 0.7);
  ui->tableWidget_right->setColumnWidth(en_Columns::Column_Left, width * 0.7);

  ui->tableWidget_left->setColumnWidth(en_Columns::Column_Right, width * 0.2);
  ui->tableWidget_right->setColumnWidth(en_Columns::Column_Right, width * 0.2);

  return;
}

void FT_Account::Slot_AddLeft(const QString &title,
                              double valueEuro) {
  Slot_AddValue(title,
                valueEuro,
                en_Columns::Column_Left);

  return;
}

void FT_Account::Slot_AddRight(const QString &title,
                               double valueEuro) {
  Slot_AddValue(title,
                valueEuro,
                en_Columns::Column_Right);

  return;
}

void FT_Account::Slot_SetAccountType(FT_Account::en_AccountTypes accountType)
{
  m_MyType = accountType;

  return;
}


void FT_Account::Slot_AccountSumChanged(double valueEuro,
                                        FT_Account::en_Columns column)
{
  FT_Account* accountSender = reinterpret_cast<FT_Account*>(sender());
  QString senderTitle = accountSender->Get_Title();

  QTableWidget* table = NULL;


  if (en_Columns::sizeof_en_Columns > column) {
    table = m_tables[column];

    bool entryFound = false;

    for (int32_t i = 0; table->rowCount() > i; i++) {
      if (table->item(i, en_Columns::Column_Left)->text() == senderTitle) {
        QTableWidgetItem* item = table->item(i, en_Columns::Column_Right);
        if (NULL == item) {

        } else {
          QString textValue = item->text();
          double newValue = textValue.toDouble() + valueEuro;

          table->item(i, en_Columns::Column_Right)->setText(QString::number(newValue, 'f', 2));
        }
        entryFound = true;
        i = table->rowCount();
      }  //  if (table->item
    }  // for

    if (true == entryFound){
      Slot_UpdateSum(column);
    } else {
      Slot_AddValue(senderTitle,
                    valueEuro,
                    column);
    }
  }
}

void FT_Account::Slot_UpdateSum(en_Columns column) {
  QTableWidget* table = NULL;
  QLineEdit* lineEdit = NULL;

  switch (column) {
  case en_Columns::Column_Left:
  case en_Columns::Column_Right:
    table = m_tables[column];
    lineEdit = m_lineEdits[column];
    break;
  default:
    break;
  }

  double newSum = 0.0;
  for (int32_t i = 0; table->rowCount() > i; i++) {
    newSum += table->item(i, Column_Right)->text().toDouble();
  }

  QString valueSumText = QString::number(newSum, 'f', 2);
  lineEdit->setText(valueSumText);
}

void FT_Account::Slot_AddValue(const QString &title,
                               double valueEuro,
                               en_Columns column) {
  QTableWidgetItem* itemLeft = new QTableWidgetItem(title);
  QTableWidgetItem* itemRight = new QTableWidgetItem(QString::number(valueEuro, 'f', 2));

  QTableWidget* table = NULL;
  QLineEdit* lineEdit = NULL;

  switch (column) {
  case en_Columns::Column_Left:
  case en_Columns::Column_Right:
    table = m_tables[column];
    lineEdit = m_lineEdits[column];
    break;
  default:
    break;
  }

  table->insertRow(table->rowCount());
  table->setItem(table->rowCount() - 1,
                 en_Columns::Column_Left,
                 itemLeft);
  table->setItem(table->rowCount() -1,
                 en_Columns::Column_Right,
                 itemRight);

  double valueSum = lineEdit->text().toDouble();
  QString valueSumText = QString::number(valueSum + valueEuro, 'f', 2);
  lineEdit->setText(valueSumText);

  emit Signal_AccountSumChanged(valueEuro,
                                column);
}

void FT_Account::on_pushButton_enterLeft_clicked()
{
  Slot_AddLeft(ui->lineEdit_enterTitleLeft->text(),
               ui->doubleSpinBox_enterValueLeft->value());
}
