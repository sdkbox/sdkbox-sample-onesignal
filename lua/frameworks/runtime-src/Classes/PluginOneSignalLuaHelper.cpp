
#include "PluginOneSignalLuaHelper.h"
#include "PluginOneSignal/PluginOneSignal.h"
#include "SDKBoxLuaHelper.h"

class OneSignalListenerLua : public sdkbox::OneSignalListener {
public:
    OneSignalListenerLua(): mLuaHandler(0) {
    }

    ~OneSignalListenerLua() {
        resetHandler();
    }

    void setHandler(int luaHandler) {
        if (mLuaHandler == luaHandler) {
            return;
        }
        resetHandler();
        mLuaHandler = luaHandler;
    }

    void resetHandler() {
        if (0 == mLuaHandler) {
            return;
        }

        LUAENGINE->removeScriptHandler(mLuaHandler);
        mLuaHandler = 0;
    }

    void onSendTag(bool success, const std::string& key, const std::string& message) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onSendTag")));
        dict.insert(std::make_pair("success", LuaValue::booleanValue(success)));
        dict.insert(std::make_pair("key", LuaValue::stringValue(key)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onGetTags(const std::string& jsonString) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onGetTags")));
        dict.insert(std::make_pair("jsonString", LuaValue::stringValue(jsonString)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onIdsAvailable(const std::string& userId, const std::string& pushToken) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onIdsAvailable")));
        dict.insert(std::make_pair("userId", LuaValue::stringValue(userId)));
        dict.insert(std::make_pair("pushToken", LuaValue::stringValue(pushToken)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onPostNotification(bool success, const std::string& message) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onPostNotification")));
        dict.insert(std::make_pair("success", LuaValue::booleanValue(success)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onNotification(bool isActive, const std::string& message, const std::string& additionalData) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onNotification")));
        dict.insert(std::make_pair("isActive", LuaValue::booleanValue(isActive)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));
        dict.insert(std::make_pair("additionalData", LuaValue::stringValue(additionalData)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

private:
    int mLuaHandler;
};

int lua_PluginOneSignalLua_PluginOneSignal_setListener(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        OneSignalListenerLua* lis = static_cast<OneSignalListenerLua*> (sdkbox::PluginOneSignal::getListener());
        if (NULL == lis) {
            lis = new OneSignalListenerLua();
        }
        lis->setHandler(handler);
        sdkbox::PluginOneSignal::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_setListener'.",&tolua_err);
#endif
    return 0;
}

static int lua_createTable(lua_State* L, const std::map<std::string, int>& map) {
    lua_newtable(L);

    std::map<std::string, int>::const_iterator it = map.begin();
    while (it != map.end()) {
        lua_pushstring(L, it->first.c_str());
        lua_pushinteger(L, it->second);
        lua_settable(L, -3);
        it++;
    }

    return 1;
}

static int lua_setTable(lua_State* L, int table, const std::string& name, const std::map<std::string, int>& map) {
    if (table < 0) {
        table = lua_gettop(L) + table + 1;
    }
    lua_pushstring(L, name.c_str());
    lua_createTable(L, map);
    lua_rawset(L, table);

    return 0;
}

int lua_PluginOneSignalLua_constants(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginOneSignal");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1)) {
        std::map<std::string, int> enums;
        enums.clear();
        enums.insert(std::make_pair("None",     sdkbox::OneSignalLogNone));
        enums.insert(std::make_pair("Fatal",    sdkbox::OneSignalLogFatal));
        enums.insert(std::make_pair("Error",    sdkbox::OneSignalLogError));
        enums.insert(std::make_pair("Warn",     sdkbox::OneSignalLogWarn));
        enums.insert(std::make_pair("Info",     sdkbox::OneSignalLogInfo));
        enums.insert(std::make_pair("Debug",    sdkbox::OneSignalLogDebug));
        enums.insert(std::make_pair("Verbose",  sdkbox::OneSignalLogVerbose));
        lua_setTable(L, -1, "LogLevel", enums);
    }
    lua_pop(L, 1);

    return 1;
}

int extern_PluginOneSignal(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginOneSignal");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L,"setListener", lua_PluginOneSignalLua_PluginOneSignal_setListener);
    }
     lua_pop(L, 1);

    lua_PluginOneSignalLua_constants(L);

    return 1;
}

TOLUA_API int register_all_PluginOneSignalLua_helper(lua_State* L) {
    tolua_module(L,"sdkbox",0);
    tolua_beginmodule(L,"sdkbox");

    extern_PluginOneSignal(L);

    tolua_endmodule(L);
    return 1;
}


