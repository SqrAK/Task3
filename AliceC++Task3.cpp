// C++Task2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Helper.h"

/*
������������ ������ �������������

14. ������ ����� ������������ ���������� � ������: �������� �����, ��� �����, ������� ���������,
��������� ������� ����������� ������, ���� ����������, ����� �����. ����� �� �������� �����, ���� �����, ���� ����������.

*/


void printMainMenu()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " ��������:" << std::endl;
	std::cout << " 1)������� �� �����" << std::endl;
	std::cout << " 2)����� ������" << std::endl;
	std::cout << " 3)�������� ������" << std::endl;
	std::cout << " 4)������������" << std::endl;
	std::cout << " 5)������� ����" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printMenuFindParam()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " �����" << std::endl;
	std::cout << " 1)�� �������� �����" << std::endl;
	std::cout << " 2)�� ���� �����" << std::endl;
	std::cout << " 3)�� ���� ����������" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printMenuSearch()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "��� ������:" << std::endl;
	std::cout << " 1)Simple search" << std::endl;
	std::cout << " 2)Binary search" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printAction()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "�������� � �������:" << std::endl;
	std::cout << " 1)������" << std::endl;
	std::cout << " 2)��������" << std::endl;
	std::cout << " 3)�������" << std::endl;
	std::cout << " 4)�������" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

void printSubSetMenu(int size)
{
	std::cout << " ������ ������������: " << size << "\n";
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)����� �� �����" << std::endl;
	std::cout << " 2)����� � ����" << std::endl;
	std::cout << " 3)������� ����" << std::endl;
	std::cout << " 0)�����" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

bool TryOpenFile(std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}
	file.close();
	return true;
}

std::string inputFileName()
{
	std::string filename;
	std::cout << "������� ��� �����:\n";
	std::cin >> filename;

	while (!TryOpenFile(filename))
	{
		std::cout << "������� ��� �����:\n";
		std::cin >> filename;
	}

	return filename;
}


