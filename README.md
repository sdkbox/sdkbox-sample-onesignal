
# How to run sdkbox samples

Steps:

~~~bash
mkdir samples
cd samples

# must clone this repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-cocos2d-x-binary.git

# clone sample repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-sample-onesignal.git

# run sample with specified language and platform
# eg: cpp and ios
# Edit cpp/Resources/sdkbox_config.json and update ios > OneSignal > id to your OneSignal App Id
./sdkbox-cocos2d-x-binary/run_sample.sh onesignal cpp ios
## or
cd cpp && cocos run -p ios

# eg: javascript and android
# Edit js/res/sdkbox_config.json and update android > OneSignal > id to your OneSignal App Id
#  Also update "project_number" to your Google Project number.
./sdkbox-cocos2d-x-binary/run_sample.sh onesignal js android
## or
cd js && cocos run -p android

# <optional> if exists "download-depends.sh" in sample repo, execute it
# ./sdkbox-sample-onesignal/download-depends.sh

~~~

Memo:

1.  Sample repo and cocos2dx repo must be in same level directory

~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-onesignal
| +-- cpp
| +-- lua
| \-- js
~~~
