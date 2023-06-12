#include "Medicine.h"
#include "Supplier.h"
#include"Staff.h"
#include "Customer.h"
#include"Pharmacist.h"
#include"Prescription.h"
#include"Bill.h"
#include "Sales.h"


#ifndef MANAGER_H
#define MANAGER_H



class Manager
{

public:

	string Manager_ID;
	string Password;
	string M_Name;
	string M_Address;
	string M_HpNo;
	string M_Email;
	string M_Branch;
	Manager* next;
	
	Customer* customer;
	
	Manager* getManagerID();
	Manager* getManagerID(std::string Manager_ID);
	Manager* getManagerByName(std::string M_Name);

	//Medicine
	int AddMedicine(Medicine* medicine);
	int AddMedicineWithoutManagerID(Medicine* medicine);
	int DeleteMedicine(Medicine* medicine);
	int UpdateMedicineSupplierID(Medicine* medicine);
	int UpdateMedicineManagerID(Medicine* medicine);
	int UpdateMedicineStaffID(Medicine* medicine);
	int UpdateMedicineMedicineType(Medicine* medicine);
	int UpdateMedicineMedicineBrand(Medicine* medicine);
	int UpdateMedicinePrice(Medicine* medicine);
	int UpdateMedicineQuantity(Medicine* medicine);
	Medicine* getMedicine(std::string Medicine_ID);
	Medicine* getMedicineBySupplierID(std::string Supplier_ID);
	Medicine* getMedicineByManagerID(std::string Manager_ID);
	Medicine* getMedicineByStaffID(std::string Staff_ID);
	Medicine* getMedicineByMedicineType(std::string MedicineType);
	Medicine* getMedicineByMedicineBrand(std::string MedicineBrand);
	Medicine* getMedicine(double Price1, double Price2);
	Medicine* getMedicineIDtoInsert();   // get the first ID from database by using desecnding method



	//Supplier
	int AddSupplier(Supplier* supplier);
	int DeleteSupplier(Supplier* supplier);
	int UpdateSupplierName(Supplier* supplier);
	int UpdateSupplierAddress(Supplier* supplier);
	int UpdateSupplierHpNo(Supplier* supplier);
	int UpdateSupplierEmail(Supplier* supplier);
	Supplier* getSupplier(std::string Supplier_ID);
	Supplier* getSupplierByName(std::string Sp_Name);
	Supplier* getSupplierByHpNo(std::string Sp_HpNo);
	Supplier* getSupplierByIDtoInsert();                 // get the first ID from database by using desecnding method


	//Staff
	int AddStaff(Staff* staff);
	int DeleteStaff(Staff* staff);
	int UpdateStaffPassword(Staff* staff);
	int UpdateStaffAddress(Staff* staff);
	int UpdateStaffHpNo(Staff* staff);
	int UpdateStaffEmail(Staff* staff);
	int UpdateStaffBranchnManagerID(Staff* staff);
	Staff* getStaffByStaffID(std::string Staff_ID);
	Staff* getStaffByName(std::string S_Name);
	Staff* getStaffByHpNo(std::string S_HpNo);
	Staff* getStaffByBranch(std::string S_Branch);
	Staff* getStaffByManagerID(std::string Manager_ID);
	Staff* getStaffIDtoInsert();                 // get the first ID from database by using desecnding method
	

	//Customer
	int AddCustomer(Customer* customer);
	int DeleteCustomer(Customer* customer);
	int UpdateCustomerAddress(Customer* customer);
	int UpdateCustomerHpNo(Customer* customer);
	int UpdateCustomerEmail(Customer* customer);
	int UpdateCustomerPassword(Customer* customer);
	Customer* getCustomerByID(std::string Customer_ID);
	Customer* getCustomerByName(std::string C_Name);
	Customer* getCustomerByIC(std::string C_IdentityCard);
	Customer* getCustomerByHpNo(std::string C_HpNo);

