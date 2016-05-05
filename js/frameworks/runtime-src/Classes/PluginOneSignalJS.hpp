#ifndef __PluginOneSignalJS_h__
#define __PluginOneSignalJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_PluginOneSignal_class;
extern JSObject *jsb_sdkbox_PluginOneSignal_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JS::HandleObject global);
void register_all_PluginOneSignalJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JSObject* global);
void register_all_PluginOneSignalJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginOneSignalJS_PluginOneSignal_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginOneSignalJS_PluginOneSignal_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_getTags(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_getTags(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_postNotification(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_postNotification(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setLogLevel(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setLogLevel(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_idsAvailable(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_idsAvailable(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setEmail(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setEmail(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_promptLocation(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_promptLocation(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_init(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_init(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_deleteTag(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_deleteTag(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setSubscription(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setSubscription(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_sendTag(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_sendTag(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif

