#ifndef Book_h
#define Book_h
#include<iostream>
class Guest;

class Book {
public:
	//constructor
	Book();
	Book(std::string titleParam,std::string authorParam, std::string isbnNoParam, bool availabilityParam);
	//sets
	void setOwner(Guest* ownerParam);
	void setTitle(std::string titleParam);
	void setAuthor(std::string authorParam);
	void setIsbnNo(std::string isbnNoParam);
	void setNextBook(Book* nextParam);
	void setPrevious(Book* previousParam);
	void setAvailability(bool availabilityParam);
	//gets
	Guest* getOwner()const;
	std::string getTitle()const;
	std::string getAuthor()const;
	std::string getIsbnNo()const;
	Book* getNext()const;
	Book* getPrevious()const;
	bool checkAvailability()const;

	//methods

private:
	Guest* owner;
	std::string title;
	std::string author;
	std::string isbnNo;
	bool availability;
	Book* next;
	Book* previous;
};

#endif