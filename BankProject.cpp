#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;


const string cstFileName = "ClientsData.txt";
const string UsersFileName = "UsersData.txt";


enum Menus { ShowClientList = 1, AddNowClient = 2, Deleteclient = 3, UpdateClient = 4, Findclient = 5, Transactions = 6, ManageUsers = 7, Logout = 8 };
enum TransaCtions { Deposit = 1, Withdraw = 2, TotalBalance = 3 };
enum enManageUsers { showuserslist = 1, addnewuser = 2, deleteuser = 3, updateuser = 4, finduser = 5 };


struct ClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Number;
	float AccountBalance = 0;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector <string> vWordsInString;
	string Word;
	int pos = 0;
	while ((pos = S1.find(Delim)) != std::string::npos) {
		Word = S1.substr(0, pos);
		if (Word != "") {
			vWordsInString.push_back(Word);
		}
		S1 = S1.erase(0, pos + Delim.length());
	}
	if (S1 != "") {
		vWordsInString.push_back(S1);
	}
	return vWordsInString;
}

bool FindClientInFile(string FileName, string AccountNumber);

ClientData ReadClientInfo() {
	ClientData Client;
	cout << "Please enter Client data: \n";
	cout << "\nAccount Number : ";
	getline(cin >> ws, Client.AccountNumber);
	while (FindClientInFile(cstFileName, Client.AccountNumber)) {
		cout << "The client with the account Number " << Client.AccountNumber << " is aleady exist. Please tray another one\n";
		getline(cin, Client.AccountNumber);
	}
	cout << "\nAccount PinCode : ";
	getline(cin, Client.PinCode);
	cout << "\nClient Name     : ";
	getline(cin, Client.Name);
	cout << "\nClient Number   : ";
	getline(cin, Client.Number);
	cout << "\nAccount Balance : ";
	cin >> Client.AccountBalance;
	return Client;
}

