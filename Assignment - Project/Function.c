#include"Header.h"

struct card {
	int rank;
	int suit;
};

struct Player {
	char name[80];
	struct card hand[5];
	int point;
	int noCard;
};

struct Computer {
	struct card hand[5];
	int point;
	int noCard;
};

struct card DECK[52];
int cur_card_index = 0;

void Display_Rank(int rank) {
	switch (rank) {
	case 1:
		printf("A"); break;
	case 11:
		printf("J"); break;
	case 12:
		printf("Q"); break;
	case 13:
		printf("K"); break;
	default:
		printf("%d", rank);
	}	
}

void Display_Suit(int suit) {
	switch (suit) {
	case 1:
		printf("Diamonds"); break;
	case 2:
		printf("Clubs"); break;
	case 3:
		printf("Hearts"); break;
	case 4:
		printf("Spades"); break;
	}
}

int Card_Value(int rank) {
	int value;
	switch (rank) {
	case 1:
		value = 11; break;
	case 11:
		value = 10; break;
	case 12:
		value = 10; break;
	case 13:
		value = 10; break;
	default:
		value = rank;
	}
	return value;
}

void Shuffle() {
	for (int i = 0; i < 52; i++) {
		DECK[i].rank = rand() % 13 + 1;
		DECK[i].suit = rand() % 4 + 1;
		for (int j = 0; j < i; j++) {
			if (DECK[i].rank == DECK[j].rank && DECK[i].suit == DECK[j].suit) {
				i--;
				break;
			}
		}
	}
}

int calPoint(struct card* hand, int noCard) {
	int point = 0;
	for (int i = 0; i < noCard; i++) {
		point += Card_Value(hand[i].rank);
	}
	return point;
}

void printDeck() {
	for (int i = 0; i < 52; i++) {
		Display_Rank(DECK[i].rank);
		printf(" ");
		Display_Suit(DECK[i].suit);
		printf("\n");
	}
}

void printCard(struct card c) {
	Display_Rank(c.rank);
	printf(" ");
	Display_Suit(c.suit);
}

void printHand(struct card* hand, int noCard) {
	for (int i = 0; i < noCard; i++) {
		printCard(hand[i]);
		printf(" ");
	}
}

void copyHand(struct card* hand1, struct card* hand2) {
	for (int i = 0; i < 5; i++) {
		hand1[i] = hand2[i];
	}
}

void copyPlayer(struct Player* p1, struct Player* p2) {
	strcpy(p1->name, p2->name);
	copyHand(p1->hand, p2->hand);
	p1->noCard = p2->noCard;
	p1->point = p2->point;
}




void Handling(struct Player* p, struct Computer* com, int n) {
	for (int i = 0; i < (n + 1) * 2; i++) {
		if (i % (n + 1) == n)
			com->hand[com->noCard++] = DECK[cur_card_index++];
		else
			p[i % (n + 1)].hand[p[i % (n + 1)].noCard++] = DECK[cur_card_index++];
	}

	for (int i = 0; i < n; i++) {
		p[i].point = calPoint(p[i].hand, p[i].noCard);
		printf("%s: ", p[i].name);
		printHand(p[i].hand, p[i].noCard);
		printf("\n%s's point: %d\n", p[i].name, p[i].point);
	}
}

void Player_turn(struct Player* p,int n) {
	char buff;
	for (int i = 0; i < n; i++) {
		printf("\n-----------------------------------------------\n");

		while (true) {
			printf("Player [%s] wants to hit or stay ? <H> or <S>", &p[i].name);
			buff = toupper(getch());
			if (buff == 'H') {
				printf("\nPlayer [%s] hit a card: ", p[i].name);

				p[i].hand[p[i].noCard++] = DECK[cur_card_index++];
				p[i].point = calPoint(p[i].hand, p[i].noCard);
				printHand(p[i].hand, p[i].noCard);
				printf("\nPoint: %d\n", p[i].point);
			}
			else if (buff == 'S') {
				printf("\nPlayer [%s] stayed.", p[i].name);
				break;
			}
			else {
				printf("\nError ! Please enter again !\n");
			}


			if (p[i].point > 21) {
				printf("\nPlayer [%s] is busted !", p[i].name);
				break;
			}
			else if (p[i].noCard < 5 && p[i].point == 21) {
				printf("\nPlayer [%s] got BLACKJACK !", p[i].name);
				break;
			}
			else if (p[i].noCard == 5 && p[i].point <= 21) {
				printf("\nPlayer [%s] got Magic Five !", p[i].name);
				break;
			}
		}
	}
}

