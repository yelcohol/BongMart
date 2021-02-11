#include "Pos.h"

POS::POS(string rep_name, string store_name, string phone_num, string address) {
    powerPos = true;
    total_money = 0;
    total_cash = 0;
    card_money = 0;
    set_rep_name(rep_name);
    set_store_name(store_name);
    set_phone_num(phone_num);
    set_address(address);
    productRead("Product.txt");
}

POS::~POS() {
    //동적할당한 메모리들 free해주기
}


void POS::set_card_money(int n){
    this->card_money = n;
}
void POS::save_history(history_information _history, int index) {
    ofstream outFile("History.txt", ios::app);

    cout << _history.age << "\t";
    if (_history.sex) cout << "Male\t";	//남자
    else cout << "Female\t";	//여자
    cout << _history.time << "\t";
    cout << setfill('0') << setw(4) << index << endl;

    outFile.close();
}

void POS::search_history(vector<history_information> history, int lage, int rage, bool _sex) {
    int index = 1;
    for (vector<history_information>::size_type i = 0; i < history.size(); ++i) {
        if ((lage <= history[i].age) && (history[i].age < rage) && (history[i].sex == _sex)) {
            cout << history[i].age << "세\t";
            if (history[i].sex) cout << "Male\t";	//남자
            else cout << "Female\t";	//여자
            cout << history[i].time << "\t";

            cout << setfill('0') << setw(4) << index++ << endl;
        }
        else continue;
    }
}

void POS::print_history(int num) {
    int index;
    vector<history_information> history;
    history_information history_info;

    ifstream inFile("History.txt");

    char Line[100];

    inFile.getline(Line, 100);
    while (!inFile.eof()) {
        inFile.getline(Line, 100);

        if (Line[0] == NULL) break;

        history_info.age = atoi(strtok(Line, "\t"));
        if (strcmp(strtok(NULL, "\t"), "Female")) history_info.sex = true;	//남자
        else history_info.sex = false;	//여자
        strcpy(history_info.time, strtok(NULL, "\t"));
        index = atoi(strtok(NULL, "\t"));

        history.push_back(history_info);
    }

    cout << "나이\t성별\t시간\t번호" << endl;
    cout << "----------------------------" << endl;
    switch (num) {
    case 1:	//전체 history
        for (vector<history_information>::size_type i = 0; i < history.size(); ++i) {
            cout << history[i].age << "세\t";
            if (history[i].sex) cout << "Male\t";	//남자
            else cout << "Female\t";	//여자
            cout << history[i].time << "\t";
            cout << setfill('0') << setw(4) << (i + 1) << endl;
        }
        break;

    case 2:	//10대 남성
        search_history(history, 10, 20, true);
        break;

    case 3:	//10대 여성
        search_history(history, 10, 20, false);
        break;

    case 4:	//20대 남성
        search_history(history, 20, 30, true);
        break;

    case 5:	//20대 여성
        search_history(history, 20, 30, false);
        break;

    case 6:	//30대 남성
        search_history(history, 30, 40, true);
        break;

    case 7:	//30대 여성
        search_history(history, 30, 40, false);
        break;

    case 8:	//40대 남성
        search_history(history, 40, 50, true);
        break;

    case 9:	//40대 남성
        search_history(history, 40, 50, false);
        break;
    }

    inFile.close();
}

void POS::check_history() {
    int input;
    cout << "-숫자키 1  -  전체 히스토리 " << endl;
    cout << "-숫자키 2  -  10대 남성  " << endl;
    cout << "-숫자키 3  -  10대 여성  " << endl;
    cout << "-숫자키 4  -  20대 남성  " << endl;
    cout << "-숫자키 5  -  20대 여성  " << endl;
    cout << "-숫자키 6  -  30대 남성  " << endl;
    cout << "-숫자키 7  -  30대 여성  " << endl;
    cout << "-숫자키 8  -  40대 남성  " << endl;
    cout << "-숫자키 9  -  40대 여성  " << endl;
    cout << "메뉴를 선택하십시오 : ";
    cin >> input;
    while (getchar() != '\n');

    system("cls");
    print_history(input);
    while (getchar() != '\n');
}


