#include <stdio.h>
#include <windows.h>

LPSTR lpstrToDword(LPSTR s)
{
	char dataConvertToStruct[]=s;
	char* pEnd;
	float kv1;
	kv1 = wcstof(dataConvertToStruct, &pEnd);
	if (kv1 == 0)
	{
		LPWSTR s = L"����������� ������� ������, ���������� ��� ���";
	}
	else
	{
		kv1 = kv1 * kv1;
		char szTest[140];
		sprintf(szTest, "%d", kv1);
		LPWSTR s = &szTest;
	}
	return s;

}
int main()
{
	system("chcp 1251>nul");
	while (TRUE)
	{
		HANDLE hNamedPipe;//��������� ���������� ������
		LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//����������, ���������� ��� ������
		hNamedPipe = CreateNamedPipe(//������� �����
			lpszPipeName,//��� ������
			PIPE_ACCESS_DUPLEX, //����� ������� � ������ (�������������)
			PIPE_TYPE_MESSAGE| PIPE_READMODE_MESSAGE|PIPE_WAIT,//����� ������ ������: ����������,������ � ����� ���������
			PIPE_UNLIMITED_INSTANCES,//���-�� ������� ���������� � ������. � ���� ������ ������������
			521,//����� ���� �� ������
			512,//����� ���� �� ������
			INFINITE,//max ����� �������� ���������
			NULL //��������� �� ��������� ������������
		);

		BOOL Connected = ConnectNamedPipe(hNamedPipe, NULL);// ��������� ���������� ������� � �������
		if (Connected)//���� ������ ��������� ��
		{
			printf("\n������ ������� ���������\n");
			DWORD size_buffer = 100;//������ ������ ��� ������
			LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));//��������� ����������, � ������� ����� ����������� ������

			DWORD actual_readen;//������� �� ����� ���� ����� ���� ���� ��� ���������
			BOOL SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\n������ �����: ");
				printf(buffer);
				LPSTR d;//���������� � ������� ����� ��������� �������� ������������ �� �������
				d = lpstrToDword(buffer);
				//������������ �� DWORD � LPWSTR
				
				buffer = &d;//��������� ����������, �������� ������� ������������ � �����
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		else
		{
			printf("\n������ �������� �� �������\n");
		}
		CloseHandle(hNamedPipe);//��������� �����
	}
}