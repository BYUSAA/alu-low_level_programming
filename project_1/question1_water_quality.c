#include <stdio.h>
#include <math.h>

/**
 * calculate_index - calculates the water-quality index
 * @temperature: temperature reading in degrees Celsius
 * @turbidity: turbidity reading in NTU
 *
 * Return: calculated water-quality index
 */
double calculate_index(double temperature, double turbidity)
{
	double temperature_deviation;
	double turbidity_penalty;

	temperature_deviation = fabs(temperature - 25.0);
	turbidity_penalty = turbidity / 2.0;

	return (100.0 - (temperature_deviation + turbidity_penalty));
}

/**
 * classify_water - classifies the water based on its index
 * @index: calculated water-quality index
 *
 * Return: water-quality status
 */
const char *classify_water(double index)
{
	if (index >= 80.0)
		return ("Good");
	else if (index >= 60.0)
		return ("Warning");
	else
		return ("Critical");
}

/**
 * main - entry point of the program
 *
 * Return: 0 on success
 */
int main(void)
{
	double temperature;
	double turbidity;
	double index;
	const char *status;

	printf("===== WATER QUALITY MONITORING SYSTEM =====\n\n");

	printf("Enter temperature (C): ");
	scanf("%lf", &temperature);

	printf("Enter turbidity (NTU): ");
	scanf("%lf", &turbidity);

	index = calculate_index(temperature, turbidity);
	status = classify_water(index);

	printf("\n===== MONITORING REPORT =====\n");
	printf("Temperature: %.2f C\n", temperature);
	printf("Turbidity: %.2f NTU\n", turbidity);
	printf("Water Quality Index: %.2f\n", index);
	printf("Water Quality Status: %s\n", status);

	return (0);
}
