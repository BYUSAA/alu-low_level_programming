#include <stdio.h>

/**
 * display_parking_status - displays the status of each parking slot
 * @slots: array containing parking slot states
 * @size: number of parking slots
 *
 * Return: number of available slots
 */
int display_parking_status(int slots[], int size)
{
	int i;
	int available = 0;

	printf("\n===== PARKING STATUS =====\n");

	for (i = 0; i < size; i++)
	{
		if (slots[i] == 0)
		{
			printf("Slot %d: Available\n", i + 1);
			available++;
		}
		else
		{
			printf("Slot %d: Occupied\n", i + 1);
		}
	}

	return (available);
}

/**
 * main - entry point of the smart parking system
 *
 * Return: 0 on success
 */
int main(void)
{
	int slots[5] = {1, 0, 1, 0, 0};
	int available;

	printf("===== SMART PARKING SYSTEM =====\n");

	available = display_parking_status(slots, 5);

	printf("\n===== PARKING SUMMARY =====\n");
	printf("Total slots: 5\n");
	printf("Occupied slots: %d\n", 5 - available);
	printf("Available slots: %d\n", available);

	if (available == 0)
	{
		printf("Parking Status: FULL\n");
	}
	else
	{
		printf("Parking Status: SPACE AVAILABLE\n");
	}

	return (0);
}
