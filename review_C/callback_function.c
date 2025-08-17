/*
 *	Viết chương trình C mô phỏng chức năng nhận dữ liệu của module UART theo yêu cầu sau:
 *		- Initiallize function: Cho người dùng truyền con trỏ hàm (callback function), để khi nhận được dữ liệu, module sẽ gọi tới function này để trả về dữ liệu và độ dài dữ liệu cho người dùng
 *		- Received  function: Xử lý data nhận được và tìm ra chuỗi dữ liệu hợp lệ và trả nó về cho người dùng thông qua callback function (cái đã được người dùng truyền vào khi gọi hàm init)
 *		- Chuỗi dữ liệu hợp lệ là chuỗi nằm giữa 2 ký tự * và #, và có độ lài lớn hơn 0.
 */

#include <stdio.h>
#include <string.h>

#define SIZE_BUFF 1024

char buff[1024];

// Global variable
void (*call_back)(const char* data, int length);

void init_callback(void (*cb)(const char* data, int length))
{
	call_back = cb;
}


void UART_receive(const char* input)
{
	if (input == NULL)
	{
		printf("String is empty");
		return;
	}

	char* start_pos = strchr(input, '*');
	char* end_pos = strchr(input, '#');

    if (start_pos == NULL || end_pos == NULL || end_pos <= start_pos + 1)
	{
        printf("No valid data\n");
        return;
    }

	int length = end_pos - start_pos - 1;

	strncpy(buff, start_pos + 1, length);

	call_back(buff, length);
}

void my_cb(const char* data, int length)
{
	printf("Data length: %d\n", length);
	printf("Data: %s\n", data);
}


int main()
{
	init_callback(my_cb);

	char* data = "*vandodinh#";

	UART_receive(data);

	return 0;
}
