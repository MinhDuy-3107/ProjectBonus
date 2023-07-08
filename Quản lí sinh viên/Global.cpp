#include"Global.h"
#include"ConsoleScreen.h"

using namespace std;


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
string classname;

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
void removeSameCourse(Course* head) {
	if (head == nullptr) {
		return;
	}

	Course* current = head;
	while (current != nullptr) {
		Course* runner = current;
		while (runner->next != nullptr) {
			if (runner->next->coursename == current->coursename) {
				Course* duplicate = runner->next;
				runner->next = runner->next->next;
				delete duplicate;
			}
			else {
				runner = runner->next;
			}
		}
		current = current->next;
	}
}
Course* deleteCourse(Course* head, string a) {
	
	if (head == nullptr)
		return head;

	Course* current = head;

	
	if (current != nullptr && current->coursename == a) {
		head = current->next;
		if (head != nullptr)
			head->prev = nullptr;
		delete current;
		return head;
	}

	
	while (current != nullptr && current->coursename != a)
		current = current->next;

	
	if (current == nullptr)
		return head;

	
	if (current->prev != nullptr)
		current->prev->next = current->next;
	if (current->next != nullptr)
		current->next->prev = current->prev;

	
	delete current;

	return head;
}
void saveListUser() {
	ofstream fout(userDataPath);
	fout << "ID,Password,Last name,First name,Class,Gender,Date of Birth,Academic year,Staff" << endl;
	User* curr = listuser.pHead;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->brithday.day) + "/" + to_string(curr->brithday.month) + "/" + to_string(curr->brithday.year);
		fout << curr->ID << "," << curr->password << "," << curr->lastname << "," << curr->firstname
			<< "," << curr->classname << "," << curr->gender << "," << dateOfBirth << "," << "2023" << ",";
		if (curr->isteacher) fout << "TRUE";
		else fout << "FALSE";
		curr = curr->next;
		if (curr != NULL) fout << endl;
	}
	fout.close();
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
void addStudentAccount(ListStudent listStudent) {
	Student* temp = listStudent.pHead;
	while (temp != NULL) {
		addUser(listuser, toUser(temp, listStudent.className));
		temp = temp->next;
	}
	saveListUser();
}
Student* toStudent(User* user) {
	Student* student = new Student;
	student->studentID = user->ID;
	
	student->lastName = user->lastname;
	student->firstName = user->firstname;
	student->gender = user->gender;
	student->dateOfBirth = user->brithday;
	
	student->prev = NULL;
	student->next = NULL;
	return student;
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
Student* convertStudentMark(ifstream& data) {
	Student* newStudent = new Student;
	string s;
	float a;
	getline(data, s, ',');
	if (s == "") return NULL;
	getline(data, newStudent->studentID, ',');
	getline(data, newStudent->lastName, ',');
	getline(data, newStudent->firstName, ',');
	getline(data, s,',');
	a = stof(s);
	newStudent->courseMark.OtherMark = (float)a;
	getline(data, s, ',');
	newStudent->courseMark.MidMark = stof(s);
	getline(data, s, ',');
	newStudent->courseMark.FinalMark= stof(s);
	getline(data, s, '\n');
	a = stof(s);
	newStudent->courseMark.AverageMark = (float)a;
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
	getline(data, course->session, '\n');
	initStudent(course->l);
	course->prev = NULL;
	course->next = NULL;
	return course;
}
Course* convertCourseMark(ifstream& data) {
	Course* course = new Course;
	string credits;
	getline(data, course->coursename, ',');
	if (course->coursename == "") return NULL;
	getline(data, credits, ',');
	course->credits = stoi(credits);
	getline(data, credits, ',');
	course->mark.OtherMark = stof(credits);
	getline(data, credits, ',');
	course->mark.MidMark = stof(credits);
	getline(data, credits, ',');
	course->mark.FinalMark = stof(credits);
	getline(data, credits, '\n');
	course->mark.AverageMark = stof(credits);
	course->prev = NULL;
	course->next = NULL;
	return course;
}




void getListCourses() {
	ifstream fin(semesterPath + "/Courses.csv");
	initCourse(listCourses);
	if (!fin) return;
	string s;
	getline(fin, s);
	getline(fin, s);
	while (!fin.eof()) {
		addCourse(listCourses, convertCourseData(fin));
	}
	fin.close();
}
void getListClasses() {
	initClasses(listClasses);
	string path = "./Data/Classes.csv";
	string a = "";
	ifstream in(path);
	getline(in, a);
	while (!in.eof()) {
		
		getline(in, a);
		if (a != "") {
			Class* tm = new Class;
			tm->ClassName = a;
			tm->next = NULL;
			tm->prev = NULL;
			addClass(listClasses, tm);
		}
		
	}
	in.close();
}
 ListStudent getListOfStudentInClass(Class *c) {
	 string a = "./Data/Classes/" + c->ClassName + ".csv", s;
	 ListStudent l;
	 initStudent(l);
	 ifstream data(a);
	 getline(data, s);
	 while(!data.eof()){
		 addStudent(l, convertStudentData(data));
	 }
	 return l;

}

 ListStudent getListOfStudentInCourse(Course* c) {
	 string a = semesterPath + "/Courses/" + c->coursename + ".csv";
	 string tmp;
	 initStudent(c->l);
	 ifstream in(a);
	 getline(in, tmp);
	 while (!in.eof()) {
		 addStudent(c->l, convertStudentData(in));
	 }
	 in.close();
	 return c->l;
 }
 ListStudent getListStudentInMark(Course* c) {
	 string a = semesterPath + "/Mark/" + c->coursename + "-mark.csv";
	 string tmp;
	 ListStudent l;
	 initStudent(l);
	 ifstream in(a);
	 getline(in, tmp);
	 while (!in.eof()) {
		 addStudent(l, convertStudentMark(in));
	 }
	 in.close();
	 return l;
 }
 ListCourse get(string a) {
	 ListCourse l;
	 initCourse(l);
	 string s;
	 ifstream in(a);
	 getline(in, s);
	 while (!in.eof()) {
		 addCourse(l, convertCourseMark(in));
	 }
	 in.close();
	 return l;
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

void createSchoolYear() {
	getCurrentDate();
	if (currentDate.month < 9) {
		currentSchoolYear = to_string(currentDate.year - 1) + "-" + to_string(currentDate.year);
	}
	else {
		currentSchoolYear = to_string(currentDate.year) + "-" + to_string(currentDate.year + 1);
	}
	
}

bool isDirectoryExists(const string& folderPath) {
	struct stat buffer;
	return (stat(folderPath.c_str(), &buffer) == 0);
}
bool isFileExists(const string& filePath) {
	ifstream file(filePath);
	return file.good();
}
bool clearFileData(const string& filePath) {
	if (remove(filePath.c_str()) == 0) {
		FILE* file = std::fopen(filePath.c_str(), "w");
		if (file != nullptr) {
			fclose(file);
			return true;
		}
	}
	return false;
}
bool removeFolder(const std::string& folderPath) {
	std::string removeCommand = "rm -rf ";
	removeCommand += folderPath;
	const char* command = removeCommand.c_str();
	int result = std::system(command);
	return (result == 0);
}


void create_folder_SchoolYear() {
	createSchoolYear();
	schoolYearPath = "./Data/" + currentSchoolYear;
	int a=_mkdir(schoolYearPath.c_str());
	string b = ".Data/Classes";
	int c = _mkdir(b.c_str());
	b = ".Data/Classes.csv";
	ofstream out(b, ios::app);
	out.close();
}
void createClasses(string className) {
	string a = "./Data/Classes/" + className + ".csv";
	ofstream out(a);
	out.close();
	string b = "./Data/Classes.csv";
	getListClasses();
	Class* tmp = listClasses.pHead;
	while (tmp != NULL) {
		if (tmp->ClassName == className) {
			notifyBox("Class is Existed!!");
			return;
		}
		tmp = tmp->next;
	}
	ofstream ou(b);
	Class* c = new Class;
	c->ClassName = className;
	c->next = NULL;
	c->prev = NULL;
	addClass(listClasses, c);
	tmp = listClasses.pHead;
	ou << "Class name";
	while (tmp!= NULL) {
		ou << endl<<tmp->ClassName;
		tmp = tmp->next;
	}
	ou.close();
	notifyBox("Create Success!!!");
}
Student* InputStudent() {
	int yPos = 10;
	Student *a = new Student;
	gotoXY(yPos, 53);
	cout << "Last name: ";
	getline(cin, a->lastName);
	gotoXY(++yPos, 53);
	cout << "First name: ";
	getline(cin, a->firstName);
	gotoXY(++yPos, 53);
	cout << "Student ID: ";
	getline(cin, a->studentID);
	gotoXY(++yPos, 53);
	cout << "Social ID: ";
	getline(cin, a->socialID);
	gotoXY(++yPos, 53);
	cout << "Gender: ";
	getline(cin, a->gender);
	gotoXY(++yPos, 53);
	cout << "Birthday: ";
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
void writestudenttoCourse(ListStudent& list, string a) {
	ofstream out(a, ios::out);
	if (!out.is_open()) return;
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
void write(ListCourse l,string a) { 
	ofstream out(a);
	out << "Course Name,Credits,OtherMark,MidMark,FinalMark,TotalMark\n";
	Course* tmp = l.pHead;
	while (tmp != NULL) {
		out << tmp->coursename << "," <<tmp->credits<<"," << tmp->mark.OtherMark << "," << tmp->mark.MidMark << "," << tmp->mark.FinalMark << "," << tmp->mark.AverageMark;
		tmp = tmp->next;
		if (tmp != NULL) out << endl;
	}
	out.close();
}
void create_folder_course() {
	string course = semesterPath + "/Courses";
	int a = _mkdir(course.c_str());
	string mark = semesterPath + "/Mark";
	int b = _mkdir(mark.c_str());
}
void create_semester() {
	createSchoolYear();
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	string temp;
	ShowCur(1);
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 55); cout << "Create Semester";
		drawBox(width, height, left, top);
		gotoXY(yPos, 50); cout << "Semester(1,2,3): ";
		cin >> currentSemester.Semester;
		cin.ignore();
		semesterPath = "./Data/" + currentSchoolYear + "/Semester " + to_string(currentSemester.Semester);
		if (isDirectoryExists(semesterPath)) {
			notifyBox("Semester is Existed");
			ifstream in(semesterPath + "/Courses.csv");
			getline(in, temp, ',');
			getline(in, temp, ',');
			currentSemester.start = strtodate(temp);
			getline(in, temp, '\n');
			currentSemester.end = strtodate(temp);
			
			getListCourses();
			
			return;
		}
		yPos++;
		
		gotoXY(yPos, 45);
		cout << "Start(dd/mm/yyyy): ";
		getline(cin, temp);
		currentSemester.start = strtodate(temp);
		yPos++;
		gotoXY(yPos, 45);
		cout << "End(dd/mm/yyyy): ";
		getline(cin, temp);
		currentSemester.end= strtodate(temp);
		int b = _mkdir(semesterPath.c_str());
		create_folder_course();
		ShowCur(0);
		string tmp = semesterPath + "/Courses.csv";
		ofstream out(tmp);
		out << "Courses registration session:," << Datetostring(currentSemester.start) << "," << Datetostring(currentSemester.end);
		out.close();
		return;
	} while (true);
}
void inputsemester() {
	createSchoolYear();
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	string temp;
	ShowCur(1);
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 55); cout << "Create Semester";
		drawBox(width, height, left, top);
		gotoXY(yPos, 50); cout << "Semester(1,2,3): ";
		cin >> currentSemester.Semester;
		cin.ignore();
		semesterPath = "./Data/" + currentSchoolYear + "/Semester " + to_string(currentSemester.Semester);
		if (!isDirectoryExists(semesterPath)) notifyBox("Open Fail!!!");
		ShowCur(0);
		notifyBox("Open Success!!!");
		return;
	} while (true);
}

