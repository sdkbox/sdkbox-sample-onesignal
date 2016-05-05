

#ifndef __js__PluginOneSignalJSHelper_H_
#define __js__PluginOneSignalJSHelper_H_

#include "jsapi.h"
#include "jsfriendapi.h"

#if MOZJS_MAJOR_VERSION >= 31
void register_all_PluginOneSignalJS_helper(JSContext* cx, JS::HandleObject global);
#else
void register_all_PluginOneSignalJS_helper(JSContext* cx, JSObject* global);
#endif

#endif /* defined(__PluginOneSignalJSHelper_H_) */
