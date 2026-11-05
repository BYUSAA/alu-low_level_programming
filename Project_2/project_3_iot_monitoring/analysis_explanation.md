# Custom Callback — Rapid Temperature Change Detector

## Purpose
This custom monitoring rule detects sudden changes between consecutive readings from the same temperature device. A reading can be within the normal temperature range and still be suspicious if it changes too quickly.

## Formula
`change = absolute(current_temperature - previous_temperature)`

## Trigger condition
The callback reports a rapid-change alert when:

`change > 5.0 °C`

The first temperature reading establishes the baseline and does not trigger this rule because there is no previous reading to compare.

## Algorithm
1. Read the current temperature from the device's active union member.
2. If a previous temperature exists, calculate the absolute difference.
3. If the difference exceeds 5.0 °C, increment the custom-alert counter and report the previous and current values.
4. Store the current temperature as the previous reading for the next cycle.

## Callback integration
The temperature device is processed through `temperature_monitor`. That callback then dispatches `rapid_temperature_change_detector` through a second function pointer using the same callback signature. This makes the custom monitoring rule a separate callback rather than merely an extra condition inside the standard temperature check.

## Limitations
The simulation uses a simple fixed threshold and simulated readings. Real deployments would need sensor-specific calibration, sampling intervals, and environmental context.
