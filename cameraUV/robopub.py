# -*- coding: utf-8 -*-

import redis
rc=redis.Redis(host="127.0.0.1",port="6379")
print(redis.ConnectionError())
flag=1
while(flag):
    order=input("order:")
    if order=="QUIT" :
        flag=0
    rc.publish("Sensor",order)
    print(order)
    