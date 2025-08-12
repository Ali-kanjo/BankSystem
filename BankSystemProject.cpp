
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenueScreen();

enum enMainMenuOptions {

	enShowClientList = 1,
	enAddClient = 2,
	enUpdateClient = 3,
	enDeleteClient = 4,
	enFindClient = 5,
	enExit = 6
};
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim = " ") {
	short Pos = 0;
	string sWord = "";
	vector<string>vString;

	while ((Pos = S1.find(Delim)) != string::npos) {

		sWord = S1.substr(0, Pos);

		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, Pos + Delim.length());
	}

	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;
}

stClient ConvertLineToRecord(string S1, string Separator = "#//#") {
	vector<string> vString = SplitString(S1, Separator);
	stClient Client;

	Client.AccountNumber = vString.at(0);
	Client.PinCode = vString.at(1);
	Client.Name = vString.at(2);
	Client.Phone = vString.at(3);
	Client.AccountBalance = stod(vString.at(4));

	return Client;
}

vector<stClient> LoadClientsDataFromFile(string FileName) {

	fstream MyFile;
	vector<stClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);

		}

		MyFile.close();
	}
	return vClients;
}

string ConvertRecordToLine(stClient Client, string Separator = "#//#") {
	string S1 = "";

	S1 += Client.AccountNumber + Separator;
	S1 += Client.PinCode + Separator;
	S1 += Client.Name + Separator;
	S1 += Client.Phone + Separator;
	S1 += to_string(Client.AccountBalance);

	return S1;
}

void AddDataLineToFile(string FileName, string line) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << line << endl;

		MyFile.close();
	}
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		stClient Client;
		string Line;

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber) {

				MyFile.close();

				return true;

			}
		}
		MyFile.close();
	}

	return false;
}

vector<stClient> SaveClientsDataInFile(string FileName, vector<stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stClient C : vClients) {
			if (C.MarkForDelete == false) {

				MyFile << ConvertRecordToLine(C) << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

void PrintFormatPresentation() {
	cout << "\n__________________________________________________________________________________________________\n\n";
	cout << setw(18) << left << "| Account Number ";
	cout << setw(12) << left << "| Pin Code ";
	cout << setw(40) << left << "| Client Name ";
	cout << setw(16) << left << "| Phone ";
	cout << setw(11) << left << "| Balance ";
	cout << "\n__________________________________________________________________________________________________\n\n";
}

void PrintClientRecordLine(stClient Client) {

	cout << "| " << setw(16) << left << Client.AccountNumber;
	cout << "| " << setw(10) << Client.PinCode;
	cout << "| " << setw(38) << Client.Name;
	cout << "| " << setw(14) << Client.Phone;
	cout << "| " << setw(9) << Client.AccountBalance;
	cout << "\n";
}

void ShowAllClientsScreen() {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In The System!";
	else
		cout << "\t\t\t\t Client List (" << vClients.size() << ") Client (s)";

	PrintFormatPresentation();
	cout << "\n";

	for (stClient C : vClients) {
		PrintClientRecordLine(C);
	}

	cout << "\n__________________________________________________________________________________________________\n";

}

stClient ReadNewClient() {
	stClient Client;

	cout << "\n";
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
		cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;

}

void AddNewClient() {
	stClient Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void ShowAddNewClientsScreen() {
	char AddMore = 'n';

	do {
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tAdd New Clients Screen";
		cout << "\n___________________________________\n\n";
		cout << "Adding New Client  : \n";
		AddNewClient();

		cout << "\n\nClient Added Successfully, do you want to add more clients ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

string ReadClientAccountNumber() {
	string AccountNumber = "";
	cout << "Please enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client) {
	for (stClient C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;

		}
	}
	return false;
}

void PrintClientCard(stClient Client) {

	cout << "\nThe following is the extracted client record :\n";
	cout << "\nAccount Number : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << endl;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
	for (stClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client ?(y/n) ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataInFile(ClientsFileName, vClients);
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\n\nClient Deleted Successfully \n";
			return true;
		}

	}
	else {
		cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}

bool ShowDeleteClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n___________________________________\n\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	bool Condition = DeleteClientByAccountNumber(AccountNumber, vClients);
	return Condition;
}

stClient ChangeClientRecord(string AccountNumber) {
	stClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\nEnter PinCode ? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdateClientDataByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

	char Answer = 'n';
	stClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to update this client ?(y/n) ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {

			for (stClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataInFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.\n";
			return true;
		}

	}
	else
	{
		cout << "\nClient with Account number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}

bool ShowUpdateClientScreen() {
	cout << "\n----------------------------------------\n";
	cout << "\t Update Client Info Screen";
	cout << "\n________________________________________\n\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	bool Condition = UpdateClientDataByAccountNumber(AccountNumber, vClients);
	return Condition;
}

bool ShowFindClientScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\t Find Client Screen";
	cout << "\n___________________________________\n\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		return true;
	}
	else
	{
		cout << "\nClient with Account number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}

short ReadMainMenuOption() {
	short UserChoice;
	cout << "Choose what do you want to do ? [1 to 6]? ";
	cin >> UserChoice;
	return UserChoice;
}

void ShowEndScreen() {
	cout << "\n---------------------------------\n";
	cout << "\tProgram end :-)";
	cout << "\n_________________________________\n";
}

void GoBackToMainMenue() {
	cout << "\n\n\n\n";
	cout << "Press any key to go back to Main Menue... ";
	system("pause>0");
	ShowMainMenueScreen();
}

void PerformMainMenueOption(enMainMenuOptions UserChoice) {

	switch (UserChoice)
	{

	case enMainMenuOptions::enShowClientList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enAddClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enExit:
		system("cls");
		ShowEndScreen();
		break;
	default:
		system("cls");
		ShowEndScreen();
		break;
	}

}

void ShowMainMenueScreen() {
	system("cls");
	cout << "================================================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Update Client.\n";
	cout << "\t[4] Delete Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "================================================\n";
	PerformMainMenueOption((enMainMenuOptions)ReadMainMenuOption());



}

int main() {

	ShowMainMenueScreen();
	system("pause>0");
	return 0;
}

