#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct customer {
	int id;
	char name[20];
	char ssnum[14];
	char phone[12];
	char address[50];
} Cus;

typedef struct video {
	int id;
	char title[20];
	char genre[10];
	int rental_fee;
	char reg_date[9];
	int rentaled_or_not;
} Vid;

typedef struct rent {
	int id;
	int vid_id;
	int cus_id;
	int returned_or_not;
} Rent;

Cus cus_list[200];
int carr = 0;
Vid vid_list[200];
int varr = 0;
Rent rent;
int rent_id = 1;

void InputCustomer();
void InputVideo();
void Run();

void InputCustomer()
{
	FILE* c_fp = fopen("cus_list.txt", "w+");
	char line[150];
	char* ptr;
	int word;

	while (fscanf(c_fp, "%s", line) > 0)
	{
		word = 0;
		ptr = strtok(line, ",");
		while (ptr != NULL)
		{
			word++;
			switch (word)
			{
			case 1:
				cus_list[carr].id = atoi(ptr);
				break;
			case 2:
				strcpy(cus_list[carr].name, ptr);
				break;
			case 3:
				strcpy(cus_list[carr].ssnum, ptr);
				break;
			case 4:
				strcpy(cus_list[carr].phone, ptr);
				break;
			case 5: 
				strcpy(cus_list[carr].address, ptr);
				break;
			}
			ptr = strtok(NULL, ",");
		}
		carr++;
	}

	fclose(c_fp);
}

void InputVideo()
{
	FILE* v_fp = fopen("vid_list.txt", "w+");
	char line[150];
	char* ptr;
	int word;

	while (fscanf(v_fp, "%s", line) > 0)
	{
		word = 0;
		ptr = strtok(line, ",");
		while (ptr != NULL)
		{
			word++;
			switch (word)
			{
			case 1:  
				vid_list[varr].id = atoi(ptr);
				break;
			case 2:
				strcpy(vid_list[varr].title, ptr);
				break;
			case 3:  
				strcpy(vid_list[varr].genre, ptr);
				break;
			case 4:  
				vid_list[varr].rental_fee = atoi(ptr);
				break;
			case 5:
				strcpy(vid_list[varr].reg_date, ptr);
				break;
			case 6: 
				vid_list[varr].rentaled_or_not = atoi(ptr);
				break;
			}
			ptr = strtok(NULL, ",");
		}
		varr++;
	}

	fclose(v_fp);
}

void main()
{
	InputCustomer();
	InputVideo();
	Run();
	return 0;
}

int SelectMenu();
void AddCustomer();
void FindCustomer();
void ViewAllCustomer();
void AddVideo();
void ViewVideo();
void ViewFullVideo();
void Rental();
void Return();
void Run()
{
	int key = 0;
	while ((key = SelectMenu()) != 0)
	{
		switch (key)
		{
		case 1: AddCustomer(); break;
		case 2: FindCustomer(); break;
		case 3: ViewAllCustomer(); break;
		case 4: AddVideo(); break;
		case 5: ViewVideo(); break;
		case 6: ViewFullVideo(); break;
		case 7: Rental(); break;
		case 8: Return(); break;
		default: printf("No number.\n"); break;
		}
	}
}
int getnum();
int SelectMenu()
{
	printf("<Video rental management program>\n");
	printf("1. New customer registration\n2. Customer information inquiry\n3. View all customer information\n4. New video registration\n");
	printf("5. View video information\n6. View full video information\n7. Rental\n8. Return\n0. Exit\n");
	printf("---------------------\n");
	printf("Please select an item: ");
	return getnum();
}
int getnum()
{
	int num = 0;
	if (scanf("%d", &num) == 0)
	{
		char buf[256];
		gets(buf, sizeof(buf));
	}
	return num;
}

void AddCustomer()
{
	FILE* c_fp = fopen("cus_list.txt", "a");

	printf("Customer number: ");
	scanf("%d", &cus_list[carr].id);
	printf("Customer name: ");
	scanf("%s", &cus_list[carr].name);
	printf("Social security number: ");
	scanf("%s", &cus_list[carr].ssnum);
	printf("Phone number: ");
	scanf("%s", &cus_list[carr].phone);
	printf("Address: ");
	scanf("%s", &cus_list[carr].address);

	fprintf(c_fp, "\n%d,%s,%s,%s,%s"
		, cus_list[carr].id
		, cus_list[carr].name
		, cus_list[carr].ssnum
		, cus_list[carr].phone
		, cus_list[carr].address);

	carr++;
	fclose(c_fp);
}

