
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenueScreen();
void ShowTransactionsMenueScreen();
void ShowManageUsersScreen();
void Login();
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct stUser {

	string Name;
	string Password;
	short Permission = 0;
	bool MarkForDelete = false;

}CurrentUser;
enum enTransactionOptions {
	enDeposit = 1,
	enWithdraw = 2,
	enTotalBalance = 3,
	enBackToMainMenue = 4
};
enum enMainMenuOptions {

	enShowClientList = 1,
	enAddClient = 2,
	enDeleteClient = 3,
	enUpdateClient = 4,
	enFindClient = 5,
	enTransactions = 6,
	enManageUsers = 7,
	LogOut = 8,
	Exit = 9
};
enum enManageUsersOptions {
	eMListUsers = 1,
	eMAddNewUser = 2,
	eMDeleteUser = 3,
	eMUpdateUser = 4,
	eMFindUser = 5,
	eMMainMenue = 6
};
enum enUserPermession {
	enFullAccess = -1,
	enShowClientListP = 1,
	enAddNewClientP = 2,
	enDeleteClientP = 4,
	enUpdateClientP = 8,
	enFindClientP = 16,
	enTransactionsP = 32,
	enManageUsersP = 64
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
stUser ConvertUserLineToRecord(string Line, string Separator = "#//#") {
	vector<string> vUser = SplitString(Line, Separator);
	stUser User;

	User.Name = vUser.at(0);
	User.Password = vUser.at(1);
	User.Permission = stoi(vUser.at(2));

	return User;
}
string ConvertUserRecordToLine(stUser User, string Separator = "#//#") {
	return User.Name + Separator + User.Password + Separator + to_string(User.Permission);
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
vector<stUser> LoadUsersDateFromFile(string FileName) {
	fstream MyFile;
	MyFile.open(UsersFileName, ios::in);
	vector< stUser> vUsers;
	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {

			vUsers.push_back(ConvertUserLineToRecord(Line));
		}
		MyFile.close();
	}
	return vUsers;
}

void AddDataLineToFile(string FileName, string line) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << line << endl;

		MyFile.close();
	}
}
stUser AddUserToFile(string FileName, stUser UserRecord) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		string Line = ConvertUserRecordToLine(UserRecord);
		MyFile << Line << endl;
		MyFile.close();
	}
	return UserRecord;
}

