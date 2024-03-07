/**
 * @file                uni_oneway_linkedlist.h
 * @brief               万能型单向链表
 * @details             需要提前写好如下自定义函数:
                            int node_destroy(void *data)
                            {
                            }

                            int data_print(void *data)
                            {
                            }

                            int data_compare(void *data, void *key)
                            {
                            }
 * @author              BHR
 * @version             v1.1
 * @date                2024-03-05
 * @copyright           MIT
 */

#ifndef __UNI_ONEWAY_LINKEDLIST_H__
#define __UNI_ONEWAY_LINKEDLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"


// 类型定义
typedef int(*op_t)(void *data);
typedef int(*cmp_t)(void *data, void *key);


/**
 * @brief 链表节点定义
 */
typedef struct _node_t
{
    void *data;                     // 数据域
    struct _node_t *next;           // 指针域
}node_t;



/**
 * @brief 链表头信息结构体定义
 */
typedef struct _uolist_t
{
    node_t *fstnode_p;              // 指向链表的第一个节点
    int size;                       // 存储数据的类型大小
    int count;                      // 节点的个数
    op_t my_destroy;                // 自定义销毁函数
}uolist_t;


/**
 * @brief           创建链表头信息结构体
 * @param           存储数据类型大小
 * @param           自定义销毁数据函数
 * @return          指向链表头信息结构体的指针
 */
uolist_t *uolist_create(int size, op_t my_destroy);


/**
 * @brief           链表头部插入
 * @param           头信息结构体的指针
 * @param           插入节点数据
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_prepend(uolist_t *uo, void *data);

/**
 * @brief           链表的遍历
 * @param           头信息结构体的指针
 * @param           自定义打印数据函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_traverse(uolist_t *uo, op_t my_print);


/**
 * @brief           链表销毁函数（不包括头信息结构体）
 * @param           头信息结构体的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_destroy(uolist_t *uo);

/**
 * @brief           头信息结构体销毁函数
 * @param           头信息结构体的指针的地址
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int head_destroy(uolist_t **p);


/**
 * @brief           获取链表中节点的个数
 * @param           头信息结构体的指针
 * @return          链表节点个数
 */
int get_count(uolist_t *p);


/**
 * @brief           链表尾部插入
 * @param           头信息结构体的指针
 * @param           数据的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_append(uolist_t *uo, void *data);


/**
 * @brief           链表根据索引插入
 * @param           头信息结构体的指针
 * @param           数据的指针
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_insert_by_index(uolist_t *uo, void *data, int index);



/**
 * @brief           链表根据索引删除
 * @param           头信息结构体的指针
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_delete_by_index(uolist_t *uo, int index);


/**
 * @brief           链表根据索引修改数据
 * @param           头信息结构体的指针
 * @param           修改数据
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_modify_by_index(uolist_t *uo, void *data, int index);


/**
 * @brief           链表根据索引检索数据
 * @param           头信息结构体的指针
 * @param           要检索的数据
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_retrieve_by_index(uolist_t *uo, void *data, int index);


/**
 * @brief           链表根据关键字删除
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_delete_by_key(uolist_t *uo, void *key, cmp_t op_cmp);


/**
 * @brief           链表根据关键字修改数据
 * @param           头信息结构体的指针
 * @param           修改的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_modify_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp);


/**
 * @brief           根据关键字寻找匹配索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数
 * @return          索引值    
 *      @arg  PAR_ERROR:参数错误
 *      @arg  MATCH_FAIL:无匹配索引
 */
int get_match_index(uolist_t *uo, void *key, cmp_t op_cmp);


/**
 * @brief           链表根据关键字获取数据
 * @param           头信息结构体的指针
 * @param           获取的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_retrieve_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp);


/**
 * @brief           链表根据关键字删除所有匹配的节点
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数 
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_delete_all_by_key(uolist_t *uo, void *key, cmp_t op_cmp);


/**
 * @brief           链表根据关键字修改所有匹配节点的数据
 * @param           头信息结构体的指针
 * @param           修改的数据
 * @param           关键字
 * @param           自定义比较函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_modify_all_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp);


/**
 * @brief           自定义索引销毁函数
 * @param           数据域
 * @return          0
 */
int index_destroy(void *data);


/**
 * @brief           链表根据关键字查找所有的索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数 
 * @return          存储索引链表
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  NULL     : 没有找到匹配索引
 */
uolist_t *uolist_find_all_index_by_key(uolist_t *uo, void *key, cmp_t op_cmp);


/**
 * @brief           自定义索引打印函数
 * @param           数据域
 * @return          0
 */
int index_print(void *data);


/**
 * @brief           链表的翻转
 * @param           头信息结构体的指针
 * @return          
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  0        : 正常
 */
int uolist_reverse(uolist_t *uo);




#endif /* __UNI_ONEWAY_LINKEDLIST_H__ */