void POS::productRead(const char* filename) {

    ifstream inFile(filename);

    while (!inFile.eof()) {
        char inputLine[200] = { 0, };
        inFile.getline(inputLine, 200);

        if (inputLine[0] == NULL) { break; }
        string r_name;
        int r_price, r_discount, r_sell, r_category;
        //int r_valid_date;
        //int r_loacation;

        r_name = strtok(inputLine, "/");
        r_price = atoi(strtok(NULL, "/"));
        char* r_stock_index = strtok(NULL, "/");
        r_discount = atoi(strtok(NULL, "/"));
        r_sell = atoi(strtok(NULL, "/"));

        vector <int> r_valid_date;
        vector <int> r_stock;
        int r_index;
        char* r_c;

        bool c = true;
        while (1) {
            if (c) {
                r_index = atoi(strtok(r_stock_index, ".#"));
                c = false;
            }
            else {
                r_c = strtok(NULL, ".#");
                if (r_c == NULL)
                    break;
                r_index = stoi(r_c);
            }

            r_valid_date.push_back(r_index);
            r_index = atoi(strtok(NULL, ".#"));
            r_stock.push_back(r_index);
        }


        Product input_p;
        input_p.setProduct(r_name, r_price, r_valid_date, r_stock, r_discount, r_sell);
        product.push_back(input_p);

    }


    //sort(student, student + numStudent, compare);

    inFile.close();
}

void POS::productWrite(const char* filename) {
    ofstream outFile(filename);

    for (int i = 0; i < product.size(); i++) {
        outFile << product.at(i).getname() << "/" << product.at(i).getprice() << "/";
        for (int j = 0; j < product.at(i).getstock().size(); j++) {
            outFile << product.at(i).getvalid_date().at(j) << "." << product.at(i).getstock().at(j);
            if (j == product.at(i).getstock().size() - 1)
                outFile << "##/";
            else
                outFile << ".";
        }
        outFile << product.at(i).getdiscount() << "/" << product.at(i).getsell() << endl;
    }
    outFile.close();

}



void POS::mainMenu() {
    /*
    int input;
    cout << "*** 오지는 객체지향 9조 ***" << endl;
    cout << "*** 마트 관리 프로그램  ***" << endl << endl;

    cout << "-숫자키 1  -  달력 " << endl;
    cout << "-숫자키 2  -  계산  " << endl;
    cout << "-숫자키 3  -  시재 점검 (현금) " << endl;
    cout << "-숫자키 4  -  시재 입력 (현금)  " << endl;
    cout << "-숫자키 5  -  현금 입금 & 출금" << endl;
    cout << "-숫자키 6  -  판매 분석//////////////" << endl;
    cout << "-숫자키 7  -  거래 내역/////////////////" << endl;
    cout << "-숫자키 8  -  제품 목록" << endl;
    cout << "-숫자키 9  -  제품 추가 & 수정 & 삭제" << endl;
    cout << "-숫자키 10 -  행사//////////////" << endl;
    cout << "-숫자키 11 -  총금액 점검//////////////" << endl;
    cout << "-숫자키 12 -  물품 폐기" << endl;
    cout << "-숫자키 0  -  제품 정보 저장 & 종료" << endl << endl;
    cout << "메뉴를 선택하십시오 : ";
    cin >> input;
    while (getchar() != '\n');


    system("cls");
    switch (input)
    {
    case 1:                  //숫자키 1 - 달력
        calendarON();
        break;
    case 2:                  //숫자키 2 - 계산
        input_buy_product();
        productWrite("Product.txt");   //저장
        break;
    case 3:                  //숫자키 3 - 시재 점검 (현금)
        check_cash();
        break;
    case 4:                  //숫자키 4 - 시재 입력 (현금)
        input_total_cash();
        break;
    case 5:                  //숫자키 5 - 현금 입금 & 출금
        modify_cash();
        break;
    case 6:                  //숫자키 6 - 판매 분석 (일일판매량등등) - sell 사용
       //sub_total_cash();
        break;
    case 7:                  //숫자키 7 - 거래 내역
       //print_product_list();
        break;
    case 8:                  //숫자키 8 - 제품 목록
        print_product_list();
        break;
    case 9:                  //숫자키 9 - 제품 추가 & 수정 & 삭제
        modify_product();
        productWrite("Product.txt");   //저장
        break;
    case 10:               //숫자키 10 - 행사 - discount 사용 , input_buy_product에도 추가할것!!!!
       //sub_total_cash();
        break;
    case 11:               //숫자키 11 - 총금액
    //sub_total_cash();
        break;
    case 12:               //숫자키 12 - 물품 폐기
        trash_product_clear();
        break;

        ////////////////////////// 총금액

        ////////////////////////// 물품 폐기

        /////////////////////////// 발전 방향 - 이름 띄어쓰기

    case 0:                  //숫자키 0 - 종료
        powerPos = false;
        productWrite("Product.txt");   //저장
        break;
    default:

        break;
    }


    system("cls");
    */
}





