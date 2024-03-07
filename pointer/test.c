/* 结构体指针变量测试代码 */
#include <stdio.h>
#include "uni_oneway_linkedlist.h"

typedef struct _stu_t
{
    char name[32];
    int num;
}stu_t;

/* 自定义节点中数据域销毁函数 */
int node_destroy(void *data)
{
    // 释放结构体指针指向的结构体空间
    free(*(stu_t **)data);

    // 释放数据域
    free(data);
    data = NULL;
    return 0;
}

/* 自定义数据域打印函数 */
int data_print(void *data)
{
    printf("name: %s  num: %d\n", (*(stu_t **)data)->name, (*(stu_t **)data)->num);
    return 0;
}

/* 自定义关键字比较函数 */
int data_compare(void *data, void *key)
{
    if (0 == memcmp(*(stu_t **)data, *(stu_t **)key, sizeof(stu_t)))
    {
        return MATCH_SUCCESS;
    }
    else 
    {
        return MATCH_FAIL;
    }
}


int main(int argc, char **argv)
{
    uolist_t *head = NULL;
    stu_t *stu = NULL;

    // 创建头信息结构体
    head = uolist_create(sizeof(stu_t *), node_destroy);

    // 插入
    stu = (stu_t *)calloc(1, sizeof(stu_t));
    stu->num = 1;
    strcpy(stu->name, "bob");
    uolist_prepend(head, &stu);

    stu = (stu_t *)calloc(1, sizeof(stu_t));
    stu->num = 2;
    strcpy(stu->name, "lucy");
    uolist_append(head, &stu);

    stu = (stu_t *)calloc(1, sizeof(stu_t));
    stu->num = 3;
    strcpy(stu->name, "john");
    uolist_insert_by_index(head, &stu, 1);

    uolist_reverse(head);

    // 输出
    printf("cnt: %d\n", get_count(head));
    uolist_traverse(head, data_print);

    uolist_destroy(head);
    head_destroy(&head);

    return 0;
}