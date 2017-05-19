### Introduction
QWebSockets is a pure Qt implementation of WebSockets - both client and server.
It is implemented as a Qt source code module (.pri file), that can easily be embedded into existing Qt projects. It has no other dependencies that Qt.

### Features
* Text and binary sockets
* Frame-based and message-based signals
* Works through proxies
* Strict Unicode checking

### Restrictions
Non-characters (according [Unicode Standard 6.2](http://www.unicode.org/versions/Unicode6.2.0/)) are rejected by QWebSockets, **even if the UTF-8 sequence is valid**.  
##### Rationale
The WebSocket specification is talking about _Valid UTF-8 codes and sequences_. Strictly speaking, UTF-xx encodings are reversible. That means, that the [66 non-character codes](http://www.unicode.org/faq/private_use.html#noncharacters) (including `U+FFFE` and `U+FFFF`), are valid UTF-8, and hence are perfectly acceptable within WebSocket text messages.  
According to the Unicode standard, they SHOULD NOT be used in information interchange, but a [recent corrigendum](http://www.unicode.org/versions/corrigendum9.html) clarifies that non-characters CAN be exchanged.  
However, non-characters are for internal use, and hence, they are implementation specific (e.g. non-characters can be used to carry meta-information). _They have to be interpreted._  
When used with `QString`, they are replaced with `U+FFFD - REPLACEMENT CHARACTER`, and rendered - non-standard - as a question mark (this is the `QString` rendering of the non-character `U+FFFD`: &#xFFFD;). Browsers keep the control characters untouched (this is the browser rendering of the non-character `U+FDD0`: &#xFDD0;).  
  
With QWebSockets, text messages are just that: a collection of human-readable characters. Text messages never have to be interpreted to be rendered correctly. In case, you still want to do implementation specific trickery, use binary messages instead. Indeed, if non-characters were allowed in text messages, then every text message has to be parsed, character-per-character, to find out if it contains special control codes, or a protocol should be devised that indicates whether the message contains that kind of control codes. We keep it simple: text is text and nothing more.

### Requirements
Qt 5.x

### Usage
Include the .pri file into your Qt project  
~~~
include (websocket.pri)
~~~

### Compliance
QWebSockets is compliant with [RFC6455](http://datatracker.ietf.org/doc/rfc6455/?include_text=1) and has been tested with the [Autobahn Testsuite](http://autobahn.ws/testsuite).  
Only tests with **Unicode non-characters** do **not** pass from the Autobahn Testsuite (see [Restrictions](#Restrictions)). 

### Missing Features
* WSS protocol
* Extensions and sub-protocols

### License
This code is licensed under LGPL v3.
