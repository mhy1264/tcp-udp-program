# ucp 

## 環境
    * Kde Neon 
    * gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04)

## configuration

### server 端
        1. 把第11行的 SERVER ip 改成伺服器端的 ip Address 
        2. g++ -o server.out udp_ack_server.cpp
        3. ./server.out 8888

### client 端
        1. 把第11行的 SERVER ip 改成伺服器端的 ip Address 
        2. g++ -o client.out udp_ack_client.cpp
        3. ./client.out 8888
        