int main()
{
	setlocale(LC_ALL, "rus");
	bool notEnd = true;
	�ontainer cont = �ontainer();
	�ontainer sub;
	std::string filename;
	std::vector<Order>::iterator it;
	bool fl;
	bool binarSearch;
	bool found;
	std::string str;
	std::string n;
	int c;
	filename = "123";
	cont.fileInput(std::fstream(filename, std::ios::in));

	while (notEnd)
	{
		printMainMenu();
		std::cin >> n;
		c = std::stoi(n);
		switch (c)
		{
		case 1:
			consoleOutput(cont);
			break;
		case 2:
			fl = true;
			while (fl)
			{
				printMenuSearch();
				std::cin >> c;

				switch (c)
				{
				case 1:
					binarSearch = false;
					fl = false;
					break;
				case 2:
					binarSearch = true;
					fl = false;
					break;
				case 0:
					fl = false;
					break;
				default:
					std::cout << "������� ������� �������!!" << std::endl;
					break;
				}

			}
			fl = true;
			while (fl)
			{
				printMenuFindParam();
				std::cin >> c;
				switch (c)
				{
				case 1:
					std::cout << "������� ��������: ";
					std::cin >> str;
					if (binarSearch)
						try
					{
						found = cont.findByName(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByNameBinary(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						while (fl)
						{
							printAction();
							std::cin >> c;

							switch (c)
							{
							case 1:
								std::cout << *it;
								break;
							case 2:
								cont.change(it);
								cont.fileOutput(std::fstream(filename, std::ios::out));
								break;
							case 3:
								cont.remove(it);
								fl = false;
								cont.fileOutput(std::fstream(filename, std::ios::out));
								break;
							case 4:
								std::cout << "�������: " << (it->priceForOne)*(it->volume) << std::endl;
								break;
							case 0:
								fl = false;
								break;
							default:
								std::cout << "������� ������� �������!" << std::endl;
								break;
							}
						}
					}
					else
						std::cout << "������ �� �������\n";
					fl = false;
					break;
				case 3:
					if (binarSearch)
						try
					{
						found = cont.findByDateBinary(inputDate(), it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByDate(inputDate(), it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						while (fl)
						{
							printAction();
							std::cin >> c;

							switch (c)
							{
							case 1:
								std::cout << *it;
								break;
							case 2:
								cont.change(it);
								cont.fileOutput(std::fstream(filename, std::ios::out));
								break;
							case 3:
								cont.remove(it);
								fl = false;
								cont.fileOutput(std::fstream(filename, std::ios::out));
								break;
							case 4:
								std::cout << "�������: " << (it->priceForOne)*(it->volume) << std::endl;
								break;
							case 0:
								fl = false;
								break;
							default:
								std::cout << "����������� ������� �������!" << std::endl;
								break;
							}

						}
					}
					else
						std::cout << "������ �� ������� \n";
					fl = false;
					break;
				case 2:
					std::cout << "������� ���: ";
					std::cin >> str;
					if (binarSearch)
						try
					{
						found = cont.findByTypeBinary(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					else
						try
					{
						found = cont.findByType(str, it);
					}
					catch (const char* str) {
						fl = false;
					}
					if (found)
					{
						std::cout << "������ ������� \n";
						printAction();
						std::cin >> c;

						switch (c)
						{
						case 1:
							std::cout << *it;
							break;
						case 2:
							cont.change(it);
							cont.fileOutput(std::fstream(filename, std::ios::out));
							break;
						case 3:
							cont.remove(it);
							cont.fileOutput(std::fstream(filename, std::ios::out));
							break;
						case 4:
							std::cout << "�������: " << (it->priceForOne)*(it->volume) << std::endl;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}

					}
					else
						std::cout << "������ �� ������� \n";
					fl = false;
					break;
				case 0:
					fl = false;
					break;
				default:
					std::cout << "����������� ������� �������!" << std::endl;
					break;
				}
			}
			break;
		case 3:
			try
			{
				cont.add(inputOrderAdd(cont));
			}
			catch (const char* str) {
				fl = false;
			}
			cont.fileOutput(std::fstream(filename, std::ios::out));
			break;
		case 4:
			fl = true;
			while (fl)
			{
				printMenuFindParam();
				std::cin >> c;
				switch (c)
				{
				case 1:
					std::cout << "������� �������� �����: ";
					std::cin >> str;
					sub = cont.findSubSetByName(str);
					fl = true;
					while (fl)
					{
						if (sub.size() == 0) {
							std::cout << "������������ ������:\n";
							fl = false;
							break;

						}

						printSubSetMenu(sub.size());
						std::cin >> c;
						switch (c)
						{
						case 1:
							consoleOutput(sub);

							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;
							sub.fileOutput(std::fstream(filename, std::ios::out));

							break;
						case 3:
							std::cout << "������� ����: " << sub.countPrice() << std::endl;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}

					}
					break;
				case 3:
					std::cout << "������� ����: ";
					sub = cont.findSubSetByDate(inputDate());
					fl = true;
					while (fl)
					{
						printSubSetMenu(sub.size());
						std::cin >> c;

						switch (c)
						{
						case 1:
							consoleOutput(sub);
							fl = false;
							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;
							sub.fileOutput(std::fstream(filename, std::ios::out));
							fl = false;
							break;
						case 3:
							std::cout << "������� ����: " << sub.countPrice() << std::endl;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}

					}
					break;
				case 2:
					std::cout << "������� ���: ";
					std::cin >> str;
					sub = cont.findSubSetByType(str);
					fl = true;
					while (fl)
					{

						printSubSetMenu(sub.size());
						std::cin >> c;

						switch (c)
						{
						case 1:
							consoleOutput(sub);
							fl = false;
							break;
						case 2:
							std::cout << "������� ��� �����:\n";
							std::cin >> filename;
							sub.fileOutput(std::fstream(filename, std::ios::out));
							fl = false;
							break;
						case 3:
							std::cout << "������� ����: " << sub.countPrice() << std::endl;
							break;
						case 0:
							fl = false;
							break;
						default:
							std::cout << "����������� ������� �������!" << std::endl;
							break;
						}
					}
					break;
				case 0: fl = false;
				}
			}
			break;
		case 5:
			std::cout << "������� ����: " << cont.countPrice() << std::endl;
			break;
		case 0:
			notEnd = false;
			break;
		default:
			std::cout << "����� ������� ���! ��������� ����!" << std::endl;
			break;
		}

	}
	return 0;
}