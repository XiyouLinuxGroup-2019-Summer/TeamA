typedef int TElemType;
typedef struct BiTNode{
    TElemType date;  //存放数据
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//前序遍历（先遍历根结点）递归实现
void PreOrderTraverse ( BiTree T )   //将根节点设为参数
{
    if ( T == NULL )
        return;
    printf("%d", T->date);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

//中序遍历（先遍历左结点，然后遍历根结点，最后遍历右结点）
void InOrderTraverse ( BiTree T )
{
    if ( T == NULL )
        return;
    InOrderTracerse(T->lchild);
    printf("%d", T->date);
    InOrderTracerse(T->rchild);
}

//后序遍历（先左结点，在右结点，最后是根结点）
void LastOrderTraverse ( BiTree T )
{
    if ( T == NULL )
        return;
    LastOrderTraverse(T->lchild);
    LastOrderTraverse(T->rchild);
    printf("%d", T->date);
}
//顺序遍历（从根节点开始，然后从左边开始，依次向右遍历）
