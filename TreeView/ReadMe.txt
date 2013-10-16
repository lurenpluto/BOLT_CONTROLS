TreeView/ReadMe.txt
安装和使用方法:

选择A. 系统中有预装BOLT_SDK的情况下:
	1. 把BOLT_SDK的 bin 目录, lib 目录和 include 目录下的链接库, 静态库和头文件分别拷贝到 TreeView/bin, TreeView/lib 和 TreeView/include 下. 
	2. 打开HelloBolt.sln, 编译, 运行
	3. 编译结果 DirModel.dll 和 TreeView.exe 都会输出到 TreeView/bin下, 前者是读取系统目录的数据模型, 后者是 TreeView 控件示例的可执行文件; 

选择B. 系统中没有预装 BOLT_SDK 而且也不想装的情况下: 
	1. 执行 TreeView/build_treeview_env.bat, 脚本会从 Bolt_SDK 的 git 上获取执行示例需要的文件到 TreeView 相应的目录下
	2. 3. 同选择A. 

示例读取系统目录并以 TreeView 的形式显示出来. 