void POS::set_total_money() {
    total_money = total_cash + card_money;
}

void POS::set_total_cash(int cash) {
    this->total_cash = cash;
}


void POS::set_rep_name(string rep_name) {
    this->rep_name = rep_name;
}

void POS::set_store_name(string store_name) {
    this->store_name = store_name;
}

void POS::set_phone_num(string phone_num) {
    this->phone_num = phone_num;
}

void POS::set_address(string address) {
    this->address = address;
}

void POS::check_cash() {
    set_total_money();

    int check_cash[8] = { 0, };
    int check_money = 0;
    cout << "50000 개수 : ";
    cin >> check_cash[0];
    while (getchar() != '\n');

    cout << "10000 개수 : ";
    cin >> check_cash[1];
    while (getchar() != '\n');

    cout << "5000 개수 : ";
    cin >> check_cash[2];
    while (getchar() != '\n');

    cout << "1000원 개수 : ";
    cin >> check_cash[3];
    while (getchar() != '\n');

    cout << "500원 개수 : ";
    cin >> check_cash[4];
    while (getchar() != '\n');

    cout << "100원 개수 : ";
    cin >> check_cash[5];
    while (getchar() != '\n');

    cout << "50원 개수 : ";
    cin >> check_cash[6];
    while (getchar() != '\n');

    cout << "10원 개수 : ";
    cin >> check_cash[7];
    while (getchar() != '\n');

    check_money = (check_cash[0] * 50000) + (check_cash[1] * 10000) + (check_cash[2] * 5000) + (check_cash[3] * 1000) + (check_cash[4] * 500) + (check_cash[5] * 100) + (check_cash[6] * 50) + (check_cash[7] * 10);
    if (check_money == (total_money - card_money)) {
        cout << "현금과부족 :" << 0;
    }
    else {
        cout << "현금과부족 :" << check_money - (total_money - card_money);
    }
    Sleep(1000);
}

void POS::modify_cash() {
   /*
    int input;
    cout << "현금 입금 : 0 출금 : 1" << endl;
    cin >> input;
    while (getchar() != '\n');

    system("cls");

    if (input == 0) {
        add_total_cash();
    }
    else if (input == 1) {
        sub_total_cash();
    }
    */
}

void POS::add_total_cash(int cash) {
    this->total_cash += cash;
}

void POS::sub_total_cash(int cash) {
    this->total_cash -= cash;
}

