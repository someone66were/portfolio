#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Person
{
	string surname, group;
	int  ozenka_math, ozenka_physic, ozenka_oaip, srednya_ozenka;
};
bool oaipOzenkaMoreThen9(Person student)
{
	return (student.ozenka_oaip == 9 || student.ozenka_oaip == 10);
}
void enterData(Person student, int kolichestvo_studentov, ofstream& fout)
{
	int i = 0;
	string delimeter = "----------";
	fout;
	for (i; i < kolichestvo_studentov; i++) {
		cout << "Pozalysta, vvedite group of " << i + 1 << " student: ";
		cin >> student.group;
		cout << "Pozalysta, vvedite surname of " << i + 1 << " student: ";
		cin >> student.surname;
		cout << "Pozalysta, vvedite math ozenka of " << i + 1 << " student: ";
		cin >> student.ozenka_math;
		cout << "Pozalysta, vvedite physic ozenka of " << i + 1 << " student: ";
		cin >> student.ozenka_physic;
		cout << "Pozalysta, vvedite oaip ozenka of " << i + 1 << " student: ";
		cin >> student.ozenka_oaip;
		student.srednya_ozenka = (student.ozenka_oaip + student.ozenka_physic + student.ozenka_math) / 3.;
		cout << "Srednya ozenka etogo studenta " << student.srednya_ozenka << endl << delimeter << endl;
		fout << student.group << "\n" << student.surname << "\n" << student.ozenka_math << "\n" << student.ozenka_physic << "\n" << student.ozenka_oaip << "\n" << student.srednya_ozenka << endl << delimeter << endl;
	}
	fout.close();
}
int main()
{
	Person student;
	string int_group, delimeter = "----------";
	int kolichestvo_studentov, chosen_option, i = 0;
	while (true)
	{
		cout << "Chto bi vi hoteli cdelat'?\n1.Perepisat' dannie\n2.Prosmotret' dannie\n3.Dobavit' dannie\n4.Posmotret reshenie IDZ\n0.Vihod\n" << delimeter << endl;
		cin >> chosen_option;
		switch (chosen_option)
		{
		case 1:
		{
			cout << "Ckolko vsego studentov? ";
			cin >> kolichestvo_studentov;
			ofstream fout("laba.txt");
			enterData(student, kolichestvo_studentov, fout);
			break;
		}
		case 2:
		{
			string str;
			ifstream fin("laba.txt");
			if (!fin.is_open())
				cout << "Oshibka!!";
			else
			{
				while (!fin.eof())
				{
					getline(fin, str);
					cout << str << endl;
				}
			}
			break;
		}
		case 3: {
			string str;
			ofstream fout("laba.txt", ios_base::app); //дозапись в файл информации, за это отвечает ios_base::app
			cout << "Ckolko vsego studentov? ";
			cin >> kolichestvo_studentov;
			enterData(student, kolichestvo_studentov, fout);
			break;

		}
		case 4:
		{
			ofstream IDZ("IDZ.txt");
			cout << "Vvedite nomer interesuischei vas gruppi: ";
			cin >> int_group;
			string str;
			int line_number = 0, kolichestvo_studentov = 0;

			ifstream fin("laba.txt"); //открываем файл
			if (!fin.is_open())
				cout << "Oshibka!!";
			else {
				while (!fin.eof()) {
					getline(fin, str);
					switch (line_number)
					{
					case 0: student.group = str; break;
					case 1: student.surname = str;  break;
					case 2: student.ozenka_math = stoi(str); break;
					case 3: student.ozenka_physic = stoi(str); break;
					case 4: student.ozenka_oaip = stoi(str); break;
					case 5: student.srednya_ozenka = stoi(str); break;
					}
					line_number++;
					if (str == delimeter) { //тут проверка на -------, который разделяет между собой всех учеников
						line_number = 0;
						if (student.group == int_group && oaipOzenkaMoreThen9(student))
						{
							cout << student.surname << " imeet ozenky po OAiPY " << student.ozenka_oaip << ". Horoshoya rabota!\n";
							kolichestvo_studentov++;
							IDZ << "Imya: " << student.surname << endl << "Gruppa: " << student.group << endl << "Ozenka po matem: " << student.ozenka_math << endl << "Ozenka po fizike: " << student.ozenka_physic << endl << "Ozenka po OAiPY: " << student.ozenka_oaip << endl << "Srednya ozenka: " << student.srednya_ozenka << endl << delimeter << endl; //выписываем этого ученка в список
						}
					}
				}
			}
			if (kolichestvo_studentov == 0)
				cout << "Ni y kogo net horoshei ozenki po OAiPY!! Ychites', tovarish'i!!\n";
			IDZ.close();
			break;
		}

		case 0:
			cout << "Do svidania!";
			exit(0);
		default:
			cout << "Pozalusta, vvedite chislo mezdu 0 and 5: ";
			cin >> chosen_option;
		}
	}
}
