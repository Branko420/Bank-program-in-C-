#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;

const unsigned short POSSIBLE_NUMBER_OF_CLIENTS = 50;
unsigned short errorCountrer = 0;
int loop = 0;

struct Client {
	string name;
	unsigned int yearOfCreation, id;

	string currency1;
	long double value1;
	unsigned int yearOfCreatedVlog1;

	Client* adress;
}*head = NULL,*p;

struct arrayOne  {
	string name;
	unsigned int yearOfCreation, id;

	string currency1;
	long double value1;
	unsigned int yearOfCreatedVlog1;
};
struct arrayTwo  {
	string name;
	unsigned int yearOfCreation, id;

	string currency1;
	long double value1;
	unsigned int yearOfCreatedVlog1;
};
struct arrayThree {
	string name;
	unsigned int yearOfCreation, id;

	string currency1;
	long double value1;
	unsigned int yearOfCreatedVlog1;
};
struct maxEuroArray {
	string name;
	unsigned int yearOfCreation, id;

	string currency1;
	long double value1;
	unsigned int yearOfCreatedVlog1;
};

Client* addFirstClient(Client* firstClient, int Id, string name, int yearOfCreation, string currency1, double value, int yearOfCreatedVlog, int& curr_clients) {
	if (firstClient != NULL || curr_clients < 0) {
		cout << "There is aweready a first clint!" << endl;
		return NULL;
	}
	Client* addNewClient = new Client;
	addNewClient->id = Id;
	addNewClient->name = name;
	addNewClient->yearOfCreation = yearOfCreation;
	addNewClient->currency1 = currency1;
	addNewClient->value1 = value;
	addNewClient->yearOfCreatedVlog1 = yearOfCreatedVlog;
	addNewClient->adress = firstClient;
	return addNewClient;
}
Client* addOtherClient(Client* prevClient, int Id, string name, int yearOfCreation, string currency1, double value, int yearOfCreatedVlog, int& curr_clients) {
	if (prevClient == NULL) {
		cout << "how tf did you get here?";
		return NULL;
	}
	Client* newClient = new Client;
	newClient->id = Id;
	newClient->name = name;
	newClient->yearOfCreation = yearOfCreation;
	newClient->currency1 = currency1;
	newClient->value1 = value;
	newClient->yearOfCreatedVlog1 = yearOfCreatedVlog;
	newClient->adress = prevClient->adress;
	newClient->adress = prevClient;
	return newClient;

}

// Меню за избор на функциите от програмата(прототип на функцията)
void menu(Client input[], int& curr_clients);
 
