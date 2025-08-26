#include "main.hpp"

EventHandler event;
AppState app = {};

int main(int argc, char *argv[])
{
	init(argc, argv);
	main_loop();
	return 0;
}
