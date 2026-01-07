#include <Arduino.h>
#include "wmbus_json.h"

char json_buffer[1024];

void setup() {
    Serial.begin(115200);
    delay(1000);

    wmbus_data_point_t data_point = {
        "1970-01-01 00:00",
        "1970-01-01 00:00",
        107.752,
        "OK"
    };

    wmbus_device_t device = {
        "water",
        "waterstarm",
        "stromleser_50898527",
        "m3",
        &data_point,
        1
    };

    wmbus_root_t root = {
        "gateway_1234",
        "1970-01-01",
        "stromleser",
        15,
        1,
        {
            1,
            &device
        }
    };

    if (wmbus_serialize_json(&root, json_buffer, sizeof(json_buffer)) == 0) {
        Serial.println("Generated JSON:");
        Serial.println(json_buffer);
    } else {
        Serial.println("JSON serialization failed");
    }
}

void loop() {
    // Nothing required
}