void Computer_turn(struct Computer* com) {
	printf("\n-----------------------------------------------\n");

	printf("Computer: ");
	printHand(com->hand, com->noCard);

	int stay_point = rand() % (21 - 15 + 1) + 15;
	while (calPoint(com->hand, com->noCard) < stay_point && com->noCard <= 5) {
		com->hand[com->noCard++] = DECK[cur_card_index++];
		printf("\nComputer hit a card: ");
		printCard(com->hand[com->noCard - 1]);
	}
	com->point = calPoint(com->hand, com->noCard);
	printf("\n\nComputer: ");
	printHand(com->hand, com->noCard);
	printf("\nPoint: %d", com->point);
}

void ProcessFinish(struct Player* p, int n, struct Computer com) {
	for (int i = 0; i < n; i++) {
		printf("%s: ", p[i].name);
		printHand(p[i].hand, p[i].noCard);
		printf("\n%s's point: %d\n", p[i].name, p[i].point);
	}

	printf("Computer: ");
	printHand(com.hand, com.noCard);
	printf("\nPoint: %d", com.point);

	printf("\n-----------------------------------------------\n");

	int noWin = 0;
	int noDraw = 0;
	struct Player* win_players = NULL;
	struct Player* draw_players = NULL;

	for (int i = 0; i < n; i++) {
		if (p[i].point < 16 || p[i].point > 21) {
			if (com.point > 21) {
				draw_players = (struct Player*)realloc(draw_players, ++noDraw * sizeof(struct Player));
				copyPlayer(&draw_players[noDraw - 1], &p[i]);
			}
		}
		else
		{
			if (com.point > 21) {
				win_players = (struct Player*)realloc(win_players, ++noWin * sizeof(struct Player));
				copyPlayer(&win_players[noWin - 1], &p[i]);
			}
			else {
				if (p[i].point == com.point) {
					draw_players = (struct Player*)realloc(draw_players, ++noDraw * sizeof(struct Player));
					copyPlayer(&draw_players[noDraw - 1], &p[i]);
				}
				else if (p[i].point > com.point || (p[i].noCard == 5 && com.noCard != 5)) {
					win_players = (struct Player*)realloc(win_players, ++noWin * sizeof(struct Player));
					copyPlayer(&win_players[noWin - 1], &p[i]);
				}
			}
		}
	}

	if (noWin == 0 && noDraw == 0) {
		printf("\nNo one wins !\n");
	}
	else {
		if (noWin != 0) {
			printf("\nWinners: ");
			for (int i = 0; i < noWin; i++) {
				printf("\t%s", win_players[i].name);
			}
		}
		if (noDraw != 0) {
			printf("\nDraw: ");
			for (int i = 0; i < noDraw; i++) {
				printf("\t%s", draw_players[i].name);
			}
		}
	}


	free(win_players);
	free(draw_players);
}

void StartGame() {
	int noPlayer;
	printf("WELCOME TO BLACKJACK GAME\n");
	do {
		printf("Please enter the number of player: ");
		scanf("%d", &noPlayer);
		system("cls");
	} while (noPlayer < 1 || noPlayer>4);
	struct Player* p = (struct Player*)malloc(noPlayer * sizeof(struct Player));
	struct Computer com;

	Shuffle();
	for (int i = 0; i < noPlayer; i++) {
		p[i].noCard = 0;
	}
	com.noCard = 0;

	for (int i = 0; i < noPlayer; i++) {
		printf("Please enter name of player %d: ", i + 1);
		scanf("%s", p[i].name);
	}
	Handling(p, &com, noPlayer);

	Player_turn(p, noPlayer);
	Computer_turn(&com);
	
	printf("\n");
	system("pause");

	system("cls");

	ProcessFinish(p, noPlayer, com);
	
	free(p);
	system("pause>0");
}

void DisplayMenu() {
	system("cls");

	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t=====================|BLACKJACK|====================\n");
	printf("\t\t\t\t|             WELCOME TO BLACKJACK GAME            |\n");
	printf("\t\t\t\t|                1.Play:                           |\n");
	printf("\t\t\t\t|                2.Rules:                          |\n");
	printf("\t\t\t\t|                3.Exit                            |\n");
	printf("\t\t\t\t====================================================\n");
}

void DisplayRules() {
	system("cls");

	printf("* The cards have the same number of points as their values (indepedent of the suit).\n");
	printf("* A (ace) has value 11, on the other hand, K (king), Q (queen) and J (jack) have value 10.\n");
	printf("* Each player (user), as well as the COMPUTER (software), begin with two cards.\n");
	printf("* There is a 'Hit or Stand' option for every additional card.\n");
	printf("* If you hit, you get one more card and it goes on until you stay.\n");
	printf("* The safe range of player is 16 to 21, and that of computer is 15 to 21.\n");
	printf("* The goal is to get the maximum score in the safe range. If your point exceeds 21, you lose\n");
	printf("* At the end, the player(s) with larger point than computer wins, however a tie can also occur.\n");

	system("pause");
}