Course* InputCourse() {
	int yPos = 10;
	string tmp;
	Course* a = new Course;
	gotoXY(yPos, 53);
	cout << "Course Name: ";
	getline(cin, a->coursename);
	gotoXY(++yPos, 53);
	cout << "Course ID: ";
	getline(cin, a->ID);
	gotoXY(++yPos, 53);
	cout << "Teacher name: ";
	getline(cin, a->teachername);
	gotoXY(++yPos, 53);
	cout << "Class Name: ";
	getline(cin, a->classname);
	gotoXY(++yPos, 53);
	cout << "Credits: ";
	getline(cin, tmp);
	a->credits = stoi(tmp);
	gotoXY(++yPos, 53);
	cout << "Day of week: ";
	getline(cin, a->dayofweek);
	gotoXY(++yPos, 53);
	cout << "Sesion: ";
	getline(cin, a->session);
	a->next = NULL;
	a->prev = NULL;

	return a;
}
void write_course() {
	string course = semesterPath + "/Courses.csv";
	ofstream out(course, ios::out);
	out << "Courses registration session:," << Datetostring(currentSemester.start) << "," << Datetostring(currentSemester.end) << endl;
	out << "ID,Course Name,Teacher Name,Credits,Class Name,Day of week,Session" << endl;
	Course* tmp = listCourses.pHead;
	while (tmp != NULL) {
		out << tmp->ID << ",";
		out << tmp->coursename << ",";
		out << tmp->teachername << ",";
		out << tmp->credits << ",";
		out << tmp->classname << ",";
		out << tmp->dayofweek << ",";
		out << tmp->session;
		tmp = tmp->next;
		if (tmp != NULL) out << endl;
	}
	out.close();
	
}




