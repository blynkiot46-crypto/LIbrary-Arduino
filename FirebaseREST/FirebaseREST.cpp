// ========================================
// FirebaseREST.cpp
// ========================================

#include "FirebaseREST.h"

// ========================================
// CONSTRUCTOR
// ========================================

FirebaseREST::FirebaseREST(
    String url
) {

    databaseURL = url;
}

// ========================================
// ASYNC PATCH
// ========================================

void FirebaseREST::patchAsync(
    String path,
    JsonDocument &doc
) {

    String json;

    serializeJson(
        doc,
        json
    );

    queue[queueTail].method =
    "PATCH";

    queue[queueTail].path =
    path;

    queue[queueTail].payload =
    json;

    queueTail++;

    if (
        queueTail >=
        FIREBASE_QUEUE_SIZE
    ) {

        queueTail = 0;
    }
}

// ========================================
// LOOP
// ========================================

void FirebaseREST::loop() {

    if (
        queueHead ==
        queueTail
    ) {

        return;
    }

    HTTPClient http;

    String url =

    databaseURL +

    queue[queueHead].path +

    ".json";

    http.begin(url);

    http.addHeader(
        "Content-Type",
        "application/json"
    );

    int httpCode = -1;

    if (
        queue[queueHead]
        .method
        == "PATCH"
    ) {

        httpCode =
        http.PATCH(
            queue[queueHead]
            .payload
        );
    }

    Serial.print(
        "HTTP Code : "
    );

    Serial.println(
        httpCode
    );

    http.end();

    queueHead++;

    if (
        queueHead >=
        FIREBASE_QUEUE_SIZE
    ) {

        queueHead = 0;
    }
}

// ========================================
// GET JSON
// ========================================

bool FirebaseREST::get(
    String path,
    JsonDocument &doc
) {

    HTTPClient http;

    String url =
    databaseURL +
    path +
    ".json";

    http.begin(url);

    int httpCode =
    http.GET();

    if (httpCode > 0) {

        String payload =
        http.getString();

        DeserializationError error =
        deserializeJson(
            doc,
            payload
        );

        http.end();

        return !error;
    }

    http.end();

    return false;
}

// ========================================
// GET STRING
// ========================================

String FirebaseREST::getString(
    String path
) {

    JsonDocument doc;

    if (
        get(path, doc)
    ) {

        return
        doc.as<String>();
    }

    return "";
}

// ========================================
// GET INT
// ========================================

int FirebaseREST::getInt(
    String path
) {

    JsonDocument doc;

    if (
        get(path, doc)
    ) {

        return
        doc.as<int>();
    }

    return 0;
}

// ========================================
// GET FLOAT
// ========================================

float FirebaseREST::getFloat(
    String path
) {

    JsonDocument doc;

    if (
        get(path, doc)
    ) {

        return
        doc.as<float>();
    }

    return 0;
}

// ========================================
// SET STRING
// ========================================

bool FirebaseREST::setString(
    String path,
    String value
) {

    HTTPClient http;

    String url =
    databaseURL +
    path +
    ".json";

    http.begin(url);

    http.addHeader(
        "Content-Type",
        "application/json"
    );

    String json =
    "\"" + value + "\"";

    int httpCode =
    http.PUT(json);

    http.end();

    return (
        httpCode > 0
    );
}

// ========================================
// SET INT
// ========================================

bool FirebaseREST::setInt(
    String path,
    int value
) {

    HTTPClient http;

    String url =
    databaseURL +
    path +
    ".json";

    http.begin(url);

    http.addHeader(
        "Content-Type",
        "application/json"
    );

    int httpCode =
    http.PUT(
        String(value)
    );

    http.end();

    return (
        httpCode > 0
    );
}

// ========================================
// SET FLOAT
// ========================================

bool FirebaseREST::setFloat(
    String path,
    float value
) {

    HTTPClient http;

    String url =
    databaseURL +
    path +
    ".json";

    http.begin(url);

    http.addHeader(
        "Content-Type",
        "application/json"
    );

    int httpCode =
    http.PUT(
        String(value)
    );

    http.end();

    return (
        httpCode > 0
    );
}

// ========================================
// GET OBJECT
// ========================================

int FirebaseREST::getObject(
    String path,
    String keys[],
    String values[],
    int maxItems
) {

    JsonDocument doc;

    if (
        !get(path, doc)
    ) {

        return 0;
    }

    JsonObject obj =
    doc.as<JsonObject>();

    int index = 0;

    for (
        JsonPair kv :
        obj
    ) {

        if (
            index >=
            maxItems
        ) {

            break;
        }

        keys[index] =
        kv.key().c_str();

        values[index] =
        kv.value().as<String>();

        index++;
    }

    return index;
}
