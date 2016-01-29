
#include "bank.h"


int main(){
	bank myBank;
	myBank.currentCustomerIndex = 0;
	myBank.importInfo();
	if (myBank.cityBank[0].accountOpen == false)
	{
		myBank.currentCustomerIndex = -1;
		myBank.addCustomer();
	}
	else{
		welcome();
		myBank.userLogin();
	}
	//prompts for a account to be made if their are no accounts in the struct.
	//otherwise ask for userlogin


	myBank.menu();

}
void welcome(){
	cout << "Jeremy Woodward \n162\n02/12/2015\n" << endl;
	cout << setw(50) << setfill('*') << "Welcome to Big Money Bank" << setw(90) << setfill('*');
	cout << "\nTo get started Please create a new account" << endl;
	cout << "or login to a existing account." << endl;
	cout << endl;
}



customer bank::currentCustomer()
{
	return cityBank[currentCustomerIndex];
}


customer bank::findCustomer(){
	int count = 0, limiter = 0;
	string accountName;
	limiter = numberOfCustomers();
	cout << "Account name: ";
	getline(cin, accountName);
	while (count < limiter)
	{

		if (cityBank[count].accountHolder == accountName)
		{
			return cityBank[count];
		}
		count++;
	}

	//looks for a account based on the name. returns the location of the account
}

int bank::findCustomerLocation(){
	int count = 0, limiter = 0;
	string accountName;
	limiter = numberOfCustomers();
	cout << "Account name: ";
	getline(cin, accountName);
	while (count < limiter)
	{

		if (cityBank[count].accountHolder == accountName)
		{
			return count;
		}
		count++;
	}
	if (count == limiter){
		cout << "Account not found, Please try again";
		findCustomerLocation();
	}

	//looks for a account based on the name. returns the location of the account
}
void bank::userLogin(){
	int customerLocation = 0;
	char choice;
	cout << "[C]ustomer Account [T]eller Account [M]anager Account"<< endl;
	cout << ": ";
	cin >> choice; cin.ignore(100, '\n');
	while (!cin)
	{
		cin.clear();
		cout << "Sorry, Wrong input try again: ";
		cin >> choice; cin.ignore(100, '\n');

	}
	choice = toupper(choice);
	switch (choice)
	{
	case 'C':
		
		customerLocation = findCustomerLocation();
		currentCustomerIndex = customerLocation;
		break;
	case 'T':
		tellerAccount();
		break;
	case 'M':
		managerFunctions();
		break;
	default:
		cout << "Didn't catch that, try again." << endl;
		userLogin();
		break;
	}
	
	//Ask the user to input a username to log in, checks to make sure the username exists. 
}


