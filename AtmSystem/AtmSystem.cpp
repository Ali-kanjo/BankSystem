#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;
const string ClientsFileName = "Clients.txt";
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enATMMainMenueOptio {
	QuickWithdraw = 1,
	NormalWithdraw = 2,
	Deposit = 3,
	CheckBalance = 4,
	eEditAccountInfo = 5,
	Logout = 6
};
enum enQuickWithdrawOption {
	Twenty = 1,
	Fifty = 2,
	Hundred = 3,
	TwoHundred = 4,
	FourHundred = 5,
	SixHundred = 6,
	EightHundred = 7,
	Thousand = 8,
	Exit = 9
};
enum enEditAccountInfo {
	enShowAccountInfo = 1,
	enChangeName = 2,
	enChangePinCode = 3,
	enChangePhoneNumber = 4,
	enMainMenu = 5
};
stClient CurrentClient;
void ShowAtmMainMenueScreen();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void ShowEditAccountInformation();
void Login();

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
stClient ConvertClientLineToRecord(string S1, string Separator = "#//#") {
	vector<string> vString = SplitString(S1, Separator);
	stClient Client;

	Client.AccountNumber = vString.at(0);
	Client.PinCode = vString.at(1);
	Client.Name = vString.at(2);
	Client.Phone = vString.at(3);
	Client.AccountBalance = stod(vString.at(4));

	return Client;
}
string ConvertClientRecordToLine(stClient Client, string Separator = "#//#") {
	string S1 = "";

	S1 += Client.AccountNumber + Separator;
	S1 += Client.PinCode + Separator;
	S1 += Client.Name + Separator;
	S1 += Client.Phone + Separator;
	S1 += to_string(Client.AccountBalance);

	return S1;
}
vector<stClient> SaveClientsDataInFile(string FileName, vector<stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stClient C : vClients) {
			if (C.MarkForDelete == false)
				MyFile << ConvertClientRecordToLine(C) << endl;
		}
		MyFile.close();
	}
	return vClients;
}
vector<stClient> LoadClientsDataFromFile(string FileName) {

	fstream MyFile;
	vector<stClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;
		stClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertClientLineToRecord(Line);
			vClients.push_back(Client);

		}

		MyFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& Client) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode) {
			Client = C;
			return true;
		}
	}
	return false;
}
void GoBackToATMMainMunueScreen() {
	cout << "\n\n\n\n";
	cout << "Press any key to go back Main Menue...";
	system("pause>0");
	ShowAtmMainMenueScreen();
}
void GoBackToEditAccountInfoScreen() {
	cout << "\n\n\n\n";
	cout << "Press any key to back to Edit Account Info Screen ...";
	system("pause>0");
	ShowEditAccountInformation();
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, int BalanceToAdd, vector<stClient>& vClients) {
	char Answer = 'n';

	cout << "\n\nAre you sure you want to perform this transaction? (y/n) ?";
	cin >> Answer;

	if (toupper(Answer) == 'Y') {
		for (stClient& C : vClients) {

			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += BalanceToAdd;
				SaveClientsDataInFile(ClientsFileName, vClients);
				cout << "\n\nDone successfully, New Balance = " << C.AccountBalance;
				return true;
			}
		}
	}
	return false;
}

void MakeAWithdrawalTransaction(int Amount) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, -1 * Amount, vClients);
	CurrentClient.AccountBalance -= Amount;
}
bool AmountExceedsBalance(int Amount) {

	if (Amount > CurrentClient.AccountBalance) {
		cout << "\n\nThe amount exceeds your balance, Enter another choice.\n\n";
		system("pause");
		system("cls");

		return true;
	}
	return false;
}

bool ChangePhoneNumByAccountNumber(string AccountNumber, string NewPhoneNum) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.Phone = NewPhoneNum;
			SaveClientsDataInFile(ClientsFileName, vClients);
			return true;
		}
	}
	return false;
}
bool ChangePinCodeByAccountNumber(string AccountNumber, string PinCode) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.PinCode = PinCode;
			SaveClientsDataInFile(ClientsFileName, vClients);
			return true;
		}
	}
	return false;
}
bool ChangeNameByAccountNumber(string AccountNumber, string NewName) {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.Name = NewName;
			SaveClientsDataInFile(ClientsFileName, vClients);
			return true;
		}
	}
	return false;
}

