#include"Global.h"
#include"ConsoleScreen.h"
#include"Student.h"
#include"Teacher.h"
#include"Login.h"
const string userDataPath = "./Data/Account/User.csv";
ListUser listuser;
 string id, pass;
 int yPos = 13;

void getlistuser() {
	ifstream fin;
	fin.open(userDataPath, ios_base::in);
	string temp;
	getline(fin, temp);
	initUser(listuser);
	while (!fin.eof()) {
		addUser(listuser, convertUserData(fin));
	}
	fin.close();
}
User* login(string id, string pass) {
	User* tmp = listuser.pHead;
	while (tmp != NULL) {
		if (tmp->ID == id) {
			if (tmp->password == pass) return tmp;
			else return NULL;
		}
		else tmp = tmp->next;;
	}
	return NULL;
}

