#ifndef HASHTABALE_H
#define HASHTABALE_H

#include <exception>
#include "citizen.h"

class HashTable{
	Citizen** citizens;
	int totalSize;
	int occupiedSize;
	void reHash();
public:
	HashTable();
	~HashTable();
	void addCitizen(int citizenID);
	Citizen* findCitizen(int citizenID) const;
	int getTotalSize() const;
	int getOccupiedSize() const;
	int getIdByCell(int i) const;

	//exceptions:
	class InvalidInput : public std::exception {};
	class CitizenAlreadyExist : public std::exception {};
};


#endif