#ifndef BONGBONG_H
#define BONGBONG_H

#include <QMainWindow>
#include <QString>
#include "Pos.h"
#include <QTextBrowser>
#include "Customer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class bongbong; }
QT_END_NAMESPACE

class bongbong : public QMainWindow
{
    Q_OBJECT
private:
    POS pos = POS("LeeSangyun","Emart","010-7310-7124","ChungAngUniv");
    Staff staf;
    vector <Customer> customer;

    QTextBrowser tb[8];
public:
    bongbong(QWidget *parent = nullptr);
    ~bongbong();
    void clear_everything();
private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_buttonmil_clicked();

    void on_buttonC_clicked();

    void on_buttonerase_clicked();

    void on_pushButton_clicked();

    void on_buttonenter_clicked();

    void on_buttoncash_clicked();

    void on_pushButton_5_clicked();

    void on_selected_cancel_clicked();

    void on_plus_clicked();

    void on_minus_clicked();

    void on_buttonnum_clicked();

    void on_checkmoney_tabBarClicked(int index);

    void on_confirm_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_productlist_clicked();

    void on_pushButton_8_clicked();

    void on_confirmbut_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_buttoncard_clicked();

    void on_ref_clicked();

    void on_buttonpoint_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::bongbong *ui;
};

#endif
