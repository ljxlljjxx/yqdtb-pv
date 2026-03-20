## Power Violence Edition

### Overall Introduction of This Project
* This project is designed to create the `Power Violence Edition`, including its rules and procedures. 
* This project has not yet been fully completed. The main part of the project's program has not been fully built.(In fact, it is almost empty.) The version of the project's rules is **0.0.15**, and the latest version of the project's update announcement is **0.0.19**.

### Specific Implementation of This Project
* The implementation of this project is placed in the **src** directory. **PowerViolenceObjects** is a set of data types in `PV`, mainly written in **C**. The **PowerViolence** directory contains the program implementation of `PV`, mainly written in **Python**.
* The rules section of this project includes the general rules and update announcements. The general rules are written in **Markdown** and are converted into a **PDF** file. The update announcements are also written in **Markdown**, but no **PDF** file is generated. Some pictures and the corresponding **Python** files for generating those pictures are also included in the rules section.
* The testing section of this project is located in the **tests** directory. The **ctests** directory mainly contains tests for **PowerViolenceObjects**, and the **pytests** directory mainly contains tests for **PowerViolence**.
* This project also includes a simple implementation, named **PowerViolence_simplified**, which does not fully implement the rules and can only allow one player and one computer to play against each other. This file is a **macOS** executable file.


## 元气打腿版

### 本项目整体介绍
* 本项目用来制作`元气打腿版`, 包含其规则和程序。
* 本项目目前尚未完全实现。本项目程序尚未搭完框架。本项目规则版本为**0.0.15**, 本项目更新公告最新版本为**0.0.19**。

### 本项目具体实现
* 本项目的实现放在**src**目录下。其中**PowerViolenceObjects**为`打腿版`中的一些数据类型, 主要语言为*C*。**PowerViolence**目录下为`打腿版`游戏的程序实现, 主要语言为*Python*。
* 本项目的规则部分包含总规则和更新公告。总规则使用*Markdown*撰写, 并对应生成*PDF*文件。更新公告也使用*Markdown*撰写, 但不生成*PDF*文件。规则部分另附有一些图片以及生成该图片的*Python*文件。
* 本项目的测试部分位于**tests**目录下, 其中**ctests**目录下主要为**PowerViolenceObjects**的测试, **pytests**目录下主要为**PowerViolence**的测试。
* 本项目另附一个简单实现, 被命名为**PowerViolence_simplified**, 不完全实现规则, 且只能一名玩家和一名电脑进行对战。该文件为*macOS*可执行文件。

[PV_rule](rule/PV_rule.html)
