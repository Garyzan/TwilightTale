#ifndef WEAPON_H
#define WEAPON_H
#include <string>
using namespace std;
class Weapon
{
    public:
		Weapon(string Name, int Type, int Power) {
			Typ = Type;
			Pow = Power;
			Nam = Name;
		};

        void SetTyp(int val){Typ = val;};
        void SetPow(int val){Pow = val;};
        void AdjDur(signed int val){Dur += val;};
        void AdjWth(signed int val){Wth += val;};

		string Nam; //Name
        string Des; //Description
        int Wth;    //Worth
        int Wgt;    //Weight
        int Typ;    //Type
        int STy;    //Subtype
        int Dur;    //Durability
        int Pow;    //Attack/Defense

    protected:

    private:
};
#endif // WEAPON_H
