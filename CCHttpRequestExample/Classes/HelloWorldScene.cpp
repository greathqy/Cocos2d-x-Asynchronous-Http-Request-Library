#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCHttpRequest.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    CCHttpRequest *requestor = CCHttpRequest::sharedHttpRequest();
    
    std::string url = "http://www.baidu.com";
    std::string postData = "key=val";
    
    requestor->addGetTask(url, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    requestor->addPostTask(url, postData, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
    std::vector<std::string> downloads;
    downloads.push_back("http://www.baidu.com/index.html");
    requestor->addDownloadTask(downloads, this, callfuncND_selector(HelloWorld::onHttpRequestCompleted));
    
    return true;
}

void HelloWorld::onHttpRequestCompleted(cocos2d::CCObject *pSender, void *data)
{
    HttpResponsePacket *response = (HttpResponsePacket *)data;
    
    if (response->request->reqType == kHttpRequestGet) {
        if (response->succeed) {
            CCLog("Get Request Completed!");
            CCLog("Content: %s", response->responseData.c_str());
        } else {
            CCLog("Get Error: %s", response->responseData.c_str());
        }
    } else if (response->request->reqType == kHttpRequestPost) {
        if (response->succeed) {
            CCLog("Post Request Completed!");
            CCLog("Content: %s", response->responseData.c_str());
        } else {
            CCLog("Post Error: %s", response->responseData.c_str());
        }
    } else if (response->request->reqType == kHttpRequestDownloadFile) {
        if (response->succeed) {
            CCLog("Download Request Completed! Downloaded:");
            
            std::vector<std::string>::iterator iter;
            for (iter = response->request->files.begin(); iter != response->request->files.end(); ++iter) {
                std::string url = *iter;
                CCLog("%s", url.c_str());
            }
        } else {
            CCLog("Download Error: %s", response->responseData.c_str());
        }
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
