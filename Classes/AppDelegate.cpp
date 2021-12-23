/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "audio/include/AudioEngine.h"

// #define USE_AUDIO_ENGINE 1

//#if USE_AUDIO_ENGINE
//#include "audio/include/AudioEngine.h"
//#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("runnerRhythm", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("runnerRhythm");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    Size screenSize = glview->getFrameSize();
    Size designSize = Size(2048, 1536);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 768) {
        searchPaths.push_back("ipadhd");
        director->setContentScaleFactor(1536/designSize.height);
    } else if (screenSize.height > 320) {
        searchPaths.push_back("ipad");
        director->setContentScaleFactor(768/designSize.height);
    } else {
        searchPaths.push_back("iphone");
        director->setContentScaleFactor(380/designSize.height);
    }
    
    auto fileUtils = FileUtils::getInstance();
    fileUtils->setSearchPaths(searchPaths);
    
    //auto audioEngine = SimpleAudioEngine::getInstance();
         int idAudioBkg = AudioEngine::play2d( fileUtils->fullPathForFilename("background3.mp3") );
    AudioEngine::setLoop(idAudioBkg, true);
    //audioEngine->preloadBackgroundMusic(fileUtils->fullPathForFilename("background3.mp3").c_str());
    //AudioEngine::preload( fileUtils->fullPathForFilename("falling.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("falling.wav").c_str() );
    //AudioEngine::preload( fileUtils->fullPathForFilename("hitBuilding.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("hitBuilding.wav").c_str() );
    //AudioEngine::preload( fileUtils->fullPathForFilename("jump.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("jump.wav").c_str() );
    //AudioEngine::preload( fileUtils->fullPathForFilename("crashing.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("crashing.wav").c_str() );
    //AudioEngine::preload( fileUtils->fullPathForFilename("start.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("start.wav").c_str() );
    //AudioEngine::preload( fileUtils->fullPathForFilename("openUmbrella.wav") );
    //audioEngine->preloadEffect( fileUtils->fullPathForFilename("openUmbrella.wav").c_str() );
    AudioEngine::setVolume(	idAudioBkg, 0.4f);
    //audioEngine->setBackgroundMusicVolume(0.5f);
    //audioEngine->setEffectsVolume(0.5f);
    
    
    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = GameLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    AudioEngine::resumeAll();
}
