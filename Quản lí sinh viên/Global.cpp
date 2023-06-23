#include"Global.h"
#include"ConsoleScreen.h"
const string userDataPath = "./Data/Account/User.csv";
const char cursorLeft = char(175);
const char cursorRight = char(174);
int yPos = 13;
ListUser listuser;
ListClasses listClasses;
ListCourse listCourses;
Semester currentSemester;
User* currentUser;
Date currentDate;
string id, pass;
string currentSchoolYear;
string semesterPath;
string schoolYearPath;

// Doi ngay thang
int dayofweek(int d, int m, int y)
{

	return ((d + 2 * m + 3 * (m + 1)) / 5 + y + (y / 4)) % 7;
}
Date strtodate(string str) {
	Date date;
	date.day = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.month = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.year = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	string wDay;
	switch (dayofweek(date.day, date.month, date.year)) {
	case 0:
		wDay = "Sunday";
		break;
	case 1:
		wDay = "Monday";
		break;
	case 2:
		wDay = "Tuesday";
		break;
	case 3:
		wDay = "Wednesday";
		break;
	case 4:
		wDay = "Thursday";
		break;
	case 5:
		wDay = "Friday";
		break;
	case 6:
		wDay = "Saturday";
		break;
	}
	date.dayofweek = wDay;
	return date;
}

string Datetostring(Date a) {
	string date = "";
	if (a.day < 10) date += "0";
	date += to_string(a.day);
	date += "/";
	if (a.month < 10) date += "0";
	date += to_string(a.month) + "/";
	date += to_string(a.year);
	return date;
}

void getCurrentDate() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	string wDay;
	switch (ltm.tm_wday) {
	case 0:
		wDay = "Sun";
		break;
	case 1:
		wDay = "Mon";
		break;
	case 2:
		wDay = "Tue";
		break;
	case 3:
		wDay = "Wed";
		break;
	case 4:
		wDay = "Thu";
		break;
	case 5:
		wDay = "Fri";
		break;
	case 6:
		wDay = "Sat";
		break;
	}
	currentDate.year = 1900 + ltm.tm_year;
	currentDate.month = 1 + ltm.tm_mon;
	currentDate.day = ltm.tm_mday;
	currentDate.dayofweek = wDay;
}

//tao danh sach
void initUser(ListUser& l) {
	l.pHead = l.pTail = NULL;
	l.sz = 0;
}
void initCourse(ListCourse& l) {
	l.pHead = l.pTail = NULL;
	l.size = 0;
	l.start = l.end = strtodate("0/0/0");
}
void initStudent(ListStudent& l) {
	l.pHead = l.pTail = NULL;
	l.size = 0;
}
void initClasses(ListClasses& l) {
	l.pHead = l.pTail = NULL;
	l.size = 0;
}