// Добавяне на нов вложител с един влог. Избира се валутата на влога (BGN (лев), USD (долар), EURO(евро))
void addClient(Client* clients, int& curr_clients);
void removeClient(Client* clients, int& curr_clients);
void addAndRemoveClient(int& curr_clients) {
	cout << "what would you like to do?\n1.Add Client\n2.Remove Client\n0.Back\nInput: ";
	int fun; cin >> fun;
	switch (fun)
	{
	case 1: 
		addClient(head, curr_clients);
		break;
	case 2:
		if (curr_clients == 0){
			cout<<"There is no clients to be remove!\nFirst add a Clinet.\n";
			addClient(head, curr_clients);
		}
		else
			removeClient(head, curr_clients);
	default:
		break;
	}
}
void removeClient(Client* clients, int& curr_clients) {
	Client* removeClients = clients;
	Client* showClients = clients;
	Client *prevc= removeClients;
	cout << "Who would you like to remove?:\n";
	int i = 0;
	while (true) {
		if (showClients != NULL) {
			cout << "ID: " << showClients->id << "\nName: " << showClients->name << endl;
			cout << "_______________________________________________________________\n";
		}
		i++; showClients = showClients->adress;
		if (i == curr_clients) break;
	}
	cout << "Choose a Client by ID or Name: ";
	string choice; cin >> choice;
	int intChoice = atoi(choice.c_str());
	
	int j = 0;
	if (removeClients->id == intChoice || removeClients->name == choice) {
		cout << "Do you really want to remove " << removeClients->name << "? [Y/N]: ";
		char YorN; cin >> YorN;
		switch (YorN) {
		case 'Y':
		case 'y':
		curr_clients--;
		loop--;
		head = removeClients->adress;
		delete removeClients;
		return;
		break;
		case 'N':
		case'n':
			addAndRemoveClient(curr_clients);
			break;
		}
	}
	while (removeClients != NULL && removeClients->id != intChoice || removeClients->name != choice) {
		prevc = removeClients;
		removeClients = removeClients->adress;
		if (removeClients->id == intChoice || removeClients->name == choice)break;
	}
	cout << "Do you really want to remove " << removeClients->name << "? [Y/N]: ";
	char YorN; cin >> YorN;
	switch (YorN) {
	case 'Y':
	case 'y':
		curr_clients--;
		loop--;
		prevc->adress = removeClients->adress;
		delete removeClients;
		return;
		break;
	case 'N':
	case'n':
		addAndRemoveClient(curr_clients);
		break;
	}
}
void addClient(Client * clients, int& curr_clients)
{	
	Client* searchForID = clients;
	int inputClientsNumber;
	bool existingCurrrency=false;
	string name = " ", currency = " ";
	double value =0.0; int yearOfCreation=0, yearOfCreatedVlog=0, id=0;
	cout << "How much clients you would like to add?: ";
	cin >> inputClientsNumber;
	curr_clients = curr_clients + inputClientsNumber;
	for (loop; loop < curr_clients; loop++) {
		id = loop + 1; while (searchForID != NULL) {
			if (searchForID->id == id)
				id++;
			searchForID = searchForID->adress;	
		}cout << "Name: "; cin >> name; cout << "Year of Creation: "; cin >> yearOfCreation;
		while (existingCurrrency == false) {
			int len = currency.length();
			cout << "Currency: "; cin >> currency; for (int i = 0; i <currency.length(); i++) {
				currency[i] = (char)toupper((int)currency[i]);
			}if (currency == "BGN" || currency == "USD" || currency == "EURO") {
				break;
			}
			else {
				cout << "Its needs to be BGN, EURO or USD" << endl;
				existingCurrrency = false;
			}
		}
		cout << "Value: "; cin >> value; cout << "Year of created vlog: "; cin >> yearOfCreatedVlog;
		cout<<"_______________________________________________________"<< endl;
		if (loop == 0) head =addFirstClient(head,id, name, yearOfCreation, currency, value, yearOfCreatedVlog, curr_clients);
		else head = addOtherClient(head, id, name, yearOfCreation, currency, value, yearOfCreatedVlog, curr_clients);
	}
	system("cls");
}

