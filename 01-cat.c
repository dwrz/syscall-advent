#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// cat takes N file names as command-line arguments, concatenates their
// contents, and writes the result to its standard output.

static char buf[4096];

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; ++i) {
		// Skip the first argument (program name).
		if (i == 0) continue;

		// Open the file.
		int fd = open(argv[i], O_RDONLY);
		if  (fd == 0) {
			perror("failed to open");
			exit(1);
		}

		// Read the file into the buffer, then print it to stdout.
		ssize_t count;
		while ((count = read(fd, &buf, sizeof(buf))) != 0) {
			if (count < 1) {
				perror("failed to read");
				exit(1);
			}
			// To prevent printing contents from a read that
			// didn't fill the buffer, terminate the string.
			if ((size_t) count < sizeof(buf)) {
				buf[count] = '\0';
			}

			printf("%s", buf);
		};

		// Close the file descriptor.
		if (close(fd) != 0) {
			perror("failed to close");
		}
	}
}
