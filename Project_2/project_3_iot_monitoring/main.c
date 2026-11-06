/*
 * Dynamic IoT Event Monitoring and Callback Engine
 * Compile: gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o iot_monitor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define STUDENT_ID "811201785"
#define NAME_SIZE 40
#define TYPE_TEMPERATURE 1
#define TYPE_PRESSURE 2
#define TYPE_BATTERY 3
#define TYPE_COUNT 3
#define TEMP_MIN 18.0
#define TEMP_MAX 30.0
#define PRESSURE_MIN 950
#define PRESSURE_MAX 1050
#define VOLTAGE_MIN 3.3
#define VOLTAGE_MAX 4.2
#define RAPID_CHANGE_LIMIT 5.0

typedef union SensorReading
{
    float temperature;
    int pressure;
    float voltage;
} SensorReading;

typedef struct Device
{
    int id;
    char name[NAME_SIZE];
    int type;
    SensorReading reading;
    int status; /* 0 = normal, 1 = alert */
    float previous_temperature;
    int has_previous_temperature;
    unsigned int readings_generated;
} Device;

typedef struct DeviceList
{
    Device *items;
    size_t count;
    size_t capacity;
} DeviceList;

typedef struct MonitorStats
{
    unsigned long readings_processed;
    unsigned long normal_readings;
    unsigned long abnormal_readings;
    unsigned long alerts_by_type[TYPE_COUNT];
    unsigned long rapid_change_alerts;
} MonitorStats;

typedef void (*DeviceCallback)(Device *, MonitorStats *);

static void process_device(Device *device, DeviceCallback callback,
                           MonitorStats *stats);

static int read_line(const char *prompt, char *buffer, size_t size)
{
    size_t length;
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;
    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        return 1;
    }
    ch = getchar();
    if (ch == '\n' || ch == EOF)
        return 1;
    while (ch != '\n' && ch != EOF)
        ch = getchar();
    printf("Input too long.\n");
    return 0;
}

static int read_int(const char *prompt, int *value)
{
    char line[128];
    char *end;
    long parsed;

    while (1)
    {
        if (!read_line(prompt, line, sizeof(line)))
            continue;
        errno = 0;
        parsed = strtol(line, &end, 10);
        if (line[0] == '\0' || *end != '\0' || errno == ERANGE ||
            parsed < 0 || parsed > 2147483647L)
        {
            printf("Enter a valid non-negative integer.\n");
            continue;
        }
        *value = (int)parsed;
        return 1;
    }
}

static int reserve_devices(DeviceList *list, size_t needed)
{
    Device *temporary;
    size_t new_capacity;

    if (needed <= list->capacity)
        return 1;
    new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
    while (new_capacity < needed)
        new_capacity *= 2;
    temporary = realloc(list->items, new_capacity * sizeof(Device));
    if (temporary == NULL)
        return 0;
    list->items = temporary;
    list->capacity = new_capacity;
    return 1;
}

static int device_id_exists(DeviceList *list, int id)
{
    Device *ptr;

    if (list->count == 0)
        return 0;
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
        if (ptr->id == id)
            return 1;
    return 0;
}

static const char *type_name(int type)
{
    if (type == TYPE_TEMPERATURE)
        return "Temperature";
    if (type == TYPE_PRESSURE)
        return "Pressure";
    if (type == TYPE_BATTERY)
        return "Battery";
    return "Unknown";
}

static void register_device(DeviceList *list)
{
    Device device;
    int type;

    read_int("Device ID: ", &device.id);
    if (device_id_exists(list, device.id))
    {
        printf("Duplicate device ID rejected.\n");
        return;
    }
    if (!read_line("Device name: ", device.name, sizeof(device.name)) ||
        device.name[0] == '\0')
    {
        printf("A device name is required.\n");
        return;
    }
    printf("Device type:\n1. Temperature sensor\n2. Pressure sensor\n3. Battery voltage monitor\n");
    read_int("Type: ", &type);
    if (type < TYPE_TEMPERATURE || type > TYPE_BATTERY)
    {
        printf("Invalid device type.\n");
        return;
    }
    device.type = type;
    device.status = 0;
    device.has_previous_temperature = 0;
    device.previous_temperature = 0.0f;
    device.readings_generated = 0;
    device.reading.temperature = 0.0f;

    if (!reserve_devices(list, list->count + 1))
    {
        printf("Memory allocation failed; device not registered.\n");
        return;
    }
    list->items[list->count++] = device;
    printf("Registered %s device. Total devices: %lu\n",
           type_name(type), (unsigned long)list->count);
}

