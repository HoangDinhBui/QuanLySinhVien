#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Students {
    string name;
    long long id;
    int date, month, year;
    float gpa;
};

// Function of color MENU
void SET_COLOR(int color) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

// Func of check student's date of birth
bool checkDob(const Students& student) {
    if (student.date <= 0 || student.month <= 0 || student.year <= 0) {
        return false;
    }
    if (student.month == 4 || student.month == 6 || student.month == 9 || student.month == 11) {
        if (student.date > 30)
            return false;
    } else if (student.month == 2) {
        if ((student.year % 4 == 0 && student.year % 100 != 0) && (student.date > 29 || student.date <= 0))
            return false;
        else if (student.date > 28 || student.date <= 0)
            return false;
    } else if (student.month > 12 || student.date > 31) {
        return false;
    }
    return true;
}

// Func of check numbers of student's id
bool checkId(const Students& student) {
    long long idCopy = student.id;
    int count = 0;
    while (idCopy > 0) {
        idCopy = idCopy / 10;
        count++;
    }
    if (count != 10)
        return false;
    return true;
}

// Func of check possible GPA
bool checkGpa(const Students& student) {
    if (student.gpa < 0 || student.gpa > 4)
        return false;
    return true;
}

// Func of add student
void addStudent(Students*& stArr, int& numOfStudent) {
    numOfStudent++;
    Students* newStArr = new Students[numOfStudent];
    // Sao chép dữ liệu từ stArr sang newStArr
    std::copy(stArr, stArr + numOfStudent, newStArr);
    // Giải phóng bộ nhớ của stArr
    delete[] stArr;
    // Gán stArr trỏ đến newStArr
    stArr = newStArr;
    Students student;
    SET_COLOR(3);
    cout << "\nNhap ten sinh vien: ";
    cin.ignore();
    getline(cin, student.name);

    cout << "\nNhap ma so sinh vien: ";
    cin >> student.id;
    if (!checkId(student)) {
        SET_COLOR(4);
        cout << "Ma so sinh vien khong hop le!\n";
        return;
    }

    cout << "\nNhap ngay thang nam sinh: ";
    cin >> student.date >> student.month >> student.year;
    if (!checkDob(student)) {
        SET_COLOR(4);
        cout << "Ngay thang hoac nam sinh khong hop le!\n";
        return;
    }

    cout << "\nNhap diem GPA: ";
    cin >> student.gpa;
    if (!checkGpa(student)) {
        SET_COLOR(4);
        cout << "GPA khong hop le!\n";
        return;
    }

    stArr[numOfStudent - 1] = student;
    SET_COLOR(10);
    cout << "\nThem sinh vien thanh cong!\n";
}

// Func of print student list
void printStudent(const Students* stArr, int numOfStudent) {
    SET_COLOR(5);
    cout << "---------------------------------------------------------------------\n";
    cout << "||      Ten                  ||   MSSV     ||   Ngay sinh   ||   GPA   ||\n";
    cout << "---------------------------------------------------------------------\n";
    for (int i = 0; i < numOfStudent; i++) {
        cout << "|| " << setw(25) << left << stArr[i].name << " || " << setw(10) << stArr[i].id << " ||  " << setfill('0') << setw(2) << stArr[i].date << "/" << setw(2) << stArr[i].month << "/" << setw(4) << stArr[i].year << "   ||  " << fixed << setprecision(2) << stArr[i].gpa << "   ||\n";
        cout << "---------------------------------------------------------------------\n";
    }
}

// Func of update student's information
void updateInfor(Students* stArr, int ordinal) {
    Students student;
    SET_COLOR(3);
    cout << "\nNhap ten sinh vien: ";
    cin.ignore();
    getline(cin, student.name);

    cout << "\nNhap ma so sinh vien: ";
    cin >> student.id;
    if (!checkId(student)) {
        SET_COLOR(4);
        cout << "Ma so sinh vien khong hop le!\n";
        return;
    }

    cout << "\nNhap ngay thang nam sinh: ";
    cin >> student.date >> student.month >> student.year;
    if (!checkDob(student)) {
        SET_COLOR(4);
        cout << "Ngay thang hoac nam sinh khong hop le!\n";
        return;
    }

    cout << "\nNhap diem GPA: ";
    cin >> student.gpa;
    if (!checkGpa(student)) {
        SET_COLOR(4);
        cout << "GPA khong hop le!\n";
        return;
    }

    stArr[ordinal] = student;
    SET_COLOR(10);
    cout << "Thong tin da duoc cap nhat!\n";
}

// Function of delete student
void deleteStudent(Students* stArr, int ordinal, int& numOfStudent) {
    if (ordinal < 0 || ordinal >= numOfStudent) {
        SET_COLOR(4);
        cout << "So thu tu sinh vien khong chinh xac!";
        return;
    }
    for (int i = ordinal; i < numOfStudent - 1; i++) {
        stArr[i] = stArr[i + 1];
    }
    numOfStudent--;
}

