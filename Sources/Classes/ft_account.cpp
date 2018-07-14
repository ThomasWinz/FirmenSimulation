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

}

FT_Account::~FT_Account()
{
  delete ui;
}

Ui::FT_Account *FT_Account::Get_ui()
{
  return ui;
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
}

void FT_Account::Slot_AddLeft(const QString &title,
                              double valueEuro) {
    Slot_AddValue(ui->tableWidget_left,
                  ui->lineEdit_sumLeft,
                  title,
                  valueEuro);
}

void FT_Account::Slot_AddRight(const QString &title,
                               double valueEuro) {
    Slot_AddValue(ui->tableWidget_right,
                  ui->lineEdit_sumRight,
                  title,
                  valueEuro);
}

void FT_Account::Slot_AddValue(QTableWidget *table,
                               QLineEdit* lineEdit,
                               const QString &title,
                               double valueEuro) {
    QTableWidgetItem* itemLeft = new QTableWidgetItem(title);
    QTableWidgetItem* itemRight = new QTableWidgetItem(QString::number(valueEuro, 'f', 2));

    table->insertRow(table->rowCount());
    table->setItem(table->rowCount() - 1,
                   en_Columns::Column_Left,
                   itemLeft);
    table->setItem(table->rowCount() -1,
                   en_Columns::Column_Right,
                   itemRight);

    double valueSum = lineEdit->text().toDouble();
    lineEdit->setText(QString::number(valueSum + valueEuro));
}
