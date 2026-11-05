# Project 3 — Dynamic IoT Event Monitoring and Callback Engine

## Description
A C simulation of temperature, pressure, and battery-monitor devices. Devices are dynamically registered and removed, generate readings, and dispatch to type-specific monitoring callbacks.

## Compile and run (Ubuntu / WSL)
```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o iot_monitor
./iot_monitor
```

Replace the student ID placeholder in `main.c`.

## Features
- Dynamic device array with registration and removal.
- Duplicate device ID validation.
- Temperature, pressure, and battery readings stored in a union.
- Callback dispatch to three device-specific monitoring functions.
- Generate one reading per registered device or simulate 10 readings.
- Current alert status and monitoring summary.
- Separate custom rapid-temperature-change callback dispatched through a function pointer.
- Pointer traversal and memory cleanup.

## Documented normal ranges
- Temperature: 18–30 °C.
- Pressure: 950–1050 kPa.
- Battery voltage: 3.3–4.2 V.

These are illustrative thresholds for this simulation, not industrial safety standards.

## Simulation
The random number generator is seeded with `time(NULL)`. The simulation deliberately includes occasional out-of-range readings so that alert handling can be demonstrated. Because readings are random, exact output varies between runs.