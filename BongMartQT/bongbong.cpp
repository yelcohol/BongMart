#include "bongbong.h"
#include "ui_bongbong.h"
#include "dialog.h"
#include "Pos.h"
#include "Product.h"
#include "Calendar.h"
#include "Staff.h"
#include "taewoo.h"


bongbong::bongbong(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bongbong)
{
    this->pos = POS("LeeSangYun","Emart","010-7310-7124","ChungAngUniv");
    this->staf = Staff();
    vector <Customer> customer;
    ui->setupUi(this);
}

bongbong::~bongbong()
{
    delete ui;
}

void bongbong::clear_everything(){
    //text
    ui->product1->clear();
    ui->product2->clear();
    ui->product3->clear();
    ui->product4->clear();
    ui->product5->clear();
    ui->product6->clear();
    ui->product7->clear();
    ui->product8->clear();

    ui->num1->clear();
    ui->num2->clear();
    ui->num3->clear();
    ui->num4->clear();
    ui->num5->clear();
    ui->num6->clear();
    ui->num7->clear();
    ui->num8->clear();

    ui->price1->clear();
    ui->price2->clear();
    ui->price3->clear();
    ui->price4->clear();
    ui->price5->clear();
    ui->price6->clear();
    ui->price7->clear();
    ui->price8->clear();

    ui->value1->clear();
    ui->value2->clear();
    ui->value3->clear();
    ui->value4->clear();
    ui->value5->clear();
    ui->value6->clear();
    ui->value7->clear();
    ui->value8->clear();

    ui->totalnum->clear();
    ui->totalprice->clear();
    ui->disc_money->clear();
    ui->get_money->clear();
    ui->chnge->clear();
    ui->mongot->clear();
    ui->outputbox->clear();
    //vector
    pos.clear_things();
}
void bongbong::on_button1_clicked()
{
    QString str = ui->inputbox->text();
    str.append("1");
    ui->inputbox->setText(str);
}


void bongbong::on_button2_clicked()
{
    QString str = ui->inputbox->text();
    str.append("2");
    ui->inputbox->setText(str);
}

void bongbong::on_button3_clicked()
{
    QString str = ui->inputbox->text();
    str.append("3");
    ui->inputbox->setText(str);
}

void bongbong::on_button4_clicked()
{
    QString str = ui->inputbox->text();
    str.append("4");
    ui->inputbox->setText(str);
}

void bongbong::on_button5_clicked()
{
    QString str = ui->inputbox->text();
    str.append("5");
    ui->inputbox->setText(str);
}

void bongbong::on_button6_clicked()
{
    QString str = ui->inputbox->text();
    str.append("6");
    ui->inputbox->setText(str);
}

void bongbong::on_button7_clicked()
{
    QString str = ui->inputbox->text();
    str.append("7");
    ui->inputbox->setText(str);
}

void bongbong::on_button8_clicked()
{
    QString str = ui->inputbox->text();
    str.append("8");
    ui->inputbox->setText(str);
}

void bongbong::on_button9_clicked()
{
    QString str = ui->inputbox->text();
    str.append("9");
    ui->inputbox->setText(str);
}

void bongbong::on_pushButton_15_clicked()
{
    QString str = ui->inputbox->text();
    str.append("00");
    ui->inputbox->setText(str);
}

void bongbong::on_pushButton_16_clicked()
{
    QString str = ui->inputbox->text();
    str.append("0");
    ui->inputbox->setText(str);
}

void bongbong::on_buttonmil_clicked()
{
    QString str = ui->inputbox->text();
    str.append("10000");
    ui->inputbox->setText(str);
}

void bongbong::on_buttonC_clicked()
{
    ui->inputbox->clear();
}

void bongbong::on_buttonerase_clicked()
{
    QString str = ui->inputbox->text();
    if(str.size() == 1){
        str.clear();
    }
    else
        str.remove(str.size() - 1,str.size() - 1);

    ui->inputbox->setText(str);
}

void bongbong::on_pushButton_clicked()
{
    Dialog secDialog;
    secDialog.setModal(true);
    secDialog.exec();
}

