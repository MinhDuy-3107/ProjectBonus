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
struct ListUser{
	User* pHead;
	User* pTail;
	int sz;
};
struct Course {
	string ID;
	string coursename;
	string teachername;
	int credits;
	int maxstudents = 50;
	int numberregistered = 0;
	int academicyear;
	string dayofweek;
	string session[3];
	Course* prev;
	Course* next;
};
struct ListCourse{
	Course * pHead;
	Course* pTail;
	Date start, end;
	int size;
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
	ListCourse enrolledCourses;
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
struct ListClass{
	Class* pHead;
	Class* pTail;
	int size;
};





int dayofweek(int d, int m, int y);
Date strtodate(string str);
string Datetostring(Date a);
void getCurrentDate();


void initUser(ListUser& l);
void initStudent(ListStudent& l);
void initClass(ListClass& l);
void addUser(ListUser& list, User* user);
void addStudent(ListStudent& list, Student* student);
void addCourse(ListCourse& list, Course* course);
void removeCourse(ListCourse& list, Course* course);
void removeStudent(ListStudent& list, Student* student);


User* convertUserData(ifstream& data);
Student* convertStudentData(ifstream& data);
Course* convertCourseData(ifstream& data);

//Dang nhap
void getlistuser();
User* login(string id, string pass);

void createSchoolYear();
void create_folder_SchoolYear();
void createClasses();



extern ListUser listuser;
extern ListClass listClasses;
extern ListCourse listCourses;
extern Semester currentSemester;
extern User* currentUser;
extern Date currentDate;
extern string id, pass;
extern string currentSchoolYear;
extern string semesterPath;
extern string schoolYearPath;
