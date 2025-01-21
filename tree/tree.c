// tree.c

#include "tree.h"

// intializing the "database" with a tree node which will have these default value as a root (its like constructor)
Tree root = {.n = {
                 .tag = (TagRoot | TagNode),
                 .north = (Node *)&root, // Node pointer as the root itself is a node
                 .west = 0,
                 .east = 0,
                 .path = "/"

             }

};

// This is just like a memset() function -> loop through the array and pad some values
void zero(int8 *str, int16 size)
{
    int8 *p;
    int16 m;

    // Intializing all the values of p pointer or basically the node to 0
    //  [0, 0, 0, 0] <- like this
    for (m = 0, p = str; m < size; p++, m++)
    {
        *p = 0;
    }
    return;
}

Node *createNode(Node *parent, int8 *path)
{
    Node *n;
    int16 size;

    errno = NoError;
    assert(parent); // Parent must not be null
    size = sizeof(struct s_node);
    n = (Node *)malloc((int)size);
    zero((int8 *)n, size);

    parent->west = n; // The left side of parent of one node will be pointing to another structure more specifically the next node
    n->tag = TagNode;
    n->north = parent;
    strncpy((char *)n->path, (char *)path, 255); // So, here the path from the parent will be copied to the upcoming node and 255 means the first 255 characters will be copied
    // lets suppose the path of parent is "/user" then the path of 'n' or the coming node will be "'/user'/{someName}"
    // This will create hierarchy like folder structure

    return n; //return this node's address :)
}

Leaf *findLastLinear(Node *parent){
    Leaf *l;

    errno = NoError;
    assert(parent);
    if (!parent->east)
    {
        reterr(NoError);
    }
    
    for ( l = parent->east; l->east ; l = l->east) //Moving the pointer one step to the right in this Structure -> Node ---- Leaf1 ----- Leaf2 ----- Leaf3 
    assert(l);

    return l;
    
}

Leaf *createLeaf(Node *parent, int8 *key, int8* value, int16 count){ 
//Structure -> Node ---- Leaf1 ----- Leaf2 ----- Leaf3 
    
    Leaf *l, *new;
    int16 size;

    assert(parent);

    l = findLast(parent);

    //Creating a new Leaf
    size = sizeof(struct s_leaf);
    new = (Leaf *)malloc(size);
    assert(new);

    if (!l)
    {
        //directly connected to parent
        parent->east = new;
    }else{
        //l is a leaf to which we have to connect
        l->east = new;
    }

    zero((int8 *)new, size);
    new->tag = TagLeaf;
    //Just if else condition like above 'east' one
    new->west = (!l) ? (Tree *)parent : (Tree *)l;

    //copying the key to new leaf
    strncpy((char *)new->key, (char *)key, 127);
    //allocating memory for the value or data of the new leaf
    new->value = (int8 *)malloc(count);
    //Padding value with 0 upto count
    zero(new->value, count);

    assert(new->value);
    
    strncpy((char *)new->value, (char *)value, count);

    new->size = count;

    return new;
    
}

int main()
{
    // printf("%p\n", (void *)&root); // Typecasting of root address with void pointer

    Node *n, *n2;
    Leaf *l1, *l2;
    int8* key, *value;
    int16 size;

    //Creating the root node
    n = createNode((Node * )&root, (int8 *)"/Users"); //Typecasting root to Node pointer as root primarily is a pointed by Tree type pointer
    assert(n);
    //Creating the consecutive node
    n2 = createNode(n, (int8 *)"Users/Login"); //Typecasting "/Users" to int8 * as in default is pointed by 'char' pointer
    assert(n2);

    printf("%p \n%p\n", n, n2);

//creating leaf

    key = (int8 *)"biratdb";
    value = (int8 *)"ThisismyfirstLeaf";
    size = (int16)strlen((char *)value);
    l1 = createLeaf(n2, key, value, size);
    assert(l1);

    printf("%s\n",l1->key);
    printf("%s\n",l1->value);


    key = (int8 *)"biratdb2";
    value = (int8 *)"This is my second leaf attached to first leaf";
    size = (int16)strlen((char*)value);
    l2 = createLeaf(n2,key, value, size);
    assert(l2);

    printf("%s\n", l2->key);
    printf("%s\n", l2->value);

    free(n2);
    free(n);

    return 0;
}


/*
Common Problem :
Segmentation Fault :
Occurs when we try to access memory that is not allocated to us
for e.g :
when we try to write :
    strncpy((char *)l->key, (char *)key, 127);
    instead of:
    strncpy((char *)new->key, (char *)key, 127);
    and we return new from createLeaf function
    and we try to access l1->key like :
    printf("%s\n",l1->key);
    since they key has been copied to l not in new there is no memory allocation for key of new (new leaf)
*/