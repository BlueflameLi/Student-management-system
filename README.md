# Student-management-system
数据结构作业 有撤销功能的树状学生管理系统

**注：除main.c、print.c、command.c为GB2312编码,其他文件皆为UTF-8编码**

main.exe为执行文件  

main.c 为主程序模块  

stack.h 栈模块，包含撤销栈数据结构的定义及相关函数声明  
stack.c 栈模块相关函数定义  

student.h 学生模块，包含学生数据结构的定义  

print.h 界面模块,包含界面绘制相关变量及函数声明  
print.c 界面模块,包含界面绘制相关变量及函数定义  

command.h 命令模块，包含学生管理系统所使用的命令相关的变量及函数声明  
command.c 命令模块，包含学生管理系统所使用的命令相关的变量及函数定义 

# 使用说明
晚点再写  

# 5.0
新增modify命令  
新增mv命令  
新增find命令  

# 4.0
新增rm命令  
重写了create、cd命令，支持绝对路径与相对路径  
修改lr命令  
去除了addschool、addcollege、addmajor、addclass、addstudent命令，原有功能由create替代    

# 3.0
新增lr命令  
ls新增显示学生信息功能  

# 2.0
新增cd命令  
新增create命令  
新增addschool命令  
新增addcollege命令  
新增addmajor命令  
新增addclass命令  
新增addstudent命令  
重构了绘制树的函数  

# 1.0
界面绘制  
新增help命令  
新增ls命令  
新增exit命令  


