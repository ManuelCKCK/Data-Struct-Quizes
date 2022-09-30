#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define SIZE 100


int currentid[10] = {0,0,0};
struct Movie
{
	char id[10];
	char nama[21];
	char genre[21];
	double rating;
	double year;
	Movie *next;
	Movie *prev;
};

Movie *head[SIZE];
Movie *tail[SIZE];

int getHash(char id[])
{
	int total = 0;
	total = id[4] + id[2] - id[3];
	return total%SIZE;
}

void push(Movie *node)
{
	int index = getHash(node->id);
	if(!head[index]){
		head[index] = node;
		return;
	}
	node->next = head[index];
	head[index] = node;
}

bool isValidname(char nama[])
{
	int len = strlen(nama);
	return len >= 5 && len <= 20;
}

bool isValidgenre(char genre[])
{
return strcmpi(genre, "Adventure") == 0|| strcmpi(genre, "Romance") == 0|| strcmpi(genre, "Comedies") == 0;
}

bool isValidrating(double rating)
{
	return rating >= 0 && rating <= 5;
}

bool isValidyear(double year)
{
	return year >=1900 && year <=2020;
}

void insertIntoTable(Movie *movie)
{
	 int key = getHash(movie->id);
	 
	 if(head[key] == NULL)
	 {
	 	head[key] = tail[key] = movie;
	 	return;
	 }
	 //push tail
	 tail[key]->next = movie;
	 movie->prev = tail[key];
	 tail[key] = movie;
}

void insertMenu()
{
	char nama[101];
	do
	{
		printf("Input Movie Title [LENGTH : 5-20] :");
		scanf("%[^\n]",nama);
		getchar();
	}while(!isValidname(nama));
	
	char genre[101];
	do
	{
		printf("Input Movie Genre [Adventure | Romance | Comedies] (Case Insensitive) :");
		scanf("%[^\n]",genre);
		getchar();
	}while(!isValidgenre(genre));
	
	double rating;
	do
	{
		printf("Input Movie's Rating [RANGE : 0.0 - 5.0] :");
		scanf("%lf",&rating);
		getchar();
	}while(!isValidrating(rating));
	
	double year;
	do
	{
		printf("Input Movie's year [RANGE : 1900-2020] :");
		scanf("%lf",&year);
		getchar();
	}while(!isValidyear(year));
	
	char id[10];
	if(strcasecmp(genre,"Adventure") == 0){
		id[0] = 'A';
		id[1] = 'E';
	}
	else if(strcasecmp(genre,"Romance") == 0){
		id[0] = 'R';
		id[1] = 'E';
	}
	else if(strcasecmp(genre,"Comedies") == 0){
		id[0] = 'C';
		id[1] = 'S';
	}
	id[2] = currentid[0];
	id[3] = currentid[1];
	id[4] = currentid[2];


printf("New Movie with ID [%s%d%d%d] has been added!\n\n",id,currentid[0],currentid[1],currentid[2]);
Movie *movie = (Movie*) malloc(sizeof(Movie));
	strcpy(movie->id,id);
	strcpy(movie->nama,nama);
	strcpy(movie->genre,genre);
	movie->rating = rating;
	movie->year = year;
	movie->prev = NULL;
	movie->next = NULL;
	
	insertIntoTable(movie);
}

void viewMenu()
{

	int flag = 0;
	printf("LIST OF FILM\n");
	printf("------------\n\n");
	for(int i=0;i<SIZE;i++)
	{
		if(head[i] != 0)
		{
			Movie* temp = head[i];
			while(temp != NULL)
			{
				flag = 1;
				printf("ID : [%s%d%d%d]\n",temp->id,temp->id[2],temp->id[3],temp->id[4]);
				printf("TITLE : %s\n",temp->nama);
				printf("GENRE : %s\n",temp->genre);
				printf("RATING : %.1lf\n",temp->rating);
				printf("YEAR : %.0lf\n",temp->year);
				printf("\n");
				temp = temp->next;
			}
		}
	}
	if(flag == 0){
		printf("No data !!!\n\n");
	}
	printf("Press any key to continue..."); getchar();

}

Movie* searchTable(char id[])
{
	int key = getHash(id);
	
	Movie *curr = head[key];
	while(curr != NULL)
	{
		if (strcmp(curr->id,id) == 0)
		{
			return curr;
		}
		curr = curr->next;
	}
}

void deleteMenu()
{
	viewMenu();
	
	char id[10];
	printf("Input movie id to remove: ");
	scanf("%s", id);
	getchar();
	
	Movie *movie = searchTable(id);
	
	if(movie == NULL)
	{
		puts("Movie not found!!!\n");
		return;
	}
	
	int key = getHash(id);
	

	// list cuman satu elemen
	if(head[key] == tail[key])
	{
		head[key] = tail[key] = NULL;
		free(movie);
		return;
	}
	//pop head
	if(head[key] = movie)
	{
		head[key] = head[key]->next;
		head[key] = head[key]->prev;
		head[key]->prev = NULL;
		free(movie);
		return;
	}
	//pop tail
	if(head[key] = movie)
	{
		tail[key] = tail[key]->prev;
		tail[key] = tail[key]->next;
		tail[key]->next = NULL;
		free(movie);
		return;
	}
	// list lebih dari satu elemen
	movie->prev->next = movie->next;
	movie->next->prev = movie->prev;
	free(movie);
}

int main()
{

	
	while(true)
	{
		viewMenu();
		puts("NEDFLIZ");
		puts("====================");
		puts("1. Add New Movie");
		puts("2. View Movies");
		puts("3. Delete Movie");
		puts("4. Exit");
		
		int input;
		do
		{
			printf("Choose [1-4] >  ");
			scanf("%d",&input);
			getchar();
		}
		while(input < 1 || input > 4);
		
		switch(input)
	    {
		case 1: insertMenu(); break;
		case 2: viewMenu(); break;
		case 3: deleteMenu(); break;
		case 4: printf("Thank you!"); return 0; 
	    }
		
	}
	return 0;
}
