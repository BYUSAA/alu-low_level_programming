# Project 3 — Dynamic IoT Event Monitoring and Callback Engine

**Student:** Byusa Mukarage Martin De Poles  
**Student ID:** 811201785

## Purpose

A C simulation for registering temperature, pressure, and battery-monitor devices, generating readings, dispatching readings to monitoring callbacks, and reporting alert status.

## Build and run

Run these commands from this directory:

```sh
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o iot_monitor
./iot_monitor
```

## Features

- Dynamic device array with registration and removal by ID.
- Duplicate device ID validation.
- A `union SensorReading` for temperature, pressure, and battery voltage.
- Function-pointer dispatch to `temperature_monitor`, `pressure_monitor`, and `battery_monitor`.
- Simulation of at least 10 readings.
- Alert messages with device, value, unit, expected range, reason, and callback.
- Current alert-status display and monitoring summary.
- Separate rapid-temperature-change callback invoked through a function pointer.
- Sets the device status to `ALERT` when the custom threshold is exceeded.
- Releases the device array at exit.

## Simulated operating ranges

| Device type | Normal range |
|---|---:|
| Temperature | 18.0–30.0 °C |
| Pressure | 950–1050 kPa |
| Battery voltage | 3.3–4.2 V |

These are illustrative coursework thresholds, not industrial safety standards.

## Repeatable demonstration

For each device, its first generated reading is a normal baseline and its second is deliberately outside the normal range. Later readings use `rand()`, seeded with `time(NULL)`. This provides both normal and abnormal examples while retaining random readings.

The custom callback compares consecutive temperature readings and triggers when the absolute difference is greater than 5.0 °C. It sets the device status to `ALERT`, prints the compared values and threshold, and increments a separate custom-alert counter. See [analysis_explanation.md](analysis_explanation.md).

## Test evidence

Run `bash Project_2/tests/run_smoke_tests.sh` from the repository root. It registers three device types, simulates 10 readings, checks callback and custom-alert messages, displays status and summary, and removes a device.