string ConvertDataToRecord(ClientData Client, string Seperator) {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Number + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

ClientData ConvertRecordToData(string stClientRecord, string Seperator) {
	vector <string> vData = SplitString(stClientRecord, Seperator);
	ClientData Client;
	Client.AccountNumber = vData[0];
	Client.PinCode = vData[1];
	Client.Name = vData[2];
	Client.Number = vData[3];
	Client.AccountBalance = stof(vData[4]);
	return Client;
}

void AddDataToFile(string FileName, string stDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

void AddNewClient() {
	ClientData Client = ReadClientInfo();
	AddDataToFile(cstFileName, ConvertDataToRecord(Client, "#//#"));
}

void AddClientsToFile() {
	bool AddMore = false;

	do {
		system("cls");
		AddNewClient();
		cout << "Client Added succufelly to File. Do you want to add More (1/0): \n";
		cin >> AddMore;
	} while (AddMore);
}

vector <ClientData> FileDataToVector(string FileName) {
	fstream ClientsFile;
	vector <ClientData> vClientsData;
	ClientsFile.open(FileName, ios::in);
	if (ClientsFile.is_open()) {
		string Line;
		while (getline(ClientsFile, Line)) {
			vClientsData.push_back(ConvertRecordToData(Line, "#//#"));
		}
		ClientsFile.close();
	}
	return vClientsData;
}

void PrintClientRecord(ClientData Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Number;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientBalance(ClientData Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <ClientData> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (ClientData Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintAllClientsBalances(vector <ClientData> vClients)
{
	double AllBalances = 0;
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (ClientData Client : vClients)
	{
		PrintClientBalance(Client);
		cout << endl;
		AllBalances += Client.AccountBalance;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\n\n\t\t\t\t Total balances is: " << AllBalances << endl;
}

void PrintClientCard(ClientData Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Number;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

bool FindClientInFile(string FileName, string AccountNumber, ClientData& sClient) {
	vector <ClientData> vClientsdata = FileDataToVector(FileName);
	for (ClientData& s : vClientsdata) {
		if (s.AccountNumber == AccountNumber)
		{
			sClient = s;
			return true;
		}
	}
	return false;
}

bool FindClientInFile(string FileName, string AccountNumber) {
	vector <ClientData> vClientsdata = FileDataToVector(FileName);
	for (ClientData& s : vClientsdata) {
		if (s.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;
}

void AddClientsToFile(vector<ClientData> vClient) {
	fstream ClientsDataFile;
	ClientsDataFile.open(cstFileName, ios::out);
	if (ClientsDataFile.is_open()) {
		for (ClientData& c : vClient) {
			if (c.MarkForDelete == false) {
				ClientsDataFile << ConvertDataToRecord(c, "#//#") << endl;
			}
		}
	}
}

string ReadAccountNumber() {
	string AccountNum;
	do
	{
		cout << "\nPlease enter the client account Number \n";
		cin >> AccountNum;
	} while (AccountNum == "");
	return AccountNum;
}

bool MarkClientToDelete(string AccountNumber, vector <ClientData>& vClients) {
	for (ClientData& c : vClients) {
		if (c.AccountNumber == AccountNumber) {
			c.MarkForDelete = true;
			return 0;
		}
	}
	return 1;
}

bool DeleteClient(vector <ClientData>& vClients) {
	char Answer;
	ClientData Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientInFile(cstFileName, AccountNumber, Client)) {
		PrintClientCard(Client);
		cout << "\nAre You sure you want to Delete This client Data (Y/N) ? " << endl;
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			MarkClientToDelete(AccountNumber, vClients);
			AddClientsToFile(vClients);
			vClients = FileDataToVector(cstFileName);
			cout << "Client was Deletes succesfully.\n";
			return true;
		}
	}
	return 0;
}

bool UpdateClientsRecordFromFile(vector <ClientData>& vClients) {
	string AccountNumber = ReadAccountNumber();
	char Answer;
	ClientData Client;
	if (FindClientInFile(cstFileName, AccountNumber, Client)) {
		PrintClientCard(Client);
		cout << "\nAre You sure you want to Update This client Data (Y/N) ? " << endl;
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			for (ClientData& c : vClients) {
				if (c.AccountNumber == AccountNumber) {
					c = ReadClientInfo();
					c.AccountNumber = AccountNumber;
					break;
				}
			}
			AddClientsToFile(vClients);
			cout << "Client was Updated succesfully.\n";
			return true;
		}
	}
	else
		cout << "Client wasn't found.\n";
}



void ShowDeleteScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "        Delete screen       \n";
	cout << "===========================================\n";
	vector <ClientData> vClients = FileDataToVector(cstFileName);
	DeleteClient(vClients);

}

void ShowUpdateScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "        Update screen       \n";
	cout << "===========================================\n";
	vector <ClientData> vClients = FileDataToVector(cstFileName);
	UpdateClientsRecordFromFile(vClients);

}

void ShowFindClientScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Find Client screen       \n";
	cout << "===========================================\n";
	ClientData c;
	vector <ClientData> vClients = FileDataToVector(cstFileName);
	if (FindClientInFile(cstFileName, ReadAccountNumber(), c)) {
		cout << "The user Exist. \n";
		PrintClientCard(c);
	}
	else
		cout << "The user dosn't Exist. \n";

}

void ShowClientsBalances() {
	system("cls");
	vector <ClientData> vClients = FileDataToVector(cstFileName);
	PrintAllClientsBalances(vClients);
}

void ShowClientsData() {
	system("cls");
	vector <ClientData> vClients = FileDataToVector(cstFileName);
	PrintAllClientsData(vClients);
}


void ShowAddNewClients() {
	system("cls");
	cout << "===========================================\n";
	cout << "        New Client screen       \n";
	cout << "===========================================\n";
	AddClientsToFile();
}

short ReadUserChoise() {
	short N;
	cout << "\nPlease enter your choise: \n";
	cin >> N;
	return N;
}

void DepositTransaction()
{
	ClientData sClient;
	vector <ClientData> vClientsData = FileDataToVector(cstFileName);
	string AccNum = ReadAccountNumber();
	while (!FindClientInFile(cstFileName, AccNum, sClient)) {
		cout << "\nThe user dosn't exist.\n";
		AccNum = ReadAccountNumber();
	}
	PrintClientCard(sClient);
	double N;
	char Answer;
	cout << "\nEnter The Deposit Amount: ";
	cin >> N;
	cout << "Confirm (Y/N) : ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		for (ClientData& s : vClientsData)
		{
			if (s.AccountNumber == AccNum) {
				s.AccountBalance += N;
			}
		}
	}
	AddClientsToFile(vClientsData);
}


void DepositScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "        Deposit screen       \n";
	cout << "===========================================\n";

	DepositTransaction();
}

void WithdrawTransaction()
{
	ClientData sClient;
	vector <ClientData> vClientsData = FileDataToVector(cstFileName);
	string AccNum = ReadAccountNumber();
	while (!FindClientInFile(cstFileName, AccNum, sClient)) {
		cout << "\nThe user dosn't exist.\n";
		AccNum = ReadAccountNumber();
	}
	PrintClientCard(sClient);
	double N;
	char Answer;
	cout << "\nEnter The Withdraw Amount: ";
	cin >> N;
	cout << "Confirm (Y/N) : ";
	cin >> Answer;
	if (toupper(Answer) == 'Y') {
		for (ClientData& s : vClientsData)
		{
			if (s.AccountNumber == AccNum) {
				while (s.AccountBalance < N) {
					cout << "\nYou can't withdraw that amount, try another amount : ";
					cin >> N;
				}
				s.AccountBalance -= N;
			}
		}
	}
	AddClientsToFile(vClientsData);
}

void WithDrawScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "        Withdraw screen       \n";
	cout << "===========================================\n";
	WithdrawTransaction();
}