vector<stClient> SaveClientsDataInFile(string FileName, vector<stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stClient C : vClients) {
			if (C.MarkForDelete == false) {

				MyFile << ConvertClientRecordToLine(C) << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector<stUser> SaveDataUsersToFile(string FileName, vector<stUser> vUsers) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		string Line;
		for (stUser U : vUsers) {
			if (U.MarkForDelete == false) {
				Line = ConvertUserRecordToLine(U);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		stClient Client;
		string Line;

		while (getline(MyFile, Line)) {

			Client = ConvertClientLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber) {

				MyFile.close();

				return true;

			}
		}
		MyFile.close();
	}

	return false;
}
bool isExistUserByUserName(string UserName) {
	vector<stUser> Users = LoadUsersDateFromFile(UsersFileName);
	for (stUser User : Users) {
		if (User.Name == UserName) {
			return true;
		}
	}
	return false;
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
bool FindUserByUserName(string UserName, stUser& User, vector<stUser> vUsers) {

	for (stUser U : vUsers) {
		if (U.Name == UserName) {
			User = U;
			return true;
		}
	}
	return false;
}
bool FindUserByUsernameAndPassword(string UserName, string Password, stUser& CurrentUser) {
	vector<stUser> vUsers = LoadUsersDateFromFile(UsersFileName);

	for (stUser U : vUsers) {
		if (U.Name == UserName && U.Password == U.Password) {
			CurrentUser = U;
			return true;
		}
	}
	return false;

}
bool FindUserByUsernameAndPassword(stUser User, stUser& CurrentUser) {
	return FindUserByUsernameAndPassword(User.Name, User.Password, CurrentUser);
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
bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUsers) {

	for (stUser& U : vUsers) {

		if (U.Name == UserName && UserName != "Admin") {
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

string ReadClientAccountNumber() {
	string AccountNumber = "";
	cout << "Please enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
string ReadUserName() {
	string UserName;
	cout << "Please Enter User Name ? ";
	getline(cin >> ws, UserName);
	return UserName;
}
string ReadPassword() {
	string Password;
	cout << "Enter Password ? ";
	getline(cin >> ws, Password);
	return Password;
}
stUser ReadUserNameAndPassword() {
	stUser User;
	User.Name = ReadUserName();
	User.Password = ReadPassword();
	return User;
}
short ReadPermessionsToSet() {

	char Answer = 'n';
	short Permissions = 0;

	cout << "\n\nDo you want to give full access? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		return -1;
	}

	cout << "\nDo you want to give access to : \n";
	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enShowClientListP;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enAddNewClientP;
	}
	cout << "\nDelete Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enDeleteClientP;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enUpdateClientP;
	}
	cout << "\nFind Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enFindClientP;
	}
	cout << "\nTransactions? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enTransactionsP;
	}
	cout << "\nManage Users? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		Permissions |= enUserPermession::enManageUsersP;
	}



	return Permissions;

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
void PrintClientCard(stClient Client) {

	cout << "\nThe following is the extracted client record :\n";
	cout << "\nAccount Number : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << endl;
}
void PrintClientBalanceListLine(stClient Client) {

	cout << "| " << left << setw(16) << Client.AccountNumber;
	cout << "| " << left << setw(38) << Client.Name;
	cout << "| " << left << setw(38) << Client.AccountBalance;


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
void PrintUserCard(stUser User) {
	cout << "\nThe following are the user details : ";
	cout << "\n------------------------------------------";
	cout << "\nUser Name   : " << User.Name;
	cout << "\nPassword    : " << User.Password;
	cout << "\nPermessions : " << User.Permission;
	cout << "\n------------------------------------------\n";
}
bool IsThisUserIsAdmin(string UserName) {
	return UserName == "Admin";
}
bool DeletedUserInFileAndGetNewUsers(string UserName, vector<stUser>& vUsers) {

	char Answer = 'n';
	cout << "\nAre you sure you want to delete this User ? y/n? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {
		MarkUserForDeleteByUserName(UserName, vUsers);
		SaveDataUsersToFile(UsersFileName, vUsers);
		vUsers = LoadUsersDateFromFile(UsersFileName);
		return true;
	}
	else {
		return false;
	}

}
bool ChangeUserInUsers(stUser User, vector<stUser>& vUsers) {
	User.Password = ReadPassword();
	User.Permission = ReadPermessionsToSet();

	for (stUser& U : vUsers) {
		if (User.Name == U.Name) {
			U = User;
			SaveDataUsersToFile(UsersFileName, vUsers);
			return true;
		}
	}
	return false;
}
bool ReadAndUpdateUserInFile(stUser User, vector<stUser> vUsers) {
	char Answer = 'n';

	cout << "\nAre you sure you want to Update this User ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {

		ChangeUserInUsers(User, vUsers);

		cout << "\n\nUser Updated Successfully.\n";
		return true;
	}
	return false;
}
bool IsTherePermessionToLogin(enUserPermession enPermession) {

	if (CurrentUser.Permission == enUserPermession::enFullAccess)
		return true;

	if ((CurrentUser.Permission & enPermession) == enPermession) {
		return true;
	}
	else {
		return false;
	}
}
void PrintAccessDenied() {
	cout << "------------------------------------------------\n";
	cout << "Access Denied,\n";
	cout << "You Don't Have Permessions To Do This,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "------------------------------------------------\n";
}
stUser ReadNewUser() {
	stUser User;

	User.Name = ReadUserName();

	while (isExistUserByUserName(User.Name)) {
		cout << "User With [" << User.Name << "] already exists.Enter another name ? ";
		getline(cin, User.Name);
	}

	User.Password = ReadPassword();
	User.Permission = ReadPermessionsToSet();

	return User;
}
void AddNewUser() {
	stUser User;
	User = ReadNewUser();
	AddUserToFile(UsersFileName, User);
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
void AddNewClient() {
	stClient Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertClientRecordToLine(Client));

}
bool DeleteUserByUserName(string UserName, vector<stUser>& vUsers) {
	stUser User;

	bool IsUserPresent;
	IsUserPresent = FindUserByUserName(UserName, User, vUsers);

	if (IsThisUserIsAdmin(UserName)) {
		cout << "\nYou cannot delete this user.\n";
	}
	else if (IsUserPresent) {
		PrintUserCard(User);
		DeletedUserInFileAndGetNewUsers(UserName, vUsers);
	}
	else {
		cout << "\nUser With User Name [" << UserName << "] Not Found!\n";
	}

	return false;
}
bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers) {
	stUser User;

	if (IsThisUserIsAdmin(UserName)) {
		cout << "\nYou Cannot Update this user! \n";
	}
	else if (FindUserByUserName(UserName, User, vUsers)) {

		PrintUserCard(User);
		ReadAndUpdateUserInFile(User, vUsers);
	}
	else {
		cout << "\nUser With User Name [" << UserName << "] Not Found!\n";
	}
	return false;
}
void AddNewUsers() {
	char AddMore = 'n';

	do {
		cout << "Adding New User : \n\n";
		AddNewUser();
		cout << "\n\nUser Added Successfully. do you want to add more Users? y/n? ";
		cin >> AddMore;
	} while (AddMore == 'y' || AddMore == 'Y');
}
void ShowAllUsers() {

	vector<stUser> vUsers = LoadUsersDateFromFile(UsersFileName);
	cout << "\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n_____________________________________________________________________________________\n\n";
	cout << "| " << left << setw(14) << "User Name";
	cout << "| " << left << setw(12) << "Password";
	cout << "| " << left << setw(6) << "Permissions";
	cout << "\n_____________________________________________________________________________________\n\n";

	if (vUsers.size() == 0) {
		cout << "\n\t\t\tNo Users available in system \n";
	}
	else {
		for (stUser User : vUsers) {
			cout << "| " << left << setw(14) << User.Name;
			cout << "| " << left << setw(12) << User.Password;
			cout << "| " << left << setw(6) << User.Permission << "\n";
		}
	}
	cout << "\n_____________________________________________________________________________________\n";
}

