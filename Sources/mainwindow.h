#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();
    void Slot_StepTimer(void);

    void on_pushButton_stop_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* m_StepTimer = NULL;
    uint32_t m_numOfDays = 0;
    double m_cashVirtual = 0.0;
    int32_t m_month = -1;
    const double m_weeksPerMonth = 4.0;
    const double m_daysPerWeek = 30.0;
    QSettings* m_Settings = NULL;
};

#endif // MAINWINDOW_H
