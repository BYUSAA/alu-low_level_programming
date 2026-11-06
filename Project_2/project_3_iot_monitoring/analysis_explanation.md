# Custom Callback — Rapid Temperature Change Detector

## Purpose

This callback detects a sudden change between consecutive readings from the same temperature sensor. A temperature can be within its normal operating range and still be unusual if it changes too quickly.

## Formula

`change = |current temperature - previous temperature|`

## Trigger condition

The callback triggers when `change > 5.0 °C`. The first reading establishes a baseline and is not compared with an earlier reading.

## Algorithm

1. Read the current temperature from the temperature member of the device's union.
2. Check whether a previous temperature reading exists.
3. Calculate the absolute difference between the current and previous values.
4. If the difference exceeds 5.0 °C, increment the custom-alert counter, print both values and the threshold, and set the device status to `ALERT`.
5. Save the current reading for the next comparison.

## Function-pointer integration

The temperature reading is processed by `temperature_monitor`, which dispatches `rapid_temperature_change_detector` through a `DeviceCallback` function pointer. The custom rule is a separate callback, not merely another condition inside the standard temperature-range check.

## Counting and status

Normal/abnormal totals describe whether a reading falls outside the configured operating range. Rapid-change alerts are counted separately because they measure a different condition. A device is marked `ALERT` when either the standard range check or custom check detects a problem. A later normal reading can return its status to `NORMAL`.

## Limitations

This coursework simulation uses a fixed threshold and generated readings. A real monitoring system would need sensor calibration, sampling intervals, noise filtering, and environmental context.
