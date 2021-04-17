#pragma once
#include <stdexcept>

namespace NVector{
    const int MIN_CAP = 16;
    const int POP_DIF = 4; 
    const int PUSH_DIF = 16;

    template <typename T>
    class TVector
    {
    private:
        T* Vbuf;
        size_t Vsize;
        size_t Vcapacity;

    public:
        TVector(): 
            Vbuf(new T[MIN_CAP]), 
            Vsize(0), 
            Vcapacity(MIN_CAP) {};
        ~TVector(){           
            delete[] Vbuf;
        }
        
        explicit TVector(size_t cap);
        void PushBack(T);
        T PopBack();
        void Resize(size_t);
        T& operator[] (size_t);
        TVector& operator= (const TVector&);

        size_t Size(){
            return Vsize;
        }

        T* Begin(){
            return &Vbuf[0];
        }

        T* End(){
            return &Vbuf[Vsize];
        }
        // Swap без копирования данных
        void Swap(TVector<T>&);
    };

    template <typename T>
    void TVector<T>::Resize(size_t cap){
        if (cap >= 0)
        {
            if (cap < MIN_CAP)
                cap = MIN_CAP;
            if (Vsize > cap)
                Vsize = cap;
            T* newbuf = new T[cap];
            for (size_t i = 0; i < Vsize; ++i) {
                newbuf[i] = Vbuf[i];
            }
            delete[] Vbuf;
            Vbuf = newbuf;
            Vcapacity = cap;
        }
    }

    template <typename T>
    TVector<T>::TVector(size_t cap){
        if (cap >= 0){
            Vbuf = new T[cap];    
            Vsize = Vcapacity = cap;
        }
    }

    template <typename T>
    void TVector<T>::PushBack(T value){
        if (Vsize == Vcapacity){
            Resize(Vcapacity * PUSH_DIF);
        }
        Vbuf[Vsize++] = value;
    }

    template <typename T>
    T TVector<T>::PopBack(){
        if (Vcapacity > MIN_CAP && Vsize * POP_DIF < Vcapacity){
            Resize(Vsize);
        }
        return Vbuf[--Vsize];
    }

    template <typename T>
    T& TVector<T>::operator[] (size_t i){
        if (i >= 0 && i < Vsize){
            return Vbuf[i];
        }else{
             throw std::out_of_range{ "TVector index is out of range" };
        }
    }

    template <typename T>
    TVector<T>& TVector<T>::operator= (const TVector& vec){
        Vsize = vec.Vsize;
        if (this->Vcapacity != vec.Vcapacity){
            delete[] Vbuf;
            this->Vbuf = new T[vec.Vcapacity];
        }
        for (size_t i = 0; i < vec.Vsize; ++i){
            this->Vbuf[i] = vec.Vbuf[i];
        }
        return *this;
    }

    template <typename T>
    void TVector<T>::Swap(TVector<T>& vec)
    {
        T* tmpbuf = vec.Vbuf;
        size_t tmpsize = vec.Vsize;
        size_t tmpcap = vec.Vcapacity;

        vec.Vbuf = this->Vbuf;
        vec.Vsize = this->Vsize;
        vec.Vcapacity = this->Vcapacity;

        this->Vbuf = tmpbuf;
        this->Vsize = tmpsize;
        this->Vcapacity = tmpcap;
    }

}