#ifndef __PluginOneSignalJS_h__
#define __PluginOneSignalJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JS::HandleObject global);
void register_all_PluginOneSignalJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginOneSignalJS_PluginOneSignal(JSContext *cx, JSObject* global);
void register_all_PluginOneSignalJS(JSContext* cx, JSObject* obj);
#endif
#endif

