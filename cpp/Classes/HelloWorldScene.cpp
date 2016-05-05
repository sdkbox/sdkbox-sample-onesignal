
#include "HelloWorldScene.h"
#include "PluginOneSignal/PluginOneSignal.h"

#define PICOJSON_USE_LOCALE 0
#include "picojson.h"

USING_NS_CC;

static std::string USER_ID =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"33ad9d96-df00-42a2-b5ab-73417f777d42";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
"4db7cb0f-daca-49d6-b3dd-a96774de9f72";
#else
"";
#endif

class CustomListener : public sdkbox::OneSignalListener {
public:

    void onNotification(bool isActive, const std::string& message, const std::string& additionalData) {
        CCLOG("%s isActive=%s, message=%s, additionalData=%s", __FUNCTION__, isActive ? "yes" : "no", message.c_str(), additionalData.c_str());
    }
    void onSendTag(bool success, const std::string& k, const std::string& message) {
        CCLOG("%s: success=%d, key=%s, message=%s", __FUNCTION__, success, k.c_str(), message.c_str());
    }
    void onGetTags(const std::string& jsonString) {
        CCLOG("%s json=%s", __FUNCTION__, jsonString.c_str());
    }
    void onIdsAvailable(const std::string& userId, const std::string& pushToken) {
        CCLOG("%s: userId='%s', pushToken='%s'", __FUNCTION__, userId.c_str(), pushToken.c_str());
        USER_ID = userId;
    }
    void onPostNotification(bool success, const std::string& message) {
        CCLOG("%s: success=%s, message=%s", __FUNCTION__, success ? "yes" : "no", message.c_str());
    }

};


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    sdkbox::PluginOneSignal::setListener(new CustomListener());
    sdkbox::PluginOneSignal::init();

    sdkbox::PluginOneSignal::setSubscription(true);
    sdkbox::PluginOneSignal::setEmail("test@example.com");
    sdkbox::PluginOneSignal::sendTag("key", "value");
    sdkbox::PluginOneSignal::sendTag("key1", "value1");
    sdkbox::PluginOneSignal::getTags();
    //    sdkbox::PluginOneSignal::deleteTag("key");
    sdkbox::PluginOneSignal::idsAvailable();
    sdkbox::PluginOneSignal::enableInAppAlertNotification(true);

    auto postNotificationTest = []() {

        // content
        picojson::object contents;
        contents["en"] = picojson::value("Test Message");

        // ids
        picojson::array ids;
        ids.push_back(picojson::value(USER_ID));
        ids.push_back(picojson::value("4db7cb0f-daca-49d6-b3dd-a96774de9f72")); // Nexus 5
        ids.push_back(picojson::value("33ad9d96-df00-42a2-b5ab-73417f777d42")); // iphone 4s
        ids.push_back(picojson::value("5ea075c5-016d-4f55-891c-3b6c4b393e49")); // ios simulator

        // data
        picojson::object data;
        data["foo"] = picojson::value("bar");

        //
        picojson::object obj;
        obj["contents"] = picojson::value(contents);
        obj["include_player_ids"] = picojson::value(ids);
        obj["data"] = picojson::value(data);

        picojson::value v(obj);
        CCLOG("picojson json=%s", v.serialize().c_str());

        // https://documentation.onesignal.com/v2.0/docs/notifications-create-notification
        sdkbox::PluginOneSignal::postNotification(v.serialize());
    };

    postNotificationTest();
    sdkbox::PluginOneSignal::promptLocation();
    // ui
    auto size = Director::getInstance()->getWinSize();
    auto menu = Menu::create(
                             MenuItemFont::create("post notification", [=](Ref*) {
        postNotificationTest();
    }),
                             NULL
                             );
    menu->setPosition(size / 2);
    addChild(menu);
}