// Function of find student by student's name
void findStudent(const Students* stArr, const string& inputName, int numOfStudent) {
    bool found = false;
    for (int i = 0; i < numOfStudent; i++) {
        if (stArr[i].name == inputName) {
            found = true;
            printStudent(&stArr[i], 1);
            break;
        }
    }
    if (!found) {
        SET_COLOR(4);
        cout << "Khong tim thay sinh vien co ten: " << inputName << endl;
    }
}

// Function of sort students by their GPA
void sortStudentByGPA(Students* stArr, int numOfStudent) {
    for (int i = 0; i < numOfStudent - 1; i++) {
        for (int j = i + 1; j < numOfStudent; j++) {
            if (stArr[i].gpa < stArr[j].gpa) {
                Students tmp = stArr[i];
                stArr[i] = stArr[j];
                stArr[j] = tmp;
            }
        }
    }
}

// Function of find the last name of student
const string findLastName(const string& fullName) {
    size_t lastWhiteSpace = fullName.find_last_of(" ");
    return ((lastWhiteSpace != string::npos) ? fullName.substr(lastWhiteSpace + 1) : fullName);
}

// Function of sort student's list by their name
void sortStudentByName(Students* stArr, int numOfStudent) {
    for (int i = 0; i < numOfStudent - 1; i++) {
        for (int j = i + 1; j < numOfStudent; j++) {
            if (findLastName(stArr[i].name) < findLastName(stArr[j].name)) {
                Students tmp = stArr[i];
                stArr[i] = stArr[j];
                stArr[j] = tmp;
            }
        }
    }
}

// Function of clear screen
void clearScreen() {
    system("cls");
}

// Function of print MENU
void printMenu() {
    SET_COLOR(10);
    cout << "************CHUONG TRINH QUAN LY SINH VIEN************\n";
    SET_COLOR(9);
    cout << "=======================================================\n";
    SET_COLOR(6);
    cout << "\t\t\tMENU\n";
    SET_COLOR(9);
    cout << "-------------------------------------------------------\n";
    cout << "||   1. Them sinh vien.                              ||\n";
    cout << "||   2. Cap nhat thong tin sinh vien.                ||\n";
    cout << "||   3. Xoa sinh vien.                               ||\n";
    cout << "||   4. Tim kiem sinh vien theo ten.                 ||\n";
    cout << "||   5. Sap xep sinh vien theo diem trung binh (GPA).||\n";
    cout << "||   6. Sap xep sinh vien theo ten.                  ||\n";
    cout << "||   7. Hien thi danh sach sinh vien.                ||\n";
    cout << "||   0. Thoat.                                       ||\n";
    cout << "-------------------------------------------------------\n";
    SET_COLOR(10);
    cout << "*******************************************************\n";
}

int main() {
    Students* stArr = nullptr;
    stArr = new Students[0];
    int numOfStudent = 0;
    int ordinal;
    string inputName;  // Di chuyển khai báo lên đây

    while (1) {
        printMenu();
        SET_COLOR(7);
        cout << "Lua chon cua ban: ";
        int choose;
        cin >> choose;

        switch (choose) {
            case 1:
                addStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 2:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                cout << "Nhap so thu tu sinh vien can chinh sua: ";
                cin >> ordinal;
                updateInfor(stArr, ordinal - 1);
                system("pause");
                clearScreen();
                break;
            case 3:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                cout << "Nhap so thu tu sinh vien muon xoa: ";
                cin >> ordinal;
                deleteStudent(stArr, ordinal - 1, numOfStudent);
                SET_COLOR(10);
                cout << "Xoa sinh vien thanh cong!";
                system("pause");
                clearScreen();
                break;
            case 4:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                cout << "Nhap ten sinh vien can tim kiem: ";
                cin.ignore();
                getline(cin, inputName);
                findStudent(stArr, inputName, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 5:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                cout << "Danh sach sau khi sap xep: \n";
                sortStudentByGPA(stArr, numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 6:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                cout << "Danh sach sau khi sap xep: \n";
                sortStudentByName(stArr, numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 7:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    cout << "Khong co sinh vien trong danh sach!\n";
                    system("pause");
                    break;
                }
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 0:
                SET_COLOR(4);
                cout << "Ban da thoat chuong trinh!\n";
                system("pause");
                delete[] stArr; // Giải phóng bộ nhớ trước khi thoát
                return 0;
            default:
                SET_COLOR(4);
                cout << "Lua chon khong nam trong MENU.\n";
                system("pause");
                delete[] stArr; // Giải phóng bộ nhớ trước khi thoát
                return 0;
        }
    }
}
