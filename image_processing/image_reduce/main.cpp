#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define Row 512
#define Column 512
void Mirror(unsigned char *, unsigned char*, FILE*);//鏡像
void Flip(unsigned char *, unsigned char*, FILE*);//翻轉
void Rotate(unsigned char *, unsigned char*, FILE*);//旋轉
void Negative(unsigned char *, unsigned char*, FILE*);//負片
void Vague(unsigned char *, unsigned char*, FILE*);//模糊化
int main(int arrc, char** argv)
{
	int x = 0;
	FILE *ptr = fopen("lena", "rb");;
	unsigned char* image = (unsigned char*)malloc(sizeof(unsigned char)*Row*Column);//char  rangs from -128~127
	unsigned char* temp = (unsigned char*)malloc(sizeof(unsigned char)*Row*Column);//unsigned char rangs from 0~255
	if (!ptr)//open file fail
	{
		printf("fail");
		return 0;
	}
	fread(image, Row*Column, sizeof(unsigned char), ptr);
	fclose(ptr);
	puts("1.Mirror");
	puts("2.Flip");
	puts("3.Rotate");
	puts("4.Negative");
	puts("5.Vague");
	printf("Input function:");
	scanf("%d", &x);
	switch (x)
	{
	case 1:
		Mirror(image, temp, ptr);
		break;
	case 2:
		Flip(image, temp, ptr);
		break;
	case 3:
		Rotate(image, temp, ptr);
		break;
	case 4:
		Negative(image, temp, ptr);
		break;
	case 5:
		Vague(image, temp, ptr);
		break;
	}
	fwrite(temp, Row*Column, sizeof(unsigned char), ptr);
	printf("Successful!");
	fclose(ptr);
	free(image);
	free(temp);
}
void Mirror(unsigned char* image, unsigned char* temp, FILE* WriteF)
{
	WriteF = fopen("mirror", "wb");
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Column; j++)
			*(temp + i * Row + j) = *(image + i * Row + Column - j);
}
void Flip(unsigned char* image, unsigned char* temp, FILE* WriteF)
{
	WriteF = fopen("flip", "wb");
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Column; j++)
			*(temp + i * Row + j) = *(image + (Row - i)*Row + j);
}
void Rotate(unsigned char* image, unsigned char* temp, FILE* WriteF)
{
	WriteF = fopen("Rotate", "wb");
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Column; j++)
			*(temp + i * Row + j) = *(image + Column * (Column - j) + i);
}
void Negative(unsigned char* image, unsigned char* temp, FILE* WriteF)
{
	WriteF = fopen("negative", "wb");
	for (int i = 0; i < Row*Column; i++)
		*(temp + i) = 255 - *(image + i);
}
void Vague(unsigned char* image, unsigned char* temp, FILE* WriteF)
{
	WriteF = fopen("vague", "wb");
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Column; j++)
			if (i == 0 || i == Row - 1 || j == 0 || j == Column - 1)
				*(temp + i * Row + j) = *(image + i * Row + j);
			else
				*(temp + i * Row + j) = ((*(image + (i - 1) * Row + j - 1) + *(image + (i - 1) * Row + j) +
					*(image + (i - 1) * Row + j + 1) + *(image + (i - 1) * Row + j) +
					*(image + i * Row + j) + *(image + i * Row + j + 1) +
					*(image + (i + 1) * Row + j - 1) + *(image + (i + 1) * Row + j) +
					*(image + (i + 1) * Row + j + 1)) / 9);
}