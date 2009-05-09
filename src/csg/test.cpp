#include "test.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include <csg/node.h>
#include <csg/normalise.h>

#include <node/shape.h>

#include <glutm/shape.h>
#include <misc/refcount.h>

#define EAT_WHITESPACE  while (*str==' ' || *str=='\n' || *str=='\t') str++;

ReferenceCountPtr<GltShape> makeTree(const char *&str)
{
    EAT_WHITESPACE

    if (*str=='(')
    {
        CsgNode *root = new CsgNode();

        str++;
        root->left() = makeTree(str);

        EAT_WHITESPACE

        switch (*str)
        {
        case '+': root->type() = NODE_UNION;        break;
        case '.': root->type() = NODE_INTERSECTION; break;
        case '-': root->type() = NODE_DIFFERENCE;   break;
        default:
            delete root;
            return NULL;
        }

        str++;
        root->right() = makeTree(str);

        EAT_WHITESPACE

        if (!root->left().get() || !root->right().get() || *str!=')')
        {
            delete root;
            return NULL;
        }

        str++;
        EAT_WHITESPACE

        return root;
    }

    if (*str>='A' && *str<='Z')
    {
        GltShape *shape = new GlutSphere();
        shape->name() += *str;
        str++;
        EAT_WHITESPACE
        return shape;
    }

    return NULL;
}

void testNormalisation(const string &input,const string &match)
{
    const char *str = input.c_str();
    ReferenceCountPtr<GltShape> root = makeTree(str);

    if (root.get() && *str=='\0')
    {
        CsgSumOfProducts products = normalise(root);
        products.optimise();
        string output = products.toString();
        cout << setw(20) << input << "   ---->   " << setw(20) << output << "   ";
        cout << (output==match ? "OK" : "FAILURE") << endl;
    }
    else
    {
        cout << "Error at: " << str << endl;
    }
}

void testNormalisation()
{
    testNormalisation( "A"                ,"(A)"             );

    testNormalisation( "(A+B)"            ,"(A) + (B)"       );
    testNormalisation( "(A-B)"            ,"(A-B)"           );
    testNormalisation( "(A.B)"            ,"(A.B)"           );

    testNormalisation( "(A.(B+C))"        ,"(A.B) + (A.C)"   );
    testNormalisation( "(A.(B.C))"        ,"(A.B.C)"         );
    testNormalisation( "(A.(B-C))"        ,"(A.B-C)"         );
    testNormalisation( "(A-(B+C))"        ,"(A-B-C)"         );
    testNormalisation( "(A-(B.C))"        ,"(A-B) + (A-C)"   );
    testNormalisation( "(A-(B-C))"        ,"(A-B) + (A.C)"   );
    testNormalisation( "(A+(B+C))"        ,"(A) + (B) + (C)" );
    testNormalisation( "(A+(B.C))"        ,"(A) + (B.C)"     );
    testNormalisation( "(A+(B-C))"        ,"(A) + (B-C)"     );

    testNormalisation( "((A+B).C)"        ,"(A.C) + (B.C)"   );
    testNormalisation( "((A.B).C)"        ,"(A.B.C)"         );
    testNormalisation( "((A-B).C)"        ,"(A-B.C)"         );
    testNormalisation( "((A+B)-C)"        ,"(A-C) + (B-C)"   );
    testNormalisation( "((A.B)-C)"        ,"(A.B-C)"         );
    testNormalisation( "((A-B)-C)"        ,"(A-B-C)"         );
    testNormalisation( "((A+B)+C)"        ,"(A) + (B) + (C)" );
    testNormalisation( "((A.B)+C)"        ,"(A.B) + (C)"     );
    testNormalisation( "((A-B)+C)"        ,"(A-B) + (C)"     );

    testNormalisation( "(A-A)"            , ""               );
    testNormalisation( "((A+B)-A)"        , "(B-A)"          );
    testNormalisation( "((A.B)-A)"        , ""               );
    testNormalisation( "((A-B)-A)"        , ""               );


    testNormalisation( "((A+B)-(A+B))"    , ""               );
    testNormalisation( "((A.B)-(A.B))"    , ""               );
    testNormalisation( "((A-B)-(A-B))"    , ""               );

    testNormalisation( "((A-B)+B)"        , "(A) + (B)"      );
    testNormalisation( "((A.B)+B)"        , "(B)"            );

    testNormalisation( "(A+(A-B))"        , "(A)"            );
    testNormalisation( "(A+(A.B))"        , "(A)"            );

//  testNormalisation( "((A.B)+(A-B))"    , "(A)"            );
}
