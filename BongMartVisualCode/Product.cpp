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
}   //가격 설정                           
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

// 배열에 물품 추가한 다음 파일에 모든 물품 저장해둬서 매번 프로그램 시작 할 때마다 파일에서 배열로 정보 옮김
// 그러면 물품 추가하면 그 프로그램 실행시 부터 적용 되니까 Product update 함수도 필요  

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
} //배열에 등록
void Product::addstock(int num , int date) {
	this->stock.push_back(num);
	this->valid_date.push_back(date);

}//재고 추가
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
		//재고가 부족합니다 출력
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
	return 1;/////////////////////////////////////////////////////////////////수정
}//재고 감소
void Product::addsell(int n) {
	this->sell += n;
}
void Product::product_discsard(int n) {
	int sum = 0;
	for (int i = 0; i < this->stock.size(); i++) {
		sum += stock[i];
	}

	if (sum < n) {
		//재고가 부족합니다 출력
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
}//물품 폐기
void Product::set_discount(int n) {
	this->discount = n;
}//물품 행사 추가

//지금 구현 안한것
//지금 순서가 addProduct로 일단 제품을 등록해놓고(재고량, 유통기한,판매량 0 default) 
// setProduct로 배열에 저장, addvaldate, addstock으로 재고량 추가 이거는 배열에서만...update함수로 메모장에도 저장해주어야함
// 