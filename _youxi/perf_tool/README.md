# Distributed Performance Test Tool Design Doc

## 配置方法 
1. 命令行参数，
- master命令行参数

```shell
./master --name master --port 9099 --total_count 200 --slave 10 --stress_hold_on_time=30 --request_count=5
```

- slave命令行参数

```shell
./slave --name node1
```

2. 通过配置文件配置

- master 的配置文件

```
name: master
host: localhost
port: 9099
total_count: 100
slave: 10
stress_hold_on_time: 30
request_count: 5
```

- slave的配置文件

```
name: node1
host: localhost
port: 9099
```

## 注册部分

master和各个slave起来的时候，首先要注册自己
- 读取配置文件，或者命令行参数
- 向服务器发送BindName消息注册自己

## 业务部分，

## TODO, 这一部分需要还没开始
- Master 读取配置文件，通过total_count和slave_count计算单机需要的线程数，例如200 / 10 = 20

- Master读取请求列表文件，带上上一步计算出来的线程数，还有各种配置参数，拼成一个新的json，例如，

```
{
    "requests" :{
        "single": [
            {
                "url": "https://www.baidu.com",
                "method": "GET",
                "Content-Type": "application/json",
                "body": ""
            }
        ],
        "multiple": ...
    },
    "thread_count": 20, // [上一步计算出来的值]
    "stress_hold_on_time": 30
}
```

- master 通过服务端将json string发送给自己和每个slave。
    - 发送一个MT_LAUNCH_TASK_MSG，
    - dump json成字符串，然后发送到每个slave和自己。


- server啥都不干，直接转发MT_LANCH_TASK_MSG
    - 每个slave和master自己接收到json字符串之后，反解，生成json。
根据收到的json进行请求，记录每个请求的响应时间，以及平均响应时间等。生成一个带
请求结果的新json。

```
{
    "requests" :{
        "single": [
            {
                "url": "https://www.baidu.com",
                "method": "GET",
                "Content-Type": "application/json",
                "body": "",
                // 在这里更新请求结果
                "max_request_time": 2,
                "min_request_time": 0.001,
                "avg_request_time": 0.1,
                "through_out": 0.167
            }
        ],
        "multiple": ...
    },
    "thread_count": 20,
    "stress_hold_on_time": 30
}
```

- 每个slave和master，单独发一个 MT_SEND_TASK_INFO_MSG, 把上一步生成的请求结果json字符串发送出去

- server不做任何处理，直接转发 MT_SEND_TASK_INFO_MSG，但是这个msg不是完全转发，
    这一次只转发给master。

- 其他slave node不会接收到 MT_SEND_TASK_INFO_MSG, 
    master node会多次接收到  MT_SEND_TASK_INFO_MSG。
    - master多次接收消息并计算结果，slave不用。
    [master用master.cpp实现， slave用slave.cpp实现，
        server用server.cpp实现]
    


## 请求交换格式
和slave交换请求的格式，包括Authorization-Token等,如果有的话
```
{
    "single": [
        {
            "url": "https://www.baidu.com",
            "method": "GET",
            "Content-Type": "application/json",
            "body": ""
        }
    ],
    
    "multiple": {
        "group1" :[
            {request1},
            {request2}
        ],
        "group2": [
            {request1},
            {request2}
        ]
    }
}
```