void GoBackToMainMenue() {
	cout << "\n\n\n\n";
	cout << "Press any key to go back to Main Menue... ";
	system("pause>0");
	ShowMainMenueScreen();
}
void GoBackToTransactionsMenue() {
	cout << "\n\n\n\n";
	cout << "Press any key to go back to Transactions Menue... ";
	system("pause>0");
	ShowTransactionsMenueScreen();
}
void GoBackToManageUsersScreen() {
	cout << "\n\n\n\n";
	cout << "Press any key to back to Transactions Menue...";
	system("pause>0");
	ShowManageUsersScreen();
}

void ShowBalanceWithdrawClientScreen() {
	cout << "\n------------------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;
	int Amount = 0;

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "\nClient with [" << AccountNumber << "] not exist.\n\n";
		cout << "Please enter Account Number ? ";
		getline(cin, AccountNumber);
	}

	PrintClientCard(Client);

	cout << "\nPlease enter Withdraw amount ? ";
	cin >> Amount;

	while (Client.AccountBalance < Amount) {
		cout << "Amount Exceeds the balance, you can withdraw up to  : " << Client.AccountBalance << "\n";
		cout << "\nPlease enter Withdraw amount ? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, -1 * Amount, vClients);
}
void ShowBalanceDepositClientsScreen() {

	cout << "\n------------------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n------------------------------------------\n";

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;
	int Amount = 0;

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "\nClient with [" << AccountNumber << "] not exist.\n\n";
		cout << "Please enter Account Number ? ";
		getline(cin, AccountNumber);
	}
	PrintClientCard(Client);
	cout << "\nPlease enter deposit amount ? ";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}
void ShowClientsTotalBalancesScreen() {
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)\n";
	cout << "\n--------------------------------------------------------------------------------------------------------\n\n";
	cout << left << setw(18) << "| Account Number";
	cout << left << setw(40) << "| Client Name";
	cout << left << setw(40) << "| Balance";
	cout << "\n\n--------------------------------------------------------------------------------------------------------\n\n";
	int Total = 0;
	for (stClient C : vClients) {
		PrintClientBalanceListLine(C);
		Total += C.AccountBalance;
		cout << "\n";
	}
	cout << "\n\n--------------------------------------------------------------------------------------------------------\n";
	cout << "\n\t\t\t\t\t  Total Balances = " << Total;
}

void ShowAddNewClientsScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enAddNewClientP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}

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
void ShowAllClientsScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enShowClientListP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}

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
void ShowDeleteClientScreen() {


	if (!IsTherePermessionToLogin(enUserPermession::enDeleteClientP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n___________________________________\n\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateClientScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enUpdateClientP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}


	cout << "\n----------------------------------------\n";
	cout << "\t Update Client Info Screen";
	cout << "\n________________________________________\n\n";
	string AccountNumber = ReadClientAccountNumber();
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	UpdateClientDataByAccountNumber(AccountNumber, vClients);
	;
}
bool ShowFindClientScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enFindClientP)) {

		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}


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
void ShowFindUserScreen() {
	cout << "-----------------------------------\n";
	cout << "\tFind User Screen \n";
	cout << "-----------------------------------\n\n";
	string UserName = ReadUserName();
	stUser User;
	vector<stUser> vUsers = LoadUsersDateFromFile(UsersFileName);
	if (FindUserByUserName(UserName, User, vUsers)) {
		PrintUserCard(User);
	}
	else {
		cout << "\nUser With User Name [" << UserName << "] Not found !\n";
	}
}
void ShowUpdateUserScreen() {

	cout << "-----------------------------------------\n";
	cout << "\tUpdate User Screen \n";
	cout << "-----------------------------------------\n";
	vector<stUser> vUsers = LoadUsersDateFromFile(UsersFileName);
	string UserName = ReadUserName();
	UpdateUserByUserName(UserName, vUsers);

}
void ShowDeleteUserScreen() {
	cout << "-------------------------------------\n";
	cout << "\tDelete Users Screen \n";
	cout << "-------------------------------------\n";
	vector<stUser> vUsers = LoadUsersDateFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUserName(UserName, vUsers);

}
void ShowAddNewUserScreen() {

	cout << "--------------------------------------------\n";
	cout << "\t\tAdd New User Screen\n";
	cout << "--------------------------------------------\n";
	AddNewUsers();

}
void ShowUsersListScreen() {
	ShowAllUsers();
}

