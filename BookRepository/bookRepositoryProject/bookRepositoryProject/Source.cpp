#include <iostream>
//#include "Book.h"
#include "Guest.h"
#include <string>

//Global variables
std::string userType;
Book artOfWar;
Book dodger;
Book raisingSteam;
Book aClashOfKings;
Book winterKnights;
Book wintersmith;


Guest guestUser;
Guest registeredUser;
Guest administrator;
Guest currentUser;

//First objects for linked lists
Guest* firstUser;
Book* firstBook;

//Add book menu
void addBook() {
	
	//variables
	std::string bookName = "";
	std::string bookAuthor = "";
	std::string ISBNno = "";
	bool bookAvailability = true;
	bool notCreated = true;
	Book* currentBook = firstBook;
	std::cin.ignore();
	//input book details
	std::cout << "Please enter the book title: " << std::endl;
	std::getline(std::cin,bookName);
	std::cout << "Please enter the book author: " << std::endl;
	std::getline(std::cin, bookAuthor);
	std::cout << "Please enter the isbn number: " << std::endl;
	std::getline(std::cin, ISBNno);
	//create new book
	Book* newBook = new  Book(bookName, bookAuthor, ISBNno, bookAvailability);
	//check if book linked list is empty
	if (firstBook != NULL) {
		//iterate through the linked list until last object found
		while (notCreated) {
			//check if the next book is null
			//if not then set it as current book
			if (currentBook->getNext() != NULL)
				currentBook = currentBook->getNext();
			//if current book is last in linked list 
			//set new book as the next bok
			else {
				currentBook->setNextBook(newBook);
				newBook->setPrevious(currentBook);
				notCreated = false;
			}
		}

	}
	//if linked list empty make the new book the begininnig
	else
		firstBook = newBook;
	std::cout<<"Book succesfuly created."<<std::endl;
	
	/**
	Book* nextParam = bookPosition->getNext();


	if (bookPosition->getNext() != NULL) {
		bookParam->setNextBook(nextParam);
		bookPosition->getNext()->setPrevious(bookParam);
	}
	else {
		bookParam->setNextBook(NULL);
	}

	bookPosition->setNextBook(bookParam);
	bookParam->setPrevious(bookPosition);

	**/
};
//removes the book by changing next and previous pointers
void removeBook() {

	std::cout << "Delete book menu." << std::endl;
	//search repository for the book to delete
	//return it to the temporary pointer
	Book* deleteBook = currentUser.searchRepository(firstBook);
	int input = 0;
	//check if admin wants to delete the book for sure
	std::cout << "Are you sure you want to delete this book?: " << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2.No"<< std::endl;
	std::cin >> input;
	if (input == 1) {
		//get the before and after pointers
		Book* after = deleteBook->getNext();
		Book* before = deleteBook->getPrevious();
		//check if books are first or last in linked list
		//if not set the pointers 
		if (before != NULL)
			before->setNextBook(after);
		else
			firstBook = after;
		if (after != NULL)
			after->setPrevious(before);
		else
			after->setPrevious(NULL);
		std::cout << "Book succesfully deleted" << std::endl;
	}
	else {
		std::cout << "Returning... "<<std::endl;
		return;
	}
};
//adds a user to the linked list
void addUser() {
	//variables
	std::string nameParam = "";
	std::string passwordParam = "";
	std::string userType = "";
	bool notCreated = true;
	Guest* currentUserParam = firstUser;

	//get new user details and create it
	std::cin.ignore();
	std::cout << "Please enter the user name: " << std::endl;
	std::getline(std::cin, nameParam);
	std::cout << "Please enter the user password: " << std::endl;
	std::getline(std::cin, passwordParam);
	std::cout << "Please enter the the user type (Admin/Registered): " << std::endl;
	std::getline(std::cin, userType);
	Guest* newUser = new  Guest(nameParam, passwordParam, userType);
	//check if user list is empty
	if (firstUser != NULL) {
		//iterate through array list
		while (notCreated) {
			//if next user is not null
			//get the next user
			if (currentUserParam->getNextUser() != NULL)
				currentUserParam = currentUserParam->getNextUser();
			else {
				// If user was last user then add the new user at that point
				currentUserParam->setNextUser(newUser);
				newUser->setPreviousUser(currentUserParam);
				notCreated = false;
			}
		}

	}
	//if linked list is empty set the new user as the start of linked list
	else
		firstUser = newUser;
	std::cout << "User succesfuly created." << std::endl;
};
//remove the user from the list
void removeUser() {
	std::cout << "Remove user menu." << std::endl;
	//variables
	Guest* deleteUser = NULL;
	std::string userName = "";
	int input = 0; 
	Guest* current = firstUser;
	bool userDeleted = true;
	bool moreUsers = true;
	//iterate through linked list
	while (userDeleted) {
		// get user name in order to find user
		std::cout << "Please enter the user name: " << std::endl;
		std::cin.ignore();
		std::getline(std::cin, userName);
		//iterate through list looking for the username
		while (moreUsers) {
			//if user is found
			if (current->getUserLogin() == userName) {
				//get the next and previous users
				Guest* after = current->getNextUser();
				Guest* before = current->getPreviousUser();
				//set the next and previous pointers
				if (before != NULL)
					before->setNextUser(after);
				else
					firstUser = after;
				if (after != NULL)
					after->setPreviousUser(before);
				//break out the loop
				userDeleted = false;
				std::cout << "User succesfully delted" << std::endl;
				std::cout << "Returning to login menu." << std::endl;
				return;
			}
			if (current->getNextUser() != NULL)
				current = current->getNextUser();
			else
				moreUsers = false;
		}
	}
};
//populate the repository
void setUpBooks() {
	//create new books
	artOfWar = Book("Art of War", "Sun Tzu", "1234", true);
	dodger = Book("Dodger", "Terry Pratchett", "1235", false);
	raisingSteam = Book("Raising Steam", "Terry Pratchett", "1236", true);
	aClashOfKings = Book("A Clash of Kings", "George Martin", "1237", false);
	winterKnights = Book("Winter Knights", "Paul Stewart", "1238", true);
	wintersmith = Book("Wintersmith", "Terry Pratchett", "1239", true);
	firstBook = &artOfWar;
	
	//set next books
	artOfWar.setNextBook(&dodger);
	dodger.setNextBook(&raisingSteam);
	raisingSteam.setNextBook(&aClashOfKings);
	aClashOfKings.setNextBook(&winterKnights);
	winterKnights.setNextBook(&wintersmith);

	//set previous books
	wintersmith.setPrevious(&winterKnights);
	winterKnights.setPrevious(&aClashOfKings);
	aClashOfKings.setPrevious(&raisingSteam);
	raisingSteam.setPrevious(&dodger);
	dodger.setPrevious(&artOfWar);
	

}

