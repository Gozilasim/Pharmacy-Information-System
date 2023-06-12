#include<mysql/jdbc.h>
#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include<string>

class DatabaseConnection 
{
	private:
		sql::Connection* connection;

	public:
		DatabaseConnection();
		~DatabaseConnection();
		sql::PreparedStatement* preparestatement(std::string query);


};










#endif