//them va xoa cac danh sach
void addUser(ListUser& list, User* user) {
	if (user == NULL) return;
	if (list.pHead == NULL) {
		list.pHead = list.pTail = user;
	}
	else {
		list.pTail->next = user;
		user->prev = list.pTail;
		list.pTail = user;
	}
	list.sz++;
}
void addStudent(ListStudent& list, Student* student) {
	if (student == NULL) return;
	if (list.pHead == NULL) {
		list.pHead = list.pTail = student;
	}
	else {
		list.pTail->next = student;
		student->prev = list.pTail;
		list.pTail = student;
	}
	list.size++;
}
void addCourse(ListCourse& list, Course* course) {
		if (course == NULL) return;
	if (list.pHead == NULL) {
		list.pHead = list.pTail = course;
	}
	else {
		list.pTail->next = course;
		course->prev = list.pTail;
		list.pTail = course;
	}
	list.size++;
}
void addClass(ListClasses& list, Class* c) {
	if (c == NULL) return;
		if (list.pHead == NULL) {
			list.pHead = list.pTail = c;
			c->prev = NULL;
		}
		else {
			list.pTail->next = c;
			c->prev = list.pTail;
			list.pTail = c;
		}
		list.size++;
}
void removeStudent(ListStudent& list, Student* student) {
	if (student == list.pHead && student == list.pTail) {
		list.pHead = list.pTail = NULL;
		delete student;
	}
	else if (student == list.pHead) {
		list.pHead = list.pHead->next;
		list.pHead->prev = NULL;
		delete student;
	}
	else if (student == list.pTail) {
		list.pTail = list.pTail->prev;
		list.pTail->next = NULL;
		delete student;
	}
	else {
		student->prev->next = student->next;
		student->next->prev = student->prev;
		delete student;
	}
	list.size--;
}
void removeCourse(ListCourse& list, Course* course) {
	if (course == list.pHead && course == list.pTail) {
		list.pHead = list.pTail = NULL;
		delete course;
	}
	else if (course == list.pHead) {
		list.pHead = list.pHead->next;
		list.pHead->prev = NULL;
		delete course;
	}
	else if (course == list.pTail) {
		list.pTail = list.pTail->prev;
		list.pTail->next = NULL;
		delete course;
	}
	else {
		course->prev->next = course->next;
		course->next->prev = course->prev;
		delete course;
	}
	list.size--;
}
User* toUser(Student* student, string className) {
	User* user = new User;
	user->ID = student->studentID;
	user->password = student->socialID;
	user->lastname = student->lastName;
	user->firstname = student->firstName;
	user->classname = className;
	user->gender = student->gender;
	user->brithday = student->dateOfBirth;
	user->academicyear = student->academicYear;
	user->isteacher = false;
	user->prev = NULL;
	user->next = NULL;
	return user;
}
//void addStudentAccount(ListStudent listStudent) {
//	Student* temp = listStudent.pHead;
//	while (temp != NULL) {
//		addUser(listuser, toUser(temp, listStudent.className));
//		temp = temp->next;
//	}
//	saveListUser();
//}

//doc danh sách
User* convertUserData(ifstream& data) {
	User* Data = new User;
	Date dateOfBirth;
	string temp;
	getline(data, Data->ID,',');
	if (Data->ID == "") return NULL;
	getline(data, Data->password, ',');
	getline(data, Data->lastname, ',');
	getline(data, Data->firstname, ',');
	getline(data, Data->classname, ',');
	getline(data, Data->gender, ',');
	getline(data, temp, ',');
	Data->brithday = strtodate(temp);
	getline(data, temp, ',');
	Data->academicyear = stoi(temp);
	getline(data, temp , '\n');
	if (temp == "TRUE") {
		Data->isteacher = true;
	}
	else Data->isteacher = false;
	Data->next = NULL;
	Data->prev = NULL;
	return Data;
}
Student* convertStudentData(ifstream& data) {
	Student* newStudent = new Student;
	string s, dateOfBirth;
	getline(data, s, ',');
	if (s == "") return NULL;
	getline(data, newStudent->studentID, ',');
	getline(data, newStudent->lastName, ',');
	getline(data, newStudent->firstName, ',');
	getline(data, newStudent->gender, ',');
	getline(data, dateOfBirth, ',');
	newStudent->dateOfBirth = strtodate(dateOfBirth);
	getline(data, newStudent->socialID, '\n');
	newStudent->next = NULL;
	newStudent->prev = NULL;
	return newStudent;
}
Course* convertCourseData(ifstream& data) {
	Course* course = new Course;
	string credits;
	getline(data, course->ID, ',');
	if (course->ID == "") return NULL;
	getline(data, course->coursename, ',');
	getline(data, course->teachername, ',');
	getline(data, credits, ',');
	course->credits = stoi(credits);
	getline(data, course->classname, ',');
	getline(data, course->dayofweek, ',');
	getline(data, course->session, ',');
	initStudent(course->l);
	course->prev = NULL;
	course->next = NULL;
	return course;
}

