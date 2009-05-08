/*
 * Copyright (C) 2008 The Android Open Source Project
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
#ifndef _SUPPLICANTLISTENER_H__
#define _SUPPLICANTLISTENER_H__

#include <pthread.h>

#include <sysutils/SocketListener.h>

struct wpa_ctrl;
class Supplicant;

class SupplicantListener: public SocketListener {
private:
    struct wpa_ctrl *mMonitor;
    Supplicant      *mSupplicant;
    pthread_t       mThread;

public:
    SupplicantListener(Supplicant *supplicant, struct wpa_ctrl *monitor);
    virtual ~SupplicantListener() {}
    int startListener();
    int stopListener();

    struct wpa_ctrl *getMonitor() { return mMonitor; }
    Supplicant *getSupplicant() { return mSupplicant; }

protected:
    virtual bool onDataAvailable(int socket);

private:
    static void *threadStart(void *obj);
};

#endif