bool ChangeAccountPhoneNumber() {
	string NewPhone;
	cout << "\nEnter New Phone Number ? ";
	getline(cin >> ws, NewPhone);
	char Answer = 'n';
	cout << "\nAre you sure you want to Change this PinCode? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		ChangePhoneNumByAccountNumber(CurrentClient.AccountNumber, NewPhone);
		CurrentClient.Phone = NewPhone;
		cout << "\n\Phone Changed Successfully.";
		return true;
	}
	return false;
}
void ShowChangePhoneNumberScreen() {
	cout << "==============================================\n";
	cout << "\t\tChange Phone Number Screen\n";
	cout << "==============================================\n";
	ChangeAccountPhoneNumber();
}
bool ChangeAccountName() {
	string NewName;
	cout << "\nEnter New Name ? ";
	getline(cin >> ws, NewName);
	char Answer = 'n';
	cout << "\nAre you sure you want to Change this PinCode? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		ChangeNameByAccountNumber(CurrentClient.AccountNumber, NewName);
		CurrentClient.Name = NewName;
		cout << "\n\Name Changed Successfully.";
		return true;
	}
	return false;
}
void ShowChangeNameScreen() {
	cout << "=======================================\n";
	cout << "\t\tChange Name Screen\n";
	cout << "=======================================\n";
	ChangeAccountName();
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
void ShowAccountInformationScreen() {
	cout << "===========================================\n";
	cout << "\t\tAccount Information \n";
	cout << "===========================================\n";
	PrintClientCard(CurrentClient);
	cout << "\n===========================================\n";
}
bool ChangeAccountPinCode() {
	string NewPinCode;
	cout << "\nEnter New PinCode ? ";
	getline(cin >> ws, NewPinCode);

	char Answer = 'n';
	cout << "\nAre you sure you want to Change this PinCode? y/n? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		ChangePinCodeByAccountNumber(CurrentClient.AccountNumber, NewPinCode);
		CurrentClient.PinCode = NewPinCode;
		cout << "\n\nPinCode Changed Successfully.";
		return true;
	}
	return false;

}
void ShowChangePinCodeScreen() {
	cout << "==============================================\n";
	cout << "\t\tChange Password Screen\n";
	cout << "==============================================\n";
	ChangeAccountPinCode();
}
void PerformEditAccountOption(enEditAccountInfo Option) {
	switch (Option) {
	case enEditAccountInfo::enShowAccountInfo:
		system("cls");
		ShowAccountInformationScreen();
		GoBackToEditAccountInfoScreen();
		break;
	case enEditAccountInfo::enChangeName:
		system("cls");
		ShowChangeNameScreen();
		GoBackToEditAccountInfoScreen();
		break;
	case enEditAccountInfo::enChangePinCode:
		system("cls");
		ShowChangePinCodeScreen();
		GoBackToEditAccountInfoScreen();
		break;
	case enEditAccountInfo::enChangePhoneNumber:
		system("cls");
		ShowChangePhoneNumberScreen();
		GoBackToEditAccountInfoScreen();
		break;
	case enEditAccountInfo::enMainMenu:
		ShowAtmMainMenueScreen();
		break;
	default:
		ShowAtmMainMenueScreen();
		break;
	}

}
short ReadEditAccountOption() {
	cout << "Enter What you want to do? [1 to 5] ?  ";
	short Option = 0;
	cin >> Option;
	return Option;
}
void ShowEditAccountInformation() {
	system("cls");
	cout << "==============================================\n";
	cout << "\t\tEdit Account Information\n";
	cout << "==============================================\n";
	cout << "\t[1] Show Account Information\n";
	cout << "\t[2] Change Name \n";
	cout << "\t[3] Change Password\n";
	cout << "\t[4] Change Phone Number\n";
	cout << "\t[5] Main Menue\n";
	cout << "==============================================\n";
	PerformEditAccountOption((enEditAccountInfo)ReadEditAccountOption());

}

