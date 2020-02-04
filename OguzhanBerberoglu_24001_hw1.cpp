#include<iostream>
#include<pthread.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

int M[2][50];
int turn = 0;

void *printMatrix() // displays matrix to console
{
	cout << "The flight is full. Numbers represent the travel agency ids';" << endl;
	cout << "Seats; " << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			cout << setw(2) << M[i][j];
		}cout << endl;
	}
}

bool isMatrixFull() // checks the cells contains 0(false) or not(true)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 50; j++){
			if (M[i][j] == 0)
				return false;
		}
	}
	return true;
}

void *Agency1 (void* id) // TravelAgency1 Thread Process
{
	int * agencyID = (int*) id;
	while (!isMatrixFull())
	{
		while(turn != 0); // busy waiting
		/********** Critical Region ***********/
		cout << "TravelAgency" << *agencyID << " is entering the critical region.." << endl;
		int i,j,randomSeat;
		do
		{
			randomSeat = rand()%100+1;
			if (randomSeat%2 == 0){
				i=1;
				j = randomSeat/2-1;
			}
			else{
				i=0;
				j=(randomSeat+1)/2-1;
			}
		} while (!isMatrixFull() && M[i][j] != 0 );
		M[i][j] = 1;
		cout << "Seat Number " << randomSeat << " is reserved by TravelAgency" << *agencyID << endl; 
		cout << "TravelAgency" << *agencyID << " is exiting the critical region.." << endl << endl;
		/********** non-Critical Region ***********/
		turn = 1;
	}
}

void *Agency2 (void* id) // TravelAgency2 Thread Process
{
	int * agencyID = (int*) id;
	while (!isMatrixFull())
	{
		while(turn != 1); // busy waiting
		/********** Critical Region ***********/
		cout << "TravelAgency" << *agencyID << " is entering the critical region.." << endl;
		int i,j,randomSeat;
		do
		{
			randomSeat = rand()%100+1;
			if (randomSeat%2 == 0){
				i=1;
				j = randomSeat/2-1;
			}
			else{
				i=0;
				j=(randomSeat+1)/2-1;
			}
		} while (!isMatrixFull() && M[i][j] != 0 );
		M[i][j] = 2;
		cout << "Seat Number " << randomSeat << " is reserved by TravelAgency" << *agencyID << endl; 
		cout << "TravelAgency" << *agencyID << " is exiting the critical region.." << endl << endl;
		/********** non-Critical Region ***********/
		turn = 2;
	}
}

void *Agency3 (void* id) // TravelAgency3 Thread Process
{
	int * agencyID = (int*) id;

	while (!isMatrixFull())
	{
		while(turn != 2); // busy waiting
		/********** Critical Region ***********/
		cout << "TravelAgency" << *agencyID << " is entering the critical region.." << endl;
		int i,j,randomSeat;
		do
		{
			randomSeat = rand()%100+1;
			if (randomSeat%2 == 0){
				i=1;
				j = randomSeat/2-1;
			}
			else{
				i=0;
				j=(randomSeat+1)/2-1;
			}
		} while (!isMatrixFull() && M[i][j] != 0 );
		M[i][j] = 3;
		cout << "Seat Number " << randomSeat << " is reserved by TravelAgency" << *agencyID << endl; 
		cout << "TravelAgency" << *agencyID << " is exiting the critical region.." << endl << endl;
		/********** non-Critical Region ***********/
		turn = 0;	
	}
}

int main()
{
	pthread_t TravelAgency1,TravelAgency2,TravelAgency3;
	int id1=1,id2=2,id3=3;

	for (int i = 0; i < 2; i++) // Matrix celss initiliazed to 0
		for (int j = 0; j < 50; j++)
			M[i][j] = 0;

	pthread_create( &TravelAgency1, NULL, Agency1, (void*) &id1);
    pthread_create( &TravelAgency2, NULL, Agency2, (void*) &id2);
	pthread_create( &TravelAgency3, NULL, Agency3, (void*) &id3);

	while (!isMatrixFull());

	pthread_join(TravelAgency1, NULL);
	pthread_join(TravelAgency2, NULL); 
	pthread_join(TravelAgency3, NULL); 
	
	printMatrix();
	return 0;
}