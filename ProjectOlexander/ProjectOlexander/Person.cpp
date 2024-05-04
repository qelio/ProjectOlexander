#include "Person.h"

Person::Person(string last_name, string first_name, string patronymic, int day, int month, int year, string phone_number) {
    this->last_name = last_name;
    this->first_name = first_name;
    this->patronymic = patronymic;
    this->day = day;
    this->month = month;
    this->year = year;
    this->phone_number = phone_number;
}

Person::Person() {
    this->last_name = "There is no value";
    this->first_name = "There is no value";
    this->patronymic = "There is no value";
    this->day = 0;
    this->month = 0;
    this->year = 0;
    this->phone_number = "There is no value";
}

Person::~Person() {
    this->last_name = "";
    this->first_name = "";
    this->patronymic = "";
    this->day = 0;
    this->month = 0;
    this->year;
    this->phone_number = "";
}

string Person::getLastName() const {
    return last_name;
}

string Person::getFirstName() const {
    return first_name;
}

string Person::getPatronymic() const {
    return patronymic;
}

int Person::getDay() const {
    return day;
}

int Person::getMonth() const {
    return month;
}

int Person::getYear() const {
    return year;
}

string Person::getPhoneNumber() const {
    return phone_number;
}

bool Person::readFromKeyboard() {
    string last_name, first_name, patronymic, date_birthday;
    int day, month, year;
    string phone_number;
    cout << "Enter your last name, first name and patronymic: ";
    cin >> last_name >> first_name >> patronymic;
    cout << "Enter the date of birth (in the format DD.MM.YYYY): ";
    cin >> date_birthday;
    cout << "Enter the phone number (in the format +XXXXXX...XXX): ";
    cin >> phone_number;
    if (!(checkCorrectLFP(last_name) && checkCorrectLFP(first_name) && checkCorrectLFP(patronymic))) {
        cout << "Incorrect surname, first name or patronymic have been entered!" << endl;
        cin.ignore();
        return false;
    }
    else if (!checkCorrectStringDate(date_birthday)) {
        cout << "An incorrect date of birth has been entered!" << endl;
        cin.ignore();
        return false;
    }
    if (!checkCorrectNumber(phone_number)) {
        cout << "An incorrect phone number has been entered!" << endl;
        cin.ignore();
        return false;
    }
    vector<int> birthday_comma;
    vector<int> birthday;
    for (int i = 0; i < date_birthday.size(); i++) {
        if (date_birthday[i] == '.') {
            birthday_comma.push_back(i);
        }
    }
    string s_day = "", s_month = "", s_year = "";
    for (int i = 0; i <= birthday_comma[0]; i++) {
        s_day += date_birthday[i];
    }
    for (int i = birthday_comma[0] + 1; i <= birthday_comma[1]; i++) {
        s_month += date_birthday[i];
    }
    for (int i = birthday_comma[1] + 1; i < date_birthday.size(); i++) {
        s_year += date_birthday[i];
    }
    day = stoi(s_day);
    month = stoi(s_month);
    year = stoi(s_year);
    if (!checkCorrectDate(day, month, year)) {
        cout << "An incorrect date of birth has been entered!" << endl;
        cin.ignore();
        return false;
    }
    this->last_name = last_name;
    this->first_name = first_name;
    this->patronymic = patronymic;
    this->day = day;
    this->month = month;
    this->year = year;
    this->phone_number = phone_number;
    cin.ignore();
    return true;
}

bool Person::readFromFile(string filename) {
    string cur_str;
    ifstream file(filename); 
    if (!file.is_open()) {
        return false;
    }
    getline(file, cur_str);
    vector<int> spaces;
    for (int i = 0; i < cur_str.size(); i++) {
        if (cur_str[i] == ' ') {
            spaces.push_back(i);
        }
    }
    if (spaces.size() != 4) {
        return false;
    }
    string last_name = "", first_name = "", patronymic = "", date_birthday = "";
    int day, month, year;
    string phone_number = "";
    for (int i = 0; i < spaces[0]; i++) {
        last_name += cur_str[i];
    }
    for (int i = spaces[0] + 1; i < spaces[1]; i++) {
        first_name += cur_str[i];
    }
    for (int i = spaces[1] + 1; i < spaces[2]; i++) {
        patronymic += cur_str[i];
    }
    for (int i = spaces[2] + 1; i < spaces[3]; i++) {
        date_birthday += cur_str[i];
    }
    for (int i = spaces[3] + 1; i < cur_str.size(); i++) {
        phone_number += cur_str[i];
    }
    // cout << last_name.size() << " " << first_name << " " << patronymic;
    if (!(checkCorrectLFP(last_name) && checkCorrectLFP(first_name) && checkCorrectLFP(patronymic))) {
        cout << "Incorrect surname, first name or patronymic have been entered!" << endl;
        return false;
    }
    else if (!checkCorrectStringDate(date_birthday)) {
        cout << "An incorrect date of birth has been entered!" << endl;
        return false;
    }
    if (!checkCorrectNumber(phone_number)) {
        cout << "An incorrect phone number has been entered!" << endl;
        return false;
    }
    vector<int> birthday_comma;
    vector<int> birthday;
    for (int i = 0; i < date_birthday.size(); i++) {
        if (date_birthday[i] == '.') {
            birthday_comma.push_back(i);
        }
    }
    string s_day = "", s_month = "", s_year = "";
    for (int i = 0; i <= birthday_comma[0]; i++) {
        s_day += date_birthday[i];
    }
    for (int i = birthday_comma[0] + 1; i <= birthday_comma[1]; i++) {
        s_month += date_birthday[i];
    }
    for (int i = birthday_comma[1] + 1; i < date_birthday.size(); i++) {
        s_year += date_birthday[i];
    }
    day = stoi(s_day);
    month = stoi(s_month);
    year = stoi(s_year);
    if (!checkCorrectDate(day, month, year)) {
        cout << "An incorrect date of birth has been entered!" << endl;
        return false;
    }
    this->last_name = last_name;
    this->first_name = first_name;
    this->patronymic = patronymic;
    this->day = day;
    this->month = month;
    this->year = year;
    this->phone_number = phone_number;
    file.close();
    return true;
}

