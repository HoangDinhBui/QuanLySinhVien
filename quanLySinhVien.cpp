#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
typedef struct Students{
    char name[30];
    long long id;
    char dob[13];
    float gpa;
}ST;
//Func of add student
void addStudent(ST *stArr, int *numOfStudent)
{
    (*numOfStudent)++;
    stArr = (ST*)realloc(stArr, *numOfStudent * sizeof(ST));
    ST student;
    printf("\nNhap ten sinh vien: ");
    while(getchar() != '\n');
    fgets(student.name, sizeof(student.name), stdin);
    printf("\nNhap ma so sinh vien: ");
    scanf("%lld", &student.id);
    printf("\nNhap ngay thang nam sinh: ");
    while(getchar() != '\n');
    scanf("%s", student.dob);
    printf("\nNhap diem GPA: ");
    while(getchar() != '\n');
    scanf("%f", &student.gpa);
    stArr[*numOfStudent-1] = student;
    printf("\nThem sinh vien thanh cong!\n");
}
//Func of print student list
void printStudent(ST *stArr, int numOfStudent)
{
	printf("---------------------------------------------------------------------\n");
    printf("||       Ten         ||     MSSV    ||     Ngay sinh   ||    GPA   ||\n");
    printf("||-------------------||-------------||-----------------||----------||\n");
    for (int i = 0; i < numOfStudent; i++)
    {
        printf("|| %s              	     ||%lld   ||   %s    ||    %0.2f  ||\n",
        stArr[i].name, stArr[i].id, stArr[i].dob, stArr[i].gpa);
        printf("||-------------------||-------------||-----------------||----------||\n");
    }
}
//Func of update student's information
void updateInfor(ST *stArr, int ordinal)
{
    ST student;
    printf("\nNhap ten sinh vien: ");
    while(getchar() != '\n');
    fgets(student.name, sizeof(student.name), stdin);
    printf("\nNhap ma so sinh vien: ");
    scanf("%lld", &student.id);
    printf("\nNhap ngay thang nam sinh: ");
    while(getchar() != '\n');
    scanf("%s", student.dob);
    printf("\nNhap diem GPA: ");
    while(getchar() != '\n');
    scanf("%f", &student.gpa);
    stArr[ordinal] = student;
    printf("Thong tin da duoc cap nhat!\n");
}
//Function of delete student
void deleteStudent(ST *stArr, int ordinal, int *numOfStudent)
{
    if(ordinal < 0 || ordinal > *numOfStudent)
    {
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
void findStudent(ST *stArr, const char *inputName, int *numOfStudent)
{
    for(int i = 0; i < *numOfStudent; i++)
    {
        if(strcmp(stArr[i].name, inputName) == 0)
        {
            printf("%s                %lld     %s           %f", 
            stArr[i].name, stArr[i].id, stArr[i].dob, stArr[i].gpa);
            printf("\n");
        }
    }
}
//Function of sort students by their GPA
void sortStudentByGPA(ST *stArr, int *numOfStudent)
{
    for(int i = 0; i < *numOfStudent; i++)
    {
        if(stArr[i].gpa < stArr[i+1].gpa)
        {
            ST tmp = stArr[i];
            stArr[i] = stArr[i+1];
            stArr[i+1] = tmp;
        }
    }
}
//Function of find the last name of student
const char* findLastName(const char* fullName)
{
    const char* lastWhiteSpace = NULL;
    for(const char* i = fullName; i != '\0'; i++)
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
    printf("************CHUONG TRINH QUAN LY SINH VIEN************\n");
    printf("======================================================\n");
    printf("\t\t\tMENU");
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
                printf("Nhap so thu tu sinh vien can chinh sua: ");
                scanf("%d", &ordinal);
                updateInfor(stArr, ordinal);
                system("pause");
                clearScreen();
                break;
            case 3:
                printf("Nhap so thu tu sinh vien muon xoa: ");
                scanf("%d", &ordinal);
                deleteStudent(stArr, ordinal, &numOfStudent);
                printf("Xoa sinh vien thanh cong!");
                system("pause");
                clearScreen();
                break;
            case 4:
                char inputName[30];
                printf("Nhap ten sinh vien can tim kiem: ");
                while(getchar() != '\n');
                fgets(inputName, sizeof(inputName), stdin);
                findStudent(stArr, inputName ,&numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 5:
                printf("Danh sach sau khi sap xep: \n");
                sortStudentByGPA(stArr, &numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 6:
                printf("Danh sach sau khi sap xep: \n");
                sortStudentByName(stArr, &numOfStudent);
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 7:
                printStudent(stArr, numOfStudent);
                system("pause");
                clearScreen();
                break;
            case 0:
                printf("Ban da thoat chuong trinh!\n");
                system("pause");
                return 0;
            default:
                printf("Lua chon khong nam trong MENU.");
                system("pause");
                return 0;
        }
    }
}