void bank::showAllCustomers(){
	int count = 0, account;
	account = numberOfCustomers();
	while (count < account)
	{
		cout << cityBank[count].accountHolder << endl;
		count++;
	}
}
void bank::showBalance(){
	cout << "Account: " << cityBank[currentCustomerIndex].accountHolder << endl;
	cout << "Checking: " << setprecision(5) << cityBank[currentCustomerIndex].checkingPerson.balance << endl;
	cout << "Savings: " << setprecision(5) << cityBank[currentCustomerIndex].savingsPerson.balance << endl;
	cout << "Credit: " << setprecision(5) << cityBank[currentCustomerIndex].creditPerson.balance << endl;

}
void bank::showBalance(customer chosenCustomer){
	cout << "Account: " << chosenCustomer.accountHolder << endl;
	cout << "Checking: " << setprecision(5) << chosenCustomer.checkingPerson.balance << endl;
	cout << "Savings: " << setprecision(5) << chosenCustomer.savingsPerson.balance << endl;
	cout << "Credit: " << setprecision(5) << chosenCustomer.creditPerson.balance << endl;

}
bool bank::alreadyExists( string accountname){
	int count = 0, accounts = 0;
	bool already = false;
	accounts = numberOfCustomers();
	while (count <= accounts)
	{


		if (cityBank[count].accountHolder == accountname)
		{

			already = true;
			break;
		}
		count++;
	}
	return already;
}
void  bank::customerChoice(){
	char ch1;
	double amount = 0;

	cout << "[W]ithdraw or [D]eposit: ";
	cin >> ch1; cin.ignore(100, '\n');
	ch1 = toupper(ch1);
	logger(ch1);
	if (ch1 == 'W'){
		cityBank[currentCustomerIndex].getAccount().withdrawFunds();
		showBalance();
	}
	else{
		cityBank[currentCustomerIndex].getAccount().depositFunds();
		showBalance();
	}

}
int bank::numberOfCustomers(){
	int temp = 0, k = 0;
	while (cityBank[k].accountHolder != "")
	{
		k++;
	}
	temp = k;
	return temp;
	//returns the total number of accounts in the struct
}
void bank::amountOfMoney(){
	double totalAmount = 0, temp = 0;
	int count = 0, total = 0;
	total = numberOfCustomers();
	while (count < total){
		temp = cityBank[count].checkingPerson.balance +
			cityBank[count].savingsPerson.balance +
			cityBank[count].creditPerson.balance;
		totalAmount += temp;
		count++;
	}
	cout << "The amount of money in the bank is: " << totalAmount << endl;
	//parses each account for a total amount of money and keeps a running total
}
void bank::addCustomer(){
	string accountname;
	currentCustomerIndex = numberOfCustomers();
	initalize();
	cityBank[currentCustomerIndex].accountOpen = true;
	cout << "Please enter a account name: ";
	getline(cin, accountname);
	if (alreadyExists(accountname) == true)
	{
		cout << "Account name already exists " << endl;
		currentCustomerIndex--;
		addCustomer();
	}
	else{
		cityBank[currentCustomerIndex].accountHolder = accountname;
	}
	while (!cin)
	{
		cin.clear();
		cout << "sorry no special characters, only letters and numbers" << endl;
		cout << "Please enter the name again: ";
		cin >> cityBank[currentCustomerIndex].accountHolder; cin.ignore(100, '\n');
	}
	//makes a new account in the struct at the next mainIterator location
}
void bank::removeCustomer(){
	char ch1;
	int count = 0, accounts = 0;
	accounts = numberOfCustomers();
	string accountName;
	cout << "Enter the account name you want to delete: ";
	getline(cin, accountName);
	cout << "Is this correct? Y/N " << accountName;
	cin >> ch1;
	ch1 = toupper(ch1);
	if (ch1 == 'Y')
	{

		while (count < accounts)
		{


			if (cityBank[count].accountHolder == accountName)
			{
				deInitalize(count);
				break;

			}
			count++;
		}
	}
	else{
		cin.clear();
		cin.ignore(100, '\n');
		removeCustomer();
	}
	//sets accountOpen to false and all the other checking, saving, credit to 0
}
void bank::transferFunds(){
	double amount = 0;
	cout << "how much money do you want to transfer?";
	while (cin >> amount){
		cin.clear();
		cout << "Sorry! Only positive numbers";
		cout << " Amount to deposit: ";
		cin >> amount; cin.ignore(100, '\n');
	}
	cout << "transfer from" << endl;

	if (cityBank[currentCustomerIndex].getAccount().withdrawFunds(amount) == 0)
	{
		cout << "Transfer canceled: insufficient funds" << endl;
		amount = 0;
	}
	else{
		cout << "transfer to " << endl;
		cityBank[currentCustomerIndex].getAccount().depositFunds(amount);
	}
	logger('T', amount);
}
void bank::transferBetweenCustomers(){
	customer firstAccount, secondAccount;
	double amount = 0;
	cout << "Transfer from ";
	firstAccount = findCustomer();
	showBalance(firstAccount);
	cout << "\nAmount to transfer: ";
	cin >> amount; cin.ignore(100, '\n');
	if (firstAccount.getAccount().withdrawFunds(amount) == 0)
	{
		cout << "Transfer canceled: insufficient funds" << endl;
		amount = 0;
	}
	else{
		cout << "Transfer to ";
		secondAccount = findCustomer();
		showBalance(secondAccount);
		secondAccount.getAccount().depositFunds(amount);
	}

	while (amount < 0 || !cin){
		cin.clear();
		cout << "Sorry! Only positive numbers";
		cout << " Amount to deposit: ";
		cin >> amount; cin.ignore(100, '\n');
	}
	logger('T', amount);
	//gets two accounts and sets one to withdraw and one to deposit
	//withdraws from first account and deposits to the second

}
void bank::importInfo(){
	bool iftrue;
	string name;
	ifstream import;
	import.open("customerinfo.txt");
	if (import.is_open())
	{

		while (!import.fail()){
			iftrue = false;
			import >> iftrue;
			if (iftrue == true)
			{
				cityBank[currentCustomerIndex].accountOpen = iftrue;
				import.ignore(100, '\n');
				getline(import, name, '\n');
				cityBank[currentCustomerIndex].accountHolder = name;
				import >> cityBank[currentCustomerIndex].checkingPerson.balance;
				import.ignore(100, '\n');
				import >> cityBank[currentCustomerIndex].savingsPerson.balance;
				import.ignore(100, '\n');
				import >> cityBank[currentCustomerIndex].creditPerson.balance;
			}
			if (cityBank[currentCustomerIndex].accountHolder == "")
			{
				currentCustomerIndex -= 2;
			}
			currentCustomerIndex++;
		}

	}
	import.close();
	//Fills struct with data, sets mainIterator to number of iterations
}
void bank::exportInfo(){
	int j = 0, k = 0;
	k = numberOfCustomers();
	ofstream fileExport;
	fileExport.open("customerinfo.txt");
	if (fileExport.is_open()){
		while (cityBank[j].accountHolder != ""){
			if (cityBank[j].accountOpen == false)
			{
				j++;
			}
			fileExport << cityBank[j].accountOpen << endl;
			fileExport << cityBank[j].accountHolder << endl;
			fileExport << cityBank[j].checkingPerson.balance << endl;
			fileExport << cityBank[j].savingsPerson.balance << endl;
			fileExport << cityBank[j].creditPerson.balance << endl;
			fileExport << endl;
			j++;

		}
	}
	else cout << "File not open";
	fileExport.close();
}

