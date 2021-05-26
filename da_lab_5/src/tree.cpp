#include "tree.hpp"

const char SENTI = '$'; 

namespace NSuffTree{

    TTree::TTree(string str){
        Root = new TNode(0, 0);
        Root->Link = Root;

        CurNode = Root;
        CurLen = 0;
        CurEdge = 0;
        Rem = 0;

        Text = str + str + SENTI;
        End = 0;
        for(int i = 0; i < (int)Text.length(); i++){
            Add(i);
            End++;
        }
    }
    
    TNode* TTree::FindNode(TNode* NodeToFind, char c){
        auto found = NodeToFind->Next.find(c);
        if(found != NodeToFind->Next.end()){
            return found->second;
        }
        return nullptr;
    }
    
    int TTree::EdgeLen(TNode* node){
        if (node->Rpos == -1) {
            return End - node->Lpos + 1;
        }
        return node->Rpos - node->Lpos;
    }

    
    void TTree::Add(int i){
        TNode* nodeForSuff = nullptr;
        Rem++;

        if (Rem == 1) {
            CurEdge = i;
        }

        while (Rem > 0){
            TNode* nextNode = FindNode(CurNode, Text[CurEdge]);
            if (nextNode == nullptr){
                CurNode->Next[Text[CurEdge]] = new TNode(i, -1);
                if (nodeForSuff != nullptr){
                    nodeForSuff->Link = CurNode;
                }
                nodeForSuff = CurNode;
            }else{
                int edgeLen = EdgeLen(nextNode);

                if (CurLen >= edgeLen){
                    CurNode = nextNode;
                    CurLen -= edgeLen;
                    CurEdge += edgeLen;
                    continue; 
                }

                if (Text[nextNode->Lpos + CurLen] == Text[i]){
                    CurLen++;
                    if (nodeForSuff != nullptr){
                        nodeForSuff->Link = CurNode;
                    }
                    break; 
                }

                TNode* midNode = new TNode(nextNode->Lpos, nextNode->Lpos + CurLen);
                CurNode->Next[Text[CurEdge]] = midNode;
                midNode->Next[Text[i]] = new TNode(i, -1);
                nextNode->Lpos += CurLen;
                midNode->Next[Text[nextNode->Lpos]] = nextNode;

                if (nodeForSuff != nullptr){
                    nodeForSuff->Link = midNode;
                }
                nodeForSuff = midNode;
            }

            
            if (CurNode == Root && CurLen > 0){
                CurEdge++;
                CurLen--;
            }else if (CurNode != Root){
                CurNode = CurNode->Link;
            }
                    
            Rem--;
        }
    }
    
    string TTree::FindMin(){
        string res = "";

        CurNode = Root;
        while (!CurNode->Next.empty()) {
            for (int i = CurNode->Lpos; i < CurNode->Rpos; i++) {
                res += Text[i];
            }

            TNode* minNode = nullptr;
            char minC = 'z' + 1;
            for (auto val : CurNode->Next) {
                if (val.first != '$' && val.first < minC) {
                    minC = val.first;
                    minNode = val.second;
                }
            }
            CurNode = minNode;
            
        }

        for (int i = CurNode->Lpos; i < (int)Text.length(); i++) {
            res += Text[i];
        }
        res = res.substr(0, (Text.length() - 1) / 2);

        return res;
    }


    void TTree::DeinitNode(TNode* node){
        for(auto next: node->Next){       
            DeinitNode(next.second);
        }
        delete node;
    }

}

