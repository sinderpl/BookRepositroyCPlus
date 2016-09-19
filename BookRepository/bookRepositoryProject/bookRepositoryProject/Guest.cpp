#include<iostream>
//#include "Book.h"
#include "Guest.h"
#include <string>
#include<locale>
#include <vector>


//constructor
Guest::Guest() {};
Guest::Guest(std::string userTypeParam) {
	userType = userTypeParam;
};
Guest::Guest(std::string userLoginParam, std::string userPasswordParam, std::string userTypeParam) {
	userPassword = userPasswordParam;
	userLogin = userLoginParam;
	userType = userTypeParam;
	setNextUser(NULL);
};
//sets
void Guest::setUserType(std::string userTypeParam) {
	userType = userTypeParam;
};
void Guest::setUserLogin(std::string userLoginParam) {
	userLogin = userLoginParam;
};
void Guest::setUserPassword(std::string userPasswordParam) {
	userPassword = userPasswordParam;
};
void Guest::setNextUser(Guest* nextUser) {
	next = nextUser;
};
void Guest::setPreviousUser(Guest* previousUser) {
	previous = previousUser;
};
//gets
std::string Guest::getUserType()const {
	return userType;
};
std::string Guest::getUserLogin()const {
	return userLogin;
};
std::string Guest::getPassword()const {
	return userPassword;
};
Guest* Guest::getNextUser()const {
	return next;
};
Guest* Guest::getPreviousUser()const {
	return previous;
};


//methods