void saveListUser() {
	ofstream fout(userDataPath);
	fout << "ID,Password,Last name,First name,Class,Gender,Date of Birth,Academic year,Staff" << endl;
	User* curr = listuser.pHead;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->brithday.day) + "/" + to_string(curr->brithday.month) + "/" + to_string(curr->brithday.year);
		fout << curr->ID<< "," << curr->password << "," << curr->lastname << "," << curr->firstname
			<< "," << curr->classname << "," << curr->gender << "," << dateOfBirth << "," << to_string(curr->academicyear) << ",";
		if (curr->isteacher) fout << "TRUE";
		else fout << "FALSE";
		curr = curr->next;
		if (curr != NULL) fout << endl;
	}
	fout.close();
}


void getListCourses() {
	ifstream fin(semesterPath + "/courses.csv");
	initCourse(listCourses);
	if (!fin) return;
	string s;
	getline(fin, s);
	while (!fin.eof()) {
		addCourse(listCourses, convertCourseData(fin));
	}
	Course* tmp = listCourses.pHead;
	while (tmp != NULL) {
		string a = semesterPath + "/Courses/" + tmp->ID + ".csv";
		ifstream in(a);
		getline(in, s);
		while (!in.eof()) {
			addStudent(tmp->l, convertStudentData(in));
		}
	}
}
void getListClasses() {
	initClasses(listClasses);
	string path = "./Data/Classes.csv";
	ifstream in(path);
	while (!in.eof()) {
		string a = "";
		getline(in, a);
		Class* tm = new Class;
		tm->ClassName = a;
		tm->next = NULL;
		tm->prev = NULL;
	}
	in.close();
}




