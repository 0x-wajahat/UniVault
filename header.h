#ifndef UNIVAULT_H
#define UNIVAULT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

int*** initCampus(int nd, int nf, int nr);
void freeCampus(int*** grid, int nd, int nf);

void growNames(char** &names, int current_size);
void growIds(int* &ids, int current_size);
void growGpas(float* &gpas, int current_size);
void growStatuses(int* &statuses, int current_size);

void removeNames(char** &names, int current_size, int remove_index);
void removeIds(int* &ids, int current_size, int remove_index);
void removeGpas(float* &gpas, int current_size, int remove_index);
void removeStatuses(int* &statuses, int current_size, int remove_index);

void enrollStudent(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
                   int &numStudents, int nd, int nf, int nr);

void runTimeStep(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
                 int &numStudents, int nd, int nf, int nr, int &step);

void displayDashboard(int*** grid, char** names, int* ids, float* gpas, int* statuses,
                      int numStudents, int nd, int nf, int nr,
                      int* currentDept, int* currentFloor, int step);

void findStudent(int*** grid, char** names, int* ids, float* gpas, int* statuses,
                 int numStudents, int nd, int nf, int nr);
void jump(int* currentDept, int* currentFloor, int nd, int nf);

bool readConfig(int &nd, int &nf, int &nr);
void writeConfig(int nd, int nf, int nr);
void saveData(int*** grid, char** names, int* ids, float* gpas, int* statuses,
              int numStudents, int nd, int nf, int nr);
bool loadData(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
              int &numStudents, int nd, int nf, int nr);

#endif