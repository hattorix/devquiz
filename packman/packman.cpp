#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "packman/game.h"
#include "packman/searcher/breadth_first.h"

using namespace std;

int main(int argc, char** argv)
{
	try {
		packman::game game;
		if (argc == 2) {
			ifstream ifs(argv[1]);
			game.load(ifs);
		} else {
			game.load(cin);
		}
		game.start();
	} catch (exception& e) {
		cout << e.what() << endl;
	}
}
