#include"ConsoleScreen.h"

int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { y, x };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}
//============= đặt màu cho chữ =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

//======= trả về mã phím người dùng bấm =========
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}
//================ đặt màu chữ và nền =================== 
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void drawBox(int width, int height, int left, int top) {
	gotoXY(top,left);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		gotoXY(top,left+i+1);
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(i,left);
		cout << char(186);
	}
	gotoXY(top+height, left);
	cout << char(200);
	for (int i = 0; i < width; i++) {
		gotoXY(top + height, left + i + 1);
		cout << char(205);
	}
	cout << char(188);
	for (int i = height + top - 1; i > top; i--) {
		gotoXY(i, left + width + 1);
		cout << char(186);
	}
}
void loading(string text) {
	system("cls");
	int width = 40;
	int height = 2;
	int left = 40;
	int top = 9;
	gotoXY(55, 8); cout << text;
	drawBox(width, height, left, top);
	for (int i = 0; i < 40; i++) {
		gotoXY(i + 41, 10); cout << char(219);
		Sleep(10);
	}
	system("cls");
}
void alignRow(int x, int& y, string text, int rowLength) {
	int n = count(text.begin(), text.end(), ' ') + 1;
	string* strArr = new string[n];
	int i = 0;
	stringstream ssin(text);
	while (ssin.good() && i < n) {
		ssin >> strArr[i];
		i++;
	}
	i = 0;
	int s = rowLength;
	while (i < n) {
		gotoXY(x, y);
		rowLength = s;
		while (rowLength > 0 || i < n) {
			cout << strArr[i] << " ";
			rowLength -= (strArr[i].length() + 1);
			i++;
			if (rowLength < (strArr[i].length() + 1)) break;
		}
		y++;
	}
}
void notifyBox(string msg) {
	ShowCur(true);
	system("cls");
	int width = 45;
	int height = 5;
	int left = 40;
	int top = 9;
	int yPos = 11;
	gotoXY(57, 8); cout << "NOTIFICATION";
	alignRow(45, yPos, msg, 37);
	height += (yPos - 11);
	drawBox(width, height, left, top);
	yPos++;
	gotoXY(45, yPos); cout << "Press any key to continue...";
	_getch();
	system("cls");
}
bool confirmBox() {
	ShowCur(true);
	system("cls");
	int width = 40;
	int height = 6;
	int left = 40;
	int top = 8;
	int yPos = 10;
	int curPos = 0;

	do
	{
		system("cls");
		gotoXY(57, 7); cout << "CONFIRM";
		textAlignCenter("Are you sure", left, width, yPos);
		drawBox(width, height, left, top);
		yPos += 2;
		gotoXY(50, yPos); cout << "Yes";
		gotoXY(70, yPos); cout << "No";
		if (curPos == 0) {
			gotoXY(48, yPos); cout << char(175);
			gotoXY(55, yPos); cout << char(174);
		}
		else {
			gotoXY(68, yPos); cout << char(175);
			gotoXY(75, yPos); cout << char(174);
		}
		int key = _getch();
		switch (key) {
		case 13:
			if (curPos == 0) return true;
			else return false;
			break;
		case 224:
			key = _getch();
			switch (key) {
			case 72:
			case 75:
				if (curPos > 0) curPos--;
				else {
					curPos = 1;
				}
				break;
			case 80:
			case 77:
				if (curPos < 1) curPos++;
				else {
					curPos = 0;
				}
				break;
			}
		}
		yPos = 10;
	} while (true);

}

void textAlignCenter(string s, int left, int width, int y) {
	int x = ((width - s.length()) / 2) + left + 1;
	gotoXY(x, y); cout << s;
}
