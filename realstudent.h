#ifndef REALSTUDENTS_H
#define REALSTUDENTS_H

#include <iostream>
using namespace std;


const int numLessonName = 3;
const string lessons[]{"Math", "Russ", "Litr"};

enum LessonName {
   Math = 0,
   Russ,
   Litr
};

class RealStudent{
private:
    string name;
    string group;

    int** marks = new int*[numLessonName];
    int sizeMarks[numLessonName];

public:
    RealStudent();
    RealStudent(string name, string group);
    RealStudent(const RealStudent& st2); // конструктор копирования

    ~RealStudent();

    void operator = (const RealStudent& st2);

    void setStudent(string name, string group);

    float getAvMark(LessonName lesson);
    string getName(){
        return name;
    }

    void addMark(int val, LessonName lesson);
    bool changeMarks(LessonName lesson, int id, int val);

    void show();
    void showMarks();
    string showMarks(LessonName lesson);
};

class MarksBook{
    int count_students = 0;
    RealStudent* students = nullptr;
    int *ids = nullptr;
public:
    MarksBook() {
    }

    ~MarksBook(){
        delete[] students;
        delete[] ids;
    }

    int getCountStudents(){
        return count_students;
    }

    RealStudent& getStudents(int id){
        return students[id];
    }

    int* getIds(){
        return ids;
    }

    void addStudent(RealStudent &st){
        RealStudent* buff = new RealStudent[count_students+1];
        for(int k = 0; k < count_students; k++){
            buff[k] = students[k];
        }
        buff[count_students] = st;
        delete[] students;
        students = buff;
        count_students++;
        refreshId();
    }

    void removeStudent(int id){
        RealStudent* buff = new RealStudent[count_students-1];
        for(int k = 0; k < id; k++){
            buff[k] = students[k];
        }
        for(int k = id+1; k < count_students; k++){
            buff[k-1] = students[k];
        }
        delete[] students;
        students = buff;
        count_students--;
        refreshId();
    }

    void showStudents(int size_id, int *ids){
        for(int k = 0; k < size_id; k++)
            students[ids[k]].show();
    }

    void showStudents(int size_id, int *id, LessonName lesson){
        for(int k = 0; k < size_id; k++){
            string str = students[k].showMarks(lesson);
            cout <<  students[k].getName().data() << "\t\t\t";
            cout << " " << str.data() << endl; // почему-то хочет char*, а string не хочет
        }
    }

    int getBadGuyIds(float threshold, int* &badGuyIds){
        int numBadGuy = 0;
        for(int k =0; k < count_students; k++){
            for(int n = 0; n < numLessonName; n++){
                if(students[k].getAvMark((LessonName)n) < threshold){
                    numBadGuy++;
                    break;
                }
            }
        }
        if(badGuyIds)
            delete[] badGuyIds;
       badGuyIds = new int[numBadGuy];
        int countBadGuy = 0;
        for(int k =0; k < count_students; k++){
            for(int n = 0; n < numLessonName; n++){
                if(students[k].getAvMark((LessonName)n) < threshold){
                    badGuyIds[countBadGuy] = k;
                    countBadGuy++;
                    break;
                }
            }
        }
        return numBadGuy;
    }

private:
    void refreshId(){
        delete[] ids;
        ids = new int[count_students];
        for(int k = 0; k < count_students; k++)
            ids[k] = k;
    }
};

void testMarksBook();


#endif // REALSTUDENTS_H
