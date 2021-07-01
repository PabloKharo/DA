#include "tree.hpp"

const char SENTI = '$'; 

namespace NSuffTree{

    void TTree::Init(){
        Text = "";
        Root = new TNode(0, 0);
        Root->Link = Root;
        findpos.CurNode = Root;
        findpos.CurLen = 0;
        findpos.CurEdge = 0;
        pos.CurNode = Root;
        pos.CurLen = 0;
        pos.CurEdge = 0;
        Rem = 0;

        End = 0;
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

    
    void TTree::Add(char c){
        Text += c;
        TNode* nodeForSuff = nullptr;
        Rem++;

        if (Rem == 1) {
            pos.CurEdge = End;
        }

        while (Rem > 0){
            TNode* nextNode = FindNode(pos.CurNode, Text[pos.CurEdge]);
            if (nextNode == nullptr){
                pos.CurNode->Next[Text[pos.CurEdge]] = new TNode(End, -1);
                if (nodeForSuff != nullptr){
                    nodeForSuff->Link = pos.CurNode;
                }
                nodeForSuff = pos.CurNode;
            }else{
                int edgeLen = EdgeLen(nextNode);

                if (pos.CurLen >= edgeLen){
                    pos.CurNode = nextNode;
                    pos.CurLen -= edgeLen;
                    pos.CurEdge += edgeLen;
                    continue; 
                }

                if (Text[nextNode->Lpos + pos.CurLen] == Text[End]){
                    pos.CurLen++;
                    if (nodeForSuff != nullptr){
                        nodeForSuff->Link = pos.CurNode;
                    }
                    break; 
                }

                TNode* midNode = new TNode(nextNode->Lpos, nextNode->Lpos + pos.CurLen);
                pos.CurNode->Next[Text[pos.CurEdge]] = midNode;
                midNode->Next[Text[End]] = new TNode(End, -1);
                nextNode->Lpos += pos.CurLen;
                midNode->Next[Text[nextNode->Lpos]] = nextNode;

                if (nodeForSuff != nullptr){
                    nodeForSuff->Link = midNode;
                }
                nodeForSuff = midNode;
            }

            
            if (pos.CurNode == Root && pos.CurLen > 0){
                pos.CurEdge++;
                pos.CurLen--;
            }else if (pos.CurNode != Root){
                pos.CurNode = pos.CurNode->Link;
            }
                    
            Rem--;
        }

        End++;
    }
    
    int TTree::FindLastChar(){
        if(findpos.CurLen == 0){
            findpos.CurEdge = End - 1;
        }

        TNode* nextNode = FindNode(findpos.CurNode, Text[findpos.CurEdge]);
        if (nextNode == nullptr){
            findpos.CurNode = Root;
            findpos.CurLen = 0;
        }else{
            int edgeLen = EdgeLen(nextNode);
            if (findpos.CurLen == edgeLen){
                findpos.CurNode = nextNode;
                findpos.CurLen -= edgeLen;
                findpos.CurEdge += edgeLen;
                nextNode = FindNode(findpos.CurNode, Text[findpos.CurEdge]);
            }

            if (nextNode != nullptr && Text[nextNode->Lpos + findpos.CurLen] == Text[End - 1] && nextNode->Lpos + findpos.CurLen != End - 1) {
                findpos.CurLen++;
                return nextNode->Lpos + findpos.CurLen; 
            }
            else {
                findpos.CurNode = Root;
                findpos.CurLen = 0;
            }
        }

        return -1;

    }


    void TTree::DeinitNode(TNode* node){
        for(auto next: node->Next){       
            DeinitNode(next.second);
        }
        delete node;
    }

}

