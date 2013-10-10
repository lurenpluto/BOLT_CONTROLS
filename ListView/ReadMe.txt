ListView/ReadMe.txt
安装和使用方法:
请先安装Bolt SDK
把文件夹ListView放在/Bolt_SDK/samples下编译运行. 

编译运行时工程会分别在/Bolt_SDK/bin, /Bolt_SDK/include, /Bolt_SDK/lib下寻找XLUE.dll, XLUE.h, XLUE.lib等库和头文件, 这些文件在正确安装Bolt SDK后应该存在. 

示例会在../3rd/inc, ../3rd/lib下寻找xl_lib_static.lib及其头文件来解析xml文件和做字符转换. 

示例读取一个"音乐.xml"文件, 用<media>区分每一条文件, 读取并以列表形式显示歌曲名称, 源地址, 和图片. 