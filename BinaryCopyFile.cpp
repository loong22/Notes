#include <fstream>
#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("The program %s requires two parameters.\n./example.exe sourceFile(Path) destinationFile(Path)\n", argv[0]);
		return 1;
	}

	std::ifstream sourceFile;
	std::ofstream destinationFile;
	
	sourceFile.open(argv[1], std::ios::binary);
	destinationFile.open(argv[2], std::ios::binary);
	
	if (sourceFile.is_open() && destinationFile.is_open()) {
		while (!sourceFile.eof()) {
			char temp = sourceFile.get();
			destinationFile.put(temp);
		}
		printf("File : %s is copied to : %s \n", argv[1], argv[2]);
	}
	else {
		printf("File : %s or %s not exist.\n", argv[1], argv[2]);
		return 1;
	}
	
	return 0;
}

