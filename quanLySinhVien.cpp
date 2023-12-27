#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
typedef struct Students{
    char name[30];
    long long id;
    int date, month, year;
    float gpa;
}ST;
//Function of color MENU
void SET_COLOR(int color)
{
	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}
//Func of check student's date of birth
bool checkDob(const ST *student)
{
    if(student->date <= 0 || student->month <= 0 || student->year <= 0)
    {
        return false;
    }
    if(student->month == 4 || student->month == 6 || student->month == 9 || student->month == 11)
    {
        if (student->date > 30)
            return false;
    }
    else if(student->month == 2)
    {
        if((student->year % 4 == 0 && student->year % 100 != 0) 
        && (student->date > 29 || student->date <= 0))
            return false;
        else if(student->date > 28 || student->date <= 0)
            return false;
    }
    else if(student->month > 12 || student->date > 31)
    {
        return false;
    }
    return true;
}
//Func of check numbers of student's id
bool checkId(const ST *student)
{
    long long idCopy = student->id;
    int count = 0;
    while(idCopy > 0)
    {
        idCopy = idCopy / 10;
        count++;
    }
    if(count != 10)
        return false;
    return true;
}
//Func of check possible GPA
bool checkGpa(ST *student)
{
    if(student->gpa < 0 || student->gpa > 4)
        return false;
    return true;
}
//Func of add student
void addStudent(ST *stArr, int *numOfStudent)
{
    (*numOfStudent)++;
    stArr = (ST*)realloc(stArr, *numOfStudent * sizeof(ST));
    ST student;
    SET_COLOR(3);
    printf("\nNhap ten sinh vien: ");
    while(getchar() != '\n');
    fgets(student.name, sizeof(student.name), stdin);
    printf("\nNhap ma so sinh vien: ");
    scanf("%lld", &student.id);
    if(!checkId(&student))
    {
        SET_COLOR(4);
        printf("Ma so sinh vien khong hop le!\n");
        return;
    }
    printf("\nNhap ngay thang nam sinh: ");
    scanf("%d%d%d", &student.date, &student.month, &student.year);
    if(!checkDob(&student))
    {
        SET_COLOR(4);
        printf("Ngay thang hoac nam sinh khong hop le!\n");
        return;
    }
    printf("\nNhap diem GPA: ");
    while(getchar() != '\n');
    scanf("%f", &student.gpa);
    if(!checkGpa(&student))
    {
        SET_COLOR(4);
        printf("GPA khong hop le!\n");
        return;
    }
    stArr[*numOfStudent-1] = student;
    SET_COLOR(10);
    printf("\nThem sinh vien thanh cong!\n");
}
//Func of print student list
void printStudent(ST *stArr, int numOfStudent)
{
    SET_COLOR(5);
	printf("---------------------------------------------------------------------\n");
    printf("||       Ten         ||     MSSV    ||     Ngay sinh   ||    GPA   ||\n");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < numOfStudent; i++)
    {
        printf("||%s\t\t\t||%lld\t||\t%d/%d/%d\t||%0.2f\t||\n",
        stArr[i].name, stArr[i].id, stArr[i].date, stArr[i].month, stArr[i].year, stArr[i].gpa);
        printf("---------------------------------------------------------------------\n");
    }
}
//Func of update student's information
void updateInfor(ST *stArr, int ordinal)
{
    ST student;
    SET_COLOR(3);
    printf("\nNhap ten sinh vien: ");
    while(getchar() != '\n');
    fgets(student.name, sizeof(student.name), stdin);
    printf("\nNhap ma so sinh vien: ");
    scanf("%lld", &student.id);
    if(!checkId(&student))
    {
        SET_COLOR(4);
        printf("Ma so sinh vien khong hop le!\n");
        return;
    }
    printf("\nNhap ngay thang nam sinh: ");
    scanf("%d%d%d", &student.date, &student.month, &student.year);
    if(!checkDob(&student))
    {
        SET_COLOR(4);
        printf("Ngay thang hoac nam sinh khong hop le!\n");
        return;
    }
    printf("\nNhap diem GPA: ");
    while(getchar() != '\n');
    scanf("%f", &student.gpa);
    if(!checkGpa(&student))
    {
        SET_COLOR(4);
        printf("GPA khong hop le!\n");
        return;
    }
    stArr[ordinal] = student;
    SET_COLOR(10);
    printf("Thong tin da duoc cap nhat!\n");
}
//Function of delete student
void deleteStudent(ST *stArr, int ordinal, int *numOfStudent)
{
    if(ordinal < 0 || ordinal > *numOfStudent)
    {
        SET_COLOR(4);
        printf("So thu tu sinh vien khong chinh xac!");
        return;
    }
    for (int i = ordinal; i <= *numOfStudent; i++)
    {
        stArr[i] = stArr[i + 1];
    }
    (*numOfStudent)--;
}
//Function of find student by student's name
void findStudent(ST *stArr, const char *inputName, int &numOfStudent)
{
    for(int i = 0; i < numOfStudent; i++)
    {
        if(strcmp(stArr[i].name, inputName) == 0)
        {
            printStudent(stArr, numOfStudent);
        }
    }
}
//Function of sort students by their GPA
void sortStudentByGPA(ST *stArr, int *numOfStudent)
{
    for(int i = 0; i < *numOfStudent - 1; i++)
    {
        for(int j = i + 1; j < *numOfStudent; j++)
        {
            if(stArr[i].gpa < stArr[j].gpa)
            {
                ST tmp = stArr[i];
                stArr[i] = stArr[j];
                stArr[j] = tmp;
            }
        }
    }
}
//Function of find the last name of student
const char* findLastName(const char* fullName)
{
    const char* lastWhiteSpace = NULL;
    for(const char* i = fullName; *i != '\0'; i++)
    {
        if (*i == '\n' || *i == '\0' || *i == ' ')
        {
            lastWhiteSpace = i;
        }
    }
    return ((lastWhiteSpace != NULL) ? lastWhiteSpace + 1 : fullName); 
}
//Function of sort student's list by their name
void sortStudentByName(ST *stArr, int *numOfStudent)
{
    for(int i = 0; i < *numOfStudent - 1; i++)
    {
        for(int j = i + 1; j < *numOfStudent; j++)
        {
            if(strcmp(findLastName(stArr[j].name), findLastName(stArr[j + 1].name)) < 0)
            {
                ST tmp = stArr[i];
                stArr[i] = stArr[j];
                stArr[j] = tmp;
            }
        }
    }
}
//Function of clear screen
void clearScreen()
{
    system("cls");
}
//Funtion of print MENU
void printMenu()
{
    SET_COLOR(10);
    printf("************CHUONG TRINH QUAN LY SINH VIEN************\n");
    SET_COLOR(9);
    printf("=======================================================\n");
    SET_COLOR(6);
    printf("\t\t\tMENU\n");
    SET_COLOR(9);
    printf("-------------------------------------------------------\n");
    printf("||   1. Them sinh vien.                              ||\n");
    printf("||   2. Cap nhat thong tin sinh vien.                ||\n");
    printf("||   3. Xoa sinh vien.                               ||\n");
    printf("||   4. Tim kiem sinh vien theo ten.                 ||\n");
    printf("||   5. Sap xep sinh vien theo diem trung binh (GPA).||\n");
    printf("||   6. Sap xep sinh vien theo ten.                  ||\n");
    printf("||   7. Hien thi danh sach sinh vien.                ||\n");
    printf("||   0. Thoat.                                       ||\n");
    printf("-------------------------------------------------------\n");
    SET_COLOR(10);
    printf("*******************************************************\n");
}
int main()
{
    ST *stArr = NULL;
    stArr = (ST*)malloc(0);
    int numOfStudent = 0;
    int ordinal;
    while(1)
    {
        printMenu();
        SET_COLOR(7);
        printf("Lua chon cua ban: ");
        int choose;
        scanf("%d", &choose);
        switch(choose){
            case 1:
                addStudent(stArr, &numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 2:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                printf("Nhap so thu tu sinh vien can chinh sua: ");
                scanf("%d", &ordinal);
                updateInfor(stArr, ordinal);
                system("pause");
                clearScreen();
                break;
            case 3:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                SET_COLOR(3);
                printf("Nhap so thu tu sinh vien muon xoa: ");
                scanf("%d", &ordinal);
                deleteStudent(stArr, ordinal, &numOfStudent);
                SET_COLOR(10);
                printf("Xoa sinh vien thanh cong!");
                system("pause");
                clearScreen();
                break;
            case 4:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                char inputName[30];
                SET_COLOR(3);
                printf("Nhap ten sinh vien can tim kiem: ");
                while(getchar() != '\n');
                fgets(inputName, sizeof(inputName), stdin);
                findStudent(stArr, inputName ,numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 5:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                printf("Danh sach sau khi sap xep: \n");
                sortStudentByGPA(stArr, &numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 6:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                SET_COLOR(10);
                printf("Danh sach sau khi sap xep: \n");
                sortStudentByName(stArr, &numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 7:
                if(numOfStudent == 0)
                {
                    SET_COLOR(4);
                    printf("Khong co sinh vien trong danh sach!\n");
                    system("pause");
                    break;
                }
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 0:
                SET_COLOR(4);
                printf("Ban da thoat chuong trinh!\n");
                system("pause");
                return 0;
            default:
                SET_COLOR(4);
                printf("Lua chon khong nam trong MENU.\n");
                system("pause");
                return 0;
        }
    }
}