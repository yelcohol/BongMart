#include "dialog.h"
#include "ui_dialog.h"
#include "Calendar.h"

#define MAX_STR 100

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    Calendar cal = Calendar();
    this->s_day = 1;
    this->s_month= 1;
    this->s_year = 2019;
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::get_day(){
    return this->s_day;
}
int Dialog::get_year(){
    return this->s_year;
}
int Dialog::get_month(){
    return this->s_month;
}
void Dialog::set_day(int n){
    this->s_day = n;
}
void Dialog::set_year(int n){
    this->s_year = n;
}
void Dialog::set_month(int n){
    this->s_month = n;
}

void Dialog::on_calendarWidget_clicked(const QDate &date)
{
    ui->text->clear();
    int day = date.day();
    int month = date.month();
    int year = date.year();
    set_day(day);
    set_year(year);
    set_month(month);

    cal.set_day(day);
    cal.set_year(year);
    cal.set_month(month);

    if(year >= 2019 && year <= 2029){
        vector<Schedule> sche;
        cal.get_schedule(sche);
        int index = 390*(year - 2019) + 30*month;
        vector<int> numsche;
        cal.get_num_schedule(numsche);
        int num = numsche.at(13*(year-2019)+month);
        for(int i = 0; i < num; i++){
            if(sche[index + i].sch_day == day){
                string a = "a";
                string e = "e";
                if(sche[index + i].sch_type == a){     //직원스케줄
                    ui->text->append(QString::number(day) + "일" + " " + QString::number(sche[index+i].sch_start_hour) + " 시 " + QString::number(sche[index+i].sch_start_min) + " 분 " + " ~ " + QString::number(sche[index + i].sch_end_hour) + " 시 " + QString::number(sche[index + i].sch_end_min) + " 분 " + " " + QString::fromLocal8Bit(sche[index + i].sch_note));
                }
                else if(sche[index + i].sch_type == e){

                }
                else{
                    ui->text->append(QString::number(day) + "일" + " " + QString::fromLocal8Bit(sche[index + i].sch_note));
                }
            }
        }

    }
    else{
        ui->text->setText("2019년~2029년까지만 사용가능합니다!");
    }
    cal.scheduleWrite();
}

void Dialog::on_pushButton_2_clicked()              //일정 삭제
{
    QString index = ui->delindex->text();
    ui->delindex->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    int del_sch = index.toInt();
    vector<int> num_sch;
    cal.get_num_schedule(num_sch);
    vector<Schedule> schedule;
    cal.get_schedule(schedule);

    if ((del_sch >= 1 && del_sch <= num_sch[(get_year() - 2019)*13 + get_month()])){
        string a = "a";
        string e = "e";
        int count = 0;
        for(int i = 0; i < num_sch[(this->get_month()) + (this->get_year() - 2019)*13]; i++){
            count++;

            if(count == del_sch){
                if(schedule[(get_year()-2019)*390 + get_month()*30 + i].sch_day == this->get_day()){

                    if (schedule[(get_year() - 2019)*390 + get_month()*30 + i].sch_type == a || schedule[(get_year() - 2019)*390 + get_month()*30 + del_sch - 1].sch_type == e) {
                        cal.sub_cal(del_sch);
                        ui->tell->setText("일정삭제완료!");
                    }


                    else {
                         ui->tell->setText("공휴일은 삭제 할 수 없습니다");
                    }
                }
            }
        }

    }
    else{
        ui->tell->setText("다시입력해주세요");
    }
}

void Dialog::on_pushButton_clicked()                //일정 추가
{
    int sh = (ui->lineEdit->text()).toInt();
    int sm = (ui->lineEdit_2->text()).toInt();
    int eh = (ui->lineEdit_3->text()).toInt();
    int em = (ui->lineEdit_4->text()).toInt();
    string str = (ui->lineEdit_5->text()).toStdString();
    if(sh =! 0 || eh != 0)
    cal.add_cal(get_day(),sh,sm,eh,em,str);
    ui->delindex->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->tell->setText("일정추가완료!");
}