struct stUserData
{
	string UserName;
	string Password;
	int Permissions = 0;
	bool MarkToDelete = 0;
	bool MarkToUpdate = 0;
};

void PerfomeTransactionsMenuScreen(stUserData User, TransaCtions N);
void MainMenueScreen(stUserData User);
void PerfomeMainMenuScreen(stUserData User, Menus N);
void PerformeManageUsersScreen(stUserData User, enManageUsers N);
void LoginScreen();
void ManageUsersScreen(stUserData User);

short showclientList = 1;
short Addnewclient = 2;
short deleteclient = 4;
short updateclient = 8;
short findclinet = 16;
short transactions = 32;
short manageUsers = 64;

string ReadUserName(string message) {
	cin.ignore();
	string username;
	do
	{
		cout << message;
		getline(cin, username);
	} while (username == "");
	return username;
}

stUserData ReadUserPermissions(stUserData user) {
	user.Permissions = 0;
	char choise;
	cout << "\nDo you want to give full acces to user? (y/n): ";
	cin >> choise;
	if (toupper( choise) == 'Y') {
		user.Permissions = -1;
		return user;
	}
	cout << "Do you want to give permission for: \n";
	cout << "Show client list? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | showclientList;
	}

	cout << "Add new client? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | Addnewclient;
	}

	cout << "Delete client? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | deleteclient;
	}

	cout << "Upadte client list? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | updateclient;
	}

	cout << "Find client? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | findclinet;
	}

	cout << "Transactions? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | transactions;
	}

	cout << "Manage users? : ";
	cin >> choise;
	if (toupper(choise) == 'Y') {
		user.Permissions = user.Permissions | manageUsers;
	}
	return user;
}

bool CheckIfUserHavePermissionTo(stUserData User,short N) {
	if (User.Permissions == -1) {
		return true;
	}
	else if ((User.Permissions & N) == N) {
		return true;
	}
	else
		return false;
}

stUserData UserRecordToData(string Line) {
	stUserData user;
	vector<string> Vuser;
	Vuser = SplitString(Line, "#//#");
	user.UserName = Vuser[0];
	user.Password = Vuser[1];
	user.Permissions = stoi(Vuser[2]);
	return user;
}

vector <stUserData> UsersDataFromeFileToVector(string FileName) {
	fstream UsersFile;
	vector <stUserData> Vuserdata;
	UsersFile.open(FileName, ios::in);
	if (UsersFile.is_open()) {
		string Line;
		while (getline(UsersFile, Line))
		{
			Vuserdata.push_back(UserRecordToData(Line));
		}
		UsersFile.close();
	}
	return Vuserdata;
}

void PrintUserRecord(stUserData user)
{
	cout << "| " << setw(15) << left << user.UserName;
	cout << "| " << setw(10) << left << user.Password;
	cout << "| " << setw(10) << left << user.Permissions;
}

void PrintAllUsersData(vector <stUserData> vUsers)
{
	cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ")Client(s).";
	cout << "\n_______________________________________________________" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permission";
	
	cout <<	"\n_______________________________________________________" << endl;
	for (stUserData& c : vUsers)
	{
		PrintUserRecord(c);
		cout << endl;
	}
	cout << "\n_______________________________________________________" << endl;
}


bool FindUser(string UserName, vector<stUserData>& VusersData, stUserData*& sUser) {
	for (stUserData& user:VusersData)
	{
		if (user.UserName == UserName) {
			sUser = &user;
			return 1;
		}
	}
	return 0;
}

bool FindUser(string UserName, vector<stUserData> VusersData) {
	
	for (stUserData& user : VusersData)
	{
		if (user.UserName == UserName) {
			return 1;
		}
	}
	return 0;
}

bool MarkUserForDelete(string username, vector<stUserData>& Vusers) {
	for (stUserData& c : Vusers) {
		if (c.UserName == username) {
			c.MarkToDelete = 1;
			return 1;
		}
	}
	return 0;
}

