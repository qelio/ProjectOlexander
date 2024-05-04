#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Person.h"
#include "PhoneBook.h"

using namespace std;

PhoneBook book;

ostream& operator<< (ostream& out, PhoneBook& book) {
    int person_count = 1;
    for (Person person : book.getPersons()) {
        cout << "Information about person #" << person_count << ":" << endl;
        person.write();
        cout << endl;
        person_count += 1;
    }
    if (person_count == 1) {
        cout << "At the moment, there is no data available!" << endl;
    }
    return out;
}

ifstream& operator>> (ifstream& in, PhoneBook& book) {
    string cur_str;
    while (getline(in, cur_str)) {
        Person cur_person;
        if (cur_person.readFromString(cur_str)) {
            book.add(cur_person);
        }
    }
    return in;
}

void help() {
    cout << "\t- help - display a list of commands" << endl;
    cout << "\t- show - display all data" << endl;
    cout << "\t- clear - clear the list" << endl;
    cout << "\t- load <filename> - add a list from a file" << endl;
    cout << "\t- save <filename> - save the list in a file" << endl;
    cout << "\t- add (switches to input mode starting with \" > \") - add an element" << endl;
    cout << "\t- sort - sort" << endl;
    cout << "\t- find <conditions> - display items that meet the conditions" << endl;
    cout << "\t- delete <conditions> - delete items that meet the conditions" << endl;
    cout << "\t- exit - shut down and exit" << endl << endl;
}

void show() {
    cout << book;
}

void clear() {
    book.remove("*", "*", "*", "*", "*", "*", "*");
    cout << "The data has been successfully deleted!" << endl;
}

void add() {
    Person person;
    if (person.readFromKeyboard()) {
        book.add(person);
        cout << "Adding a user is successful!" << endl;
    }
}

void sortings() {
    book.sorting();
    cout << "The data has been successfully sorted!" << endl;
}

void birthday() {
    int person_count = 1;
    int min_day = book.getBirthday();
    for (Person person : book.getPersons()) {
        if (person.daysBeforeBirthday() == min_day) {
            cout << "Information about the person by birthday #" << person_count << ":" << endl;
            cout << "FCs: " << person.getLastName() << " " << person.getFirstName() << " " << person.getPatronymic() << endl;
            string s_day = (person.getDay() < 10) ? "0" + to_string(person.getDay()) : to_string(person.getDay());
            string s_month = (person.getMonth() < 10) ? "0" + to_string(person.getMonth()) : to_string(person.getMonth());
            cout << "Date of birth: " << s_day << "." << s_month << "." << person.getYear() << endl;
            cout << "Phone number: " << person.getPhoneNumber() << endl;
            person_count += 1;
            cout << endl;
        }
    }
}

void load(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> book;
        file.close();
        cout << "Data reading is successful!" << endl;
    }
    else {
        cout << "File opening error!" << endl;
    }
}

void finding(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) {
    if (!book.write(last_name, first_name, patronymic, day, month, year, phone_number)) {
        cout << "No relevant data has been found!" << endl;
    }
}

void deleting(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) {
    if (book.remove(last_name, first_name, patronymic, day, month, year, phone_number)) {
        cout << "Data deletion is successful!" << endl;
    }
    else {
        cout << "No relevant data has been found!" << endl;
    }
}

void save(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (Person person : book.getPersons()) {
            string s_day = (person.getDay() < 10) ? "0" + to_string(person.getDay()) : to_string(person.getDay());
            string s_month = (person.getMonth() < 10) ? "0" + to_string(person.getMonth()) : to_string(person.getMonth());
            file << person.getLastName() << " " << person.getFirstName() << " " << person.getPatronymic() << " " << s_day << "." << s_month << "." << person.getYear() << " " << person.getPhoneNumber() << endl;
        }
        cout << "The data was saved successfully!" << endl;
        file.close();
    }
    else {
        cout << "File opening error!" << endl;
    }
}

