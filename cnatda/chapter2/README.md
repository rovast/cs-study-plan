# 传输层


## UDP


启动 server 来监听 12000 端口
```bash
python UDPServer.py

# The server is ready to receive
```


启动 client 来进行数据发送，并返回已经被转为大写的数据
```bash
python UDPClient.py
# Input lower case senrence:hello
# HELLO
```


## TCP


Server
```bash
python TCPServer.py 
# The server is ready to receive
```

Client
```bash
python TCPClient.py
# Input lowercase sentence:hello
# ('From server:', u'HELLO')
```