void bank::initalize(){
	cityBank[currentCustomerIndex].accountOpen = false;
	cityBank[currentCustomerIndex].accountHolder;
	cityBank[currentCustomerIndex].checkingPerson.balance = 0;
	cityBank[currentCustomerIndex].savingsPerson.balance = 0;
	cityBank[currentCustomerIndex].creditPerson.balance = 0;

}
void bank::deInitalize(int count){
	cityBank[count].accountOpen = false;
	cityBank[count].accountHolder = "closed";
	cityBank[count].checkingPerson.balance = 0;
	cityBank[count].savingsPerson.balance = 0;
	cityBank[count].creditPerson.balance = 0;

}
void bank::menu(){
	char inquire;
	cout << "[B]alance [A]ccount [M]anager" << endl;
	cout << "[F]transfer [T]eller [L]og [Q]uit " << endl;
	cout << ": ";
	cin >> inquire; cin.ignore(100, '\n');
	inquire = toupper(inquire);
	logger(inquire);
	switch (inquire)
	{
	case 'A':
		customerChoice();
		menu();
		break;
	case 'B':
		showBalance();
		menu();
		break;
	case 'M':
		managerFunctions();
		menu();
		break;
	case 'T':
		tellerAccount();
		menu();
		break;

	case 'F':
		transferFunds();
		showBalance();
		menu();
		break;
	case 'L':
		viewLog();
		menu();
		break;

	case 'Q':
		exportInfo();
		break;
	default:
		menu();
		break;
	}

}

