#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
void clear_keyboard_buffer(void);
Boolean game(GENERIC_VECTOR hVector[]);
int main(int argc, char* argv[])
{
	int play_again=1;
	int w =0;
	int l=0;
	char c;
	int i;
	FILE* fp = fopen("dictionary.txt","r");
	MY_STRING hString = my_string_init_default();
	GENERIC_VECTOR hVector[30];
	for(i=0;i<30;i++) hVector[i] = NULL;
	for(i=0;i<30;i++)hVector[i]=generic_vector_init_default(my_string_assignment, my_string_destroy);
	while(my_string_extraction(hString,fp))generic_vector_push_back(hVector[my_string_get_size(hString)-1],hString);
	
	//test Code
	/*
	MY_STRING hKey = my_string_init_c_string("---");
	tree_add_words(hVector[3], &hTree, hKey, 'c');
	my_string_destroy(&hKey);

	*/
	while(play_again == 1)
	{
		if(!game(hVector))
		{
			w++;
			printf("HAHA PATHETIC HUMAN.\n");
		}
		else
		{
			l++;
			printf("HA..wait..\nYOU WON???\nIMPOSSIBLE\ni mean whatever\ngg ig, lol\n");
		}
		printf("I won %d times, you won %d times.\n",w,l);
		printf("Play Again? (y) or (n):");
		int noc = scanf("%c",&c);	
		printf("%c\n",c);
		while(noc != 1 || (c != 'y' && c!='Y' && c!='n' && c!='N'))
		{
			clear_keyboard_buffer();
			printf("Please input either (y) or (n).\n");
			printf("Play Again? (y) or (n):");
			int noc = scanf("%c",&c);	
		}
		clear_keyboard_buffer();
		if(c == 'y' || c == 'Y') play_again = 1;
		else play_again = 0;
	}
	for(i=0;i<30;i++)
	{
		generic_vector_destroy(hVector+i);
	}
	fclose(fp);
	my_string_destroy(&hString);
	return 0;
}
Boolean game(GENERIC_VECTOR hVector[])
{	
	//init
	TREE hTree = tree_init_default();
	if(hTree == NULL)
	{
		printf("hTree is NULL\n");
		return 3;
	}
	Status status;
	MY_STRING hKey = NULL;
	hKey = my_string_init_default();
	MY_STRING letters_used = my_string_init_default();
	MY_STRING temp = my_string_init_default();
	int noc,d,i,j;
	char c;
	Boolean already_guessed;
	Boolean boolean = FALSE;
	GENERIC_VECTOR possible_words = generic_vector_init_default(my_string_assignment, my_string_destroy);
	//game start
	printf("Welcome to Hangman, you pathetic Human.  Try to beat me...if you dare.\n");
	printf("How long of a word do you want to guess?");
	//Letters
	noc = scanf("%d",&d);
	while(noc != 1 || d<= 0 ||  d>30 || generic_vector_get_size(hVector[d-1]) == 0)
	{
		clear_keyboard_buffer();
		if(noc != 1) printf("Give me a Number...you know the things on a calculator.\n");
		else if(d<=0 || d>30) printf("The Number you have given me is saddly out of bounds.  You remeber how words work, yes?\nPick a number that is at least 1 but smaller than 30.\n");
		else if(generic_vector_get_size(hVector[d-1]) == 0) printf("There are no words of %d length! You should know that, pathetic flesh.\n",d);
		printf("How long of a word do you want to guess?");
		noc = scanf("%d",&d);	
	}
	clear_keyboard_buffer();
	int number_of_letters = d;

	//gueses
	printf("Now how many guesses would you like?");
	noc = scanf("%d",&d);
	while(noc != 1 || d<=0)
	{
		clear_keyboard_buffer();
		if(noc != 1) printf("Give me a number...you know the things on a calculator.\n");
		else if (d<=0) printf("You can't have zero or negative guesses. Idiot\n");
		printf("How many guesses?");
		noc = scanf("%d",&d);
	}
	clear_keyboard_buffer();
	int number_of_guesses = d;
	
	//cheater?
	printf("Are you a dirty cheater who wishes to see a running total of possible words left? (y) or (n):");
	noc = scanf("%c",&c);
	while(noc != 1 || (c != 'y' && c!='Y' && c != 'n' && c != 'N') )
	{
		clear_keyboard_buffer();
		if(noc != 1) printf("Please actually provide a letter.  Or do you need a lesson on ABC's?\n");
		else printf("That letter is meaningless.  Please either put in (y) for yes or (n) for no.\n");
		printf("Are you a dirty cheater who wishes to see a running total of possible words left? (y) or (n):");
		noc = scanf("%c",&c);
	}
	clear_keyboard_buffer();
	Boolean cheater = FALSE;
	if(c == 'y' || c=='Y') cheater = TRUE;
	
	//Game Set up
	for(i=0;i<generic_vector_get_size(hVector[number_of_letters-1]);i++) generic_vector_push_back(possible_words,generic_vector_at(hVector[number_of_letters-1],i));
	for(i=0;i<number_of_letters;i++) my_string_push_back(hKey, '-'); 	
	
	printf("\n\n***\n\n");
	//Game Loop
	for(i=0;i < number_of_guesses && boolean == FALSE;)
	{
		printf("The current knowledge of the word is '%s'\n",my_string_c_str(hKey));
		if(my_string_get_size(letters_used))
		{
			printf("Your letters guessed are: ");
			for(j=0;j<my_string_get_size(letters_used);j++) printf("%c, ",*my_string_at(letters_used,j));
			printf("\n");	
		}
		if(cheater) printf("There are %d possible words remaining\n",generic_vector_get_size(possible_words));
		printf("You have %d guesses left\n",number_of_guesses-i);
		printf("Which letter would you like to guess?\n");
		noc = scanf("%c",&c);
		clear_keyboard_buffer();
		already_guessed = FALSE;
		if(i != 0)
			for(j=0;j<my_string_get_size(letters_used) && !already_guessed;j++) 
			{
				if(*my_string_at(letters_used,j) == tolower(c))
				{
					already_guessed = TRUE;
				}
			}
		while(noc != 1 || !isalpha(c) || already_guessed == TRUE)
		{
			if(!isalpha(c))
				printf("A letter...the things from the alphabet!\n");
			if(already_guessed)
				printf("FOOLISH, YOU ALREADY GUESSED THAT!!\n");
			already_guessed = FALSE;
			printf("Which letter would you like to guess?\n");
			noc = scanf("%c",&c);
			clear_keyboard_buffer();
			if(i != 0)for(j=0;j<my_string_get_size(letters_used) && !already_guessed;j++) if(*my_string_at(letters_used,j) == tolower(c)) already_guessed = TRUE;
		}
		c = tolower(c);
		if(!tree_add_words(possible_words, &hTree, hKey, c))
		{
			printf("Failure to add words to Tree\n");
			exit(1);
		}
		my_string_assignment(&temp,tree_key_find(hTree, possible_words));
		if(my_string_compare(temp,hKey) == 0)
		{
			printf("WRONG, %c is not in the word!! PATHETIC\n",c);
			i++;
		}
		else
		{
			printf("...correct...somehow...%c is in the word.  Well done\n",c);
		}
		my_string_assignment(&hKey,temp);	
		my_string_push_back(letters_used, c);
		boolean = TRUE;
		for(j=0;j<my_string_get_size(hKey) && boolean != FALSE;j++)
		{
			if(*my_string_at(hKey, j) == '-') 
			{
				boolean = FALSE;
			}
		}
		printf("\n\n***\n\n");
	}
	printf("The word I was thinking of was '%s'\n",my_string_c_str(generic_vector_at(possible_words,0)));
	//end	
	my_string_destroy(&hKey);
	my_string_destroy(&letters_used);
	my_string_destroy(&temp);
	generic_vector_destroy(&possible_words);
	tree_destroy(&hTree);
	return boolean;
}
void clear_keyboard_buffer(void)
{
	char c;
	int NOC = scanf("%c", &c);
	while (NOC != -1  && c != '\n')
		{
			scanf("%c", &c);
		}
}

