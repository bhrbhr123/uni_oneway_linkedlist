/**
 * @file                uni_oneway_linkedlist.c
 * @brief               万能型单向链表
 * @author              BHR
 * @version             v1.1
 * @date                2024-03-05
 * @copyright           MIT
 */

#include "uni_oneway_linkedlist.h"

/**
 * @brief           创建节点空间
 * @param           链表头信息结构体指针
 * @return          节点指针
 */
static node_t *__node_calloc(uolist_t *uo)
{
    /* 变量定义 */
    node_t *p = NULL;

    /* 参数检查 */
    if (NULL == uo)
    {
    #ifdef DEBUG
        printf("__node_calloc: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;  
    } /* end of if (NULL == uo) */

    /* 创建节点空间 */ 
    p = (node_t *)calloc(1, sizeof(node_t));
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("__node_calloc: p calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR1;  
    } /* end of if (NULL == p) */

    /* 创建节点中数据空间 */
    p->data = (void *)calloc(1, uo->size);
    if (NULL == p->data)
    {
    #ifdef DEBUG
        printf("__node_calloc: data calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR2;          
    } /* end of if (NULL == p->data) */

    return p;

ERR0:
    return (void *)PAR_ERROR;
ERR2:
    free(p);
    p = NULL;
ERR1:
    return (void *)FUN_ERROR;
}



/**
 * @brief           创建链表头信息结构体
 * @param           存储数据类型大小
 * @param           自定义销毁数据函数
 * @return          指向链表头信息结构体的指针
 */
uolist_t *uolist_create(int size, op_t my_destroy)
{
    /* 变量定义 */
    uolist_t *uo = NULL;

    /* 参数检查 */
    if (size <= 0)
    {
    #ifdef DEBUG
        printf("uolist_create: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;
    } /* end of if (size <= 0 || NULL == my_destroy) */


    /* 申请头信息结构体空间 */
    uo = (uolist_t *)calloc(1, sizeof(uolist_t));
    if (NULL == uo)
    {
    #ifdef DEBUG
        printf("uolist_create: calloc error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR1;       
    } /* end of if (NULL == uo) */

    /* 信息输入 */
    uo->count = 0;
    uo->size = size;
    uo->fstnode_p = NULL;
    uo->my_destroy = my_destroy;


    return uo;

ERR0:
    return (void *)PAR_ERROR;
ERR1:
    return (void *)FUN_ERROR;
}


/**
 * @brief           链表头部插入
 * @param           头信息结构体的指针
 * @param           插入节点数据
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_prepend(uolist_t *uo, void *data)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;

    /* 参数检查 */
    if (NULL == uo || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_prepend: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == data) */

    /* 1.创建一个新的节点 */
    temp1 = __node_calloc(uo);

    /* 2.节点数据输入 */
    temp1->next = NULL;
    memcpy(temp1->data, data, uo->size);


    /* 3.链表节点头部插入 */
    if (NULL == uo->fstnode_p)
    {
        uo->fstnode_p = temp1;
    }
    else 
    {
        temp2 = uo->fstnode_p;
        uo->fstnode_p = temp1;
        temp1->next = temp2;
    }

    /* 链表头信息更新 */
    uo->count++;

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;
}

/**
 * @brief           链表的遍历
 * @param           头信息结构体的指针
 * @param           自定义打印数据函数
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_traverse(uolist_t *uo, op_t my_print)
{
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == uo || NULL == my_print)
    {
    #ifdef DEBUG
        printf("uolist_traverse: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == my_print) */



    /* 链表的遍历 */
    temp = uo->fstnode_p;
    while (temp != NULL)
    {
        my_print(temp->data);
        temp = temp->next;
    } /* end of while (temp != NULL) */


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;    
}


/**
 * @brief           链表销毁函数（不包括头信息结构体）
 * @param           头信息结构体的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_destroy(uolist_t *uo)
{
    node_t *temp = NULL;
    node_t *save = NULL;

    /* 参数检查 */
    if (NULL == uo)
    {
    #ifdef DEBUG
        printf("uolist_destroy: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo) */    

    temp = uo->fstnode_p;

    /* 依次释放节点空间 */
    while (NULL != temp)
    {
        /* 1.保存下个节点的指针 */
        save = temp->next;

        /* 2.释放数据空间 */
        uo->my_destroy(temp->data);
        temp->data = NULL;

        /* 3.释放节点空间 */
        free(temp);
        temp = NULL;

        /* 4.指向下一个节点 */
        temp = save;
    } /* end of while (NULL != temp) */

    /* 头信息刷新 */
    uo->fstnode_p = NULL;
    uo->count = 0;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;     
}


/**
 * @brief           头信息结构体销毁函数
 * @param           头信息结构体的指针的地址
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int head_destroy(uolist_t **p)
{
    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("head_destroy: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == p) */  

    /* 销毁结构体空间 */
    free(*p);
    *p = NULL;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;  
}

/**
 * @brief           获取链表中节点的个数
 * @param           头信息结构体的指针
 * @return          链表节点个数
 */
int get_count(uolist_t *p)
{

    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("get_count: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == p) */  

    return p->count;

ERR0:
    return PAR_ERROR;
}

/**
 * @brief           链表尾部插入
 * @param           头信息结构体的指针
 * @param           数据的指针
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_append(uolist_t *uo, void *data)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;

    /* 参数检查 */
    if (NULL == uo || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_append: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == data) */

    /* 1.创建一个新的节点 */
    temp1 = __node_calloc(uo);

    /* 2.节点数据输入 */
    temp1->next = NULL;
    memcpy(temp1->data, data, uo->size);

    /* 3.数据尾部插入 */
    if (NULL == uo->fstnode_p)
    {
        uo->fstnode_p = temp1;
    }
    else 
    {
        temp2 = uo->fstnode_p;
        while (temp2->next != NULL)
        {
            temp2 = temp2->next;
        } /* end of while (temp2->next != NULL) */

        temp2->next = temp1;
    }

    /* 4.刷新信息 */
    uo->count++;

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;  

}

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
int uolist_insert_by_index(uolist_t *uo, void *data, int index)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;
    node_t *save = NULL;
    int i = 0;


    /* 参数检查 */
    if (NULL == uo || NULL == data || index < 0)
    {
    #ifdef DEBUG
        printf("uolist_insert_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == data || index < 0) */

    /* 1.创建一个新的节点 */
    temp1 = __node_calloc(uo);

    /* 2.节点数据输入 */
    temp1->next = NULL;
    memcpy(temp1->data, data, uo->size);

    /* 3.判断索引 */
    temp2 = uo->fstnode_p;
    if (index < uo->count && index > 0)
    {
        // 寻找索引位置
        for (i = 0; i < index - 1; i++)
        {
            temp2 = temp2->next;
        } /* end of for (i = 0; i < index; i++) */

        // 保存索引位置的链表
        save = temp2->next;

        // 在索引位置插入新节点
        temp2->next = temp1;

        // 链接保存链表
        temp1->next = save;
    }
    else if (index == 0)
    {
        // 头部插入
        uo->fstnode_p = temp1;
        temp1->next = temp2;
    }
    else 
    {
        // 尾部插入
        while (temp2->next != NULL)
        {
            temp2 = temp2->next;
        } /* end of while (temp2->next != NULL) */

        temp2->next = temp1;
    }

    /* 刷新管理信息 */
    uo->count++;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 

}



/**
 * @brief           链表根据索引删除
 * @param           头信息结构体的指针
 * @param           索引值
 * @return          
 *      @arg  0:正常
 *      @arg  PAR_ERROR:参数错误
 *      @arg  FUN_ERROR:函数错误
 */
int uolist_delete_by_index(uolist_t *uo, int index)
{
    node_t *temp1 = NULL;
    node_t *temp2 = NULL;
    node_t *des = NULL;
    int i = 0;


    /* 参数检查 */
    if (NULL == uo || index < 0 || index >= uo->count)
    {
    #ifdef DEBUG
        printf("uolist_delete_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || index < 0 || index >= uo->count) */

    /* 寻找索引的前一个 */
    if (index == 0)
    {
        // 保存节点
        des = uo->fstnode_p;
        temp2 = uo->fstnode_p->next;

        // 连接节点
        uo->fstnode_p = temp2;

        // 释放节点
        uo->my_destroy(des->data);
        free(des);
        des = NULL;
    }
    else 
    {
        // 寻找并保存节点
        temp1 = uo->fstnode_p;
        for (i = 0; i < index - 1; i++)
        {
            temp1 = temp1->next;
        } /* end of for (i = 0; i < index - 1; i++) */

        temp2 = temp1->next->next;
        des = temp1->next;

        // 连接节点
        temp1->next = temp2;

        // 释放节点
        uo->my_destroy(des->data);
        free(des);
        des = NULL;
    }


    /* 刷新信息 */
    uo->count--;

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 

}


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
int uolist_modify_by_index(uolist_t *uo, void *data, int index)
{
    int i = 0;
    node_t *temp = NULL;


    /* 参数检查 */
    if (NULL == uo || index < 0 || index >= uo->count || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_modify_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || index < 0 || index >= uo->count || NULL == data) */

    /* 寻找索引位置 */
    temp = uo->fstnode_p;
    for (i = 0; i < index; i++)
    {
        temp = temp->next;
    } /* end of for (i = 0; i < index; i++) */

    /* 修改数据 */
    memcpy(temp->data, data, uo->size);

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;     
}


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
int uolist_retrieve_by_index(uolist_t *uo, void *data, int index)
{
    int i = 0;
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == uo || index < 0 || index >= uo->count || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_retrieve_by_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || index < 0 || index >= uo->count || NULL == data) */


    /* 寻找索引位置 */
    temp = uo->fstnode_p;
    for (i = 0; i < index; i++)
    {
        temp = temp->next;
    } /* end of for (i = 0; i < index; i++) */

    /* 修改数据 */
    memcpy(data, temp->data, uo->size);


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;      
}


/**
 * @brief           根据关键字寻找匹配索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数
 * @return          索引值    
 *      @arg  PAR_ERROR:参数错误
 *      @arg  MATCH_FAIL:无匹配索引
 */
int get_match_index(uolist_t *uo, void *key, cmp_t op_cmp)
{
    int index = 0;
    node_t *temp = NULL;


    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("get_match_index: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp) */


    /* 判断是否为空链表 */
    if (NULL == uo->fstnode_p)
    {
        goto ERR1;
    } /* end of if (NULL == uo->fstnode_p) */

    /* 寻找匹配索引 */
    index = 0;
    temp = uo->fstnode_p;
    while (1)
    {
        if (MATCH_SUCCESS == op_cmp(temp->data, key))
        {
            return index;
        } /* end of if (MATCH_SUCCESS == op_cmp(temp->data, key)) */

        temp = temp->next;
        if (NULL == temp)
        {
            goto ERR1;
        } /* end of if (NULL == temp) */
        index++;
    } /* end of while (1) */


ERR0:
    return PAR_ERROR;
ERR1:
    return MATCH_FAIL; 
}


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
int uolist_delete_by_key(uolist_t *uo, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("uolist_delete_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp) */


    /* 获取匹配索引 */
    index = get_match_index(uo, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


    /* 根据索引删除节点 */
    uolist_delete_by_index(uo, index);


    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;        
}

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
int uolist_modify_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_modify_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data) */


    /* 获取匹配索引 */
    index = get_match_index(uo, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


    /* 根据索引修改数据 */
    uolist_modify_by_index(uo, data, index);


    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}


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
int uolist_retrieve_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_retrieve_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data) */


    /* 获取匹配索引 */
    index = get_match_index(uo, key, op_cmp);
    if (PAR_ERROR == index || MATCH_FAIL == index)
    {
        goto ERR1;
    } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */

    /* 根据索引获取数据 */
    uolist_retrieve_by_index(uo, data, index);

    return 0;


ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}



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
int uolist_delete_all_by_key(uolist_t *uo, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("uolist_delete_all_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp) */

    while (1)
    {
        /* 获取匹配索引 */
        index = get_match_index(uo, key, op_cmp);
        if (PAR_ERROR == index || MATCH_FAIL == index)
        {
            goto ERR1;
        } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


        /* 根据索引删除节点 */
        uolist_delete_by_index(uo, index);

    } /* end of while (1) */

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;  

}


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
int uolist_modify_all_by_key(uolist_t *uo, void *data, void *key, cmp_t op_cmp)
{
    int index = 0;

    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data)
    {
    #ifdef DEBUG
        printf("uolist_modify_all_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp || NULL == data) */

    while (1)
    {
        /* 获取匹配索引 */
        index = get_match_index(uo, key, op_cmp);
        if (PAR_ERROR == index || MATCH_FAIL == index)
        {
            goto ERR1;
        } /* end of if (PAR_ERROR == index || MATCH_FAIL == index) */


        /* 根据索引修改数据 */
        uolist_modify_by_index(uo, data, index);

    } /* end of while (1) */

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR; 
}


/**
 * @brief           自定义索引销毁函数
 * @param           数据域
 * @return          0
 */
int index_destroy(void *data)
{
    free(data);
    data = NULL;
    return 0;
}


/**
 * @brief           自定义索引打印函数
 * @param           数据域
 * @return          0
 */
int index_print(void *data)
{
    printf("index = %d\n", *(int *)data);
    return 0;
}


/**
 * @brief           链表根据关键字查找所有的索引
 * @param           头信息结构体的指针
 * @param           关键字
 * @param           自定义比较函数 
 * @return          存储索引链表
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  NULL     : 没有找到匹配索引
 */
uolist_t *uolist_find_all_index_by_key(uolist_t *uo, void *key, cmp_t op_cmp)
{
    uolist_t *index_head = NULL;
    node_t *temp = NULL;
    int index = 0;


    /* 参数检查 */
    if (NULL == uo || NULL == key || NULL == op_cmp)
    {
    #ifdef DEBUG
        printf("uolist_find_all_index_by_key: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo || NULL == key || NULL == op_cmp) */


    /* 判断链表是否存在 */
    if (NULL == uo->fstnode_p)
    {
        goto ERR1;
    } /* end of if (NULL == uo->fstnode_p) */


    /* 创建存储索引的链表头信息结构体 */
    index_head = uolist_create(sizeof(int), index_destroy);


    /* 查找索引并插入链表 */
    temp = uo->fstnode_p;
    for (index = 0; NULL != temp; index++, temp = temp->next)
    {
        if (MATCH_SUCCESS == op_cmp(temp->data, key))
        {
            uolist_append(index_head, &index);
        }
    } /* end of for (index = 0; NULL != temp; index++, temp = temp->next) */


    /* 判断是否为空链表 */
    if (0 == get_count(index_head))
    {
        head_destroy(&index_head);
    } /* end of if (0 == get_count(index_head)) */


    return index_head;


ERR0:
    return (void *)PAR_ERROR;
ERR1:
    return NULL;
}


/**
 * @brief           链表的翻转
 * @param           头信息结构体的指针
 * @return          
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  0        : 正常
 */
int uolist_reverse(uolist_t *uo)
{
    node_t *p = NULL;
    node_t *save = NULL;
    node_t *temp = NULL;

    /* 参数检查 */
    if (NULL == uo)
    {
    #ifdef DEBUG
        printf("uolist_reverse: Parameter error\n");
    #elif defined FILE_DEBUG
        
    #endif
        goto ERR0;        
    } /* end of if (NULL == uo) */

    /* 链表的翻转 */
    for (p = uo->fstnode_p, uo->fstnode_p = NULL, uo->count = 0; NULL != p; p = save)
    {
        /* 保存下一个节点 */
        save = p->next;

        /* 链表头插 */
        p->next = NULL;
        if (NULL == uo->fstnode_p)
        {
            uo->fstnode_p = p;
        }
        else 
        {
            temp = uo->fstnode_p;
            uo->fstnode_p = p;
            p->next = temp;
        }

        /* 链表头信息更新 */
        uo->count++;
    } /* end of for (p = uo->fstnode_p, uo->fstnode_p = NULL, uo->count = 0; NULL != p; p = save) */

    return 0;


ERR0:
    return PAR_ERROR;


}



  