void bank::managerFunctions(){
	char ch1;
	int customerLocation = 0;
	cout << "[A]ccounts [D]eposits [W]ithdraws [R]transfers" << endl;
	cout <<	"[M]oney [S]how [T]eller [B]transfer Menu [F]ind [Q]back" << endl;
	cout << ":";
	cin >> ch1; cin.ignore(100, '\n');
	ch1 = toupper(ch1);
	switch (ch1)
	{
	case 'A':
		cout << "Number of accounts: " << numberOfCustomers() << endl;
		managerFunctions();
		break;
	case 'B':
		transferMenu();
		break;
	case 'D':
		cout << "Number of deposits: " << totalDeposits() << endl;
		managerFunctions();
		break;
	case 'W':
		cout << "Number of withdraws: " << totalWithdraws() << endl;
		managerFunctions();
		break;
	case 'R':
		cout << "Number of transfers: " << totalTransfers() << endl;
		managerFunctions();
		break;
	case 'M':
		amountOfMoney();
		managerFunctions();
		break;
	case 'S':
		showAllCustomers();
		managerFunctions();
		break;
	case 'T':
		tellerAccount();
		managerFunctions();
		break;
	case 'F':
		customerLocation = findCustomerLocation();
		currentCustomerIndex = customerLocation;
		showBalance();
		managerFunctions();
		break;
	case 'Q':
		menu();
		break;
	default:
		cout << "Wrong input" << endl;
		managerFunctions();
		break;
	}
	//All the functions that the manager has access to, so all the functions.
}
void bank::transferMenu(){
	char ch1;
	cout << "[T]ransfer [B]transfer between accounts [Q]back" << endl;
	cout << ":";
	cin >> ch1; cin.ignore(100, '\n');
	ch1 = toupper(ch1);
	switch (ch1)
	{
	case 'B':
		transferBetweenCustomers();
		break;
	case 'T':
		transferFunds();
		break;
	case 'Q':
		break;
	default:
		break;
	}
}
void bank::tellerAccount(){
	char choice;
	int customerLocation = 0;
	cout << "[A]dd Account [D]elete Account [B]alance" << endl;
	cout <<"[C]ustomer Accounts [S]how Account [F]ind Account [Q]back" << endl;
	cout << ":";
	cin >> choice; cin.ignore(100, '\n');
	choice = toupper(choice);
	if (!cin){
		cin.clear();
		tellerAccount();
	}
	switch (choice)
	{
	case 'A':
		addCustomer();
		tellerAccount();
		break;
	case 'C':
		findCustomer();
		customerChoice();
		tellerAccount();
		break;
	case 'D':
		removeCustomer();
		tellerAccount();
		break;
	case 'B':
		showBalance();
		tellerAccount();
		break;
	case 'S':
		showAllCustomers();
		tellerAccount();
		break;
	case 'F':
		customerLocation = findCustomerLocation();
		currentCustomerIndex = customerLocation;
		tellerAccount();
		break;
	case 'Q':
		break;
	default:
		cout << "Wrong input" << endl;
		tellerAccount();
		break;
	}
	//The functions that the teller has access to
}
void Account::depositFunds(){
	//have them pick the account first then decide how much they want to deposit.
	double amountToDeposit = 0;
	cout << "Amount to deposit: ";
	cin >> amountToDeposit; cin.ignore(100, '\n');
	while (!cin || amountToDeposit < 0){
		cin.clear(); cin.ignore(100, '\n');
		cout << "Sorry! Only positive numbers" << endl;
		cout << "Amount to deposit: ";
		cin >> amountToDeposit;

	}
	balance = amountToDeposit + balance;
	logger('D', amountToDeposit);

}
void Account::depositFunds(double addTo){

	balance += addTo;
	logger('D', addTo);

}
void Account::withdrawFunds(){

	char  continues;
	double amount;
	cout << "Amount: ";
	cin >> amount; cin.ignore(100, '\n');
	while (amount < 0 || !cin){
		cin.clear(); cin.ignore(100, '\n');
		cout << "Sorry! Only positive numbers";
		cout << "Amount to deposit: ";
		cin >> amount; cin.ignore(100, '\n');
	}

	if (balance - amount < 0){
		cout << "looks like you're going to over draw your account\n and will receive a overdraft fee, \ndo you want to continue? Y/N: ";
		cin >> continues; cin.ignore(100, '\n');
		continues = toupper(continues);
		if (continues == 'N'){
			amount = 0;
		}
		else{
			amount += 30;
		}
	}
	balance = balance - amount;

	logger('W', amount);
}
double Account::withdrawFunds(double takeAway){
	if (balance - takeAway < 0){
		takeAway = 0;
	}
	balance -= takeAway;
	logger('W', takeAway);
	return takeAway;
	//gets the balance, minuses the amount the user specified then returns a double
}
Account& customer::getAccount(){
	char accountChoice;
	cin.clear();
	cout << "[C]hecking [S]avings [R]Credit" << endl;
	cout << ": ";
 	cin >> accountChoice; cin.ignore(100, '\n');
	accountChoice = toupper(accountChoice);
	logger(accountChoice);
	
	switch (accountChoice)
	{
	case 'C':
		return checkingPerson;
		break;
	case 'S':
		return savingsPerson;
		break;
	case 'R':
		return creditPerson;
		break;
	default:
		cout << "error 22" << endl;
		getAccount();
		break;

	}
	
}

