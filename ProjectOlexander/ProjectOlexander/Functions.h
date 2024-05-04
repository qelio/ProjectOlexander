#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Person.h"

using namespace std;

bool checkCorrectLFP(string check_in);

bool checkCorrectNumber(string phone_number);

bool checkLeapYear(int year);

bool checkCorrectDate(int day, int month, int year);

bool checkCorrectStringDate(string date_birthday);


