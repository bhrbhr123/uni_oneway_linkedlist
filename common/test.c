/* 普通存储(int)变量测试代码 */
#include <stdio.h>
#include "uni_oneway_linkedlist.h"

/* 自定义节点中数据域销毁函数 */
int node_destroy(void *data)
{
    free(data);
    data = NULL;
    return 0;
}

/* 自定义数据域打印函数 */
int data_print(void *data)
{
    printf("%d\n", *(int *)data);
    return 0;
}

/* 自定义关键字比较函数 */
int data_compare(void *data, void *key)
{
    if (0 == memcmp(data, key, sizeof(int)))
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
    uolist_t *index = NULL;
    uolist_t *head = NULL;
    int i = 0;
    int j = 0;
    int temp = 0;
    int key = 0;

    // 头信息结构体的创建
    head = uolist_create(sizeof(int), node_destroy);

    // 节点插入
    for (i = 1; i <= 10; i++)
    {
        uolist_append(head, &i);
    }

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表按照索引插入
    temp = 1989;
    uolist_insert_by_index(head, &temp, 6);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据索引修改
    temp = 2024;
    uolist_modify_by_index(head, &temp, 6);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据索引删除
    uolist_delete_by_index(head, 6);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据索引获取
    uolist_retrieve_by_index(head, &temp, 6);
    printf("temp = %d\n", temp);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据关键字删除
    key = 3;
    uolist_delete_by_key(head, &key, data_compare);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据关键字修改
    temp = 666;
    key = 6;
    uolist_modify_by_key(head, &temp, &key, data_compare);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据关键字获取数据
    temp = 0;
    key = 666;
    uolist_retrieve_by_key(head, &temp, &key, data_compare);
    printf("temp = %d\n", temp);

    // 尾差3个5
    temp = 5;
    uolist_append(head, &temp);
    uolist_append(head, &temp);
    uolist_append(head, &temp);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据关键字查找所有的索引
    key = 5;
    index = uolist_find_all_index_by_key(head, &key, data_compare);

    // 索引链表的遍历
    printf("count = %d\n", get_count(index));
    uolist_traverse(index, index_print);
    printf("==================================================\n");

    // 链表根据关键字修改所有的节点
    temp = 555;
    key = 5;
    uolist_modify_all_by_key(head, &temp, &key, data_compare);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表根据关键字删除所有的节点
    key = 555;
    uolist_delete_all_by_key(head, &key, data_compare);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表的翻转
    uolist_reverse(head);

    // 链表的遍历
    printf("count = %d\n", get_count(head));
    uolist_traverse(head, data_print);
    printf("==================================================\n");

    // 链表的释放
    uolist_destroy(head);
    uolist_destroy(index);
    head_destroy(&head);
    head_destroy(&index);

    return 0;
}