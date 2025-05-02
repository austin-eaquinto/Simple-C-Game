/*
 ============================================================================
 Name        : Simple.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// I've learned how to use the stdbool.h and string.h libraries. The stdbool.h was pretty self explanatory
// to use but the string.h had certain structures that I had to learn about and how to use them. While
// working through developing this program I didn't end up using the string.h library but I left the initial
// pType variable I was using in in my playerInfo struct.

// Examples of the code I used from string.h included:
// strcpy(whatKind->type, "fire"); strcpy copied a string into the 'type' character array.
// strcmp(attacker->type, "fire") == 0; strcmp compares the the string stored in attacker->type to "fire"
// to check if they are equal. These two don't make complete sense without the context, but they did work.

struct playerInfo
{
	char pName[20];
	int pType;
//	char pType[10];
	int pHealth;
};

struct computerInfo
{
	char cName[10];
	int cType;
	int cHealth;
};

bool playerFlipACoin() // determine who goes first
{
	int first[] = {0, 1};
	int random = rand() % 2;

	if (first[random] == 1)
	{
		printf("Heads!\n");
		return true;
	}
	printf("Tails!\n");
	return false;
}

bool computerFlipACoin()
{
	int first[] = {0, 1};
	int random = rand() % 2;

	if (first[random] == 1)
	{
		return true;
	}
	return false;
}

void computerRandomType(struct computerInfo* whatKind) // assigns a random type to the computer
{
	int randomType = rand() % 3;

	switch (randomType)
	{
		case 0:
		{
			whatKind->cType = 1; // Fire
			break;
		}
		case 1:
		{
			whatKind->cType = 2; // Grass
			break;
		}
		case 2:
		{
			whatKind->cType = 3; // Water
			break;
		}
		default:
		{
			break;
		}
	}
}

#define FIRE 1
#define GRASS 2
#define WATER 3

int playerAttack(struct playerInfo* player, struct computerInfo* computer)
{
	int baseDamage = 5;
	int damage = baseDamage;

	if ((player->pType == FIRE && computer->cType == GRASS) ||
		(player->pType == GRASS && computer->cType == WATER) ||
		(player->pType == WATER && computer->cType == FIRE))
		{
			damage *= 2;
		}

	computer->cHealth -= damage;
	return damage;
}

int computerAttack(struct computerInfo* computer, struct playerInfo* player)
{
	int baseDamage = 5;
	int damage = baseDamage;

	if ((computer->cType == FIRE && player->pType == GRASS) ||
		(computer->cType == GRASS && player->pType == WATER) ||
		(computer->cType == WATER && player->pType == FIRE))
		{
			damage *= 2;
		}

	player->pHealth -= damage;
	return damage;
}

int playerTripleAttack(struct computerInfo* computer)
{
	int damage = 5;
	int totalDamage = 0;

	for (int i = 0; i < 3; i++)
	{
		if (playerFlipACoin())
		{
			computer->cHealth -= damage;
			totalDamage += damage;
		}
	}
	return totalDamage;
}

int computerTripleAttack(struct playerInfo* player)
{
	int damage = 5;
	int totalDamage = 0;

	for (int i = 0; i < 3; i++)
	{
		if (computerFlipACoin())
		{
			player->pHealth -= damage;
			totalDamage += damage;
		}
	}
	return totalDamage;
}

void getPlayerInfo(struct playerInfo* player)
{
	printf("What is your name?\n");
	scanf("%s", player->pName);
	printf("There are three types. Each has an advantage and disadvantage.\n");
	printf("Pick:\n1. Fire\n2. Grass\n3. Water\n4. Random\n");
	printf("Number: ");
	int type;
	scanf("%d", &type);

	if (type == 4)
	{
		player->pType = rand() % 3 + 1;
	}
	else
	{
		player->pType = type;
	}

	player->pHealth = 20;

	printf("\n");
}

void displayPlayerInfo(struct playerInfo* pInfo)
{
	char* typeName;
	switch (pInfo->pType)
	{
		case 1:
		{
			typeName = "Fire";
			break;
		}
		case 2:
		{
			typeName = "Grass";
			break;
		}
		case 3:
		{
			typeName = "Water";
			break;
		}
		default:
		{
			typeName = "Broken";
			break;
		}
	}
	printf("Your name: %s\n", pInfo->pName);
	printf("You chose: %s\n", typeName);
	printf("You have %d health\n", pInfo->pHealth);
	printf("\n");
}

void getOpponentInfo(struct computerInfo* opponent)
{
	strcpy(opponent->cName, "Computer");
	computerRandomType(opponent);
	opponent->cHealth = 20;
}

void displayOpponentInfo(struct computerInfo* cInfo)
{
	char* typeName;
	switch (cInfo->cType)
	{
		case 1:
		{
			typeName = "Fire";
			break;
		}
		case 2:
		{
			typeName = "Grass";
			break;
		}
		case 3:
		{
			typeName = "Water";
			break;
		}
		default:
		{
			typeName = "Broken";
			break;
		}
	}
	printf("Opponent: %s\n", cInfo->cName);
	printf("Opponent type: %s\n", typeName);
	printf("Opponent has %d health\n", cInfo->cHealth);
	printf("\n");
}

void displayPlayersInfo(struct playerInfo* player, struct computerInfo* opponent)
{
	displayPlayerInfo(player);
	displayOpponentInfo(opponent);
}

void PlayThrough(struct playerInfo* player, struct computerInfo* opponent)
{
	displayPlayersInfo(player, opponent);

	if (playerFlipACoin())
	{
		printf("You go first!\n");
		while (player->pHealth > 0 && opponent->cHealth > 0)
		{
			int turn;
			printf("1. Normal Attack\n2. Triple Attack\n");
			printf("Enter number: ");
			scanf("%d", &turn);

			if (turn == 1)
			{
				int damage = playerAttack(player, opponent);
				printf("You dealt %d damage!\n", damage);
			}
			else if (turn == 2)
			{
				int damage = playerTripleAttack(opponent);
				printf("You dealt %d damage with a triple attack!\n", damage);
			}
			printf("Opponent health: %d\n", opponent->cHealth);

			if (opponent->cHealth > 0)
			{
				if (computerFlipACoin())
				{
					int damage = computerAttack(opponent, player);
					printf("Opponent dealt %d damage!\n", damage);
					printf("Your health: %d\n", player->pHealth);
				}
				else
				{
					int damage = computerTripleAttack(player);
					printf("Opponent dealt %d damage with a triple Attack!\n", damage);
					printf("Your health: %d\n", player->pHealth);
				}
			}
		}
	}
	else
	{
		printf("You go second.\n");
		while (player->pHealth > 0 && opponent->cHealth > 0)
		{
			if (computerFlipACoin())
			{
				int damage = computerAttack(opponent, player);
				printf("Opponent dealt %d damage!\n", damage);
				printf("Your health: %d\n", player->pHealth);
			}
			else
			{
				int damage = computerTripleAttack(player);
				printf("Opponent dealt %d damage with a triple Attack!\n", damage);
				printf("Your health: %d\n", player->pHealth);
			}

			if (player->pHealth > 0)
			{
				int turn;
				printf("1. Normal Attack\n2. Triple Attack\n");
				printf("Enter number: ");
				scanf("%d", &turn);

				if (turn == 1)
				{
					int damage = playerAttack(player, opponent);
					printf("You dealt %d damage!\n", damage);
				}
				else
				{
					int damage = playerTripleAttack(opponent);
					printf("You dealt %d damage with a triple attack!\n", damage);
				}
			}
			printf("Opponent health: %d\n", opponent->cHealth);
		}
	}

	if (player->pHealth <= 0)
	{
		printf("You lost!\n");
	}
	else
	{
		printf("You won!\n");
	}
}

void gameInstructions()
{
	printf("This is a game against a 'computer'.\n");
	printf("The goal is to get the computer's health to zero before it gets your health to zero.\n");
	printf("There is a normal attack and a triple attack.\n");
	printf("Normal attack does 5 damage.\n");
	printf("Triple attack does 5 damage for each 'heads' from a behind the scenes coin flip function and 0 for each 'tails'.\n");
	printf("\n");
	printf("There are three types that come into play- Fire, Grass, Water.\n");
	printf("Each one has an advantage over one other.\n");
	printf("You may choose your type but the computer is randomly assigned a type.\n");
	printf("If there is a type advantage, had by you or the computer, there is a +5 damage to the normal attack.\n");
	printf("The triple attack is unaffected by the type advantage.\n");
	printf("\n");
	printf("First one to get the other's health to zero wins.\n");
	printf("\n");
	printf("The game will repeat until you enter '0' at the main menu.\n");
}

int main(void) {

	struct playerInfo player;
	struct computerInfo opponent;

	printf("Welcome to the game.\n");

	while (1)
	{
		printf("Pick a number:\n1. About this game\n2. Play Game\n0. Quit\n");
		int pick = 0;
		scanf("%d", &pick);

		switch(pick)
		{
		case 1:
		{
			gameInstructions();
			break;
		}
		case 2:
		{
			getPlayerInfo(&player);
			getOpponentInfo(&opponent);
			PlayThrough(&player, &opponent);
			break;
		}
		case 0:
		{
			printf("Quitting...\n");
			return EXIT_SUCCESS;
		}
		default:
		{
			printf("Not an option. Please try again\n");
			break;
		}
		}
	}
}
