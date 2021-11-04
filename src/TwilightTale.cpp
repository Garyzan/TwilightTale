#include <cmath>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <sys/stat.h>
#include "Weapon.h"
#include "Entity.h"
using namespace std;
Entity Player;              //player stat variables
int win;                    //determines win
int truewin;                //determines, if a true win can be achieved
int mmenu;                  //determines current node in main menu
int bmenu;                  //determines current node in battle menu
int battle;                 //determines if in battle or not
int quit;                   //determines if going back to main menu
int PClass;                 //class as index
int first;                  //determines if a run begins from the character creation
int conf;                   //describes current confirmation value
int close;                  //determines if completely closing the application
int areaprog;               //indicates progress in game
string pName = "";          //current characters name
string confirm = "";        //raw input of confirmation value
string input = "";          //general input
string Help = "   //Inv  : Opens inventory\n   //Char : Opens Character screen\n   //Tal  : Opens Talent tree\n   //Sur  : Opens Surroundings window\n   //Menu : Opens menu\n   //Exit : Exit to the Main Menu\n\n   //Type 'Help' to see this text again\n\n";
string InvHelp;             //gives commands for the Inv node
string CharHelp;            //gives commands for the Char node
string TalHelp;             //gives commands for the Tal node
string SurrHelp;            //gives commands for the Surr node
string ShopHelp;            //gives commands for the Shop node
string MenuHelp = "   //Menu :\n\n   //Save n(Saves to file n)\n   //Load n (Loads file n)\n   //Exit to Main Menu\n\n   //Back\n\n";
string DistHelp;
string path(){              //gives moral path for Char node
    string out = "";
        if(Player.Path == 0){
            out = "Dark";
        }
        else{
            out = "Light";
        }
    return out;
}
string lengthf(string in){  //inserts hyphens for inventory
    string out = "";
    for(unsigned int i = 0; i < in.length(); i++){
        out = out + "-";
    }
    return out;
}
string ins(int val){        //determines space for aligning values
    string out = "";
    string l = to_string(val);
    int z = 3 - l.length();
    for(int i = 0; i < z; i++){
        out = out + " ";
    }
    out = out + to_string(val);
    return out;
}
string pClass(int n){       //outputs Class as string based on variable
    string out = "";
    switch((int) to_string(n).at(0)){
        case 1:
            switch(n % 10){
                case 0:
                    out = "Knight";
                    break;
                case 1:
                    out = "Herald";
                    break;
                case 2:
                    out = "Paladin";
                    break;
            }
            break;
        case 2:
            switch(n%10){
                case 0:
                    out = "Mage";
                    break;
                case 1:
                    out = "Sage";
                    break;
                case 2:
                    out = "Necromancer";
                    break;
            }
            break;
        case 3:
            switch(n % 10){
                case 0:
                    out = "Thief";
                    break;
                case 1:
                    out = "Assassin";
                    break;
                case 2:
                    out = "Rogue";
                    break;
            }
            break;
    }
    return out;
}
void save(int i){           //saves to slot i
    string fnm = to_string(i)+".save";
    if(ifstream(fnm)){
        cout << "\n   Save Data already exist in slot " << to_string(i) << ".\n   Do you want to overwrite it?(Y/N)\n" << endl;
        cin >> input;
        if(input == "Y"){
            cout << "\n   Saving to Slot " << to_string(i)<<endl;
            ofstream fout((fnm).c_str());
            fout << Player.Lev;fout << "\n";
            fout << Player.Atk;fout << "\n";
            fout << Player.Def;fout << "\n";
            fout << Player.MgA;fout << "\n";
            fout << Player.Res;fout << "\n";
            fout << Player.End;fout << "\n";
            fout << Player.Man;fout << "\n";
            fout << Player.AtS;fout << "\n";
            fout << Player.Crt;fout << "\n";
            fout << Player.Health;fout << "\n";
            fout << Player.CrM;fout << "\n";
            fout << Player.Lif;fout << "\n";
            fout << Player.SPt;fout << "\n";
            fout << Player.TPt;fout << "\n";
            fout << pName << endl;
            cout << "\n   Saving complete\n\n";
        }
        else if(input == "N"){
            cout << "\n   Aborted saving.\n" << endl;
        }
        else{
            cout << "\n   Please choose a valid answer! (Y/N)\n" << endl;
        }
    }
    else{
        cout << "\n   Saving to Slot " << to_string(i)<<endl<<endl;
        ofstream fout((fnm).c_str());
            fout << Player.Lev;fout << "\n";
            fout << Player.Atk;fout << "\n";
            fout << Player.Def;fout << "\n";
            fout << Player.MgA;fout << "\n";
            fout << Player.Res;fout << "\n";
            fout << Player.End;fout << "\n";
            fout << Player.Man;fout << "\n";
            fout << Player.AtS;fout << "\n";
            fout << Player.Crt;fout << "\n";
            fout << Player.Health;fout << "\n";
            fout << Player.CrM;fout << "\n";
            fout << Player.Lif;fout << "\n";
            fout << Player.SPt;fout << "\n";
            fout << Player.TPt;fout << "\n";
            fout << pName     ;fout << "\n";
            cout << "Saving complete\n\n";
    }
}
void load(int i){           //loads from slot i
    string fnm = to_string(i)+".save";
    cout << "\n   Loading Save " << to_string(i) << "...\n" << endl;
    ifstream fin((fnm).c_str());
    fin >> Player.Lev;
    fin >> Player.Atk;
    fin >> Player.Def;
    fin >> Player.MgA;
    fin >> Player.Res;
    fin >> Player.End;
    fin >> Player.Man;
    fin >> Player.AtS;
    fin >> Player.Crt;
    fin >> Player.Health;
    fin >> Player.CrM;
    fin >> Player.Lif;
    fin >> Player.SPt;
    fin >> Player.TPt;
    fin >> pName;
    cout << "   Loading complete.\n\n\n" << endl;
}
void menuf(){               //evaluates Main Menu
    string out = "";
    string in = "";
    cout << "   ### # # ### #   ###  ## # # ###   ###  #  #   ###\n    #  # #  #  #    #  #   # #  #     #  # # #   #\n    #  ###  #  #    #  # # ###  #     #  ### #   ###\n    #  ###  #  #    #  # # # #  #     #  # # #   #\n    #  # # ### ### ###  ## # #  #     #  # # ### ###\n\n   Main Menu\n\n   //New    : Start a new Game\n   //Load n : Load Save File with number n\n   //Exit   : Close the App\n\n";
    menuin:
    cin >> in;
    if(in == "New"){
        first = 1;
    }
    else if(in == "Load"){
        int inn;
        cin >> inn;
        if(ifstream(to_string(inn) + ".save")){
            load(inn);
        }
        else{
            cout << "\n   File not found.\n" << endl;
            goto menuin;
        }
    }
    else if(in == "Exit"){
        win = 1;
        close = 1;
        cout << "\n   Shutting down...\n   Press any button to Exit.\n";
		while (!(_kbhit())) {};
    }
    else{
        cout << "\nPlease enter a valid command!\n\n";
    }
}
void battlef(){             //evaluates input in battle--------------------------------------highly-unfinished
    string out = "";
    string in = "";
    int backk = 0;
    cin >> in;
    switch(bmenu){

    }
}
void inputf(){              //evaluates input out of battle----------------------------------by-far-unfinished
    string out = "";
    string in = "";
    int backk = 0;
	if (mmenu == 0) { cout << Help; }
    cin >> in;
    switch(mmenu){
        case 0:{//Main Actions
            if(in == "Inv") {
                out = "\n   Inventory of " + pName + ":  \n   -------------" + lengthf(pName) + "-\n\n";
                mmenu = 1;
            }
            else if(in == "Char"){
                out = "\n   Name: " + pName + "  (" + to_string(Player.Exp) + " XP/" + to_string(100 * (int)round(pow(1.07303, Player.Lev - 1))) + " XP)\n\n   Path of the " + path() + "   Level: " + ins(Player.Lev) + "   " + "SP:   " + ins(Player.SPt) + "\n\n   HP:    " + ins(Player.Health) + "/" + to_string(Player.Lif) + "\n\n   Atk:   " + ins(Player.Atk) + "   " + "Mag:  " + ins(Player.MgA) + "\n   Def:   " + ins(Player.Def) + "   " + "Res:  " + ins(Player.Res) + "\n   End:   " + ins(Player.End) + "   " + "Mana: " + ins(Player.Man) + "\n   AtSp:  " + ins(Player.AtS) + "   " + "Dex:  " + ins((int)50 * Player.Crt) + "\n";
				mmenu = 2;
            }
            else if(in == "Tal") {
                mmenu = 3;
            }
            else if(in == "Sur") {
                switch(areaprog){
                    case 6:
                        if(Player.Path == 1){
                            out = "    Black Spire\n" + out;
                        }
                        else{
                            out = "    White Spire\n" + out;
                        }
                    case 5:
                        if(Player.Path == 1){
                            out = "    Merthvyk Arc\n" + out;
                        }
                        else{
                            out = "    Daliang Chapel\n" + out;
                        }
                    case 4:
                        if(Player.Path == 1){
                            out = "    Fasach Desert\n" + out;
                        }
                        else{
                            out = "    Scathaithe Mare\n" + out;
                        }
                    case 3:
                        if(Player.Path == 1){
                            out = "    Shore of the Abhainn Mhor\n" + out;
                        }
                        else{
                            out = "    Edraighe Bridge\n" + out;
                        }
                    case 2:
                        if(Player.Path == 1){
                            out = "    Ruins of Riverside\n" + out;
                        }
                        else{
                            out = "    City of Windfall\n" + out;
                        }
                    case 1:
                        if(Player.Path == 1){
                            out = "    Field of Sorrow\n" + out;
                        }
                        else{
                            out = "    Forest of Aire\n" + out;
                        }
                    case 0:
                        if(areaprog == 0){
                            out = "    Ambushed Barrack\n" + out;
                        }
                        else{
                            out = "    Old Barrack\n" + out;
                        }
                        break;
                }
                out = "\n\n   Available Areas:\n" + out;
                mmenu = 4;
            }
            else if(in == "Shop"){
                mmenu = 5;
            }
            else if(in == "Menu"){
                out = MenuHelp;
                mmenu = 6;
            }
            else if(in == "Help"){
                out = Help;
            }
            else if(in == "Exit"){
                string inln = "";
                    cout << "\n   Are you sure? Unsaved data will be lost!(Y/N)\n\n";
                cin >> inln;
                if(inln == "Y"){
                    win = 1;
                    quit = 1;
                }
            }
            else{
                cout << "\n   Unknown command. Please use one of the commands listed above.\n" << endl;
            }
            break;
        }
        case 1:{//Inventory    --- unfinished --- Needs reevaluation
            if(in == "Equip"){
                string inn;
                cin >> inn;
                
            }
            else if(in == "Back"){
                mmenu = 0;
            }
            else if(in == "Help"){
                out = InvHelp;
            }
            break;
        }
        case 2:{//Character
            if(in == "Back"){
                mmenu = 0;
            }
            else if(in == "Distr"){
                mmenu = 7;
            }
            else if(in == "Help"){
                out = CharHelp;
            }
            break;
        }
        case 3:{//Talent Tree  --- unfinished
            if(in == "Back"){
                mmenu = 0;
            }
            else if(in == "Help"){
                out = TalHelp;
            }
            break;
        }
        case 4:{//Surroundings --- unfinished
            if(in == "Back"){
                mmenu = 0;
            }
            else if(in == "Help"){
                out = SurrHelp;
            }
            break;
        }
        case 5:{//Shop         --- unfinished
            //Insert shop here ^^'
        }
        case 6:{//Menu
            int inn;
            cin >> inn;
            if(in == "Save"){
                save(inn);
                mmenu = 0;
            }
            else if(in == "Load"){
                load(inn);
                mmenu = 0;
            }
            else if(in == "Back"){
                mmenu = 0;
            }
            else if(in == "Help"){
                out = MenuHelp;
            }
            else{
                cout << "\n   Please enter a valid command!\n\n";
            }
            break;
        }
        case 7:{//Distribute
            string inn;
            if(Player.SPt > 0){
                while(Player.SPt > 0 && backk == 0){
                    cin >> inn;
                    if(inn == "Back"){
                        backk = 1;
                        Player.SPt++;
                    }
                    else if(inn == "Atk"){
                        Player.Atk++;
                    }
                    else if(inn == "Def"){
                        Player.Def++;
                    }
                    else if(inn == "End"){
                        Player.End++;
                    }
                    else if(inn == "Mag"){
                        Player.MgA++;
                    }
                    else if(inn == "Res"){
                        Player.Res++;
                    }
                    else if(inn == "Mana"){
                        Player.Man++;
                    }
                    else if(inn == "AtSp"){
                        Player.AtS++;
                    }
                    else if(inn == "Dex"){
                        Player.Crt += 0.02;
                    }
                    else if(in == "Help"){
                        out = DistHelp;
                    }
                    else{
                        cout << "Please enter a valid stat!";
                    Player.SPt++;
                        }
                    Player.SPt--;
                    if(backk == 0){
                        cout << "\nYou enhanced your " + inn + "! " + to_string(Player.SPt) + " Points remaining.\n\n";
                    }
                }
				backk = 0;
				cout << "\nFinished distributing Status Points!\n\n";
				break;
            }
            else{
                cout << "You have no Stat Points!\n\n";
            }
			break;
        }
    }
    cout << out << endl;
}
void pwinf(){               //unrolls pseudowin sequence
    string n;
    string m;
    if(Player.Path == 1){
        n = "Athail, Angel of the Heavens";
        m = "'Justice'";
    }
    else{
        n = "Zaelion, Angel of the Void";
        m = "'Sin'";
    }
    cout << "   "<<n<<" replenished all Health.\n\n    Why, you fool? Why do you want to make us suffer like that?\n    I can't bear you anymore!\n\n   "<<n<<" grew to full Power.\n   "<<n<<" used "<<m<<".\n   Every Effect has been nullified!\n   You suffered 99999999 Damage!\n   "<<n<<" defeated you!\n\n   You unlocked the Achievement 'I died'!\n\n   THE END...?";
    cout << "\n\n\n   Press any button to return to the Main Menu\n\n";
    _getch();
    cout << "\n\n\n\n\n";
    win = 0;
    battle = 0;
    quit = 1;
}
void winf(){                //unrolls true win sequence--------------------------------------unfinished
    cout << "you won";
}
int main(){                 //game
    mainmenu:
    menuf();
    if (first == 1){
        first = 0;
        cout << "\n   You awaken in a void place. Somethings here. Somehow, you seem to here its voice.\n\n   Welcome, Warrior!\n   Our land is in war with the Void. It keeps sending its minions to eliminate our People and conquer our kingdom.\n   You are our only hope. But before you can begin your journey, you must create yourself a body.\n   First, you have to choose a Class:\n\n";
        ChooseClass:
        cout << "   Knight: Wields a Sword\n       A brave Warrior, who encounters enemies with his sword and shield.\n       Exceeds at close range combat, but lacks speed.\n       Can promote to Paladin or Herald.\n\n   Mage: Wields a Tome\n       A wise Warrior, who engages enemies at a distance with various spells.\n       Exceeds at afflicting effects to enemies, but lacks Defense.\n       Can promote to Sage or Necromancer.\n\n   Thief: Wields a Dagger\n       A skilled Warrior, who sneaks behind enemies and strikes swiftly.\n       Exceeds at staying out of range, but lacks Damage.\n       Can promote to Assassin or Rogue.\n\n";
        inputclass:
        cin >> input;
        if(input == "Knight"){
            PClass = 10;
            Player.Health = 100;
            Player.Atk = 5;
            Player.End = 50;
            Player.Def = 7;
            Player.MgA = 2;
            Player.Man = 10;
            Player.Res = 3;
            Player.AtS = 5;
            Player.Crt = 0.05;
            Player.CrM = 1.67;
            Player.Lif = 100;
        }
        else if(input == "Mage"){
            PClass = 20;
            Player.Health = 100;
            Player.Atk = 2;
            Player.End = 20;
            Player.Def = 3;
            Player.MgA = 7;
            Player.Man = 50;
            Player.Res = 6;
            Player.AtS = 4;
            Player.Crt = 0.05;
            Player.CrM = 1.67;
            Player.Lif = 100;
        }
        else if(input == "Thief"){
            PClass = 30;
            Player.Health = 100;
            Player.Atk = 4;
            Player.End = 40;
            Player.Def = 4;
            Player.MgA = 3;
            Player.Man = 20;
            Player.Res = 4;
            Player.AtS = 8;
            Player.Crt = 0.1;
            Player.CrM = 1.5;
            Player.Lif = 100;
        }
        else{
            cout << "\n   Please choose a valid class!\n" << endl;
            goto inputclass;
        }
        cout << "\n   Do you choose to be a "<<input<<"?(Y/N)\n" << endl;
        ConfClass:
        cin >> confirm;
        if(confirm == "N") {
			cout << "\n   Then choose again:\n" << endl;
			goto ChooseClass;
        }
        else if(confirm == "Y") {
			cout << "\n   Then so be it!\n   Now you have to choose yourself a name.\n" << endl;
        }
		else {
			cout << "\n   Please choose a valid answer!(Y/N)\n" << endl;
			goto ConfClass;
        }
        inputname:
        cin >> pName;
        cout << "\n   So your name shall be "<<pName<<"?(Y/N)\n" << endl;
        ConfName:
        conf = 0;
        cin >> confirm;
        if(confirm == "N"){
			cout << "\n   Then choose again\n";
			goto inputname;
        }
        else if(confirm == "Y"){
			cout << "\n   " << pName << " then! A good name, befitting a great Warrior like you." << endl;
        }
		else {
			cout << "\n   Please choose a valid answer!(Y/N)\n" << endl;
			goto ConfName;
		}
        cout << "\n   Your journey shall begin now...\n\n\n\n   You dream. You feel a power surging within you, ";
        switch(PClass){
            case 10:
                cout << "an unstoppable force.";
                break;
            case 20:
                cout << "a neverending well of magic.";
                break;
            case 30:
                cout << "godlike dexterity.";
                break;
        }
        cout << "\n   With it comes a vision, of a place colder than the deepest winter, hotter than the sun.\n   You wander around, feeling an overwhelming Presence. It speaks with thunder, but you cannot understand a word.\n   Both quickly fade away, as you awaken.\n\n   You hear the sounds of war. Your Constable stands over you, ready to hit you again.\n\n    WAKE UP! Dark Forces have ambushed us! I can't believe you were still able to sleep!\n    Hurry up and get yourself ready!\n\n";
        cout << Help << endl;
    }
    while(win == 0){
        switch(battle){
            case 0:
                inputf();
                break;
            case 1:
                battlef();
                break;
            default:
                cout << "An error (0x01) occured.\nPlease send case description to the developer.";
                quit = 1;
                win = 0;
                break;
        }
    }
    if(close != 1 && quit != 1){
        if(truewin == 0){
            pwinf();
        }
        else{
            winf();
        }
    }
    if(quit == 1){
        quit = 0;
        goto mainmenu;
    }
    return 0;
}