
#include "Calendar.h"


Calendar::Calendar() {
    powerCal = true;

    reset_curr_time();

    for(int i = 0; i < 11; i++){
        for(int j = 0; j <13; j++){
            num_sch[i][j] = 0;
        }
    }
    scheduleRead("special_days.txt");
    scheduleRead("staff_schedule.txt");

}
Calendar::~Calendar() {
    //동적할당한 메모리들 free해주기
}

void Calendar::set_year(int n){
    this->year = n;
}
void Calendar::set_day(int n){
    this->day = n;
}
void Calendar::set_month(int n){
    this->month = n;
}
int Calendar::get_year(){
    return this->year;
}
int Calendar::get_day(){
    return this->day;
}
int Calendar::get_month(){
    return this->month;
}
void Calendar::reset_curr_time() {
    time(&curr_sec);
    curr_time = localtime(&curr_sec);
    year = curr_time->tm_year + 1900;
    month = curr_time->tm_mon + 1;
    day = curr_time->tm_mday;
    hour = curr_time->tm_hour;
    minute = curr_time->tm_min;
}

void Calendar::scheduleRead(string filename) {

    ifstream inFile(filename);

    while (!inFile.eof()) {
        char inputLine[100] = { 0, };
        inFile.getline(inputLine, 100);

        if (inputLine[0] == NULL) { break; }


        char* r_note;

        int r_year, r_month, r_day, r_start_hour, r_start_min, r_end_hour, r_end_min;

        string r_type(strtok(inputLine, "/"));
        r_year = atoi(strtok(NULL, "/")) - 2019;
        r_month = atoi(strtok(NULL, "/"));
        r_day = atoi(strtok(NULL, "/"));

        schedule[num_sch[r_year][r_month]][r_year][r_month].sch_type = r_type;
        schedule[num_sch[r_year][r_month]][r_year][r_month].sch_day = r_day;

        if (r_type[0] == 'a') {
            r_start_hour = atoi(strtok(NULL, "/"));
            schedule[num_sch[r_year][r_month]][r_year][r_month].sch_start_hour = r_start_hour;


            r_start_min = atoi(strtok(NULL, "/"));
            schedule[num_sch[r_year][r_month]][r_year][r_month].sch_start_min = r_start_min;

            r_end_hour = atoi(strtok(NULL, "/"));
            schedule[num_sch[r_year][r_month]][r_year][r_month].sch_end_hour = r_end_hour;

            r_end_min = atoi(strtok(NULL, "/"));
            schedule[num_sch[r_year][r_month]][r_year][r_month].sch_end_min = r_end_min;

            r_note = strtok(NULL, "/");
            strcpy(schedule[num_sch[r_year][r_month]][r_year][r_month].sch_note, r_note);
            if(r_note == NULL)
                schedule[num_sch[r_year][r_month]][r_year][r_month].sch_note ==NULL;
        }
        else if (r_type[0] == 'e') {

        }
        else {		// b, c, d
            r_note = strtok(NULL, "/");
            strcpy(schedule[num_sch[r_year][r_month]][r_year][r_month].sch_note, r_note);
        }
        num_sch[r_year][r_month]++;

    }


    //sort(student, student + numStudent, compare);

    inFile.close();
}

void Calendar::scheduleWrite() {	////////////////////////////////////// a,e 나눠야 할수도?????????

    ofstream outFile("staff_schedule.txt");
    for (int y = 0; y < 10; y++) {
        for (int m = 1; m < 13; m++) {
            for (int i = 0; i < num_sch[y][m]; i++) {

                if (schedule[i][y][m].sch_type[0] == 'a') {
                    outFile << "a/" << y + 2019 << "/" << m << "/" << schedule[i][y][m].sch_day << "/";
                    outFile << schedule[i][y][m].sch_start_hour << "/" << schedule[i][y][m].sch_start_min << "/";
                    outFile << schedule[i][y][m].sch_end_hour << "/" << schedule[i][y][m].sch_end_min << "/";
                    outFile << schedule[i][y][m].sch_note << endl;
                }
                else {			// e일경우

                }
            }
        }
    }

    outFile.close();

}

int Calendar::dayMonthLimit(int mon) {
    int day_month_lim;
    if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) {
        day_month_lim = 31;
    }
    else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
        day_month_lim = 30;
    }
    else if (mon == 2) {
        if (year % 400 == 0) {
            day_month_lim = 29;
        }
        else if (year % 100 == 0) {
            day_month_lim = 28;
        }
        else if (year % 4 == 0) {
            day_month_lim = 29;
        }
        else {
            day_month_lim = 28;
        }
    }
    return day_month_lim;
}

