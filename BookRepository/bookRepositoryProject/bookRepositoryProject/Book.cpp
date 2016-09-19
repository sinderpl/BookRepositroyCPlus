#include<iostream>
#include "Book.h"
#include "Guest.h"
//constructor
Book::Book() {};
Book::Book(std::string titleParam, std::string authorParam, std::string isbnNoParam, bool availabilityParam) {
	title = titleParam;
	author = authorParam;
	isbnNo = isbnNoParam;
	availability = availabilityParam;
	next = NULL;
	previous = NULL;
	owner = NULL;
};
//setsv
void Book::setOwner(Guest* ownerParam) {
	owner = ownerParam;
};
void Book::setTitle(std::string titleParam) {
	title = titleParam;
};
void Book::setAuthor(std::string authorParam) {
	author = authorParam;
};
void Book::setIsbnNo(std::string isbnNoParam) {
	isbnNo = isbnNoParam;
};
void Book::setNextBook(Book* nextParam) {
	if (nextParam != NULL) {
		next = nextParam;
	}
	else {
		next = NULL;
	}
	
};
void Book::setPrevious(Book* previousParam) {
	if(previousParam != NULL){
		previous = previousParam;
	}
	else {
		previous = NULL;
	}
};
void Book::setAvailability(bool availabilityParam) {
	availability = availabilityParam;
};

//gets
Guest* Book::getOwner()const{
	return owner;
};
std::string Book::getTitle()const {
	return title;
};
std::string Book::getAuthor()const {
	return author;
};
std::string Book::getIsbnNo()const {
	return isbnNo;
};
Book* Book::getNext()const {
	return next;
};
Book* Book::getPrevious()const {
	return previous;
};
bool Book::checkAvailability()const {
	return availability;
};