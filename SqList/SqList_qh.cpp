/**
 * @author QH
 * @create time 2021年3月22日15:44:51
 * 线性表的基础操作参考了《数据结构（C语言版）》（严蔚敏版）第二章线性表 第19-20页的内容
 * 同时增加了王道考研中的一些操作，属于王道考研中的操作，在函数说明中会以 CSKaoYan 标注
 * 函数相同，返回形式不同的，会以函数重载的形式实现
 */
#include <iostream>

using namespace std;

#define LIST_INIT_SIZE 100      //线性表存储空间的初始分配量
#define LISTINCREMENT 10        //线性表存储空间的分配增量
#define OVERFLOW -1             //存储分配失败的返回值
#define OK 1                    //操作成功
#define ERROR -1                //条件错误，函数使用前提不成立
#define FALSE 0                 //操作失败或者判断为否

typedef int Status;             //函数状态简单编码为-1，0，1，对应以上几种情况


typedef struct {
    int value;
    string name;
} ElemType;

typedef struct {
    ElemType *elem;     //存储空间基址
    int length;         //当前长度
    int listsize;       //当前分配的存储容量（以sizeof(ElemType)为单位）
} SqList;

//#####################################################
bool equal(ElemType e1, ElemType e2) {
    if (e1.value == e2.value && e1.name == e2.name) {
        return true;
    }
    return false;
}
//#####################################################

/**
 * 初始化线性表
 * 初始化线性表，使用malloc函数给L.elem分配对应的空间
 * @param L 线性表指针
 * @return
 */
Status InitList(SqList &L) {
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

/**
 * 销毁线性表
 * 物理上需要释放L.elem的内存，逻辑上需要将L.length和L.listsize设置为0
 * 经过这样才能真正说线性表被销毁了
 * @param L 线性表指针
 * @return
 */
Status DestroyList(SqList &L) {
    if (L.elem != NULL) {
        free(L.elem);
        L.listsize = 0;
        L.length = 0;
        return OK;
    }
    return ERROR;
}

/**
 * 清空线性表
 * 辨析 若线性表未创建，则认为函数调用的条件不成立，应返回ERROR
 * 思路 在顺序线性表中，所谓清空线性表，没有必要真的去处理线性表中的每个元素
 *      只要让线性表的length为0，那么它在逻辑上就算是清空了
 * @param L 线性表指针
 * @return
 */
Status ClearList(SqList &L) {
    if (L.elem == NULL) {
        return ERROR;
    }
    L.length = 0;
    return OK;
}

/**
 * 判断线性表是否为空，若为空表则返回TRUE
 * 辨析 若线性表未创建，则认为函数调用的条件不成立，应返回ERROR
 * 思路 线性表是否为空，看L.length是否为0即可
 * @param L 线性表的指针
 * @return
 */
Status ListEmpty(SqList L) {
    if (L.elem == NULL) {
        return ERROR;
    }
    if (L.length == 0) {
        return OK;
    }
    return FALSE;
}

/**
 * 返回线性表的长度
 * @param L 线性表的指针
 * @return 线性表的长度
 */
int ListLength(SqList L) {
    return L.length;
}

/**
 * 用e返回线性表中第index个元素的值（若存在）
 * 辨析 函数调用的条件是：线性表已创建；index小于等于当前线性表长度
 *      注意下标与位序的关系
 * @param L 线性表指针
 * @param index 要获取的元素的位置
 * @param e 接收获取元素的值
 * @return
 */
Status GetElem(SqList L, int index, ElemType &e) {
    if (L.elem == NULL || index >= L.length) {
        return ERROR;
    }
    e = L.elem[index - 1];
    return OK;
}

/**
 * 返回线性表中第一个与e满足判定关系compare的元素的位置
 * @param L
 * @param e
 * @return
 */
//int LocateElem(SqList L,ElemType e,compare())

/**
 * 若cur_e是L的数据元素且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
 * 思路 先找到cur_e所在的位置,若cur_e在线性表第一个位置，报错
 *      否则，返回cur_e的前一个元素
 *      那么，直接从第二个元素开始找，如果没有找到，那么不管第一个元素是不是cur_e，都可以认为操作失败
 *      这样省去了一次比较的过程
 * @param L 线性表指针
 * @param cur_e 查找的元素
 * @param pre_e 查找元素的前驱
 * @return
 */
Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e) {
    if (L.elem == NULL) {
        return ERROR;
    }
    for (int i = 1; i < L.length; i++) {
//        if (L.elem[i].name == cur_e.name && L.elem[i].value == cur_e.value) {
//            pre_e = L.elem[i-1];
//            return OK;
//        }
//        比较Element元素相等的代码过于冗长，可以把它封装为一个函数
        if (equal(L.elem[i], cur_e)) {
            pre_e = L.elem[i - 1];
            return OK;
        }
    }
    return FALSE;
}

