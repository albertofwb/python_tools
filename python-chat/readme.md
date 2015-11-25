参考来源（其实我从上面复制了一点）：
Python 的 Socket 编程教程  http://www.oschina.net/question/12_76126
Python线程指南 http://www.open-open.com/lib/view/open1345476194313.html

具体思路：
每个client有两个线程，分别负责接收和发送，当没有发送时，在raw_input()那卡住，当没有接收时，在recv()那卡住
server为每个client开两个线程，分别处理接收和发送。每个发送的线程在con.wait()那阻塞，等待notify。每个接收的线程，在recv()那里等待来自client的输入，接收到输入后，发出一个notify，激活所有输出线程，自身则因为循环在下一个recv()那里等待。

这样做的优势时在等待期间，cpu都处于空闲状态，cpu只在接收和发送的瞬间被使用。
目前没有想到更好方法。。。

注意：
我做得有点粗糙，复制后有些注释和代码对应不起来，也没有添加新的注释
