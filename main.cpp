#include "header.h"
int*** initCampus(int nd, int nf, int nr){
    int *** grid = new int** [nd];
    for(int d=0; d<nd; d++){
        *(grid+d) = new int* [nf];
        for(int f=0; f<nf; f++){
            *(*(grid+d)+f) = new int[nr];
            for(int r=0; r<nr; r++){
                *(*(*(grid+d)+f)+r) = 0;
            }
        }
    }
    return grid;
}
void freeCampus(int*** grid, int nd, int nf){
    for (int d = 0; d < nd; d++){
        for (int f = 0; f < nf; f++){
            delete[] *(*(grid + d) + f);   // free rooms array
        }
        delete[] *(grid + d);              // free floors array
    }
    delete[] grid;                         // free departments array
}
void growNames(char** &names, int current_size){    // here Current_Size is numStudents
    char** New_Name = new char*[current_size + 1];
    for (int i = 0; i < current_size; i++){
        *(New_Name+i) = *(names+i);
    }
    *(New_Name+current_size) = nullptr;
    delete[] names;
    names = New_Name;
}

void growIds(int* &ids, int current_size){
    int* New_ids = new int[current_size+1];
    for(int i=0; i<current_size; i++){
        *(New_ids+i) = *(ids+i);
    }
    *(New_ids + current_size) = 0;
    delete[] ids;
    ids = New_ids;
}

void growGpas(float* &gpas, int current_size){
    float* New_gpas = new float[current_size+1];
    for(int i=0; i<current_size; i++){
        *(New_gpas+i) = *(gpas+i);
}
    *(New_gpas+current_size) = 0;
    delete[] gpas;
    gpas = New_gpas;
}

void growStatuses(int* &statuses, int current_size){
     int *New_statuses = new int[current_size+1];
     for(int i=0; i<current_size; i++){
        *(New_statuses+i) = *(statuses+i);
     }
     *(New_statuses + current_size) = 0;
     delete[]statuses;
     statuses = New_statuses;
}
// Removing student data
void removeNames(char** &names, int current_size, int remove_index){
    delete[] *(names+remove_index);
    *(names + remove_index) = nullptr;
    for (int i = remove_index; i < current_size - 1; i++){
        *(names+i) = *(names+i+1);
    }
//  shrinked array
    char** New_names = new char*[current_size - 1];
    for (int i = 0; i<current_size-1; i++)
    {
        *(New_names+i) = *(names+i);
    }
    delete[] names;
    names = New_names;
}
void removeIds(int* &ids, int current_size, int remove_index){
    for (int i = remove_index; i<current_size-1; i++){
        *(ids + i) = *(ids+i+1);
    }
// shrinked array
    int* New_ids = new int[current_size-1];
    for (int i = 0; i < current_size-1; i++){
        *(New_ids+i) = *(ids+i);
    }
    delete[] ids;
    ids = New_ids;
}