void remove_course(Course*course) {
	string tmp;
	ListStudent l;
	initStudent(l);
	string a = semesterPath + "/Courses/" + course->coursename + ".csv";
	ifstream in(a);
	getline(in, tmp);
	while (!in.eof()) {
		addStudent(l, convertStudentData(in));
	}
	in.close();
	remove(a.c_str());
	a = semesterPath + "/Mark/" + course->coursename + "-mark.csv";
	remove(a.c_str());
	
	removeCourse(listCourses, course);
}

void saveScoreboard(ListStudent list, Course course) {
	ofstream fout(semesterPath + "/Mark/" + course.coursename + "-mark.csv");
	fout << "No,Student Id,Last name,First name,OtherMark,MidMark,FinalMark,AverageMark" << endl;
	int no = 1;
	Student* temp = list.pHead;
	while (temp != NULL) {
		fout << no << "," << temp->studentID << "," << temp->lastName << "," << temp->firstName
			<< "," << temp->courseMark.OtherMark << "," << temp->courseMark.MidMark << ","
			<< temp->courseMark.FinalMark << "," << temp->courseMark.AverageMark << endl;
		temp = temp->next;
		no++;
	}
	fout.close();
}



void SemesterSummary() {
	getListCourses();
	string a = semesterPath + "/Student";
	
	int x = _mkdir(a.c_str());
	Course* tmp = listCourses.pHead;
	while (tmp != NULL) {
		ListStudent l;
		initStudent(l);
		string f = semesterPath + "/Mark/" + tmp->coursename + "-mark.csv";
		ifstream ifile(f);
		string tm;
		getline(ifile, tm);
		while (!ifile.eof()) {
			addStudent(l, convertStudentMark(ifile));
		}
		ifile.close();
		Student* tm1 = l.pHead;
		while (tm1 != NULL) {
			ListCourse m;
			string b = a + "/" + tm1->studentID + ".csv";
			if (!isFileExists(b)) {
				ofstream w(b);
				w.close();
			}
			Course* af = new Course;
			af->coursename = tmp->coursename;
			af->credits = tmp->credits;
			af->mark.OtherMark = tm1->courseMark.OtherMark;
			af->mark.MidMark = tm1->courseMark.MidMark;
			af->mark.FinalMark = tm1->courseMark.FinalMark;
			af->mark.AverageMark = tm1->courseMark.FinalMark;
			af->next = NULL;
			af->prev = NULL;
			m=get(b);
			removeSameCourse(m.pHead);
			addCourse(m, af);
			write(m, b);
			tm1 = tm1->next;
		}
		tmp = tmp->next;
	}
	loading("Calculate");
}