void adminMenu() {
	//variables
	int input = 0;
	Book* bookFound;
	std::string availability = "Available";
	//menu choices
	std::cout << "Welcome to administration menu, please choose one of the following: " << std::endl;
	std::cout << "0. Return." << std::endl;
	std::cout << "1. Search repository." << std::endl;
	std::cout << "2. Add book." << std::endl;
	std::cout << "3. Delete book" << std::endl;
	std::cout << "4. Add user." << std::endl;
	std::cout << "5. Delete user." << std::endl;
	std::cin >> input;
	switch (input) {
		//return case
	case(0) : {
		return;
		break;
	}
		//search repositoru
	case(1) : {
		int in = -1;
		//search repository and set the pointer to the book found
		bookFound = currentUser.searchRepository(firstBook);
		if (bookFound->checkAvailability() == false)
			availability = "Unavailable";
		std::cout << "The book is currently: " << availability << std::endl;

		std::cout << "0. To return" << std::endl;
		std::cout << "1. Set book as available" << std::endl;
		std::cout << "2. Set book as unavailable" << std::endl;
		std::cin >> in;
		switch (in) {
		case(0) : {
			return;
			break;
		};
				  //set book as available
		case(1) : {
			bookFound->setAvailability(true);
			std::cout << "Book set as available." << std::endl;
			break;
		}
				  //set the book as unavialable
		case(2) : {
			bookFound->setAvailability(false);
			std::cout << "Book set as unavailable" << std::endl;
			break;
		}
		}
		break;
	}
	case(2) : {
		//add book method call
		addBook();
		break;
	}
	case(3) : {
		//remove book method call
		removeBook();
		break;
	}
	case(4) : {
		//add user method call
		addUser();
		break;
	}
	case(5) : {
		//remove user method call
		removeUser();
		break;
	}
	}
};
//populates users and allows to log in 
void setUp() {
	int input = 1;
	std::string userName;
	std::string userPassword;
	bool loggedIn = false;
	bool moreUsers;

	//construct objects
	guestUser =  Guest("guest");
	registeredUser = Guest("jim","1234","Registered");
	administrator = Guest("alan","4321", "Admin");

	//set up next users
	administrator.setNextUser(&registeredUser);
	registeredUser.setPreviousUser(&administrator);
	firstUser = &administrator;

	//set up all the books
	setUpBooks();

	std::cout << "" << std::endl;
	std::cout << "Welcome to Hardback Libraries book repository" << std::endl;
	while (input != 0) {
		//main login menu
		std::cout << "Please choose one of the following options: " << std::endl;
		std::cout << "1. Login" << std::endl;
		std::cout << "2. Guest User" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cin >> input;
		std::cin.ignore();
		//switch cases based on input
		switch (input) {
		case(1) :
			//iterate untill logged in
			while (loggedIn != true) {
				//if there are no users
				if (firstUser == NULL) {
					std::cout << "There are no users. Redirecting to creation screen." << std::endl;
					return;
				}

				//variables
				moreUsers = true;
				currentUser = *firstUser;
				userName = "";
				userPassword = "";
				//ask for user name and input
				std::cout << "Please enter the user name: " << std::endl;
				
				std::getline(std::cin, userName);
				//return if input is 0
				if (userName == "0")
					break;
				
				std::cout << "Please enter the user password: " << std::endl;
				std::getline(std::cin, userPassword);
				//return if password is 0
				if (userPassword == "0")
					break;
				//iterate through users linked lists
				while (moreUsers) {
					if (currentUser.getUserLogin() == userName && currentUser.getPassword() == userPassword) {
						std::cout << "Succesfully logged in as a: " << currentUser.getUserType() << " type user." << std::endl;
						//if user is a registered user
						//log in and search repository
						if (currentUser.getUserType() == "Registered")
							currentUser.registeredUserSearch(firstBook);
						else
							//if user is admin go to admin menu
							adminMenu();
						break;
					}
					//if reached end of linked list and no match
					//print and return to start  of method
					if (currentUser.getNextUser() == NULL) {	
					std::cout << "The password or user name was incorrect, please try again" << std::endl;
					moreUsers = false;
					}
					//get next user
					else
						currentUser = *(currentUser.getNextUser());
				}
				
				currentUser = *firstUser;
				
			}
			break;
		case(2) :
			//guest screen login
			input = -4;
			currentUser = guestUser;
			std::cout << "Welcome to the guest screen." << std::endl;
			while (input != 0) {
				Book* bookFound;
				//search repository and show book availability
				bookFound = currentUser.searchRepository(firstBook);
				if (bookFound->checkAvailability() == false)
					std::cout << "This book is unavailable." << std::endl;
				else
					std::cout << "This book is available." << std::endl;
				input = 0;
			}
			input = -5;
			break;
		case(3) :
			return;
		}
	}

};
void main() {
	
	setUp();
	system("pause");
}