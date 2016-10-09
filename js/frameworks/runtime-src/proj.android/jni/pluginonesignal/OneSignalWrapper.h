/****************************************************************************

 Copyright (c) 2014-2015 SDKBOX Inc

 ****************************************************************************/

#ifndef _PLUGIN_ONESIGNAL_WRAPPER_H_
#define _PLUGIN_ONESIGNAL_WRAPPER_H_

#include "PluginOneSignal.h"
#include "json98.h"

#define TAG        "OneSignal"
#define VERSION    "2.6.1"

namespace sdkbox {

class OneSignalWrapper {

public:
    // OneSignalWrapper();
    static OneSignalWrapper* getInstance();

    virtual bool init() = 0;
    virtual void setListener(OneSignalListener* listener) = 0;
    virtual OneSignalListener* getListener() = 0;
    virtual void removeListener() = 0;

    //
    virtual void registerForPushNotifications() = 0;
    virtual void setLogLevel(int logLevel, int visualLogLevel) = 0;
    virtual void sendTag(const std::string& key, const std::string& value) = 0;

    virtual void setEmail(const std::string& email) = 0;
    virtual void getTags() = 0;
    virtual void deleteTag(const std::string& key) = 0;
    virtual void idsAvailable() = 0;
    virtual void enableInAppAlertNotification(bool enable) = 0;
    virtual void setSubscription(bool enable) = 0;
    virtual void postNotification(const std::string& jsonString) = 0;
    virtual void promptLocation() = 0;

//    virtual void sendTags(const std::map<std::string, std::string>& keyValuePair) = 0;
//    virtual void sendTagsWithJsonString(const std::string& jsonString) = 0;
//    virtual void deleteTags(const std::vector<std::string>& keys) = 0;
//    virtual void deleteTagsWithJsonString(const std::string& jsonString) = 0;
//    virtual void postNotification(const std::map<std::string, std::string>& jsonData) = 0;

    // event callback
    void onNotification(bool isActive, const std::string& message, const std::string& additionalData);
    void onSendTag(bool success, const std::string& k, const std::string& v);
    void onGetTags(const std::string& jsonString);
    void onIdsAvailable(const std::string& userId, const std::string& pushToken);
    void onPostNotification(bool success, const std::string& message);
};

class OneSignalWrapperDisabled : public OneSignalWrapper {
public:
    bool init() { return false; }
    void setListener(OneSignalListener* listener) {}
    OneSignalListener* getListener() { return NULL; }
    void removeListener() {}

    //
    void registerForPushNotifications() {}
    void setLogLevel(int logLevel, int visualLogLevel) {}
    void sendTag(const std::string& key, const std::string& value) {}
    void setEmail(const std::string& email) {}
    void getTags() {}
    void deleteTag(const std::string& key) {}
    void idsAvailable() {}
    void enableInAppAlertNotification(bool enable) {}
    void setSubscription(bool enable) {}

    void postNotification(const std::string& jsonString) {}
    void promptLocation() {}

//    void sendTags(const std::map<std::string, std::string>& keyValuePair) {}
//    void sendTagsWithJsonString(const std::string& jsonString) {}
//    void deleteTags(const std::vector<std::string>& keys) {}
//    void deleteTagsWithJsonString(const std::string& jsonString) {}
//    void postNotification(const std::map<std::string, std::string>& jsonData) {}
};

class OneSignalWrapperEnabled : public OneSignalWrapper {
public:
    OneSignalWrapperEnabled();
    bool init();
    void setListener(OneSignalListener* listener);
    OneSignalListener* getListener();
    void removeListener();

    //
    void registerForPushNotifications();
    void setLogLevel(int logLevel, int visualLogLevel);
    void sendTag(const std::string& key, const std::string& value);

    void setEmail(const std::string& email);
    void getTags();
    void deleteTag(const std::string& key);
    void idsAvailable();
    void enableInAppAlertNotification(bool enable);
    void setSubscription(bool enable);
    void postNotification(const std::string& jsonString);
    void promptLocation();

//    void postNotification(const std::map<std::string, std::string>& jsonData);
//    void deleteTags(const std::vector<std::string>& keys);
//    void deleteTagsWithJsonString(const std::string& jsonString);
//    void sendTags(const std::map<std::string, std::string>& keyValuePair);
//    void sendTagsWithJsonString(const std::string& jsonString);
protected:
    bool nativeInit(const Json& config);
    std::string nativeSDKVersion();
    void __trackInit(const Json &json);

    OneSignalListener* _listener;
};

}

#endif
