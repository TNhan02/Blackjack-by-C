#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

void Shuffle();//Shuffling the deck 
void Display_Rank(int rank); //Display the rank's card face
void Display_Suit(int suit); //Display the suit's card face
void DisplayMenu(); //Display the Menu of the game
void DisplayRules(); //Display rules
void StartGame(); //Initialize the game
void Handling(struct Player* p, int n, struct Computer com); //Delivering first 2 cards to player and computer
void Player_turn(struct Player* p, int n);//Each player's turn and decision of hitting or staying
void Computer_turn(struct Computer* com); //Computer's ways of playing this game

void printHand(struct card* hand, int noCard); //Print hand of a player or computer
void printCard(struct card c); //Print card
void copyHand(struct card* hand1, struct card* hand2); //Copy player's hand or computer's hand to win_player or draw_player
void copyPlayer(struct Player* p1, struct Player* p2); //Copy player's name or computer to win_player or draw_player
void ProcessFinish(struct Player* p, int n, struct Computer com); //Finding who wins computer and who draws with computer


int Card_Value(int rank); //Display the value of each card
int calPoint(struct card* hand, int noCard); //Calculate the point of player's hand or computer's hand