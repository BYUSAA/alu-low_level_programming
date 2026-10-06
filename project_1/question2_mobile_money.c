#include <stdio.h>

/**
 * display_menu - displays the mobile money menu
 */
void display_menu(void)
{
	printf("\n===== MOBILE MONEY SYSTEM =====\n");
	printf("1. Deposit\n");
	printf("2. Withdraw\n");
	printf("3. Check Balance\n");
	printf("4. Transaction Summary\n");
	printf("5. Exit\n");
	printf("Enter your choice: ");
}

/**
 * deposit - processes a deposit
 * @balance: pointer to the current balance
 * @deposits: pointer to the deposit counter
 *
 * Return: 1 if successful, 0 otherwise
 */
int deposit(double *balance, int *deposits)
{
	double amount;

	printf("Enter deposit amount (RWF): ");

	if (scanf("%lf", &amount) != 1)
	{
		printf("Invalid amount. Deposit cancelled.\n");

		while (getchar() != '\n')
			;

		return (0);
	}

	if (amount <= 0)
	{
		printf("Deposit failed: amount must be greater than 0.\n");
		return (0);
	}

	*balance += amount;
	(*deposits)++;

	printf("Deposit successful: %.0f RWF\n", amount);
	printf("New balance: %.0f RWF\n", *balance);

	return (1);
}

/**
 * withdraw - processes a withdrawal
 * @balance: pointer to the current balance
 * @withdrawals: pointer to the withdrawal counter
 *
 * Return: 1 if successful, 0 otherwise
 */
int withdraw(double *balance, int *withdrawals)
{
	double amount;

	printf("Enter withdrawal amount (RWF): ");

	if (scanf("%lf", &amount) != 1)
	{
		printf("Invalid amount. Withdrawal cancelled.\n");

		while (getchar() != '\n')
			;

		return (0);
	}

	if (amount <= 0)
	{
		printf("Withdrawal failed: amount must be greater than 0.\n");
		return (0);
	}

	if (amount > *balance)
	{
		printf("Withdrawal failed: insufficient balance.\n");
		printf("Available balance: %.0f RWF\n", *balance);
		return (0);
	}

	*balance -= amount;
	(*withdrawals)++;

	printf("Withdrawal successful: %.0f RWF\n", amount);
	printf("Remaining balance: %.0f RWF\n", *balance);

	return (1);
}

/**
 * display_report - displays balance and transaction summary
 * @balance: current balance
 * @deposits: number of successful deposits
 * @withdrawals: number of successful withdrawals
 */
void display_report(double balance, int deposits, int withdrawals)
{
	printf("\n===== BALANCE =====\n");
	printf("Current balance: %.0f RWF\n", balance);

	printf("\n===== TRANSACTION SUMMARY =====\n");
	printf("Successful deposits: %d\n", deposits);
	printf("Successful withdrawals: %d\n", withdrawals);
	printf("Current balance: %.0f RWF\n", balance);
}

/**
 * main - mobile money transaction processing system
 *
 * Return: 0 on success
 */
int main(void)
{
	double balance = 0.0;
	int choice;
	int deposits = 0;
	int withdrawals = 0;

	while (1)
	{
		display_menu();

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
			deposit(&balance, &deposits);
			break;

		case 2:
			withdraw(&balance, &withdrawals);
			break;

		case 3:
			printf("\n===== BALANCE =====\n");
			printf("Current balance: %.0f RWF\n", balance);
			break;

		case 4:
			display_report(balance, deposits, withdrawals);
			break;

		case 5:
			printf("\nThank you for using the Mobile Money System.\n");
			printf("System terminated.\n");
			return (0);

		default:
			printf("Invalid choice. Please select between 1 and 5.\n");
		}
	}
}