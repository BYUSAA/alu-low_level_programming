#include <stdio.h>

/**
 * main - mobile money transaction processing system
 *
 * Return: 0 on success
 */
int main(void)
{
	double balance = 0.0;
	double amount;
	int choice;
	int deposits = 0;
	int withdrawals = 0;

	while (1)
	{
		printf("\n===== MOBILE MONEY SYSTEM =====\n");
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Check Balance\n");
		printf("4. Transaction Summary\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number from 1 to 5.\n");

			while (getchar() != '\n')
				;

			continue;
		}

		switch (choice)
		{
		case 1:
			printf("Enter deposit amount (RWF): ");

			if (scanf("%lf", &amount) != 1)
			{
				printf("Invalid amount. Deposit cancelled.\n");

				while (getchar() != '\n')
					;

				continue;
			}

			if (amount <= 0)
			{
				printf("Deposit failed: amount must be greater than 0.\n");
				continue;
			}

			balance += amount;
			deposits++;

			printf("Deposit successful: %.0f RWF\n", amount);
			printf("New balance: %.0f RWF\n", balance);
			break;

		case 2:
			printf("Enter withdrawal amount (RWF): ");

			if (scanf("%lf", &amount) != 1)
			{
				printf("Invalid amount. Withdrawal cancelled.\n");

				while (getchar() != '\n')
					;

				continue;
			}

			if (amount <= 0)
			{
				printf("Withdrawal failed: amount must be greater than 0.\n");
				continue;
			}

			if (amount > balance)
			{
				printf("Withdrawal failed: insufficient balance.\n");
				printf("Available balance: %.0f RWF\n", balance);
				continue;
			}

			balance -= amount;
			withdrawals++;

			printf("Withdrawal successful: %.0f RWF\n", amount);
			printf("Remaining balance: %.0f RWF\n", balance);
			break;

		case 3:
			printf("\n===== BALANCE =====\n");
			printf("Current balance: %.0f RWF\n", balance);
			break;

		case 4:
			printf("\n===== TRANSACTION SUMMARY =====\n");
			printf("Successful deposits: %d\n", deposits);
			printf("Successful withdrawals: %d\n", withdrawals);
			printf("Current balance: %.0f RWF\n", balance);
			break;

		case 5:
			printf("\nThank you for using the Mobile Money System.\n");
			printf("System terminated.\n");
			break;

		default:
			printf("Invalid choice. Please select between 1 and 5.\n");
			continue;
		}

		if (choice == 5)
			break;
	}

	return (0);
}
