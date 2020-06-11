#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_address
{
	char city[20];
	char street[20];
	int	number_house;
	int	flat;
	int	index;
}	Adress;

typedef struct	s_mail
{
	Adress	recipient;
	int	weight;
	int	mail_id;
}	Mail;

typedef struct	s_post
{
	Adress	adress_post_office;
	Mail* mail_array;
	int	size_array;
}	Post;

void sort_struct(Post* post_office)
{
	int i = 0;
	Mail temp;

	while (i < post_office->size_array - 1)
	{
		temp = post_office->mail_array[i + 1];
		if (post_office->mail_array[i].recipient.index > temp.recipient.index)
		{
			post_office->mail_array[i + 1] = post_office->mail_array[i];
			post_office->mail_array[i] = temp;
			i = 0;
			continue;
		}
		else if (post_office->mail_array[i].recipient.index == temp.recipient.index && post_office->mail_array[i].mail_id > temp.mail_id)
		{
			post_office->mail_array[i + 1] = post_office->mail_array[i];
			post_office->mail_array[i] = temp;
			i = 0;
			continue;
		}
		i++;
	}
}

void print_struct(Mail mail)
{
	printf("mail_id: %d\nweigth: %d\nAddress: %s, %s, home %d, flat %d, index %d\n\n",
		mail.mail_id, mail.weight, mail.recipient.city, mail.recipient.street,
		mail.recipient.number_house, mail.recipient.flat, mail.recipient.index);
}

void print_struct_full(Post* post_office)
{
	for (int i = 0; i < post_office->size_array; i++)
		print_struct(post_office->mail_array[i]);
}

void search_mailID(Post* post_office, int mail_id)
{
	for (int i = 0; i < post_office->size_array; i++)
		if (post_office->mail_array[i].mail_id == mail_id)
			print_struct(post_office->mail_array[i]);
}
void add_mail(Post* post_office, const char* city, const char* street, int number_house, int flat, int index, int weight, int mail_id)
{
	post_office->size_array++;
	if (post_office->size_array == 1)
		post_office->mail_array = (Mail*)malloc(sizeof(Mail) * 1);
	else
		post_office->mail_array = (Mail*)realloc(post_office->mail_array, sizeof(Mail) * post_office->size_array);
	strcpy(post_office->mail_array[post_office->size_array - 1].recipient.city, city);
	strcpy(post_office->mail_array[post_office->size_array - 1].recipient.street, street);
	post_office->mail_array[post_office->size_array - 1].recipient.number_house = number_house;
	post_office->mail_array[post_office->size_array - 1].recipient.flat = flat;
	post_office->mail_array[post_office->size_array - 1].recipient.index = index;
	post_office->mail_array[post_office->size_array - 1].weight = weight;
	post_office->mail_array[post_office->size_array - 1].mail_id = mail_id;
	sort_struct(post_office);
}

int	main()
{
	Post post_office;

	strcpy(post_office.adress_post_office.city, "Moscow");
	strcpy(post_office.adress_post_office.city, "Festival");
	post_office.adress_post_office.number_house = 5;
	post_office.adress_post_office.flat = 4;
	post_office.adress_post_office.index = 192168;
	post_office.size_array = 0;
	add_mail(&post_office, "Kazan", "Shorina", 12, 3, 255255, 10, 5);
	add_mail(&post_office, "Moscow", "Lomonosov", 1, 5, 255255, 8, 2);
	add_mail(&post_office, "VP", "Gagarina", 2, 8, 255456, 9, 3);
	add_mail(&post_office, "Mars", "Lermontovo", 6, 15, 123255, 12, 10);
	add_mail(&post_office, "Moon", "Kirova", 7, 19, 255255, 25, 1);
	search_mailID(&post_office, 10);
	print_struct_full(&post_office);
	free(post_office.mail_array);
}