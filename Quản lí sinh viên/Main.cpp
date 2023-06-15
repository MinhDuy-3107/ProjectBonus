#include"ConsoleScreen.h"
#include"Global.h"


int main() {
	resizeConsole(50, 100);
	/*create_folder_course();*/
	/*ListCourse currentCourse;*/
	initCourse(listCourses);
	Course* a = Inputcourse();
	addCourse(listCourses, a);
	Course* b = Inputcourse();
	addCourse(listCourses, b);
	create_semester(1);
	create_folder_course();
	write_course(listCourses);
	List_Courses(listCourses);
	string a1 = semesterPath + "/Courses/MATH.csv";
	string b1 = "D:\\16CTT1.csv";
	Copyfile(b1, a1);
	/*Display_Course(listCourses);*/
	
	remove_course("MATH");
	
	


	




	
}