//giao dien
int command(int&, int, int, function<int(int)>);
int viewListOfClassesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option);
int classDetailCommand(int& curPos, int minPos, int maxPos, Class* c, function<int(int, Class*)> option);
int viewCoursesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option);
int updateCourseCommand(int& curPos, int minPos, int maxPos, Course* course, function<int(int, Course*)> option);
int viewScoreboardCommand(int& curPos, int minPos, int maxPos, ListStudent list, Course course,
	int& page, int numberPages, function<int(int, int, ListStudent, Course)> option);



void UserAccount();

int generalOption(int curPos);
int staffOption(int curPos);
int studentOption(int curPos);
int userAccountOption(int curPos);
int managerStudentOption(int curPos);
int selectAddstudentOPtion(int curPos);
int viewListOfClassesOption(int curPos, int page);
int classDetailOption(int curPos, Class* c);
int viewListOfStudentOption(int curPos, int page);
int viewCourseOption(int curPos, int page);
int manageCoursesOption(int curPos);
int updateCourseOption(int curPos, Course* course);
int viewScoreboardOption(int curPos, int page, ListStudent list, Course course);



void selectAddstudent();


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

void StudentMenu() {
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
		gotoXY(3, 10);
		cout << " _______  _______  __   __  ______   _______  __   _  _______    __   __  _______  __    _  __   __";
		gotoXY(4, 10);
		cout << "|       ||       ||  | |  ||      | |       ||  | | ||       |  |  |_|  ||       ||  |  | ||  | |  |";
		gotoXY(5, 10);
		cout << "|  _____||_     _||  | |  ||  _ ||_||   |_|_||_    _|  |   |    |       ||   |___||  | |  |";
		gotoXY(6, 10);
		cout << "| |_____   |   |  |  |_|  || | |   ||   |___ |      |  |   |    |       ||   |___ |       ||  |_|  |";
		gotoXY(7, 10);
		cout << "|_____  |  |   |  |       || |_|   ||    ___ || _   |  |   |    |       ||    ___|| |_    ||       |";
		gotoXY(8, 10);
		cout << " ____|  |  |   |  |       ||       ||   |___ | | |  |  |   |    | ||_|| ||   |___|| | ||  ||       |";
		gotoXY(9, 10);
		cout << "|_______|  |___|  |_______||______| |_______||_| |__|  |___|    |_|   |_||_______||_|   |_||_______|";

		drawBox(width, height, left, top);
		gotoXY(x, 50);
		x++;
		cout << "User Account";
		gotoXY(x, 50);
		x++;
		cout << "Profile";
		gotoXY(x, 50);
		x++;
		cout << "InPut Semester";
		gotoXY(x, 50);
		x++;
		x++;
		cout << "View Scoreboard";
		gotoXY(x, 50);
		cout << "Exit";
		x = 13;
		if (curPos == 4) x++;
		gotoXY(x + curPos, 45);
		cout << (char)175;
		x = 13;
	} while (command(curPos, 0, 4, studentOption));
}


