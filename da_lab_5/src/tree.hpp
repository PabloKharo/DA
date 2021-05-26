#pragma once 

#include <string>
#include <unordered_map>

using namespace std;

namespace NSuffTree{

    struct TNode{
        int Lpos, Rpos;
        TNode* Link;
        unordered_map<char, TNode*> Next;

        TNode(int lpos, int rpos):Lpos(lpos), Rpos(rpos){
            Link = nullptr;
        }
    };

    class TTree{
        private:
            string Text;
            TNode* Root;
            TNode* CurNode;
            int CurLen, End, Rem;
            int CurEdge;

            void DeinitNode(TNode* node);
            TNode* FindNode(TNode* NodeToFind, char c);
            int EdgeLen(TNode* node);
        public:
            void Add(int i);
            string FindMin();
            TTree(string str);
            ~TTree(){
                DeinitNode(Root);
            }
    };

}
