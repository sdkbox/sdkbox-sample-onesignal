#include "PluginOneSignalJSHelper.h"
#include "PluginOneSignal/PluginOneSignal.h"
#include "SDKBoxJSHelper.h"

extern JSObject* jsb_sdkbox_PluginOneSignal_prototype;
static JSContext* s_cx = nullptr;

#if (COCOS2D_VERSION < 0x00030000)
#define Ref CCObject
#define Director CCDirector
#define getInstance sharedDirector
#define schedule scheduleSelector
#endif

class OneSignal_CallbackJS: public cocos2d::Ref {
public:
    OneSignal_CallbackJS();
    void schedule();
    void notityJs(float dt);

    std::string _name;

    jsval _paramVal[3];
    int _paramLen;
};

class OneSignalListenerJS : public sdkbox::OneSignalListener, public sdkbox::JSListenerBase
{
public:
    OneSignalListenerJS():sdkbox::JSListenerBase() {
    }

    void onSendTag(bool success, const std::string& key, const std::string& message) {
        OneSignal_CallbackJS* cb = new OneSignal_CallbackJS();
        cb->_name = "onSendTag";
        cb->_paramVal[0] = BOOLEAN_TO_JSVAL(success);
        cb->_paramVal[1] = std_string_to_jsval(s_cx, key);
        cb->_paramVal[2] = std_string_to_jsval(s_cx, message);
        cb->_paramLen = 3;
        cb->schedule();
    }
    void onGetTags(const std::string& jsonString) {
        OneSignal_CallbackJS* cb = new OneSignal_CallbackJS();
        cb->_name = "onGetTags";
        cb->_paramVal[0] = std_string_to_jsval(s_cx, jsonString);
        cb->_paramLen = 1;
        cb->schedule();
    }
    void onIdsAvailable(const std::string& userId, const std::string& pushToken) {
        OneSignal_CallbackJS* cb = new OneSignal_CallbackJS();
        cb->_name = "onIdsAvailable";
        cb->_paramVal[0] = std_string_to_jsval(s_cx, userId);
        cb->_paramVal[1] = std_string_to_jsval(s_cx, pushToken);
        cb->_paramLen = 2;
        cb->schedule();
    }
    void onPostNotification(bool success, const std::string& message) {
        OneSignal_CallbackJS* cb = new OneSignal_CallbackJS();
        cb->_name = "onPostNotification";
        cb->_paramVal[0] = BOOLEAN_TO_JSVAL(success);
        cb->_paramVal[1] = std_string_to_jsval(s_cx, message);
        cb->_paramLen = 2;
        cb->schedule();
    }
    void onNotification(bool isActive, const std::string& message, const std::string& additionalData) {
        OneSignal_CallbackJS* cb = new OneSignal_CallbackJS();
        cb->_name = "onNotification";
        cb->_paramVal[0] = BOOLEAN_TO_JSVAL(isActive);
        cb->_paramVal[1] = std_string_to_jsval(s_cx, message);
        cb->_paramVal[2] = std_string_to_jsval(s_cx, additionalData);
        cb->_paramLen = 3;
        cb->schedule();
    }

    void invokeJS(const char* func, jsval* pVals, int valueSize) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = func;
        JS::RootedObject obj(cx, getJSDelegate());
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(valueSize, pVals), &retval);
            }
#else
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, valueSize, pVals, &retval);
            }
#endif
        }
    }

};


OneSignal_CallbackJS::OneSignal_CallbackJS():
_paramLen(0) {
}

void OneSignal_CallbackJS::schedule() {
    retain();
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(OneSignal_CallbackJS::notityJs), this, 0.1, 0, 0.0f, false);
    autorelease();
}

void OneSignal_CallbackJS::notityJs(float dt) {
    sdkbox::OneSignalListener* lis = sdkbox::PluginOneSignal::getListener();
    OneSignalListenerJS* l = dynamic_cast<OneSignalListenerJS*>(lis);
    if (l) {
        l->invokeJS(_name.c_str(), _paramVal, _paramLen);
    }
    release();
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginOneSignalJS_PluginOneSignal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#else
bool js_PluginOneSignalJS_PluginOneSignal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }

        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_setIAPListener : Error processing arguments");
        OneSignalListenerJS* wrapper = new OneSignalListenerJS();
        wrapper->setJSDelegate(args.get(0));
        sdkbox::PluginOneSignal::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_setIAPListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void onesignal_set_constants(JSContext* cx, const JS::RootedObject& obj, const std::string& name, const std::map<std::string, int>& params)
#else
void onesignal_set_constants(JSContext* cx, JSObject* obj, const std::string& name, const std::map<std::string, int>& params)
#endif
{
    jsval val = sdkbox::std_map_string_int_to_jsval(cx, params);

    JS::RootedValue rv(cx);
    rv = val;
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    JS_SetProperty(cx, obj, name.c_str(), rv);
#else
    JS_SetProperty(cx, obj, name.c_str(), rv.address());
#endif
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void onesignal_register_constants(JSContext* cx, const JS::RootedObject& obj)
#else
void onesignal_register_constants(JSContext* cx, JSObject* obj)
#endif
{
    std::map<std::string, int> enums;
    enums.clear();
        enums.insert(std::make_pair("None", sdkbox::OneSignalLogNone));
        enums.insert(std::make_pair("Fatal", sdkbox::OneSignalLogFatal));
        enums.insert(std::make_pair("Error", sdkbox::OneSignalLogError));
        enums.insert(std::make_pair("Warn", sdkbox::OneSignalLogWarn));
        enums.insert(std::make_pair("Info", sdkbox::OneSignalLogInfo));
        enums.insert(std::make_pair("Debug", sdkbox::OneSignalLogDebug));
        enums.insert(std::make_pair("Verbose", sdkbox::OneSignalLogVerbose));
    onesignal_set_constants(cx, obj, "LogLevel", enums);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginOneSignalJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginOneSignal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginOneSignalJS_PluginOneSignal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    onesignal_register_constants(cx, pluginObj);
}
#else
void register_all_PluginOneSignalJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginOneSignal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginOneSignalJS_PluginOneSignal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    onesignal_register_constants(cx, pluginObj);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginOneSignalJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginOneSignal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginOneSignalJS_PluginOneSignal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    onesignal_register_constants(cx, pluginObj);
}
#endif
