#include<stdio.h>
#include<stdlib.h>

struct BSnode
{
    int Value;
    BSnode * left ;
    BSnode * right;
}STONE={0,0,0};

int Myinsert=0;
BSnode * NewConect;
//AVL
BSnode * LL(BSnode * SubRoot)
{
    BSnode * NewRoot = SubRoot->right;
    SubRoot->right=NewRoot->left;
    NewRoot->left=SubRoot;
    return NewRoot;
}
BSnode * RR(BSnode * SubRoot)
{
    BSnode * NewRoot = SubRoot->left;
    SubRoot->left=NewRoot->right;
    NewRoot->right = SubRoot;
    return NewRoot;
}
BSnode * LR(BSnode * SubRoot)
{
    SubRoot->left = LL(SubRoot->left);
    SubRoot = RR(SubRoot);
    return SubRoot;
}
BSnode * RL(BSnode * SubRoot)
{
    SubRoot->right = RR(SubRoot->right);
    SubRoot = LL(SubRoot);
    return SubRoot;
}
int WhichType(BSnode * currentnode,int NewNodeValue)
{
    if (currentnode->Value > NewNodeValue )
    {
        if (currentnode->left->Value > NewNodeValue )
            return 1;  //RR
        else
            return 2;  //LR
    }
    else
    {
        if (currentnode->right->Value > NewNodeValue )
            return 3;  //RL
        else
            return 4;  //LL
    }
}

BSnode * AVL(BSnode * currentnode)
{
    int choice = WhichType(currentnode ,Myinsert );
    if (choice == 1)
        return RR(currentnode);
    else if (choice == 2)
        return LR(currentnode);
    else if (choice == 3)
        return RL(currentnode);
    else if (choice == 4)
        return LL(currentnode);
}
//
void preorder(BSnode * currentnode)
{
    printf("%d ",currentnode->Value );
    if (currentnode->left != NULL)
        preorder( currentnode->left);
    if (currentnode->right != NULL)
        preorder( currentnode->right);
}
void INorder(BSnode * currentnode)
{
    if (currentnode->left != NULL)
        INorder( currentnode->left);

    printf("%d ",currentnode->Value );

    if (currentnode->right != NULL)
        INorder( currentnode->right);
}
int THeight(BSnode * currentnode,BSnode * PP)
{
    int HL=0,HR=0;
    if (currentnode->left != NULL)
        HL= THeight( currentnode->left,currentnode)+1;
    if (currentnode->right != NULL)
        HR= THeight( currentnode->right,currentnode)+1;

    if ( abs(HR - HL) >=2)
    {
        printf("AVL %d\n",currentnode->Value);
        NewConect=AVL(currentnode);
        if (NewConect->Value > PP->Value )
        {
            if ( PP == &STONE )
            {
                PP->right=NewConect;
                PP->left=NewConect;
            }
            PP->right=NewConect;
        }
        else
        {
            if ( PP == &STONE )
            {
                PP->right=NewConect;
                PP->left=NewConect;
            }
            PP->left=NewConect;
        }
        return 0;
    }

    if (HL > HR)
        return HL;
    else
        return HR;
}
void create_tree()
{
    int temp;
    scanf("%d",&temp);
    Myinsert=temp ;

    STONE.right=new BSnode;
    STONE.left=STONE.right;
    STONE.right->Value=temp;
    STONE.right->right=NULL;
    STONE.right->left=NULL;

    while (1)
    {
        BSnode *Nptr = STONE.right;
        scanf("%d",&temp);

        if (temp == -1)
        {
            break;
        }
        Myinsert=temp ;

        while (1)
        {
            if (Nptr->Value <= temp)
            {
                if (Nptr->right == NULL)
                {
                    Nptr->right=new BSnode;
                    Nptr->right->Value=temp;
                    Nptr->right->right=NULL;
                    Nptr->right->left=NULL;
                    break;
                }
                else
                {
                    Nptr = Nptr->right;
                }
            }
            else if (Nptr->Value > temp)
            {
                if (Nptr->left == NULL)
                {
                    Nptr->left=new BSnode;
                    Nptr->left->Value=temp;
                    Nptr->left->right=NULL;
                    Nptr->left->left=NULL;
                    break;
                }
                else
                {
                    Nptr = Nptr->left;
                }
            }
        }
        ////////////AVL Tree
        THeight(STONE.right,&STONE);
        ////////////
    }
    return ;
}
int main()
{
    printf("Please enter Data\n");
    create_tree();

    printf("PreOrder travel\n");
    preorder( STONE.right );
    printf("\nInOrder travel\n");
    INorder( STONE.right );
    return 0 ;
}
