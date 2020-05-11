///*Структура Mail содержит структуру Address получателя(город, улица, дом, квартира, индекс), вес посылки, почтовый 
//идентификатор.Структура Post содержит структуру Address текущего почтового отделения и динамический массив структур 
//Mail.Реализовать добавление объекта Mail, удаление, информативный вывод при поиске по идентификатору.Объекты структуры
//Mail должны быть отсортированы по индексу получателя и идентификатору посылки.*/
						



#pragma warning(disable:4996)
/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#define SIZE_OF_NAMES 150

typedef struct a {
	char* city;
	char* street;
	int house;
	int block;
	int index;
} Address;

typedef struct m {
	Address* address;
	int id;
} Mail;

typedef struct Post {
	Address address;
	Mail* mails;
} Post;

Mail* createMail(int id, Address* address) {
	Mail* mail = (Mail*)malloc(sizeof(Mail));
	mail->address = address;//заполняем адрес
	mail->id = id;
	return mail;
}

void sortMailByIdAndIndex(Mail* mails, int size) {//сортируем письма по id и индексу
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < i; ++j) {
			if (mails[j].address->index > mails[j + 1].address->index) {
				Mail tmp = mails[j];
				mails[j] = mails[j + 1];
				mails[j + 1] = tmp;
			}
			else if (mails[j].address->index == mails[j + 1].address->index) {
				if (mails[j].id > mails[j + 1].id) {
					Mail tmp = mails[j];
					mails[j] = mails[j + 1];
					mails[j + 1] = tmp;
				}
			}
		}
	}
}

Address* createAddress(char* city, char* street, int house, int block, int index) {//возвращает адрес
	Address* address =(Address*) malloc(sizeof(Address));
	address->city = city;
	address->street = street;
	address->house = house;
	address->block = block;
	address->index = index;
	return address;
}

int main() {
	Post* post = (Post*)malloc(sizeof(Post));
	printf("Enter address of post IN format: City Street House Block Index");
	char bufCity[SIZE_OF_NAMES];
	char bufStreet[SIZE_OF_NAMES];
	int house;
	int block;
	int index;
	scanf("%s %s %d %d %d", bufCity, bufStreet, &house, &block, &index);
	char* city = (char*)malloc(sizeof(char) * (strlen(bufCity) + 1));
	char* street = (char*)malloc(sizeof(char) * (strlen(bufStreet) + 1));
	strcpy(city, bufCity);
	strcpy(street, bufStreet);
	Address* postAddress = createAddress(city, street, house, block, index);
	post->address = *postAddress;

	int sizeOfMails = 5;
	int curSizeOfMails = 0;

	Mail* mails = (Mail*)malloc(sizeof(Mail) * sizeOfMails);
	int id = 0;
	post->mails = mails;//прмисваиваем массив писем
	int chose = -1;
	while (chose != 5) {
		chose = -1;
		printf("1. Adding\n"
			"2. Deletion\n"
			"3. Search by ID\n"
			"4. View mail\n"
			"5. Exit\n");
		scanf("%d", &chose);
		//        Mail* ptr = post->mails;
		switch (chose) {
		case 1:{
			if (curSizeOfMails == sizeOfMails) {
				sizeOfMails *= 2;
				post->mails = (Mail*)realloc(post->mails, sizeof(Mail) * sizeOfMails);
			}
			printf("City Street House Block Index\n");
			scanf("%s %s %d %d %d", bufCity, bufStreet, &house, &block, &index);
			city = (char*)malloc(sizeof(char) * (strlen(bufCity) + 1));
			street = (char*)malloc(sizeof(char) * (strlen(bufStreet) + 1));
			strcpy(city, bufCity);
			strcpy(street, bufStreet);
			Address* addr = createAddress(city, street, house, block, index);

			(post->mails + curSizeOfMails)->address = addr;
			(post->mails + curSizeOfMails)->id = id++;
			curSizeOfMails++;
			sortMailByIdAndIndex(mails, curSizeOfMails);
		}
			break;
		case 2://удаление
			printf("Enter ID\n");
			int id;
			scanf("%d", &id);
			for (int j = 0; j < curSizeOfMails; ++j) {
				if (curSizeOfMails != 1) {
					if (post->mails[j].id == id) {
						for (int i = j; i < curSizeOfMails - 1; ++i) {
							post->mails[j] = post->mails[j + 1];
						}
						curSizeOfMails--;
						break;

					}
				}
				else {
					curSizeOfMails = 0;
				}
			}
			break;

		case 3://поиск
			printf("Enter ID\n");
			scanf("%d", &id);
			for (int j = 0; j < curSizeOfMails; ++j) {
				if (post->mails[j].id == id) {
					printf("ID | City | Street | House | Block | Index\n");

					Mail curMail = post->mails[j];
					printf("%d | %s | %s | %d | %d | %d\n", curMail.id, curMail.address->city, curMail.address->street,
						curMail.address->house, curMail.address->block, curMail.address->index);
					break;
				}
			}
			break;


		case 4://вывод всей почты на экран
			printf("ID | City | Street | House | Block | Index\n");
			for (int i = 0; i < curSizeOfMails; ++i) {
				Mail curMail = post->mails[i];
				printf("%d | %s | %s | %d | %d | %d\n", curMail.id, curMail.address->city, curMail.address->street,
					curMail.address->house, curMail.address->block, curMail.address->index);
			}
			break;
		case 5://выход
			return 0;
		}
	}
}*/

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