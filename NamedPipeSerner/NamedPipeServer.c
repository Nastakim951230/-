#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#define SIZE_BUFFER 140
double mas[10];
char masu[20];
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
				sprintf(s, "%f ", mas[i]);//записываем данные в массив
				strcat(str, s);
			}
			str1 = str;
			return str1;
		}
		else
		{
			char* str = calloc(100, sizeof(char));
			char* s = calloc(100, sizeof(char));
			for (int i = 0; i < 1; i++)
			{
				sprintf(s, "%f ", mas[i]);//записываем данные в массив
				strcat(str, s);
			}
			str1 = str;
			return str1;
		}
		
}

int main()
{
	system("chcp 1251>nul");
	HANDLE hNamedPipe;//объявляем дескриптор канала
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//переменная, содержащая имя канала
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer=(CHAR*)calloc(size_buffer,sizeof(CHAR));
	BOOL Connected;
	DWORD actual_reaen;
	BOOL SuccessRead;
	DWORD d = 0;
	while (TRUE)
	{
			
		
		hNamedPipe = CreateNamedPipe(//создаем канал
			lpszPipeName,//имя канала
			PIPE_ACCESS_DUPLEX, //режим доступа к каналу (двухсторонний)
			PIPE_TYPE_MESSAGE| PIPE_READMODE_MESSAGE|PIPE_WAIT,//режим работы канала: передовать,читать и ждать сообщения
			PIPE_UNLIMITED_INSTANCES,//кол-во водящих соединений к каналу. В этом случае неограничено
			SIZE_BUFFER,//Объем байт на чтение
			SIZE_BUFFER,//Объем байт на запись
			INFINITE,//max время ожидания сообщения
			NULL //указатель на структуру безопасности
		);

		Connected = ConnectNamedPipe(hNamedPipe, NULL);// установка соединения клиента с каналом
		if (Connected)//если клиент подключен то
		{
			printf("\nКлиент успешно подключен\n");
			

			
			SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_reaen, NULL);
			if (SuccessRead)
			{
				printf("\nКлиент пишет: ");
				printf(buffer);
				LPSTR d;//переменная в которой будет храниться значение пердаваемого от клиента
				d = lpstrToDword(buffer);
				//конвертирует из DWORD в LPWSTR
				
				buffer = d;//строковая переменная, значение которой записывается в канал
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_reaen, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключен от сервера\n");
		}
		CloseHandle(hNamedPipe);//закрываем канал
	}
}