void bongbong::on_buttonenter_clicked()
{

    QTextBrowser* qtb[8];
    qtb[0] = ui->product1;
    qtb[1] = ui->product2;
    qtb[2] = ui->product3;
    qtb[3] = ui->product4;
    qtb[4] = ui->product5;
    qtb[5] = ui->product6;
    qtb[6] = ui->product7;
    qtb[7] = ui->product8;

    QTextBrowser* qtbn[8];
    qtbn[0] = ui->num1;
    qtbn[1] = ui->num2;
    qtbn[2] = ui->num3;
    qtbn[3] = ui->num4;
    qtbn[4] = ui->num5;
    qtbn[5] = ui->num6;
    qtbn[6] = ui->num7;
    qtbn[7] = ui->num8;

    QTextBrowser* qtbv[8];
    qtbv[0] = ui->value1;
    qtbv[1] = ui->value2;
    qtbv[2] = ui->value3;
    qtbv[3] = ui->value4;
    qtbv[4] = ui->value5;
    qtbv[5] = ui->value6;
    qtbv[6] = ui->value7;
    qtbv[7] = ui->value8;

    QTextBrowser* qtbp[8];
    qtbp[0] = ui->price1;
    qtbp[1] = ui->price2;
    qtbp[2] = ui->price3;
    qtbp[3] = ui->price4;
    qtbp[4] = ui->price5;
    qtbp[5] = ui->price6;
    qtbp[6] = ui->price7;
    qtbp[7] = ui->price8;

    //text clear
    for(int i = 0; i < 8; i++){
        qtb[i]->clear();
        qtbn[i]->clear();
        qtbv[i]->clear();
        qtb[i]->clear();
        qtbp[i]->clear();
        ui->chnge->clear();
        ui->mongot->clear();
    }
    string sr;
    QString str = ui->inputbox->text();
    ui->inputbox->clear();
    std::string current_locale_text = str.toLocal8Bit().constData();

    pos.input_buy_product(current_locale_text);
    vector <int> purch = pos.get_purchase();
    vector <int> purch_num = pos.get_purchase_num();
    vector<Product> prod = pos.get_product();
    vector <int> purch_dic = pos.get_purchase_disc();


    for(int i = 0; i < purch.size(); i++){

        sr = prod[purch[i]].getname();                  //상품이름
        str = QString::fromStdString(sr);
        qtb[i]->setText(str);

        int n = purch_num[i];                          //상품 개수
        str = QString::number(n);
        qtbn[i]->setText(str);

        n = prod[purch[i]].getprice();              //상품 단가
        str = QString::number(n);
        qtbv[i]->setText(str);

        str = QString::number(purch_num[i]*n);          //상품 가격
        qtbp[i]->setText(str);

    }

    int totaln = 0;                                     //총개수
    for(int i = 0; i < purch.size();i++){
        totaln += purch_num[i];
    }
    str = QString::number(totaln);
    ui->totalnum->setText(str);

    int totalp = 0;                                     //총 가격
    for(int i = 0; i < purch.size(); i++){
        totalp += (prod[purch[i]].getprice()*purch_num[i]);
    }
    str = QString::number(totalp);
    ui->totalprice->setText(str);
    double discount_how = 0;
    double temp;
    for(int i = 0; i < purch.size(); i++){
        temp = double(purch_dic[i]) / 10;
        double v = (double)(purch_num[i]) * (double)(prod[purch[i]].getprice()) * temp;
        discount_how += v;
    }

    str = QString::number(discount_how);
    ui->disc_money->setText(str);

    str = QString::number(totalp - discount_how);
    ui->get_money->setText(str);
    //할인정보 outputbox에 출력
    ui->outputbox->clear();
    for(int i = 0; i < purch.size(); i++){
        if(purch_dic[i] != 0){
            QString stri = QString::number(purch_dic[i] * 10);
            QString strn = QString::fromStdString(prod[purch[i]].getname());
            ui->outputbox->append(strn + stri + "% discount!");
        }
    }


}

