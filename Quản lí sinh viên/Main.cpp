#include"ConsoleScreen.h"
#include"Global.h"


int main() {
	int width = 8, top = 8, height = 4, left = 8;
	gotoXY(left, top);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(left, i);
		cout << char(186);
	}
	
	
	
}