void PrintUserCard(stUserData User){
	cout << "\nThe following are the User details:\n";
	cout << "\nUsername: " << User.UserName;
	cout << "\nPasswrod : " << User.Password;
	cout << "\nPermissions : " << User.Permissions;
	
}

string UserDataToRecord(stUserData user,string delim = "#//#") {
	string UserRecord;
	UserRecord = user.UserName + delim + user.Password + delim + to_string(user.Permissions);
	return UserRecord;
}

stUserData ReadUserData() {
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	stUserData user;
	cin.ignore();
	cout << "Enter UserName: ";
	getline(cin, user.UserName);
	while (FindUser(user.UserName, vUsers)) {
		cout << "User already exist, enter another username : ";
		getline(cin, user.UserName);
	}
	cout << "Enter Passwrod: ";
	getline(cin, user.Password);
	user = ReadUserPermissions(user);
	return user;
}

void DataFromVectorToFile(string FileName, vector<stUserData> VusersData) {
	fstream UsersFile;
	UsersFile.open(FileName, ios::out);
	if (UsersFile.is_open())
	{
		for (stUserData& c : VusersData) {
			if (c.MarkToDelete == 0)
			{
				UsersFile << UserDataToRecord(c, "#//#") << endl;
			}
		}
		UsersFile.close();
	}
}

void AddNewUser(vector<stUserData> vUsers) {
	char choise;
	do
	{
		cout << "------------------[Add new user]----------------- \n";
		vUsers.push_back(ReadUserData());
		cout << "Do you want to add another user? : ";
		cin >> choise;
	} while (toupper(choise) == 'Y');

	DataFromVectorToFile(UsersFileName, vUsers);
}

void DeleteUser(vector<stUserData> vUsersdata) {
	stUserData *user = nullptr;
	string Username = ReadUserName("Enter user name for delete: ");
	if (FindUser(Username, vUsersdata, user)) {
		char choise;
		PrintUserCard(*user);
		cout << "\nAre you sure you want to delete the user (Y/N): " << user->UserName << endl;
		cin >> choise;
		if (toupper(choise) == 'Y') {
			user->MarkToDelete = 1;
		}
		DataFromVectorToFile(UsersFileName, vUsersdata);
		vUsersdata = UsersDataFromeFileToVector(UsersFileName);
		cout << "User Deleted successfully" << endl;
	}
	else
	{
		cout << "User doesn't exist" << endl;
	}
}

void UpdateUser(vector<stUserData> vUsersdata) {
	stUserData *c = nullptr;

	string Username = ReadUserName("Enter the user's  username for Update: ");
	if (FindUser(Username, vUsersdata, c)) {
		PrintUserCard(*c);
		char choise;

		cout << "\nAre you sure you want to Update the user (Y/N): " << c->UserName << endl;
		cin >> choise;
		if (toupper(choise) == 'Y') {
			cout << "Enter user Password: ";
			cin >> c->Password;
			*c = ReadUserPermissions(*c);
		}
		DataFromVectorToFile(UsersFileName, vUsersdata);
		vUsersdata = UsersDataFromeFileToVector(UsersFileName);
		cout << "User updated successfully" << endl;
	}	
	else {
		cout << "User doesn't exist" << endl;
		}

}

void PerformeUsersListScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Users List screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	PrintAllUsersData(vUsers);
}

void PerformeAddNewUserScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Delete Users screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	AddNewUser(vUsers);
}

void PerformedeleteUsersScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Delete Users screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	DeleteUser(vUsers);
}

void PerformeUpdateUsersScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Update Users screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	UpdateUser(vUsers);
}

void PerformeFindUsersScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "       Find Users screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	stUserData* user = nullptr;
	string UserName = ReadUserName("Enter the user's Username: ");
	if (FindUser(UserName, vUsers, user)) {
		PrintUserCard(*user);
	}
	else
	{
		cout << "User couldn't be found." << endl;
	}
}



void TransactionsMenueScreen(stUserData User) {
	system("cls");
	cout << "===========================================\n";
	cout << "        Transactions screen       \n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Back to main menue.\n";

	cout << "===========================================\n";
	PerfomeTransactionsMenuScreen(User,(TransaCtions)ReadUserChoise());
}
void GoBackToMainMenue(stUserData User) {
	cout << "\n\nPress Any Key to Go Back to main menue...";
	system("pause>0");
	MainMenueScreen(User);
}
void GoBackToTransactionsMenue(stUserData User) {
	cout << "\n\nPress Any Key to Go Back to Transactions menue...";
	system("pause>0");
	TransactionsMenueScreen(User);
}

