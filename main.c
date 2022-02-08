#include <stdio.h>
#include <stdlib.h>
#include "services/menu_service.h"
#include "models/options_enum.h"
#include "helper/utility.h"

void handleMenuInput(char input) {
	clearTerminal();
	switch (input) {
		case PLAY:
			play();
			break;
		case VIEW:
			showHighestScore();
			break;
		case RESET:
			resetScore();
			break;
		case HELP:
			showHelp();
			break;
		case QUIT:
			quit();
			break;
	}
}

int main() {
	clearTerminal();
	greetUser();
	printCurrentTime();
	while (TRUE) {
		displayMenu();
		handleMenuInput(getMenuInput());
	}
	return 0;
}
