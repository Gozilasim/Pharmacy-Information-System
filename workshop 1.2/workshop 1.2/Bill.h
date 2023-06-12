#ifndef BILL_H
#define BILL_H
#include <string>
#include<ctime>

using namespace std;

class Bill
{
public:
	string Bill_ID;
	string Prescription_ID;
	string Medicine_ID;
	string Customer_ID;
	int Quantity;
	double TotalPrice;
	string PaymentType;
	string DateOfBill;
	int count;
	double total;
	Bill* next;



};



#endif 