bool Person::readFromString(string cur_str) {
    vector<int> spaces;
    for (int i = 0; i < cur_str.size(); i++) {
        if (cur_str[i] == ' ') {
            spaces.push_back(i);
        }
    }
    if (spaces.size() != 4) {
        return false;
    }
    string last_name = "", first_name = "", patronymic = "", date_birthday = "";
    int day, month, year;
    string phone_number = "";
    for (int i = 0; i < spaces[0]; i++) {
        last_name += cur_str[i];
    }
    for (int i = spaces[0] + 1; i < spaces[1]; i++) {
        first_name += cur_str[i];
    }
    for (int i = spaces[1] + 1; i < spaces[2]; i++) {
        patronymic += cur_str[i];
    }
    for (int i = spaces[2] + 1; i < spaces[3]; i++) {
        date_birthday += cur_str[i];
    }
    for (int i = spaces[3] + 1; i < cur_str.size(); i++) {
        phone_number += cur_str[i];
    }
    if (!(checkCorrectLFP(last_name) && checkCorrectLFP(first_name) && checkCorrectLFP(patronymic))) {
         // cout << "Incorrect surname, first name or patronymic have been entered!" << endl;
        return false;
    }
    else if (!checkCorrectStringDate(date_birthday)) {
        // cout << "An incorrect date of birth has been entered!" << endl;
        return false;
    }
    if (!checkCorrectNumber(phone_number)) {
        // cout << "An incorrect phone number has been entered!" << endl;
        return false;
    }
    vector<int> birthday_comma;
    vector<int> birthday;
    for (int i = 0; i < date_birthday.size(); i++) {
        if (date_birthday[i] == '.') {
            birthday_comma.push_back(i);
        }
    }
    string s_day = "", s_month = "", s_year = "";
    for (int i = 0; i <= birthday_comma[0]; i++) {
        s_day += date_birthday[i];
    }
    for (int i = birthday_comma[0] + 1; i <= birthday_comma[1]; i++) {
        s_month += date_birthday[i];
    }
    for (int i = birthday_comma[1] + 1; i < date_birthday.size(); i++) {
        s_year += date_birthday[i];
    }
    day = stoi(s_day);
    month = stoi(s_month);
    year = stoi(s_year);
    if (!checkCorrectDate(day, month, year)) {
        // cout << "An incorrect date of birth has been entered!" << endl;
        return false;
    }
    this->last_name = last_name;
    this->first_name = first_name;
    this->patronymic = patronymic;
    this->day = day;
    this->month = month;
    this->year = year;
    this->phone_number = phone_number;
    return true;
}

void Person::write() const {
    cout << "FCs: " << last_name << " " << first_name << " " << patronymic << endl;
    string s_day = (day < 10) ? "0" + to_string(day) : to_string(day);
    string s_month = (month < 10) ? "0" + to_string(month) : to_string(month);
    cout << "Date of birth: " << s_day << "." << s_month << "." << year << endl;
    cout << "Phone number: " << phone_number << endl;
}

int Person::compare(const Person& other) const {
    string fcs_1 = this->last_name + this->first_name + this->patronymic;
    string fcs_2 = other.last_name + other.first_name + other.patronymic;
    string date_1 = to_string(this->day) + '.' + to_string(this->month) + '.' + to_string(this->year);
    string date_2 = to_string(other.day) + '.' + to_string(other.month) + '.' + to_string(other.year);
    tm t1 = {};
    istringstream date_s1(date_1);
    date_s1 >> get_time(&t1, "%d.%m.%Y");
    tm t2 = {};
    istringstream date_s2(date_2);
    date_s2 >> get_time(&t2, "%d.%m.%Y");
    if (fcs_1 > fcs_2) {
        return 1;
    }
    else if (fcs_1 < fcs_2) {
        return -1;
    }
    else {
        // cout << mktime(&t1) << " " << mktime(&t2) << endl;
        if (mktime(&t1) < mktime(&t2)) {
            return 1;
        }
        else if (mktime(&t1) > mktime(&t2)) {
            return -1;
        }
    }
    return 0;
}

bool Person::check(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) {
    if (last_name != "*" && last_name != this->last_name) {
        return false;
    }
    if (first_name != "*" && first_name != this->first_name) {
        return false;
    }
    if (patronymic != "*" && patronymic != this->patronymic) {
        return false;
    }
    if (day != "*") {
        if (stoi(day) != this->day) {
            return false;
        }
    }
    if (month != "*") {
        if (stoi(month) != this->month) {
            return false;
        }
    }
    if (year != "*") {
        if (stoi(year) != this->year) {
            return false;
        }
    }
    if (phone_number != "*" && phone_number != this->phone_number) {
        return false;
    }
    return true;
}

int Person::daysBeforeBirthday() const {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* current_date = localtime(&now_time);

    tm birthday_date = *current_date;
    birthday_date.tm_mday = this->day;
    birthday_date.tm_mon = this->month - 1;
    time_t birthday_time = mktime(&birthday_date);

    if (now_time > birthday_time) {
        birthday_date.tm_year += 1;
        birthday_time = mktime(&birthday_date);
    }

    double seconds_diff = difftime(birthday_time, now_time);
    int days_diff = seconds_diff / (60 * 60 * 24);
    return days_diff;
}

