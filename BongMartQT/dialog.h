#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Calendar.h>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
    Calendar cal;
    int s_day;
    int s_year;
    int s_month;
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    int get_day();
    int get_year();
    int get_month();
    void set_day(int);
    void set_year(int);
    void set_month(int);

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