void LoginSystem() {
	resizeConsole(50, 100);
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
	gotoXY(22, 30);
	
	cout << "ID:   ";
	gotoXY(24, 30);
	cout << "Password:  ";
	gotoXY(22, 34);
	gotoXY(22, 34);
	
	getline(cin, id);
	gotoXY(24, 41);
	getline(cin, pass);
	getlistuser();
	//getListClasses();
	currentUser = login(id, pass);
	if (currentUser == NULL) {
		gotoXY(26, 35);
		notifyBox("Login Fail!!!!");
		system("cls");
		ShowCur(1);
		LoginSystem();
		
	}
	else {
		notifyBox("Login Success!!!");
		if (currentUser->isteacher) {
			system("cls");
			StaffMenu();
		}
		else {
			system("cls");
			StudentMenu();
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
		drawBox(width, height+5, left, top);
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
void createNewClass() {
	const int width = 45;
	const int height = 10;
	const int left = 45;
	const int top = 10;

	int curPos = 0;
	int yPos = 12;
	
	
	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 4, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 2, 57); cout << "Create New Class";
		drawBox(width, height, left, top);
		gotoXY(yPos, 48);
		cout << "Class Name (APCS/CLC/CTT/VP): ";
		getline(cin, classname);
		ShowCur(0);
		createClasses(classname);
	
		return;
	} while (1);
}

void AddOne() {
	const int width = 45;
	const int height = 10;
	const int left = 45;
	const int top = 8;

	int curPos = 0;
	int yPos = 12;


	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 7, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 5, 57); cout << "Add One Student";
		drawBox(width, height, left, top);
		ListStudent l;
		initStudent(l);
		l.className = classname;
		string name = "./Data/Classes/" + classname + ".csv";
		ifstream fin;
		fin.open(name, ios::in);
		string temp;
		getline(fin, temp);
		
		while (!fin.eof()) {
			addStudent(l, convertStudentData(fin));
		}
		fin.close();

		addStudent(l, InputStudent());
		ShowCur(0);
		addStudentAccount(l);
		writestudent(l, classname);
		notifyBox("Add Success!!!");
		return;
	} while (1);

}
void AddFile() {
	const int width = 45;
	const int height = 10;
	const int left = 45;
	const int top = 10;
	string s;
	int curPos = 0;
	int yPos = 12;
	ListStudent l;
	initStudent(l);
	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 4, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 2, 57); cout << "Add File Student";
		drawBox(width, height, left, top);
		gotoXY(yPos, 55);
		cout << "Path of file: ";
		string a="./Data/Classes/" + classname + ".csv";
		string b;
		getline(cin, b);
		ShowCur(0);
		Copyfile(b,a);
		ifstream in(a);
		getline(in, s);
		while (!in.eof()) {
			addStudent(l, convertStudentData(in));
		}
		in.close();
		addStudentAccount(l);
		notifyBox("Add Success!!!");
		return;
	} while (1);


}
void AddOneCourse() {
	const int width = 50;
	const int height = 13;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	string s;
	do {
		ShowCur(1);
		system("cls");
		getListCourses();
		gotoXY(yPos - 7, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 5, 57); cout << "Add One Course";
		drawBox(width, height, left, top);
		Course* e = InputCourse();
		addCourse(listCourses,e);
		write_course();
		string a = semesterPath + "/Courses/" + e->coursename + ".csv";
		ofstream out(a);
		out.close();
		string b;
		gotoXY(19, 53);
		cout << "File Students enrolled: ";
		getline(cin, b);
		Copyfile(b, a);
		ListStudent ss;
		initStudent(ss);
		ofstream o1(semesterPath + "/Mark/" + e->coursename + "-mark.csv");
		o1.close();
		ifstream i(semesterPath + "/Courses/" + e->coursename + ".csv");
		ofstream o(semesterPath + "/Mark/" + e->coursename + "-mark.csv");
		getline(i, s);
		while (!i.eof()) {
			addStudent(ss, convertStudentData(i));
		}
		i.close();
		int stt = 1;
		o << "No,ID,Last name,First name,OtherMark,MidMark,FinalMark,AverageMark" << endl;
		Student* r = ss.pHead;
		while (r != NULL) {
			o << stt << "," << r->studentID << "," << r->lastName<<"," << r->firstName<<","<<"0,0,0,0";
			if (r->next != NULL) o << endl;
			r = r->next;
			stt++;
		}
		ShowCur(0);
		notifyBox("Create Success!!!");
		return;
	} while (true);
}
void AddStudentToCourse(Course* &course) {
	
	const int width = 45;
	const int height = 10;
	const int left = 45;
	const int top = 8;

	int curPos = 0;
	int yPos = 12;


	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 7, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 5, 57); cout << "Add One Student";
		drawBox(width, height, left, top);
		string a = semesterPath + "/Courses/" + course->coursename + ".csv";
		ifstream in(a);
		string tmp;
		initStudent(course->l);
		getline(in, tmp);
		while (!in.eof()) {
			addStudent(course->l, convertStudentData(in));
		}
		in.close();

		addStudent(course->l, InputStudent());
		ShowCur(0);
		writestudenttoCourse(course->l, a);
		return;
	} while (1);
}
void DeleteStudent(Course*&course) {
	const int width = 45;
	const int height = 6;
	const int left = 45;
	const int top = 8;

	int curPos = 0;
	int yPos = 12;


	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 7, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 5, 57); cout << "Delete Student";
		drawBox(width, height, left, top);
		string a = semesterPath + "/Courses/" + course->coursename + ".csv";
		ifstream in(a);
		string tmp;
		initStudent(course->l);
		getline(in, tmp);
		while (!in.eof()) {
			addStudent(course->l, convertStudentData(in));
		}
		in.close();
		string b;
		gotoXY(yPos, 55); cout << "Student ID: ";
		getline(cin, b);
		ShowCur(0);
		Student* tm = course->l.pHead;
		while (tm != NULL) {
			if (tm->studentID == b) {
				removeStudent(course->l, tm);
				writestudenttoCourse(course->l, a);
				return;
			}
			tm = tm->next;
		}
		
		return;
	} while (1);
}
void ImportScoreBoard(Course*course) {
	const int width = 45;
	const int height = 6;
	const int left = 45;
	const int top = 8;

	int curPos = 0;
	int yPos = 12;
	do {
		ShowCur(1);
		system("cls");
		gotoXY(yPos - 7, 59); cout << "HCMUS Portal";
		gotoXY(yPos - 5, 57); cout << "Import ScoreBoard";
		drawBox(width, height, left, top);
		gotoXY(yPos, 47); cout << "File ScoreBoard: ";
		string b;
		getline(cin, b);
		string a = semesterPath + "/Mark/" + course->coursename + "-mark.csv";
		Copyfile(b, a);
		ShowCur(0);
		return;
	} while (1);
}
void StudentListOfCourse() {
	const int width = 64;
	int height = 10;
	const int left = 28;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	Student* e = toStudent(currentUser);
	string b = semesterPath + "/Student/" + e->studentID + ".csv";
	ListCourse list = get(b);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 58); cout <<"List of Course";
		gotoXY(10, 36); cout << "No";
		gotoXY(10, 42); cout << "Course Name";
		gotoXY( 10,60); cout << "Other";
		gotoXY(10,67); cout << "Midterm";
		gotoXY(10,76); cout << "Final";
		gotoXY(10,83); cout << "Total";
		if (list.pHead != NULL) {
			Course* temp = list.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(yPos, 36); cout << no;
				gotoXY(yPos,42); cout << temp->coursename;
				gotoXY(yPos, 60); cout << temp->mark.OtherMark;
				gotoXY(yPos, 67); cout << temp->mark.MidMark;
				gotoXY(yPos, 76); cout << temp->mark.FinalMark;
				gotoXY(yPos, 83); cout << temp->mark.AverageMark;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos, 58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(yPos, 59); cout << "Back";
			gotoXY(curPos + yPos, 57); cout << cursorLeft;
			gotoXY(curPos + yPos, 64); cout << cursorRight;
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, 0, page, numberPages, viewListOfStudentOption));
}

