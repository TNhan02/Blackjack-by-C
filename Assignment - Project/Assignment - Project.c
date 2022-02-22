// Assignment - Project
#include"Header.h"

int main() {
	srand(time(NULL));
	
	while (true) {
		DisplayMenu();

		char option;
		printf("Enter option: ");
		scanf("%c", &option);

		switch (option) {
		case'1':
			StartGame();
			break;
		case'2':
			DisplayRules();
			break;
		case'3':
			exit(0);
		}
	}
}