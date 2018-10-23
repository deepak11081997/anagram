#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#include "WORDS.c"


extern char* words[12][50];

int maxx, maxy;


void welcome()
{
	setfillstyle(1, DARKGRAY);
	bar(maxx/2-350, maxy/2-280, maxx/2+350, maxy/2+280);
	
	setcolor(RED);
	outtextxy(maxx/2-100, maxy/2-150,"   ANAGRAM");
	outtextxy(maxx/2-120, maxy/2+80,"PRESS ANY KEY TO CONTINUE..!");
	
	setcolor(2);
	outtextxy(maxx/2-120, maxy/2-100,"Instructions:");
	outtextxy(maxx/2-120, maxy/2-80,"You will recieve jumbled words");
	outtextxy(maxx/2-120, maxy/2-60,"Try to solve as many as you can");

	setcolor(BLUE);
	outtextxy(maxx/2-120, maxy/2-40,"Points are as follows:-");
	outtextxy(maxx/2-120, maxy/2-20,"Score is multiplied with 10 and the level");
	
	setcolor(YELLOW);
	outtextxy(maxx/2-120, maxy/2-0,"EG: Level 1--> score is 10*1");

	getch();
	
	setfillstyle(1, 0);
	setcolor(0);
	bar(maxx/2-350, maxy/2-280, maxx/2+350, maxy/2+280);

	return 0;
}


int rand_int(int number) {

	int limit = RAND_MAX - RAND_MAX % number;
	int random_number;
	time_t t;

	srand((unsigned) time(&t));
	do {
	random_number = rand();
	}while (random_number >= limit);

	return random_number % number;

}


void swap(char *word) {

	int counter, counter_2, number;
	char tmp;
	number = strlen(word);

	for (counter = number - 1; counter > 0; counter--) 
	{
		counter_2 = rand_int(counter + 1);
		tmp = word[counter_2];
		word[counter_2] = word[counter];
		word[counter] = tmp;
	}

}


int random_number_generator()
{
   int random_number;
   time_t t;
   
   srand((unsigned) time(&t));
   
   random_number = rand() %50;

   return random_number;
}


void gameover()
{
	int gm = 0, gd = DETECT, counter, counter_2;
	initgraph(&gd, &gm, " ");

	for(counter = 1; counter <= 51; counter += 	4)
	{
		setcolor(counter);
		sound(400-counter);
		outtextxy(260-counter, 340-counter*10, "GAME OVER");
		nosound();
		go(0, 60, 20, 80, random(15), random(15));
		delay(3);
		go(400, 460, 420, 480, random(15), random(15));
	}

}


void go(int sy1, int ey1, int sy2, int ey2, int k, int h)
{
	int counter, counter_2;
	
	for(counter = sy1; counter <= ey1; counter += 40)        
	{
		for(counter_2 = 0; counter_2 <= 640; counter_2 += 40)
		{
			setcolor(k);
			rectangle(counter_2, 1 + counter, 20 + counter_2, 21 + counter);
			setfillstyle(SOLID_FILL, k);
			floodfill(10 + counter_2, 10 + counter, k);
			
			setcolor(h);
			rectangle(20 + counter_2, 1 + counter, 40 + counter_2, 21 + counter);
			setfillstyle(SOLID_FILL, h);
			floodfill(25 + counter_2, 10 + counter, h);
		}
	}
	
	for(counter_2 = sy2; counter_2 <= ey2; counter_2 += 40)
	{
		for(counter = 0; counter <= 640; counter += 40)
		{
			setcolor(h);
			rectangle(counter, 1 + counter_2, 20 + counter, 21 + counter_2);
			setfillstyle(SOLID_FILL, h);
			floodfill(10 + counter, 10 + counter_2, h);
			
			setcolor(k);
			rectangle(20 + counter, 1 + counter_2, 40 + counter, 21 + counter_2);
			setfillstyle(SOLID_FILL, k);
			floodfill(25 + counter, 10 + counter_2, k);
		}
	}

}


void main()
{
	int counter, level = 1, level_counter=1, score=0;
	
	int gd = DETECT, gm;
	char word_swapped[15], word_copy[15], user_answer[15];
	
	clrscr();
	
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	maxx = getmaxx();
	maxy = getmaxy();
	
	welcome();
	
	while(level <= 10)
	{
		setfillstyle(1, 0);
		setcolor(0);

		bar(maxx/2 - 350, maxy/2 - 280, maxx/2 + 350, maxy/2 + 280);

		if(level_counter <= 8)
		{
			int word_length = random_number_generator();

			printf("\n\n\n\t\t\tLEVEL%d\n\n\n", level);
	
			strcpy(word_swapped, words[level_counter-1][word_length]);
			strcpy(word_copy, word_swapped);

			LABEL_1 : swap(word_swapped);
			if(strcmp(word_swapped, word_copy) == 0)
				goto LABEL_1;

			for(counter = 0; counter < strlen(word_swapped); counter ++)
				printf("%c ", word_swapped[counter]);
			printf("\n");
			
			scanf("%s", user_answer);
			
			if((strcmp(user_answer, word_copy)) == 0)
			{
				printf("\n\nCongratulations!!!Correct answer\n\n\n\n");
				
				delay(1000);
				clrscr();
				
				score = score + 10 * level;
				level ++;
			}
			else
			{
				printf("Correct answer is:%s\n Score is:%d", word_copy, score);
				break;
			}
		}
		else
		{
			int word_length = random_number_generator();
			int user_word_length;
			
			printf("\n\n\n\t\t\tLEVEL%d\n", level);
			printf("Enter the word length between 12 to 14:");
			scanf("%d", &user_word_length);
			printf("\n\n");
			
			strcpy(word_swapped, words[user_word_length-4][word_length]);
			strcpy(word_copy, word_swapped);
			
			LABEL_2 : swap(word_swapped);
			if(strcmp(word_swapped, word_copy) == 0)
				goto LABEL_2;
			
			for(counter = 0; counter < strlen(word_swapped); counter ++)
				printf("%c ", word_swapped[counter]);
			printf("\n");
			
			scanf("%s", user_answer);
			
			if((strcmp(user_answer, word_copy)) == 0)
			{
				if(level_counter == 10)
				{
					printf("Congratulations!!!Correct Answer\nScore is:%d\n\n\n", score);
					break;
				}
				else
				{
					printf("\n\nCongratulations!!!Correct answer\n\n\n\n");
					
					delay(1000);
					clrscr();
					
					score = score + 10 * level;
					level ++; 
				}
			}
			else
			{
				printf("Correct answer is:%s\n Score is:%d", word_copy, score);
				break;
			}
		}
		
	level_counter ++;
	}
	
	delay(2000);
	gameover();
	getch();

}