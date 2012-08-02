/****************************************************************************
 @author greathqy@gmail.com
 @weibo http://weibo.com/u/1678467541
 
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

#ifndef __CCHttpRequest_h
#define __CCHttpRequest_h

#include "cocos2d.h"
#include <curl/curl.h>

USING_NS_CC;

NS_CC_EXT_BEGIN

//Http request type
typedef enum {
    kHttpRequestGet,
    kHttpRequestPost,
    kHttpRequestDownloadFile,
} HttpRequestType;

//Request structure
typedef struct {
    HttpRequestType             reqType;
    std::string                 url;
    std::string                 reqData;
    std::vector<std::string>    files;
    std::string                 reqName;
    CCObject                    *pTarget;
    SEL_CallFuncND              pSelector;
} HttpRequestPacket;

//Response structure
typedef struct {
    HttpRequestPacket       *request;
    std::string             responseData;
    int32_t                 responseCode;
    bool                    succeed;
} HttpResponsePacket;

/** @brief Singleton that handles asynchrounous http requests
 * Once the request completed, a callback will issued in main thread when it provided during make request
 */
class CCHttpRequest : public CCObject
{
public:
    /** Return the shared instance **/
    static CCHttpRequest *sharedHttpRequest();
    
    /** Relase the shared instance **/
    static void purgeSharedHttpRequest();
    
    CCHttpRequest();
    virtual ~CCHttpRequest();
    
    /**
     * Add a get request to task queue
     * @param url url want to get
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addGetTask(std::string &url, CCObject *pTarget, SEL_CallFuncND pSelector);
    
    /**
     * Add a get request to task queue
     * @param url the post destination url
     * @param postData data want to post
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addPostTask(std::string &url, std::string &postData, CCObject *pTarget, SEL_CallFuncND pSelector);
    
    /**
     * Add a get request to task queue
     * @param url urls want to download
     * @param pTarget  callback target
     * @param pSelector callback selector
     * @return NULL
     */
    void addDownloadTask(std::vector<std::string> &urls, CCObject *pTarget, SEL_CallFuncND pSelector);
    
public:
    /**
     * Change the connect timeout
     * @param timeout 
     * @return NULL
     */
    inline void setConnectTimeout(int32_t timeout) {m_connectTimeout = timeout;};
    
    /**
     * Change the download timeout
     * @param timeout
     * @return NULL
     */
    inline void setDownloadTimeout(int32_t timeout) {m_timeout = timeout;};
    
    /**
     * Get connect timeout
     * @return int
     */ 
    inline int32_t getConnectTimeout() {return m_connectTimeout;}
    
    /**
     * Get download timeout
     * @return int
     */
    inline int32_t getDownloadTimeout() {return m_timeout;}
    
private:
    /**
     * Init pthread mutex, semaphore, and create new thread for http requests
     * @return bool
     */
    bool lazyInitThreadSemphore();
    /** Poll function called from main thread to dispatch callbacks when http requests finished **/
    void httpRequestCallback(float delta);
    
private:
    int32_t m_connectTimeout;
    int32_t m_timeout;
};

NS_CC_EXT_END

#endif //__CCHttpRequest_h