void bongbong::on_buttoncash_clicked()
{
    //현금계산
    //현금부족하면 창띄우고 리턴

    QString sti = ui->inputbox->text();
    ui->inputbox->clear();
    pos.calcul(sti.toInt());

    if(pos.get_flag() == 2){
        clear_everything();
        ui->outputbox->setText("재고 부족!");
        pos.set_flag(0);
        return;
    }
    if(pos.get_flag() == 1){
        ui->outputbox->setText("주문상품이 없습니다!");
        pos.set_flag(0);
        return;
    }
    if(sti.toInt() < pos.get_sum_purchase()){
        clear_everything();
        ui->outputbox->setText("돈이 부족합니다!");
        return;
    }

    ui->outputbox->clear();
    QString a = QString::number(pos.get_change());
    ui->outputbox->setText("거스름 돈 :" + a);
    if(pos.get_total_cash() < a.toInt()){
        ui->outputbox->setText("포스에 현금이 부족합니다!");
    }
    ui->outputbox->append("계산완료");

    ui->mongot->setText(sti);

    ui->chnge->setText(a);

    pos.productWrite("Product.txt");
    //product write안뎀 ㅜㅜ***

    ui->textBrowser_9->setText("총 현금 : " + QString::number(pos.get_total_cash()));
    on_confirm_clicked();
    on_productlist_clicked();
}

void bongbong::on_pushButton_5_clicked()
{
    clear_everything();

}

void bongbong::on_selected_cancel_clicked()
{
    //입력값이 숫자가 아닐 경우???
    QString hownum = ui->totalnum->toPlainText();
    int hown = hownum.toInt();
    QString number = ui->inputbox->text();
    int n = number.toInt();
    if(n < 1 || n > hown){
        return;
    }
    else{
        pos.erase_purch(n - 1);
        ui->inputbox->setText("?");
        on_buttonenter_clicked();
        ui->inputbox->clear();
    }
}

void bongbong::on_plus_clicked()
{
    QString pl = ui->inputbox->text();
    int pln = pl.toInt();
    QString howlong = ui->totalnum->toPlainText();
    int howl = howlong.toInt();
    if(pln < 1 || pln > howl){
        return;
    }
    else{
        pos.inc_purch_num(pln - 1);
        ui->inputbox->setText("?");
        on_buttonenter_clicked();
        ui->inputbox->setText(pl);
    }
}


void bongbong::on_minus_clicked()
{
    QString pl = ui->inputbox->text();
    int pln = pl.toInt();
    vector<int> vec = pos.get_purchase_num();

    QString howlong = ui->totalnum->toPlainText();
    int howl = howlong.toInt();
    if(pln < 1 || pln > vec.size()){
        return;
    }
    else{
        if(vec[pln] == 1){
            on_selected_cancel_clicked();
            return;
        }
        pos.dec_purch_num(pln - 1);
        ui->inputbox->setText("?");
        on_buttonenter_clicked();
        ui->inputbox->setText(pl);
    }
}


void bongbong::on_buttonnum_clicked()
{
    QString qn = ui->inputbox->text();
    int n = qn.toInt();
    if(n == 0){
        return;
    }
    else{
        vector <int> vec = pos.get_purchase_num();
        for(int i = 0; i < vec[(pos.get_purchase()).size() - 1]; i++){
            pos.dec_purch_num((pos.get_purchase()).size() - 1);
        }
        for(int i = 0; i < n; i++){
            pos.inc_purch_num((pos.get_purchase()).size() - 1);
        }
        ui->inputbox->setText("?");
        on_buttonenter_clicked();
       ui->inputbox->clear();

    }
}


void bongbong::on_confirm_clicked()
{
    int sum = 0;
    sum = sum + 50000*((ui->fivemil->text()).toInt());
    sum = sum + 10000*((ui->mil->text()).toInt());
    sum = sum + 5000*((ui->fivethous->text()).toInt());
    sum = sum + 1000*((ui->thous->text()).toInt());
    sum = sum + 100*((ui->hund->text()).toInt());
    sum = sum + 500*((ui->fivehund->text()).toInt());
    sum = sum + 50*((ui->fifty->text()).toInt());
    sum = sum + 10*((ui->ten->text()).toInt());

    sum = sum - pos.get_total_cash();
    ui->moneycorrect->setText(QString::number(sum));

}

