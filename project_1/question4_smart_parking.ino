/*
 * Smart Parking System
 *
 * HC-SR04 ultrasonic sensor detects the distance
 * to an object and determines whether the parking
 * space is available or occupied.
 *
 * Distance > 20 cm:
 * Green LED ON
 * Red LED OFF
 * Buzzer OFF
 *
 * Distance <= 20 cm:
 * Green LED OFF
 * Red LED ON
 * Buzzer ON
 */

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int GREEN_LED = 6;
const int RED_LED = 7;
const int BUZZER = 8;

const float THRESHOLD_CM = 20.0;

/**
 * measure_distance - measures distance using HC-SR04
 *
 * Return: distance in centimeters
 */
float measure_distance(void)
{
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = (duration * 0.0343) / 2.0;

    return distance;
}

/**
 * setup - initializes the Arduino
 *
 * Return: void
 */
void setup(void)
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    Serial.begin(9600);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
}

/**
 * loop - continuously checks parking status
 *
 * Return: void
 */
void loop(void)
{
    float distance;

    distance = measure_distance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= THRESHOLD_CM)
    {
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        digitalWrite(BUZZER, HIGH);

        Serial.println("Parking Status: OCCUPIED");
        Serial.println("Red LED: ON");
        Serial.println("Green LED: OFF");
        Serial.println("Buzzer: ON");
    }
    else
    {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER, LOW);

        Serial.println("Parking Status: AVAILABLE");
        Serial.println("Green LED: ON");
        Serial.println("Red LED: OFF");
        Serial.println("Buzzer: OFF");
    }

    Serial.println("----------------------------");

    delay(500);
}

