#include <string>
#include <new>

#include "tree.hpp"
using TUll = unsigned long long;

namespace TTree {

    void VTree::RightRotate(VNode* x){
        if(x->Left != nullptr){
            VNode* y = x->Left;
            x->Left = y->Right;
            if(y->Right != nullptr){
                y->Right->Par = x;
            }
            y->Par = x->Par;
            if(x->Par == nullptr){
                this->root = y;
            }else if (x == x->Par->Right){
                x->Par->Right = y;
            }else{
                x->Par->Left = y;
            }
            y->Right = x;
            x->Par = y;
        }
    }
    
    void VTree::LeftRotate(VNode* x){
        if(x->Right != nullptr){
            VNode* y = x->Right;
            x->Right = y->Left;
            if(y->Left != nullptr){
                y->Left->Par = x;
            }
            y->Par = x->Par;
            if(x->Par == nullptr){
                this->root = y;
            }else if (x == x->Par->Left){
                x->Par->Left = y;
            }else{
                x->Par->Right = y;
            }
            y->Left = x;
            x->Par = y;
        }
    }

    void VTree::InsertFixTree(VNode* node){
        using TTree::VColor;
        while(node->Par != nullptr && node->Par->Par != nullptr && node->Par->Color == RED){
            if(node->Par == node->Par->Par->Right){
                VNode* uncle = node->Par->Par->Left;
                if (uncle == nullptr || uncle->Color == BLACK) {
                    if (node == node->Par->Left) {
                        node = node->Par;
                        (*this).RightRotate(node);
                    }
                    node->Par->Color = BLACK;
                    node->Par->Par->Color = RED;
                    (*this).LeftRotate(node->Par->Par);       
                }else{
                    node->Par->Color = BLACK;
                    node->Par->Par->Color = RED;
                    uncle->Color = BLACK;
                    node = node->Par->Par;
                }
            }else{
                VNode* uncle = node->Par->Par->Right;
                if (uncle == nullptr || uncle->Color == BLACK) {
                    if (node == node->Par->Right) {
                        node = node->Par;
                        (*this).LeftRotate(node);
                    }
                    node->Par->Color = BLACK;
                    node->Par->Par->Color = RED;
                    (*this).RightRotate(node->Par->Par);
                }else{
                    node->Par->Color = BLACK;
                    node->Par->Par->Color = RED;
                    uncle->Color = BLACK;
                    node = node->Par->Par;
                }
            }
        }

        this->root->Color = BLACK;
    }

    VInsert VTree::Insert(char key[], TUll& value) {
        VNode* parent = nullptr;
        VNode* node = this->root;

        int comp = 0;
        while (node != nullptr) {
            comp = strcmp(key, node->Key);
            parent = node;
            if (comp == 0) {
                return VInsert::EXIST;
            }else if (comp < 0) {
                node = node->Right;
            }else {
                node = node->Left;
            }
        }

        try{
            node = new VNode();
        }catch(std::bad_alloc& er){
            return VInsert::ERR_OUT_OF_MEMORY;
        }

        strcpy(node->Key, key);
        node->Value = value;
        node->Par = parent;

        if (parent != nullptr) {
            if (comp < 0) {
                parent->Right = node;
            }else {
                parent->Left = node;
            }
        }else {
            this->root = node;
        }

        (*this).InsertFixTree(node);

        return VInsert::OK;
    }

    void VTree::DeleteFixTree(VNode* node) {
        while (node->Par != nullptr && node->Color == BLACK) {
            if (node == node->Par->Left) {
                VNode* bro = node->Par->Right;
                if (bro->Color == RED) {
                    bro->Color = BLACK;
                    node->Par->Color = RED;
                    LeftRotate(node->Par);
                    bro = node->Par->Right;
                }
                if ((bro->Left == nullptr && bro->Right == nullptr) 
                        || (bro->Left != nullptr && bro->Right != nullptr 
                            && bro->Left->Color == BLACK && bro->Right->Color == BLACK)) {
                    bro->Color = RED;
                    node = node->Par;
                }
                else {
                    if (bro->Right == nullptr || bro->Right->Color == BLACK) {
                        bro->Left->Color = BLACK;
                        bro->Color = RED;
                        RightRotate(bro);
                        bro = node->Par->Right;
                    }
                    bro->Color = node->Par->Color;
                    node->Par->Color = BLACK;
                    bro->Right->Color = BLACK;
                    LeftRotate(node->Par);
                    node = root;
                }
            }
            else {
                VNode* bro = node->Par->Left;
                if (bro->Color == RED) {
                    bro->Color = BLACK;
                    node->Par->Color = RED;
                    RightRotate(node->Par);
                    bro = node->Par->Left;
                }
                if ((bro->Right == nullptr && bro->Left == nullptr) 
                        || (bro->Right != nullptr && bro->Left != nullptr 
                            && bro->Right->Color == BLACK && bro->Left->Color == BLACK)) {
                    bro->Color = RED;
                    node = node->Par;
                }
                else {
                    if (bro->Left == nullptr || bro->Left->Color == BLACK) {
                        bro->Right->Color = BLACK;
                        bro->Color = RED;
                        LeftRotate(bro);
                        bro = node->Par->Left;
                    }
                    bro->Color = node->Par->Color;
                    node->Par->Color = BLACK;
                    bro->Left->Color = BLACK;
                    RightRotate(node->Par);
                    node = root;
                }
            }
        }

        node->Color = BLACK;
    }

    VNode* NearestValueNode(VNode* node){
        VNode* res = nullptr;
        if (node->Right != nullptr) {
            res = node->Right;
            while (res->Left != nullptr) {
                res = res->Left;
            }
        }
        return res;
    }

    void VTree::DeleteElem(VNode* node) {
        VNode* y;

        if (node->Right == nullptr || node->Left == nullptr) {
            y = node;
        }
        else {
            y = NearestValueNode(node);
            strcpy(node->Key, y->Key);
            node->Value = std::move(y->Value);
        }

        if (y->Color == BLACK) {
            (*this).DeleteFixTree(y);
        }

        VNode* x;

        if (y->Right != nullptr) {
            x = y->Right;
        }
        else {
            x = y->Left;
        }

        if (x != nullptr){
            x->Par = y->Par;
        }
        if (y->Par != nullptr){
            if (y == y->Par->Right){
                y->Par->Right = x;
            }
            else{
                y->Par->Left = x;
            }
        }
        else{
            root = x;
        }

        delete y;
    }

    VDelete VTree::Delete(char key[]){
        VNode* node = this->root;
        while (node != nullptr) {
            int comp = strcmp(key, node->Key);
            if (comp == 0) {
                (*this).DeleteElem(node);
                return VDelete::OK;
            }else if (comp < 0) {
                node = node->Right;
            }else {
                node = node->Left;
            }
        }

        return VDelete::NO_SUCH_WORD;
    }


    VSearch VTree::Search(char key[]){
        VNode* node = this->root;
        while (node != nullptr) {
            int comp = strcmp(key, node->Key);
            if (comp == 0) {
                return { VSearch::OK, node->Value };
            }else if (comp < 0) {
                node = node->Right;
            }else {
                node = node->Left;
            }
        }
        return { VSearch::NO_SUCH_WORD, 0 };
    }


    void DeleteNode(VNode* node) {
        if (node->Right != nullptr)
            DeleteNode(node->Right);
        if (node->Left != nullptr) {
            DeleteNode(node->Left);
        }
        delete node;
    }
    
    void VTree::DeleteTree(){
        if(this->root != nullptr){
            DeleteNode(this->root);
        }
        this->root = nullptr;
    }
}