int main() {
    while (true) {
        cout << "Enter a command (use help to list commands): ";
        string command;
        getline(cin, command);
        if (command == "help") {
            help();
        }
        else if (command == "clear"){
            clear();
        }
        else if (command == "show") {
            show();
        }
        else if (command == "add") {
            add();
        }
        else if (command == "sort") {
            sortings();
        }
        else if (command == "exit") {
            return 0;
        }
        else if (command == "birthday"){
            birthday();
        }
        else {
            int in_arrows_r = 0, in_arrows_l = 0;
            int arrows_r = 0, arrows_l = 0;
            for (int i = 0; i < command.size(); i++) {
                if (command[i] == '<') {
                    arrows_l += 1;
                    in_arrows_l = i;
                }
                if (command[i] == '>') {
                    arrows_r += 1;
                    in_arrows_r = i;
                }
            }
            if (arrows_l == 1 && arrows_r == 1) {
                if (in_arrows_l < in_arrows_r && in_arrows_r == command.size() - 1) {
                    string in_command = "", arguments = "";
                    for (int i = 0; i <= in_arrows_l - 2; i++) {
                        in_command += command[i];
                    }
                    for (int i = in_arrows_l + 1; i <= in_arrows_r - 1; i++) {
                        arguments += command[i];
                    }
                    if (in_command == "load") {
                        load(arguments);
                    }
                    else if (in_command == "save") {
                        save(arguments);
                    }
                    else if (in_command == "find") {
                        vector<int> spaces;
                        for (int i = 0; i < arguments.size(); i++) {
                            if (arguments[i] == ' ') {
                                spaces.push_back(i);
                            }
                        }
                        if (spaces.size() == 4) {
                            string last_name = "", first_name = "", patronymic = "", date_birthday = "";
                            string day = "", month = "", year = "";
                            string phone_number = "";
                            for (int i = 0; i < spaces[0]; i++) {
                                last_name += arguments[i];
                            }
                            for (int i = spaces[0] + 1; i < spaces[1]; i++) {
                                first_name += arguments[i];
                            }
                            for (int i = spaces[1] + 1; i < spaces[2]; i++) {
                                patronymic += arguments[i];
                            }
                            for (int i = spaces[2] + 1; i < spaces[3]; i++) {
                                date_birthday += arguments[i];
                            }
                            for (int i = spaces[3] + 1; i < arguments.size(); i++) {
                                phone_number += arguments[i];
                            }
                            // cout << last_name.size() << " " << first_name.size() << " " << patronymic.size() << " " << date_birthday.size() << " " << phone_number.size();
                            vector<int> dots;
                            for (int i = 0; i < date_birthday.size(); i++) {
                                if (date_birthday[i] == '.') {
                                    dots.push_back(i);
                                }
                            }
                            if (dots.size() == 2) {
                                for (int i = 0; i < dots[0]; i++) {
                                    day += date_birthday[i];
                                }
                                for (int i = dots[0] + 1; i < dots[1]; i++) {
                                    month += date_birthday[i];
                                }
                                for (int i = dots[1] + 1; i < date_birthday.size(); i++) {
                                    year += date_birthday[i];
                                }
                                finding(last_name, first_name, patronymic, day, month, year, phone_number);
                            }
                            else if (date_birthday == "*") {
                                finding(last_name, first_name, patronymic, "*", "*", "*", phone_number);
                            }
                            else {
                                cout << "Incorrect command!" << endl;
                            }
                        }
                        else {
                            cout << "Incorrect command!" << endl;
                        }
                    }
                    else if (in_command == "delete") {
                        vector<int> spaces;
                        for (int i = 0; i < arguments.size(); i++) {
                            if (arguments[i] == ' ') {
                                spaces.push_back(i);
                            }
                        }
                        if (spaces.size() == 4) {
                            string last_name = "", first_name = "", patronymic = "", date_birthday = "";
                            string day = "", month = "", year = "";
                            string phone_number = "";
                            for (int i = 0; i < spaces[0]; i++) {
                                last_name += arguments[i];
                            }
                            for (int i = spaces[0] + 1; i < spaces[1]; i++) {
                                first_name += arguments[i];
                            }
                            for (int i = spaces[1] + 1; i < spaces[2]; i++) {
                                patronymic += arguments[i];
                            }
                            for (int i = spaces[2] + 1; i < spaces[3]; i++) {
                                date_birthday += arguments[i];
                            }
                            for (int i = spaces[3] + 1; i < arguments.size(); i++) {
                                phone_number += arguments[i];
                            }
                            vector<int> dots;
                            for (int i = 0; i < date_birthday.size(); i++) {
                                if (date_birthday[i] == '.') {
                                    dots.push_back(i);
                                }
                            }
                            if (dots.size() == 2) {
                                for (int i = 0; i < dots[0]; i++) {
                                    day += date_birthday[i];
                                }
                                for (int i = dots[0] + 1; i < dots[1]; i++) {
                                    month += date_birthday[i];
                                }
                                for (int i = dots[1] + 1; i < date_birthday.size(); i++) {
                                    year += date_birthday[i];
                                }
                                deleting(last_name, first_name, patronymic, day, month, year, phone_number);
                            }
                            else if (date_birthday == "*") {
                                deleting(last_name, first_name, patronymic, "*", "*", "*", phone_number);
                            }
                            else {
                                cout << "Incorrect command!" << endl;
                            }
                        }
                        else {
                            cout << "Incorrect command!" << endl;
                        }
                    }
                    else {
                        cout << "Incorrect command!" << endl;
                    }
                }
                else {
                    cout << "Incorrect command!" << endl;
                }
            }
            else {
                cout << "Incorrect command!" << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
