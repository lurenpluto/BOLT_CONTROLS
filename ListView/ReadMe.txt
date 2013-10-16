ListView/ReadMe.txt
安装和使用方法:

选择A. 系统中有预装BOLT_SDK的情况下:
	1. 把BOLT_SDK的 bin 目录, lib 目录和 include 目录下的链接库, 静态库和头文件分别拷贝到 ListView/bin, ListView/lib 和 ListView/include 下. 
	2. 打开HelloBolt.sln, 编译, 运行
	3. 编译结果 datamodel.dll 和 ListView.exe 都会输出到 ListView/bin下, 前者解析xml文件并返回"音乐"列表, 后者是 ListView 控件示例的可执行文件; 

选择B. 系统中没有预装 BOLT_SDK 而且也不想装的情况下: 
	1. 执行 ListView/build_treeview_env.bat, 脚本会从 Bolt_SDK 的 git 上获取执行示例需要的文件放到 ListView 相应的目录下
	2. 3. 同选择A. 

示例读取一个"音乐.xml"文件, 用<media>区分每一条文件, 读取并以列表形式显示歌曲名称, 源地址, 和图片. 