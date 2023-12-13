#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct SinhVien{
    char Ten[30];
    int mssv;
    char ngaySinh[30];
    float gpa;
}SV;
//ham nhap sinh vien
void nhapSinhVien(SV *sv, int soSinhVien)
{
    while (getchar() != '\n');
    printf("****** Nhap thong tin sinh vien ******\n");
    for (int i = 0; i < soSinhVien; i++)
    {
        printf("Sinh vien %d: \n", i - 1);
        printf("Ho va ten: ");
        fgets(sv[i].Ten, sizeof(sv[i].Ten), stdin);
        sv[i].Ten[strcspn(sv[i].Ten, "\n")] = '\0';
        printf("Ma so sinh vien: ");
        scanf("%d", &sv->mssv);
        printf("Ngay thang nam sinh: ");
        scanf("%s", &sv->ngaySinh);
        sv[i].ngaySinh[strcspn(sv[i].ngaySinh, "\n")] = '\0';
        printf("Diem GPA: ");
        scanf("%f", &sv->gpa);
        while (getchar() != '\n');
    } 
}
//ham in thong tin sinh vien
void inSinhVien(SV *sv, int soSinhVien)
{
    for (int i = 1; i <= soSinhVien; i++)
    {
        printf("Sinh vien %d: \n", i);
        printf("%s      %d      %s      %f\n", sv->Ten, sv->mssv, sv->ngaySinh, sv->gpa);
    }
}
int main()
{
    int soSinhVien;
    printf("Nhap so sinh vien cua lop: ");
    scanf("%d", &soSinhVien);
    SV *sinhVien;
    sinhVien = (SV*) malloc (soSinhVien * sizeof(SV));
    int tieptuc = 1;
    while(tieptuc)
    {
        printf("******************************************\n");
        printf("##  CHUONG TRINH QUAN LY SINH VIEN      ##\n");
        printf("##   1. Nhap thong tin sinh vien.       ##\n");
        printf("##   2. In thong tin sinh vien.         ##\n");
        printf("##   3. Sap xep sinh vien theo diem TB. ##\n");
        printf("##   4. Xep loai sinh vien.             ##\n");
        printf("##   5. Xuat danh sach sinh vien.       ##\n");
        printf("##   0. Thoat.                          ##\n");
        printf("******************************************\n");
        printf("##   Lua chon cua ban: "); printf("\t\t\t##\n");
        int choose;
        scanf("%d", &choose);
        switch (choose)
        {
            case 1:
                nhapSinhVien(sinhVien, soSinhVien);
                break;
            case 2:
                inSinhVien(sinhVien, soSinhVien);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le!\n");
                printf("Xin vui long nhap lai: ");
        }
        char choice;
        printf("Ban co muon tiep tuc khong?(y/n)");
        scanf("%c", &choice);
        if(choice == 'n' || choice == 'N')
        {
            printf("Ban da roi chuong trinh!");
            tieptuc = 0;
        }
    }
    return 0;
}