void bongbong::on_checkmoney_tabBarClicked(int index)
{

}

void bongbong::on_pushButton_4_clicked()            //영업준비금
{

    QString st = ui->lineEdit->text();
    if(st == NULL){
        return;
    }
    ui->lineEdit->clear();
    pos.set_total_cash(st.toInt());
    pos.set_card_money(0);
    pos.set_total_money();
    ui->textBrowser_9->setText("총 현금 : " + QString::number(pos.get_total_cash()));
    ui->textBrowser_9->append("총 카드 돈 : " + QString::number(pos.get_total_money() - pos.get_total_cash()));
}

void bongbong::on_pushButton_3_clicked()        //중간출금
{
    QString str = ui->lineEdit->text();
    ui->lineEdit->clear();
    if(pos.get_total_cash() < str.toInt()){
        ui->textBrowser_9->setText("현금 부족!");
        return;
    }
    pos.sub_total_cash(str.toInt());
    pos.set_total_money();
    ui->textBrowser_9->setText("총 현금 : " + QString::number(pos.get_total_cash()));
    ui->textBrowser_9->append("카드 돈 : " + QString::number(pos.get_total_money() - pos.get_total_cash()));
}

void bongbong::on_pushButton_2_clicked()            //중간입금
{
    QString str = ui->lineEdit->text();
    ui->lineEdit->clear();
    pos.add_total_cash(str.toInt());
    ui->textBrowser_9->setText("총 현금 : " + QString::number(pos.get_total_cash()));
    pos.set_total_money();
    ui->textBrowser_9->append("카드 돈 : " + QString::number(pos.get_total_money() - pos.get_total_cash()));
}

void bongbong::on_productlist_clicked()                     //상품 리스트
{
    ui->productnum->clear();
    ui->productname->clear();
    ui->productprice->clear();
    ui->productstock->clear();
    ui->productdiscount->clear();
    ui->productsell->clear();

    vector<Product> pr = pos.get_product();

    for(int i = 0; i < pr.size(); i++){
        ui->productnum->append(QString::number(i));
        vector<int> stock = pr[i].getstock();
        ui->productname->append(QString::fromStdString(pr[i].getname()));
        ui->productprice->append(QString::number(pr[i].getprice()));
        int n = 0;
        for(int j = 0; j < stock.size(); j++){
            n += stock[j];
        }
        ui->productstock->append(QString::number(n));
        ui->productdiscount->append(QString::number(pr[i].getdiscount()));
        ui->productsell->append(QString::number(pr[i].getsell()));
    }
}

void bongbong::on_pushButton_8_clicked()                //상품등록
{
    QString name = ui->input_values_1->text();
    QString price = ui->input_values_2->text();
    QString validdate = ui->input_values_3->text();
    QString stock = ui->input_values_4->text();
    QString discount = ui->input_values_5->text();
    if(name == NULL || price == NULL|| validdate == NULL|| stock == NULL|| discount == NULL){
        ui->tell_how->setText("형식을 지켜주세요!");
        ui->tell_how->append("예) (사과) (1000) (20200101) (10) (10%)");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
        return;
    }
    else if(discount.toInt() > 100 || discount.toInt() < 0){
        ui->tell_how->setText("형식을 지켜주세요!");
        ui->tell_how->append("예) (사과) (1000) (20200101) (10) (10%)");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
        return;
    }
    else if(stock.toInt() < 0){
        ui->tell_how->setText("형식을 지켜주세요!");
        ui->tell_how->append("예) (사과) (1000) (20200101) (10) (10%)");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
        return;
    }
    else if(validdate.toInt() >= 100000000){ //유통기한 확인
            ui->tell_how->setText("형식을 지켜주세요!");
            ui->tell_how->append("예) (사과) (1000) (20200101) (10) (10%)");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
            return;


        //else if (validdate >= 10000 * time[0] + 100 * time[1] + time[2]){
        //
        //}
        //else {
            //ui->tell_how->setText("형식을 지켜주세요!");
            //ui->tell_how->append("예) (사과) (1000) (20200101) (10) (10%)");
            //return;
        //}


    }
    else{
        pos.add_product(name.toLocal8Bit().constData(), price.toInt(), stock.toInt(), validdate.toInt(), discount.toInt());
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
        ui->tell_how->setText("등록완료");
    }
    on_productlist_clicked();

}

