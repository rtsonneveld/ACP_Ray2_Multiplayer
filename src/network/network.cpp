#include "network.h"

int networkTest() {
	// Initialize ENet
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	// Write something to test
	FILE* pFile = fopen("test.txt", "a");
	if (pFile != NULL) {
		fprintf(pFile, "Test Output");
		fprintf(pFile, "\n");
		fclose(pFile);
	}
}