short ReadManageUserOption() {
	short Option;
	cout << "Choose what do you want to do? [1 to 6]?";
	cin >> Option;
	return Option;
}
short ReadMainMenuOption() {
	short UserChoice;
	cout << "Choose what do you want to do? [1 to 9]? ";
	cin >> UserChoice;
	return UserChoice;
}
short ReadTransactionOption() {
	short userChoice = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> userChoice;
	return userChoice;
}
void ShowEndScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tProgram end :-)";
	cout << "\n____________________________________\n";
}

void PerformManageUsersOption(enManageUsersOptions Option) {

	switch (Option) {

	case enManageUsersOptions::eMListUsers:
		system("cls");
		ShowUsersListScreen();
		GoBackToManageUsersScreen();
		break;
	case enManageUsersOptions::eMAddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUsersScreen();
		break;
	case enManageUsersOptions::eMDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersScreen();
		break;
	case enManageUsersOptions::eMUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersScreen();
		break;
	case enManageUsersOptions::eMFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUsersScreen();
		break;

	case enManageUsersOptions::eMMainMenue:
		ShowMainMenueScreen();
		break;

	}

}
void PerformTransactionOption(enTransactionOptions UserChoice) {
	switch (UserChoice) {

	case enTransactionOptions::enDeposit:
		system("cls");
		ShowBalanceDepositClientsScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionOptions::enWithdraw:
		system("cls");
		ShowBalanceWithdrawClientScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionOptions::enTotalBalance:
		system("cls");
		ShowClientsTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionOptions::enBackToMainMenue:
		ShowMainMenueScreen();
		break;

	default:
		ShowMainMenueScreen();

	}
}
void PerformMainMenueOptionWithPermessions(enMainMenuOptions UserChoice) {

	switch (UserChoice) {

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
	case enMainMenuOptions::enTransactions:
		system("cls");
		ShowTransactionsMenueScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::enManageUsers:
		system("cls");
		ShowManageUsersScreen();
		GoBackToMainMenue();
		break;
	case enMainMenuOptions::LogOut:
		system("cls");
		Login();
		break;
	case enMainMenuOptions::Exit:
		system("cls");
		ShowEndScreen();
		break;
	default:
		system("cls");
		ShowEndScreen();
		break;


	}

}

void ShowManageUsersScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enManageUsersP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tManage Users Menue Screen \n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Manue\n";
	cout << "===========================================\n";
	PerformManageUsersOption((enManageUsersOptions)ReadManageUserOption());
}
void ShowTransactionsMenueScreen() {

	if (!IsTherePermessionToLogin(enUserPermession::enTransactionsP)) {
		PrintAccessDenied();
		GoBackToMainMenue();
		return;
	}

	system("cls");
	cout << "====================================================\n";
	cout << "\t\t\Transactions Menue Screen \n";
	cout << "====================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "====================================================\n";

	PerformTransactionOption((enTransactionOptions)ReadTransactionOption());
}
void ShowMainMenueScreen() {
	system("cls");
	cout << "================================================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "\t[9] Exit.\n";
	cout << "================================================\n";
	PerformMainMenueOptionWithPermessions((enMainMenuOptions)ReadMainMenuOption());



}

bool LoadUserInfo(stUser User) {

	return FindUserByUsernameAndPassword(User, CurrentUser) ? true : false;

}
void Login() {
	stUser User;
	bool LoadFailed = false;
	do {

		system("cls");
		cout << "------------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "------------------------------------\n";
		if (LoadFailed) {
			cout << "Invalid UserName/Password!\n";
		}

		User = ReadUserNameAndPassword();
		LoadFailed = !LoadUserInfo(User);


	} while (LoadFailed);

	ShowMainMenueScreen();

}

int main() {
	Login();
	system("pause>0");

	return 0;
}