void viewScoreboard(Course* course) {
	const int width = 64;
	int height = 10;
	const int left = 28;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListStudentInMark(course);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 10;
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,56); cout << "Scoreboard";
		textAlignCenter(course->coursename, left, width, 9);
		gotoXY(11,31); cout << "No";
		gotoXY(11,36); cout << "ID";
		gotoXY(11,45); cout << "Full name";
		gotoXY(11,63); cout << "Other";
		gotoXY(11,70); cout << "Midterm";
		gotoXY(11,79); cout << "Final";
		gotoXY(11,89); cout << "Total";
		if (list.pHead != NULL) {
			Student* temp = list.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(yPos,31); cout << no;
				gotoXY(yPos,36); cout << temp->studentID;
				string fullName = temp->lastName + " " + temp->firstName;
				if (fullName.length() > 27) fullName = fullName.substr(0, 27);
				gotoXY(yPos,45); cout << fullName;
				gotoXY(yPos,63); cout << temp->courseMark.OtherMark;
				gotoXY(yPos,70); cout << temp->courseMark.MidMark;
				gotoXY(yPos,79); cout << temp->courseMark.FinalMark;
				gotoXY(yPos,86); cout << temp->courseMark.AverageMark;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos,58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(yPos,59); cout << "Save";
			yPos++;
			gotoXY(yPos,59); cout << "Back";
			yPos = 13;
			if (curPos == i || curPos == i + 1) {
				yPos += 2;
				gotoXY( curPos + yPos,57); cout << cursorLeft;
				gotoXY( curPos + yPos,64); cout << cursorRight;
			}
			else {
				gotoXY( curPos + yPos,29); cout << cursorLeft;
				gotoXY(curPos + yPos,92); cout << cursorRight;
			}
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewScoreboardCommand(curPos, 0, i + 1, list, *course, page, numberPages, viewScoreboardOption));
}
void viewListOfClasses() {
	const int width = 40;
	int height = 6;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	int numberPages;
	int page = 1;
	int i = 0;

	getListClasses();
	do {
		numberPages = (listClasses.size / 10) + 1;
		i = 0;
		height = 6;
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		//gotoXY(52, 7); cout << year;
		if (listClasses.pHead != NULL) {
			Class* temp = listClasses.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY(yPos,58); cout << temp->ClassName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos,58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(yPos,59); cout << "Back";
			yPos = 10;
			if (curPos == i) {
				yPos += 2;
				gotoXY( curPos + yPos,57); cout << cursorLeft;
				gotoXY( curPos + yPos,64); cout << cursorRight;
			}
			else {
				gotoXY( curPos + yPos,56); cout << cursorLeft;
				gotoXY(curPos + yPos,66); cout << cursorRight;
			}
			yPos = 10;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewListOfClassesCommand(curPos, 0, i, page, numberPages, viewListOfClassesOption));
}
void viewListOfStudent(Class* c) {
	const int width = 54;
	int height = 9;
	const int left = 33;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentInClass(c);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,58); cout << c->ClassName;
		gotoXY(10,36); cout << "No";
		gotoXY(10,42); cout << "ID";
		gotoXY(10,52); cout << "Last name";
		gotoXY(10,77); cout << "First name";
		if (list.pHead != NULL) {
			Student* temp = list.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(yPos,36); cout << no;
				gotoXY(yPos,42); cout << temp->studentID;
				string lastName = temp->lastName;
				if (lastName.length() > 24) lastName = lastName.substr(0, 24);
				gotoXY(yPos,52); cout << lastName;
				gotoXY(yPos,77); cout << temp->firstName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos,58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY( yPos,59); cout << "Back";
			gotoXY( curPos + yPos,57); cout << cursorLeft;
			gotoXY(curPos + yPos,64); cout << cursorRight;
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, 0, page, numberPages, viewListOfStudentOption));
}
void viewListStudentOfCourse(Course* c) {
	const int width = 54;
	int height = 9;
	const int left = 33;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentInCourse(c);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 58); cout << c->coursename;
		gotoXY(10, 36); cout << "No";
		gotoXY(10, 42); cout << "ID";
		gotoXY(10, 52); cout << "Last name";
		gotoXY(10, 77); cout << "First name";
		if (list.pHead != NULL) {
			Student* temp = list.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(yPos, 36); cout << no;
				gotoXY(yPos, 42); cout << temp->studentID;
				string lastName = temp->lastName;
				if (lastName.length() > 24) lastName = lastName.substr(0, 24);
				gotoXY(yPos, 52); cout << lastName;
				gotoXY(yPos, 77); cout << temp->firstName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos, 58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(yPos, 59); cout << "Back";
			gotoXY(curPos + yPos, 57); cout << cursorLeft;
			gotoXY(curPos + yPos, 64); cout << cursorRight;
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, 0, page, numberPages, viewListOfStudentOption));
}
void courseDetail(Course* course) {
	const int width = 40;
	const int height = 14;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	
	do {
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "View Course";
		drawBox(width, height, left, top);
		alignRow(yPos, 45, "Course ID: " + course->ID, 32);
		alignRow(yPos, 45, "Course name: " + course->coursename, 32);
		alignRow(yPos, 45, "Teacher name: " + course->teachername, 32);
		alignRow(yPos, 45, "Class name: " + course->classname, 32);
		alignRow(yPos, 45, "Credits: " + to_string(course->credits), 32);
		alignRow(yPos, 45, "Number of student: " + to_string(course->maxstudents), 32);
		alignRow(yPos, 45,  "Weekday: " + course->dayofweek, 32);
		alignRow(yPos, 45, "Session: " + course->session, 32);
		yPos++;
		gotoXY(yPos,60); cout << "Back";
		gotoXY(yPos + curPos,58); cout << cursorLeft;
		gotoXY(curPos + yPos,65); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

}
void updateStudentResult(Student* student) {
	const int width = 30;
	int height = 8;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	string s;
	ShowCur(1);
	system("cls");
	textAlignCenter("HCMUS Portal", left, width, 5);
	textAlignCenter("Update Student Result", left, width, 7);
	drawBox(width, height, left, top);
	textAlignCenter(student->lastName + " " + student->firstName, left, width, 9);
	gotoXY(11, 50); cout << "Other Mark: "; getline(cin, s); student->courseMark.OtherMark = stof(s);
	gotoXY(12, 50); cout << "Midterm Mark: "; getline(cin, s);  student->courseMark.MidMark=stof(s);
	gotoXY(13, 50); cout << "Final Mark: ";  getline(cin, s);  student->courseMark.FinalMark = stof(s);
	gotoXY(14, 50); cout << "Total Mark: ";  getline(cin, s);  student->courseMark.AverageMark = stof(s);
	ShowCur(0);
}





void updateCourse(Course* course) {
	const int width = 30;
	const int height = 12;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	ShowCur(0);
	do {
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "Update Course";
		drawBox(width, height, left, top);
		gotoXY( yPos,58); cout << "Detail";
		yPos++;
		textAlignCenter("Delete Course", 45, 30, yPos);
		yPos++;
		textAlignCenter("Add Student", 45, 30, yPos);
		yPos++;
		textAlignCenter("Delete Student", 45, 30, yPos);
		yPos++;
		textAlignCenter("List Of Student", 45, 30, yPos);
		yPos++;
		textAlignCenter("Import Scoreboard", 45, 30, yPos);
		yPos++;
		textAlignCenter("View Scoreboard", 45, 30, yPos);
		yPos++;
		yPos++;
		gotoXY(yPos,58); cout << "Back";
		yPos = 10;
		if (curPos == 7) yPos++;
		if (curPos < 1 || curPos == 7) {
			gotoXY(curPos + yPos,56); cout << cursorLeft;
			gotoXY( curPos + yPos,65); cout << cursorRight;
		}
		else {
			gotoXY(curPos + yPos,48); cout << cursorLeft;
			gotoXY(curPos + yPos,73); cout << cursorRight;
		}
		yPos = 10;
	} while (updateCourseCommand(curPos, 0, 7, course, updateCourseOption));
	
	write_course();
}
void viewCourses() {
	const int width = 50;
	int height = 9;
	const int left = 35;
	const int top = 8;
	int curPos = 0;
	int yPos = 11;
	int numberPages;
	int page = 1;
	int i = 0;
	
	do {
		i = 0;
		numberPages = ((listCourses.size - 1) / 10) + 1;
		height = 9;
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "List Course";
		gotoXY(10,48); cout << "ID";
		gotoXY(10,60); cout << "Course name";
		getListCourses();
		
		if (listCourses.pHead != NULL) {
			Course* temp = listCourses.pHead;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY( yPos,48); cout << temp->ID;
				string courseName = temp->coursename;
				if (courseName.length() > 24) courseName = courseName.substr(0, 24);
				gotoXY( yPos,60); cout << courseName;
				
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(yPos,58);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(yPos,59); cout << "Back";
			yPos = 11;
			if (curPos == i) {
				yPos += 2;
				gotoXY(curPos + yPos,57 ); cout << cursorLeft;
				gotoXY( curPos + yPos,64); cout << cursorRight;
			}
			else {
				gotoXY(curPos + yPos,36); cout << cursorLeft;
				gotoXY( curPos + yPos,82); cout << cursorRight;
			}
			yPos = 11;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, i, page, numberPages, viewCourseOption));
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
	const int height = 9;
	const int left = 41;
	const int top = 9;
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
		gotoXY(yPos, 52); cout << "Add Student";
		yPos++;
		gotoXY(yPos, 52); cout << "List of Class";
		yPos++;
		
		yPos++;
		gotoXY(yPos, 52); cout << "Back";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(curPos + yPos, 45); cout << cursorLeft;
		yPos = 10;
	} while (command(curPos, 0, 4, managerStudentOption));
}
void selectAddstudent() {
	const int width = 40;
	const int height = 7;
	const int left = 41;
	const int top = 9;
	int curPos = 0;
	int yPos = 10;
	system("cls");
	ShowCur(1);
	drawBox(width, height, left, top);
	gotoXY(5, 55); cout << "HCMUS Portal";
	gotoXY(7, 55); cout << "Select Add Student";
	gotoXY(yPos, 52); cout << "Class Name: ";
	getline(cin, classname);
	ShowCur(0);
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7, 55); cout << "Select Add Student";
		
		gotoXY(yPos, 52); cout << "Add One Student";
		yPos++;
		gotoXY(yPos, 52); cout << "Add file";
		yPos++;
		yPos++;
		gotoXY(yPos, 52); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(curPos + yPos, 45); cout << cursorLeft;
		yPos = 10;
	} while (command(curPos, 0, 2,selectAddstudentOPtion));
}
void ManageCourses() {
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	do {
		getListCourses();
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(5, 55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "Manage Courses";
		gotoXY(yPos, 50); cout << "Create Semester";
		yPos++;
		gotoXY(yPos,50); cout << "Add Courses";
		yPos++;
		gotoXY( yPos,50); cout << "List Of Courses";
		yPos++;
		gotoXY(yPos,50); cout << "Semester Summary";
		yPos++;
		yPos++;
		gotoXY(yPos,50); cout << "Back";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(curPos + yPos,48); cout << cursorLeft;
		gotoXY(curPos + yPos,78); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 4, manageCoursesOption));
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
		notifyBox("Create Success!!!");
		break;
	case 1:
		createNewClass();
		break;
	case 2:
		selectAddstudent();
		break;
	case 3:
		getListClasses();
		viewListOfClasses();
		break;
	case 4:
		return 0;
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
		ManageStudent();
		break;
	case 3:
		ManageCourses();
		break;
	case 4:
		exit(0);
		break;
	}
	return 1;
}

