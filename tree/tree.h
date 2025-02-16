// tree.h
// Contains all the header files

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Error handling
#include <assert.h>
#include <errno.h>

#define TagRoot 1 /*00 01*/
#define TagNode 2 /*00 10*/
#define TagLeaf 4 /*01 00*/


#define NoError     0

/*Creating what a nullptr looks like*/
typedef void* Nullptr;

Nullptr null_ptr = 0; //nullptr is reserved keyword in C++ in std > 2x

#define findLast(x) findLastLinear(x)
#define reterr(x) \
    errno = (x); \
    return null_ptr

//When we define our macro in multiline we should end it with backslash '\' and must not have any space at the end

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef unsigned char Tag;

struct s_node
{
    struct s_node *north; // this is a root of the tree which will point itself when intialized, north means upward link
    struct s_node *west; // west means left path or downward path
    struct s_leaf *east; // east means leaves
    int8 path[256];      // this contians all the path in the database
    Tag tag;
};

typedef struct s_node Node;

struct s_leaf
{
    union u_tree *west;
    struct s_leaf *east;
    int8 key[128];
    int8 *value; // this value will contain all the information of the leaf
    int16 size;
    Tag tag;
};

typedef struct s_leaf Leaf;

// Union's members share same memory space
// so i can have only one member at one time
union u_tree
{
    Node n;
    Leaf l;
};

typedef union u_tree Tree;


















// Types :
// Tress -> {Node,
//           Leaf}

/*
Structure of this datbase :

/ {this is a root node}
    /Users/
    Leaves -> /Users/Birat {Linked list from Users to Birat}
              /Users/Someone

          /Users/Login/



*/