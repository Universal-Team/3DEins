#include <algorithm> // For std::shuffle.
#include <array> // The array.
#include <fstream> // For std::ofstream.
#include <random> // For std::mt19937.
#include <string> // General string header.
#include <time.h> // To get the seed time.
#include <unistd.h> // For access.

// Include all cardNames here.
std::array<std::string, 62> cardNames = {{
	"0_blue", "0_green", "0_red", "0_yellow",
	"1_blue", "1_green", "1_red", "1_yellow",
	"2_blue", "2_green", "2_red", "2_yellow",
	"3_blue", "3_green", "3_red", "3_yellow",
	"4_blue", "4_green", "4_red", "4_yellow",
	"5_blue", "5_green", "5_red", "5_yellow",
	"6_blue", "6_green", "6_red", "6_yellow",
	"7_blue", "7_green", "7_red", "7_yellow",
	"8_blue", "8_green", "8_red", "8_yellow",
	"9_blue", "9_green", "9_red", "9_yellow",
	"skip_blue", "skip_green", "skip_red", "skip_yellow",
	"reverse_blue", "reverse_green", "reverse_red", "reverse_yellow",
	"draw2_blue", "draw2_green", "draw2_red", "draw2_yellow",
	"wild_blue", "wild_green", "wild_red", "wild_yellow", "wild",
	"wild_draw4_blue", "wild_draw4_green", "wild_draw4_red", "wild_draw4_yellow", "wild_draw4"
}};

std::string header = "--atlas -f rgba8888 -z auto"; // The header for the spritesheet.

std::mt19937 randomGen; // Our random generator.

int main() {
	printf("Generating seed...\n");
	randomGen.seed(time(NULL));
	printf("Shuffle names...\n");
	std::shuffle(cardNames.begin(), cardNames.end(), randomGen);

	printf("Checking if exist...\n");
	if (access("gfx", F_OK) != 0) mkdir("gfx"); // If not exist, create!
	printf("Open file...\n");
	std::ofstream file("gfx/cards.t3s");
	if (file.is_open()) {
		// Push over the header & 1 new lines.
		printf("Writing Header stuff...\n");
		file << header << std::endl;
		file << std::endl;

		printf("Writing CardNames...\n");
		// Write our card names there.
		for (int i = 0; i < (int)cardNames.size(); i++) {
			file << "cards/" << cardNames[i] << ".png" << std::endl;
		}
		printf("Closing file...\n");
		file.close();
	} else {
		printf("Not able to open file!"); // We are not able to open the file.
	}

	printf("Done!\n");
	printf("Now run 'make' to generate the SpriteSheet.\n");
	return 0;
}