#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
typedef struct Students{
    char name[30];
    long long id;
    char dob[13];
    float gpa;
}ST;
void addStudents(ST *stArr, int *numOfStudent)
{
    ST student;
    printf("\nNhap ten sinh vien: ");
    while(getchar() != '\n');
    fgets(student.name, sizeof(student.name), stdin);
    printf("\nNhap ma so sinh vien: ");
    scanf("%ld", &student.id);
    printf("\nNhap ngay thang nam sinh: ");
    while(getchar() != '\n');
    scanf("%c", &student.dob);
    printf("\nNhap diem GPA: ");
    scanf("%f", &student.gpa);
    stArr[*numOfStudent] = student;
    (*numOfStudent)++;
    printf("\nThem sinh vien thanh cong!");
}
int main()
{
    ST *stArr;
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
    printf("Lua chon cua ban: ");
    int choose;
    scanf("%d", &choose);
    switch(choose){
        case 1:
        addStudents(stArr, numOfStudent);
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
            break;
        case 0:
            return 0;
        default:
            printf("Lua chon khong nam trong MENU.");
            return 0;
    }
}