#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

typedef struct SinhVien
{
	int mssv;
	char Hoten[50];
	float toan;
	float ly;
	float hoa;
};

void XuatThongTinSV(SinhVien sv[], int stt);

void ToLower(SinhVien sv[], int stt);

void DocFile(SinhVien sv[], int &SoLuongSV)
{
	FILE* inout = fopen("inout.txt", "rt");
	if (inout == NULL)
	{
		printf("Khong doc duoc File");
	}
	else
	{
		int i = 0;
		while (!feof(inout))
		{
			fscanf(inout, "%d %s %f %f %f", &sv[i].mssv, &sv[i].Hoten, &sv[i].toan, &sv[i].ly, &sv[i].hoa);
			ToLower(sv, i);
			XuatThongTinSV(sv, i);
			i++;
			SoLuongSV++;
		}
	}
}

int TimSinhVien(SinhVien sv[], int SoLuongSV, char hoten1[])
{
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(sv[i].Hoten, hoten1) == 0)
			return i;
	}
	return -1;
}

void XuatThongTinSV(SinhVien sv[], int stt)
{
	printf("MSSV: %d\n", sv[stt].mssv);
	printf("Ho va Ten sv: %s\n", sv[stt].Hoten);
	printf("Diem Toan: %.2f\n", sv[stt].toan);
	printf("Diem Ly: %.2f\n", sv[stt].ly);
	printf("Diem Hoa: %.2f\n", sv[stt].hoa);
}

void ToLower(SinhVien sv[], int stt)
{
	for (int i = 0; sv[stt].Hoten[i]; i++)
	{
		sv[stt].Hoten[i] = tolower(sv[stt].Hoten[i]);
	}
}

void SapXepDanhSachSV(SinhVien sv[], int SoLuongSV)
{
	int pos;
	char x[50];
	for (int i = 0; i < SoLuongSV; i++)
	{
		strcpy(x, sv[i].Hoten);
		for (pos = i; pos > 0 && strcmp(sv[pos - 1].Hoten, x) >= 0; pos--)
			strcpy(sv[pos].Hoten, sv[pos - 1].Hoten);
		strcpy(sv[pos].Hoten, x);
	}
}

int main()
{
	SinhVien sv[50];
	int SoLuongSV = 0;
	DocFile(sv, SoLuongSV);
	char hoten1[50];
	printf("Nhap ho ten sv can tim kiem: ");
	gets_s(hoten1);
	if (TimSinhVien(sv, SoLuongSV, hoten1) == -1)
	{
		printf("Khong tim thay sinh vien mang ten nay");
	}
	else
		XuatThongTinSV(sv, TimSinhVien(sv, SoLuongSV, hoten1));
	printf("Xuat danh sach theo thu tu tang dan theo ten:\n");
	SapXepDanhSachSV(sv, SoLuongSV);
	for (int i = 0; i < SoLuongSV; i++)
	{
		XuatThongTinSV(sv, i);
	}
	_getch();
}