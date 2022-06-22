#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

//Create a new student with the given name
//DO NOT MODIFY THIS CONSTRUCTOR
Student::Student(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open student data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,grade;
  int courseNum;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> grade;
    grades[courseNum] = grade;
  }
}

//DO NOT MODIFY THIS CONSTRUCTOR
ClassList::ClassList(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open classlist data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,courseName;
  int courseNum,credits;
  while(getline(ifs,line)) {
//    std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> credits;
    getline(stst,courseName); //Remainder of the line is course name
    courses[courseNum] = {courseName, credits};
  }
}

//TODO Add methods as necessary for compatability with p3.hpp
// You may add additional helper methods
// You may NOT change the required method signatures in p3.hpp
// You are encouraged to use method stubs so that your code will compile and
//   you can test the early pieces of your program.

void ClassList::printClassList()
{
	std::cout << "School Name: " << name << std::endl;
	std::cout << "Class List:" << std::endl;
	for(std::unordered_map<int,std::pair<std::string,int>>::iterator i = courses.begin(); i != courses.end(); i++)
	{
		std::cout << i->first << i->second.first << i->second.second << std::endl;
	}
}

OutsideClassList::OutsideClassList(std::string name) : ClassList(name)
{
}

std::string ClassList::getCourseName(int courseNumber)
{
	if(courses.find(courseNumber) != courses.end())
	{
		return courses.at(courseNumber).first;
	}
	else
	{
		return "F";
	}
}

void OutsideClassList::printClassList()
{
	std::cout << "Other School Name: " << name << std::endl;
	for(std::unordered_map<int,std::pair<std::string,int>>::iterator i = courses.begin(); i != courses.end(); i++)
	{
		std::cout << i->first << i->second.first << std::endl;
	}
}

void OutsideClassList::printClassList(ClassList& cl)
{
	std::cout << "Other School Name: " << name << std::endl;
	for(std::unordered_map<int,std::pair<std::string,int>>::iterator i = courses.begin(); i != courses.end(); i++)
	{
		std::string courseName = cl.getCourseName(i->second.second);
		std::cout << i->first << courseName << i->second.first << std::endl;
	}
}

int OutsideClassList::getCourseEquivalent(int courseNumber)
{
	return courses.at(courseNumber).second;
}

std::string Student::getStudentName()
{
	return name;
}

void Student::printStudent(ClassList& cl)
{
	std::cout << "Student Name: " << name << std::endl;
	for(std::map<int, std::string>::iterator i = grades.begin(); i != grades.end(); i++)
	{
		std::string className = cl.getCourseName(i->first);
		std::cout << className << ":	" << i->second << std::endl;
	}
}

StudentWithTransferCredit::StudentWithTransferCredit(std::string name, std::string schoolName) : Student(name)
{
	this->schoolName = schoolName;
}

std::string StudentWithTransferCredit::getSchoolName()
{
	return schoolName;
}

void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool, ClassList& newSchool)
{
	for(std::map<int, std::string>::iterator i = grades.begin(); i != grades.end(); i++)
	{
		if(newSchool.getCourseName(oldSchool.getCourseEquivalent(i->first)).compare("F") != 0)
		{
			std::cout << newSchool.getCourseName(oldSchool.getCourseEquivalent(i->first)) << ": " << i->second << std::endl;
		}
	}
}

int main() {
  //TODO Your code here
	std::string s, o, n;
	std::cout << "New Class List: ";
	std::cin >> s;
	ClassList c = ClassList(s);
	c.printClassList();
	std::cout << "Old Class List: ";
	std::cin >> o;
	OutsideClassList q = OutsideClassList(o);
	q.printClassList();
	q.printClassList(c);
	std::cout << "Transfer Student Name: ";
	std::cin >> n;
	StudentWithTransferCredit v = StudentWithTransferCredit(n, o);
	v.printStudent(q, c);
}
