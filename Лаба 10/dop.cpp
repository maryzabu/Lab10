#include <sstream>
#include <iostream>
#include <algorithm>
#include <list> //для списков
#include <Windows.h> //для корректного отображения русских букв
#include <fstream> //для работы с файловым потоком
#include <set> //для работы со множествами
#include <vector>

#include <iomanip>//для форматирования
#include <numeric>//для задания 2.2
#include <map>//для задания 3.2
int s = 0;
bool pr(int a) {
	return a < 7;
}

void sum(int a) {
	s += a;
}
int main() {
	//дополнение
	vector<int> v3 = { 1, 12, -4 };
	cout << count_if(v3.begin(), v3.end(), pr);

}