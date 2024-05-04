#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Functions.h"

using namespace std;

class Person {
private:
    string last_name, first_name, patronymic;
    int day, month, year;
    string phone_number;
public:
    Person(string last_name, string first_name, string patronymic, int day, int month, int year, string phone_number);

    Person();

    ~Person();

    string getLastName() const;

    string getFirstName() const;

    string getPatronymic() const;

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    string getPhoneNumber() const;

    bool readFromKeyboard();

    bool readFromFile(string filename);

    bool readFromString(string cur_str);

    void write() const;

    int compare(const Person& other) const;

    bool check(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number);

    int daysBeforeBirthday() const;

};