#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <ctime>
#include <direct.h>
#include <io.h>
#include <filesystem>
#include <sstream>
#include <cwchar>



using namespace std;


struct Date {
	string dayofweek;
	int day;
	int month;
	int year;
};
struct User {
	string ID;
	string password;
	string lastname;
	string firstname;
	string gender;
	string classname;
	int academicyear;
	bool isteacher;
	Date brithday;
	User* prev;
	User* next;

};

struct ListUser {
	User* pHead;
	User* pTail;
	int sz;
};



struct CourseMark {
	float MidMark;
	float FinalMark;
	float OtherMark;
	float AverageMark;
};
struct Semester {
	int Semester;
	Date start, end;
};
struct semesterMark{
	float GPA;
	float overrallGPA;
};
struct Student {
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string socialID;
	Date dateOfBirth;
	int academicYear;
	CourseMark courseMark;
	semesterMark semesterMark;
	Student* prev;
	Student* next;
};
struct ListStudent {
	Student* pHead;
	Student* pTail;
	string program;
	string className;
	string year;
	int academicYear;
	int size;
};
struct Class{
	string ClassName;
	Class* next;
	Class* prev;
};
struct ListClasses{
	Class* pHead;
	Class* pTail;
	int size;
};
struct Course {
	string ID;
	string coursename;
	string teachername;
	string classname;
	ListStudent l;
	int credits;
	int maxstudents = 50;
	int numberregistered = 0;
	int academicyear;
	string dayofweek;
	string session;
	Course* prev;
	Course* next;
};
struct ListCourse {
	Course* pHead;
	Course* pTail;
	Date start, end;
	int size;
};






int dayofweek(int d, int m, int y);
Date strtodate(string str);
string Datetostring(Date a);
void getCurrentDate();


void initUser(ListUser& l);
void initStudent(ListStudent& l);
void initClasses(ListClasses& l);
void initCourse(ListCourse& l);
void addUser(ListUser& list, User* user);
void addStudent(ListStudent& list, Student* student);
void addCourse(ListCourse& list, Course* course);
void removeCourse(ListCourse& list, Course* course);
void removeStudent(ListStudent& list, Student* student);
User* toUser(Student* student, string className);
void addStudentAccount(ListStudent listStudent);


User* convertUserData(ifstream& data);
Student* convertStudentData(ifstream& data);
Course* convertCourseData(ifstream& data);
void getListCourses();
void getListClasses();
ListStudent getListOfStudentInClass(Class* c);

//Dang nhap
void getlistuser();
User* login(string id, string pass);
void getInfomationUser();
void logout();

void createSchoolYear();
void create_folder_SchoolYear();
void createClasses(string lassName);
Student* InputStudent();
void Copyfile(string a, string b);
void writestudent(ListStudent& list, string className);


void create_semester(int a);
Course* Inputcourse();
void write_course(ListCourse l);
void create_folder_course();
void List_Courses(ListCourse l);
void Display_Course(ListCourse l);
void add_student_to_course(Student* a, string CourseId);
void remove_student_from_course(string id, string CourseId);
void remove_course(string Courseid);
ListCourse Student_Display();


void LoginSystem();
void StaffMenu();


extern ListUser listuser;
extern ListClasses listClasses;
extern ListCourse listCourses;
extern Semester currentSemester;
extern User* currentUser;
extern Date currentDate;
extern string id, pass;
extern string currentSchoolYear;
extern string semesterPath;
extern string schoolYearPath;
extern string classname;