void removeGpas(float* &gpas, int current_size, int remove_index){
    for (int i = remove_index; i < current_size-1; i++){
        *(gpas+i) = *(gpas+i+1);
    }
// shrinked array
    float* New_gpas = new float[current_size - 1];
    for (int i = 0; i < current_size-1; i++){
        *(New_gpas + i) = *(gpas+i);
    }
    delete[] gpas;
    gpas = New_gpas;
}
void removeStatuses(int* &statuses, int current_size, int remove_index){
    for (int i = remove_index; i < current_size-1; i++){
        *(statuses+i) = *(statuses+i+1);
    }
// shrinked array
    int* New_statuses = new int[current_size-1];
    for (int i = 0; i < current_size-1; i++){
        *(New_statuses+i) = *(statuses+i);
    }
    delete[] statuses;
    statuses = New_statuses;
}
// M2: Student Enrollement
void enrollStudent(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
                   int &numStudents, int nd, int nf, int nr){
    char name_entered[200];
    cout << endl;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(name_entered, 200);
    if (strlen(name_entered) == 0){
    cout << "Error: Name cannot be empty!" << endl;
    return;
}

    int new_ID = 1001 + numStudents;
    
    // calling the growing arrays functions
    growNames(names, numStudents);
    growIds(ids, numStudents);
    growGpas(gpas, numStudents);
    growStatuses(statuses, numStudents);

    // store name 
    int name_length = (int)strlen(name_entered);
    *(names + numStudents) = new char[name_length + 1];
    for (int i = 0; i <= name_length; i++)
    {
        *(*(names + numStudents) + i) = *(name_entered + i);
    }

    *(ids+numStudents)      = new_ID;
    *(gpas+numStudents)     = 2.50;
    *(statuses+numStudents) = 0;

    // randomly pick a starting room
    int d = rand() % nd;
    int f = rand() % nf;
    int r = rand() % nr;

    int skipped = 0;

    // if occupied, linear search for free room
    if (*(*(*(grid + d) + f) + r) != 0){
        bool found = false;
        for (int i = 0; i < nd && !found; i++){
            for (int j = 0; j < nf && !found; j++){
                for (int k = 0; k < nr && !found; k++){
                    if (*(*(*(grid + i) + j) + k) == 0){
                        d = i;
                        f = j;
                        r = k;
                        found = true;
                    }
                    else{
                        skipped++;
                    }
                }
            }
        }
        if (!found)
        {
            cout << "Error: Campus is full! Cannot enrol student." << endl;
            delete[] *(names + numStudents);
            return;
        }
        cout << "Room Search Skipped " << skipped << " occupied slots" << endl;
    }
    // mark room occupied
    *(*(*(grid + d) + f) + r) = new_ID;
    numStudents++;
    cout << "Enrolled: " << *(names + numStudents - 1)<< "  ID: "<<new_ID << " | Room: Dept "<<d
         << ", Floor "<< f
         << ", Room " << r << endl;
}
//M3: Time Step
void runTimeStep(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
                 int &numStudents, int nd, int nf, int nr, int &step){
    step++;
    cout << endl;
    cout << "\t" << "TIME-STEP " << step << endl;
    for (int i = numStudents - 1; i >= 0; i--){
        unsigned char flags = 0;
        int event = (rand() % 10) + 1;
        if (event >= 1 && event <= 5){
            // Academic Progress
            flags = flags | (1 << 0);
            *(gpas + i) = *(gpas + i) + 0.1;
            if (*(gpas + i) > 4){
                *(gpas + i) = 4;
            }
            *(statuses + i) = 0;
            cout << "  PROGRESS: " << *(names + i)<< " | GPA: " << fixed << setprecision(2) << *(gpas + i) << endl;
        }
        else if (event >= 6 && event <= 8){
            // Steady
            cout << "  STEADY:   " << *(names + i)
                 << " | GPA unchanged: " << fixed << setprecision(2) << *(gpas + i) << endl;
        }
        else if (event == 9){
            // Warning
            flags = flags | (1 << 1);
            *(gpas + i) = *(gpas + i) - 0.2;

            if (*(gpas + i)<0){
                *(gpas + i) = 0;
            }
            *(statuses + i) = 1;
            cout << "  WARNING:  " << *(names + i)
                 << " | GPA:  " << fixed << setprecision(2) << *(gpas + i) << endl;
        }
        else   // event == 10
        {
            // Graduation
            flags = flags | (1 << 2);
            *(statuses + i) = 2;
            int gradID = *(ids + i);
            cout << "  [GRADUATE] " << *(names + i)
                 << " (ID " << gradID << ") is graduating!" << endl;
            
            // clear room from grid
            for (int d = 0; d < nd; d++){
                for (int f = 0; f < nf; f++){
                    for (int r = 0; r < nr; r++){
                        if (*(*(*(grid + d) + f) + r) == gradID){
                            *(*(*(grid + d) + f) + r) = 0;
                        }
                    }
                }
            }
            if (flags & (1 << 2)){
                cout << "  [FLAG]     Graduation flag confirmed for " << *(names + i) << endl;
            }

            // call remove functions
            removeNames(names, numStudents, i);
            removeIds(ids, numStudents, i);
            removeGpas(gpas, numStudents, i);
            removeStatuses(statuses, numStudents, i);
            numStudents = numStudents - 1;
        }
    }
    cout << "========================================" << endl;
}
// M4: Dashboard
void displayDashboard(int*** grid, char** names, int* ids, float* gpas, int* statuses,
                      int numStudents, int nd, int nf, int nr,
                      int* current_dept, int* current_floor, int step){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    
    int d = *current_dept;
    int f = *current_floor;

    cout << "===========================================================================" << endl;
    cout << "                 UniVault  .  LIVE RESOURCE DASHBOARD"                       << endl;
    cout << "===========================================================================" << endl;
    cout << right
    << "[DEPT: "   << setfill('0') << setw(2) << d 
    << "][FLOOR: " << setfill('0') << setw(2) << f
    << "][ROOMS: " << setfill('0') << setw(2) << nr
    << "][STEP: "  << setfill('0') << setw(3) << step
    << "]" << setfill(' ') << endl;

    cout << "---------------------------------------------------------------------------" << endl;
    cout << left
         <<setw(19)<<"ROOM ADDR"<<setw(11)<<"ID"<<setw(19)<< "NAME"<< setw(9)<<"GPA"<< setw(12)<<"STATUS"<< endl;
    cout << "---------------------------------------------------------------------------" << endl;

    for (int r = 0; r < nr; r++){
        int* roomPtr  = *(*(grid + d) + f) + r;
        int  occupant = *roomPtr;
        cout << left << setw(18) << (void*)roomPtr;
        if (occupant == 0){
            cout << setw(9)  << "----"
                 << setw(22) << "----------"
                 << setw(9)  << "0.00"
                 << setw(12) << "EMPTY"
                 << endl;
        }
        else{
            int search_idx = -1;
            for (int i = 0; i < numStudents; i++){
                if (*(ids + i) == occupant){
                    search_idx = i;
                    break;
                }
            }
            cout << setw(9)  << *(ids + search_idx);
            cout << setw(22) << *(names + search_idx);
            cout << fixed << setprecision(2) << setw(9) << *(gpas + search_idx);
            if (*(statuses + search_idx) == 1){
                cout << setw(14) << "WARNING !"    << endl;
            }
            else if (*(statuses + search_idx) == 2){
                cout << setw(14) << "GRADUATING *" << endl;
            }
            else{
                cout << setw(14) << "STUDYING"     << endl;
            }
        }
    }
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "COMMANDS: [ENTER] Step | [E] Enroll | [J] Jump | [F] Find | [S] Save | [X] Exit" << endl;
    cout << "===========================================================================" << endl;
    cout << "Choice: ";
}
//M5: Find and Jump
//find
void findStudent(int*** grid, char** names, int* ids, float* gpas, int* statuses,
                 int numStudents, int nd, int nf, int nr){
    int search_ID;
    cout << "Enter the ID of the student you want to search: ";
    cin  >> search_ID;
    cin.ignore();
    if (search_ID < 1001){
    cout << "Error: Invalid ID!" << endl;
    cout << endl << "Press ENTER to continue...";
    cin.ignore();
    return;
}
    //search in ids array
    int found_id = -1;
    for (int i = 0; i < numStudents; i++){
        if (*(ids + i) == search_ID){
            found_id = i;
            break;
        }
    }
    if (found_id == -1){
        cout << "No student enrolled with the ID: " << search_ID << endl;
        return;
    }
    // find room in grid
    int dept_found = -1, floor_found = -1, room_found = -1;
    for (int d = 0; d < nd && dept_found == -1; d++){
        for (int f = 0; f < nf && dept_found == -1; f++){
            for (int r = 0; r < nr && dept_found == -1; r++){
                if (*(*(*(grid + d) + f) + r) == search_ID){
                    dept_found = d;
                    floor_found = f;
                    room_found = r;
                }
            }
        }
    }
    // print record
    cout << "--- Student Record ---"  << endl;
    cout << "ID     : " << *(ids + found_id)   << endl;
    cout << "Name   : " << *(names + found_id) << endl;
    cout << "GPA    : " << fixed << setprecision(2) << *(gpas + found_id) << endl;
    cout << "Status : ";
    if(*(statuses + found_id) == 0){
    cout << "STUDYING"   << endl;
    }
    else if (*(statuses + found_id) == 1){
    cout << "WARNING"    << endl;
    }
    else if (*(statuses + found_id) == 2){
    cout << "GRADUATING" << endl;
    }

    int* roomPtr = *(*(grid + dept_found) + floor_found) + room_found;
    cout << "Dept: " << dept_found << " Floor: " << floor_found << " Room: " << room_found << endl;
    cout << "Address  : " << (void*)roomPtr << endl;
    cin.ignore();
    cout << endl << "Press ENTER to continue...";
    cin.ignore();
}
// jump
void jump(int* currentDept, int* currentFloor, int nd, int nf){
    int target_dept, target_floor;
    cout << "Enter Department index (0 to " << nd-1 << "): ";
    cin  >> target_dept;
    cin.ignore();
    if (target_dept < 0 || target_dept >= nd){
        cout << "ERROR: Invalid department index." << endl;
        return;
    }
    cout << "Enter Floor index (0 to " << nf - 1 << "): ";
    cin  >> target_floor;
    cin.ignore();
    if (target_floor < 0 || target_floor >= nf){
        cout << "Error: Invalid floor index." << endl;
        return;
    }
    *currentDept  = target_dept;
    *currentFloor = target_floor;
    cout << "Jump to Dept " << target_dept << ", Floor " << target_floor << endl;
}
// M6: File Handling
bool readConfig(int &nd, int &nf, int &nr){
    ifstream config_file;
    config_file.open("config.txt");
    if (!config_file.is_open()){
        return false;
    }
    config_file >> nd >> nf >> nr;  // reads nd, nf and nr from the file and copies into these 3 variables
    config_file.close();
    return true;
}
void writeConfig(int nd, int nf, int nr){
    ofstream config_file;
    config_file.open("config.txt");  
    config_file << nd << endl;
    config_file << nf << endl;
    config_file << nr << endl;
    config_file.close();
}
void saveData(int*** grid, char** names, int* ids, float* gpas, int* statuses,
              int numStudents, int nd, int nf, int nr){
    ofstream data_b;
    data_b.open("database.txt");
    data_b << numStudents << endl;
    for (int i = 0; i < numStudents; i++){
        int dept_found = 0, floor_found = 0, room_found = 0;
        for (int d = 0; d < nd; d++){
            for (int f = 0; f < nf; f++){
                for (int r = 0; r < nr; r++){
                    if (*(*(*(grid + d) + f) + r) == *(ids + i)){
                        dept_found  = d;
                        floor_found = f;
                        room_found  = r;
                    }
                }
            }
        }
        data_b << *(ids + i) << "  ";
        // write name char by char, replacing spaces with underscores
        for (int c = 0; c < (int)strlen(*(names + i)); c++){
            if (*(*(names + i) + c) == ' '){
                data_b << '_';
            }
            else{
                data_b << *(*(names + i) + c);
            }
        }
        data_b << "  " << *(gpas + i) << "  " << *(statuses + i) << "  "
               << dept_found      << "  "
               << floor_found     << "  "
               << room_found      << endl;
    }
    // write grid occupancy
    for (int d = 0; d < nd; d++){
        for (int f = 0; f < nf; f++){
            for (int r = 0; r < nr; r++){
                if (*(*(*(grid + d) + f) + r) != 0){
                    data_b << d << "   "<< f << "   "<< r << "   "<< *(*(*(grid + d) + f) + r) << endl;
                }
            }
        }
    }
    data_b.close();
    cout << "Saved: Data written to database.txt." << endl;
}
bool loadData(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses,
              int &numStudents, int nd, int nf, int nr){
    ifstream data_b;
    data_b.open("database.txt");
    if(!data_b.is_open()){
        return false;
    }
    data_b >> numStudents;
    if(numStudents>0){
        names    = new char* [numStudents];
        ids      = new int   [numStudents];
        gpas     = new float [numStudents];
        statuses = new int   [numStudents];
        for (int i = 0; i < numStudents; i++){
            int id, status, d, f, r;
            float gpa;
            char name_print[200];
            data_b >> id >> name_print >> gpa >> status >> d >> f >> r;
            // convert underscores back to spaces
            for (int c = 0; c < (int)strlen(name_print); c++){
                if (*(name_print + c) == '_'){
                    *(name_print + c) = ' ';
                }
            }
            *(ids + i)      = id;
            *(gpas + i)     = gpa;
            *(statuses + i) = status;
            int name_length = (int)strlen(name_print);
            *(names + i) = new char[name_length + 1];   // space of /n
            for (int c = 0; c <= name_length; c++){
                *(*(names + i) + c) = *(name_print + c);
            }
        }
    }
    // read grid occupancy until end of file
    int d, f, r, occupant;
    while ((!data_b.fail()) && (!data_b.eof())){
        data_b >> d >> f >> r >> occupant;
        if (!data_b.fail()){
            *(*(*(grid + d) + f) + r) = occupant;
        }
    }
    data_b.close();
    cout << "Loaded data for" << numStudents << " student(s) from database.txt." << endl;
    return true;
}
// Main
int main(){
    srand((unsigned int)time(0));

    int numDepts = 0, numFloors = 0, numRooms = 0;

    if (!readConfig(numDepts, numFloors, numRooms))
    {
        cout << "config.txt not found, enter campus dimensions:" << endl;
        cout << "Number of Departments : ";
        cin  >> numDepts;
        cout << "Number of Floors      : ";
        cin  >> numFloors;
        cout << "Number of Rooms/Floor : ";
        cin  >> numRooms;
        cin.ignore();
        writeConfig(numDepts, numFloors, numRooms);
    }
    int*** CampusGrid = initCampus(numDepts, numFloors, numRooms);
    // declaring the 4 parallel arrays 
    char**  names       = new char*[1];
    int*    ids         = new int  [1];
    float*  gpas        = new float[1];
    int*    statuses    = new int  [1];
    int     numStudents = 0;

    loadData(CampusGrid, names, ids, gpas, statuses, numStudents,
             numDepts, numFloors, numRooms);

    int currentDept  = 0;
    int currentFloor = 0;
    int step         = 0;
    
    char choice = ' ';
    while (choice != 'X' && choice != 'x'){
        displayDashboard(CampusGrid, names, ids, gpas, statuses, numStudents,
                         numDepts, numFloors, numRooms,
                         &currentDept, &currentFloor, step);
        cin.get(choice);
        switch (choice){
            case '\n':
            case '\r':
                runTimeStep(CampusGrid, names, ids, gpas, statuses, numStudents,numDepts, numFloors, numRooms, step);
                cout << endl << "Press ENTER to continue: ";
                cin.ignore();
                break;
            case 'E':
            case 'e':

                enrollStudent(CampusGrid, names, ids, gpas, statuses, numStudents,numDepts, numFloors, numRooms);
                cout << endl << "Press ENTER to continue...";
                cin.ignore();
                break;
            case 'J':
            case 'j':
                 cin.ignore(); 
                jump(&currentDept, &currentFloor, numDepts, numFloors);
                cout << endl << "Press ENTER to continue...";
                cin.ignore();
                break;
            case 'F':
            case 'f':
                cin.ignore();
                findStudent(CampusGrid, names, ids, gpas, statuses, numStudents,numDepts, numFloors, numRooms);
                break;
            case 'S':
            case 's':
                cin.ignore();
                saveData(CampusGrid, names, ids, gpas, statuses, numStudents,numDepts, numFloors, numRooms);
                cout << endl << "Press ENTER to continue: ";
                cin.ignore();
                break;
            case 'X':
            case 'x':
                cin.ignore();
                cout << "Save before exit? (Y/N): ";
                char saveChoice;
                cin  >> saveChoice;
                cin.ignore();
                if (saveChoice == 'Y' || saveChoice == 'y'){
                    saveData(CampusGrid, names, ids, gpas, statuses, numStudents,numDepts, numFloors, numRooms);
                }
                break;
            default:
                cin.ignore();
                break;
        }
    }
     for (int i = 0; i < numStudents; i++){
        delete[] *(names + i);
     }
    delete[] names;
    delete[] ids;
    delete[] gpas;
    delete[] statuses;
    freeCampus(CampusGrid, numDepts, numFloors);
    cout << endl << "Goodbye!" << endl;
    return 0;
}