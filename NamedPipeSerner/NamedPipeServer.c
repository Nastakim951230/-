#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#define SIZE_BUFFER 140
double mas[10];

LPSTR lpstrToDword(LPSTR s)
{
	double otvet;
	char str[10];
	int n = 0;
	LPSTR str1;
	
		mas[n] = atof(s);
		n++;
	
	
		if (mas[0] != 0)
		{
			otvet = mas[0] * mas[0];
			mas[0] = otvet;

			char* str = calloc(100, sizeof(char));
			char* s = calloc(100, sizeof(char));
			for (int i = 0; i < 1; i++)
			{
				sprintf(s, "%f ", mas[i]);//���������� ������ � ������
				strcat(str, s);
			}
			str1 = str;
			return str1;
		}
		
	
	

}

int main()
{
	system("chcp 1251>nul");
	HANDLE hNamedPipe;//��������� ���������� ������
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//����������, ���������� ��� ������
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer=(CHAR*)calloc(size_buffer,sizeof(CHAR));
	BOOL Connected;
	DWORD actual_reaen;
	BOOL SuccessRead;
	DWORD d = 0;
	while (TRUE)
	{
			
		
		hNamedPipe = CreateNamedPipe(//������� �����
			lpszPipeName,//��� ������
			PIPE_ACCESS_DUPLEX, //����� ������� � ������ (�������������)
			PIPE_TYPE_MESSAGE| PIPE_READMODE_MESSAGE|PIPE_WAIT,//����� ������ ������: ����������,������ � ����� ���������
			PIPE_UNLIMITED_INSTANCES,//���-�� ������� ���������� � ������. � ���� ������ ������������
			SIZE_BUFFER,//����� ���� �� ������
			SIZE_BUFFER,//����� ���� �� ������
			INFINITE,//max ����� �������� ���������
			NULL //��������� �� ��������� ������������
		);

		Connected = ConnectNamedPipe(hNamedPipe, NULL);// ��������� ���������� ������� � �������
		if (Connected)//���� ������ ��������� ��
		{
			printf("\n������ ������� ���������\n");
			

			
			SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_reaen, NULL);
			if (SuccessRead)
			{
				printf("\n������ �����: ");
				printf(buffer);
				LPSTR d;//���������� � ������� ����� ��������� �������� ������������ �� �������
				d = lpstrToDword(buffer);
				//������������ �� DWORD � LPWSTR
				
				buffer = d;//��������� ����������, �������� ������� ������������ � �����
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_reaen, NULL);
			}
		}
		else
		{
			printf("\n������ �������� �� �������\n");
		}
		CloseHandle(hNamedPipe);//��������� �����
	}
}