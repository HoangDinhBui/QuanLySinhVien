#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
    scanf("%12s", student.dob);
    printf("\nNhap diem GPA: ");
    while(getchar() != '\n');
    scanf("%f", &student.gpa);
    stArr[*numOfStudent-1] = student;
    printf("\nThem sinh vien thanh cong!\n");
}
//Func of print student list
void printStudent(ST *st, int numOfStudent)
{
    printf("    Ten              MSSV         Ngay sinh         GPA\n");
    for (int i = 0; i < numOfStudent; i++)
    {
        printf("%s                %lld     %s           %f", st[i].name, st[i].id, st[i].dob, st[i].gpa);
        printf("\n");
    }
}
int main()
{
    ST *stArr = NULL;
     stArr = (ST*)malloc(0);
    int numOfStudent = 0;
    printf("************CHUONG TRINH QUAN LY SINH VIEN************\n");
    printf("#   1. Them sinh vien.                               #\n");
    printf("#   2. Cap nhat thong tin sinh vien.                 #\n");
    printf("#   3. Xoa sinh vien.                                #\n");
    printf("#   4. Tim kiem sinh vien theo ten.                  #\n");
    printf("#   5. Sap xep sinh vien theo diem trung binh (GPA). #\n");
    printf("#   6. Sap xep sinh vien theo ten.                   #\n");
    printf("#   7. Hien thi danh sach sinh vien.                 #\n");
    printf("#   0. Thoat.                                        #\n");
    printf("******************************************************\n");
    while(1)
    {
        printf("Lua chon cua ban: ");
        int choose;
        scanf("%d", &choose);
        switch(choose){
            case 1:
                addStudent(stArr, &numOfStudent);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                printStudent(stArr, numOfStudent);
                break;
            case 0:
                printf("Ban da thoat chuong trinh!\n");
                return 0;
            default:
                printf("Lua chon khong nam trong MENU.");
                return 0;
        }
    }
}