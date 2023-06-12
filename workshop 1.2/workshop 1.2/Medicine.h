#ifndef MEDICINE_H
#define MEDICINE_H


class Medicine
{
	public:
		std::string Medicine_ID;
		std::string Supplier_ID;
		std::string Manager_ID;
		std::string Staff_ID;
		std::string MedicineType;
		std::string MedicineBrand;
		double Price;
		int Quantity;
		int Restock;
		Medicine* next;


};


#endif 

