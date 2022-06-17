#include "realstudent.h"
#include <iostream>
#include <sstream>

using namespace std;

#define SHOWCOSTRUCTORS 0

RealStudent::RealStudent(string name, string group): RealStudent(){
    this->name = name;
    this->group = group;
    for(int k =0; k < numLessonName; k++)
        sizeMarks[k] = 0;
}

RealStudent::RealStudent() {
    for(int k =0; k < numLessonName; k++){
        this->marks[k] = nullptr;
    }
    if(SHOWCOSTRUCTORS) cout << "create obj. " << name.data() << endl;
}

RealStudent::~RealStudent() {
    if(SHOWCOSTRUCTORS) cout << "delete obj. " << name.data() << endl;
    delete[] marks;
}

RealStudent::RealStudent(const RealStudent &st2):RealStudent() {
    this->name = st2.name;
    this->group = st2.group;
    for(int k =0; k < numLessonName; k++){
        this->sizeMarks[k] = st2.sizeMarks[k];
        delete[] marks[k];
        marks[k] = new int[sizeMarks[k]];
        for (int n = 0; n < sizeMarks[k]; n++) {
            marks[k][n] = st2.marks[k][n];
        }
    }

    //this = st2; - так нельзя
}

void RealStudent::operator = (const RealStudent &st2) {
    // this =  RealStudent(st2); - так нельзя
    this->name = st2.name;
    this->group = st2.group;
    //marks = new int*[numLessonName];
    for(int k =0; k < numLessonName; k++){
        this->sizeMarks[k] = st2.sizeMarks[k];
        delete [] marks[k];
        marks[k] = new int[sizeMarks[k]];
        for (int n = 0; n < sizeMarks[k]; n++) {
            marks[k][n] = st2.marks[0][0];
        }
    }
}

void RealStudent::addMark(int val, LessonName lesson) {
    int id = (int)lesson;
    int* buffer = new int[sizeMarks[id] + 1];
    for (int k = 0; k < sizeMarks[id]; k++) {
        buffer[k] = marks[id][k];
    }
    buffer[sizeMarks[id]] = val;
    sizeMarks[id]++;
    delete [] marks[id];
    marks[id] = buffer;
}

void RealStudent::setStudent(string name, string group) {
    this->name = name;
    this->group = group;
}

void RealStudent::show() {
    cout << name.data() << " " << group.data() << "\t\t\t";
    for(int k = 0; k < numLessonName; k++)
        cout << lessons[k].data() << ": " << getAvMark((LessonName)k) << "   ";
    cout << endl;
}

void RealStudent::showMarks() {
    for(int n = 0; n < numLessonName; n++){
        cout << lessons[n].data() << ": ";
        for (int k = 0; k < sizeMarks[n]; k++) {
            cout << marks[n][k] << " ";
        }
        cout << endl;
    }
}

string RealStudent::showMarks(LessonName lesson) {
    stringstream sstr;  // как-то проще нужно
    for (int k = 0; k < sizeMarks[int(lesson)]; k++) {
        int mark = marks[(int)lesson][k];
        sstr << mark << " ";
    }
    return sstr.str();
}

float RealStudent::getAvMark(LessonName lesson) {
    int id = (int)lesson;
    if(sizeMarks[id] <= 0) return 0;
    float avMark = 0;
    for(int k = 0; k < sizeMarks[id]; k++)
        avMark += marks[id][k];
    return (int)(100*avMark /  sizeMarks[id]) / 100.0;
}

bool RealStudent::changeMarks(LessonName lesson, int id, int val) {
    int n = (int)lesson;
    if (id >= 0 && id < sizeMarks[n]) {
        marks[n][id] = val;
        return 1;
    }
    return 0;
}
#undef SHOWCOSTRUCTORS

void testMarksBook(){
    MarksBook hogwarts;

    hogwarts.addStudent(RealStudent("Harry Potter", "Griffindor"));
    hogwarts.addStudent(RealStudent("Hermione Grainger", "Griffindor"));
    hogwarts.addStudent(RealStudent("Ronald Weasley ", "Griffindor"));
    hogwarts.addStudent(RealStudent("Tom Riddle", "Slytherin"));
    hogwarts.addStudent(RealStudent("Draco Malfoy", "Slytherin"));
    hogwarts.addStudent(RealStudent("Luna LoveGood", "Ravenclaw"));
    hogwarts.addStudent(RealStudent("Cedric Diggory ", "Hufflepuff"));

    for(int m = 0; m < hogwarts.getCountStudents(); m++)
        for(int n = 0; n < numLessonName; n++)
            for(int k = 0; k < 1 + rand() % 5; k++)
                hogwarts.getStudents(m).addMark((m==1)? 5: 2 + rand() % 4, (LessonName)n);

    // выравнивание  нужно setw() - но с ним беда
    cout << endl << "There are all students."<< endl;
    hogwarts.showStudents(hogwarts.getCountStudents(), hogwarts.getIds());

    cout << endl << "There are bad guys."<< endl;
    int *badGuys = nullptr;
    int numBadGuys = hogwarts.getBadGuyIds(3, badGuys);
    hogwarts.showStudents(numBadGuys, badGuys);
    delete [] badGuys;

    cout << endl << "There are Potions marks."<< endl;
    hogwarts.showStudents(hogwarts.getCountStudents(), hogwarts.getIds(), LessonName::Math);
}