//Dang nhap
void getlistuser() {
	ifstream fin;
	fin.open(userDataPath, ios::in);
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
void logout() {
	currentUser == NULL;
}
//Giao vu
void getInfomationUser() {
	if (currentUser->isteacher) {
		cout << "\nFirst name: " << currentUser->firstname;
		cout << "\nLast name: " << currentUser->lastname;
		cout << "\nGender: " << currentUser->gender;
		cout << "\nStaff ID: " << currentUser->ID;
		cout << "\nDate of birth: " << Datetostring(currentUser->brithday);
	}
	else {
		cout << "\nFirst name: " << currentUser->firstname;
		cout << "\nLast name: " << currentUser->lastname;
		cout << "\nGender: " << currentUser->gender;
		cout << "\nStudent ID: " << currentUser->ID;
		cout << "\nClass: " << currentUser->lastname;
		cout << "\nDate of birth: " << Datetostring(currentUser->brithday);
	}
}
void createSchoolYear() {
	getCurrentDate();
	if (currentDate.month < 9) {
		currentSchoolYear = to_string(currentDate.year - 1) + "-" + to_string(currentDate.year);
	}
	else {
		currentSchoolYear = to_string(currentDate.year) + "-" + to_string(currentDate.year + 1);
	}
	
}

void create_folder_SchoolYear() {
	createSchoolYear();
	string s = "./Data/" + currentSchoolYear;
	int a=_mkdir(s.c_str());
}
void createClasses(string className) {
	string b = "./Data/Classes.csv";
	ofstream ou(b);

	string a = "./Data/Classes/" + className + ".csv";
	ofstream out(a);
	out.close();
	Class* c = new Class;
	c->ClassName = className;
	c->next = NULL;
	c->prev = NULL;
	addClass(listClasses, c);
	Class* tmp = listClasses.pHead;
	while (tmp != NULL) {
		ou << tmp->ClassName << endl;
		tmp = tmp->next;
	}
}
Student* InputStudent() {
	Student *a = new Student;
	cout << "\nLast name: ";
	getline(cin, a->lastName);
	cout << "\nFirst name: ";
	getline(cin, a->firstName);
	cout << "\nStudent ID: ";
	getline(cin, a->studentID);
	cout << "\nSocial ID: ";
	getline(cin, a->socialID);
	cout << "\nGender: ";
	getline(cin, a->gender);
	cout << "\nBirthday: ";
	string date = "";
	getline(cin, date);
	a->dateOfBirth = strtodate(date);
	a->next = NULL;
	a->prev = NULL;
	
	return a;
}
void Copyfile(string a, string b) {
	char c;
	ifstream in(a);
	ofstream out(b);
	while (in.get(c)) {
		out << c;
	}
	in.close();
	out.close();
}
void writestudent(ListStudent& list,string className) {
	string a = "./Data/Classes/" + className + ".csv";
	ofstream out(a,ios::out);
	if (!out.is_open()) return;
	list.className = className;
	Student* tmp = list.pHead;
	int stt = 1;
	out << "No,Student ID,Last name,First name,Gender,Date of Birth,Social ID" << endl;
	while (tmp != NULL) {
		out << stt << ",";
		stt++;
		out << tmp->studentID << ",";
		out << tmp->lastName << ",";
		out << tmp->firstName << ",";
		out << tmp->gender << ",";
		string date = Datetostring(tmp->dateOfBirth);
		out << date << ",";
		out << tmp->socialID;
		out << endl;
		tmp = tmp->next;
	}
	out.close();

}
void create_semester(int a) {
	createSchoolYear();
	
	semesterPath = "./Data/" + currentSchoolYear + "/Semester " + to_string(a);
	int b=_mkdir(semesterPath.c_str());
}
void create_folder_course() {
	string course = semesterPath + "/Courses";
	int a = _mkdir(course.c_str());
}
Course* Inputcourse() {
	Course* c = new Course;
	cout << "\nCourse Name: ";
	getline(cin, c->coursename);
	cout << "\nCredit: ";
	cin >> c->credits;
	cin.ignore();
	cout << "\nCourse ID: ";
	getline(cin, c->ID);
	cout << "\nClass Name: ";
	getline(cin, c->classname);
	cout << "Teacher Name: ";
	getline(cin, c->teachername);
	cout << "\nDay of week: ";
	getline(cin, c->dayofweek);
	cout << "\nSession: ";
	getline(cin, c->session);
	c->next = NULL;
	c->prev = NULL;
	return c;
}
void write_course(ListCourse l) {
	string course = semesterPath + "/Course.csv";
	ofstream out(course, ios::out);
	out << "ID,Course Name,Teacher Name,Credits,Class Name,Day of week,Session" << endl;
	Course* tmp = l.pHead;
	while (tmp != NULL) {
		out << tmp->ID << ",";
		out << tmp->coursename << ",";
		out << tmp->teachername << ",";
		out << tmp->credits << ",";
		out << tmp->classname << ",";
		out << tmp->dayofweek << ",";
		out << tmp->session << endl;
		tmp = tmp->next;
	}
	out.close();
	delete tmp;
}
void List_Courses(ListCourse l) {
	Course* tmp = l.pHead;
	
	while (tmp != NULL) {
		string a = semesterPath + "/Courses/" + tmp->ID + ".csv";
		ofstream out(a, ios::out);
		out.close();
		tmp = tmp->next;
	}
}
void Display_Course(ListCourse l) {
	Course* tmp = l.pHead;
	
	while (tmp != NULL) {
		cout << tmp->coursename << "\t" << tmp->classname;
		tmp = tmp->next;
	}
}
void add_student_to_course(Student *a,string CourseId) {
	Course* tmp = listCourses.pHead;
	while (tmp != NULL) {
		if (tmp->ID == CourseId) {
			break;
		}
		tmp = tmp->next;
	}
	
	string name = semesterPath + "/Courses/" + CourseId + ".csv";
	ifstream fin;
	fin.open(name, ios::in);
	string temp;
	getline(fin, temp);
	initStudent(tmp->l);
	while (!fin.eof()) {
		addStudent(tmp->l, convertStudentData(fin));
	}
	fin.close();
	addStudent(tmp->l, a);
	
	ofstream out(name, ios::out);
	if (!out.is_open()) return;
	
	Student* tmp1 = tmp->l.pHead;
	int stt = 1;
	out << "No,Student ID,Last name,First name,Gender,Date of Birth,Social ID" << endl;
	while (tmp1 != NULL) {
		out << stt << ",";
		stt++;
		out << tmp1->studentID << ",";
		out << tmp1->lastName << ",";
		out << tmp1->firstName << ",";
		out << tmp1->gender << ",";
		string date = Datetostring(tmp1->dateOfBirth);
		out << date << ",";
		out << tmp1->socialID;
		out << endl;
		tmp1 = tmp1->next;
	}
	out.close();
}
void remove_student_from_course(string id, string CourseId) {
	Course* tmp = listCourses.pHead;
	while (tmp != NULL) {
		if (tmp->ID == CourseId) {
			break;
		}
		tmp = tmp->next;
	}

	string name = semesterPath + "/Courses/" + CourseId + ".csv";
	ifstream fin;
	fin.open(name, ios::in);
	string temp;
	getline(fin, temp);
	initStudent(tmp->l);
	while (!fin.eof()) {
		addStudent(tmp->l, convertStudentData(fin));
	}
	fin.close();
	Student* tm = tmp->l.pHead;
	while (tm != NULL) {
		if (tm->studentID == id) break;
		tm = tm->next;
	}
	removeStudent(tmp->l, tm);

	ofstream out(name, ios::out);
	if (!out.is_open()) return;

	Student* tmp1 = tmp->l.pHead;
	int stt = 1;
	out << "No,Student ID,Last name,First name,Gender,Date of Birth,Social ID" << endl;
	while (tmp1 != NULL) {
		out << stt << ",";
		stt++;
		out << tmp1->studentID << ",";
		out << tmp1->lastName << ",";
		out << tmp1->firstName << ",";
		out << tmp1->gender << ",";
		string date = Datetostring(tmp1->dateOfBirth);
		out << date << ",";
		out << tmp1->socialID;
		out << endl;
		tmp1 = tmp1->next;
	}
	out.close();
}
void remove_course(string Courseid) {
	Course* tm = listCourses.pHead;
	string course;
	while (tm != NULL) {
		if (tm->ID == Courseid) {
			 course= semesterPath + "/Courses/" + Courseid + ".csv";
			removeCourse(listCourses, tm); 
			break;
		}
		tm = tm->next;
	}
	write_course(listCourses);
	int a = remove(course.c_str());
}
ListCourse Student_Display() {
	Course* tmp = listCourses.pHead;
	ListCourse list;
	initCourse(list);
	//initCourse(currentUser->list);
	while (tmp != NULL) {
		Student* tm = tmp->l.pHead;
		while (tm != NULL) {
			if (currentUser->ID == tm->studentID) {
				addCourse(list, tmp);
			}
			tm = tm->next;
		}
		tmp = tmp->next;
	}
	return list;
}
void Mark() {

}











































































//giao dien
int command(int&, int, int, function<int(int)>);
int generalOption(int curPos);

void UserAccount();


int staffOption(int curPos);
int userAccountOption(int curPos);


void StaffMenu() {
	const int width = 42;
	const int height = 7;
	const int left = 40;
	const int top = 12;
	int curPos = 0;
	int x = 13;
	do {
		resizeConsole(50, 100);
		ShowCur(0);
		system("cls");
		gotoXY(3, 20);
		cout << " _______  _______  _______  _______  _______    __   __  _______  __    _  __   __" << endl;
		gotoXY(4, 20);
		cout << "|       ||       ||   _   ||       ||       |  |  |_|  ||       ||  |  | ||  | |  |" << endl;
		gotoXY(5, 20);
		cout << "|  _____|| _    _||  |_|  ||    ___||    ___|  |       ||    ___||   |_| ||  | |  |" << endl;
		gotoXY(6, 20);
		cout << "| |_____   |   |  |       ||   |___ |   |___   |       ||   |___ |       ||  |_|  |" << endl;
		gotoXY(7, 20);
		cout << "|_____  |  |   |  |       ||    ___||    ___|  |       ||    ___ |  _    ||       |" << endl;
		gotoXY(8, 20);
		cout << " _____| |  |   |  |   _   ||   |    |   |      | ||_|| ||   |___ | | |   ||       |" << endl;
		gotoXY(9, 20);
		cout << "|_______|  |___|  |__| |__||___|    |___|      |_|   |_||_______||_|  |__||_______|" << endl;
		drawBox(width, height, left, top);
		gotoXY(x, 50);
		x++;
		cout << "User Account";
		gotoXY(x, 50);
		x++;
		cout << "Profile";
		gotoXY(x, 50);
		x++;
		cout << "Manage Student";
		gotoXY(x, 50);
		x++;
		x++;
		cout << "Manage Course";
		gotoXY(x, 50);
		cout << "Exit";
		x = 13;
		if (curPos == 4) x++;
		gotoXY(x + curPos, 45);
		cout << (char)175;
		x = 13;
	} while (command(curPos, 0, 4, staffOption));
}




void LoginSystem() {
	
	gotoXY(5, 11);
	cout << ".----------------.  .----------------.  .----------------.  .----------------.  .---------------- - ." << endl;
	gotoXY(6, 11);
	cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
	gotoXY(7, 11);
	cout << "| |   _____      | || |     ____     | || |    ______    | || |     _____    | || | ____  _____  | |" << endl;
	gotoXY(8, 11);
	cout << "| |  |_   _|     | || |   .'    `.   | || |  .' ___  |   | || |    |_   _|   | || ||_   \\ | _ _| | |" << endl;
	gotoXY(9, 11);
	cout << "| |    | |       | || |  /  .--.  \\  | || | / .'   \\_|   | || |      | |     | || |  |   \\ | |   | |" << endl;
	gotoXY(10, 11);
	cout << "| |    | |   _   | || |  | |    | |  | || | | |    ____  | || |      | |     | || |  | |\\ \\| |   | |" << endl;
	gotoXY(11, 11);
	cout << "| |   _| |__/ |  | || |  \\ `- - ' /  | || | \\ `.___]  _| | || |     _| |_    | || | _| |_\\   |_  | |" << endl;
	gotoXY(12, 11);
	cout << "| |  |________|  | || |   `.____.'   | || |  `._____.'   | || |    |_____|   | || ||_____|\\____| | |" << endl;
	gotoXY(13, 11);
	cout << "| |              | || |              | || |              | || |              | || |              | |" << endl;
	gotoXY(14, 11);
	cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
	gotoXY(15, 11);
	cout << "'----------------'  '----------------'  '----------------'  '----------------'  '----------------'" << endl;
	gotoXY(20, 30);
	cout << "ID:   ";
	gotoXY(22, 30);
	cout << "Password:  ";
	gotoXY(20, 34);
	getline(cin, id);
	gotoXY(22, 41);
	getline(cin, pass);
	getlistuser();
	currentUser = login(id, pass);
	if (currentUser == NULL) {
		gotoXY(24, 35);
		cout << "Login Fail!!";
		exit(0);
	}
	else {
		gotoXY(24, 35);
		cout << "Login Success!!";
		if (currentUser->isteacher) {
			system("cls");
			StaffMenu();
		}
		else {
			system("cls");
		}
	}
}


void changePassword() {
	const int width = 42;
	const int height = 7;
	const int left = 40;
	const int top = 10;
	int curPos = 0;
	int yPos = 13;
	string currentPassword;

	ShowCur(1);
	do {
		system("cls");
		gotoXY(9,55); cout << "HCMUS Portal";
		gotoXY(7,53); cout << "Change Password";
		drawBox(width, height, left, top);
		gotoXY(yPos,45); cout << "Current password: ";
		yPos++;
		yPos++;
		getline(cin, currentPassword);
		if (currentPassword == currentUser->password) {
			gotoXY(yPos,45); cout << "New password: ";
			yPos++;
			getline(cin, currentUser->password);
			ShowCur(0);
			saveListUser();
			return;
		}
		else {
			gotoXY(15,45); cout << "Wrong password";
			gotoXY(16,45); cout << "Enter to try again...";
			gotoXY(17, 45); cout << "Esc to back...";
			int key = _getch();
			if (key == 27) {
				ShowCur(0);
				return;
			}
		}
		yPos = 13;
	} while (true);
}
























void UserAccount() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "User Account";
		gotoXY(yPos, 52); cout << "Change Password";
		yPos++;
		gotoXY(yPos,52); cout << "Logout";
		yPos++;
		yPos++;
		gotoXY(yPos,52); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(curPos + yPos,45); cout << cursorLeft;
		yPos = 10;
	} while (command(curPos, 0, 2, userAccountOption));
}
void Profile() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	Date dateOfBirth = currentUser->brithday;
	do {
		system("cls");
		gotoXY(yPos - 4,55); cout << "HCMUS Portal";
		gotoXY( yPos - 2,57); cout << "Profile";
		drawBox(width, height, left, top);
		gotoXY( yPos,48); cout << "Last name: " << currentUser->lastname;
		yPos++;
		gotoXY(yPos,48); cout << "First name: " << currentUser->firstname;
		yPos++;
		gotoXY(yPos,48); cout << "Gender: " << currentUser->gender;
		yPos++;
		if (!currentUser->isteacher) {
			gotoXY(yPos,48); cout << "Class: " << currentUser->classname;
			yPos++;
			gotoXY(yPos,48); cout << "Student ID: " << currentUser->ID;
			yPos++;
		}
		else {
			gotoXY(yPos,48); cout << "Staff ID: " << currentUser->ID;
			yPos++;
		}
		gotoXY(yPos,48); cout << "Date of Birth: " << dateOfBirth.day << '/' << dateOfBirth.month << '/' << dateOfBirth.year;
		yPos += 2;
		gotoXY( yPos,60); cout << "Back";
		gotoXY( curPos + yPos,58); cout << cursorLeft;
		//gotoXY(65, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

}
void ManageStudent() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 55); cout << "Manage Student";
		gotoXY(yPos, 52); cout << "Create New School Year";
		yPos++;
		gotoXY(yPos, 52); cout << "Create New Class";
		yPos++;
		gotoXY(yPos, 52); cout << "List of Class";
		yPos++;
		gotoXY(yPos, 52); cout << "Student of Class";
		yPos++;
		yPos++;
		gotoXY(yPos, 52); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(curPos + yPos, 45); cout << cursorLeft;
		yPos = 10;
	} while (command(curPos, 0, 2, userAccountOption));
}






int userAccountOption(int curPos) {
	switch (curPos) {
	case 0:
		changePassword();
		break;
	case 1:
		logout();
		ShowCur(1);
		LoginSystem();
		return 0;
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}
int managerStudentOption(int curPos) {
	switch (curPos) {
	case 0:
		create_folder_SchoolYear();
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
	return 1;
}



int staffOption(int curPos) {
	switch (curPos) {
	case 0:
		UserAccount();
		break;
	case 1:
		Profile();
		break;
	case 2:
		cout << "haha";
		break;
	case 3:
		cout << "hihi";
		break;
	case 4:
		exit(0);
		break;
	}
	return 1;
}







int command(int& curPos, int minPos, int maxPos, function<int(int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos);
	case 224:
		key = _getch();
		switch (key) {
		case 72:
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80:
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		}
	}
	return 1;
}
int generalOption(int curPos) {
	switch (curPos) {
	case 0:
		return 0;
		break;
	}
	return 1;
}