void POS::print_product_list() {


    for (int i = 0; i < product.size(); i++) {
        cout << i + 1 << ". " << product.at(i).getname() << endl;
        cout << "*가격 : " << product.at(i).getprice() << endl;
        cout << "*재고 및 유통기한*" << endl;
        for (int j = 0; j < product.at(i).getstock().size(); j++) {
            cout << product.at(i).getstock().at(j) << "개 - ";
            cout << product.at(i).getvalid_date().at(j) << "까지" << endl;
        }
        cout << "*행사 여부 : " << discount_string(product.at(i).getdiscount()) << endl;
        cout << "*일일 판매량 : " << product.at(i).getsell() << "개" << endl;
        cout << "------------------------------------------------------------" << endl;
    }
    cout << "엔터 키 입력하면 돌아갑니다." << endl;
    int i;
    //getch();
    //cin >> i;
    while (getchar() != '\n');
}

void POS::modify_product() {
    int index;
    cout << "재고 ++ : 1" << endl;
    cout << "재고 -- : 2 - (제거는 유통기한 빠른 순으로)" << endl;
    cout << "상품 ++ : 3 - (신상품)" << endl;
    cout << "상품 -- : 4" << endl;
    cout << "메뉴를 골라주세요 : ";
    cin >> index;
    while (getchar() != '\n');

    system("cls");

    switch (index) {
    case 1:
        //add_stock();
        break;
    case 2:
        //sub_stock();
        break;
    case 3:
        //add_product();
        break;
    case 4:
        //sub_product();
        break;

    }
}

void POS::add_stock(int code, int validdate, int stock) {
    int index, num, date;
    index = code;
    num = stock;
    date = validdate;

    calendar.reset_curr_time();
    vector<int> time = calendar.returnTime();

    product.at(index).addstock(num, date);
    productWrite("Product.txt");
}

void POS::sub_stock(int code, int stock) {
    int index, num;
    index = code;
    num = stock;
    product.at(index).substock(num);
    productWrite("Product.txt");

}

void POS::add_product(string name, int price, int stock, int validdate, int discount) {
    string i_name;
    int i_price, i_stock, i_valid_date;
    int i_sell = 0;
    int i_discount = discount;
    i_discount /= 10;
    i_name = name;
    i_price = price;
    i_stock = stock;
    i_valid_date = validdate;

    vector <int> dumy;
    Product input_p;
    input_p.setProduct(i_name, i_price, dumy, dumy, i_discount, i_sell);
    input_p.addstock(i_stock, i_valid_date);
    product.push_back(input_p);
    productWrite("Product.txt");
}

void POS::sub_product(int _index) {
    int index, num, date;
    index = _index;
    product.erase(product.begin() + index);
    productWrite("Product.txt");
}

void POS::add_transaction(string _type) {                                   //거래내역 추가
    int sum = this->sum_purchase;
    string type = _type;
    vector<int> productbought = purchase;
    ofstream file("transaction.txt",ios::app);

    file << sum;
    file << " ";
    file << type;
    file << " ";
    for(int i = 0; i < productbought.size(); i++){
        file << productbought[i];
        file << "?";
        file << this->purchase_num[i];
        if(i != productbought.size() - 1)
            file << "/";

    }
    file << endl;
    file.close();
}


//거래내역을 텍스트 파일로 저장해 놓는다
//거래내역에 필요한 정보, 지불일시, 매출액, 현금, 카드, 포인트
//영수증 출력은 거래내역 텍스트 파일을 베이스로 출력해준다.