static void display_devices(DeviceList *list)
{
    Device *ptr;

    if (list->count == 0)
    {
        printf("No devices registered.\n");
        return;
    }
    printf("\n%-6s %-20s %-14s %-18s %s\n",
           "ID", "NAME", "TYPE", "LATEST READING", "STATUS");
    printf("--------------------------------------------------------------------------\n");
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        printf("%-6d %-20.20s %-14s ", ptr->id, ptr->name, type_name(ptr->type));
        if (ptr->type == TYPE_TEMPERATURE)
            printf("%-18.2f C ", ptr->reading.temperature);
        else if (ptr->type == TYPE_PRESSURE)
            printf("%-18d kPa ", ptr->reading.pressure);
        else
            printf("%-18.2f V ", ptr->reading.voltage);
        printf("%s\n", ptr->status ? "ALERT" : "NORMAL");
    }
}

static void remove_device(DeviceList *list)
{
    int id;
    size_t index;
    Device *temporary;

    if (list->count == 0)
    {
        printf("No devices to remove.\n");
        return;
    }
    read_int("Device ID to remove: ", &id);
    for (index = 0; index < list->count; index++)
        if (list->items[index].id == id)
            break;
    if (index == list->count)
    {
        printf("Device not found.\n");
        return;
    }
    for (; index + 1 < list->count; index++)
        list->items[index] = list->items[index + 1];
    list->count--;
    if (list->count == 0)
    {
        free(list->items);
        list->items = NULL;
        list->capacity = 0;
    }
    else
    {
        temporary = realloc(list->items, list->count * sizeof(Device));
        if (temporary != NULL)
        {
            list->items = temporary;
            list->capacity = list->count;
        }
    }
    printf("Device removed. Remaining devices: %lu\n",
           (unsigned long)list->count);
}

static void record_result(Device *device, MonitorStats *stats,
                          int abnormal, const char *callback_name,
                          const char *reason, const char *range,
                          double value, const char *unit)
{
    stats->readings_processed++;
    if (abnormal)
    {
        device->status = 1;
        stats->abnormal_readings++;
        stats->alerts_by_type[device->type - 1]++;
        printf("ALERT: Device %d (%s), %.2f %s; expected %s; reason: %s; callback: %s\n",
               device->id, device->name, value, unit, range, reason, callback_name);
    }
    else
    {
        device->status = 0;
        stats->normal_readings++;
        printf("NORMAL: Device %d (%s), %.2f %s; callback: %s\n",
               device->id, device->name, value, unit, callback_name);
    }
}

static void rapid_temperature_change_detector(Device *device,
                                               MonitorStats *stats)
{
    float current = device->reading.temperature;
    float difference;

    if (device->has_previous_temperature)
    {
        difference = current - device->previous_temperature;
        if (difference < 0.0f)
            difference = -difference;
        if (difference > RAPID_CHANGE_LIMIT)
        {
            device->status = 1;
            stats->rapid_change_alerts++;
            printf("CUSTOM CALLBACK ALERT: Device %d (%s) changed from %.2f C "
                   "to %.2f C; absolute change %.2f C exceeded %.2f C. "
                   "Device status set to ALERT. "
                   "Callback: rapid_temperature_change_detector\n",
                   device->id, device->name, device->previous_temperature,
                   current, difference, RAPID_CHANGE_LIMIT);
        }
    }
    device->previous_temperature = current;
    device->has_previous_temperature = 1;
}

static void temperature_monitor(Device *device, MonitorStats *stats)
{
    float value = device->reading.temperature;
    int abnormal = (value < TEMP_MIN || value > TEMP_MAX);
    DeviceCallback custom_callback = rapid_temperature_change_detector;

    record_result(device, stats, abnormal, "temperature_monitor",
                  "temperature outside normal range", "18.0 to 30.0 C",
                  value, "C");

    /* Dispatch the original custom rule through a function pointer. */
    custom_callback(device, stats);
}

