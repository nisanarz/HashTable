#include <cstdlib>
#include "hashTable.h"

#define SIZE 4
#define C1 2
#define C2 3

#define INPUT_CHECK if (citizenID < 0){ \
						throw InvalidInput(); \
					}

#define CHOOSE_CONSTANT int hx = citizenID % totalSize; \
						int rx; \
						if (citizenID % 2 == 0){ \
							rx = citizenID % (totalSize - C1); \
						} else if (citizenID / (totalSize - C2) % 2 == 0){ \
								rx = citizenID % (totalSize - C2) + 1; \
							} else{ \
								rx = citizenID % (totalSize - C2); \
							}

HashTable::HashTable() : citizens(new Citizen*[SIZE]), totalSize(SIZE), occupiedSize(0){
	for (int i = 0; i < SIZE; i++){
		citizens[i] = NULL;
	}
}
HashTable::~HashTable(){
	for (int i = 0; i < totalSize; i++){
		delete citizens[i];
	}
	delete[] citizens;
}


void HashTable::reHash(){
	int newSize = totalSize * 2;
	Citizen** citizens2 = new Citizen*[newSize];
	for (int i = 0; i < newSize; i++){
		citizens2[i] = NULL;
	}
	for (int i = 0; i < totalSize; i++){
		int id = citizens[i]->getCitizenID(); 
		int hx = id % newSize;
		int rx;
		if (id % 2 == 0){
			rx = id % (newSize - C1);
		}
		else{
			if (id / (newSize - C2) % 2 == 0){
				rx = id % (newSize - C2) + 1;
			}
			else{
				rx = id % (newSize - C2);
			}
		}
		for (int k = 0; k < newSize; k++){
			int h = (hx + k *(1 + rx)) % newSize;
			if (citizens2[h] == NULL){
				citizens2[h] = citizens[i];
				citizens[i] = NULL;
				break;
			}
		}
	}
	delete[] citizens;
	citizens = citizens2;
	totalSize = newSize;
}

void HashTable::addCitizen(int citizenID){
	INPUT_CHECK
	if (findCitizen(citizenID) != NULL){
		throw CitizenAlreadyExist();
	}
	CHOOSE_CONSTANT
	for (int k = 0; k < totalSize; k++){
		int h = (hx + k * (1 + rx)) % totalSize;
		if (citizens[h] == NULL){
			citizens[h] = new Citizen(citizenID);
			occupiedSize++;
			break;
		}
	}
	if (occupiedSize == totalSize){
		reHash();
	}
}

Citizen* HashTable::findCitizen(int citizenID) const{
	INPUT_CHECK
	CHOOSE_CONSTANT
	for (int k = 0; k < totalSize; k++){
		int h = (hx + k * (1 + rx)) % totalSize;
		if (citizens[h] != NULL && citizens[h]->getCitizenID() != citizenID){
			continue;
		} else if (citizens[h] == NULL){
			return NULL;
		}
		else if (citizens[h]->getCitizenID() == citizenID){
			return citizens[h];
		}
	}
	return NULL;
}

int HashTable::getTotalSize() const{
	return totalSize;
}

int HashTable::getOccupiedSize() const{
	return occupiedSize;
}

int HashTable::getIdByCell(int i) const{
	return (citizens[i] == NULL) ? -1 : citizens[i]->getCitizenID();
}