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
		LPWSTR s = L"Некорректно введены данные, попробуйте еще раз";
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
		HANDLE hNamedPipe;//объявляем дескриптор канала
		LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";//переменная, содержащая имя канала
		hNamedPipe = CreateNamedPipe(//создаем канал
			lpszPipeName,//имя канала
			PIPE_ACCESS_DUPLEX, //режим доступа к каналу (двухсторонний)
			PIPE_TYPE_MESSAGE| PIPE_READMODE_MESSAGE|PIPE_WAIT,//режим работы канала: передовать,читать и ждать сообщения
			PIPE_UNLIMITED_INSTANCES,//кол-во водящих соединений к каналу. В этом случае неограничено
			521,//Объем байт на чтение
			512,//Объем байт на запись
			INFINITE,//max время ожидания сообщения
			NULL //указатель на структуру безопасности
		);

		BOOL Connected = ConnectNamedPipe(hNamedPipe, NULL);// установка соединения клиента с каналом
		if (Connected)//если клиент подключен то
		{
			printf("\nКлиент успешно подключен\n");
			DWORD size_buffer = 100;//размер буфера для чтения
			LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));//строковая переменная, в которую будут считываться данные

			DWORD actual_readen;//сколько на самом деле нужно было байт для прочтения
			BOOL SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\nКлиент пишет: ");
				printf(buffer);
				LPSTR d;//переменная в которой будет храниться значение пердаваемого от клиента
				d = lpstrToDword(buffer);
				//конвертирует из DWORD в LPWSTR
				
				buffer = &d;//строковая переменная, значение которой записывается в канал
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключен от сервера\n");
		}
		CloseHandle(hNamedPipe);//закрываем канал
	}
}