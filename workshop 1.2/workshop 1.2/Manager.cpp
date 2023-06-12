#include"DatabaseConnection.h"
#include "Manager.h"


/************************                           **************************************************/
/************************          Manager          **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Manager* manager)
{
	manager->Manager_ID = rs->getString("Manager_ID");
	manager->Password = rs->getString("Password");
	manager->M_Name = rs->getString("M_Name");
	manager->M_Address = rs->getString("M_Address");
	manager->M_HpNo = rs->getString("M_HpNo");
	manager->M_Email = rs->getString("M_Email");
	manager->M_Branch = rs->getString("M_Branch");
}

Manager* Manager::getManagerID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM MANAGER ");

	sql::ResultSet* rs = ps->executeQuery();

	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next()) {

		if (manager == NULL) {
			manager = new Manager();
			head = manager;
		}
		else {
			manager->next = new Manager();
			manager = manager->next;

		}


		transform(rs, manager);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Manager* Manager::getManagerID(std::string Manager_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MANAGER WHERE Manager_ID = ?");

	ps->setString(1, Manager_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Manager* manager = NULL;

	if (rs->next()) {
		manager = new Manager();

		transform(rs, manager);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return manager;

}

Manager* Manager::getManagerByName(std::string M_Name)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MANAGER WHERE M_Name = ?");

	ps->setString(1, M_Name);

	sql::ResultSet* rs = ps->executeQuery();

	Manager* manager = NULL;

	if (rs->next()) {
		manager = new Manager();

		transform(rs, manager);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return manager;
}

/************************                           **************************************************/
/************************          Login            **************************************************/
/************************                           **************************************************/


string Manager::LoginCustomer(string ID, string pwd)     //login 
{
	
	
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM CUSTOMER WHERE Customer_ID = ? AND Password = ? ");

	ps->setString(1, ID);
	ps->setString(2, pwd);


	string name = "\0" ;
	sql::ResultSet* rs = ps->executeQuery();

	if (rs->next()) {	   // if can proceed the id and password
	
		name = rs->getString("C_Name");           // set name = customer name
	}
	else
	{
		 name = "\0";
	}


	rs->close();
	ps->close();

	return name;

}

string Manager::LoginStaff(string ID, string pwd)     //login 
{


	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE Staff_ID = ? AND Password = ? ");

	ps->setString(1, ID);
	ps->setString(2, pwd);


	string name = "\0";
	sql::ResultSet* rs = ps->executeQuery();

	if (rs->next()) {	   // if can proceed the id and password

		name = rs->getString("S_Name");           // set name = customer name
	}
	else
	{
		name = "\0";
	}


	rs->close();
	ps->close();

	return name;

}

string Manager::LoginManager(string ID, string pwd)     //login 
{


	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MANAGER WHERE Manager_ID = ? AND Password = ? ");

	ps->setString(1, ID);
	ps->setString(2, pwd);


	string name = "\0";
	sql::ResultSet* rs = ps->executeQuery();

	if (rs->next()) {	   // if can proceed the id and password

		name = rs->getString("M_Name");           // set name = customer name
	}
	else
	{
		name = "\0";
	}


	rs->close();
	ps->close();

	return name;

}




/************************                           **************************************************/
/************************          Medicine         **************************************************/
/************************                           **************************************************/


void transform(sql::ResultSet* rs, Medicine* medicine)
{
	medicine->Medicine_ID = rs->getString("Medicine_ID");
	medicine->Supplier_ID = rs->getString("Supplier_ID");
	medicine->Staff_ID = rs->getString("Staff_ID");
	medicine->Manager_ID = rs->getString("Manager_ID");
	medicine->MedicineBrand = rs->getString("MedicineBrand");
	medicine->MedicineType = rs->getString("MedicineType");
	medicine->Price = rs->getDouble("Price");
	medicine->Quantity = rs->getInt("Quantity");
	medicine->Restock = rs->getInt("Restock");
}



