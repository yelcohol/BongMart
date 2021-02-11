#include <iostream>
#include "Calendar.h"
#include "Pos.h"

using namespace std;

int main() {

	string rep_name = "이태운";
	string store_name = "이마트";
	string phone_num = "010-3222-3474";
	string address = "중앙대학교";

	POS pos(rep_name, store_name, phone_num, address);
	while (1) {
		pos.mainMenu();
		if (!pos.checkPowerPos())
			break;
	}

	return 0;
}