void Calendar::compareDay() {
    for (int i = 0; i < num_sch[year - 2019][month]; i++) {
        if (schedule[i][year - 2019][month].sch_type[0] == 'b' || schedule[i][year - 2019][month].sch_type[0] == 'c' || schedule[i][year - 2019][month].sch_type[0] == 'd')
            continue;

        if (schedule[i][year - 2019][month].sch_day > schedule[num_sch[year - 2019][month]][year - 2019][month].sch_day) {
            schedule[0][0][0] = schedule[num_sch[year - 2019][month]][year - 2019][month];
            schedule[num_sch[year - 2019][month]][year - 2019][month] = schedule[i][year - 2019][month];
            schedule[i][year - 2019][month] = schedule[0][0][0];
        }
        else if (schedule[i][year - 2019][month].sch_day == schedule[num_sch[year - 2019][month]][year - 2019][month].sch_day && schedule[i][year - 2019][month].sch_start_hour > schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_hour) {
            schedule[0][0][0] = schedule[num_sch[year - 2019][month]][year - 2019][month];
            schedule[num_sch[year - 2019][month]][year - 2019][month] = schedule[i][year - 2019][month];
            schedule[i][year - 2019][month] = schedule[0][0][0];
        }
        else if (schedule[i][year - 2019][month].sch_day == schedule[num_sch[year - 2019][month]][year - 2019][month].sch_day && schedule[i][year - 2019][month].sch_start_hour == schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_hour && schedule[i][year - 2019][month].sch_start_min > schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_min) {
            schedule[0][0][0] = schedule[num_sch[year - 2019][month]][year - 2019][month];
            schedule[num_sch[year - 2019][month]][year - 2019][month] = schedule[i][year - 2019][month];
            schedule[i][year - 2019][month] = schedule[0][0][0];
        }
    }
}

void Calendar::drawDay(int day_week_1) {
    int day_month_lim;
    int week = 0;
    day_month_lim = dayMonthLimit(month);
    for (int i = 1; i <= day_week_1; i++) {
        printf("     ");
    }
    for (int i = 1; i <= day_month_lim; i++) {
        if (day_week_1 == 7) {
            printf("\n");
            day_week_1 = 0;
            week++;
        }
        printf("  ");
        printf("%3d", i);
        day_week_1++;
    }
    if (week == 4)
        printf("\n");
    printf("\n");
}

void Calendar::keyInput(int key_input) {//////////////////////////////////////////갈아엎어야함?!!!

    //num_sch[year - 2019][month]++;

    int day_month_lim;
    int del_sch = 0;
    string str;
    day_month_lim = dayMonthLimit(month);
    if (key_input == 75) {		// LEFT: month--
        if (year == 2019 && month == 1) {

        }
        else month--;
        if (month == 0) {
            month = 12;
            year--;
        }
    }
    if (key_input == 77) {		// RIGHT: month++
        if (year == 2029 && month == 12) {

        }
        else month++;
        if (month == 13) {
            month = 1;
            year++;
        }

    }
    if (key_input == 72) {		// UP: year++
        if (year == 2029) {

        }
        else year++;
    }
    if (key_input == 80) {		// DOWN: year--
        if (year == 2019) {

        }
        else year--;
    }
    if (key_input == 65 || key_input == 97) { // ADD schedule
        system("cls");
        printf("### Add a schedule ###\n");
        printf("Year : %d\n", year);
        //schedule[num_sch[year - 2019][month]][year - 2019][month].sch_year = year;													//sch_year
        printf("Month : %d\n", month);
        //schedule[num_sch[year - 2019][month]][year - 2019][month].sch_month = month;												//sch_month

        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_type = "a";

        int index;
        while(1){
            cout << "Day : ";
            cin >> index;
            while (getchar() != '\n');
            cout << endl;
            if (index >= 1 && index <= day_month_lim)
                break;
        }
        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_day = index;

        while (1) {
            cout << "Start_hour(0~23) : ";
            cin >> index;
            while (getchar() != '\n');
            cout << endl;
            if (index >= 0 && index <= 23)
                break;
        }
        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_hour = index;

        while (1) {
            cout << "Start_min(0~59) : ";
            cin >> index;
            while (getchar() != '\n');
            cout << endl;
            if (index >= 0 && index <= 59)
                break;
        }
        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_min = index;

        while (1) {
            cout << "End_hour(0~23) : ";
            cin >> index;
            while (getchar() != '\n');
            cout << endl;
            if (index >= 0 && index <= 59)
                break;
        }
        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_end_hour = index;

        while (1) {
            cout << "End_min(0~59) : ";
            cin >> index;
            while (getchar() != '\n');
            cout << endl;
            if (index >= 0 && index <= 59)
                break;
        }
        schedule[num_sch[year - 2019][month]][year - 2019][month].sch_end_min = index;

        cout << "Note : ";
        cin >> str;
        while (getchar() != '\n');
        //getchar();
        //fgets(str, MAX_STR, stdin);
        strcpy(schedule[num_sch[year - 2019][month]][year - 2019][month].sch_note, str.c_str());

        compareDay();

        num_sch[year - 2019][month]++;
    }
    if (key_input == 68 || key_input == 100 && num_sch[year - 2019][month] > 0) { // DEL schedule

        while (1) {
            printf("Which schedule do you want to delete? : ");

            cin >> del_sch;
            while(getchar()!='\n');
            if (del_sch >= 1 && del_sch <= num_sch[year - 2019][month])
                break;
        }
        if (schedule[del_sch - 1][year - 2019][month].sch_type[0] == 'a' || schedule[del_sch - 1][year - 2019][month].sch_type[0] == 'e') {
            if (del_sch == num_sch[year - 2019][month]) {
                //schedule[del_sch][year][month] = schedule[del_sch - 1][year - 2019][month];
            }

            else {
                for (int i = del_sch - 1; i < num_sch[year - 2019][month]; i++) {
                    schedule[i][year - 2019][month] = schedule[i + 1][year - 2019][month];
                }
            }

            num_sch[year - 2019][month]--;

            printf("\nSchedule deleted.");
            Sleep(1000);
        }
        else {
            printf("\n공휴일 혹은 행사 일정은 삭제할 수 없습니다.");
            Sleep(1000);
        }


    }
    if (key_input == 9) {
        reset_curr_time();
    }
}

