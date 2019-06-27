# IRcamera-radis

目标：
监测radis传递过来的命令，调用武汉高德工业红外摄像头拍摄红外图像

流程：
1、radis采用发布者/订阅者模式，订阅Sensor通道；
2、通过武汉高德红外摄像头SDK提供的接口，连接摄像头，登录，打开流，设置回调函数，设置色带等；
3、YuMiRobot机器人通过Sensor通道发布到达指定点的命令（Robot::Arrive_Purpose_A or Robot::Arrive_Purpose_B）；
4、程序接收到指定命令后，控制摄像头对焦并拍照，通过回调函数获取温度矩阵、最高温、最低温等
5、存图，名称包含最高温及最低温数据，下一步由matlab脚本进行图像处理

![](/img/预览图.JPG)
