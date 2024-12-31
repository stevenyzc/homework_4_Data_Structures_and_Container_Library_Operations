template<class T>
class MyQueue{
private:
    T *p=nullptr; // 数组指针初始化为空指针
    int _capacity=0; // 容量初始化为0
    int _size=0; // 元素个数初始化为0
public:
    bool empty() // 判断队列是否为空
    {
        if (p==nullptr) // 空指针
            return true; // 队列为空
        else
            return false; // 队列不为空
    }
    void create_queue(int &capacity,int &size) // 创建队列
    {
        capacity=2; // 初始容量为2
        p=new T[capacity]; // 创建指针数组模拟队列
        size=1; // 初始元素个数为1
    }
    T* whether_capacity_expansion(int &capacity,int &size) // 判断数组是否扩容
    {
        if (size>capacity) // 元素个数大于容量时数组扩容
        {
            capacity*=2; // 容量翻倍
            T* q=new T[capacity]; // 创建扩容后的新数组
            int i;
            for (i=0;i<capacity/2;i++) // 把原数组的元素复制到扩容后的新数组中
                q[i]=p[i];
            for (int j=i;j<capacity;j++) // 将扩容新空间的元素初始化为0
                q[j]=0;
            return q; // 返回扩容后的新数组的指针
        }
        else 
            return p; // 返回原数组的指针
    }
    int size() // 读取元素个数
    {
        return _size;
    }
    T front() // 读取队首元素
    {
        return p[0];
    }
    T back() // 读取队尾元素
    {
        return p[_size-1];
    }
    void add_data_preparation() // 添加数据前的准备工作
    {
        bool flag=empty(); // 判断队列是否为空
        if (flag==1) // 队列为空
            create_queue(_capacity,_size); // 创建新队列
        else
        {
            _size++; // 元素个数加1
            p=whether_capacity_expansion(_capacity,_size); // 判断数组是否扩容
        }
    }
    void push(T data) // 入队
    {
        add_data_preparation(); // 添加数据前的准备工作
        p[_size-1]=data;
    }
    void pop() // 出队
    {
        for (int i=1;i<_size;i++) // 从第二项开始元素前移一位，覆盖第一项
            p[i-1]=p[i];
        p[_size-1]=0; // 原最后一项元素设为0
        _size--; // 元素个数减1
    }
    void clear() // 清除队列
    {
        delete[] p; // 释放内存
        p=nullptr; // 将野指针设为空指针
        _capacity=0; // 容量初始化为0
        _size=0; // 元素个数初始化为0
    }
};

int main()
{
    return 0;
}