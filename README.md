# COMP3016  


# CourseWork1 -- The Urged Snake
## Introduction
Full name of subject: COMP3016 Immersive Game Technologies  
Student number: 10881130  
CW1：Snake Game A console game based on C++ and SDL
## Development Environment
Microsoft Visual Studio Professional 2022 (64 位) - Current
Version 17.7.4  
Operating System Version: Windows 10 Home Chinese version (version number 22H2)


## 贪吃蛇游戏需求
Development Environment
Visual Studio Version: 17.1.0
Operating System Version: Windows 10 Home Chinese version (version number 22H2)
界面设计
主界面
最左菜单栏按钮

定义蛇的颜色（紫、黄）
定义背景是否加网格（背景颜色为白）   
选择是否开启游戏声音
中间按钮

开始游戏
最右按钮

退出游戏
帮助界面
游戏玩法介绍：
使用 W A S D 控制蛇移动，也可以通过鼠标指引蛇移动方向
长按空格键加速
不同水果对应不同分数，共有5种
游戏主界面
左上角显示当前分数
右上角可暂停游戏
游戏结束界面
与主界面类似
显示蛇的得分
中间按钮改为重新开始游戏
游戏操作
使用 W A S D 控制蛇移动
长按空格键加速
鼠标指引蛇移动方向
蛇的特性
蛇可进行平滑曲线运动
结束判定条件为当蛇碰到自己身长两个以外节点时
游戏显示游戏结束，有碰到自己身体就死亡，并跳转至结束界面
游戏元素
不同水果对应不同分数（对应分数增长蛇身相应的长度） 共有5种
音效
吃到水果时触发吃到的音效
以上需求描述提供了贪吃蛇游戏的基本功能和用户界面。在实现这些需求时，你可以使用C++和SDL2库进行游戏的开发。需要实现蛇的平滑曲线运动、碰撞检测、游戏逻辑等功能。同时，你可以使用SDL2提供的音频功能来实现吃到水果时的音效。
