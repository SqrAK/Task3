#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include "Date.h"



class Order {
public:

	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	Order(std::string aname, std::string atype, std::string aunit, int apriceForOne, Date atime, int avolume)
	{
		name = aname;
		type = atype;
		unit = aunit;
		priceForOne = apriceForOne;
		time = atime;
		volume = avolume;
	}

	Order()
	{
		name = "";
		type = "";
		unit = "";
		priceForOne = 0;
		time = Date();
		volume = 0;
	}

	~Order()
	{
	}

	bool operator==(const Order& right) const
	{
		return	this->name == right.name;
	}

	bool operator < (const Order &ord)
	{
		return this->name == ord.name;
	}
};


std::ostream& operator <<(std::ostream &os, const Order &ord) {
	os << ord.name + "\t" +
		ord.type + "\t" +
		ord.unit + "\t" +
		std::to_string(ord.priceForOne) + "\t";
	os << ord.time;
	os << "\t" + std::to_string(ord.volume) << "\n";
	return os;
}

std::istream& operator >> (std::istream& is, Order &ord)
{
	is >> ord.name;
	is >> ord.type;
	is >> ord.unit;
	is >> ord.priceForOne;
	std::string str1;
	std::string str2;
	is >> str1;
	is >> str2;
	Date::StrToDate(str1 + " " + str2, ord.time);
	is >> ord.volume;

	return is;
}

Order inputOrder();

//Predicats and Comparators

class NamePred
{
protected:
	std::string name;

public:
	NamePred(std::string n)
	{
		name = n;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.name == name;
	}
};


class TypePred
{
protected:
	std::string type;

public:
	TypePred(std::string s)
	{
		type = s;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.type == type;
	}
};



class DatePred
{
protected:
	Date date;

public:
	DatePred(Date s)
	{
		date = s;
	}

	bool virtual operator  () (Order ord)
	{
		return ord.time == date;
	}
};

class NameComp
{
public:
	bool operator () (Order ord1, Order ord2)
	{
		return ord1.name < ord2.name;
	}
};


class TypeComp
{
public:
	bool virtual operator () (Order ord1, Order ord2)
	{
		return ord1.type < ord2.type;
	}
};


class DateComp
{
public:
	bool virtual operator () (Order ord1, Order ord2)
	{
		return ord1.time < ord2.time;
	}
};


class NameAcc
{
protected:
	std::string str;
	std::vector<Order>* v;

public:
	NameAcc(std::string s)
	{
		str = s;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.name == str)
			(*v).push_back(ord);
	}
};


class TypeAcc
{
protected:
	std::string str;
	std::vector<Order>* v;

public:
	TypeAcc(std::string s)
	{
		str = s;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.type == str)
			(*v).push_back(ord);
	}
};



class DateAcc
{
protected:
	Date date;
	std::vector<Order>* v;

public:
	DateAcc(Date d)
	{
		date = d;
		v = new std::vector<Order>();
	}

	std::vector<Order> getSet()
	{
		return *v;
	}

	void virtual operator () (Order ord)
	{
		if (ord.time == date)
			(*v).push_back(ord);
	}
};

class CountAllPrice
{
protected:
	int count;

public:
	CountAllPrice(int c)
	{
		count = c;
	}

	void virtual operator () (Order ord)
	{
		count = count + ord.priceForOne*ord.volume;
	}

	int getCount()
	{
		return count;
	}

};



template <class O>
class Abs�ontainer
{
public:

	Abs�ontainer(int size)
	{
		vect = std::vector<O>(size);
	}

	Abs�ontainer()
	{
		vect = std::vector<O>();
	}

	~Abs�ontainer() {}

	void add(O ord) {
		vect.push_back(ord);
	}


	bool find(O ord, std::random_access_iterator_tag &it)
	{
		it = std::find(vect.begin(), vect.end(), ord);
		return it != vect.end()
	}

	bool find(O ord)
	{
		std::vector<O>::iterator it =
			std::find(vect.begin(), vect.end(), ord);
		return it != vect.end();
	}

	template<class Predicate>
	bool findBy(Predicate &pred, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> &it)
	{
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> tmpIt;
		tmpIt = std::find_if(vect.begin(), vect.end(), pred);
		if (tmpIt == vect.end())
			return false;
		it = tmpIt;
		return true;
	}
	
