/*******************************************************************************
 * Filename: student.cpp
 * Author  : Saagar Shah
 * Version : 1.0
 * Date    : Sept 15, 2023
 * Description: Creates as student class and implements it, finding all students failing.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student{
	private:
		string first_; //String variable for first name
		string last_; //String variable for last name
		float gpa_; //Float variable for gpa
		int id_; //Int variable for id
	public:
		string full_name() const{ //Returns the full name
			return first_ + " " + last_;
		}

		int id() const{ //Returns the id
			return id_;
		}

		float gpa() const{ //Returns the gpa
			return gpa_;
		}

		void print_info() const{ //Prints player info. Ex: John Doe, GPA: 3.4, ID: 123456
			cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: " << id_ << endl;
		}

		Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}; //Constructor for student class

};

vector<Student> find_failing_students(const vector<Student> &students) { //Finds failing students
vector<Student> failing_students; //Vector to store failing students
for (auto it = students.cbegin(); it != students.cend(); it ++){ //Iterates through each student in the vector
	if((*it).gpa() < 1.0){ //Checks gpa
		failing_students.push_back(*it); //Adds student to failing students list if gpa is below 1.0
	}
}
return failing_students; //Returns failing student vector
}

void print_students(const vector<Student> &students){ //Prints students
	for (auto it = students.cbegin(); it != students.cend(); it ++){ //Iterates through the vector of students
		(*it).print_info(); //Prints the current student
	}
}

int main() {
string first_name, last_name;
float gpa;
int id;
char repeat;
vector<Student> students;
do {
cout << "Enter student's first name: ";
cin >> first_name;
cout << "Enter student's last name: ";
cin >> last_name;
gpa = -1;
while (gpa < 0 || gpa > 4) {
cout << "Enter student's GPA (0.0-4.0): ";
cin >> gpa;
}
cout << "Enter student's ID: ";
cin >> id;
students.push_back(Student(first_name, last_name, gpa, id));
cout << "Add another student to database (Y/N)? ";
cin >> repeat;
} while (repeat == 'Y' || repeat == 'y');
cout << endl << "All students:" << endl;
print_students(students);
cout << endl << "Failing students:";
vector<Student> failing_students = find_failing_students(students);
if (failing_students.size() == 0){
	cout << " None" << endl;
}else{
	cout << endl;
	print_students(failing_students);
}
return 0;
}

