/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AAUDIO_AAUDIO_SERVICE_MESSAGE_H
#define AAUDIO_AAUDIO_SERVICE_MESSAGE_H

#include <stdint.h>

#include <aaudio/AAudioDefinitions.h>

namespace aaudio {

// TODO move this to an "include" folder for the service.

// Used to send information about the HAL to the client.
struct AAudioMessageTimestamp {
    int64_t position;     // number of frames transferred so far
    int64_t deviceOffset; // add to client position to get device position
    int64_t timestamp;    // time when that position was reached
};

typedef enum aaudio_service_event_e : uint32_t {
    AAUDIO_SERVICE_EVENT_STARTED,
    AAUDIO_SERVICE_EVENT_PAUSED,
    AAUDIO_SERVICE_EVENT_FLUSHED,
    AAUDIO_SERVICE_EVENT_CLOSED,
    AAUDIO_SERVICE_EVENT_DISCONNECTED,
    AAUDIO_SERVICE_EVENT_VOLUME
} aaudio_service_event_t;

struct AAudioMessageEvent {
    aaudio_service_event_t event;
    double                 dataDouble;
    int64_t                dataLong;
};

typedef struct AAudioServiceMessage_s {
    enum class code : uint32_t {
        NOTHING,
        TIMESTAMP,
        EVENT,
    };

    code what;
    union {
        AAudioMessageTimestamp timestamp; // what == TIMESTAMP
        AAudioMessageEvent event;         // what == EVENT
    };
} AAudioServiceMessage;

} /* namespace aaudio */

#endif //AAUDIO_AAUDIO_SERVICE_MESSAGE_H
