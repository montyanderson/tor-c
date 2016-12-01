# tor-c
Connecting through Tor in C.

```
$ gcc main.c && ./a.out
HTTP/1.0 302 Found
Cache-Control: private
Content-Type: text/html; charset=UTF-8
Location: http://www.google.fr/?gfe_rd=cr&ei=I6RAWJrpDeLM8ge0rq_ACw
Content-Length: 258
Date: Thu, 01 Dec 2016 22:28:51 GMT

<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>302 Moved</TITLE></HEAD><BODY>
<H1>302 Moved</H1>
The document has moved
<A HREF="http://www.google.fr/?gfe_rd=cr&amp;ei=I6RAWJrpDeLM8ge0rq_ACw">here</A>.
</BODY></HTML>
```
