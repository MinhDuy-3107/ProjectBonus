#include"ConsoleScreen.h"
#include"Global.h"


int main() {
	create_semester(2);
	initCourse(listCourses);
	Course* a = Inputcourse();
	addCourse(listCourses, a);
	Course* b = Inputcourse();
	addCourse(listCourses, b);
	
	List_Courses(listCourses);


	
}