static void pressure_monitor(Device *device, MonitorStats *stats)
{
    int value = device->reading.pressure;
    int abnormal = (value < PRESSURE_MIN || value > PRESSURE_MAX);

    record_result(device, stats, abnormal, "pressure_monitor",
                  "pressure outside normal range", "950 to 1050 kPa",
                  (double)value, "kPa");
}

static void battery_monitor(Device *device, MonitorStats *stats)
{
    float value = device->reading.voltage;
    int abnormal = (value < VOLTAGE_MIN || value > VOLTAGE_MAX);

    record_result(device, stats, abnormal, "battery_monitor",
                  "battery voltage outside normal range", "3.3 to 4.2 V",
                  value, "V");
}

static void process_device(Device *device, DeviceCallback callback,
                           MonitorStats *stats)
{
    callback(device, stats);
}

static void generate_readings(DeviceList *list, MonitorStats *stats)
{
    Device *ptr;
    int i;

    if (list->count == 0)
    {
        printf("Register devices before generating readings.\n");
        return;
    }
    printf("\nGenerating one reading for every registered device:\n");
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        DeviceCallback callback = NULL;

        if (ptr->type == TYPE_TEMPERATURE)
        {
            if (ptr->readings_generated == 0)
                ptr->reading.temperature = 22.0f;
            else if (ptr->readings_generated == 1)
                ptr->reading.temperature = 36.0f;
            else
            {
                i = rand() % 5;
                ptr->reading.temperature = (i == 0) ?
                    (float)(34 + rand() % 8) :
                    (float)(18 + rand() % 13);
            }
            callback = temperature_monitor;
        }
        else if (ptr->type == TYPE_PRESSURE)
        {
            if (ptr->readings_generated == 0)
                ptr->reading.pressure = 1000;
            else if (ptr->readings_generated == 1)
                ptr->reading.pressure = 1080;
            else
            {
                i = rand() % 5;
                ptr->reading.pressure = (i == 0) ?
                    (rand() % 2 ? 1080 + rand() % 30 : 900 + rand() % 40) :
                    950 + rand() % 101;
            }
            callback = pressure_monitor;
        }
        else if (ptr->type == TYPE_BATTERY)
        {
            if (ptr->readings_generated == 0)
                ptr->reading.voltage = 3.8f;
            else if (ptr->readings_generated == 1)
                ptr->reading.voltage = 2.8f;
            else
            {
                i = rand() % 5;
                ptr->reading.voltage = (i == 0) ?
                    (float)(2.7 + (rand() % 15) / 10.0) :
                    (float)(3.3 + (rand() % 10) / 10.0);
            }
            callback = battery_monitor;
        }
        if (callback != NULL)
        {
            process_device(ptr, callback, stats);
            ptr->readings_generated++;
        }
    }
}

static void simulate_ten_readings(DeviceList *list, MonitorStats *stats)
{
    int reading_number;
    Device *device;
    DeviceCallback callback;
    int type;

    if (list->count == 0)
    {
        printf("Register devices before simulation.\n");
        return;
    }
    printf("\nSimulating 10 readings across registered devices.\n");
    for (reading_number = 0; reading_number < 10; reading_number++)
    {
        device = &list->items[(size_t)reading_number % list->count];
        callback = NULL;
        type = device->type;
        if (type == TYPE_TEMPERATURE)
        {
            int n = rand() % 7;
            if (device->readings_generated == 0)
                device->reading.temperature = 22.0f;
            else if (device->readings_generated == 1)
                device->reading.temperature = 36.0f;
            else
                device->reading.temperature = (n == 0) ?
                    (float)(36 + rand() % 5) : (float)(20 + rand() % 9);
            callback = temperature_monitor;
        }
        else if (type == TYPE_PRESSURE)
        {
            int n = rand() % 7;
            if (device->readings_generated == 0)
                device->reading.pressure = 1000;
            else if (device->readings_generated == 1)
                device->reading.pressure = 1080;
            else
                device->reading.pressure = (n == 0) ?
                    1080 + rand() % 30 : 970 + rand() % 61;
            callback = pressure_monitor;
        }
        else if (type == TYPE_BATTERY)
        {
            int n = rand() % 7;
            if (device->readings_generated == 0)
                device->reading.voltage = 3.8f;
            else if (device->readings_generated == 1)
                device->reading.voltage = 2.8f;
            else
                device->reading.voltage = (n == 0) ?
                    (float)(2.8 + (rand() % 5) / 10.0) :
                    (float)(3.5 + (rand() % 6) / 10.0);
            callback = battery_monitor;
        }
        printf("Reading %d: ", reading_number + 1);
        if (callback != NULL)
        {
            process_device(device, callback, stats);
            device->readings_generated++;
        }
    }
}