void Calendar::drawCalender() {
    char am_pm[2][3] = { "AM","PM" };

    int day_week_1;		// 그 달의 1일이 무슨 요일인지 계산

    if (month == 1 || month == 2) {
        year--;
        month = month + 12;
        day_week_1 = (1 + (26 * (month + 1) / 10) + year + (year / 4) + 6 * (year / 100) + (year / 400) + 6) % 7;
        year++;
        month = month - 12;
    }
    else {
        day_week_1 = (1 + (26 * (month + 1) / 10) + year + (year / 4) + 6 * (year / 100) + (year / 400) + 6) % 7;
    }
    ////////////////////////////////////////////

    system("cls");		//화면 초기화

    ////////////////////////////////////////////

    printf("\t%d %s \n\n", year, str_month[month]);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    drawDay(day_week_1);
    printf("\n");
    for (int i = 0; i < num_sch[year - 2019][month]; i++) {
        if (schedule[i][year - 2019][month].sch_type[0] == 'a') {	//직원 스케쥴 일때

            if (schedule[i][year - 2019][month].sch_start_hour <= 12 && schedule[i][year - 2019][month].sch_end_hour > 12) {
                printf(" %d.  %d.%d.%d %d:%d %s ~ %d:%d %s %s", i + 1, year, month, schedule[i][year - 2019][month].sch_day, schedule[i][year - 2019][month].sch_start_hour, schedule[i][year - 2019][month].sch_start_min, am_pm[0], schedule[i][year - 2019][month].sch_end_hour - 12, schedule[i][year - 2019][month].sch_end_min, am_pm[1], schedule[i][year - 2019][month].sch_note);
            }
            else if (schedule[i][year - 2019][month].sch_start_hour > 12 && schedule[i][year - 2019][month].sch_end_hour <= 12) {	//다음날 오전으로 넘어가는 경우!
                printf(" %d.  %d.%d.%d %d:%d %s ~ %d:%d %s %s", i + 1, year, month, schedule[i][year - 2019][month].sch_day, schedule[i][year - 2019][month].sch_start_hour - 12, schedule[i][year - 2019][month].sch_start_min, am_pm[1], schedule[i][year - 2019][month].sch_end_hour, schedule[i][year - 2019][month].sch_end_min, am_pm[0], schedule[i][year - 2019][month].sch_note);
            }
            else if (schedule[i][year - 2019][month].sch_start_hour <= 12) {
                printf(" %d.  %d.%d.%d %d:%d %s ~ %d:%d %s %s", i + 1, year, month, schedule[i][year - 2019][month].sch_day, schedule[i][year - 2019][month].sch_start_hour, schedule[i][year - 2019][month].sch_start_min, am_pm[0], schedule[i][year - 2019][month].sch_end_hour, schedule[i][year - 2019][month].sch_end_min, am_pm[0], schedule[i][year - 2019][month].sch_note);
            }
            else if (schedule[i][year - 2019][month].sch_start_hour > 12) {
                printf(" %d.  %d.%d.%d %d:%d %s ~ %d:%d %s %s", i + 1, year, month, schedule[i][year - 2019][month].sch_day, schedule[i][year - 2019][month].sch_start_hour - 12, schedule[i][year - 2019][month].sch_start_min, am_pm[1], schedule[i][year - 2019][month].sch_end_hour - 12, schedule[i][year - 2019][month].sch_end_min, am_pm[1], schedule[i][year - 2019][month].sch_note);
            }
        }
        else if (schedule[i][year - 2019][month].sch_type[0] == 'e') {

        }
        else {
            printf(" %d.  %d.%d.%d %s", i + 1, year, month, schedule[i][year - 2019][month].sch_day, schedule[i][year - 2019][month].sch_note);
        }
        printf("\n");
    }
    printf("\n");
    printf("[ A: add a schedule, D: delete a schedule, TAB: reset to today             ]\n");
    printf("[ LEFT: month--, RIGHT: month++, DOWN: year--, UP: year++, ESC: save & exit]\n");
    printf("[ 한/영 키 주의해 주세요.^^                                                ]\n");

    ////////////////////////////////////////////////////

    int key_input = getch();

    if (key_input == 27) {

        scheduleWrite();

        powerCal = false;
    }


    keyInput(key_input);
}

