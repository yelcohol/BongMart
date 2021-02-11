#include "Pos.h"


POS::POS(string rep_name, string store_name, string phone_num, string address) {
	powerPos = true;
	set_rep_name(rep_name);
	set_store_name(store_name);
	set_phone_num(phone_num);
	set_address(address);
	transaction.set_info(rep_name, store_name, phone_num, address);//�¿�
	productRead("Product.txt");

}

POS::~POS() {
	//�����Ҵ��� �޸𸮵� free���ֱ�
}

int POS::get_index() {
	int index = 0;

	ifstream inFile("History.txt");
	char Line[100];
	while (!inFile.eof()) {
		inFile.getline(Line, 100);
		index++;
	}
	inFile.close();
	return index;
}

void POS::save_history (history_information _history, int index) {
	ofstream outFile("History.txt", ios::app);

	outFile << _history.age << "\t";
	if (_history.sex) outFile << "Male\t";	//����
	else outFile << "Female\t";	//����
	outFile << _history.time << "\t";
	outFile << setfill('0') << setw(4) << index << endl;

	outFile.close();
}

void POS::search_history(vector<history_information> history, int lage, int rage, bool _sex) {
	int index = 1;
	for (vector<history_information>::size_type i = 0; i < history.size(); ++i) {
		if ((lage <= history[i].age) && (history[i].age < rage) && (history[i].sex == _sex)) {
			cout << history[i].age << "��\t";
			if (history[i].sex) cout << "Male\t";	//����
			else cout << "Female\t";	//����
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
		if (strcmp(strtok(NULL, "\t"), "Female")) history_info.sex = true;	//����
		else history_info.sex = false;	//����
		strcpy(history_info.time, strtok(NULL, "\t"));
		index = atoi(strtok(NULL, "\t"));

		history.push_back(history_info);
	}

	cout << "����\t����\t�ð�\t��ȣ" << endl;
	switch (num) {
	case 1:	//��ü history
		for (vector<history_information>::size_type i = 0; i < history.size(); ++i) {
			cout << history[i].age << "��\t";
			if (history[i].sex) cout << "Male\t";	//����
			else cout << "Female\t";	//����
			cout << history[i].time << "\t";
			cout << setfill('0') << setw(4) << (i + 1) << endl;
		}
		break;

	case 2:	//10�� ����
		search_history(history, 10, 20, true);
		break;

	case 3:	//10�� ����
		search_history(history, 10, 20, false);
		break;

	case 4:	//20�� ����
		search_history(history, 20, 30, true);
		break;

	case 5:	//20�� ����
		search_history(history, 20, 30, false);
		break;

	case 6:	//30�� ����
		search_history(history, 30, 40, true);
		break;

	case 7:	//30�� ����
		search_history(history, 30, 40, false);
		break;

	case 8:	//40�� ����
		search_history(history, 40, 50, true);
		break;

	case 9:	//40�� ����
		search_history(history, 40, 50, false);
		break;
	}

	inFile.close();
}

void POS::check_history() {
	int input;
	cout << "-����Ű 1  -  ��ü �����丮 " << endl;
	cout << "-����Ű 2  -  10�� ����  " << endl;
	cout << "-����Ű 3  -  10�� ����  " << endl;
	cout << "-����Ű 4  -  20�� ����  " << endl;
	cout << "-����Ű 5  -  20�� ����  " << endl;
	cout << "-����Ű 6  -  30�� ����  " << endl;
	cout << "-����Ű 7  -  30�� ����  " << endl;
	cout << "-����Ű 8  -  40�� ����  " << endl;
	cout << "-����Ű 9  -  40�� ����  " << endl;
	cout << "�޴��� �����Ͻʽÿ� : ";
	cin >> input;
	while (getchar() != '\n');

	system("cls");
	print_history(input);
	while (getchar() != '\n');
}
//�� �м�

void POS::new_customer() {
	string name;
	string sex_s;
	bool sex;
	int age;
	string tel;

	cout << "�̸��� �Է����ּ���." << endl;
	cin >> name;
	cout << "������ �Է����ּ���." << endl;
	cin >> sex_s;
	if ((sex_s == "Female") || (sex_s == "female")) sex = false;
	else sex = true;
	cout << "���̸� �Է����ּ���." << endl;
	cin >> age;
	cout << "��ȭ��ȣ�� �Է����ּ���." << endl;
	cin >> tel;

	Customer customer(name, sex, age, tel);

	ofstream outFile("Customer.txt", ios::app);

	outFile << customer.get_name() << "\t";
	outFile << customer.get_sex_s() << "\t";
	outFile << customer.get_age() << "\t";
	outFile << customer.get_tel() << endl;

	outFile.close();
}
//�ű� ��
void POS::search_tel(vector<Customer> customers, vector<Customer> good_customers, string _tel) {
	int index = 1;
	for (vector<Customer>::size_type i = 0; i < customers.size(); ++i) {
		if (customers[i].Check_tel(_tel)) {
			cout << index++ << "." << "\t";
			cout << customers[i].get_name() << "\t";
			cout << customers[i].get_sex_s() << "\t";
			cout << customers[i].get_age() << "\t";
			cout << customers[i].get_tel() << endl;
			
			good_customers.push_back(Customer(customers[i].get_name(), customers[i].get_sex(), customers[i].get_age(), customers[i].get_tel()));
		}
		else continue;
	}
}

vector <Customer> POS::make_customers(vector <Customer> customers) {
	string name;
	string sex_s;
	bool sex;
	int age;
	string tel;

	ifstream inFile("Customer.txt");

	char Line[100];

	inFile.getline(Line, 100);
	while (!inFile.eof()) {
		inFile.getline(Line, 100);

		if (Line[0] == NULL) break;

		name = strtok(Line, "\t");
		sex_s = strtok(NULL, "\t");
		if ((sex_s == "Female") || (sex_s == "female")) sex = false;
		else sex = true;
		age = atoi(strtok(NULL, "\t"));
		tel = strtok(NULL, "\t");

		customers.push_back(Customer(name, sex, age, tel));
	}
	inFile.close();
	return customers;
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
	int input;
	cout << "*** ������ ��ü���� 9�� ***" << endl;
	cout << "*** ��Ʈ ���� ���α׷�  ***" << endl << endl;

	cout << "-����Ű 1  -  �޷� " << endl;
	cout << "-����Ű 2  -  ���  " << endl;
	cout << "-����Ű 3  -  ���� ���� (����) " << endl;
	cout << "-����Ű 4  -  ���� �Է� (����)  " << endl;
	cout << "-����Ű 5  -  ���� �Ա� & ���" << endl;
	cout << "-����Ű 6  -  �Ǹŷ� �ʱ�ȭ" << endl;
	cout << "-����Ű 7  -  �� �м� " << endl;
	cout << "-����Ű 8  -  ��ǰ ���" << endl;
	cout << "-����Ű 9  -  ��ǰ �߰� & ���� & ����" << endl;
	cout << "-����Ű 10 -  ��� ���� ����" << endl;
	cout << "-����Ű 11 -  ���� ����" << endl;
	cout << "-����Ű 12 -  ��ǰ ���" << endl;
	cout << "-����Ű 13 -  �ű� �� ���" << endl;
	cout << "-����Ű 0  -  ��ǰ ���� ���� & ����" << endl << endl;
	cout << "�޴��� �����Ͻʽÿ� : ";
	cin >> input;
	while (getchar() != '\n');


	system("cls");
	switch (input)
	{
	case 1:                  //����Ű 1 - �޷�
		calendarON();
		break;
	case 2:                  //����Ű 2 - ���
		input_buy_product();
		productWrite("Product.txt");   //����
		break;
	case 3:                  //����Ű 3 - ���� ���� (����) 
		check_cash();
		break;
	case 4:                  //����Ű 4 - ���� �Է� (����) 
		input_total_cash();
		break;
	case 5:                  //����Ű 5 - ���� �Ա� & ���
		modify_cash();
		break;
	case 6:                  //����Ű 6 - �Ǹŷ� �ʱ�ȭ
		reset_sell();
		break;
	case 7:                  //����Ű 7 - �ŷ� ����
		check_history();
		break;
	case 8:                  //����Ű 8 - ��ǰ ���
		print_product_list();
		break;
	case 9:                  //����Ű 9 - ��ǰ �߰� & ���� & ����
		modify_product();
		productWrite("Product.txt");   //����
		break;
	case 10:               //����Ű 10 - ��� ���� ����
		modify_discount();
		break;
	case 11:
		staff.result();

		break;
	case 12:               
		trash_product_clear();
		break;

		////////////////////////// �ѱݾ�

		////////////////////////// ��ǰ ���

		/////////////////////////// ���� ���� - �̸� ����

	case 13:
		new_customer();
		break;
	case 0:                  //����Ű 0 - ����
		powerPos = false;
		productWrite("Product.txt");   //����
		break;
	default:

		break;
	}


	system("cls");
}



void POS::set_total_money() {
	total_money = (cash[0] * 50000) + (cash[1] * 10000) + (cash[2] * 5000) + (cash[3] * 1000) + (cash[4] * 500) + (cash[5] * 100) + (cash[6] * 50) + (cash[7] * 10) + card_money;
}

void POS::set_total_cash(int* set_cash) {
	for (int i = 0; i < 7; i++)
		cash[i] = set_cash[i];
}

void POS::input_total_cash() {
	int set_cash[8] = { 0, };
	cout << "50000 ���� : ";
	cin >> set_cash[0];
	while (getchar() != '\n');

	cout << "10000 ���� : ";
	cin >> set_cash[1];
	while (getchar() != '\n');

	cout << "5000 ���� : ";
	cin >> set_cash[2];
	while (getchar() != '\n');

	cout << "1000�� ���� : ";
	cin >> set_cash[3];
	while (getchar() != '\n');

	cout << "500�� ���� : ";
	cin >> set_cash[4];
	while (getchar() != '\n');

	cout << "100�� ���� : ";
	cin >> set_cash[5];
	while (getchar() != '\n');

	cout << "50�� ���� : ";
	cin >> set_cash[6];
	while (getchar() != '\n');

	cout << "10�� ���� : ";
	cin >> set_cash[7];
	while (getchar() != '\n');

	set_total_cash(set_cash);
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
	cout << "50000 ���� : ";
	cin >> check_cash[0];
	while (getchar() != '\n');

	cout << "10000 ���� : ";
	cin >> check_cash[1];
	while (getchar() != '\n');

	cout << "5000 ���� : ";
	cin >> check_cash[2];
	while (getchar() != '\n');

	cout << "1000�� ���� : ";
	cin >> check_cash[3];
	while (getchar() != '\n');

	cout << "500�� ���� : ";
	cin >> check_cash[4];
	while (getchar() != '\n');

	cout << "100�� ���� : ";
	cin >> check_cash[5];
	while (getchar() != '\n');

	cout << "50�� ���� : ";
	cin >> check_cash[6];
	while (getchar() != '\n');

	cout << "10�� ���� : ";
	cin >> check_cash[7];
	while (getchar() != '\n');

	check_money = (check_cash[0] * 50000) + (check_cash[1] * 10000) + (check_cash[2] * 5000) + (check_cash[3] * 1000) + (check_cash[4] * 500) + (check_cash[5] * 100) + (check_cash[6] * 50) + (check_cash[7] * 10);
	if (check_money == (total_money - card_money)) {
		cout << "���ݰ����� :" << 0;
	}
	else {
		cout << "���ݰ����� :" << check_money - (total_money - card_money);
	}
	Sleep(1000);
}

void POS::modify_cash() {
	int input;
	cout << "���� �Ա� : 0 ��� : 1" << endl;
	cin >> input;
	while (getchar() != '\n');

	system("cls");

	if (input == 0) {
		add_total_cash();
	}
	else if (input == 1) {
		sub_total_cash();
	}
}

void POS::add_total_cash() {
	set_total_money();

	int input, i;
	cout << "�Ա��� ���� ������ �Է��Ͻÿ� : ";
	cin >> input;
	while (getchar() != '\n');
	switch (input)
	{
	case 50000:
		i = 0;
		break;
	case 10000:
		i = 1;
		break;

	case 5000:
		i = 2;
		break;

	case 1000:
		i = 3;
		break;

	case 500:
		i = 4;
		break;

	case 100:
		i = 5;
		break;

	case 50:
		i = 6;
		break;

	case 10:
		i = 7;
		break;

	default:
		cout << "�߸��� ������ �ԷµǾ����ϴ�." << endl;
		return;
		break;
	}

	cout << "�� ���� �Ա��Ͻðڽ��ϱ�?? : ";
	cin >> input;
	while (getchar() != '\n');
	if (i > 0) {
		cash[i] += input;
		set_total_money();
	}


}

void POS::sub_total_cash() {
	set_total_money();

	int input, i;
	cout << "����� ���� ������ �Է��Ͻÿ� : ";
	cin >> input;
	while (getchar() != '\n');
	switch (input)
	{
	case 50000:
		i = 0;
		break;
	case 10000:
		i = 1;
		break;

	case 5000:
		i = 2;
		break;

	case 1000:
		i = 3;
		break;

	case 500:
		i = 4;
		break;

	case 100:
		i = 5;
		break;

	case 50:
		i = 6;
		break;

	case 10:
		i = 7;
		break;

	default:
		cout << "�߸��� ������ �ԷµǾ����ϴ�." << endl;
		return;
		break;
	}

	cout << "�� ���� ����Ͻðڽ��ϱ�?? : ";
	cin >> input;
	while (getchar() != '\n');
	if (i > 0 && cash[i] >= input) {
		cash[i] -= input;
		set_total_money();
	}
	else if (i > 0 && cash[i] < input) {
		cout << "�ܵ��� ������ ���ڶ��ϴ�." << endl;
	}
}

void POS::reset_sell() {
	for (int i = 0; i < product.size(); i++)
		product.at(i).setsell(0);
}

void POS::print_product_list() {


	for (int i = 0; i < product.size(); i++) {
		cout << i + 1 << ". " << product.at(i).getname() << endl;
		cout << "*���� : " << product.at(i).getprice() << endl;
		cout << "*��� �� �������*" << endl;
		for (int j = 0; j < product.at(i).getstock().size(); j++) {
			cout << product.at(i).getstock().at(j) << "�� - ";
			cout << product.at(i).getvalid_date().at(j) << "����" << endl;
		}
		cout << "*��� ���� : " << discount_string(product.at(i).getdiscount()) << endl;
		cout << "*���� �Ǹŷ� : " << product.at(i).getsell() << "��" << endl;
		cout << "------------------------------------------------------------" << endl;
	}
	cout << "���� Ű �Է��ϸ� ���ư��ϴ�." << endl;
	int i;
	//getch();
	//cin >> i;
	while (getchar() != '\n');
}

void POS::modify_product() {
	int index;
	cout << "��� ++ : 1" << endl;
	cout << "��� -- : 2 - (���Ŵ� ������� ���� ������)" << endl;
	cout << "��ǰ ++ : 3 - (�Ż�ǰ)" << endl;
	cout << "��ǰ -- : 4" << endl;
	cout << "�޴��� ����ּ��� : ";
	cin >> index;
	while (getchar() != '\n');

	system("cls");

	switch (index) {
	case 1:
		add_stock();
		break;
	case 2:
		sub_stock();
		break;
	case 3:
		add_product();
		break;
	case 4:
		sub_product();
		break;

	}
}

void POS::add_stock() {
	int index, num, date;
	while (1) {
		cout << "��� �߰��� ��ǰ�� ��ȣ�� �Է��Ͻÿ� : ";
		cin >> index;
		while (getchar() != '\n');
		cout << endl;
		if (index >= 1 && index <= product.size())
			break;
	}
	while (1) {
		cout << "�߰��� ������ �Է��Ͻÿ� : ";
		cin >> num;
		while (getchar() != '\n');
		cout << endl;
		if (num >= 1)
			break;
	}


	calendar.reset_curr_time();
	vector<int> time = calendar.returnTime();

	while (1) {
		cout << "��ǰ���� ��������� �Է��Ͻÿ� (�� : 20191225) : ";
		cin >> date;
		while (getchar() != '\n');
		cout << endl;
		if (date >= 100000000) {
			cout << "�߸��� ���� �ԷµǾ����ϴ�.";
			continue;
		}
		else if (date >= 10000 * time[0] + 100 * time[1] + time[2])   // ���� ���� ��¥
			break;
		else {
			cout << "��������� �̹� ���� ��ǰ�Դϴ�.";
			return;
		}
	}

	product.at(index).addstock(num, date);
}

void POS::sub_stock() {
	int index, num, date;
	while (1) {
		cout << "��� ������ ��ǰ�� ��ȣ�� �Է��Ͻÿ� : ";
		cin >> index;
		while (getchar() != '\n');
		cout << endl;
		if (index >= 1 && index <= product.size())
			break;
	}

	while (1) {
		cout << "������ ������ �Է��Ͻÿ� : ";
		cin >> num;
		while (getchar() != '\n');
		cout << endl;
		if (num >= 1 && num <= product.at(index).get_allstock())
			break;
	}
	product.at(index).substock(num);

	cout << "���� �Ϸ�";
	Sleep(1000);
}

void POS::add_product() {
	string i_name;
	int i_price, i_stock, i_valid_date;
	int i_sell = 0;
	int i_discount = 0;

	cout << "�߰��� ��ǰ�� �̸��� �Է��Ͻÿ� : ";
	cin >> i_name;
	while (getchar() != '\n');
	//strcpy(schedule[num_sch[year - 2019][month]][year - 2019][month].sch_note, i_name.c_str());

	while (1) {
		cout << "�߰��� ��ǰ�� ������ �Է��Ͻÿ� : ";
		cin >> i_price;
		while (getchar() != '\n');
		cout << endl;
		if (i_price >= 10 && i_price % 10 == 0)
			break;
		else {
			cout << "������ 10�� ����� ������ �ּ���." << endl;
		}
	}

	while (1) {
		cout << "�߰��� ������ �Է��Ͻÿ� : ";
		cin >> i_stock;
		while (getchar() != '\n');
		cout << endl;
		if (i_stock >= 1)
			break;
	}


	calendar.reset_curr_time();
	vector<int> time = calendar.returnTime();

	while (1) {
		cout << "��ǰ���� ��������� �Է��Ͻÿ� (�� : 20191225) : ";
		cin >> i_valid_date;
		while (getchar() != '\n');
		cout << endl;
		if (i_valid_date >= 100000000) {
			cout << "�߸��� ���� �ԷµǾ����ϴ�.";
			continue;
		}
		else if (i_valid_date >= 10000 * time[0] + 100 * time[1] + time[2])   // ���� ���� ��¥
			break;
		else {
			cout << "��������� �̹� ���� ��ǰ�Դϴ�.";
			return;
		}
	}

	while (1) {
		cout << "�߰��� ��ǰ�� ��������� �Է��Ͻÿ� : ";
		cin >> i_discount;
		while (getchar() != '\n');
		cout << endl;
		if (i_discount >= 0)
			break;
	}

	vector <int> dumy;
	Product input_p;
	input_p.setProduct(i_name, i_price, dumy, dumy, i_discount, i_sell);
	input_p.addstock(i_stock, i_valid_date);

	product.push_back(input_p);

}

void POS::sub_product() {
	int index, num, date;
	while (1) {
		cout << "������ ��ǰ�� ��ȣ�� �Է��Ͻÿ� : ";
		cin >> index;
		while (getchar() != '\n');
		cout << endl;
		if (index >= 1 && index <= product.size())
			break;
	}
	product.erase(product.begin() + index - 1);
}




void POS::input_buy_product() {

	char in[100];
	int input;
	///////////////////////////////////�¿�
	vector<string> r_name;
	vector<int> r_price;
	vector<int> r_count;
	vector<int> r_discount;
	/////////////////////////////////

	sum_purchase = 0;
	purchase.clear();
	purchase_num.clear();

	while (1) {                     // ������ ��ǰ�� ���ڵ�(����)�� �Է�
		cin >> in;
		while (getchar() != '\n');
		if (in[0] == '?')            //�ƹ��͵����� ���͸� ������
			break;

		
		input = atoi(in);
		purchase.push_back(input);
		purchase_num.push_back(1);

		cout << "��� - " << discount_string(product.at(input).getdiscount()) << endl;


		for (int i = 0; i < purchase.size() - 1; i++) {            //���� ��ǰ�� ��� ������ up
			if (input == purchase[i]) {
				purchase_num[i]++;
				purchase.pop_back();
				purchase_num.pop_back();
			}

		}
	}
	if (purchase.size() == 0) {
		cout << "�ֹ� ��ǰ�� �����ϴ�!" << endl;
		return;
	}
	for (int i = 0; i < purchase.size(); i++) {
		if (this->product[purchase[i]].get_allstock() < purchase_num[i]) {
			cout << "��� �����մϴ� (" << purchase[i] << ")" << endl;
			purchase.erase(purchase.begin() + i);
		}
	}

	for (int i = 0; i < purchase.size(); i++) {
		if(product.at(i).getdiscount() < 10 && product.at(i).getdiscount() > 0)
			sum_purchase += (product[purchase[i]].getprice() * purchase_num[i] / 10 * (10 - i));//�¿�
		else
			sum_purchase += (product[purchase[i]].getprice() * purchase_num[i]);
	}

	while (1) {
		cout << "���� ���� = 0 , ī�� ���� = 1 : " << endl;
		cin >> input;
		while (getchar() != '\n');
		if (input == 0 || input == 1)
			break;
	}
	int card_cash = input;

	if (card_cash) {               // ī�� ����

		this->card_money += this->sum_purchase;      //ī�� �Ӵ� ����

		for (int i = 0; i < purchase.size(); i++) {
			int kkk = 0;//////�¿�

			product[purchase[i]].addsell(purchase_num[i]);
			product[purchase[i]].substock(purchase_num[i]);    //��� ����  
			
			////////////////////////�¿�
			kkk += purchase_num[i];

			r_name.push_back(product[purchase[i]].getname());
			if (product[purchase[i]].getdiscount() < 10 && product[purchase[i]].getdiscount() > 0)
				r_price.push_back(product[purchase[i]].getprice() / 10 * (10 - product[purchase[i]].getdiscount()));
			else
				r_price.push_back(product[purchase[i]].getprice());

			r_discount.push_back(product[purchase[i]].getdiscount());
			///////////////////////
			if (product.at(purchase[i]).getdiscount() == 11) {
				product[purchase[i]].addsell(purchase_num[i]);
				product[purchase[i]].substock(purchase_num[i]);
				kkk += purchase_num[i];//////�¿�
			}
			else if (product.at(purchase[i]).getdiscount() == 21) {
				product[purchase[i]].addsell(purchase_num[i] / 2);
				product[purchase[i]].substock(purchase_num[i] / 2);
				kkk += purchase_num[i]/ 2;//////�¿�
			}
			r_count.push_back(kkk);//////�¿�
		}

		transaction.add_transaction(r_name, r_price, r_count, r_discount, sum_purchase);//�¿�
	}
	else {                  // ���� ����
		while (1) {
			cout << "���� �ݾ� �Է� : " << endl;
			cin >> this->get_money;
			while (getchar() != '\n');
			//qt���� �߰� ���� ��¥���� ���� �޴��� 
			if (this->get_money >= sum_purchase) {

				break;
			}
			cout << "�ݾ��� �����մϴ�" << endl;
		}
		this->change = this->get_money - sum_purchase;            //�Ž�����
		this->calculate_cash_buy(this->change);                  //���� �� �Ž����� ���?
		for (int i = 0; i < purchase.size(); i++) {
			int kkk = 0;//////�¿�

			product[purchase[i]].addsell(purchase_num[i]);
			product[purchase[i]].substock(purchase_num[i]);         //��� ����
			////////////////////////�¿�
			kkk += purchase_num[i];

			r_name.push_back(product[purchase[i]].getname());
			if (product[purchase[i]].getdiscount() < 10 && product[purchase[i]].getdiscount() > 0)
				r_price.push_back(product[purchase[i]].getprice() / 10 * (10 - product[purchase[i]].getdiscount()));
			else
				r_price.push_back(product[purchase[i]].getprice());

			r_discount.push_back(product[purchase[i]].getdiscount());
			///////////////////////
			if (product.at(purchase[i]).getdiscount() == 11) {
				product[purchase[i]].addsell(purchase_num[i]);
				product[purchase[i]].substock(purchase_num[i]);
				kkk += purchase_num[i];//////�¿�
			}
			else if (product.at(purchase[i]).getdiscount() == 21) {
				product[purchase[i]].addsell(purchase_num[i] / 2);
				product[purchase[i]].substock(purchase_num[i] / 2);
				kkk += purchase_num[i] / 2;//////�¿�
			}
			r_count.push_back(kkk);//////�¿�
		}
		transaction.add_transaction(r_name, r_price, r_count, r_discount, sum_purchase);//�¿�
	}

	system("cls");

	vector <Customer> customers, good_customers;
	customers = make_customers(customers);

	string _tel;
	cout << "��ȭ��ȣ ���ڸ� 4�ڸ��� �Է����ּ���." << endl;
	cin >> _tel;
	
	search_tel(customers, good_customers, _tel);

	cout << "��ȣ�� �Է����ּ���." << endl;
	cin >> input;

	history_information history;
	history.age = good_customers[input - 1].get_age();
	history.sex = good_customers[input - 1].get_sex();
	Calendar calendar;
	vector<int> cur_time = calendar.returnTime();
	char time[6];
	time[0] = (cur_time[4] / 10) + 48;
	time[1] = (cur_time[4] % 10) + 48;
	time[2] = ':';
	time[3] = (cur_time[5] / 10) + 48;
	time[4] = (cur_time[5] % 10) + 48;
	time[5] = '\0';
	strcpy(history.time, time);

	int index = get_index();

	save_history(history, index + 1);

	transaction.print_receipt(transaction.get_tran_num() - 1);
	transaction.transactionWrite("Transaction.txt");
	Sleep(5000);
	//������ - purchase �̿��ؼ�!!


}

void POS::calculate_cash_buy(int q) {

	set_total_money();

	// (�����ұݾ�) �� (��ǰ���� * ��ǰ����) ����
		  // (�����ұݾ�) �� (��ǰ���� * ��ǰ����) �ؼ� �Ž����� ���
	cout << "�Ž����� : " << q << endl;
	if (cash[0] < q / 50000) {
		cout << "50000�� : " << cash[0];
		cout << "\t50000���� �����մϴ�." << endl;
		q -= (cash[0] * 50000);
		cash[0] = 0;

	}
	else {
		cout << "50000�� :   " << q / 50000 << endl;
		cash[0] = cash[0] - (q / 50000);
		q = q % 50000;
	}


	if (cash[1] < q / 10000) {
		cout << "10000�� :  " << cash[1];
		cout << "\t10000���� �����մϴ�." << endl;
		q -= (cash[1] * 10000);
		cash[1] = 0;
	}
	else {
		cout << "10000�� :   " << q / 10000 << endl;
		cash[1] = cash[1] - (q / 10000);
		q = q % 10000;
	}


	if (cash[2] < q / 5000) {
		cout << "5000�� :  " << cash[2];
		cout << "\t5000���� �����մϴ�." << endl;
		q -= (cash[2] * 5000);
		cash[2] = 0;
	}
	else {
		cout << "5000�� :   " << q / 5000 << endl;
		cash[2] = cash[2] - (q / 5000);
		q = q % 5000;
	}


	if (cash[3] < q / 1000) {
		cout << "1000�� :  " << cash[3];
		cout << "\t1000���� �����մϴ�." << endl;
		q -= (cash[3] * 1000);
		cash[3] = 0;
	}
	else {
		cout << "1000�� :  " << q / 1000 << endl;
		cash[3] = cash[3] - (q / 1000);
		q = q % 1000;
	}


	if (cash[4] < q / 500) {
		cout << "500�� :  " << cash[4];
		cout << "\t500���� �����մϴ�." << endl;
		q -= (cash[4] * 500);
		cash[4] = 0;
	}
	else {
		cout << "500�� :  " << q / 500 << endl;
		cash[4] = cash[4] - (q / 500);
		q = q % 500;
	}


	if (cash[5] < q / 100) {
		cout << "100�� :  " << cash[5];
		cout << "\t100���� �����մϴ�." << endl;
		q -= (cash[5] * 100);
		cash[5] = 0;
	}
	else {
		cout << "100�� :  " << q / 100 << endl;
		cash[5] = cash[5] - (q / 100);
		q = q % 100;
	}


	if (cash[6] < q / 50) {
		cout << "50�� :  " << cash[6];
		cout << "\t50���� �����մϴ�." << endl;
		q -= (cash[6] * 50);
		cash[6] = 0;
	}
	else {
		cout << "50�� :  " << q / 50 << endl;
		cash[6] = cash[6] - (q / 50);
		q = q % 50;
	}


	if (cash[7] < q / 10) {
		cout << "10�� :  " << cash[7];
		cout << "\t10���� �����մϴ�." << endl;
		q -= (cash[7] * 10);
		cash[7] = 0;
	}
	else {
		cout << "10�� :  " << q / 10 << endl;
		cash[7] = cash[7] - (q / 10);
	}

	if (total_money - card_money < q) {
		cout << "�ܾ��� �����մϴ�" << endl;
	}


}

void POS::modify_discount() {
	
	int i_index;
	int i_discount = 0;

	cout << "0 : ��� ���� | 1~9 : 10% ~ 90% ���� | 11 : 1+1 ��� | 21 : 2+1 ���" << endl;
	cout << "��� ������ ������ ��ǰ�� ��ȣ�� �Է��Ͻÿ� : ";
	cin >> i_index;
	while (getchar() != '\n');

	while (1) {
		cout << "������ ��� ������ �Է��Ͻÿ� : ";
		cin >> i_discount;
		while (getchar() != '\n');
		cout << endl;
		if (i_discount >= 0 && i_discount < 10)
			break;
		else if (i_discount == 11 || i_discount == 21)
			break;
		else {
			cout << "�߸��� ���� �ԷµǾ����ϴ�." << endl;
		}
	}
	product.at(i_index).setdiscount(i_discount);
}


string POS::discount_string(int dis) {
	switch (dis) {
	case 0:
		return "��� ����";
	case 1:
		return "10% ����";
	case 2:
		return "20% ����";
	case 3:
		return "30% ����";
	case 4:
		return "40% ����";
	case 5:
		return "50% ����";
	case 6:
		return "60% ����";
	case 7:
		return "70% ����";
	case 8:
		return "80% ����";
	case 9:
		return "90% ����";
	case 11:
		return "1+1 ���";
	case 21:
		return "2+1 ���";

	}
}

void POS::trash_product_clear() {
	int index, date;

	calendar.reset_curr_time();
	vector<int> time = calendar.returnTime();


	cout << "***������� ���� ��ǰ ���***" << endl;
	int num = 0;
	for (int i = 0; i < product.size(); i++) {
		for (int j = 0; j < product.at(i).getstock().size(); j++) {

			if (product.at(i).getvalid_date().at(j) >= 10000 * time[0] + 100 * time[1] + time[2])
				continue;
			else {
				cout << i + 1 << ". " << product.at(i).getname() << endl;
				cout << product.at(i).getstock().at(j) << "�� - ";
				cout << product.at(i).getvalid_date().at(j) << "����" << endl;
				num++;
			}



		}
		product.at(i).substock(num);
	}


	Sleep(5000);
	cout << endl << "���� �Ϸ�";
	Sleep(2000);
	productWrite("Product.txt");
}



void POS::calendarON() {
	calendar.PowerCalON();
	while (1) {
		calendar.drawCalender();
		if (!calendar.checkPowerCal())
			break;
	}
}


bool POS::checkPowerPos() {
	return powerPos;
}