//Добавяне на списък от вложители. Въвежда се цяло число n и след него n на брой вложители с един влог.Избира се валутата на влога(BGN(лев), USD(долар), EURO(евро))
void outputClientsByNumberOfVlogsAndCurrency(Client * clients, int& curr_clients) {
	int counterForVlogsEURO = 0;
	int counterForVlogsBGN = 0;
	int counterForVlogsUSD = 0;
	Client* current=clients;
	for (int i = 0; i < curr_clients;i++) {
		if (current->currency1 == "BGN")
			counterForVlogsBGN++;
		else if (current->currency1 == "USD")
			counterForVlogsUSD++;
		else if (current->currency1 == "EURO")
			counterForVlogsEURO++;
		current = current->adress;
	}
	cout << "Type an N number to output N number of clients with 1 vlog: ";
	int n; cin >> n;
	cout << "Type a currency you would like to out put the clients: ";
	string currency; cin >> currency;
	if (currency == "euro" || currency == "EURO") {
		if (n > counterForVlogsEURO) {
			cout << "We didn't have that much of clients with 1 EURO vlogs.\nWe have " << counterForVlogsEURO << " vlogs.\n Try again with smaller number.\n";
			cout << "_______________________________________________________\n";
			outputClientsByNumberOfVlogsAndCurrency(head, curr_clients);
		}
		else {
			for (int i = 0; i < n; i++) {
				if ( clients->currency1 == "BGN" || clients->currency1 == "USD")
					n++;
					if (clients->currency1 == "EURO") {
						cout << "ID: " << clients->id << "		" << "Name: " << clients->name << "	\n"  << "	" << "Currency of vlogs: " << clients->currency1 << "	\n" << "Value: " << clients->value1 << "		" << "Year of creation: " << clients->yearOfCreation << endl;
						cout << "_______________________________________________________\n";
					}
					clients = clients->adress;
			}
		}
	}
	else if (currency == "bgn" || currency == "BGN") {
		if (n > counterForVlogsBGN) {
			cout << "We didn't have that much of clients with 1 BGN vlogs.\nWe have " << counterForVlogsBGN << " vlogs.\n Try again with smaller number.\n";
			cout << "_______________________________________________________\n";
			outputClientsByNumberOfVlogsAndCurrency(head, curr_clients);
		}
		else {
			for (int i = 0; i < n; i++) {
				if (clients->currency1 == "USD" || clients->currency1 == "EURO")
					n++;
					if (clients->currency1 == "BGN") {
						cout << "ID: " << clients->id << "		" << "Name: " << clients->name << "	\n"  << "	" << "Currency of vlogs: " << clients->currency1 << "	\n" << "Value: " <<clients->value1 << "		" << "Year of creation: " << clients->yearOfCreation << endl;
						cout << "_______________________________________________________\n";
					}
					clients = clients->adress;
			}
		}
	}
	else if (currency == "usd" || currency == "USD") {
		if (n > counterForVlogsUSD) {
			cout << "We didn't have that much of clients with 1 USD vlogs.\nWe have " << counterForVlogsUSD << " vlogs.\n Try again with smaller number.\n";
			cout << "_______________________________________________________\n";
			outputClientsByNumberOfVlogsAndCurrency(head, curr_clients);
		}
		else {

			for (int i = 0; i < n; i++) {
				if (clients->currency1 == "BGN" || clients->currency1 == "EURO")
					n++;
				
					if (clients->currency1 == "USD") {
						cout << "ID: " << clients->id << "		" << "Name: " << clients->name << "	\n" << "	" << "Currency of vlogs: " << clients->currency1 << "	\n" << "Value: " << clients->value1 << "		" << "Year of creation: " << clients->yearOfCreation << endl;
						cout << "_______________________________________________________\n";
					}
					clients = clients->adress;
			}
		}
	}
	else {
		cout << "We didn't have this type of currency.\nTry again.\n";
		outputClientsByNumberOfVlogsAndCurrency(head, curr_clients);
	}
	system("pause");
	system("cls");
}

//Извеждане на всички вложители в оформен вид
void outputClients(Client * clients, int& curr_clients) {
	while (clients != NULL) { 
			cout << "ID: " << clients->id << "\nName: " << clients->name << "\nYear of creation: " << clients->yearOfCreation << endl;
			clients = clients->adress;
	}
	system("pause");
	system("cls");
}

//Извеждане на вложители с влог BGN
void outputClientsWithBGNVlogs(Client * clients, int& curr_clients) {
	while(clients!=NULL) {
		if (clients->currency1 == "BGN")
				cout << " Currency: " << clients->currency1 << "	|" << "Value: " << clients->value1 << "	|" << "Year of vlog creation: " << clients->yearOfCreatedVlog1 << "	|" << endl;
		clients = clients->adress;
	}
	cout<< "_______________________________________________________\n";
	system("pause");
	system("cls");
}

//Извеждане на вложители с максимален влог в EURO
void outputTheClientWithMaximumValueOfEUROVlogs( Client * clients, int& curr_clients) {
	Client* findMaxEuroUser = clients;
	int index = 0;
	maxEuroArray arr[10];

	while(findMaxEuroUser !=NULL) {
		if (findMaxEuroUser->currency1 == "EURO" && index <10) {
			arr[index].name = findMaxEuroUser->name;
			arr[index].id = findMaxEuroUser->id;
			arr[index].yearOfCreation = findMaxEuroUser->yearOfCreation;
			arr[index].currency1 = findMaxEuroUser->currency1;
			arr[index].value1 = findMaxEuroUser->value1;
			arr[index].yearOfCreatedVlog1 = findMaxEuroUser->yearOfCreatedVlog1;
			index++;
			if (index == 10) break;
		}
		findMaxEuroUser = findMaxEuroUser->adress;
	}
	int bottom = 1
		,mid, celling;
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index - i -1; j++) {
			if (arr[j].value1 < arr[j + 1].value1)
				swap(arr[j], arr[j + 1]);
		}
	}
	cout << "Give celling for the search: ";
	cin >> celling;
	while (celling < arr[0].value1) {
		if (celling == arr[0].value1) break;
		cout << "Celling is more smaller than the max.\nTry again: "; cin >> celling;
	}
	mid= (bottom-1 + celling) / 2;
	int nesht = 1;
	while (true) {
		if (mid < arr[0].value1) {
			bottom = mid;
			mid = mid + mid + 1;
		}
		 if (mid > arr[0].value1) {
			 celling = mid;
			mid = mid / 2 - 1;
		}
		if (mid == arr[0].value1 || mid+1 == arr[0].value1 || mid-1 == arr[0].value1) {
			cout << "ID: " << arr[0].id << "	|" << "Name: " << arr[0].name << "	|" << "Value: " << arr[0].value1 << "	|" << endl;
			system("pause");
			system("cls");
			return;
		}
		nesht++;
	}
}