void FindCustomer()
{
	int i, idx;
	char phone[30];
	printf("Phone number: ");
	scanf("%s", phone);

	for (i = 0; i < carr; i++)
	{
		if (strcmp(phone, cus_list[i].phone) == 0)
		{
			idx = i;
			i = carr;
		}
		else idx = -1;
	}
	if (idx == -1)
		printf("There is no matching customer.\n");
	else
	{
		printf("%d, %s, %s, %s, %s\n"
			, cus_list[idx].id
			, cus_list[idx].name
			, cus_list[idx].ssnum
			, cus_list[idx].phone
			, cus_list[idx].address);
	}
}

void ViewAllCustomer()
{
	int i;
	for (i = 0; i < carr; i++)
	{
		printf("%d, %s, %s, %s, %s\n"
			, cus_list[i].id
			, cus_list[i].name
			, cus_list[i].ssnum
			, cus_list[i].phone
			, cus_list[i].address);
	}
}

void AddVideo()
{
	FILE* v_fp = fopen("vid_list.txt", "a");

	printf("Video number: ");
	scanf("%d", &vid_list[varr].id);
	printf("Video name: ");
	scanf("%s", vid_list[varr].title);
	printf("Genre: ");
	scanf("%s", vid_list[varr].genre);
	printf("Rental fee: ");
	scanf("%d", &vid_list[varr].rental_fee);
	printf("Registration date: ");
	scanf("%s", vid_list[varr].reg_date);
	vid_list[varr].rentaled_or_not = 0;

	fprintf(v_fp, "\n%d,%s,%s,%d,%s,%d"
		, vid_list[varr].id
		, vid_list[varr].title
		, vid_list[varr].genre
		, vid_list[varr].rental_fee
		, vid_list[varr].reg_date
		, vid_list[varr].rentaled_or_not);

	varr++;
	fclose(v_fp);
}

void ViewVideo()
{
	int i, idx;
	char title[30];
	printf("Video name: ");
	scanf("%s", title);

	for (i = 0; i < varr; i++)
	{
		if (strcmp(title, vid_list[i].title) == 0)
		{
			idx = i;
			i = varr;
		}
		else idx = -1;
	}
	if (idx == -1)
		printf("There is no matching video.\n");
	else
	{
		printf("%d, %s, %s, %d, %s, %d\n"
			, vid_list[idx].id
			, vid_list[idx].title
			, vid_list[idx].genre
			, vid_list[idx].rental_fee
			, vid_list[idx].reg_date
			, vid_list[idx].rentaled_or_not);
	}
}

void ViewFullVideo()
{
	int i;
	for (i = 0; i < varr; i++)
	{
		printf("%d, %s, %s, %d, %s, %d\n"
			, vid_list[i].id
			, vid_list[i].title
			, vid_list[i].genre
			, vid_list[i].rental_fee
			, vid_list[i].reg_date
			, vid_list[i].rentaled_or_not);
	}
}

void Rental()
{
	int i, vid_id, cus_id;

	for (i = 0; i < varr; i++)
	{
		if (vid_list[i].rentaled_or_not == 0)
			printf("%d, %s, %s, %d, %s, %d\n"
				, vid_list[i].id
				, vid_list[i].title
				, vid_list[i].genre
				, vid_list[i].rental_fee
				, vid_list[i].reg_date
				, vid_list[i].rentaled_or_not);
	}
	printf("Please input video number to rental: ");
	scanf("%d", &vid_id);
	vid_list[vid_id - 1].rentaled_or_not = 1;

	for (i = 0; i < carr; i++)
	{
		printf("%d, %s, %s, %s, %s\n"
			, cus_list[i].id
			, cus_list[i].name
			, cus_list[i].ssnum
			, cus_list[i].phone
			, cus_list[i].address);
	}

	printf("Please input customer number: ");
	scanf("%d", &cus_id);

	rent.id = rent_id++;
	rent.vid_id = vid_list[vid_id - 1].id;
	rent.cus_id = cus_id;
	rent.returned_or_not = 0;
}

void Return()
{
	int i, vid_id, cus_id;

	for (i = 0; i < varr; i++)
	{
		if (vid_list[i].rentaled_or_not == 1)
			printf("%d, %s, %s, %d, %s, %d\n"
				, vid_list[i].id
				, vid_list[i].title
				, vid_list[i].genre
				, vid_list[i].rental_fee
				, vid_list[i].reg_date
				, vid_list[i].rentaled_or_not);
	}
	printf("Please input video number to return: ");
	scanf("%d", &vid_id);
	vid_list[vid_id - 1].rentaled_or_not = 0;

	rent.vid_id;
	rent.returned_or_not = 1;
}