int ReadNormalWithdrawOption() {
	int Amount = 0;

	do {
		cout << "\n\nEnter an amount multiple of 5's ? ";
		cin >> Amount;

	} while (Amount % 5 != 0);

	return Amount;
}
void PerformNormalWithdrawOption() {
	int Amount = ReadNormalWithdrawOption();

	AmountExceedsBalance(Amount) ? ShowNormalWithdrawScreen() : MakeAWithdrawalTransaction(Amount);
}
void ShowNormalWithdrawScreen() {
	cout << "=============================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "=============================================\n";
	PerformNormalWithdrawOption();

}
short GetBalanceNumberFromQuickWithdrawOption(short Option) {
	short arr[] = { 20,50,100,200,400,600,800,1000 };
	return arr[Option - 1];
}
short ReadQuickWithdrawOption() {
	short Option = 0;
	cout << "\nChoose What to Withdraw From [1] to [8] ? ";
	cin >> Option;
	return Option;
}
void PerformQuickWithdrawOption(enQuickWithdrawOption Option) {

	if (Option == enQuickWithdrawOption::Exit) {
		ShowAtmMainMenueScreen();
		return;
	}

	short Amount = GetBalanceNumberFromQuickWithdrawOption((short)Option);

	AmountExceedsBalance(Amount) ? ShowQuickWithdrawScreen() : MakeAWithdrawalTransaction(Amount);

}
void ShowQuickWithdrawScreen() {
	cout << "===============================================\n";
	cout << "\t\tQuick Withdraw Screen\n";
	cout << "===============================================\n";
	cout << "\t[1] 20" << "\t\t[2] 50\n";
	cout << "\t[3] 100 " << "\t[4] 200 \n";
	cout << "\t[5] 400 " << "\t[6] 600 \n";
	cout << "\t[7] 800 " << "\t[8] 1000 \n";
	cout << "\t[9] Exit\n";
	cout << "===============================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance;
	PerformQuickWithdrawOption((enQuickWithdrawOption)ReadQuickWithdrawOption());

}

double ReadDepositOption() {
	double Amount = 0;
	do {
		cout << "Enter a Positive Deposit Amount ? ";
		cin >> Amount;


	} while (Amount < 0);

	return Amount;
}
void PerformDepositBalanceOption() {
	short Amount = ReadDepositOption();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount, vClients);
	CurrentClient.AccountBalance += Amount;

}
void ShowDepositScreen() {
	cout << "=======================================\n";
	cout << "\t\tDeposit Screen \n";
	cout << "=======================================\n";
	PerformDepositBalanceOption();

}

void ShowCheckBalanceScreen() {
	cout << "=============================================\n";
	cout << "\t\tCheck Balance Screen \n";
	cout << "=============================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance;
}

short ReadATMMainMenueOption() {
	cout << "Choose what do you want to do ? [1 to 6]? ";
	short Option = 0;
	cin >> Option;
	return Option;
}
void PerformATMMainMenueOption(enATMMainMenueOptio Option) {
	switch (Option) {
	case enATMMainMenueOptio::QuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToATMMainMunueScreen();
		break;
	case enATMMainMenueOptio::NormalWithdraw:
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToATMMainMunueScreen();
		break;
	case enATMMainMenueOptio::Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToATMMainMunueScreen();
		break;
	case enATMMainMenueOptio::CheckBalance:
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToATMMainMunueScreen();
		break;
	case enATMMainMenueOptio::eEditAccountInfo:
		ShowEditAccountInformation();
	case enATMMainMenueOptio::Logout:
		Login();
		break;
	}
}
void ShowAtmMainMenueScreen() {
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Edit Account Info.\n";
	cout << "\t[6] Logout.\n";
	cout << "=============================================\n";
	cout << "\nHello " << CurrentClient.Name << " Welcome To Atm System:)\n\n";

	PerformATMMainMenueOption((enATMMainMenueOptio)ReadATMMainMenueOption());
}

bool LoadClientInfo(string AccountNumber, string PinCode) {
	return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient);
}
void Login() {
	string AccountNumber;
	string PinCode;
	bool LoadFailed = false;
	do {
		system("cls");
		cout << "\n----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n----------------------------------\n";

		if (LoadFailed) {
			cout << "Invalid Account Number/Password!\n";
		}

		cout << "Enter Account Number? ";
		getline(cin >> ws, AccountNumber);
		cout << "Enter Pin? ";
		getline(cin, PinCode);

		LoadFailed = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoadFailed);
	ShowAtmMainMenueScreen();

}

int main() {

	Login();

	return 0;
}
