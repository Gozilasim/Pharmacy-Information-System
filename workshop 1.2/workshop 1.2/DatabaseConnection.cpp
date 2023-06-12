#include"DatabaseConnection.h"
#include<iostream>

DatabaseConnection::DatabaseConnection()
{

	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	connection = driver->connect("tcp://127.0.0.1", "root", "");

	connection->setSchema("i_care pharmacy");
}

DatabaseConnection::~DatabaseConnection()
{
	connection->close();

	delete connection;

} 

sql::PreparedStatement* DatabaseConnection::preparestatement(std::string query)
{
	return connection->prepareStatement(query);
}