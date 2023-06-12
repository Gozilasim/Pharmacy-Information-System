#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

using namespace std;

class Customer
{
	public:
		string Customer_ID;
		string Password;
		string C_Name;
		string C_IdentityCard;
		string C_Address;
		string C_HpNo;
		string C_Email;
		Customer* next;
 

};



#endif 


