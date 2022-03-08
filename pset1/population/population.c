#include <cs50.h>
#include <stdio.h>

int main(void)
{

	// Rules
	printf("Determine how long it takes for a population to reach a particular size.\n\n");


	// TODO: Prompt for start size
	int StartSize;

	do {
		StartSize = get_int("Start size (choose a number above 9) :");
	}
	while (StartSize < 9);
	

	// TODO: Prompt for end size
	int EndSize;

	do {
		EndSize = get_int("End size ?:");
	}
	while (EndSize < StartSize);



// TODO: Calculate number of years until we reach threshold
	int count = 0;
	int newpop = StartSize;

	while (newpop < EndSize) {
		newpop = newpop + (newpop / 3) - (newpop / 4);
		++count;	
	}

	// TODO: Print number of years
	printf("Years: %i", count);
	
}