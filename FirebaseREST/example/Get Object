// Struct In Firebase
//"Jadwal": {
//    "Jadwal 1": "06:00-06:20",
//    "Jadwal 2": "12:00-12:30"
//  }

#include <WiFi.h>
#include "FirebaseREST.h"

// =====================
// WIFI
// =====================

const char* ssid =
"WiFi";

const char* password =
"12345678";

// =====================
// FIREBASE
// =====================

FirebaseREST firebase(
    "https://project-default-rtdb.firebaseio.com"
);

// =====================
// ARRAY OBJECT
// =====================

String jadwalKeys[10];
String jadwalValues[10];

int jadwalCount = 0;

// =====================
// SETUP
// =====================

void setup() {

    Serial.begin(115200);

    WiFi.begin(
        ssid,
        password
    );

    while (
        WiFi.status()
        != WL_CONNECTED
    ) {

        delay(500);

        Serial.print(".");
    }

    Serial.println();
    Serial.println(
        "WiFi Connected"
    );

    // =====================
    // AMBIL OBJECT
    // =====================

    jadwalCount =
    firebase.getObject(
        "/Jadwal",
        jadwalKeys,
        jadwalValues,
        10
    );

    // =====================
    // TAMPILKAN
    // =====================

    for (
        int i = 0;
        i < jadwalCount;
        i++
    ) {

        Serial.print(
            jadwalKeys[i]
        );

        Serial.print(
            " : "
        );

        Serial.println(
            jadwalValues[i]
        );
    }
}

// =====================
// LOOP
// =====================

void loop() {

    firebase.loop();
}
