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

std::string toLower(const std::string);

int main() {
	std::srand(time(0)); // Setting seed for random number genrator
	int b = 0, n = 1; // Initializing ball's position and current row (n)
	int timeout = 300;
	
	std::vector<float> multipliers;	
	std::string command;
	while (command != "start" && command != "settings" && command != "exit") {
		std::system(CLS);
		std::cout << "Welcome to the pocet plinko!\n\n\n";
		std::cout << "Type start to start or settings to open settings\n\n";
		std::cout << "Type exit to exit game\n";
		std::getline(std::cin, command);
		command = toLower(command);
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
				command = toLower(command);
				if (command == "1") {
					std::system(CLS);
					do {
						std::cout << "Enter new value for layers: ";
						std::getline(std::cin, command);
						std::system(CLS);
						try {
							LAYERS = std::stoi(command);
						} catch (const std::invalid_argument& e) {
							LAYERS = 6;
						} catch (const std::out_of_range& e) {
							LAYERS = 6;
						}
						if (LAYERS <= 0) std::cout << "Number of layers must be positive\n";
					} while (LAYERS <= 0);
				} else if (command == "2") {
					std::system(CLS);
					do {
						std::cout << "Enter new value for time per layer(ms): ";
						std::getline(std::cin, command);
						std::system(CLS);
						try {
							timeout = stoi(command);
						} catch (const std::invalid_argument& e) {
							timeout = 300;
						} catch (const std::out_of_range& e) {
							timeout = 300;
						}
						if (timeout <= 0)  std::cout << "Timeout must be possitive\n";
					} while (timeout <= 0);
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
			while (balance <= 0) {
				std::cout << "Enter balance: ";
				std::getline(std::cin, command);
				std::system(CLS);
				try {
					balance = stof(command);
				} catch (const std::invalid_argument& e) {
					std::cout << "Invalid balance\n";
				} catch (const std::out_of_range& e) {
					std::cout << "Balance out of allowed range\n";
				}
				if (balance <= 0) {
					std::cout << "Balance has to be positive\n";
				}
			}
			while (command != "exit" && balance > 0) {
				system(CLS);
				do {
					std::cout << "Your balance: " << balance << '\n';
					std::cout << "Enter bet: ";
					std::getline(std::cin, command);
					std::system(CLS);
					try {
						bet = stof(command);
					} catch (const std::invalid_argument& e) {
						std::cout << "Invalid bet\n";
					} catch (const std::out_of_range& e) {
						std::cout << "Bet out of allowed range\n";
					}
					if (bet <= 0) {
						std::cout << "Bet has to be positive\n";
					}
				} while (bet <= 0);
				balance -= bet;
				b = 0;
				n = 1;
				while (n <= LAYERS + 1) {
					std::system(CLS);

					int start = middle;
					int current = 0;
					
					for (int i = 0; i <= LAYERS; ++i) {
						start = middle - i;
						std::cout << std::string(start - 1, ' ');
						for (int k = 0; k <= i; ++k) {
							if (current == b)
								std::cout << "O ";
							else
								std::cout << "  ";
							current++;
						}
						std::cout << '\n' << std::flush;
						std::cout << std::string(start - 1, ' ');
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
					std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
					if (n == LAYERS + 1) break;
					b += rand() % 2 + n;
					n++;
				}
				std::cout << "You have landed on " << float(multipliers[b - decrement]) << "x!\n";
				std::cout << "You have won " << float(bet * multipliers[b - decrement]) << "!\n";
				balance += bet * multipliers[b - decrement];

				std::cout << "Press enter to continue or exit to exit to main menu\n";
				std::getline(std::cin, command);
				command = toLower(command);
			}
			command = "";
		}
	}
	return 0;
}

std::string toLower(const std::string str) {
	std::string output;
	for (const char& i : str) {
		if (i >= 65 && i <= 90)
			output += (i + 32);
		else
			output += i;
	}
	return output;
}
