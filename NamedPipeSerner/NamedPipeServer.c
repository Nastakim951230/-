#include <stdio.h>
#include <windows.h>

DWORD lpstrToDword(LPSTR s)
{

}
int main()
{
	system("chcp 1251>nul");
	while (TRUE)
	{
		HANDLE hNamedPipe;//��������� ���������� ������
		LPSTR lpszPipeName = L"";//����������, ���������� ��� ������
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
				DWORD d;//���������� � ������� ����� ��������� �������� ������������ �� �������

				//������������ �� DWORD � LPWSTR
				char szTest[140];
				sprintf(szTest, "%d", d);
				LPWSTR s = &szTest;
				buffer = &s;//��������� ����������, �������� ������� ������������ � �����
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