//Подреждане на основния масив с вложители, без да се извежда на екрана
void swapClients(Client * clients , int& curr_clients) {
	Client* current = clients;
	Client* index = NULL;
	Client* prevIndex;

	int idTemp;
	string nameTemp;
	int yearOfCreationTemp;
	double valueTemp;
	string currencyTemp;
	int yearOfCreatedVlogTemp;

	bool flag = false;
		while (current != NULL) {
			int nesh = 0;
			index = current;
			while (index != NULL) {
				prevIndex = index;
				if (nesh == 0) {
					index = index->adress;
					nesh++;
				}
				if (index != NULL)
					if (index->id >= prevIndex->id) {
						index = index->adress;
					}
					else {
						idTemp = index->id;
						nameTemp = index->name;
						yearOfCreationTemp = index->yearOfCreation;
						currencyTemp = index->currency1;
						valueTemp = index->value1;
						yearOfCreatedVlogTemp = index->yearOfCreatedVlog1;

						index->id = prevIndex->id;
						index->name = prevIndex->name;
						index->yearOfCreation = prevIndex->yearOfCreation;
						index->currency1 = prevIndex->currency1;
						index->value1 = prevIndex->value1;
						index->yearOfCreatedVlog1 = prevIndex->yearOfCreatedVlog1;

						prevIndex->id = idTemp;
						prevIndex->name = nameTemp;
						prevIndex->yearOfCreation = yearOfCreationTemp;
						prevIndex->currency1 = currencyTemp;
						prevIndex->value1 = valueTemp;
						prevIndex->yearOfCreatedVlog1 = yearOfCreatedVlogTemp;

						index = prevIndex->adress;
					}
			}
			current = current->adress; cout << "im here" << endl;
		}
	return;
}