//Registered user search menu
void Guest::registeredUserSearch(Book* firstBook) {

	//variables
	int inputMenuChoice;
	Book* bookFound = NULL;
	//search repository for book
	bookFound = searchRepository(firstBook);
	bool bookInPossesion = false;
	int position = 0;
	//if book was found
	if (bookFound != NULL) {
		//if book is available let the user take it out
		if (bookFound->checkAvailability() == true) {
			std::cout << "This book is available" << std::endl;
			std::cout << "1.Take book out" << std::endl;
			std::cin >> inputMenuChoice;
			if (inputMenuChoice == 1) {
				//add the book to the users taken out books
				//set the owner of the book to the user
				std::cout << "Book taken out." << std::endl;
				ownedBooks.push_back(bookFound);
				bookFound->setAvailability(false);
				bookFound->setOwner(this);
				std::cin.ignore();
			}
		}
		else {
			//if books is not available
			std::cout << "This book is not available." << std::endl;
			if (bookFound->getOwner() != NULL) {
				// if user is book owner
				if ((bookFound->getOwner())->getUserLogin() == userLogin) {
					//allow the user to give the book back if he is the owner
					std::cout << "1.Return book." << std::endl;
					std::cin >> inputMenuChoice;
					if (inputMenuChoice == 1) {
						int position = 0;
						std::cout << "Book returned." << std::endl;
						//take the book off the users owned books list
						for (int x = 0; x < ownedBooks.size(); x++) {
							if (ownedBooks.at(x)->getTitle() == bookFound->getTitle()) {}
							ownedBooks.erase(ownedBooks.begin() + x);
						}
					}
					bookFound->setAvailability(true);
					bookFound->setOwner(NULL);
					std::cin.ignore();
				}
			}
			}
		}

	
};
//sets any string to a lowercase and returns it
std::string Guest::toLower(std::string param) {
	std::locale loc;
	std::string tempString;
	//iterates throught the string
	//sets each char to its lowercase equivalent
	for (std::string::size_type i = 0; i < param.length(); i++)
		tempString += std::tolower(param[i], loc);
	return tempString;
};
//partial search method for two strings
bool Guest::checkPartial(std::string input, std::string compare) {
	//variables
	bool finished = false;
	bool result = false;
	//add each char of the two strings to a vector
	//in order to allow to iterate through them easily
	std::vector<char> inputVector(input.begin(), input.end());
	std::vector<char> compareVector(compare.begin(), compare.end());
	int closeness = 0;
	int indexParam = 0;
	//iterate until all chars checked
	while(!finished) {
		//iterate through the string to which the input is being compared to
		for (int x = 0; x<(compareVector.size()); x++) {
			//if the char at the compare vector equals to the one at the
			//input vector (closensess) 
			if (compareVector.at(x) == inputVector.at(closeness)) {
				//increase closeness variable
				closeness++;

				//in case the string doesnt match at some point
				//this allows for the iteration to be restarted from this point
				//so if ("terry pratchett" is the author name) and input is "tche"
				//the method iterates throught all the "t" chars untill match is found
				indexParam = x;

				//if closeness variable equals to the size of the input stirng
				if (closeness == inputVector.size()) {
					//break loop and return result
					result = true;
					finished = true;
					return result;
				}
			}
			//if the last iteration of a possible match failed
			//resets the iteration to the index param char
			else if (closeness > 0) {
				closeness = 0;
				x = indexParam++;
			}
		}
		finished = true;
	}
	return result;
};
//book search method, returns the book found object
Book* Guest::searchRepository(Book* firstBook) {
	Book* result = NULL;
	//if there are no books the method breaks now
	if (firstBook == NULL) {
		std::cout << "No books in repository." << std::endl;
		return result;
	}
	//variables
	Book* bookParam = firstBook;
	std::vector<Book*> bookVector;
	std::string input;
	std::string tempstring;
	std::locale loc;
	int inputMenuChoice = -5;

	//for cin and getline problems
	while (inputMenuChoice != 0) {
		if ( userType == "Admin")
			std::cin.ignore();

		input = "";
		tempstring = "";
		bookVector.clear();
		std::cout << "Please enter either the book title , author or ISBN number: " << std::endl;
		//asks for search criteria and stores it

		std::getline(std::cin, input);
		if (input == "0") {
			inputMenuChoice = 0;
			return result;
		}


		input = toLower(input);
		bool moreBooks = true;
		//checks if the repository has any objects left
		while (moreBooks) {
			//checks the title
			if (bookParam->getNext() == NULL)
				moreBooks = false;
			if (checkPartial(input, toLower(bookParam->getTitle()))) {
				bookVector.push_back(bookParam);
			}
			//checks the author
			else if (checkPartial(input, toLower(bookParam->getAuthor()))) {
				bookVector.push_back(bookParam);
			}
			//checks the isbn number
			else if (checkPartial(input, toLower(bookParam->getIsbnNo()))) {
				bookVector.push_back(bookParam);
			}
			//if the next book is the first one it stops the loop
			if (bookParam->getNext() == firstBook) {
				break;
			}
			//gets the next param if not null
			if (bookParam->getNext() != NULL) {
				bookParam = bookParam->getNext();
			}
			else {
				break;
			}
		}
		bookParam = firstBook;

		//prints the book vector
		printBooks(&bookVector);
		std::cout << "Please choose the number of the book or press 0 to return to the search menu" << std::endl;
		std::cin >> inputMenuChoice;
		int bookChoice = inputMenuChoice;
		if (inputMenuChoice == 0)
			return result;
		else
			result = bookVector.at(bookChoice - 1);
		return result;
	}
	return result;
};
//prints the vector of books
void Guest::printBooks(std::vector<Book*>* bookVector) {
	std::cout << "List of books that match your criteria: " << std::endl;
	//iterates through found book array
	//prints all the possible options
	if (bookVector->size() >= 1) {
		for (int x = 0; x <= bookVector->size()-1; x++) {
			std::cout << x + 1 << ".    Title: " << bookVector->at(x)->getTitle() << "    Author: " << bookVector->at(x)->getAuthor() << "   ISBN no: " << bookVector->at(x)->getIsbnNo() << std::endl;// iterate and print out the books in the vector
		}
	}
	else {
		std::cout << "There are no books that match your criteria." << std::endl;
	}
	std::cout << "--------------" << std::endl;
};