#include <iostream>

template<class T>
class MyList{
private:
    T *p=nullptr; // 数组指针初始化为空指针
    int _capacity=0; // 容量初始化为0
    int _size=0; // 元素个数初始化为0
public:
    T *it=nullptr; // 迭代器指针初始化为空指针
    bool empty() // 判断链表是否为空
    {
        if (p==nullptr) // 空指针
            return true; // 链表为空
        else
            return false; // 链表不为空
    }
    void create_list(int &capacity,int &size) // 创建链表
    {
        capacity=2; // 初始容量为2
        p=new T[capacity]; // 创建指针数组模拟链表
        size=1; // 初始元素个数为1
    }
    T* whether_resize(int new_capacity,int &capacity) // 判断是否重新指定容量
    {
        if (new_capacity==capacity) // 容量不变
        {
            std::cout<<"容量不变"<<std::endl;
            return p; // 返回原数组的指针
        }
        else
        {
            T* q=new T[new_capacity]; // 创建新容量的数组
            int i;
            if (new_capacity>capacity) // 数组扩容
            {
                for (i=0;i<capacity;i++) // 把原数组的元素复制到新容量的数组中
                    q[i]=p[i];
                for (int j=i;j<new_capacity;j++) // 将扩容新空间的元素初始化为0
                    q[j]=0;
            }
            else // 数组缩容
            {
                for (i=0;i<new_capacity;i++) // 保留原数组的前面部分元素复制到新容量的数组中
                    q[i]=p[i];
            }
            capacity=new_capacity; // 更新容量
            return q; // 返回新容量的数组的指针
        }
    }
    void resize(int new_capacity) // 重新指定容量
    {            
        p=whether_resize(new_capacity,_capacity); // 判断是否重新指定容量
        if (_size>_capacity) // 原元素个数大于新容量
            _size=_capacity; // 更新元素个数
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
    T front() // 读取链表头元素
    {
        return p[0];
    }
    T back() // 读取链表尾元素
    {
        return p[_size-1];
    }
    T* begin() // 读取链表头元素地址
    {
        it=&p[0];
        return it;
    }
    T* end() // 读取链表尾元素地址的后一位地址
    {
        it=&p[_size];
        return it;
    }
    T* advance(T* it,int move) // 迭代器移动
    {
        if (move==0)
            std::cout<<"迭代器未移动"<<std::endl;
        else if (move>0) // 迭代器前移
            for (int i=0;i<move;i++)
                it++;
        else // 迭代器后移
            for (int i=0;i>move;i--)
                it--;
        return it;
    }
    void add_data_preparation() // 添加数据前的准备工作
    {
        bool flag=empty(); // 判断链表是否为空
        if (flag==1) // 链表为空
            create_list(_capacity,_size); // 创建新链表
        else
        {
            _size++; // 元素个数加1
            p=whether_capacity_expansion(_capacity,_size); // 判断数组是否扩容
        }
    }
    void push_back(T data) // 尾插数据
    {
        add_data_preparation(); // 添加数据前的准备工作
        p[_size-1]=data;
    }
    void push_front(T data) // 头插数据
    {
        add_data_preparation(); // 添加数据前的准备工作
        for (int i=_size-2;i>=0;i--)
            p[i+1]=p[i]; // 元素后移一位
        p[0]=data;
    }
    void pop_back() // 尾删数据
    {
        p[_size-1]=0; // 末尾元素设为0
        _size--; // 元素个数减1
    }
    void pop_front() // 头删数据
    {
        for (int i=1;i<_size;i++) // 从第二项开始元素前移一位，覆盖第一项
            p[i-1]=p[i];
        p[_size-1]=0; // 原最后一项元素设为0
        _size--; // 元素个数减1
    }
    int it_to_index(T *it) // 找到迭代器指向的数组下标
    {
        int i; // 数组下标
        for (i=0;i<_size;i++)
        {
            if (it==&p[i])
                break;
        }
        return i;
    }
    void insert(T* it,T data) // 添加一个元素
    {
        add_data_preparation(); // 添加数据前的准备工作
        int i=it_to_index(it); // 找到迭代器指向的数组下标i
        for (int j=_size-2;j>=i;j--)
            p[j+1]=p[j]; // 元素后移一位
        p[i]=data;
    }
    void insert(T* it,int n,T data) // 添加n个元素
    {
        for (int j=0;j<n;j++) // 进行n次添加一个元素的操作
            insert(it,data);
    }
    void erase(T* it) // 删除一个元素
    {
        int i=it_to_index(it); // 找到迭代器指向的数组下标i
        for (int j=i+1;j<_size;j++) // 从要删除的元素的后一元素开始前移一位，覆盖要删除的元素
            p[j-1]=p[j];
        p[_size-1]=0; // 原最后一项元素设为0
        _size--; // 元素个数减1
    }
    void remove(T data) // 删除容器中所有某一元素
    {
        for (int i=0;i<_size;i++) 
        {
            if (p[i]==data)
            {
                for (int j=i;j<_size-1;j++)
                    p[j]=p[j+1]; // 从要删除的元素的后一项开始元素前移一位，覆盖要删除的元素项
                p[_size-1]=0; // 原最后一项元素设为0
                _size--; // 元素个数减1
                i--; // 这一步i--与for循环i++抵消，i值不变，下一个元素的下标等于刚被删除的元素的下标，下一步检验下一个元素是否等于要删除的元素
            }
        }
    }
    void clear() // 清除链表
    {
        delete[] p; // 释放内存
        p=nullptr; // 将野指针设为空指针
        _capacity=0; // 容量初始化为0
        _size=0; // 元素个数初始化为0
    }
    void sort() // 元素升序排列
    {
        for (int i=0;i<_size-1;i++)
        {
            for (int j=0;j<_size-1-i;j++)
            {
                if (p[j]>p[j+1]) // 前项大于后项时交换前后项
                {
                    T t=p[j];
                    p[j]=p[j+1];
                    p[j+1]=t;
                }
            }
        }
    }
    void reverse() // 元素倒序排列
    {
        for (int i=0;i<_size/2;i++) // 关于中间（两）项对称的两项交换
        {
            T t=p[i];
            p[i]=p[_size-1-i];
            p[_size-1-i]=t;
        }
    }
};

int main()
{
    /* 
    无法通过 MyList<T>::iterator it 创建迭代器
    只能使用 MyList 成员 it 为迭代器,语法如:
    MyList<int>a;
    a.it=a.begin();
    其他语法与STL list相同
    */
    return 0;
}