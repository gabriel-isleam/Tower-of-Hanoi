/* ISLEAM Gabriel-Mihai 315 CB */
#include "header.h"

int main(int argc, char *argv[])
{
	char *input_file = strdup(argv[1]);										// preluarea numelor fisierelor primite ca parametru
	char *output_file = strdup(argv[2]);

	FILE *input, *output;

	if ((input = fopen(input_file, "rt")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", input_file);
		return -1;
	}

	if ((output = fopen(output_file, "wt")) == NULL)
	{
		fprintf(stderr, "Can't open %s\n", output_file);
		return -1;
	}

	TLista Lista_sisteme = NULL;
	Read(&Lista_sisteme, input, output);

	free(input_file);
	free(output_file);
	fclose(input);
	fclose(output);
	return 0;
}