void bongbong::on_confirmbut_clicked()
{
    ui->tell_how->clear();
    ui->input_values_1->clear();
    ui->input_values_2->clear();
    ui->input_values_3->clear();
    ui->input_values_4->clear();
    ui->input_values_5->clear();
    ui->transaction->clear();
    /*
    ui->transaction->setText("-------거래내역-------");
    ifstream in("C:/Users/99san/Documents/bongbong/transaction.txt");
    int count = 1;
    while(!in.eof()){
        char inputLine[200] = { 0, };
        in.getline(inputLine, 200);

        if (inputLine[0] == NULL) { break; }
        string r_sum, r_type;
        string r_prod[8];
        string r_num[8];
        char* temp[8];

        char a[8] = {'{','{','{','{','{','{','{','{'};
        for(int i = 0; i < 8; i++){
            temp[i] = &a[i];
        }
        r_sum = strtok(inputLine, " ");
        r_type = strtok(NULL, " ");
        char* line;
        line = strtok(NULL, " ");
        temp[0] = strtok(line,"/");
        int l = 1;
        while(1){
            temp[l] = strtok(NULL,"/");
            l++;
            if(temp[l-1] == NULL){
                l--;
                break;
            }
            if(*temp[l-1] == '{' || l == 8){
                l--;
                break;
            }


        }

        for(int j = 0; j < l; j++){
            r_prod[j] = strtok(temp[j],"?");
            r_num[j] = strtok(NULL, "?");
        }
        ui->transaction->append(QString::number(count) + ". " + QString::fromStdString(r_sum) + "  " + QString::fromStdString(r_type));
        for(int j = 0; j < l; j++){
            ui->transaction->append("    " + QString::fromStdString((pos.get_product())[stoi(r_prod[j])].getname()) + " " + QString::fromStdString(r_num[j]));
        }
        count++;
    }
*/
}

void bongbong::on_pushButton_9_clicked()                        //상품삭제
{

    QString index = ui->input_values_1->text();
    string in = index.toLocal8Bit().constData();
    if(atoi(in.c_str()) != 0 || in.compare("0") == 0){                      //숫자인지
        if(index == "" ){
            ui->tell_how->setText("해당제품이 없습니다");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
            return;

        }
        if(index.toInt() >= 0 && index.toInt() <= (pos.get_product().size() - 1)){
            pos.sub_product(index.toInt());
        }
        else{
            ui->tell_how->setText("해당제품이 없습니다");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
            return;
        }
        on_productlist_clicked();
    }
    else{
        ui->tell_how->setText("해당제품이 없습니다");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
        return;
    }
}

void bongbong::on_pushButton_7_clicked()                        //재고등록
{
    ui->tell_how->setText("제폼 코드, 유통기한, 재고량을 차례대로 입력하고 재고 등록 버튼을 눌러주세요");
    QString code = ui->input_values_1->text();
    QString validdate = ui->input_values_2->text();
    QString stock = ui->input_values_3->text();
    string in = code.toLocal8Bit().constData();
    string inv = validdate.toLocal8Bit().constData();
    string ins = stock.toLocal8Bit().constData();
    if((atoi(in.c_str()) != 0 || in.compare("0") == 0) && (atoi(inv.c_str()) != 0 || inv.compare("0") == 0) && (atoi(ins.c_str()) != 0 || ins.compare("0") == 0)){
        if(code == NULL | validdate == NULL || stock == NULL){
            ui->tell_how->setText("재고추가 실패");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
        }
        else if(code.toInt() < 0 || code.toInt() > (pos.get_product()).size() - 1){
            ui->tell_how->setText("재고추가실패");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();

        }
        /*
        else if(validdate >= 100000000 || date < 10000 * time[0] + 100 * time[1] + time[2]){        //오늘 전이거나  잘못된낳짜
            ui->tell_how->setText("재고추가실패");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
        }
        */
        else if(stock.toInt() <= 0){
            ui->tell_how->setText("재고추가실패");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
        }
        else{
            pos.add_stock(code.toInt(), validdate.toInt(), stock.toInt());
            ui->tell_how->setText("재고추가성공");
            ui->input_values_1->clear();
            ui->input_values_2->clear();
            ui->input_values_3->clear();
            ui->input_values_4->clear();
            ui->input_values_5->clear();
            on_productlist_clicked();
        }



    }
    else{
        ui->tell_how->setText("재고추가실패");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
    }

}

