#include"Global.h"
#include"ConsoleScreen.h"
const string userDataPath = "./Data/Account/User.csv";
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
		course->prev = NULL;
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
//Course* convertCourseData(ifstream& data) {
//
//}




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
	
	string a = "./Data/Classes/" + className + ".csv";
	ofstream out(a);
	out.close();
	Class* c = new Class;
	c->ClassName = className;
	c->next = NULL;
	c->prev = NULL;
	addClass(listClasses, c);
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
	ListStudent b;
	
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









































































//giao dien
void LoginSystem() {
	getlistuser();
	drawBox(20, 3, 47, 4);
	gotoXY(5, 55);
	cout << "LOGIN";
	gotoXY(10, 35);
	cout << "User:  ";
	gotoXY(12, 35);
	cout << "Password:  ";
	gotoXY(10, 9 + 35);
	getline(cin, id);
	gotoXY(12, 12 + 35);

	getline(cin, pass);

	currentUser = login(id, pass);
	gotoXY(14, 45);
	if (currentUser == NULL) {
		cout << "Login fail!";
	}
	else {
		cout << "Login success!";
	}
}