	//Pharmacist
	int AddPharmacist(Pharmacist* pharmacist);
	int DeletePharmacist(Pharmacist* pharmacist);
	int UpdatePharmacistAddress(Pharmacist* pharmacist);
	int UpdatePharmacistHpNo(Pharmacist* pharmacist);
	int UpdatePharmacistEmail(Pharmacist* pharmacist);
	Pharmacist* getPharmacistByID(std::string Pharmacist_ID);
	Pharmacist* getPharmacistByName(std::string Ph_Name);
	Pharmacist* getPharmacistByIC(std::string Ph_IdentityCard);
	Pharmacist* getPharmacistByHpNo(std::string Ph_HpNo);
	Pharmacist* getPharmacistIDtoInsert();   // get the first ID from database by using desecnding method


	//Prescripstion
	int AddPrescription(Prescription* prescription);
	int DeletePrescription(Prescription* prescription);
	int UpdatePrescriptionPharmacistID(Prescription* prescription);
	int UpdatePrescriptionCustomerID(Prescription* prescription);
	int UpdatePrescriptionDate(Prescription* prescription);
	int UpdatePrescriptionDosage(Prescription* prescription);
	int UpdatePrescriptionMedicineID(Prescription* prescription);
	Prescription* getPrescriptionByID(std::string Prescription_ID);
	Prescription* getPrescriptionByCustomer_ID(std::string Customer_ID);
	Prescription* getPrescriptionByPharmacsit_ID(std::string Pharmacist_ID);
	Prescription* getPrescriptionByMedicine_ID(std::string Medicine_ID);
	Prescription* getPrescriptionByYear(std::string Pr_Date);
	Prescription* getPrescriptionByMonth(std::string Pr_Date);
	Prescription* getPrescriptionByDay(std::string Pr_Date);
	Prescription* getPrescriptionByHour(std::string Pr_Date);
	Prescription* getPrescriptionIDtoInsert();                 // get the first ID from database by using desecnding method


	//Bill
	int AddBill(Bill* bill);
	int AddBillWithoutPrescription(Bill* bill);
	int DeleteBill(Bill* bill);
	int UpdateBillMedicineID(Bill* bill);
	int updateBill(Bill* bill);                            //total price and medicine id
	int UpdateBillPaymentType(Bill* bill);
	int UpdateBillCustomerID(Bill* bill);
	int UpdateBillPrice(Bill* bill);
	int UpdateBillMedicine(Bill* bill);
	Bill* getBillByID(std::string Bill_ID);
	Bill* getBillByPrescriptionID(std::string Prescription_ID);
	Bill* getBillByCustomerID(std::string Customer_ID);
	Bill* getBillByPaymentType(std::string PaymentType);
	Bill* getBillByDate(std::string DateOfBill);
	Bill* getBillIDtoInsert();
	Bill* getBillByYear(std::string DateOfBill);
	Bill* getBillByMonth(std::string DateOfBill);
	Bill* getBillByDay(std::string DateOfBill);
	Bill* getBillByHour(std::string DateOfBill);
	Bill* getBillID();



	//Sales
	int AddSales(Sales* sales);
	int DeleteSales(Sales* sales);
	int UpdateSalesBillID(Sales* sales);
	int UpdateSalesMedicineID(Sales* sales);
	int UpdateQuantity(Sales* sales);
	Sales* getMedicineIDWithoutrepeat();
	Sales* getSalesToInsert();
	Sales* getSalesBySales_ID(std::string Sales_ID);
	Sales* getSalesByMedicine_ID(std::string Medicine_ID);
	Sales* getSalesByBill_ID(std::string Bill_ID);
	Sales* getSalesByQuantity(std::string Quantity);


	//login customer
	string LoginCustomer(std::string, std::string);

	//login Staff
	string LoginStaff(std::string, std::string);

	//login Manager
	string LoginManager(std::string, string);


	// return the ID to select when insert the medicine or something
	Staff* getStaffID();
	Supplier* getSupplierID();
	Pharmacist* getPharmacistID();
	Customer* getCustomerID();
	Medicine* getMedicineID();
	Prescription* getPrescriptionID();



	Medicine* getMedicineTypeWithoutrepeat();
	Medicine* getMedicineBrandWithoutrepeat();
	Medicine* getMedicineNotSoldYet();


	//get the most sales prodcut
	Bill* getmostSalesProduct();
	Bill* getAllSales();
	Bill* getAllSales2();
	Bill* allquantity();
	
	Bill* reportyear(std::string year, std::string month);
	Bill* reportyear2(std::string year, std::string month);
	Bill* report(std::string year);
	Bill* report2(std::string year);

	
	
};



#endif