void logger(char menu){
	ofstream output;
	output.open("logstats.txt", ios::app);


	switch (menu)
	{
	case 'B':
		output << __TIMESTAMP__ << "{ BALANCE }" << endl;
		break;
	case 'D':
		output << __TIMESTAMP__ << "{ DEPOSIT }" << endl;
		break;
	case 'W':
		output << __TIMESTAMP__ << "{ WITHDRAW }" << endl;
		break;
	case 'L':
		output << __TIMESTAMP__ << "{ LOG }" << endl;
		break;
	case 'T':
		output << __TIMESTAMP__ << "{ TRANSFER }" << endl;
		break;
	}
	output.close();

}
void logger(char menu, double amountcheck){
	ofstream output;
	output.open("logstats.txt", ios::app);


	switch (menu)
	{

	case 'D':
		output << __TIMESTAMP__ << "{ DEPOSIT: " << amountcheck << "}" << endl;
		break;
	case 'W':
		output << __TIMESTAMP__ << "{ WITHDRAW: " << amountcheck << "}" << endl;
		break;
	case 'T':
		output << __TIMESTAMP__ << "{ TRANSFER: " << amountcheck << " }" << endl;
		break;
	}
	output.close();

}
void viewLog(){
	string line;
	ifstream view;
	view.open("logstats.txt");
	if (view.is_open()){
		while (getline(view, line)){

			cout << line << endl;
		}
	}
	else{
		cout << "unable to open file";
	}
	view.close();
}
int totalDeposits(){
	string line, match;
	int count = 0;
	match = ("{ DEPOSIT }");
	size_t found;
	ifstream view;
	view.open("logstats.txt");
	if (view.is_open()){
		while (getline(view, line)){
			found = line.find(match);
			found += 2;
			if (line[found] == 'D')
			{
				count++;
			}
		}
	}
	else{
		cout << "unable to open file";
	}
	view.close();
	return count;
}
int totalWithdraws(){
	string line, match;
	int count = 0;
	match = ("{ WITHDRAW }");
	size_t found;
	ifstream view;
	view.open("logstats.txt");
	if (view.is_open()){
		while (getline(view, line)){
			found = line.find(match);
			found += 2;
			if (line[found] == 'W')
			{
				count++;
			}
		}
	}
	else{
		cout << "unable to open file";
	}
	view.close();
	return count;
}
int totalTransfers(){
	string line, match;
	int count = 0;
	match = ("{ TRANSFER }");
	size_t found;
	ifstream view;
	view.open("logstats.txt");
	if (view.is_open()){
		while (getline(view, line)){
			found = line.find(match);
			found += 2;
			if (line[found] == 'T')
			{
				count++;
			}
		}
	}
	else{
		cout << "unable to open file";
	}
	view.close();
	return count;
}