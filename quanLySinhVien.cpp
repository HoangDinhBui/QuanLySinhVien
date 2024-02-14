#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

using namespace std;

struct Students {
    wstring name;
    long long id;
    int date, month, year;
    float gpa;
};

void setVietnameseTextMode() {
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
}

// Function of color MENU
void SET_COLOR(int color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        WORD wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
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
    setVietnameseTextMode();

    numOfStudent++;
    Students* newStArr = new Students[numOfStudent];
    // Copy data from stArr to newStArr
    std::copy(stArr, stArr + numOfStudent - 1, newStArr);
    // Release memory of stArr
    delete[] stArr;
    // stArr points to newStArr
    stArr = newStArr;

    Students student;
    SET_COLOR(3);
    wcout << L"\nNhập tên sinh viên: ";
    wcin.ignore();
    getline(wcin, student.name);

    wcout << L"\nNhập mã số sinh viên: ";
    wcin >> student.id;
    if (!checkId(student)) {
        SET_COLOR(4);
        wcout << L"Mã số sinh viên không hợp lệ!\n";
        return;
    }

    wcout << L"\nNhập ngày tháng năm sinh: ";
    wcin >> student.date >> student.month >> student.year;
    if (!checkDob(student)) {
        SET_COLOR(4);
        wcout << L"Ngày tháng hoặc năm sinh không hợp lệ!\n";
        return;
    }

    wcout << L"\nNhập điểm GPA: ";
    wcin >> student.gpa;
    if (!checkGpa(student)) {
        SET_COLOR(4);
        wcout << L"GPA Không hợp lệ!\n";
        return;
    }

    stArr[numOfStudent - 1] = student;
    SET_COLOR(10);
    wcout << L"\nThêm sinh viên thành công!\n";
}

// Func of print student list
void printStudent(const Students* stArr, int numOfStudent) {
    setVietnameseTextMode();

    SET_COLOR(5);
    wcout << L"---------------------------------------------------------------------\n";
    wcout << L"||      Tên                  ||   MSSV     ||   Ngày sinh   ||   GPA   ||\n";
    wcout << L"---------------------------------------------------------------------\n";
    for (int i = 0; i < numOfStudent; i++) {
        wcout << L"|| " << setw(25) << left << stArr[i].name << L" || " << setw(10) << stArr[i].id << L" ||  " << setfill(L'0') << setw(2) << stArr[i].date << L"/" << setw(2) << stArr[i].month << L"/" << setw(4) << stArr[i].year << L"   ||  " << fixed << setprecision(2) << stArr[i].gpa << L"   ||\n";
        wcout << L"||---------------------------||------------||---------------||-------  ||\n";
    }
}

// Func of update student's information
void updateInfor(Students* stArr, int ordinal) {
    Students student;
    SET_COLOR(3);
    wcout << L"\nNhập tên sinh viên: ";
    wcin.ignore();
    getline(wcin, student.name);

    wcout << L"\nNhập mã số sinh viên: ";
    wcin >> student.id;
    if (!checkId(student)) {
        SET_COLOR(4);
        wcout << L"Mã số sinh viên không hợp lệ!\n";
        return;
    }

    wcout << L"\nNhập ngày tháng năm sinh: ";
    wcin >> student.date >> student.month >> student.year;
    if (!checkDob(student)) {
        SET_COLOR(4);
        wcout << L"Ngày tháng hoặc năm sinh không hợp lệ!\n";
        return;
    }

    wcout << L"\nNhập điểm GPA: ";
    wcin >> student.gpa;
    if (!checkGpa(student)) {
        SET_COLOR(4);
        wcout << L"GPA không hợp lệ!\n";
        return;
    }

    stArr[ordinal] = student;
    SET_COLOR(10);
    wcout << L"Thông tin đã được cập nhật!\n";
}

