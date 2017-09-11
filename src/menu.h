typedef struct menu Menu;

struct menu {
	WINDOW window;
	int visible;
	int validatedOption;
};

Menu createMenu(maxX, maxY);
void displayMenu(Menu* m);
void toggleMenu(Menu* m);
void deleteMenu(Menu m);
