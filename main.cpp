#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <vector>

#ifdef _WIN32
const char CLS[4] = "cls";
#endif
#ifdef __linux__
const char CLS[6] = "clear";
#endif

int LAYERS = 6;

using namespace std::chrono_literals;

void beginning();

int main() {
	std::srand(time(0)); // Setting seed for random number genrator
	int b = 0, n = 1; // Initializing ball's position and current row (n)
	int timeout = 300;
	
	std::vector<float> multipliers;	
	beginning();
	//TODO make it not case sensitive
	std::string command;
	while (command != "start" && command != "settings" && command != "exit") {
		beginning();
		std::getline(std::cin, command);

		if (command == "exit") {
			std::cout << "Thanks for playing!\n";
			return 0;
		} else if (command == "settings") {
			while (command != "exit") {
				std::system(CLS);
				std::cout << "Layers: " << LAYERS << '\n';
				std::cout << "Time per layer(ms): " << timeout << "\n\n\n";
				std::cout << "Enter 1 for layers or 2 for time per layer\n\n";
				std::cout << "Enter exit to exit to main menu\n";
				std::getline(std::cin, command);
				if (command == "1") {
					std::system(CLS);
					std::cout << "Enter new value for layers: ";
					std::getline(std::cin, command);
					LAYERS = std::stoi(command);
				} else if (command == "2") {
					std::system(CLS);
					std::cout << "Enter new value for time per layer(ms): ";
					std::getline(std::cin, command);
					timeout = stoi(command);
				}
			}
			command = "";
		} else if (command == "start") {
			float balance, bet;
			int decrement = (LAYERS * (LAYERS + 1)) / 2;
			int width = 2 * LAYERS + 1; // Calculating width of whole triangle
			int middle = width / 2 + 1; // Calculating middle of this triangle

			multipliers = std::vector<float>(LAYERS + 1);
			if (LAYERS % 2 == 0) {
				int radius = (LAYERS + 1) / 2;
				for (int f = 0; f < radius; ++f) {
					multipliers[f] = 0.5 + (radius - f) * 0.3;
					multipliers[LAYERS - f] = 0.5 + (radius - f) * 0.3;
				}
				multipliers[radius] = 0.5;
			} else {
				int radius = (LAYERS + 1) / 2 - 1;
				for (int f = 0; f < radius; ++f) {
					multipliers[f] = 0.5 + (radius - f) * 0.3;
					multipliers[LAYERS - f] = 0.5 + (radius - f) * 0.3;
				}
				multipliers[radius] = 0.5;
				multipliers[radius + 1] = 0.5;
			}
			//for (int h = 0; h < LAYERS + 1; ++h) {
			//	std::cout << multipliers[h] << ' ';
			//}
			//std::cout << '\n';
			//return 0;
			std::cout << "Enter balance: ";
			std::getline(std::cin, command);
			balance = stof(command);
			while (command != "exit" && balance > 0) {
				//TODO make bets real
				system(CLS);
				std::cout << "Your balanme: " << balance << '\n';
				std::cout << "Enter bet: ";
				std::getline(std::cin, command);
				bet = stof(command);
				balance -= bet;
				b = 0;
				n = 1;
				while (n <= LAYERS + 1) {
					std::system(CLS);

					int start = middle;
					int current = 0;
					//std::cout << "h0\n";
					
					for (int i = 0; i <= LAYERS; ++i) {
				//		try {
						start = middle - i;
						std::cout << std::string(start - 1, ' ');
						for (int k = 0; k <= i; ++k) {
							if (current == b)
								std::cout << "O ";
							else
								std::cout << "  ";
							current++;
						}//}} catch (const std::length_error& e) {
						//	std::cerr << "Error: " << e.what() << '\n';
						//}

						//std::cout << "h1\n";
						std::cout << '\n' << std::flush;
       
       
						//try {
						std::cout << std::string(start - 1, ' ');
			//			} catch (const std::length_error& e) {
			//				std::cerr << "Error length: " << e.what() << '\n';
			//			}
						if (i == LAYERS) {
							for (int j = 0; j <= i; ++j) {
								std::cout << "U ";
							}
						} else {
							for (int j = 0; j <= i; ++j) {
								std::cout << "I ";
							}
						}
						std::cout << '\n' << std::flush;
					}
					std::cout << '\n';
					//std::cout << "h2\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
					//std::cout << "h3\n";
					if (n == LAYERS + 1) break;
					//std::cout << "h4\n";
					b += rand() % 2 + n;
					n++;
				}
				//std::cout << b << '\n';
				//std::cout << b - decrement << '\n';
				std::cout << "You have landed on " << float(multipliers[b - decrement]) << "x!\n";
				std::cout << "You have won " << float(bet * multipliers[b - decrement]) << "!\n";
				balance += bet * multipliers[b - decrement];

				std::cout << "Press enter to continue or exit to exit to main menu\n";
				std::getline(std::cin, command);
			}
			command = "";
		}
	}
	return 0;
}

void beginning() {
	std::system(CLS);
	std::cout << "Welcome to the pocet plinko!\n\n\n";
	std::cout << "Type start to start or setting to open settings\n\n";
	std::cout << "Type exit to exit game\n";
}
