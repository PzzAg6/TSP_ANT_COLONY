## void io  
从一个路径当中读取.tsp，然后存到一个矩阵当中去  
用到stringstream，打开文件，从行中读取字符串，然后写入stringstream中，再从stringstream中把数据读取出来（真的太妙了）  
```c++
 num_line << line;
                while(num_line >> num){
                    p[i][j] = num;
                    j++;
                }
                num_line.clear();//不清理缓冲区的话，都是零
                j = 0;
                i++;
```
如果不加`num_line.clear()`，只能读取一行，我才可能是读取到最后一个字符以后，缓冲区满了？或者出现了goodit有异常？估计和getline有关，估计释放掉可能就好了。总之这个地方研究下  
其实有文件的话，直接按照行来计数就好了，不必这么麻烦。