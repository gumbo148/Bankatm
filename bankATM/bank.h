#include<iostream>
#include<string>
#include<iomanip>
#include<cctype>
#include<ctime>
#include<fstream>
using namespace std;
struct Account{


	void depositFunds();
	void depositFunds(double addTo);
	void withdrawFunds();
	double withdrawFunds(double takeAway);
	double balance;

};


struct customer{
	bool	accountOpen = false;
	string  accountHolder;
	Account checkingPerson;
	Account savingsPerson;
	Account creditPerson;
	Account& getAccount();
	
};

struct bank
{
	int currentCustomerIndex;
	customer cityBank[100];

	customer currentCustomer();
	customer findCustomer();
	int findCustomerLocation();
	void userLogin();
	void showAllCustomers();
	void showBalance();
	void showBalance(customer chosenCustomer);
	bool alreadyExists( string accountname);
	int numberOfCustomers();
	void customerChoice();
	void amountOfMoney();
	void addCustomer();
	void removeCustomer();
	void transferFunds();
	void transferBetweenCustomers();
	void importInfo();
	void exportInfo();
	void initalize();
	void deInitalize(int count);
	void menu();
	void managerFunctions();
	void transferMenu();
	void tellerAccount();
};

void logger(char menu);
void logger(char menu, double accountcheck);
void viewLog();
int totalDeposits();
int totalWithdraws();
int totalTransfers();
void welcome();