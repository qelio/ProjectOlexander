#include "Functions.h"

bool checkCorrectLFP(string check_in) {
    string correct = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
    for (int i = 0; i < check_in.size(); i++) {
        bool flag = false;
        for (int j = 0; j < correct.size(); j++) {
            if (check_in[i] == correct[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

bool checkCorrectNumber(string phone_number) {
    if (phone_number[0] != '+') {
        return false;
    }
    string correct = "1234567890";
    for (int i = 1; i < phone_number.size(); i++) {
        bool flag = false;
        for (int j = 0; j < correct.size(); j++) {
            if (phone_number[i] == correct[j]) {
                flag = true;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

bool checkLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    }
    else if (year % 100 == 0) {
        return false;
    }
    else if (year % 4 == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool checkCorrectDate(int day, int month, int year) {
    if (!(day > 0 && day < 32)) {
        return false;
    }
    if (!(month > 0 && month < 13)) {
        return false;
    }
    if ((day == 31) && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) {
        return false;
    }
    if (!checkLeapYear(year) && day >= 29 && month == 2) {
        return false;
    }
    if (checkLeapYear(year) && day > 29 && month == 2) {
        return false;
    }
    if (year < 1) {
        return false;
    }
    return true;
}

bool checkCorrectStringDate(string date_birthday) {
    int count_comma = 0;
    for (int i = 0; i < date_birthday.size(); i++) {
        if (date_birthday[i] == '.') {
            count_comma += 1;
        }
    }
    if (count_comma != 2) {
        return false;
    }
    return true;
}

