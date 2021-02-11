#include "Product.h"

//Constructor
Product::Product()
{
	this->stock.clear();
	this->discount = 0;
	this->sell = 0;
}

//Destructor
Product::~Product() {
}

//Setter
void Product::setname(string name) {
	this->name = name;
}
void Product::setprice(int price) {
	this->price = price;
}   //���� ����                           
void Product::setstock(int stock) {
	this->stock.push_back(stock);
}
void Product::setvalid_date(int validdate) {
	this->valid_date.push_back(validdate);
}
void Product::setdiscount(int discount) {
	this->discount = discount;
}
void Product::setsell(int sell) {
	this->sell = sell;
}
//void Product::setcategory(int category) {
//	this->category = category;
//}

// �迭�� ��ǰ �߰��� ���� ���Ͽ� ��� ��ǰ �����صּ� �Ź� ���α׷� ���� �� ������ ���Ͽ��� �迭�� ���� �ű�
// �׷��� ��ǰ �߰��ϸ� �� ���α׷� ����� ���� ���� �Ǵϱ� Product update �Լ��� �ʿ�  

//Getter
string Product::getname() {
   return this->name;
}
int Product::getprice() {
	return this->price;
}
vector<int> Product::getstock() {
	return this->stock;
}
vector<int> Product::getvalid_date() {
	return this->valid_date;
}
int Product::getdiscount() {
	return this->discount;
}
int Product::getsell() {
	return this->sell;
}
//int Product::getcategory() {
//	return this->category;
//}



//Fucntions
void Product::setProduct(string name, int price, vector<int> valid_date, vector<int> stock, int discount, int sell) {
	this->setname(name);
	this->setprice(price);
	for (int i = 0; i < valid_date.size(); i++) {
		this->setvalid_date(valid_date.at(i));
		this->setstock(stock.at(i));
	}
	this->setdiscount(discount);
	this->setsell(sell);
	//this->setcategory(category);
} //�迭�� ���
void Product::addstock(int num , int date) {
	this->stock.push_back(num);
	this->valid_date.push_back(date);

}//��� �߰�
int Product::get_allstock()
{
	int sumofstock = 0;
	for (int i = 0; i < this->stock.size(); i++) {
		sumofstock += this->stock[i];
	}
	return sumofstock;
}
int Product::substock(int n) {
	int sum = 0;
	for (int i = 0; i < this->stock.size(); i++) {
		sum += stock[i];
	}
	if (sum < n) {
		//��� �����մϴ� ���
	}
	else {
		while (n > 0) {
			int temp = n;
			n -= this->stock[0];
			this->stock[0] -= temp;

			if (this->stock[0] <= 0) {
				this->stock.erase(stock.begin());
				this->valid_date.erase(valid_date.begin());
			}
		}
	}
	return 1;/////////////////////////////////////////////////////////////////����
}//��� ����
void Product::addsell(int n) {
	this->sell += n;
}
void Product::product_discsard(int n) {
	int sum = 0;
	for (int i = 0; i < this->stock.size(); i++) {
		sum += stock[i];
	}

	if (sum < n) {
		//��� �����մϴ� ���
	}
	else {
		while (n > 0) {
			int temp = n;
			n -= this->stock[0];
			this->stock[0] -= temp;

			if (this->stock[0] <= 0) {
				this->stock.erase(stock.begin());
				this->valid_date.erase(stock.begin());
			}
		}
	}
}//��ǰ ���
void Product::set_discount(int n) {
	this->discount = n;
}//��ǰ ��� �߰�

//���� ���� ���Ѱ�
//���� ������ addProduct�� �ϴ� ��ǰ�� ����س���(���, �������,�Ǹŷ� 0 default) 
// setProduct�� �迭�� ����, addvaldate, addstock���� ��� �߰� �̰Ŵ� �迭������...update�Լ��� �޸��忡�� �������־����
// 