int selectAddstudentOPtion(int curPos) {
	switch (curPos) {
	case 0:
		AddOne();
		break;
	case 1:
		AddFile();
		break;
	case 2:
		return 0;
		break;

	
	}
	return 1;
}
void classDetail(Class* c) {
	const int width = 30;
	const int height = 7;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(5,55); cout << "HCMUS Portal";
		gotoXY(7,55); cout << "Class Option";
		drawBox(width, height, left, top);
		textAlignCenter("List Of Student", left, width, yPos);
		
		yPos++;
		yPos++;
		gotoXY(yPos,58); cout << "Back";
		yPos = 10;
		if (curPos == 1) yPos++;
		if (curPos == 1) {
			gotoXY(curPos + yPos,56); cout << cursorLeft;
			gotoXY(curPos + yPos,65); cout << cursorRight;
		}
		else {
			gotoXY(curPos + yPos,48); cout << cursorLeft;
			gotoXY(curPos + yPos,73); cout << cursorRight;
		}
		yPos = 10;
	} while (classDetailCommand(curPos, 0, 1, c, classDetailOption));

}
int viewListOfClassesOption(int curPos, int page) {
	int count = 0;

	Class* temp = listClasses.pHead;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Class* classSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			classSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (classSelected == NULL) {
		return 0;
	}
	else {
		if (currentUser->isteacher) classDetail(classSelected);
		else viewListOfStudent(classSelected);
	}
	return 1;
}
int classDetailOption(int curPos, Class* c) {
	switch (curPos) {
	case 0:
		viewListOfStudent(c);
		break;
	case 1:
		return 0;
		break;
	}
	return 1;
}
int viewListOfStudentOption(int curPos, int page) {
	return 0;
}
int viewCourseOption(int curPos, int page) {
	int count = 0;
	getListCourses();
	Course* temp = listCourses.pHead;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Course* courseSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			courseSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (courseSelected == NULL) {
		return 0;
	}
	else {
		updateCourse(courseSelected);
	}
	return 1;
}
int manageCoursesOption(int curPos) {
	switch (curPos) {
	case 0:
		create_semester();
		break;
	case 1:
		AddOneCourse();
		break;
	case 2:
		viewCourses();
		break;
	case 3:
		SemesterSummary();
		break;
	case 4:
		return 0;
		break;
	
	}
	return 1;
}
int updateCourseOption(int curPos, Course* course) {
	switch (curPos)
	{
	case 0:
		courseDetail(course);
		
		return 1;
		break;
	
	case 1:
		if (confirmBox())remove_course(course);
		else return 1;
		break;
	case 2:
		AddStudentToCourse(course);
		return 1;
		break;
	case 3:
		DeleteStudent(course);
		return 1;
		break;
	case 4:
		viewListStudentOfCourse(course);
		return 1;
		break;
	case 5:
		ImportScoreBoard(course);
		return 1;
		break;
	case 6:
		viewScoreboard(course);
		return 1;
		break;
	case 7:
	
		break;
	}
	
	write_course();
	return 0;
}
int viewScoreboardOption(int curPos, int page, ListStudent list, Course course) {
	int count = 0;

	Student* temp = list.pHead;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Student* studentSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			studentSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (studentSelected == NULL) {
		int n = count - curPos;
		switch (n) {
		case 0:
			loading("Saving...");
			saveScoreboard(list, course);
			return 0;
		}
		return 0;
	}
	else {
		updateStudentResult(studentSelected);
	}
	return 1;
}

int studentOption(int curPos) {
	switch (curPos) {
	case 0:
		UserAccount();
		break;
	case 1:
		Profile();
		break;
	case 2:
		inputsemester();
		break;
	case 3:
	StudentListOfCourse();
	break;
	case 4:
		exit(0);
	}
	return 1;
}
//int AddCourse(int curPos) {
//	switch (curPos) {
//	case 0:
//		AddOneCourse();
//		break;
//	case 1:
//		//AddFileCourse();
//		break;
//	case 2:
//		return 0;
//		break;
//
//
//	}
//	return 1;
//}





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
int viewListOfClassesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
int classDetailCommand(int& curPos, int minPos, int maxPos, Class* c, function<int(int, Class*)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, c);
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
int viewCoursesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
int updateCourseCommand(int& curPos, int minPos, int maxPos, Course* course, function<int(int, Course*)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, course);
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
int viewScoreboardCommand(int& curPos, int minPos, int maxPos, ListStudent list, Course course,
	int& page, int numberPages, function<int(int, int, ListStudent, Course)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page, list, course);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
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