// insert function of medicicne by Manager
int Manager::AddMedicine(Medicine* medicine)
{

	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO MEDICINE ( Medicine_ID, Supplier_ID, Manager_ID,  Staff_ID, MedicineType, MedicineBrand, Price, Quantity) VALUES (?, ?, ?, NULL , ?, ?, ?, ?)");

	ps->setString(1, medicine->Medicine_ID);
	ps->setString(2, medicine->Supplier_ID);
	ps->setString(3, medicine->Manager_ID);

	ps->setString(4, medicine->MedicineType);
	ps->setString(5, medicine->MedicineBrand);
	ps->setDouble(6, medicine->Price);
	ps->setInt(7, medicine->Quantity);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::AddMedicineWithoutManagerID(Medicine* medicine)
{

	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO MEDICINE ( Medicine_ID, Supplier_ID, Manager_ID,  Staff_ID, MedicineType, MedicineBrand, Price, Quantity) VALUES (?, ?, NULL, ? , ?, ?, ?, ?)");

	ps->setString(1, medicine->Medicine_ID);
	ps->setString(2, medicine->Supplier_ID);
	ps->setString(3, medicine->Staff_ID);
	ps->setString(4, medicine->MedicineType);
	ps->setString(5, medicine->MedicineBrand);
	ps->setDouble(6, medicine->Price);
	ps->setInt(7, medicine->Quantity);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::UpdateMedicineSupplierID(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET Supplier_ID = ? WHERE Medicine_ID = ? ");

	ps->setString(1, medicine->Supplier_ID);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicineManagerID(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET Manager_ID = ?, Staff_ID = NULL WHERE Medicine_ID = ? ");

	ps->setString(1, medicine->Manager_ID);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicineStaffID(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET Manager_ID = NULL, Staff_ID = ? WHERE Medicine_ID = ? ");

	ps->setString(1, medicine->Staff_ID);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicineMedicineType(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET MedicineType = ? WHERE Medicine_ID = ? ");

	ps->setString(1, medicine->MedicineType);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicineMedicineBrand(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET MedicineBrand = ? WHERE Medicine_ID = ? ");

	ps->setString(1, medicine->MedicineBrand);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicinePrice(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET Price = ? WHERE Medicine_ID = ? ");

	ps->setDouble(1, medicine->Price);
	ps->setString(2, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateMedicineQuantity(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Medicine SET Quantity = ?, Restock = ?  WHERE Medicine_ID = ? ");

	ps->setInt(1, medicine->Quantity);
	ps->setInt(2, medicine->Restock);
	ps->setString(3, medicine->Medicine_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::DeleteMedicine(Medicine* medicine)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM Medicine WHERE Medicine_ID = ?");

	ps->setString(1, medicine->Medicine_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

Medicine* Manager::getMedicine(std::string Medicine_ID)
{
	
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE Medicine_ID = ?");

	ps->setString(1, Medicine_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;

	if (rs->next()) {
		medicine = new Medicine();

		transform(rs, medicine);
	}
	
	

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return medicine;
	
}

Medicine* Manager::getMedicineBySupplierID(std::string Supplier_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE Supplier_ID = ?");

	ps->setString(1, Supplier_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}
		

		transform(rs, medicine);
	}
	


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Medicine* Manager::getMedicineByManagerID(std::string Manager_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE Manager_ID = ?");

	ps->setString(1, Manager_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Medicine* Manager::getMedicineByStaffID(std::string Staff_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE Staff_ID = ? or Manager_ID = ?");

	ps->setString(1, Staff_ID);
	ps->setString(2, Staff_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}

Medicine* Manager::getMedicineByMedicineType(std::string MedicineType)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE MedicineType = ?");

	ps->setString(1, MedicineType);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Medicine* Manager::getMedicineByMedicineBrand(std::string MedicineBrand)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE MedicineBrand = ?");

	ps->setString(1, MedicineBrand);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Medicine* Manager::getMedicine(double Price1, double Price2)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM MEDICINE WHERE Price >= ? AND Price <= ?");

	ps->setDouble(1, Price1);
	ps->setDouble(2, Price2);

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Medicine* Manager::getMedicineIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM MEDICINE ORDER BY Medicine_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;


	if (rs->next()) {
		medicine = new Medicine();

		transform(rs, medicine);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return medicine;
}

Medicine* Manager::getMedicineID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM MEDICINE ");

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Medicine* Manager::getMedicineTypeWithoutrepeat()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM MEDICINE GROUP BY MedicineType ");

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}

Medicine* Manager::getMedicineBrandWithoutrepeat()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM MEDICINE GROUP BY MedicineBrand ");

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}


		transform(rs, medicine);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}

Medicine* Manager::getMedicineNotSoldYet()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("SELECT * FROM MEDICINE where Medicine_ID NOT IN (SELECT Medicine_ID FROM bill GROUP BY Medicine_ID ORDER BY Medicine_ID)");

	sql::ResultSet* rs = ps->executeQuery();

	Medicine* medicine = NULL;
	Medicine* head = NULL;

	while (rs->next()) {

		if (medicine == NULL) {
			medicine = new Medicine();
			head = medicine;
		}
		else {
			medicine->next = new Medicine();
			medicine = medicine->next;

		}

		transform(rs, medicine);
		
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}



/************************                           **************************************************/
/************************          Supplier         **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Supplier* supplier)
{
	supplier->Supplier_ID = rs->getString("Supplier_ID");
	supplier->Sp_Name = rs->getString("Sp_Name");
	supplier->Sp_Address = rs->getString("Sp_Address");
	supplier->Sp_HpNo = rs->getString("Sp_HpNo");
	supplier->Sp_Email = rs->getString("Sp_Email");

}




int Manager::AddSupplier(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO SUPPLIER ( Supplier_ID, Sp_Name, Sp_Address, Sp_HpNo, Sp_Email) VALUES ( ?, ?, ?, ?, ?)");

	ps->setString(1, supplier->Supplier_ID);
	ps->setString(2, supplier->Sp_Name);
	ps->setString(3, supplier->Sp_Address);
	ps->setString(4, supplier->Sp_HpNo);
	ps->setString(5, supplier->Sp_Email);
	

	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeleteSupplier(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM SUPPLIER WHERE Supplier_ID = ?");

	ps->setString(1, supplier->Supplier_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateSupplierName(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE SUPPLIER SET Sp_Name = ? WHERE Supplier_ID = ? ");



	ps->setString(1, supplier->Sp_Name);
	ps->setString(2, supplier->Supplier_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdateSupplierAddress(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE SUPPLIER SET Sp_Address = ? WHERE Supplier_ID = ? ");



	ps->setString(1, supplier->Sp_Address);
	ps->setString(2, supplier->Supplier_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateSupplierHpNo(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE SUPPLIER SET Sp_HpNo = ? WHERE Supplier_ID = ? ");



	ps->setString(1, supplier->Sp_HpNo);
	ps->setString(2, supplier->Supplier_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateSupplierEmail(Supplier* supplier)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE SUPPLIER SET Sp_Email = ? WHERE Supplier_ID = ? ");


	ps->setString(1, supplier->Sp_Email);
	ps->setString(2, supplier->Supplier_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

Supplier* Manager::getSupplier(std::string Supplier_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM SUPPLIER WHERE Supplier_ID = ?");

	ps->setString(1, Supplier_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Supplier* supplier = NULL;

	if (rs->next()) {
		supplier = new Supplier();

		transform(rs, supplier);
	}
	

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return supplier;
}

Supplier* Manager::getSupplierByName(std::string Sp_Name)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM SUPPLIER WHERE Sp_Name = ?");

	ps->setString(1, Sp_Name);

	sql::ResultSet* rs = ps->executeQuery();

	Supplier* supplier = NULL;


	if (rs->next()) {
		supplier = new Supplier();

		transform(rs, supplier);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return supplier;
}

Supplier* Manager::getSupplierByHpNo(std::string Sp_HpNo)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM SUPPLIER WHERE Sp_HpNo = ?");

	ps->setString(1, Sp_HpNo);

	sql::ResultSet* rs = ps->executeQuery();

	Supplier* supplier = NULL;


	if (rs->next()) {
		supplier = new Supplier();

		transform(rs, supplier);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return supplier;
}

Supplier* Manager::getSupplierByIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM SUPPLIER ORDER BY SUPPLIER_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Supplier* supplier = NULL;


	if (rs->next()) {
		supplier = new Supplier();

		transform(rs, supplier);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return supplier;
}


Supplier* Manager::getSupplierID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM SUPPLIER ");

	sql::ResultSet* rs = ps->executeQuery();

	Supplier* supplier = NULL;
	Supplier* head = NULL;

	while (rs->next()) {

		if (supplier == NULL) {
			supplier = new Supplier();
			head = supplier;
		}
		else {
			supplier->next = new Supplier();
			supplier = supplier->next;

		}


		transform(rs, supplier);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}






/************************                           **************************************************/
/************************          Staff            **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Staff* staff)
{
	staff->Staff_ID = rs->getString("Staff_ID");
	staff->Password = rs->getString("Password");
	staff->S_Name = rs->getString("S_Name");
	staff->S_Address = rs->getString("S_Address");
	staff->S_HpNo = rs->getString("S_HpNo");
	staff->S_Email = rs->getString("S_Email");
	staff->S_Branch = rs->getString("S_Branch");
	staff->Manager_ID = rs->getString("Manager_ID");

}

int Manager::AddStaff(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO STAFF ( Staff_ID, Password, S_Name, S_Address, S_HpNo, S_Email, S_Branch, Manager_ID) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, staff->Staff_ID);
	ps->setString(2, staff->Password);
	ps->setString(3, staff->S_Name);
	ps->setString(4, staff->S_Address);
	ps->setString(5, staff->S_HpNo);
	ps->setString(6, staff->S_Email);
	ps->setString(7, staff->S_Branch);
	ps->setString(8, staff->Manager_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeleteStaff(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM STAFF WHERE Staff_ID = ?");

	ps->setString(1, staff->Staff_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateStaffPassword(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE STAFF SET Password = ? WHERE Staff_ID = ? ");



	
	ps->setString(1, staff->Password);
	ps->setString(2, staff->Staff_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateStaffAddress(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE STAFF SET S_Address = ? WHERE Staff_ID = ? ");




	ps->setString(1, staff->S_Address);
	ps->setString(2, staff->Staff_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateStaffHpNo(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE STAFF SET S_HpNo = ? WHERE Staff_ID = ? ");




	ps->setString(1, staff->S_HpNo);
	ps->setString(2, staff->Staff_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateStaffEmail(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE STAFF SET S_Email = ? WHERE Staff_ID = ? ");




	ps->setString(1, staff->S_Email);
	ps->setString(2, staff->Staff_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateStaffBranchnManagerID(Staff* staff)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE STAFF SET S_Branch = ?, Manager_ID = ? WHERE Staff_ID = ? ");




	ps->setString(1, staff->S_Branch);
	ps->setString(2, staff->Manager_ID);
	ps->setString(3, staff->Staff_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}




Staff* Manager::getStaffByStaffID(std::string Staff_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE Staff_ID = ?");

	ps->setString(1, Staff_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;

	if (rs->next()) {
		staff = new Staff();

		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}

Staff* Manager::getStaffByName(std::string S_Name)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE S_Name = ?");

	ps->setString(1, S_Name);

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;
	


	if (rs->next()) {
		staff = new Staff();

		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}

Staff* Manager::getStaffByHpNo(std::string S_HpNo)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE S_HpNo = ?");

	ps->setString(1, S_HpNo);

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;


	if (rs->next()) {
		staff = new Staff();

		transform(rs, staff);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}



Staff* Manager::getStaffByBranch(std::string S_Branch)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE S_Branch = ?");

	ps->setString(1, S_Branch);

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next()) {

		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;

		}


		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* Manager::getStaffByManagerID(std::string Manager_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM STAFF WHERE Manager_ID = ?");

	ps->setString(1, Manager_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next()) {

		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;

		}


		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Staff* Manager::getStaffID() 
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM STAFF ");

	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next()) {

		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;

		}


		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}

Staff* Manager::getStaffIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM STAFF ORDER BY Staff_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Staff* staff = NULL;


	if (rs->next()) {
		staff = new Staff();

		transform(rs, staff);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}






/************************                           **************************************************/
/************************          Customer         **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Customer* customer)
{
	customer->Customer_ID = rs->getString("Customer_ID");
	customer->Password = rs->getString("Password");
	customer->C_Name = rs->getString("C_Name");
	customer->C_IdentityCard = rs->getString("C_IdentityCard");
	customer->C_Address = rs->getString("C_Address");
	customer->C_HpNo = rs->getString("C_HpNo");
	customer->C_Email = rs->getString("C_Email");

}

int Manager::AddCustomer(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO CUSTOMER ( Customer_ID, Password,  C_Name, C_IdentityCard,  C_Address, C_HpNo, C_Email) VALUES ( ?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, customer->Customer_ID);
	ps->setString(2, customer->Password);
	ps->setString(3, customer->C_Name);
	ps->setString(4, customer->C_IdentityCard);
	ps->setString(5, customer->C_Address);
	ps->setString(6, customer->C_HpNo);
	ps->setString(7, customer->C_Email);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}


int Manager::DeleteCustomer(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM CUSTOMER WHERE Customer_ID = ?");

	ps->setString(1, customer->Customer_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdateCustomerAddress(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE CUSTOMER SET C_Address = ?  WHERE Customer_ID = ? ");



	ps->setString(1, customer->C_Address);
	ps->setString(2, customer->Customer_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdateCustomerHpNo(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE CUSTOMER SET C_HpNo = ?  WHERE Customer_ID = ? ");


	ps->setString(1, customer->C_HpNo);
	ps->setString(2, customer->Customer_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateCustomerEmail(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE CUSTOMER SET C_Email = ?  WHERE Customer_ID = ? ");


	ps->setString(1, customer->C_Email);
	ps->setString(2, customer->Customer_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateCustomerPassword(Customer* customer)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE CUSTOMER SET Password = ?  WHERE Customer_ID = ? ");


	ps->setString(1, customer->Password);
	ps->setString(2, customer->Customer_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}






Customer* Manager::getCustomerByID(std::string Customer_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM CUSTOMER WHERE Customer_ID = ?");

	ps->setString(1, Customer_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Customer* customer = NULL;

	if (rs->next()) {
		customer = new Customer();

		transform(rs, customer);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}

Customer* Manager::getCustomerByName(std::string C_Name)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM CUSTOMER WHERE C_Name = ?");

	ps->setString(1, C_Name);

	sql::ResultSet* rs = ps->executeQuery();

	Customer* customer = NULL;

	if (rs->next()) {
		customer = new Customer();

		transform(rs, customer);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}

Customer* Manager::getCustomerByIC(std::string C_IdentityCard)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM CUSTOMER WHERE C_IdentityCard = ?");

	ps->setString(1, C_IdentityCard);

	sql::ResultSet* rs = ps->executeQuery();

	Customer* customer = NULL;

	if (rs->next()) {
		customer = new Customer();

		transform(rs, customer);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}

Customer* Manager::getCustomerByHpNo(std::string C_HpNo)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM CUSTOMER WHERE C_HpNo = ?");

	ps->setString(1, C_HpNo);

	sql::ResultSet* rs = ps->executeQuery();

	Customer* customer = NULL;

	if (rs->next()) {
		customer = new Customer();

		transform(rs, customer);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}


Customer* Manager::getCustomerID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM CUSTOMER ");

	sql::ResultSet* rs = ps->executeQuery();

	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next()) {

		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;

		}


		transform(rs, customer);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


/************************                           **************************************************/
/************************          Pharmacist       **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Pharmacist* pharmacist)
{
	pharmacist->Pharmacist_ID = rs->getString("Pharmacist_ID");
	pharmacist->Ph_Name = rs->getString("Ph_Name");
	pharmacist->Ph_IdentityCard = rs->getString("Ph_IdentityCard");
	pharmacist->Ph_Address = rs->getString("Ph_Address");
	pharmacist->Ph_HpNo = rs->getString("Ph_HpNo");
	pharmacist->Ph_Email = rs->getString("Ph_Email");

}

int Manager::AddPharmacist(Pharmacist* pharmacist)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO PHARMACIST ( Pharmacist_ID,  Ph_Name, Ph_IdentityCard,  Ph_Address, Ph_HpNo, Ph_Email) VALUES ( ?, ?, ?, ?, ?, ?)");

	ps->setString(1, pharmacist->Pharmacist_ID);
	ps->setString(2, pharmacist->Ph_Name);
	ps->setString(3, pharmacist->Ph_IdentityCard);
	ps->setString(4, pharmacist->Ph_Address);
	ps->setString(5, pharmacist->Ph_HpNo);
	ps->setString(6, pharmacist->Ph_Email);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeletePharmacist(Pharmacist* pharmacist)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM PHARMACIST WHERE Pharmacist_ID = ?");

	ps->setString(1, pharmacist->Pharmacist_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdatePharmacistAddress(Pharmacist* pharmacist)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PHARMACIST SET  Ph_Address = ?  WHERE Pharmacist_ID = ? ");



	ps->setString(1, pharmacist->Ph_Address);
	ps->setString(2, pharmacist->Pharmacist_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdatePharmacistHpNo(Pharmacist* pharmacist)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PHARMACIST SET  Ph_HpNo = ?  WHERE Pharmacist_ID = ? ");



	ps->setString(1, pharmacist->Ph_HpNo);
	ps->setString(2, pharmacist->Pharmacist_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdatePharmacistEmail(Pharmacist* pharmacist)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PHARMACIST SET  Ph_Email = ?  WHERE Pharmacist_ID = ? ");



	ps->setString(1, pharmacist->Ph_Email);
	ps->setString(2, pharmacist->Pharmacist_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


Pharmacist* Manager::getPharmacistByID(std::string Pharmacist_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PHARMACIST WHERE Pharmacist_ID = ?");

	ps->setString(1, Pharmacist_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;

	if (rs->next()) {
		pharmacist = new Pharmacist();

		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return pharmacist;
}


Pharmacist* Manager::getPharmacistByIC(std::string Ph_IdentityCard)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PHARMACIST WHERE Ph_IdentityCard = ?");

	ps->setString(1, Ph_IdentityCard);

	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;

	if (rs->next()) {
		pharmacist = new Pharmacist();

		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return pharmacist;
}


Pharmacist* Manager::getPharmacistByName(std::string Ph_Name)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PHARMACIST WHERE Ph_Name = ?");

	ps->setString(1, Ph_Name);

	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;

	if (rs->next()) {
		pharmacist = new Pharmacist();

		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return pharmacist;
}


Pharmacist* Manager::getPharmacistByHpNo(std::string Ph_HpNo)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PHARMACIST WHERE Ph_HpNo = ?");

	ps->setString(1, Ph_HpNo);

	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;

	if (rs->next()) {
		pharmacist = new Pharmacist();

		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return pharmacist;
}

Pharmacist* Manager::getPharmacistIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM PHARMACIST ORDER BY Pharmacist_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;


	if (rs->next()) {
		pharmacist = new Pharmacist();

		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return pharmacist;

}

Pharmacist* Manager::getPharmacistID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM Pharmacist ");

	sql::ResultSet* rs = ps->executeQuery();

	Pharmacist* pharmacist = NULL;
	Pharmacist* head = NULL;

	while (rs->next()) {

		if (pharmacist == NULL) {
			pharmacist = new Pharmacist();
			head = pharmacist;
		}
		else {
			pharmacist->next = new Pharmacist();
			pharmacist = pharmacist->next;

		}


		transform(rs, pharmacist);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


/************************                           **************************************************/
/************************          prescription     **************************************************/
/************************                           **************************************************/



void transform(sql::ResultSet* rs, Prescription* prescription)
{
	prescription->Prescription_ID = rs->getString("Prescription_ID");
	prescription->Customer_ID = rs->getString("Customer_ID");
	prescription->Pharmacist_ID = rs->getString("Pharmacist_ID");
	prescription->Medicine_ID = rs->getString("Medicine_ID");
	prescription->Pr_Date = rs->getString("Pr_Date");
	prescription->Pr_Dosage = rs->getString("Pr_Dosage");
	
}

int Manager::AddPrescription(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO PRESCRIPTION ( Prescription_ID,  Customer_ID , Pharmacist_ID, Medicine_ID , Pr_Date, Pr_Dosage) VALUES ( ?, ?, ?, ?, ?, ?)");

	ps->setString(1, prescription->Prescription_ID);
	ps->setString(2, prescription->Customer_ID);
	ps->setString(4, prescription->Medicine_ID);
	ps->setString(3, prescription->Pharmacist_ID);
	ps->setString(5, prescription->Pr_Date);
	ps->setString(6, prescription->Pr_Dosage);
	

	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeletePrescription(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM PRESCRIPTION WHERE Prescription_ID = ?");

	ps->setString(1, prescription->Prescription_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdatePrescriptionPharmacistID(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PRESCRIPTION SET  Pharmacist_ID = ? WHERE Prescription_ID = ? ");

	

	ps->setString(1, prescription->Pharmacist_ID);
	ps->setString(2, prescription->Prescription_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdatePrescriptionCustomerID(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PRESCRIPTION SET  Customer_ID = ? WHERE Prescription_ID = ? ");



	ps->setString(1, prescription->Customer_ID);
	ps->setString(2, prescription->Prescription_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdatePrescriptionDate(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PRESCRIPTION SET  Pr_Date = ? WHERE Prescription_ID = ? ");



	ps->setString(1, prescription->Pr_Date);
	ps->setString(2, prescription->Prescription_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdatePrescriptionMedicineID(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PRESCRIPTION SET  Medicine_ID = ? WHERE Prescription_ID = ? ");



	ps->setString(1, prescription->Medicine_ID);
	ps->setString(2, prescription->Prescription_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdatePrescriptionDosage(Prescription* prescription)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE PRESCRIPTION SET  Pr_Dosage = ? WHERE Prescription_ID = ? ");



	ps->setString(1, prescription->Pr_Dosage);
	ps->setString(2, prescription->Prescription_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


Prescription* Manager::getPrescriptionByID(std::string Prescription_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE Prescription_ID = ?");

	ps->setString(1, Prescription_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Prescription* Manager::getPrescriptionByCustomer_ID(std::string Customer_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE Customer_ID = ?");

	ps->setString(1, Customer_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Prescription* Manager::getPrescriptionByPharmacsit_ID(std::string Pharmacist_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE Pharmacist_ID = ?");

	ps->setString(1, Pharmacist_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Prescription* Manager::getPrescriptionByMedicine_ID(std::string Medicine_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE Medicine_ID = ?");

	ps->setString(1, Medicine_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Prescription* Manager::getPrescriptionByYear(std::string Pr_Date)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE extract(year from Pr_Date) = ? ");

	ps->setString(1, Pr_Date);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Prescription* Manager::getPrescriptionByMonth(std::string Pr_Date)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE extract(MONTH from Pr_Date) = ? ");

	ps->setString(1, Pr_Date);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Prescription* Manager::getPrescriptionByDay(std::string Pr_Date)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE extract(day from Pr_Date) = ? ");

	ps->setString(1, Pr_Date);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Prescription* Manager::getPrescriptionByHour(std::string Pr_Date)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION WHERE extract(hour from Pr_Date) = ? ");

	ps->setString(1, Pr_Date);

	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Prescription* Manager::getPrescriptionIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM Prescription ORDER BY Prescription_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;


	if (rs->next()) {
		prescription = new Prescription();

		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return prescription;
}

Prescription* Manager::getPrescriptionID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM PRESCRIPTION ");


	sql::ResultSet* rs = ps->executeQuery();

	Prescription* prescription = NULL;
	Prescription* head = NULL;

	while (rs->next()) {

		if (prescription == NULL) {
			prescription = new Prescription();
			head = prescription;
		}
		else {
			prescription->next = new Prescription();
			prescription = prescription->next;

		}


		transform(rs, prescription);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}




/************************                           **************************************************/
/************************          Bill             **************************************************/
/************************                           **************************************************/


void transform(sql::ResultSet* rs, Bill* bill)
{
	bill->Bill_ID = rs->getString("Bill_ID");
	bill->Prescription_ID = rs->getString("Prescription_ID");
	bill->Medicine_ID = rs->getString("Medicine_ID");
	bill->Customer_ID = rs->getString("Customer_ID");
	bill->Quantity = rs->getInt("Quantity");
	bill->TotalPrice = rs->getDouble("TotalPrice");
	bill->PaymentType = rs->getString("PaymentType");
	bill->DateOfBill = rs->getString("DateOfBill");

}

int Manager::AddBill(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO BILL ( Bill_ID, Prescription_ID, Medicine_ID ,Customer_ID ,Quantity, TotalPrice, PaymentType,  DateOfBill) VALUES ( ? ,?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, bill->Bill_ID);
	ps->setString(2, bill->Prescription_ID);
	ps->setString(3, bill->Medicine_ID);
	ps->setString(4 , bill->Customer_ID);
	ps->setInt(5, bill->Quantity);
	ps->setDouble(6, bill->TotalPrice);
	ps->setString(7, bill->PaymentType);
	ps->setString(8, bill->DateOfBill);
	


	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::AddBillWithoutPrescription(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO BILL ( Bill_ID, Prescription_ID, Medicine_ID ,Customer_ID ,Quantity, TotalPrice, PaymentType,  DateOfBill) VALUES ( ? ,NULL, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, bill->Bill_ID);
	ps->setString(2, bill->Medicine_ID);
	ps->setString(3, bill->Customer_ID);
	ps->setInt(4, bill->Quantity);
	ps->setDouble(5, bill->TotalPrice);
	ps->setString(6, bill->PaymentType);
	ps->setString(7, bill->DateOfBill);



	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeleteBill(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM BILL WHERE Bill_ID = ?");

	ps->setString(1, bill->Bill_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::updateBill(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET   Medicine_ID = ? , TotalPrice = ?  WHERE Bill_ID = ? ");


	ps->setString(1, bill->Medicine_ID);
	ps->setDouble(2, bill->TotalPrice);
	ps->setString(3, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}



int Manager::UpdateBillPaymentType(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET   PaymentType = ?  WHERE Bill_ID = ? ");


	ps->setString(1, bill->PaymentType);
	ps->setString(2, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdateBillMedicine(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET   Medicine_ID = ?   WHERE Bill_ID = ? ");


	ps->setString(1, bill->Medicine_ID);
	ps->setString(2, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateBillCustomerID(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET   Customer_ID = ?   WHERE Bill_ID = ? ");


	ps->setString(1, bill->Customer_ID);
	ps->setString(2, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}


int Manager::UpdateBillPrice(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET  TotalPrice = ? WHERE Bill_ID = ? ");


	ps->setDouble(1, bill->TotalPrice);
	ps->setString(2, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateBillMedicineID(Bill* bill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE BILL SET  Medicine_ID = ? WHERE Bill_ID = ? ");


	ps->setString(1, bill->Medicine_ID);
	ps->setString(2, bill->Bill_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

Bill* Manager::getBillByID(std::string Bill_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL WHERE Bill_ID = ?");

	ps->setString(1, Bill_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;

	if (rs->next()) {
		bill = new Bill();

		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;
}

Bill* Manager::getBillByPrescriptionID(std::string Prescription_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL WHERE Prescription_ID = ?");

	ps->setString(1, Prescription_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;

	if (rs->next()) {
		bill = new Bill();

		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;
}

Bill* Manager::getBillByCustomerID(std::string Customer_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL WHERE Customer_ID = ?");

	ps->setString(1, Customer_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillByPaymentType(std::string PaymentType)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL WHERE PaymentType = ?");

	ps->setString(1, PaymentType);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillByDate(std::string DateOfBill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL WHERE DateOfBill = ?");

	ps->setString(1, DateOfBill);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillIDtoInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM BILL ORDER BY Bill_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;


	if (rs->next()) {
		bill = new Bill();

		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;
}

Bill* Manager::getBillByYear(std::string DateOfBill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Bill WHERE extract(year from DateOfBill) = ? ");

	ps->setString(1, DateOfBill);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillByMonth(std::string DateOfBill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Bill WHERE extract(MONTH from DateOfBill) = ? ");

	ps->setString(1, DateOfBill);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillByDay(std::string DateOfBill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Bill WHERE extract(day from DateOfBill) = ? ");

	ps->setString(1, DateOfBill);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Bill* Manager::getBillByHour(std::string DateOfBill)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Bill WHERE extract(hour from DateOfBill) = ? ");

	ps->setString(1, DateOfBill);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::getBillID()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM BILL ");


	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next()) {

		if (bill == NULL) {
			bill = new Bill();
			head = bill;
		}
		else {
			bill->next = new Bill();
			bill = bill->next;

		}


		transform(rs, bill);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}



/************************                           **************************************************/
/************************          Sales            **************************************************/
/************************                           **************************************************/


void transform(sql::ResultSet* rs, Sales* sales)
{
	sales->Sales_ID = rs->getString("Sales_ID");
	sales->Bill_ID = rs->getString("Bill_ID");
	sales->Medicine_ID = rs->getString("Medicine_ID");
	sales->Quantity = rs->getInt("Quantity");


}

int Manager::AddSales(Sales* sales)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("INSERT INTO Sales ( Sales_ID, Bill_ID, Medicine_ID ,Quantity ) VALUES ( ?, ?, ?, ?)");

	ps->setString(1, sales->Sales_ID);
	ps->setString(2, sales->Bill_ID);
	ps->setString(3, sales->Medicine_ID);
	ps->setInt(4, sales->Quantity);




	int numRowwsAffected = ps->executeUpdate();


	ps->close();

	return numRowwsAffected;
}

int Manager::DeleteSales(Sales* sales)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("DELETE FROM BILL WHERE Sales_ID = ?");

	ps->setString(1, sales->Sales_ID);


	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateSalesBillID(Sales* sales)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Sales SET   Bill_ID = ?   WHERE Sales_ID = ? ");


	ps->setString(1, sales->Bill_ID);
	ps->setString(2, sales->Sales_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateSalesMedicineID(Sales* sales)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Sales SET   Medicine_ID = ?   WHERE Sales_ID = ? ");


	ps->setString(1, sales->Medicine_ID);
	ps->setString(2, sales->Sales_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}

int Manager::UpdateQuantity(Sales* sales)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement("UPDATE Sales SET   Quantity = ?   WHERE Sales_ID = ? ");


	ps->setInt(1, sales->Quantity);
	ps->setString(2, sales->Sales_ID);

	int numRowwsAffected = ps->executeUpdate();


	ps->close();
	delete ps;

	return numRowwsAffected;
}





Sales* Manager::getMedicineIDWithoutrepeat()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM Sales GROUP BY Medicine_ID ");

	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;
	Sales* head = NULL;

	while (rs->next()) {

		if (sales == NULL) {
			sales = new Sales();
			head = sales;
		}
		else {
			sales->next = new Sales();
			sales = sales->next;

		}


		transform(rs, sales);
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Sales* Manager::getSalesToInsert()
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT * FROM Sales ORDER BY Sales_ID DESC LIMIT 1");


	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;


	if (rs->next()) {
		sales = new Sales();

		transform(rs, sales);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return sales;
}

Sales* Manager::getSalesBySales_ID(std::string Sales_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Sales WHERE Sales_ID = ?");

	ps->setString(1, Sales_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;

	if (rs->next()) {
		sales = new Sales();

		transform(rs, sales);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return sales;
}

Sales* Manager::getSalesByMedicine_ID(std::string Medicine_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Sales WHERE Medicine_ID = ?");

	ps->setString(1, Medicine_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;
	Sales* head = NULL;

	while (rs->next()) {
		
		if (sales == NULL) {
			sales = new Sales();
			head = sales;
		}
		else {
			sales->next = new Sales();
			sales = sales->next;

		}


		transform(rs, sales);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Sales* Manager::getSalesByBill_ID(std::string Bill_ID)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Sales WHERE Bill_ID = ?");

	ps->setString(1, Bill_ID);

	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;

	if (rs->next()) {
		sales = new Sales();

		transform(rs, sales);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return sales;
}

Sales* Manager::getSalesByQuantity(std::string Quantity)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT* FROM Sales WHERE Quantity = ?");

	ps->setString(1, Quantity);

	sql::ResultSet* rs = ps->executeQuery();

	Sales* sales = NULL;
	Sales* head = NULL;

	while (rs->next()) {

		if (sales == NULL) {
			sales = new Sales();
			head = sales;
		}
		else {
			sales->next = new Sales();
			sales = sales->next;

		}


		transform(rs, sales);
	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


Bill* Manager::getAllSales()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.preparestatement("SELECT Medicine_ID, SUM(Quantity) as Quantity FROM bill GROUP BY Medicine_ID ORDER BY Quantity  ");
	sql::ResultSet* rs = ps->executeQuery();
	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next())
	{
		if (bill == NULL)
		{
			bill = new Bill();
			head = bill;
		}
		else
		{
			bill->next = new Bill();
			bill = bill->next;
		}

		bill->Medicine_ID = rs->getString("Medicine_ID");
		bill->Quantity = rs->getInt("Quantity");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}

Bill* Manager::getAllSales2()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.preparestatement("SELECT Medicine_ID, SUM(Quantity) as Quantity FROM bill GROUP BY Medicine_ID ORDER BY Medicine_ID  ");
	sql::ResultSet* rs = ps->executeQuery();
	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next())
	{
		if (bill == NULL)
		{
			bill = new Bill();
			head = bill;
		}
		else
		{
			bill->next = new Bill();
			bill = bill->next;
		}

		bill->Medicine_ID = rs->getString("Medicine_ID");
		bill->Quantity = rs->getInt("Quantity");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Bill* Manager::allquantity()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.preparestatement("SELECT SUM(Quantity) as Quantity FROM bill ");
	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	

	while (rs->next())
	{
		bill = new Bill();
		bill->count = rs->getInt("Quantity");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;

}

Bill* Manager::getmostSalesProduct()
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.preparestatement("SELECT Medicine_ID, SUM(Quantity) as Quantity FROM bill GROUP BY Medicine_ID ORDER BY Quantity DESC LIMIT 3");
	sql::ResultSet* rs = ps->executeQuery();
	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next())
	{
		if (bill == NULL)
		{
			bill = new Bill();
			head = bill;
		}
		else
		{
			bill->next = new Bill();
			bill = bill->next;
		}

		bill->Medicine_ID = rs->getString("Medicine_ID");
		bill->Quantity = rs->getInt("Quantity");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;

}


Bill* Manager::reportyear(std::string year, std::string month)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT SUM(TotalPrice) AS TotalPrice FROM bill  WHERE extract(year from DateOfBill) = ? AND extract(month from DateOfBill) = ? ");

	ps->setString(1, year);
	ps->setString(2, month);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;


	if (rs->next()) {
		
		bill = new Bill();
		bill->total = rs->getDouble("TotalPrice");

	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;
}

Bill* Manager::reportyear2(std::string year, std::string month)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT Medicine_ID, COUNT(Medicine_ID) AS NUMBER_OF_PAYMENT, SUM(Quantity) AS TOTAL from bill WHERE extract(year from DateOfBill) = ? AND extract(month from DateOfBill) = ? group by Medicine_ID    ");

	ps->setString(1, year);
	ps->setString(2, month);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next())
	{
		if (bill == NULL)
		{
			bill = new Bill();
			head = bill;
		}
		else
		{
			bill->next = new Bill();
			bill = bill->next;
		}

		bill->Medicine_ID = rs->getString("Medicine_ID");
		bill->count = rs->getInt("NUMBER_OF_PAYMENT");
		bill->Quantity = rs->getInt("TOTAL");
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}




Bill* Manager::report2(std::string year)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT Medicine_ID, COUNT(Medicine_ID) AS NUMBER_OF_PAYMENT, SUM(Quantity) AS TOTAL from bill WHERE extract(year from DateOfBill) = ?  group by Medicine_ID   ");

	ps->setString(1, year);

	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;
	Bill* head = NULL;

	while (rs->next())
	{
		if (bill == NULL)
		{
			bill = new Bill();
			head = bill;
		}
		else
		{
			bill->next = new Bill();
			bill = bill->next;
		}

		bill->Medicine_ID = rs->getString("Medicine_ID");
		bill->count = rs->getInt("NUMBER_OF_PAYMENT");
		bill->Quantity = rs->getInt("TOTAL");
	}


	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Bill* Manager::report(std::string year)
{
	DatabaseConnection DbCon;

	sql::PreparedStatement* ps = DbCon.preparestatement(" SELECT SUM(TotalPrice) AS TotalPrice FROM bill  WHERE extract(year from DateOfBill) = ? ");

	ps->setString(1, year);


	sql::ResultSet* rs = ps->executeQuery();

	Bill* bill = NULL;


	if (rs->next()) {

		bill = new Bill();
		bill->total = rs->getDouble("TotalPrice");

	}



	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return bill;
}