void POS::print_transactional_table() {

}
//
void POS::print_receipt() {
}
void POS::calcul(int getmon){

    if (purchase.size() == 0) {                                 //아무것도 없을때 purchase clear 안해줌
        //cout << "주문 상품이 없습니다!" << endl;
        set_flag(1);
        popDialog dialogpop;
        dialogpop.setModal(true);
        dialogpop.exec();

        return;
    }
    for (int i = 0; i < purchase.size(); i++) {                             //재고 없을때 걍 계산 안됨 purchase clear 안해줌
        if (this->product[purchase[i]].get_allstock() < purchase_num[i]) {
            //cout << "재고가 부족합니다 (" << purchase[i] << ")" << endl;
            set_flag(2);
            nostock ns;
            ns.setModal(true);
            ns.exec();
            return;
        }
    }
    sum_purchase = 0;
    for (int i = 0; i < purchase.size(); i++) {
        sum_purchase += (product[purchase[i]].getprice() * purchase_num[i]);
    }
    for(int i = 0; i < purchase.size(); i++){
        double temp = double(purchase_disc[i]) / 10;
        double v = (double)(purchase_num[i]) * (double)(product[purchase[i]].getprice()) * temp;
        sum_purchase -= (int)v;
    }


    this->get_money = getmon;
    if(getmon < sum_purchase){
        getmon = 0;
        this->get_money = 0;
        return;
    }
    this->change = this->get_money - sum_purchase;            //거스름돈
    this->total_cash += sum_purchase;
    this->total_money += sum_purchase;
    //this->calculate_cash_buy(this->change);                  //현금 별 거스름돈 계산?
    for (int i = 0; i < purchase.size(); i++) {
        product[purchase[i]].addsell(purchase_num[i]);
        product[purchase[i]].substock(purchase_num[i]);         //재고 감소
    }

    this->add_transaction("현금");
    purchase.clear();
    purchase_num.clear();
    purchase_disc.clear();


}
void POS::cardcal(){

    if (purchase.size() == 0) {                                 //아무것도 없을때 purchase clear 안해줌
        //cout << "주문 상품이 없습니다!" << endl;
        set_flag(1);
        popDialog dialogpop;
        dialogpop.setModal(true);
        dialogpop.exec();

        return;
    }
    for (int i = 0; i < purchase.size(); i++) {                             //재고 없을때 걍 계산 안됨 purchase clear 안해줌
        if (this->product[purchase[i]].get_allstock() < purchase_num[i]) {
            //cout << "재고가 부족합니다 (" << purchase[i] << ")" << endl;
            set_flag(2);
            nostock ns;
            ns.setModal(true);
            ns.exec();
            return;
        }
    }
    sum_purchase = 0;
    for (int i = 0; i < purchase.size(); i++) {
        sum_purchase += (product[purchase[i]].getprice() * purchase_num[i]);
    }
    for(int i = 0; i < purchase.size(); i++){
        double temp = double(purchase_disc[i]) / 10;
        double v = (double)(purchase_num[i]) * (double)(product[purchase[i]].getprice()) * temp;
        sum_purchase -= (int)v;
    }


    this->get_money = sum_purchase;
    this->change = this->get_money - sum_purchase;            //거스름돈
    this->card_money += sum_purchase;
    this->total_money += sum_purchase;
    //this->calculate_cash_buy(this->change);                  //현금 별 거스름돈 계산?
    for (int i = 0; i < purchase.size(); i++) {
        product[purchase[i]].addsell(purchase_num[i]);
        product[purchase[i]].substock(purchase_num[i]);         //재고 감소
    }

    this->add_transaction("카드");

    purchase.clear();
    purchase_num.clear();
    purchase_disc.clear();

}
void POS::input_buy_product(string in) {
    if(this->purchase.size() > 8){                      //주문창 꽉찼을때
        popDialog dialogpop;
        dialogpop.setModal(true);
        dialogpop.exec();
        return;
    }
    //char in[100];
    int input;

    sum_purchase = 0;

    if(atoi(in.c_str()) != 0 || in.compare("0") == 0){                          //숫자입력
        //cout << "행사 상품 - "  << product.at(in).getdiscount() << endl;
        input = stoi(in);

        //Product 배열에서 확인해야함
        if(input >= product.size()){
            popDialog dialogpop;
            dialogpop.setModal(true);
            dialogpop.exec();
            return;
        }
        purchase.push_back(input);
        purchase_num.push_back(1);

        for (int i = 0; i < purchase.size() - 1; i++) {            //같은 제품일 경우 수량만 up
            if (input == purchase[i]) {
                purchase_num[i]++;
                purchase.pop_back();
                purchase_num.pop_back();
            }
        }
        purchase_disc.clear();
        for(int i = 0; i < purchase.size(); i++){               //할인정보저장!
            purchase_disc.push_back(product[purchase[i]].getdiscount());
        }

    }
    else{       //문자입력
        if(in == "?"){
            return;
        }
        popDialog dialogpop;
        dialogpop.setModal(true);
        dialogpop.exec();
        return;
    }
}
vector<int> POS::get_purchase(){
    return this->purchase;
}
vector<int> POS::get_purchase_num(){
   return this->purchase_num;
}
vector<Product> POS::get_product(){
   return this->product;
}
int POS::get_total_money(){
    return this->total_money;
}
int POS::get_total_cash(){
    return this->total_cash;
}
int POS::get_sum_purchase(){
    return this->sum_purchase;
}
void POS::clear_things(){
    this->purchase.clear();
    this->purchase_num.clear();
    this->purchase_disc.clear();
    this->get_money = 0;
    this->change = 0;
    this->sum_purchase = 0;
}
void POS::clear_purchvec(){
    this->purchase.clear();
    this->purchase_num.clear();
    this->purchase_disc.clear();
}
vector<int> POS::get_purchase_disc(){
    return this->purchase_disc;
}
int POS::get_change(){
    return this->change;
}
void POS::set_flag(int n){
    this->flag = n;
}
int POS::get_flag(){
    return this->flag;
}
void POS::erase_purch(int i){
    this->purchase.erase(purchase.begin() + i);
    this->purchase_num.erase(purchase_num.begin() + i);
    this->purchase_disc.erase(purchase_disc.begin() + i);
}
void POS::inc_purch_num(int i){
    this->purchase_num[i]++;
}
void POS::dec_purch_num(int i){
    this->purchase_num[i]--;
}
POS POS::get_pos(){
    return *this;
}