void bongbong::on_pushButton_10_clicked()                       //재고삭제
{
    QString code = ui->input_values_1->text();
    QString stock = ui->input_values_2->text();
    string cod = code.toLocal8Bit().constData();
    string stok = stock.toLocal8Bit().constData();

    int sum = 0;
    vector<int> vec = (pos.get_product())[code.toInt()].getstock();
    for(int i = 0; i < vec.size(); i++){
        sum += vec[i];
    }

    if((atoi(cod.c_str()) != 0 || cod.compare("0") == 0) && (atoi(stok.c_str()) != 0 || stok.compare("0") == 0)){
        if(code.toInt() >= 0 || code.toInt() < (pos.get_product().size())){
            if(stock.toInt() > 0 || stock.toInt() <= sum){
                pos.sub_stock(code.toInt(), stock.toInt());
                on_productlist_clicked();
                ui->tell_how->setText("재고삭제 완료");
                ui->input_values_1->clear();
                ui->input_values_2->clear();
                ui->input_values_3->clear();
                ui->input_values_4->clear();
                ui->input_values_5->clear();
                on_productlist_clicked();
            }
            else{
                ui->tell_how->setText("재고삭제 실패");
                ui->input_values_1->clear();
                ui->input_values_2->clear();
                ui->input_values_3->clear();
                ui->input_values_4->clear();
                ui->input_values_5->clear();
            }
        }
    }
    else{
        ui->tell_how->setText("재고삭제 실패");
        ui->input_values_1->clear();
        ui->input_values_2->clear();
        ui->input_values_3->clear();
        ui->input_values_4->clear();
        ui->input_values_5->clear();
    }
}

void bongbong::on_buttoncard_clicked()                          //카드결제
{

    //QString sti = ui->inputbox->text();
    ui->inputbox->clear();
    pos.cardcal();

    if(pos.get_flag() == 2){
        clear_everything();
        ui->outputbox->setText("재고 부족!");
        pos.set_flag(0);
        return;
    }
    if(pos.get_flag() == 1){
        ui->outputbox->setText("주문상품이 없습니다!");
        pos.set_flag(0);
        return;
    }

    ui->outputbox->clear();
    ui->outputbox->append("계산완료");

    QString b = QString::number(pos.get_sum_purchase());
    ui->mongot->setText(b);
    ui->chnge->setText("0");

    pos.productWrite("Product.txt");

    on_confirm_clicked();
    on_productlist_clicked();
}

void bongbong::on_buttonpoint_clicked()
{
    //Taewoo secDialog;
    //secDialog.setModal(true);
     //secDialog.exec();
}
/*

void bongbong::on_pushButton_11_clicked()
{
    QString n = ui->Name->text();
    QString a = ui->Age->text();
    QString nm = ui->number->text();
    if(n == NULL || a == NULL || nm == NULL){
        return;
    }
    bool sex;
    sex = ui->Sex_male->isChecked();
    string str = n.toLocal8Bit().constData();
    string st = nm.toLocal8Bit().constData();
    Customer temp = Customer(str, sex, a.toInt(), st);
    customer.push_back(temp);
    ui->Name->clear();
    ui->Age->clear();
    ui->number->clear();
}
*/



void bongbong::on_pushButton_11_clicked()
{

}

void bongbong::on_ref_clicked()
{

}

void bongbong::on_pushButton_6_clicked()
{

}
