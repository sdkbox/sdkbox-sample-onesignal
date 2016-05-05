#include "PluginOneSignalLua.hpp"
#include "PluginOneSignal/PluginOneSignal.h"
#include "tolua_fix.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginOneSignalLua_PluginOneSignal_getTags(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_getTags'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::getTags();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:getTags",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_getTags'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_enableInAppAlertNotification(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:enableInAppAlertNotification");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_enableInAppAlertNotification'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::enableInAppAlertNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:enableInAppAlertNotification",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_enableInAppAlertNotification'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_postNotification(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:postNotification");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_postNotification'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::postNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:postNotification",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_postNotification'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_setLogLevel(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "sdkbox.PluginOneSignal:setLogLevel");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "sdkbox.PluginOneSignal:setLogLevel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_setLogLevel'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::setLogLevel(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:setLogLevel",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_setLogLevel'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_idsAvailable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_idsAvailable'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::idsAvailable();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:idsAvailable",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_idsAvailable'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_setEmail(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:setEmail");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_setEmail'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::setEmail(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:setEmail",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_setEmail'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_promptLocation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_promptLocation'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::promptLocation();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:promptLocation",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_promptLocation'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_init'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginOneSignal::init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_init'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_registerForPushNotifications(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_registerForPushNotifications'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::registerForPushNotifications();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:registerForPushNotifications",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_registerForPushNotifications'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_deleteTag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:deleteTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_deleteTag'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::deleteTag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:deleteTag",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_deleteTag'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_setSubscription(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:setSubscription");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_setSubscription'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::setSubscription(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:setSubscription",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_setSubscription'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginOneSignalLua_PluginOneSignal_sendTag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginOneSignal",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginOneSignal:sendTag");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "sdkbox.PluginOneSignal:sendTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginOneSignalLua_PluginOneSignal_sendTag'", nullptr);
            return 0;
        }
        sdkbox::PluginOneSignal::sendTag(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginOneSignal:sendTag",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginOneSignalLua_PluginOneSignal_sendTag'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginOneSignalLua_PluginOneSignal_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginOneSignal)");
    return 0;
}

int lua_register_PluginOneSignalLua_PluginOneSignal(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.PluginOneSignal");
    tolua_cclass(tolua_S,"PluginOneSignal","sdkbox.PluginOneSignal","",nullptr);

    tolua_beginmodule(tolua_S,"PluginOneSignal");
        tolua_function(tolua_S,"getTags", lua_PluginOneSignalLua_PluginOneSignal_getTags);
        tolua_function(tolua_S,"enableInAppAlertNotification", lua_PluginOneSignalLua_PluginOneSignal_enableInAppAlertNotification);
        tolua_function(tolua_S,"postNotification", lua_PluginOneSignalLua_PluginOneSignal_postNotification);
        tolua_function(tolua_S,"setLogLevel", lua_PluginOneSignalLua_PluginOneSignal_setLogLevel);
        tolua_function(tolua_S,"idsAvailable", lua_PluginOneSignalLua_PluginOneSignal_idsAvailable);
        tolua_function(tolua_S,"setEmail", lua_PluginOneSignalLua_PluginOneSignal_setEmail);
        tolua_function(tolua_S,"promptLocation", lua_PluginOneSignalLua_PluginOneSignal_promptLocation);
        tolua_function(tolua_S,"init", lua_PluginOneSignalLua_PluginOneSignal_init);
        tolua_function(tolua_S,"registerForPushNotifications", lua_PluginOneSignalLua_PluginOneSignal_registerForPushNotifications);
        tolua_function(tolua_S,"deleteTag", lua_PluginOneSignalLua_PluginOneSignal_deleteTag);
        tolua_function(tolua_S,"setSubscription", lua_PluginOneSignalLua_PluginOneSignal_setSubscription);
        tolua_function(tolua_S,"sendTag", lua_PluginOneSignalLua_PluginOneSignal_sendTag);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::PluginOneSignal).name();
    g_luaType[typeName] = "sdkbox.PluginOneSignal";
    g_typeCast["PluginOneSignal"] = "sdkbox.PluginOneSignal";
    return 1;
}
TOLUA_API int register_all_PluginOneSignalLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginOneSignalLua_PluginOneSignal(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

