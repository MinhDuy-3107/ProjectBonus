#include"ConsoleScreen.h"
#include"Global.h"
int main() {
	getCurrentDate();
	createSchoolYear();
	ifstream in("./Data/" + currentSchoolYear + "/semester.txt");
	in.close();
}