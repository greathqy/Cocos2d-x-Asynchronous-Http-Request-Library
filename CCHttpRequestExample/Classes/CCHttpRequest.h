//
//  HttpRequest.h
//
//  Created by qingyun on 12-7-29.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
//  @author greathqy@gmail.com
//  sina weibo: http://weibo.com/u/1678467541

#ifndef CCHttpRequest_h
#define CCHttpRequest_h

#include "cocos2d.h"
#include <curl/curl.h>

USING_NS_CC;

NS_CC_EXT_BEGIN

typedef enum {
    kHttpRequestGet,
    kHttpRequestPost,
    kHttpRequestDownloadFile,
} HttpRequestType;

typedef struct {
    HttpRequestType             reqType;
    std::string                 url;
    std::string                 reqData;
    std::vector<std::string>    files;
    std::string                 reqName;
    CCObject                    *pTarget;
    SEL_CallFuncND              pSelector;
} HttpRequestPacket;

typedef struct {
    HttpRequestPacket       *request;
    std::string             responseData;
    int32_t                 responseCode;
    bool                    succeed;
} HttpResponsePacket;

class CCHttpRequest : public CCObject
{
public:
    static CCHttpRequest *sharedHttpRequest();
    static void purgeSharedHttpRequest();
    CCHttpRequest();
    virtual ~CCHttpRequest();
    
    void addGetTask(std::string &url, CCObject *pTarget, SEL_CallFuncND pSelector);
    void addPostTask(std::string &url, std::string &postData, CCObject *pTarget, SEL_CallFuncND pSelector);
    void addDownloadTask(std::vector<std::string> &urls, CCObject *pTarget, SEL_CallFuncND pSelector);
    
    void httpRequestCallback(float delta);
    
public:
    inline void setConnectTimeout(int32_t timeout) {m_connectTimeout = timeout;};
    inline void setDownloadTimeout(int32_t timeout) {m_timeout = timeout;};
    inline int32_t getConnectTimeout() {return m_connectTimeout;}
    inline int32_t getDownloadTimeout() {return m_timeout;}
    
private:
    bool lazyInitThreadSemphore();
    
private:
    int32_t m_connectTimeout;
    int32_t m_timeout;
};

NS_CC_EXT_END

#endif