string POS::discount_string(int dis) {
    switch (dis) {
    case 0:
        return "행사 없음";
    case 1:
        return "10% 할인";
    case 2:
        return "20% 할인";
    case 3:
        return "30% 할인";
    case 4:
        return "40% 할인";
    case 5:
        return "50% 할인";
    case 6:
        return "60% 할인";
    case 7:
        return "70% 할인";
    case 8:
        return "80% 할인";
    case 9:
        return "90% 할인";
    case 11:
        return "1+1 행사";
    case 21:
        return "2+1 행사";

    }
}

void POS::trash_product_clear() {
    int index, date;

    calendar.reset_curr_time();
    vector<int> time = calendar.returnTime();


    cout << "***유통기한 지난 제품 목록***" << endl;
    int num = 0;
    for (int i = 0; i < product.size(); i++) {
        for (int j = 0; j < product.at(i).getstock().size(); j++) {

            if (product.at(i).getvalid_date().at(j) < 10000 * time[0] + 100 * time[1] + time[2])
                continue;
            else {
                cout << i + 1 << ". " << product.at(i).getname() << endl;
                cout << product.at(i).getstock().at(j) << "개 - ";
                cout << product.at(i).getvalid_date().at(j) << "까지" << endl;
                num++;
            }



        }
        product.at(i).substock(num);
    }


    Sleep(5000);
    cout << endl << "제거 완료";
    Sleep(2000);
    productWrite("Product.txt");
}



void POS::calendarON() {
    calendar.PowerCalON();
    //while (1) {
        //calendar.drawCalender();
        //if (!calendar.checkPowerCal())
         //   break;
   // }
}


bool POS::checkPowerPos() {
    return powerPos;
}
