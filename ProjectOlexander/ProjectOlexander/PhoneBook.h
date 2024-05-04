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
#include "Person.h"
#include "Functions.h"
using namespace std;

bool operator < (const Person& person_1, const Person& person_2);

void merge(vector<Person>& arr, int left, int mid, int right);

void mergeSort(vector<Person>& arr, int left, int right);

class PhoneBook {
private:
    vector<Person> contacts;

public:
    PhoneBook();

    PhoneBook(PhoneBook& p);

    ~PhoneBook();

    void add(const Person& person);

    void sorting();

    void addToSorted(const Person& person);

    vector<Person> getPersons();

    bool write(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) const;

    bool remove(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number);

    int getBirthday() const;
};