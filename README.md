# 笔记
### find

```
struct stat结构体存放文件类型，大小，连接数等
struct dirent结构体存放文件名称，名称长度
```

```
fstat(fd,struct stat *)
fd为文件描述符，由open()打开，获取该文件描述符所指的文件信息
```

```
stat(path,stuct stat *)
path为路径(包括文件名)，获取该路径所指的文件信息

fstat 可以获取一个文件描述符指向的文件的信息
```

```
如果fd所指为目录文件：
read(fd,stuct dirent* dir,sizeof(dir))
可遍历读取该目录下的文件，并存入dir中

若需递归遍历则可检测path+dir.name是否为目录文件( stat() )
```

### xargs

```
‘|’将其之前的输出结果作为其后的输入参数
 argv[0]则是‘|’之后的第一个参数
 ```

### read/write

```fd:```
```0:stdin  标准输入```   
```1:stdout   标准输出```  
```2:stderr    标准错误输出```