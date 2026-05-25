// ========================================
// FirebaseREST.h
// ========================================

#ifndef FIREBASEREST_H
#define FIREBASEREST_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define FIREBASE_QUEUE_SIZE 10
#define FIREBASE_MAX_OBJECT_ITEMS 20

class FirebaseREST {

    private:

        String databaseURL;

        struct Request {

            String method;
            String path;
            String payload;
        };

        Request queue[
            FIREBASE_QUEUE_SIZE
        ];

        int queueHead = 0;
        int queueTail = 0;

    public:

        FirebaseREST(
            String url
        );

        // =====================
        // ASYNC PATCH
        // =====================

        void patchAsync(
            String path,
            JsonDocument &doc
        );

        // =====================
        // LOOP
        // =====================

        void loop();

        // =====================
        // GET JSON
        // =====================

        bool get(
            String path,
            JsonDocument &doc
        );

        // =====================
        // GET STRING
        // =====================

        String getString(
            String path
        );

        // =====================
        // GET INT
        // =====================

        int getInt(
            String path
        );

        // =====================
        // GET FLOAT
        // =====================

        float getFloat(
            String path
        );

        // =====================
        // SET STRING
        // =====================

        bool setString(
            String path,
            String value
        );

        // =====================
        // SET INT
        // =====================

        bool setInt(
            String path,
            int value
        );

        // =====================
        // SET FLOAT
        // =====================

        bool setFloat(
            String path,
            float value
        );

        // =====================
        // GET OBJECT
        // =====================

        int getObject(
            String path,
            String keys[],
            String values[],
            int maxItems
        );
};

#endif
