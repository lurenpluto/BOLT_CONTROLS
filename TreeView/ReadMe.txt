TreeView/ReadMe.txt
安装和使用方法:
请先安装Bolt SDK
把文件夹ListView放在/Bolt_SDK/samples下编译运行. 

编译运行时工程会分别在/Bolt_SDK/bin, /Bolt_SDK/include, /Bolt_SDK/lib下寻找XLUE.dll, XLUE.h, XLUE.lib等库和头文件, 这些文件在正确安装Bolt SDK后应该存在. 

示例会使用TreeView/xl_lib和TreeView/xl_include下寻找xl_lib_static.lib及其头文件来做字符转换. 请替换成你习惯使用的方法或者到ListView/xl_lib下拷贝过来.  

示例读取系统目录并以TreeView的形式显示出来. 