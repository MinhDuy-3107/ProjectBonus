
#pragma once // tránh đụng độ thư viện khi gọi chồng file lên nhau
#include <stdio.h>
#include"Global.h"
#include <conio.h>
#include<Windows.h>
#include<ctime> /* thư viện hỗ trợ về thời gian thực */
//======= lấy tọa độ x của con trỏ hiện tại =============
#define KEY_NONE -1

int whereX();//========= lấy tọa độ y của con trỏ hiện tại =======
int whereY();//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(int x, int y);
void gotoxy(int x, int y);
//============= đặt màu cho chữ =========
void SetColor(WORD color);
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility);
//======= trả về mã phím người dùng bấm =========
int inputKey();
//================ đặt màu chữ và nền =================== 
void textcolor(int x);
// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height);
// Hàm xóa màn hình.
void XoaManHinh();
void drawBox(int width, int height, int left, int top);
void loading(string text);
void notifyBox(string msg);
bool confirmBox();
void alignRow(int x, int& y, string text, int rowLength);
void textAlignCenter(string s, int left, int width, int y);