int Calendar::D_day(int d_year, int d_month, int d_day) {
    int anni_all_day = 0, ye = 0, mo = 0, a = 0;
    int now_all_day = 0, ye2 = 0, mo2 = 0, b = 0;
    int D_day = 0;
    for (int i = 2018; i < d_year; ++i) {
        ye += 365;
        if (dayMonthLimit(2) == 29)
            ye += 366;
    }
    for (int i = 0; i < d_month - 1; ++i) {
        mo += dayMonthLimit(i);
    }
    if (dayMonthLimit(year) == 29 && d_month > 2) {
        a = 1;
    }
    anni_all_day = d_day + ye + mo + a;

    for (int i = 2018; i < year; ++i) {
        ye2 += 365;
        if (dayMonthLimit(2) == 29)
            ye2 += 366;
    }
    for (int i = 0; i < month - 1; ++i) {
        mo2 += dayMonthLimit(i);
    }
    if (dayMonthLimit(year) == 29 && month > 2) {
        b = 1;
    }
    now_all_day = day + ye2 + mo2 + b;
    D_day = (anni_all_day - now_all_day);
    return D_day;
}

vector<int> Calendar::returnTime() {
    vector<int> clock = { year, month, day, hour, minute };
    return clock;
}

void Calendar::PowerCalON() {
    powerCal = true;
}

bool Calendar::checkPowerCal() {
    return powerCal;
}

vector<Schedule> Calendar::get_schedule(vector<Schedule>& sche){
    for(int i = 0; i < 11; i++){
       for(int j = 0; j < 13; j++){
           for(int k = 0; k < 30; k++){
               sche.push_back(this->schedule[k][i][j]);
           }
       }
    }
    return sche;
}

vector<int> Calendar::get_num_schedule(vector<int>& s){

    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 13; j++){
            s.push_back(this->num_sch[i][j]);
        }
    }
    return s;
}

void Calendar::sub_cal(int index){
    if (index == num_sch[year - 2019][month]) {
        //schedule[del_sch][year][month] = schedule[del_sch - 1][year - 2019][month];
    }

    else {
        for (int i = index - 1; i < num_sch[year - 2019][month]; i++) {
            if(i == num_sch[year-2019][month] - 1){

                schedule[i][year-2019][month].sch_day = 0;
                schedule[i][year-2019][month].sch_note;
                schedule[i][year-2019][month].sch_type = "";
                schedule[i][year-2019][month].sch_end_min = 0;
                schedule[i][year-2019][month].sch_end_hour = 0;
                schedule[i][year-2019][month].sch_start_min = 0;
                schedule[i][year-2019][month].sch_start_hour = 0;

            }

            else{

                schedule[i][year - 2019][month] = schedule[i + 1][year - 2019][month];
            }
        }
    }
    num_sch[year - 2019][month]--;

   this->scheduleWrite();
}

void Calendar::add_cal(int index, int sth, int stm, int eh, int em, string str){

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_type = "a";

    int day_month_lim = dayMonthLimit(month);

    //if (index >= 1 && index <= day_month_lim)

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_day = index;

    //if (index >= 0 && index <= 23)

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_hour = sth;

    //if (index >= 0 && index <= 59)

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_start_min = stm;

    //if (index >= 0 && index <= 59)

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_end_hour = eh;

    //if (index >= 0 && index <= 59)

    schedule[num_sch[year - 2019][month]][year - 2019][month].sch_end_min = em;

    strcpy(schedule[num_sch[year - 2019][month]][year - 2019][month].sch_note, str.c_str());

    compareDay();

    num_sch[year - 2019][month]++;

    this->scheduleWrite();
}
