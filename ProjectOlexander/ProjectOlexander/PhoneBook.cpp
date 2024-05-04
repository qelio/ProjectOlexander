#include "PhoneBook.h"

bool operator < (const Person& person_1, const Person& person_2) {
    if (person_1.compare(person_2) == -1) {
        return true;
    }
    return false;
}

void merge(vector<Person>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Person> L(n1);
    vector<Person> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Person>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

PhoneBook::PhoneBook() {

}

PhoneBook::PhoneBook(PhoneBook& p) {
    contacts.clear();
    for (Person person : p.getPersons()) {
        contacts.push_back(person);
    }
}

PhoneBook::~PhoneBook() {
	contacts.clear();
}

void PhoneBook::add(const Person& person) {
	contacts.push_back(person);
}

vector<Person> PhoneBook::getPersons() {
    return contacts;
}

void PhoneBook::sorting() {
	mergeSort(contacts, 0, contacts.size() - 1);
}

void PhoneBook::addToSorted(const Person& person) {
	contacts.push_back(person);
	mergeSort(contacts, 0, contacts.size() - 1);
}


bool PhoneBook::write(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) const {
	int person_count = 1;
    bool success = false;
	for (Person person : contacts) {
		if (person.check(last_name, first_name, patronymic, day, month, year, phone_number)) {
			cout << "Information about the person under condition #" << person_count << ":" << endl;
			person.write();
			cout << endl;
			person_count += 1;
            success = true;
		}
	}
    return success;
}

bool PhoneBook::remove(string last_name, string first_name, string patronymic, string day, string month, string year, string phone_number) {
	bool flag = false;
    bool success = false;
	while (!flag) {
		int person_count = 0;
		flag = true;
		for (Person person : contacts) {
            vector<Person>::iterator it_begin = contacts.begin();
			if (person.check(last_name, first_name, patronymic, day, month, year, phone_number)) {
				flag = false;
				contacts.erase(it_begin + person_count);
				person_count += 1;
                success = true;
				break;
			}
			person_count += 1;
		}
	}
    return success;
}

int PhoneBook::getBirthday() const {
    vector<int> days_birth;
    for (Person person : contacts) {
        days_birth.push_back(person.daysBeforeBirthday());
    }
    return *min_element(days_birth.begin(), days_birth.end());
}