	template<class Comparator>
	bool findByBinary(Comparator &comp, O &bibb, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> &it)
	{
		std::sort(vect.begin(), vect.end(), comp);
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<O>>> tmpIt;
		tmpIt = std::lower_bound(vect.begin(), vect.end(), bibb, comp);
		if (tmpIt == vect.end() || comp(bibb, *tmpIt))
			return false;
		it = tmpIt;
		return true;
	}

	template<class Accomulator>
	std::vector<O> findSubSetBy(Accomulator acc)
	{
		std::for_each(vect.begin(), vect.end(), acc);
		return acc.getSet();
	}


	int size()
	{
		return vect.size();
	}

	void clear()
	{
		vect.clear();
	}

protected:
	std::vector<O> vect;
};



void inputOrderChange(std::vector<Order>::iterator &it);
class �ontainer : public Abs�ontainer<Order>
{
public:
	�ontainer(std::vector<Order> v)
	{
		vect = v;
	}

	�ontainer()
	{
		vect = std::vector<Order>();
	}

	void remove(std::vector<Order>::iterator it) {
		vect.erase(it);
	}

	void change(std::vector<Order>::iterator &it) {
		inputOrderChange(it);
	}


	bool findByName(std::string name, std::vector<Order>::iterator &it)
	{
		NamePred &pred = NamePred(name);
		return findBy(pred, it);
	}

	bool findByType(std::string type, std::vector<Order>::iterator &it)
	{
		TypePred pred = TypePred(type);
		return findBy(pred, it);
	}

	bool findByDate(Date date, std::vector<Order>::iterator &it)
	{
		DatePred pred = DatePred(date);
		return findBy(pred, it);
	}

	bool findByNameBinary(std::string name, std::vector<Order>::iterator &it)
	{
		NameComp comp = NameComp();
		Order bibb = Order(name, "", "", 0, Date(), 0);
		return findByBinary(comp, bibb, it);
	}


	bool findByTypeBinary(std::string type, std::vector<Order>::iterator &it)
	{
		TypeComp comp = TypeComp();
		Order bibb = Order("", type, "", 0, Date(), 0);
		return findByBinary(comp, bibb, it);
	}

	bool findByDateBinary(Date date, std::vector<Order>::iterator &it)
	{
		DateComp comp = DateComp();
		Order bibb = Order("", "", "", 0, date, 0);
		return findByBinary(comp, bibb, it);
	}


	�ontainer findSubSetByName(std::string s)
	{
		NameAcc acc = NameAcc(s);
		return �ontainer(findSubSetBy(acc));
	}

	�ontainer findSubSetByType(std::string s)
	{
		TypeAcc acc = TypeAcc(s);
		return �ontainer(findSubSetBy(acc));
	}

	�ontainer findSubSetByDate(Date d)
	{
		DateAcc acc = DateAcc(d);
		return �ontainer(findSubSetBy(acc));
	}


	void fileInput(std::fstream& fin) {

		if (fin.is_open()) {
			try
			{
				std::istream_iterator<Order> is(fin);
				vect.clear();
				Order ord = *is++;

				while (!fin.fail() && !fin.eof()) {
					add(ord);
					ord = *is++;
				}
				/*	add(ord);*/
			
				if (fin.eof() && ord.name != "")
					add(ord);
			}
			catch(...)
			{
				std::cout << "������ ���������!" << std::endl;
			}
			fin.close();
		}
		else
			std::cout << "���� �� ����������!" << std::endl;
	}

	void fileOutput(std::fstream& fout) {
		if (fout.is_open()) {
			copy(vect.begin(), vect.end(), std::ostream_iterator<Order>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "������ �������� �����!" << std::endl;
	}



	void output(std::ostream_iterator<Order> os)
	{
		copy(vect.begin(), vect.end(), os);
	}

	int countPrice()
	{
		CountAllPrice count = CountAllPrice(0);
		for (auto v : vect) count(v);
		return count.getCount();
	}
};





//-----------------helpers------------------

static void printHead();

void consoleInput(�ontainer& cont) {
	cont.clear();
	Order ord;
	while (true) {
		try {
			ord = inputOrder();

		}
		catch (const char* str) {
			return;

		}

		cont.add(ord);

	}

}

void consoleOutput(�ontainer& cont)
{
	if (cont.size() != 0)
	{
		printHead();
		cont.output(std::ostream_iterator<Order>(std::cout, "\n"));
	}
	else
	{
		std::cout << "�����\n";
	}
}



int inputInt(std::string message = "", bool isAdd = false, int min = 0, int max = 10000) {
	std::string str;
	int res;

	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "skip" && !isAdd) return -1;
			if (str == "exit") throw "exit";
			res = std::stoi(str);
			while (res < min || res > max) {	
				
				std::cout << "������ (�������� < " << min << " ��� �������� > " << max << "). ������: ";
				std::cin >> str;
				if (str == "skip" && !isAdd) return -1;
				res = std::stoi(str);
			
			}
			return res;
		}
		catch (std::exception &e) {
			std::cout << "������! ����������� ������� �����" << std::endl;
		}
	}
}

