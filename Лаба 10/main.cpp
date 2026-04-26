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
using namespace std;


int main(){
	SetConsoleCP(1251); // для того, чтобы в последнем с list нормально выводило текст
	SetConsoleOutputCP(1251);

    const string s = "myla mama ramu b";
	stringstream ss(s); 
	list<string> text;
	copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(text));

	copy(text.begin(), text.end(), ostream_iterator<string>(cout, " "));
	cout << endl; cout << endl;

//Задание: Найти последнее слово в строке, начинающееся с заданной буквы
	cout << endl; cout << endl;
	char ch = 'm';
	auto itb = text.rbegin();//создадим обратные итераторы
	auto ite = text.rend();
	
	bool b = true;
	while (b && itb != ite) {
		if ((*itb)[0] == ch) { 
			b = false;
			cout << "Последнее слово на заданную букву: " << *itb << endl;
		}
		else itb++;
	}

	if (b) cout << "Не найденою." << endl; //либо же можно if(itb==ite)
	cout << endl; cout << endl;



//Задание: Вывести нечётные слова строки в обратном порядке.
	bool flag = text.size() % 2;
	for (auto it = text.rbegin(); it != text.rend(); it++) {
		if (flag) {
			cout << *it << " ", flag = false;
		}
		else {
			flag = true;
		}
	}
	cout << endl; cout << endl;


//Выполнить сортировку контейнера
	text.sort();
	copy(text.begin(), text.end(), ostream_iterator<string>(cout, " "));
	cout << endl; cout << endl;
	cout << endl;



/*2. Дан текстовый файл, содержащий последовательности целых чисел.
Каждая последовательность начинается с новой строки и содержит
произвольное множество значений, значения разделяются запятой: */ //создали текстовый файл nums.txt

//*1Вычислить максимум и минимум каждой последовательности. Результат вывести в форме таблицы : номер строки, максимум, минимум.
//
//*2Найти последовательность с максимальной суммой элементов
	ifstream file1("nums.txt");
	int current_sum = 0; int max_sum = INT_MIN; vector<int>Vmax;//для 2.2
	if (!file1.is_open()) cout << "Файл  не найден!" << endl;
	else {
		cout << setw(10) << "Номер строки " << setw(15) << "Максимальный элемент " << setw(15) << "Минимальный элемент " << endl;

		string line;
		int Linecnt = 0;//2.1

		while (getline(file1, line)) {
			replace(line.begin(), line.end(), ',', ' '); //replace <- метод из библиотеки алгоритм. replace(начало, конец, 'что меняем', 'на что меняем');
			
			stringstream ss(line);
			vector<int> v;
			copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(v)); //заполнили вектор v текущей строкой


			//Вычислить максимум и минимум каждой последовательности. Результат вывести в форме таблицы : номер строки, максимум, минимум.
			if (v.size() != 0) {
				auto minV = min_element(v.begin(), v.end()); //минимальный элемент
				auto maxV = max_element(v.begin(), v.end()); //максимальный элемент 
				cout << setw(5) << ++Linecnt << setw(15) << *maxV << setw(20) << * minV << endl;
			}
			else {
				cout << setw(5) << ++Linecnt << setw(15) << "нет" << setw(20) << "нет" << endl;
			}

			if (v.size()) {
				current_sum = accumulate(v.begin(), v.end(), 0); 
				if (current_sum > max_sum) {
					max_sum = current_sum;
					Vmax = v;
				}
			}
		}
	}
	
	file1.close();
	cout << endl;
	cout << "Максимальная сумма элементов " << max_sum << endl;
	cout << "Последовательность с максимальной суммой элементов: ";
	copy(Vmax.begin(), Vmax.end(), ostream_iterator<int>(cout, " "));
	cout << endl; cout << endl; cout << endl; 



/*3. Рассмотреть примеры, рассмотренные в разделе 8.4 (ассоциативные
контейнеры) электронного учебника. Дан текстовый файл, содержащий
ФИО студентов, разделённые точкой с запятой.*/

//1. Получить множества уникальных фамилий, имён и отчеств set<string>
//2, Для каждого имени посчитать количество студентов с таким именем. Определить отображение map<string, int> name_count.
	set<string> names;
	set<string> surnames;
	set<string> patronyms;
	string str;

	map<string, int> names_counter; //отображение для 3.2

	ifstream file2("names.txt");
	if (file2.is_open()) {
		while (getline(file2, str, ';')) {
			stringstream ss(str);
			string s;
			ss >> s; //взяли фамилию
			surnames.insert(s);

			ss >> s; names.insert(s); //имя 
			names_counter[s]++;//2-ое задание

			ss >> s; patronyms.insert(s); // отчество
		}
	}
	file2.close();
	//Получить множества уникальных фамилий, имён и отчеств set<string>
	cout << "Уникальные имена " << endl;
	for (auto s : names) cout << s << endl; 
	cout << endl;
	cout << "Уникальные фамилии" << endl;
	copy(surnames.begin(), surnames.end(), ostream_iterator<string>(cout, "\n"));
	cout << endl;
	cout << "Уникальные отчества" << endl;
	copy(patronyms.begin(), patronyms.end(), ostream_iterator<string>(cout, "\n"));
	cout << endl;


	//Для каждого имени посчитать количество студентов с таким именем. Определить отображение map<string, int> name_count.
	for (auto p : names_counter) {
		cout << p.first << " - - - -> " << p.second << endl;
	}
	cout << endl; cout << endl;

/*4. Рассмотреть пример построения частотного словаря (электронный
учебник, пример 104). */
	
	ifstream ifs("source.txt");
	if (!ifs.is_open()) {
		cout << "He могу открыть файл словаря " << "source.txt" << endl;
		exit(1);
	}
	typedef istream_iterator<string> string_input;
	vector<string> textе;
	map<string, int> dictionary;
	copy(string_input(ifs), string_input(), back_inserter(textе));
	for (string s : textе) {
		++dictionary[s];
	}
	for (auto s : dictionary) {
		cout << s.first << " - " << s.second<<endl;
	}

	//Дана символьная строка, для букв латинского алфавита построить отображение map<char, int> letter_count.
	string str2 = "Abcd 1 2 3 5 @/, ...";
	
	map<char, int> letter_count;
	vector<char> c;
	copy(str2.begin(), str2.end(), back_inserter(c));
	for (char s : c) {
		if (tolower(s) >= 'a' && tolower(s) <= 'z') {
			++letter_count[s];
		}
		else {

		}
	}
	for (auto s : letter_count) {
		cout << s.first << " - " << s.second << endl;
	}cout << endl; cout << endl;


	//реализация через лямбда-функцию //БЕЗ ЦИКЛОВ
	string str3 = "Abcd 1 2 3 5 @/, ...";

	map<char, int> letter_count2;
	vector<char> c1;
	copy_if(str3.begin(), str3.end(), back_inserter(c1), [](char ch) {return tolower(ch) >= 'a' && tolower(ch) <= 'z'; });
	copy(c1.begin(), c1.end(), ostream_iterator<char>(cout, " "));
	transform(c1.begin(), c1.end(), c1.begin(), tolower);
	cout << endl;
	copy(c1.begin(), c1.end(), ostream_iterator<char>(cout, " "));
	for (auto s : c1) {
		++letter_count2[s];
	}
	for (auto p : letter_count2) {
		cout << p.first << " " << p.second << endl;
	}




}