// Извлича от базовия масив вложителите от дадена година на откриване на сметка и ги сортира по номер на сметка
void sortIDFromGivenYearOfCreation(Client * clients, int& curr_clients) {
	arrayOne firstArray[500];
	int add = 0;
	while (clients != NULL){
		firstArray[add].id = clients->id;
		firstArray[add].name = clients->name;
		firstArray[add].currency1 = clients->currency1;
		firstArray[add].value1 = clients->value1;
		firstArray[add].yearOfCreatedVlog1 = clients->yearOfCreatedVlog1;
		firstArray[add].yearOfCreation = clients->yearOfCreation;
		clients = clients->adress;
		add++;
	}
	cout << "What is the year you would like add?: ";
	int year; cin >> year;
	arrayThree item[500];
	for (int i = 0; i < curr_clients; i++) {
		if (firstArray[i].yearOfCreation == year) {
			for (int cycleStart = 0; cycleStart < curr_clients - 2; cycleStart++) {
				item[cycleStart].id = firstArray[cycleStart].id;
				item[cycleStart].name = firstArray[cycleStart].name;
				item[cycleStart].value1 = firstArray[cycleStart].value1;
				item[cycleStart].currency1 = firstArray[cycleStart].currency1;
				item[cycleStart].yearOfCreatedVlog1 = firstArray[cycleStart].yearOfCreatedVlog1;
				item[cycleStart].yearOfCreation = firstArray[cycleStart].yearOfCreation;
				int pos = cycleStart;
				for (int i = cycleStart + 1; i < curr_clients; i++) 
					if (firstArray[i].id < item[cycleStart].id)
						pos++; 
				if (pos == cycleStart)
					continue;
				while (item[cycleStart].id == firstArray[pos].id)
					pos++;
				if (pos != cycleStart) {
					int idTemp = item[cycleStart].id;
					string nameTemp = item[cycleStart].name;
					int yearOfCreationTemp = item[cycleStart].yearOfCreation;
					double valueTemp = item[cycleStart].value1;
					string currencyTemp = item[cycleStart].currency1;
					int yearOfCreatedVlogTemp = item[cycleStart].yearOfCreatedVlog1;
					item[cycleStart].id = firstArray[pos].id;
					item[cycleStart].name = firstArray[pos].name;
					item[cycleStart].yearOfCreation = firstArray[pos].yearOfCreation;
					item[cycleStart].currency1 = firstArray[pos].currency1;
					item[cycleStart].value1 = firstArray[pos].value1;
					item[cycleStart].yearOfCreatedVlog1 = firstArray[pos].yearOfCreatedVlog1;
					firstArray[pos].id = idTemp;
					firstArray[pos].name = nameTemp;
					firstArray[pos].yearOfCreation = yearOfCreationTemp;
					firstArray[pos].currency1 = currencyTemp;
					firstArray[pos].value1 = valueTemp;
					firstArray[pos].yearOfCreatedVlog1 = yearOfCreatedVlogTemp;
				}
				while (pos != cycleStart)
				{
					pos = cycleStart;

					// Find position where we put the element
					for (int i = cycleStart + 1; i < curr_clients; i++)
						if (firstArray[i].id< item[cycleStart].id)
							pos += 1;

					// ignore all duplicate  elements
					while (item[cycleStart].id == firstArray[pos].id)
						pos += 1;

					// put the item to it\'s right position
					if (item[cycleStart].id != firstArray[pos].id)
					{
						int idTemp = item[cycleStart].id;
						string nameTemp = item[cycleStart].name;
						int yearOfCreationTemp = item[cycleStart].yearOfCreation;
						double valueTemp = item[cycleStart].value1;
						string currencyTemp = item[cycleStart].currency1;
						int yearOfCreatedVlogTemp = item[cycleStart].yearOfCreatedVlog1;
						item[cycleStart].id = firstArray[pos].id;
						item[cycleStart].name = firstArray[pos].name;
						item[cycleStart].yearOfCreation = firstArray[pos].yearOfCreation;
						item[cycleStart].currency1 = firstArray[pos].currency1;
						item[cycleStart].value1 = firstArray[pos].value1;
						item[cycleStart].yearOfCreatedVlog1 = firstArray[pos].yearOfCreatedVlog1;
						firstArray[pos].id = idTemp;
						firstArray[pos].name = nameTemp;
						firstArray[pos].yearOfCreation = yearOfCreationTemp;
						firstArray[pos].currency1 = currencyTemp;
						firstArray[pos].value1 = valueTemp;
						firstArray[pos].yearOfCreatedVlog1 = yearOfCreatedVlogTemp;
					}
				}
			}
		}
	}
	for (int out = 0; out < curr_clients; out++) {
		if (firstArray[out].yearOfCreation == year) {
			cout << "ID: " << firstArray[out].id << "		" << "Name: " << firstArray[out].name << "	\n" << "	" << "Year of creation: " << firstArray[out].yearOfCreation << endl << "Currency: " << firstArray[out].currency1 << "	Value: " << firstArray[out].value1 << "	Year of created vlog: " << firstArray[out].yearOfCreatedVlog1 << endl;
			cout << "_______________________________________________________\n";
		}
	}
	system("pause");
	system("cls");
}

