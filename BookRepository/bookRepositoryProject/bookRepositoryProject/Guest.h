#ifndef Guest_h
#define Guest_h
#include <iostream>
#include"Book.h"
#include <vector>

class Guest {
public:
	//constructor
	Guest();
	Guest(std::string userTypeParam);
	Guest(std::string userLoginParam, std::string userPasswordParam, std::string userTypeParam );
	//sets
	void setUserType(std::string userTypeParam);
	void setUserLogin(std::string userLoginParam);
	void setUserPassword(std::string userPasswordParam);
	void setNextUser(Guest* nextUser);
	void setPreviousUser(Guest* previousUser);
	//gets
	std::string getUserType()const;
	std::string getUserLogin()const;
	std::string getPassword()const;
	Guest* getNextUser()const;
	Guest* getPreviousUser()const;
	//methods
	void registeredUserSearch(Book* firstBook);
	bool checkPartial(std::string input, std::string title);
	void adminMenu(Guest* firstGuest, Book* firstBook);
	std::string toLower(std::string param);
	Book* searchRepository(Book* firstBook);
	void printBooks(std::vector<Book*>* bookVector);
	
private:
	std::vector<Book*> ownedBooks;
	std::string userType;
	std::string userLogin;
	std::string userPassword;
	Guest* next;
	Guest* previous;
};
#endif