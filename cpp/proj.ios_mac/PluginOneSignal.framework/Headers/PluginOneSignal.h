/****************************************************************************

 Copyright (c) 2014-2015 SDKBOX Inc

 ****************************************************************************/

#ifndef _PLUGIN_ONESIGNAL_H_
#define _PLUGIN_ONESIGNAL_H_

#include <string>
#include <map>
#include <vector>

namespace sdkbox {

    // log level
    const static int OneSignalLogNone    = 0;
    const static int OneSignalLogFatal   = 1;
    const static int OneSignalLogError   = 2;
    const static int OneSignalLogWarn    = 3;
    const static int OneSignalLogInfo    = 4;
    const static int OneSignalLogDebug   = 5;
    const static int OneSignalLogVerbose = 6;

    class OneSignalListener;
    class PluginOneSignal {
    public:

        /**
         *  initialize the plugin instance.
         */
        static bool init();

        /**
         * Set listener to listen for onesignal events
         */
        static void setListener(OneSignalListener* listener);

        /**
         * Get the listener
         */
        static OneSignalListener* getListener();

        /**
         * Remove the listener, and can't listen to events anymore
         */
        static void removeListener();

        // Only use if you passed FALSE to autoRegister
        static void registerForPushNotifications();

        static void setLogLevel(int logLevel, int visualLogLevel);

        // callback in `onSendTag`
        static void sendTag(const std::string& key, const std::string& value);

        static void setEmail(const std::string& email);

        // callback in `onGetTags`
        static void getTags();

        static void deleteTag(const std::string& key);

        // callback in `onIdsAvailable`
        static void idsAvailable();

        static void enableInAppAlertNotification(bool enable);

        static void setSubscription(bool enable);

        // callback in `onPostNotification`
        static void postNotification(const std::string& jsonString);

        static void promptLocation();
        };

    class OneSignalListener {
    public:
        virtual void onSendTag(bool success, const std::string& key, const std::string& message) {}
        virtual void onGetTags(const std::string& jsonString) {}
        virtual void onIdsAvailable(const std::string& userId, const std::string& pushToken) {}
        virtual void onPostNotification(bool success, const std::string& message) {}
        virtual void onNotification(bool isActive, const std::string& message, const std::string& additionalData) {}
    };
}

#endif
