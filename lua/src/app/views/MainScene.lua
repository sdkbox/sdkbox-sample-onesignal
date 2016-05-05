
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()

    local postNotificationTest = function() end

    local menu = cc.Menu:create()

    local label1 = cc.Label:createWithSystemFont("post notification lua", "sans", 28)
    local item1 = cc.MenuItemLabel:create(label1)
    item1:onClicked(function()
        postNotificationTest()
    end)
    menu:addChild(item1)

    local item2 = cc.MenuItemFont:create("<null>")
    item2:setEnabled(false)
    menu:addChild(item2)

    menu:alignItemsVerticallyWithPadding(24)
    self:addChild(menu)

    -- plugin
    require "json"
    sdkbox.PluginOneSignal:init()
    sdkbox.PluginOneSignal:setListener(function ( args )
      dump(args)
      local event = args.event
      if "onSendTag" == event then
        print(args.success, args.key, args.message)
      elseif "onGetTags" == event then
        dump(json.decode(args.jsonString))
      elseif "onIdsAvailable" == event then
        print(args.userId, args.pushToken)
        item2:setString(args.userId)
      elseif "onPostNotification" == event then
        print(args.success, args.message)
      elseif "onNotification" == event then
        print(args.isActive, args.message, args.additionalData)
      end
    end)

    sdkbox.PluginOneSignal:setSubscription(true)
    sdkbox.PluginOneSignal:setEmail("test@example.com")
    sdkbox.PluginOneSignal:sendTag("key", "value")
    sdkbox.PluginOneSignal:sendTag("keylua1", "valuelua1")
    sdkbox.PluginOneSignal:getTags()
    sdkbox.PluginOneSignal:deleteTag("key")
    sdkbox.PluginOneSignal:idsAvailable()
    sdkbox.PluginOneSignal:enableInAppAlertNotification(true)
    sdkbox.PluginOneSignal:promptLocation()

    postNotificationTest = function ()
        -- https://documentation.onesignal.com/v2.0/docs/notifications-create-notification
        local data = {
            contents = {
                en = "Test Message"
            },
            data = {
                foo = "bar"
            },
            include_player_ids = {
                "5ea075c5-016d-4f55-891c-3b6c4b393e49",
                "4db7cb0f-daca-49d6-b3dd-a96774de9f72",
                "33ad9d96-df00-42a2-b5ab-73417f777d42","5ea075c5-016d-4f55-891c-3b6c4b393e49"
            }
        }
        sdkbox.PluginOneSignal:postNotification(json.encode(data))
    end
    postNotificationTest()

end

return MainScene