Date inputDate(bool isAdd = false, std::string message = "Input date in format hh:mm dd/mm/yyyy : ") {

	Date date = Date();

	std::string buf1;
	std::string buf2;
	bool ok = false;
	while (!ok)
	{
		std::cout << message;
		std::cin >> buf1;
		if (buf1 == "skip" && !isAdd) return Date();
		if (buf1 == "exit") throw "exit";
		std::cin >> buf2;
		ok = Date::StrToDate(buf1 + " " + buf2, date);
		if (!ok)
			std::cout << "�������� ����!!!!";
	}
	return date;
}

Order inputOrder()
{
	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	std::cout << "-------------�����-------------" << std::endl;
	std::cout << "������� \"exit\" ��� ������" << std::endl;

	std::cout << "������� �������� �����: ";
	std::cin >> name;
	if (name == "exit") throw "exit";

	std::cout << "������� ��� �����: ";
	std::cin >> type;
	if (type == "exit") throw "exit";

	std::cout << "������� ������� ���������: ";
	std::cin >> unit;
	if (unit == "exit") throw "exit";

	priceForOne = inputInt("������� ��������� ������� ����������� ������: ", true);

	time = inputDate(true);

	volume = inputInt("������� ����� �����: ", true);


	return Order(name, type, unit, priceForOne, time, volume);
}


Order inputOrderAdd(�ontainer &c)
{
	std::string name;
	std::string type;
	std::string unit;
	int priceForOne;
	Date time;
	int volume;

	std::cout << "-------------�����-------------" << std::endl;
	std::cout << "������� \"exit\" ��� ������" << std::endl;

	std::cout << "������� �������� �����: ";
	std::cin >> name;
	if (name == "exit") throw "exit";

	std::cout << "������� ��� �����: ";
	std::cin >> type;
	if (type == "exit") throw "exit";

	std::cout << "������� ������� ���������: ";
	std::cin >> unit;
	if (unit == "exit") throw "exit";

	priceForOne = inputInt("������� ��������� ������� ����������� ������: ", true);

	time = inputDate(true);

	volume = inputInt("������� ����� �����: ", true);


	return  Order(name, type, unit, priceForOne, time, volume);
}


void inputOrderChange(std::vector<Order>::iterator &it)
{
	std::cout << "-------------�����-------------" << std::endl;
	std::cout << "������� \"skip\" ��� ��������" << std::endl;

	std::string StrName;
	std::cout << "������� �������� �����(������: " + it->name + "): ";
	std::cin >> StrName;
	if (StrName != "skip")  it->name = StrName;

	std::string strType;
	std::cout << "������� ��� �����(������: " + it->type + "): ";
	std::cin >> strType;
	if (strType != "skip") it->type = strType;

	std::string strUnit;
	std::cout << "������� ������� ���������(������: " + it->unit + "): ";
	std::cin >> strUnit;
	if (strUnit != "skip") it->unit = strUnit;

	int tmp = inputInt("������� ��������� ������� ����������� ������(������: " + std::to_string(it->priceForOne) + "): ");
	if (tmp != -1) it->priceForOne = tmp;

	std::string curDate = it->time.to_string();
	Date dt = inputDate(false, "������� ���� �� �������(mm:hh dd/mm/yyyy)( ������: " + curDate + ")");
	Date defDt = Date();
	if (!(dt == defDt))
		it->time = dt;


	tmp = inputInt("������� ����� �����( ������: " + std::to_string(it->volume) + "): ");
	if (tmp != -1) it->volume = tmp;

}

static void printHead()
{
	std::cout << "��������\t" << "���\t" << "������� ���������\t" << " ��������� �������\t" << "����\t\t" << "�����\n";
}



