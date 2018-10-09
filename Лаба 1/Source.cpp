#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <iomanip>

using namespace std;

union type
{
	char t_char;
	int t_int;
	float t_float;
	double t_double;
	int64_t t_int64; //под double
};

enum n_type
{
	nt_char,
	nt_int,
	nt_float,
	nt_double
};

int get_dec(string input, int base = 10)
{
	int num(0), offset(0);
	bool negative = false;
	if (input[0] == '-')
	{
		offset = 1;
		negative = true;
	}
	int result(0);

	for (int i = input.length() - 1, mtp(0); i >= 0 + offset; i--, mtp++)
	{
		num = input[i] - '0';
		result += (int)num*pow(base, mtp);
		// cout << (int)input[i] << ' ';
	}

	if (!negative)
		return(result);
	else
		return(-result);
}

void get_bin(int input, int size)
{
	int source = input;
	cout << endl << "[bin] ";
	for (int i = size * 8 - 1; i >= 0; i--)
	{
		cout << ((source >> i) & 1);
		if (i % 8 == 0)
			cout << ' ';
	}
	cout << endl;
	return;
}

void get_bin_float(type source)
{
	cout << "[bin] ";
	for (int i = sizeof(float) * 8 - 1, k = 1; i >= 0; i--, k++)
	{
		cout << ((source.t_int >> i) & 1);
		if ((k == 1) || (k == 9))
		{
			cout << ' ';
		}
	}
	cout << endl;
	return;
}

void get_bin_double(type source)
{
	cout << "[bin] ";
	for (int i = sizeof(double) * 8 - 1, k = 1; i >= 0; i--, k++)
	{
		cout << ((source.t_int64 >> i) & 1);
		if ((k == 1) || (k == 12))
		{
			cout << ' ';
		}
	}
	cout << endl;
	return;
}

void set_bit(type *p_source, int value, int pos)
{
	p_source->t_int64 = (p_source->t_int64 & ~(1 << pos)) | (value << pos);
	return;
}


int main()
{
	setlocale(0, "");

	type temp;

	char sign[] = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; //ASCII
	string input = "";
	int num, base;
	cout << "Выберите тип данных:" << endl << "1. char" << endl
		<< "2. int" << endl << "3. float" << endl << "4. double" << endl;

	do
	{
		cin >> num;
		if ((num < 1) || (num > 4))
			cout << "Типа под таким номером не предусмотрено. Попробуйте еще раз." << endl;
	} while ((num < 1) || (num > 4));
	num--;

	system("cls");

	if ((num == nt_char) || (num == nt_int))
	{
		cout << "Введите основание системы счисления, в которой будет производиться ввод (1-79): ";

		do
		{
			cin >> base;
			if ((base > 79) || (base < 1))
				cout << "Недопустимое основание системы счисления. Попробуйте еще раз." << endl;
		} while ((base > 79) || (base < 1));

		system("cls");
		if (base > 10)
			for (int i(0); i < base; i++)
			{
				cout << setw(3) << right << i << "=" << setw(3) << left << sign[i];
				if ((i + 1) % 5 == 0)
					cout << endl;
			}
		cout << endl;
		cout << "Введите число: ";
		cin >> input;
		//		cout << input.size();
	}

	if ((num == nt_float) || (num == nt_double))
		cout << "Введите число: ";

	int res(0), ch, pos, value;
	switch (num)
	{
	case nt_char:
		res = get_dec(input, base);
		if ((res < -128) || (res > 127))
		{
			cout << "Переполнение типа char.";
			_getch();
			return 1;
		}
		cout << "[dec] " << res;
		get_bin(res, sizeof(char));
		break;
	case nt_int:
		res = get_dec(input, base);
		cout << "[dec] " << res;
		get_bin(res, sizeof(char));
		break;
	case nt_float:
		cin >> temp.t_float;
		cout /*<< setw(6)*/ << right << "[dec] " << temp.t_float << endl;
		get_bin_float(temp);
		cout << "Изменить конкретный бит?" << endl << "1. Нет" << endl << "2. Да" << endl;
		cin >> ch;
		do
		{
			if (ch - 1)
			{
				cout << "Введите номер бита и желаемое значение: ";
				cin >> pos >> value;
				set_bit(&temp, value, pos);
				cout << "[dec]" << temp.t_float << endl;
				get_bin_float(temp);
			}
			else
				break;
			cout << "Для продолжения нажмите любую клавишу, для выхода нажмите Esc." << endl;
		} while (_getch() != 27);
		break;
	case nt_double:
		cin >> temp.t_double;
		cout << right << "[dec] " << temp.t_double << endl;
		get_bin_double(temp);
		cout << "Изменить конкретный бит?" << endl << "1. Нет" << endl << "2. Да" << endl;
		cin >> ch;
		do
		{
			if (ch - 1)
			{
				cout << "Введите номер бита и желаемое значение: ";
				cin >> pos >> value;
				set_bit(&temp, value, pos);
				cout << "[dec]" << temp.t_double << endl;
				get_bin_double(temp);
			}
			else
				break;
			cout << "Для продолжения нажмите любую клавишу, для выхода нажмите Esc.";
		} while (_getch() != 27);
	default:
		break;
	}

	_getch();
	return 0;
}