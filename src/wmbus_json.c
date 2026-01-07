#include "wmbus_json.h"
#include <stdio.h>

#define CHECK_WRITE(ret, max, used) \
    if ((ret) < 0 || (size_t)(ret) >= ((max) - (used))) return -1; \
    (used) += (ret);

int wmbus_serialize_json(
    const wmbus_root_t *input,
    char *output,
    size_t output_size
) {
    size_t used = 0;
    int ret;

    if (!input || !output || output_size == 0)
        return -1;

    ret = snprintf(output + used, output_size - used,
        "[{"
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%d,"
        "\"total_readings\":%d,"
        "\"values\":{"
        "\"device_count\":%d,"
        "\"readings\":[",
        input->gateway_id,
        input->date,
        input->device_type,
        input->interval_minutes,
        input->total_readings,
        input->values.device_count
    );
    CHECK_WRITE(ret, output_size, used);

    for (uint8_t i = 0; i < input->values.device_count; i++) {
        wmbus_device_t *dev = &input->values.readings[i];

        ret = snprintf(output + used, output_size - used,
            "{"
            "\"media\":\"%s\","
            "\"meter\":\"%s\","
            "\"deviceId\":\"%s\","
            "\"unit\":\"%s\","
            "\"data\":[",
            dev->media,
            dev->meter,
            dev->device_id,
            dev->unit
        );
        CHECK_WRITE(ret, output_size, used);

        for (uint8_t j = 0; j < dev->data_count; j++) {
            wmbus_data_point_t *dp = &dev->data[j];

            ret = snprintf(output + used, output_size - used,
                "{"
                "\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\""
                "}%s",
                dp->timestamp,
                dp->meter_datetime,
                dp->total_m3,
                dp->status,
                (j + 1 < dev->data_count) ? "," : ""
            );
            CHECK_WRITE(ret, output_size, used);
        }

        ret = snprintf(output + used, output_size - used,
            "]}"
            "%s",
            (i + 1 < input->values.device_count) ? "," : ""
        );
        CHECK_WRITE(ret, output_size, used);
    }

    ret = snprintf(output + used, output_size - used,
        "]}}]"
    );
    CHECK_WRITE(ret, output_size, used);

    return 0;
}
