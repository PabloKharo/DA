#pragma once
#include <fstream>
#include <cstring>

namespace TTree {
    
    const int STR_SIZE = 257;

    enum VColor{
        BLACK, 
        RED,
    };

    enum class VInsert{
        OK,
        EXIST,
        ERR_OUT_OF_MEMORY,
    };

    enum class VDelete{
        OK,
        NO_SUCH_WORD,
    };

    struct VSearch {
        enum VState{
            OK,
            NO_SUCH_WORD,
        };
        VState state;
        unsigned long long Key;
    };

    enum class VLoad {
        OK,
        ERR_OPEN,
        ERR_WRONG_VARIABLE,
        ERR_OUT_OF_MEMORY,
    };

    enum class VSave {
        OK,
        ERR_OPEN,
    };

    class VNode {
    public:
        VNode* Left;
        VNode* Right;
        VNode* Par;
        char Key[STR_SIZE];
        unsigned long long Value;
        VColor Color;

        VNode():Key(""){
            Left = nullptr;
            Right = nullptr;
            Par = nullptr;
            Value = 0;  
            Color = RED;
        }
    };

    class VTree {
    private:
        // tree.cpp
        void LeftRotate(VNode* node);
        void RightRotate(VNode* node);
        void InsertFixTree(VNode* node);
        void DeleteFixTree(VNode* node);
        void DeleteElem(VNode* node);
        void DeleteTree();
    public:
        VNode* root;
        VTree() {
            root = nullptr;
        };
        ~VTree(){
            this->DeleteTree();
        }
        // tree.cpp
        VInsert Insert(char key[], unsigned long long& val);
        VDelete Delete(char key[]);       
        VSearch Search(char key[]);

        // sltree.cpp
        VSave Save(char path[]);
        VLoad Load(char path[]);
    };
}