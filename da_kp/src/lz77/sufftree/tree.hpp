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

    struct Pos{
        TNode* CurNode;
        int CurLen;
        int CurEdge;
    };

    class TTree{
        private:
            TNode* Root;
            int End, Rem;
            Pos pos;
            Pos findpos;

            TNode* FindNode(TNode* NodeToFind, char c);
            int EdgeLen(TNode* node);
            void DeinitNode(TNode* node);
        public:
            string Text;
            void Init();
            void Deinit(){
                DeinitNode(Root);
            }
            void Add(char c);
            int FindLastChar();
            
            TTree(){
                Init();
            }
            ~TTree(){
                DeinitNode(Root);
            }
    };

}
