#include <iostream>
#ifndef ENTITY_H
#define ENTITY_H
class Entity{
    public:
        Entity();
        void Lvup(){
            Lev += 1;
            TPt++;
            SPt += 4;
        }
        void AddAtk(int val){
            Atk += val;
        }
        void AddLif(int val){
            Lif += val;
        }
        void AddDef(int val){
            Def += val;
        }
        void AddAtS(int val){
            AtS += val;
        }
        void AddMgA(int val){
            MgA += val;
        }
        void AddRes(int val){
            Res += val;
        }
        void AddMan(int val){
            Man += val;
        }
        void AddEnd(int val){
            End += val;
        }
        void AddCrt(double val){
            Crt += val;
        }
        void AddCrM(double val){
            CrM += val;
        }

        int Health;
        int Path;
        int TPt;
        int SPt;
        int Exp;
        int Lev;
        int Atk;
        int Lif;
        int Def;
        int AtS;
        int MgA;
        int Res;
        int Man;
        int End;

        double Crt;
        double CrM;
    protected:
    private:
};
#endif