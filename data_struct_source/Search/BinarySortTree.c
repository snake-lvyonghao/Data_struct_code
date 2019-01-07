#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int  ElemType; //数据类型

typedef struct BiTNode{
    ElemType  data; //数据域
    struct BiTNode *lChild, *rChlid; //左右子树域
}BiTNode, *BiTree;

/**递归查找二叉排序树
 * 指针m指向二叉排序树的双亲，初始值为NULL
 * 若查找成功，则返回指针p指向该数据元素，并返回TRUE
 * 若查找不成功，则指针p指向查找路径上最后一个节点，并返回FALSE
 * @return
 */

int SearchBST(BiTree T,int key,BiTree m,BiTree *p){
    if(!T){             //查找失败
        *p = m;
        return 0;
    }
    else if (key == T->data){   //找到key
        *p = T;
        return 1;
    }
    else if(key < T->data){
        return SearchBST(T->lChild,key,T,p);
    }
    else {
        return SearchBST(T->rChlid,key,T,p);
    }
}


/**
 * 二叉排序树的插入
 * 当二叉树中不存在关键字等于key的数据元素时，插入key并返回True
 */
 int InsertBST(BiTree *T,int key){
     BiTree p,s;
     if(!SearchBST(*T,key,NULL,&p)){        //没找到key
         s = (BiTree)malloc(sizeof(BiTNode));
         s->data = key;
         s->lChild = s->rChlid = NULL;  //新结点初始化

         if(!p)
             *T = s; //插入s为新的根节点
         else if(key < p->data)
             p->lChild = s;     //插入s为左孩子
         else
             p->rChlid = s;     //插入s为右孩子
         return 1;
     } else
         return 0;
 }

 /**
  *从二叉排序树中删除结点p。并重接他的左/右子树
  * @return
  */
  int Delete(BiTree *p){
      BiTree q,s;

      if((*p)->rChlid == NULL){     //右子树为空，重接他的左子树
          q = *p;
          *p = (*p)->lChild;
          free(q);
      } else if((*p)->lChild == NULL){  //左子树为空，重接他的右子树
          q = *p;
          *p = (*p)->rChlid;
          free(q);
      }else{                            //左右子树都部位空
          q = *p;
          s = (*p)->lChild;
          while(s->rChlid){             //找到左子树的最右子树
              q = s;
              s = s->rChlid;
          }

          (*p)->data = s->data;         //s指向被删除结点的直接前驱（将被删除结点的值改为直接前驱结点的值）

          q->lChild = s->lChild;    //重接q的左子树

          free(s);
      }
  }

  /**
   * 二叉排序树的删除
   * 当二叉排序树中存在关键字等于key的数据元素时，删除该数据元素并返回True
   * @return
   */
   int DeleteBST(BiTree *T,int key){
       if(!*T)      //不存在关键字等于key的元素
           return 0;
       else{
           if(key == (*T)->data)
               return Delete(T);
           else if (key < (*T)->data)
               return DeleteBST(&(*T)->lChild,key);
           else
               return DeleteBST(&(*T)->rChlid,key);
       }
   }

//中序遍历查找二叉树
void InOrderBiTree(BiTree T)
{
    if (T == NULL)
        return ;
    InOrderBiTree(T->lChild);
    printf("%d ", T->data);
    InOrderBiTree(T->rChlid);
}

int main(){
    int i;
    int a[10] ={62,88,58,47,35,73,51,99,37,93};

    BiTree T = NULL;
    for (i = 0; i < 10; i++) {  // 通过插入操作来构建二叉排序树
        InsertBST(&T, a[i]);
    }

    printf("中序递归遍历二叉排序树：\n");
    InOrderBiTree(T);
    printf("\n\n");

    DeleteBST(&T, 93);
    printf("删除结点 93 后的结果为：\n");
    InOrderBiTree(T);
    printf("\n\n");

    printf("插入 91 后的结果为：\n");
    InsertBST(&T, 91);
    InOrderBiTree(T);
    printf("\n\n");
    return 0;
}