static void display_alert_status(DeviceList *list)
{
    Device *ptr;
    int alerts = 0;

    printf("\nCURRENT DEVICE ALERTS\n");
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        if (ptr->status)
        {
            printf("Device %d (%s) is currently in ALERT status.\n",
                   ptr->id, ptr->name);
            alerts++;
        }
    }
    if (alerts == 0)
        printf("No devices currently have alert status.\n");
}

static void monitoring_summary(DeviceList *list, MonitorStats *stats)
{
    printf("\n========== IOT MONITORING SUMMARY ==========\n");
    printf("Registered devices: %lu\n", (unsigned long)list->count);
    printf("Readings processed: %lu\n", stats->readings_processed);
    printf("Normal readings: %lu\n", stats->normal_readings);
    printf("Abnormal readings: %lu\n", stats->abnormal_readings);
    printf("Temperature alerts: %lu\n", stats->alerts_by_type[0]);
    printf("Pressure alerts: %lu\n", stats->alerts_by_type[1]);
    printf("Battery alerts: %lu\n", stats->alerts_by_type[2]);
    printf("Rapid temperature change alerts: %lu\n",
           stats->rapid_change_alerts);
    printf("============================================\n");
}

int main(void)
{
    DeviceList list;
    MonitorStats stats;
    int choice;
    char line[64];
    char *end;
    long selected;

    list.items = NULL;
    list.count = 0;
    list.capacity = 0;
    memset(&stats, 0, sizeof(stats));
    srand((unsigned int)time(NULL));

    printf("============================================================\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic IoT Event Monitoring and Callback Engine\n");
    printf("Custom Callback: Rapid Temperature Change Detector\n");
    printf("============================================================\n");
    printf("Operating thresholds: Temperature 18-30 C; Pressure 950-1050 kPa; ");
    printf("Battery 3.3-4.2 V.\n");

    while (1)
    {
        printf("\nIOT MONITOR MENU\n");
        printf("1. Register a device\n");
        printf("2. Display all devices\n");
        printf("3. Remove a device\n");
        printf("4. Generate one reading per device\n");
        printf("5. Simulate at least 10 readings\n");
        printf("6. Display detected alerts\n");
        printf("7. Generate monitoring summary\n");
        printf("8. Exit\n");
        printf("Choose an option: ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;
        errno = 0;
        selected = strtol(line, &end, 10);
        if (end == line || (*end != '\n' && *end != '\0') ||
            errno == ERANGE || selected < 1 || selected > 8)
        {
            printf("Enter a whole menu number from 1 to 8.\n");
            continue;
        }
        choice = (int)selected;
        if (choice == 1)
            register_device(&list);
        else if (choice == 2)
            display_devices(&list);
        else if (choice == 3)
            remove_device(&list);
        else if (choice == 4)
            generate_readings(&list, &stats);
        else if (choice == 5)
            simulate_ten_readings(&list, &stats);
        else if (choice == 6)
            display_alert_status(&list);
        else if (choice == 7)
            monitoring_summary(&list, &stats);
        else if (choice == 8)
            break;
        else
            printf("Choose a number from 1 to 8.\n");
    }

    free(list.items);
    list.items = NULL;
    list.count = 0;
    list.capacity = 0;
    printf("Device memory released. Goodbye.\n");
    return EXIT_SUCCESS;
}