// Function of delete student
void deleteStudent(Students* stArr, int ordinal, int& numOfStudent) {
    setVietnameseTextMode();

    if (ordinal < 0 || ordinal >= numOfStudent) {
        SET_COLOR(4);
        wcout << L"Số thứ tự sinh viên không chính xác!";
        return;
    }
    for (int i = ordinal; i < numOfStudent - 1; i++) {
        stArr[i] = stArr[i + 1];
    }
    numOfStudent--;
}

// Function of find student by student's name
void findStudent(const Students* stArr, const wstring& inputName, int numOfStudent) {
    setVietnameseTextMode();

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
        wcout << L"Không tìm thấy sinh viên!" << endl;
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
const wstring findLastName(const wstring& fullName) {
    size_t lastWhiteSpace = fullName.find_last_of(L" ");
    return ((lastWhiteSpace != wstring::npos) ? fullName.substr(lastWhiteSpace + 1) : fullName);
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
    setVietnameseTextMode();

    SET_COLOR(10);
    wcout << L"************CHƯƠNG TRÌNH QUẢN LÝ SINH VIÊN************\n";
    SET_COLOR(9);
    wcout << L"=======================================================\n";
    SET_COLOR(6);
    wcout << L"\t\t\tMENU\n";
    SET_COLOR(9);
    wcout << L"-------------------------------------------------------\n";
    wcout << L"||   1. Thêm sinh viên.                              ||\n";
    wcout << L"||   2. Cập nhật thông tin sinh viên.                ||\n";
    wcout << L"||   3. Xóa sinh viên.                               ||\n";
    wcout << L"||   4. Tìm kiếm sinh viên theo tên.                 ||\n";
    wcout << L"||   5. Sắp xếp sinh viên theo điểm trung bình (GPA).||\n";
    wcout << L"||   6. Sắp xếp sinh viên theo tên.                  ||\n";
    wcout << L"||   7. Hiển thị danh sách sinh viên.                ||\n";
    wcout << L"||   0. Thoát.                                       ||\n";
    wcout << L"-------------------------------------------------------\n";
    SET_COLOR(10);
    wcout << L"*******************************************************\n";
}

int main() {
    setVietnameseTextMode();

    Students* stArr = nullptr;
    stArr = new Students[0];
    int numOfStudent = 0;
    int ordinal;
    wstring inputName;  // Move the declaration up here

    while (1) {
        printMenu();
        SET_COLOR(7);
        wcout << L"Lựa chọn của bạn: ";
        int choose;
        wcin >> choose;

        switch (choose) {
            case 1:
                addStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 2:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                wcout << L"Nhập số thứ tự sinh viên cần chỉnh sửa thông tin: ";
                wcin >> ordinal;
                updateInfor(stArr, ordinal - 1);
                system("pause");
                clearScreen();
                break;
            case 3:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                wcout << L"Nhập số thứ tự sinh viên cần xóa: ";
                wcin >> ordinal;
                deleteStudent(stArr, ordinal - 1, numOfStudent);
                SET_COLOR(10);
                wcout << L"Xóa sinh viên thành công!";
                system("pause");
                clearScreen();
                break;
            case 4:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                wcout << L"Nhập tên sinh viên cần tìm kiếm: ";
                wcin.ignore();
                getline(wcin, inputName);
                findStudent(stArr, inputName, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 5:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                wcout << L"Danh sách sau khi sắp xếp: \n";
                sortStudentByGPA(stArr, numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 6:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                wcout << L"Danh sách sau khi sắp xếp: \n";
                sortStudentByName(stArr, numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 7:
                if (numOfStudent == 0) {
                    SET_COLOR(4);
                    wcout << L"Không có sinh viên trong danh sách!\n";
                    system("pause");
                    clearScreen();
                    break;
                }
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 0:
                SET_COLOR(4);
                wcout << L"Bạn đã thoát chương trình!\n";
                system("pause");
                delete[] stArr; // Release memory before exit
                return 0;
            default:
                SET_COLOR(4);
                wcout << L"Lựa chọn không nằm trong MENU.\n";
                system("pause");
                delete[] stArr; // Release memory before exit
                return 0;
        }
    }
}
