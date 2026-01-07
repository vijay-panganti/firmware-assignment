#ifndef WMBUS_JSON_H
#define WMBUS_JSON_H

#include <stdint.h>
#include <stddef.h>

/* -------- Meter Data Point -------- */
typedef struct {
    const char *timestamp;
    const char *meter_datetime;
    float total_m3;
    const char *status;
} wmbus_data_point_t;

/* -------- Device Reading -------- */
typedef struct {
    const char *media;
    const char *meter;
    const char *device_id;
    const char *unit;
    wmbus_data_point_t *data;
    uint8_t data_count;
} wmbus_device_t;

/* -------- Values Container -------- */
typedef struct {
    uint8_t device_count;
    wmbus_device_t *readings;
} wmbus_values_t;

/* -------- Root Object -------- */
typedef struct {
    const char *gateway_id;
    const char *date;
    const char *device_type;
    uint16_t interval_minutes;
    uint16_t total_readings;
    wmbus_values_t values;
} wmbus_root_t;

/* -------- API -------- */
int wmbus_serialize_json(
    const wmbus_root_t *input,
    char *output,
    size_t output_size
);

#endif
