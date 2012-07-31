A Cocos2d-x Asynchronous Http Request Libray That Let You Make Asynchrounous Http Request From Cocos2d-x A FUN!

You can find the library file:
CCHttpRequest.h
CCHttpRequest.cpp
Under CCHttpRequestExample/Classes

This library had been written as a cocos2d-x extension, Use it is very simple:

CCHttpRequest *gateway = CCHttpRequest::sharedHttpRequest();

//Get Request
std::string url = "http://www.baidu.com";
gateway->addGetTask(url, NULL, NULL);

//Post Request
std::string postData = "key=value";
gateway->addPostTask(url, postData, NULL, NULL);

//Download File
std::vector<std::string> downloads;
downloads.push_back("http://www.baidu.com/index.php");
gateway->addDownloadTask(urls, NULL, NULL);

You can specify a callback just by simply replace the NULL parameter with your selector, So you can process the response data in your callback method.
