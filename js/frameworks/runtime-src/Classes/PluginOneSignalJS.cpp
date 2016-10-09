#include "PluginOneSignalJS.hpp"
#include "PluginOneSignal/PluginOneSignal.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
        JS::RootedObject proto(cx, typeClass->proto.ref());
        JS::RootedObject parent(cx, typeClass->parentProto.ref());
#else
        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
#endif
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));

        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
#else
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
#endif
#elif defined(JS_VERSION)
template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    assert(p);
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_FALSE;
}
#endif
JSClass  *jsb_sdkbox_PluginOneSignal_class;
JSObject *jsb_sdkbox_PluginOneSignal_prototype;

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_getTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginOneSignal::getTags();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_getTags : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_getTags(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginOneSignal::getTags();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification : Error processing arguments");
        sdkbox::PluginOneSignal::enableInAppAlertNotification(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(argv[0]);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::enableInAppAlertNotification(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_postNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_postNotification : Error processing arguments");
        sdkbox::PluginOneSignal::postNotification(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_postNotification : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_postNotification(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::postNotification(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setLogLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_setLogLevel : Error processing arguments");
        sdkbox::PluginOneSignal::setLogLevel(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_setLogLevel : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setLogLevel(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        int arg0;
        int arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::setLogLevel(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_idsAvailable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginOneSignal::idsAvailable();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_idsAvailable : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_idsAvailable(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginOneSignal::idsAvailable();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setEmail(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_setEmail : Error processing arguments");
        sdkbox::PluginOneSignal::setEmail(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_setEmail : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setEmail(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::setEmail(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_promptLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginOneSignal::promptLocation();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_promptLocation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_promptLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginOneSignal::promptLocation();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::PluginOneSignal::init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_init : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::PluginOneSignal::init();
        jsval jsret;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginOneSignal::registerForPushNotifications();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginOneSignal::registerForPushNotifications();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_deleteTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_deleteTag : Error processing arguments");
        sdkbox::PluginOneSignal::deleteTag(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_deleteTag : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_deleteTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::deleteTag(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_setSubscription(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_setSubscription : Error processing arguments");
        sdkbox::PluginOneSignal::setSubscription(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_setSubscription : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_setSubscription(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(argv[0]);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::setSubscription(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginOneSignalJS_PluginOneSignal_sendTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginOneSignalJS_PluginOneSignal_sendTag : Error processing arguments");
        sdkbox::PluginOneSignal::sendTag(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginOneSignalJS_PluginOneSignal_sendTag : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginOneSignalJS_PluginOneSignal_sendTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginOneSignal::sendTag(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginOneSignalJS_PluginOneSignal_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginOneSignal)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;

#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
#else
    jsproxy = jsb_get_js_proxy(obj);
#endif

    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        sdkbox::PluginOneSignal *nobj = static_cast<sdkbox::PluginOneSignal *>(nproxy->ptr);
        if (nobj)
            delete nobj;

        jsb_remove_proxy(nproxy, jsproxy);
    }
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JS::HandleObject global) {
    jsb_sdkbox_PluginOneSignal_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginOneSignal_class->name = "PluginOneSignal";
    jsb_sdkbox_PluginOneSignal_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginOneSignal_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginOneSignal_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginOneSignal_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginOneSignal_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginOneSignal_class->finalize = js_PluginOneSignalJS_PluginOneSignal_finalize;
    jsb_sdkbox_PluginOneSignal_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getTags", js_PluginOneSignalJS_PluginOneSignal_getTags, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableInAppAlertNotification", js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("postNotification", js_PluginOneSignalJS_PluginOneSignal_postNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLogLevel", js_PluginOneSignalJS_PluginOneSignal_setLogLevel, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("idsAvailable", js_PluginOneSignalJS_PluginOneSignal_idsAvailable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmail", js_PluginOneSignalJS_PluginOneSignal_setEmail, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("promptLocation", js_PluginOneSignalJS_PluginOneSignal_promptLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginOneSignalJS_PluginOneSignal_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("registerForPushNotifications", js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("deleteTag", js_PluginOneSignalJS_PluginOneSignal_deleteTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSubscription", js_PluginOneSignalJS_PluginOneSignal_setSubscription, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendTag", js_PluginOneSignalJS_PluginOneSignal_sendTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginOneSignal_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_sdkbox_PluginOneSignal_class,
        dummy_constructor<sdkbox::PluginOneSignal>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "PluginOneSignal", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
    JS::RootedObject proto(cx, jsb_sdkbox_PluginOneSignal_prototype);
    jsb_register_class<sdkbox::PluginOneSignal>(cx, jsb_sdkbox_PluginOneSignal_class, proto, JS::NullPtr());
#else
    TypeTest<sdkbox::PluginOneSignal> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginOneSignal_class;
        p->proto = jsb_sdkbox_PluginOneSignal_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif
}
#else
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginOneSignal_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginOneSignal_class->name = "PluginOneSignal";
    jsb_sdkbox_PluginOneSignal_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginOneSignal_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginOneSignal_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginOneSignal_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginOneSignal_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginOneSignal_class->finalize = js_PluginOneSignalJS_PluginOneSignal_finalize;
    jsb_sdkbox_PluginOneSignal_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getTags", js_PluginOneSignalJS_PluginOneSignal_getTags, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableInAppAlertNotification", js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("postNotification", js_PluginOneSignalJS_PluginOneSignal_postNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLogLevel", js_PluginOneSignalJS_PluginOneSignal_setLogLevel, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("idsAvailable", js_PluginOneSignalJS_PluginOneSignal_idsAvailable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmail", js_PluginOneSignalJS_PluginOneSignal_setEmail, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("promptLocation", js_PluginOneSignalJS_PluginOneSignal_promptLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginOneSignalJS_PluginOneSignal_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("registerForPushNotifications", js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("deleteTag", js_PluginOneSignalJS_PluginOneSignal_deleteTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSubscription", js_PluginOneSignalJS_PluginOneSignal_setSubscription, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendTag", js_PluginOneSignalJS_PluginOneSignal_sendTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginOneSignal_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginOneSignal_class,
        dummy_constructor<sdkbox::PluginOneSignal>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "PluginOneSignal", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginOneSignal> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginOneSignal_class;
        p->proto = jsb_sdkbox_PluginOneSignal_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginOneSignal_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginOneSignal_class->name = "PluginOneSignal";
    jsb_sdkbox_PluginOneSignal_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginOneSignal_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginOneSignal_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginOneSignal_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginOneSignal_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginOneSignal_class->finalize = js_PluginOneSignalJS_PluginOneSignal_finalize;
    jsb_sdkbox_PluginOneSignal_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getTags", js_PluginOneSignalJS_PluginOneSignal_getTags, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableInAppAlertNotification", js_PluginOneSignalJS_PluginOneSignal_enableInAppAlertNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("postNotification", js_PluginOneSignalJS_PluginOneSignal_postNotification, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLogLevel", js_PluginOneSignalJS_PluginOneSignal_setLogLevel, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("idsAvailable", js_PluginOneSignalJS_PluginOneSignal_idsAvailable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmail", js_PluginOneSignalJS_PluginOneSignal_setEmail, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("promptLocation", js_PluginOneSignalJS_PluginOneSignal_promptLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginOneSignalJS_PluginOneSignal_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("registerForPushNotifications", js_PluginOneSignalJS_PluginOneSignal_registerForPushNotifications, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("deleteTag", js_PluginOneSignalJS_PluginOneSignal_deleteTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSubscription", js_PluginOneSignalJS_PluginOneSignal_setSubscription, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendTag", js_PluginOneSignalJS_PluginOneSignal_sendTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginOneSignal_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginOneSignal_class,
        dummy_constructor<sdkbox::PluginOneSignal>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "PluginOneSignal", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginOneSignal> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_PluginOneSignal_class;
        p->proto = jsb_sdkbox_PluginOneSignal_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginOneSignalJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "sdkbox", &ns);

    js_register_PluginOneSignalJS_PluginOneSignal(cx, ns);

    sdkbox::setProjectType("js");
}
#else
void register_all_PluginOneSignalJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginOneSignalJS_PluginOneSignal(cx, obj);

    sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginOneSignalJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginOneSignalJS_PluginOneSignal(cx, obj);

    sdkbox::setProjectType("js");
}
#endif