/**
 * 若cur_e是L的数据元素且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义
 * 思路 先找到cur_e所在的位置,若cur_e在线性表最后一个位置，报错
 *      否则，返回cur_e的后一个元素
 *      那么，只遍历到倒数第二个，如果没有找到，那么不管最后一个元素是不是cur_e，都可以认为操作失败
 *      这样省去了一次比较的过程
 * @param L 线性表指针
 * @param cur_e 查找的元素
 * @param next_e 查找元素的后继
 * @return
 */
Status NextElem(SqList L, ElemType cur_e, ElemType &next_e) {
    if (L.elem == NULL) {
        return ERROR;
    }
    for (int i = 0; i < L.length - 1; i++) {
        if (equal(L.elem[i], cur_e)) {
            next_e = L.elem[i + 1];
            return OK;
        }
    }
    return FALSE;
}

/**
 * 在线性表的第 index 个位置前插入元素 e
 * 思路 因为这是一个动态线性顺序表，因此要考虑的以下事情
 *      1、当前链表是否已满？用L.length == L.listsize判断，二者相等，表明顺序表分配的空间已满，那么为其分配一个空闲的空间
 *          追加空间可以使用realloc()函数
 *      2、要插入的位置是否合法？插入位置index不应该为0（顺序表逻辑上不存在0号元素，代码上存在），也不应该大于当前链表的长度
 *      3、要先将插入位置及以后的元素先后移一位，才能空出位置来插入新元素
 *      4、记得修改L.length的值
 * @param L 线性表指针
 * @param index 要插入的位置
 * @param e 要插入的元素
 * @return
 */
Status ListInsert(SqList &L, int index, ElemType e) {
    if (index < 1 || index > L.length) {
        return ERROR;
    }
    if (L.length == L.listsize) {
        //空间已满，追加一个空间
        L.elem = realloc(L.elem, (L.listsize + 1) * sizeof(ElemType));
        L.listsize++;
    }
    for (int i = L.length; i >= index; i--) {
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[index - 1] = e;
    L.length++;
    return OK;
}

/**
 * 删除线性表中第i个元素，并用e返回删除元素的值
 * 思路 删除操作可以视为插入操作的逆操作，不同的是，删除操作不会涉及到分配空间溢出的问题
 *      1、检查index的合法性
 *      2、删除指定位置的元素
 *      3、将被删除元素后的元素都向前移动一位
 *      显然，要删除一个元素，可以用另一个元素的值覆盖这个元素，那么这个元素在逻辑上视为被删除
 * @param L
 * @param index
 * @param e
 * @return
 */
Status ListDelete(SqList &L, int index, ElemType &e) {
    if (index < 1 || index > L.length) {
        return ERROR;
    }
    e = L.elem[index - 1];
    for (int i = index; i < L.length; i++) {
        L.elem[i - 1] = L.elem[i];
    }
    L.length--;
    return OK;
}
/**
 * 依次对线性表中的每一个元素调用函数visit(),若visit()操作失败，则整个操作失败
 * @param L
 * @return
 */
//bool ListTraverse(SqList &L,visit());

/**
 * 打印输出线性表
 * CSKaoYan
 * @param L
 * @return
 */
void PrintList(SqList L) {
    for (int i = 0; i < L.length - 1; i++) {
        cout << L.elem[i] << "->";
    }
    cout << L.elem[L.length - 1] << endl;
}

/**
 * 返回线性表的长度
 * @param L 线性表指针
 * @return
 */
int Length(SqList L);

/**
 * 判断线性表是否为空
 * @param L 线性表
 * @return
 */
Status Empty(SqList L);

/**
 * 返回线性表中元素e的位置
 * @param L 线性表
 * @param e 元素
 * @return
 */
int LocateElem(SqList L, ElemType e);

ElemType GetElem(SqList L, int i);

/**
 * 给线性表追加len个元素大小的空间
 * @param L 线性表指针
 * @param len 追加元素空间的大小
 * @return
 */
Status IncreaseSize(SqList &L, int len);

int main() {
    return 0;
}
