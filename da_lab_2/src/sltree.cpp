#include <fstream>

#include "tree.hpp"
using TUll = unsigned long long;

// key ull color left right \n
// В конце количество листьев

namespace TTree{

    void PrintNode(std::ofstream& out, VNode* node){
        out << node->Key << "  " << node->Value 
                        << "  " << node->Color << " ";
        if(node->Left != nullptr){
            out << 1 << " ";
        }else{
            out << 0 << " ";
        }

        if(node->Right != nullptr){
            out << 1;
        }else{
            out << 0;
        }

        out << '\n';
    }

    void PrintNodes(std::ofstream& out, VNode* node, int& count){ 
        PrintNode(out, node);
        ++count;
        if(node->Left != nullptr){
            PrintNodes(out, node->Left, count);
        }

        if(node->Right != nullptr){
            PrintNodes(out, node->Right, count);
        }

    }

    VSave VTree::Save(char path[]){
        std::ofstream file(path, std::ios::out);
        if(file.is_open()){
            VNode* root = this->root;
            int count = 0;
            if(root != nullptr){
                PrintNodes(file, root, count);
            }
            else {
                file << "NULL" << '\n';
            }
            file << count;
        }else{
            return VSave::ERR_OPEN;
        }
        return VSave::OK;
    }




    enum class VScanNode{
        OK,
        ERR_WRONG_VARIABLE,
        ERR_OUT_OF_MEMORY,
    };

    bool IsLowerCase(char str[]){
        for(size_t i = 0; str[i] != '\0'; ++i){
            if(!(tolower(str[i]) == str[i])){
                return false;
            }
        }
        return true;
    }

    void ScanNodes(std::ifstream& in, VNode** node, VScanNode& state, int& count){
        char key[STR_SIZE] = "";
        TUll value;
        int color;
        int left;
        int right;

        if(!(in >> key >> value >> color >> left >> right)){
            if (strcmp(key, "NULL") == 0 && count == 0){
                return;
            }
            state = VScanNode::ERR_WRONG_VARIABLE;
        }
        
        if(color < 0 || color > 1){
            state = VScanNode::ERR_WRONG_VARIABLE;
        }
        if(!IsLowerCase(key)){
            state = VScanNode::ERR_WRONG_VARIABLE;
        }
        count++;

        try{
            *node = new VNode();
        }catch(std::bad_alloc& err){
            state = VScanNode::ERR_OUT_OF_MEMORY;
        }

        strcpy((*node)->Key, key);
        (*node)->Value = value;
        (*node)->Color = (VColor)color;

        if(left == 1 && state == VScanNode::OK){
            ScanNodes(in, &(*node)->Left, state, count);
            (*node)->Left->Par = *node;
        }

        if(right == 1 && state == VScanNode::OK){
            ScanNodes(in, &(*node)->Right, state, count);
            (*node)->Right->Par = *node;
        }
    }

    VLoad VTree::Load(char path[]){
        std::ifstream file(path, std::ios::in);
        VNode* root = nullptr;
        if(file.is_open()){
            VTree new_tree;
            VScanNode state = VScanNode::OK;
            int count = 0;
            new_tree.root = root;
            ScanNodes(file, &root, state, count);
            if(state == VScanNode::ERR_OUT_OF_MEMORY){
                return VLoad::ERR_OUT_OF_MEMORY;
            }
            else if(state == VScanNode::ERR_WRONG_VARIABLE){
                return VLoad::ERR_WRONG_VARIABLE;
            }
            int scanCount;
            if(!(file >> scanCount) || scanCount != count){
                return VLoad::ERR_WRONG_VARIABLE;
            }
            new_tree.root = nullptr;
        }
        

        (*this).DeleteTree();
        (*this).root = root;

        return VLoad::OK;
    }

}