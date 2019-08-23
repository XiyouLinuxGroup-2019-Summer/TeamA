#include <iostream> 
#include <unistd.h> 
#include <sys/types.h> 
using namespace std; 
int main() 
{ 
//子进程创建了几个，为什么执行顺序会是这个样子 
for(int i = 1; i < 4; i ++) 
{ 
pid_t t = fork(); 
if(t == 0) 
{ 
cout << "child " << getpid()<< endl; } 
else { 
cout << "parent " << getpid()<< endl; 
}

} 
return 0; 
}