//Извлича от базовия масив вложителите, които имат само един влог и ги сортира по стойност на този влог
void sortByValueFromClientsWithOneVlog(Client * clients, int& curr_clients) {
	arrayTwo secondArray[500];
	int i = 0;
	while (clients != NULL) {
		secondArray[i].id = clients->id;
		secondArray[i].name = clients->name;
		secondArray[i].currency1 = clients->currency1;
		secondArray[i].value1 = clients->value1;
		secondArray[i].yearOfCreatedVlog1 = clients->yearOfCreatedVlog1;
		secondArray[i].yearOfCreation = clients->yearOfCreation;
		clients = clients->adress;
		i++;
	}
	int id, yearOfCreation, yearOfCreatedVlog; double values; int j; string name, currency;
	// insertion sort
	for (int sort = 0; sort < curr_clients; sort++) {
		id = secondArray[sort].id;
		name = secondArray[sort].name;
		yearOfCreation = secondArray[sort].yearOfCreation;
		currency = secondArray[sort].currency1;
		values = secondArray[sort].value1;
		yearOfCreatedVlog = secondArray[sort].yearOfCreatedVlog1;
		j = sort - 1;
		while (j >= 0 && secondArray[j].value1 > values) {
			secondArray[j + 1] = secondArray[j];
			j--;
		}
		secondArray[j + 1].id = id;
		secondArray[j + 1].name = name;
		secondArray[j + 1].yearOfCreation = yearOfCreation;
		secondArray[j + 1].currency1 = currency;
		secondArray[j + 1].value1 = values;
		secondArray[j + 1].yearOfCreatedVlog1 = yearOfCreatedVlog;
	}

	for (int out = 0; out < curr_clients; out++) {
			cout << "ID: " << secondArray[out].id << "		" << "Name: " << secondArray[out].name << "	\n"  << "	" << "Year of creation: " << secondArray[out].yearOfCreation << endl << "Currency: " << secondArray[out].currency1 << "	Value: " << secondArray[out].value1 << "	Year of created vlog: " << secondArray[out].yearOfCreatedVlog1 << endl;
			cout << "_______________________________________________________\n";
	}
	system("pause");
	system("cls");
}

//Справки за влоговете с под меню
void referencesForSubMenuVlogs(Client * clients, int& curr_clients) {
	int inputFun = NULL;
	do {
		cout << "_______________________________________________________\n";
		cout << "1. Sort with ID with added year.\n2. Sort clients with one vlog by value of the vlog.\n0. Go back.\n_______________________________________________________\nInput: ";
		cin >> inputFun;
		system("cls");
		switch (inputFun) {
		case 1:
			sortIDFromGivenYearOfCreation(head, curr_clients);
			break;
		case 2:
			sortByValueFromClientsWithOneVlog(head, curr_clients);
			break;
		case 0:
			menu(head, curr_clients);
			break;
		default:
			cout << "There is no function whit that number.\nPlease try again.\n";
			referencesForSubMenuVlogs(head, curr_clients);
			system("pause");
			system("cls");
			break;
		}
	} while (inputFun != 0);
}

// Меню за избор на функциите от програмата
void menu(Client input[], int& curr_clients) {
	int inputFun = NULL;
	do {
		cout << "_______________________________________________________\n";
		cout << "1.	Add a Client/Remove a Client.\n2.	Show clients with one vlog.\n3.	Show every client.\n4.	Show every client with BGN currency vlog.\n5.	SHow the highest added value form client in EURO currency.\n6.	Sort clients by ID\n9.	Vlog inquiries.\n0.	Exit.\n";
		cout << "_______________________________________________________\nInput your option: ";
		cin >> inputFun;
		system("cls");
		if (inputFun > 1 && inputFun < 13) {
			if (inputFun != 8)
				if (curr_clients == 0) {
					cout << "There is no clients to interact with " << inputFun << " function.\nTry to add clients.\n";
					system("pause");
					system("cls");
					menu(input, curr_clients);
				}
			if (inputFun == 1 && curr_clients >= 50) {
				cout << "You can't add new clients.\nThe limit is 50.\n";
				system("pause");
				system("cls");
				menu(input, curr_clients);
			}
		}
		switch (inputFun)
		{
		case 1:
			addAndRemoveClient(curr_clients);
			break;
		case 2:
			outputClientsByNumberOfVlogsAndCurrency(head, curr_clients);;
			break;
		case 3:
			outputClients(head, curr_clients);
			break;
		case 4:
			outputClientsWithBGNVlogs(head, curr_clients);
			break;
		case 5:
			outputTheClientWithMaximumValueOfEUROVlogs(head, curr_clients);
			break;
		case 6:
			for(int i = 0;i<curr_clients;i++)
			swapClients(head, curr_clients);
			break;
		case 9:
			referencesForSubMenuVlogs(head, curr_clients);
			break;
		case 0:
			cout << "Bye.\n";
			exit(0);
			break;
		default:
			cout << "There is no function whit that number.\nPlease try again.\n";
			system("pause");
			system("cls");
			break;
		}
		system("cls");
	} while (inputFun != 0);
}
int main() {
	int count = 0;
	Client input[POSSIBLE_NUMBER_OF_CLIENTS];
	menu(input, count);
}