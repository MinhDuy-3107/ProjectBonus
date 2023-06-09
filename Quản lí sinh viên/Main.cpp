#include"ConsoleScreen.h"
#include"Global.h"


int main() {
	ListCourse l;
	initCourse(l);
	Course* a = Inputcourse();
	addCourse(l, a);
	Course* b = Inputcourse();
	addCourse(l, b);
	create_semester(2);
	create_folder_course();
	List_Courses(l);

	
}