void PerfomeTransactionsMenuScreen(stUserData User,TransaCtions N) {
	switch (N)
	{
	case Deposit:
		DepositScreen();
		GoBackToTransactionsMenue(User);
		break;
	case Withdraw:
		WithDrawScreen();
		GoBackToTransactionsMenue(User);
		break;
	case TotalBalance:
		ShowClientsBalances();
		GoBackToTransactionsMenue(User);
		break;
	default:
		MainMenueScreen(User);
	}
}

void GoBackToManageUsersScreen(stUserData User) {
	cout << "\n\nPress Any Key to Go Back to manage users menue...";
	system("pause>0");
	ManageUsersScreen(User);
}

void PerformeManageUsersScreen(stUserData User,enManageUsers N) {
	switch (N) {
	case 1 :
		PerformeUsersListScreen();
		GoBackToManageUsersScreen(User);
		break;
	case 2:
		PerformeAddNewUserScreen();
		GoBackToManageUsersScreen(User);
		break;
	case 3:
		PerformedeleteUsersScreen();
		GoBackToManageUsersScreen(User);
		break;
	case 4:
		PerformeUpdateUsersScreen();
		GoBackToManageUsersScreen(User);
		break;
	case 5:
		PerformeFindUsersScreen();
		GoBackToManageUsersScreen(User);
		break;
	default :
		MainMenueScreen(User);
	}
}

void ManageUsersScreen(stUserData User) {
	system("cls");
	cout << "===========================================\n";
	cout << "        Manage users screen       \n";
	cout << "===========================================\n";
	cout << "\t[1] Show Users List.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main menue.\n";
	cout << "===========================================\n";
	PerformeManageUsersScreen(User, (enManageUsers)ReadUserChoise());
}

void CheckTheAdminScreen() {
	system("cls");
	cout << "==========================================\n\n";
	cout << "You apparently don't have Permission\nto do this action.\nPlease check The Admin.";
	cout << "\n========================================\n";
}

void PerfomeMainMenuScreen(stUserData User,Menus N) {

	switch (N)
	{
	case ShowClientList:
		if (CheckIfUserHavePermissionTo(User, showclientList))
		{
			ShowClientsData();
		}
		else
		{
			CheckTheAdminScreen();
		}
		GoBackToMainMenue(User);
		break;
	case AddNowClient:
		if (CheckIfUserHavePermissionTo(User, Addnewclient))
			ShowAddNewClients();
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case Deleteclient:
		if (CheckIfUserHavePermissionTo(User, deleteclient))
			ShowDeleteScreen();
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case UpdateClient:
		if (CheckIfUserHavePermissionTo(User, updateclient))
			ShowUpdateScreen();
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case Findclient:
		if (CheckIfUserHavePermissionTo(User, findclinet))
			ShowFindClientScreen();
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case Transactions:
		if (CheckIfUserHavePermissionTo(User, transactions))
			TransactionsMenueScreen(User);
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case ManageUsers:
		if (CheckIfUserHavePermissionTo(User, manageUsers))
			ManageUsersScreen(User);
		else
			CheckTheAdminScreen();
		GoBackToMainMenue(User);
		break;
	case Logout:
		LoginScreen();
		break;
	default:
		break;
	}
}

void MainMenueScreen(stUserData User) {
	system("cls");
	cout << "===========================================\n";
	cout << "        Menu screen       \n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";
	PerfomeMainMenuScreen(User, (Menus)ReadUserChoise());
}

bool CheckUser(stUserData& User, vector<stUserData> vUsers) {
	stUserData *p = nullptr;

	if (FindUser(User.UserName, vUsers, p)) {
		if (p->Password == User.Password)
		{
			User.Permissions = p->Permissions;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

void LoginScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "        Login screen       \n";
	cout << "===========================================\n";
	vector<stUserData> vUsers = UsersDataFromeFileToVector(UsersFileName);
	stUserData User;
	cout << "\nEnter Username: ";
	cin >> User.UserName;
	cout << "Enter Password: ";
	cin >> User.Password;
	bool UserValid = CheckUser(User, vUsers);
	while (!UserValid)
	{
		system("cls");
		cout << "Username/Password invalid.\n\n";
		cout << "Enter Username: ";
		cin >> User.UserName;
		cout << "Enter Password: ";
		cin >> User.Password;
		UserValid = CheckUser(User, vUsers);
	}
	MainMenueScreen(User);
}

int main() {
	LoginScreen();

	return 0;
}