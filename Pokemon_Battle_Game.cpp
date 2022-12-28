#include <iostream>
#include <string>
using namespace std;
// function prototypes start
//  void manage_current_party(Trainer *&current_trainers, int &index);
// function prototypes end
class Trainer;
class PokeType;
class Pokemon;

class PokeType
{
private:
    char type;
    int base_speed;
    int base_attack;
    int base_hp;

public:
    PokeType(char _type)
    {
        switch (_type)
        {
        case 'f':
            base_speed = 10;
            base_attack = 15;
            base_hp = 65;
            break;
        case 'w':
            base_speed = 5;
            base_attack = 20;
            base_hp = 100;
            break;
        case 'g':
            base_speed = 2;
            base_attack = 25;
            base_hp = 50;
            break;
        }
    }
    char getType()
    {
        return type;
    }
    int getBaseSpeed()
    {
        return base_speed;
    }
    int getBaseAttack()
    {
        return base_attack;
    }
    int getBaseHp()
    {
        return base_hp;
    }
};

class Pokemon
{
private:
    string name;
    PokeType *type; // points to Poketype class
    int level;
    Trainer *trainer; // points to trainer class
    double current_hp;
    double current_speed;
    double current_attack;
    double total_hp;
    double xp;

public:
    Pokemon()
    {
        name = "";
        type = nullptr;
        trainer = NULL;
        level = 1;
        current_attack = 0;
        current_speed = 0;
        total_hp = 0;
        current_hp = 0;
        xp = 0;
    }
    Pokemon(string _name, char _input_type, int _level)
    {
        type = new PokeType(_input_type);
        level = _level;
        trainer = NULL;
        xp = 0;
        current_speed = type->getBaseSpeed();
        current_hp = type->getBaseHp();
        current_attack = type->getBaseAttack();
        name = _name;
        if (level == 1)
        {
            current_hp = type->getBaseHp();
            current_attack = type->getBaseAttack();
        }
        else
        {
            for (int i = 2; i < level + 1; i++)
            {
                current_hp = 1.1 * current_hp;
                current_attack = 1.05 * current_attack;
            }
        }
        total_hp = current_hp;
    }
    Pokemon operator++(int)
    {
        Pokemon temp(*this);
        level += 1;
        current_hp = 1.1 * current_hp;
        current_attack = 1.05 * current_attack;
        total_hp = 1.1 * total_hp;
        return temp;
    }
    Pokemon(const Pokemon &old)
    {
        // copy constructor
        name = old.name;
        char wt = old.type->getType();
        type = new PokeType(wt);
        current_speed = old.current_speed;
        level = old.level;
        current_hp = old.current_hp;
        total_hp = old.total_hp;
        trainer = old.trainer;
        current_attack = old.current_attack;
        xp = old.xp;
    }
    string getPokemonName()
    {
        return name;
    }
    int getPokemonLevel()
    {
        return level;
    }
    double getc_speed()
    {
        return current_speed;
    }
    double getc_attack()
    {
        return current_attack;
    }
    double getc_hp()
    {
        return current_hp;
    }
    double getc_totalhp()
    {
        return total_hp;
    }
    void setPokemonLevel(int _level)
    {
        level = _level;
    }
    void setPokemonName(string _name)
    {
        name = _name;
    }
    void setPokemonSpeed(double _speed)
    {
        current_speed = _speed;
    }
    void setPokemonAttack(double _attack)
    {
        current_attack = _attack;
    }
    void setPokemonHP(double _hp)
    {
        current_hp = _hp;
    }
    void setPokemonTOTALHP(double _hp)
    {
        total_hp = _hp;
    }
    void setXP(double _xp)
    {
        xp = _xp;
    }
    ~Pokemon()
    {
        delete type;
    }
};

class Trainer
{
private:
    string name;
    int num_pokemon_owned;
    Pokemon *pokemon_owned;
    Pokemon *current_party[6] = {NULL};
    int count_in_current_party;

public:
int get_cp_index(string _pokiname){
    for(int i=0;i<count_in_current_party;i++){
        if(current_party[i]->getPokemonName()==_pokiname){
            return i;
        }
    }
}
    bool all_pass_out();
    void awardXP();
    void restorehp();
    void pok_switch(int &ind);
    bool active_pok_passout(int _index);
    void remove_from_cp();
    void add_to_cp();
    void display_current_party();
    friend void Battle(Trainer *&current_trainers,int &index_t1,int &index_t2);
    Trainer()
    {
        // default constructor
        name = "";
        pokemon_owned = {NULL};
        for (int i = 0; i < 6; i++)
        {
            current_party[i] = NULL;
        }
        num_pokemon_owned = 0;
        count_in_current_party = 0;
    }
    Trainer(string _trainer_name)
    {
        // parametrised constructor
        pokemon_owned = {NULL};
        name = _trainer_name;
        num_pokemon_owned = 0;
        for (int i = 0; i < 6; i++)
        {
            current_party[i] = NULL;
        }
        count_in_current_party = 0;
    }
    double get_ap_speed(int index){
        // cout<<"\nin ap speed func member"<<endl;
        return current_party[index]->getc_speed();
    }
    double get_ap_attack(int index){
        return current_party[index]->getc_attack();
    }
    void reduce_hp_byattack(int index,double attackval){
        current_party[index]->setPokemonHP((current_party[index]->getc_hp())-(attackval));
    }
    double get_ap_hp(int index){
        return current_party[index]->getc_hp();
    }
    void AddPokemon(Pokemon poki)
    {
        Pokemon *ptr;
        // checking if already pokemon present or not
        // if yes then dynamically increase size else first time array declaration
        if (num_pokemon_owned > 0)
        {
            ptr = new Pokemon[num_pokemon_owned];
            for (int i = 0; i < num_pokemon_owned; i++)
            {
                ptr[i] = pokemon_owned[i];
            }
        }
        num_pokemon_owned++;
        // delete [] pokemon_owned;
        pokemon_owned = new Pokemon[num_pokemon_owned];

        if ((num_pokemon_owned - 1) > 0)
        {
            for (int i = 0; i < (num_pokemon_owned - 1); i++)
            {
                pokemon_owned[i] = ptr[i];
            }
        }
        pokemon_owned[num_pokemon_owned - 1] = poki;
        // delete [] ptr;
    }

    void DisplayPokemon()
    {
        cout << name << "'s "
             << "Pokemon: " << endl;
        for (int i = 0; i < num_pokemon_owned; i++)
        {
            cout << pokemon_owned[i].getPokemonName() << " --- " << pokemon_owned[i].getPokemonLevel() << endl;
            // cout << "Current attack: " <<pokemon_owned[i].getc_attack() << endl;
            // cout << "Current speed: " <<pokemon_owned[i].getc_speed() << endl;
            // cout << "Current hp: " <<pokemon_owned[i].getc_hp() << endl;
        }
    }
    void operator+(Pokemon pokiobj)
    {
        Pokemon *ptr;
        if (num_pokemon_owned > 0)
        {
            ptr = new Pokemon[num_pokemon_owned];
            for (int i = 0; i < num_pokemon_owned; i++)
            {
                ptr[i] = pokemon_owned[i];
            }
        }
        num_pokemon_owned++;
        pokemon_owned = new Pokemon[num_pokemon_owned];

        if ((num_pokemon_owned - 1) > 0)
        {
            for (int i = 0; i < (num_pokemon_owned - 1); i++)
            {
                pokemon_owned[i] = ptr[i];
            }
        }
        pokemon_owned[num_pokemon_owned - 1] = pokiobj;
        // delete [] ptr;
    }
    string getTrainerName()
    {
        return name;
    }
    int get_cp_count()
    {
        return count_in_current_party;
    }
    void setTrainerName(string _name)
    {
        name = _name;
    }
    friend ostream &operator<<(ostream &, Trainer);
    ~Trainer()
    {
        delete[] pokemon_owned;
    }
};
ostream &operator<<(ostream &out, Trainer trainerobj)
{
    out << trainerobj.name << "'s "
        << "Pokemon: " << endl;
    for (int i = 0; i < trainerobj.num_pokemon_owned + 1; i++)
    {
        cout << trainerobj.pokemon_owned[i].getPokemonName() << " --- " << trainerobj.pokemon_owned[i].getPokemonLevel() << endl;
    }
    return out;
}

void displayGameMenu()
{
    cout << "Enter one of the options to proceed:" << endl;
    cout << "    "
         << "1. Trainer Menu?" << endl;
    cout << "    "
         << "2. Battle Menu?" << endl;
    cout << "    "
         << "3. Exit?" << endl;
}
void displayTrainerMenu()
{
    cout << "    1. Add Pokemon? " << endl;
    cout << "    2. Display Pokemon? " << endl;
    cout << "    3. Manage Current Party" << endl;
    cout << "    4. Exit to Main Menu? " << endl;
}
void Battle(Trainer *&current_trainers,int &index_t1,int &index_t2){
    string poki1, poki2 = "";
    int index_poki1, index_poki2 = 0;

    current_trainers[index_t1].display_current_party();
    cout << "\nTrainer 1 please enter corresponding index of the pokemon: " << endl;
    cin >> index_poki1;
    // index_poki1 = current_trainers->get_cp_index(poki1);
    index_poki1--;

    current_trainers[index_t2].display_current_party();
    cout << "\nTrainer 2 please enter corresponding index of the pokemon: " << endl;
    cin >> index_poki2;
    // index_poki2 = current_trainers->get_cp_index(poki2);
    index_poki2--;

    int k=1;
    bool tn1win = false;
    bool tn2win = false;
    int choice_t1=0;
    int choice_t2=0;
    // cout<<"\ngoing in while loop"<<endl;
    while (k==1)
    {
        cout << "\nPlayer 1's turn: " << endl;
        cout << "Press 1 to attack: " << endl;
        cout << "Press 2 for switch: " << endl;
        cout << "Press 3 for forfeit: " << endl;
        cin >> choice_t1;

        cout << "\nPlayer 2's turn: " << endl;
        cout << "Press 1 to attack: " << endl;
        cout << "Press 2 for switch: " << endl;
        cout << "Press 3 for forfeit: " << endl;
        cin >> choice_t2;

        // cout<<choice_t1<<" CHOICE t1"<<endl;
        // cout<<choice_t2<<" CHOICE t2"<<endl;

        if (choice_t1 == 3)
        {
            // cout<<"\nline 389"<<endl;
            tn2win = true;
        }
        if (choice_t2 == 3)
        {
            // cout<<"\nline 394"<<endl;
            tn1win = true;
        }

        if (choice_t1 == 1 && choice_t2 == 1) // both attack
        {
            // cout<<"line 413"<<endl;
            cout<<index_poki1<<endl;
            cout<<index_poki2<<endl;
            // cout<<"trainer indexes"<<endl;
            cout<<current_trainers[index_t1].current_party[index_poki1]->getPokemonName();
            //check if active pokemon passout or not then switch accordingly
            if (current_trainers[index_t1].active_pok_passout(index_poki1) == true)
            {
                current_trainers[index_t1].pok_switch(index_poki1);
            }
            if (current_trainers[index_t2].active_pok_passout(index_poki2) == true)
            {
                current_trainers[index_t2].pok_switch(index_poki2);
            }
            // cout<<"line 423"<<endl;


            //t1speed > t2speed
            if (current_trainers[index_t1].get_ap_speed(index_poki1) > current_trainers[index_t2].get_ap_speed(index_poki2))
            {
                // cout<<"line 429"<<endl;
                // t1 attack first
                current_trainers[index_t2].reduce_hp_byattack(index_poki2, current_trainers[index_t1].get_ap_attack(index_poki1));
                // then t2 attack if pokemon not passed out
                if (current_trainers[index_t2].active_pok_passout(index_poki2)==false) //checking if pass out
                {
                    current_trainers[index_t1].reduce_hp_byattack(index_poki1, current_trainers[index_t2].get_ap_attack(index_poki2));
                }
            }
            //t2speed > t1speed
            //or t2speed==t1speed
            else
            {
                // cout<<"line 443"<<endl;
                // t2 attack first
                current_trainers[index_t1].reduce_hp_byattack(index_poki1, current_trainers[index_t2].get_ap_attack(index_poki2));
                // then t1 attack if pokemon not passed out
                if (current_trainers[index_t1].active_pok_passout(index_poki1)==false) //checking if pass out
                {
                    current_trainers[index_t2].reduce_hp_byattack(index_poki2, current_trainers[index_t1].get_ap_attack(index_poki1));
                }
            }
            // cout<<"line 451"<<endl;

            //checking if anyone won after this specific turn
            if (current_trainers[index_t1].all_pass_out() == true)
            {
                tn2win = true; // trainer 2 wins
            }
            if (current_trainers[index_t2].all_pass_out() == true)
            {
                tn1win = true; // trainer 1 wins
            }
        }
        if (choice_t1 == 1 && choice_t2 == 2) // t1 attack and t2 switch
        {
            // t1 attack so check if pokemon pass out or not
            if (current_trainers[index_t1].active_pok_passout(index_poki1) == true)
            {
                // means t1 pokemon passed out
                // so switch called for both
                current_trainers[index_t1].pok_switch(index_poki1);
                current_trainers[index_t2].pok_switch(index_poki2);
            }
            else
            {
                // t1 attack
                // attack lands first
                current_trainers[index_t2].reduce_hp_byattack(index_poki2, current_trainers[index_t1].get_ap_attack(index_poki1));
                // switch happens second
                current_trainers[index_t2].pok_switch(index_poki2);
            }

            // checking if anyone won after this specific turn
            if (current_trainers[index_t1].all_pass_out() == true)
            {
                tn2win = true; // trainer 2 wins
            }
            if (current_trainers[index_t2].all_pass_out() == true)
            {
                tn1win = true; // trainer 1 wins
            }
        }
        if (choice_t1 == 2 && choice_t2 == 1) // t1 switch and t2 attack
        {
            // t2 attack so check if pokemon pass out or not
            if (current_trainers[index_t2].active_pok_passout(index_poki2) == true)
            {
                // means t2 pokemon passed out
                // so switch called for both
                current_trainers[index_t2].pok_switch(index_poki2);
                current_trainers[index_t1].pok_switch(index_poki1);
            }
            else
            {
                // t2 attack
                // attack lands first
                current_trainers[index_t1].reduce_hp_byattack(index_poki1, current_trainers[index_t2].get_ap_attack(index_poki2));
                // switch happens second
                current_trainers[index_t1].pok_switch(index_poki1);
            }

            // checking if anyone won after this specific turn
            if (current_trainers[index_t1].all_pass_out() == true)
            {
                tn2win = true; // trainer 2 wins
            }
            if (current_trainers[index_t2].all_pass_out() == true)
            {
                tn1win = true; // trainer 1 wins
            }
        }

        if(choice_t1==2&&choice_t2==2)//both switch
        {
            current_trainers[index_t1].pok_switch(index_poki1);
            current_trainers[index_t2].pok_switch(index_poki2);
        }

        cout<<"\nDisplaying parties after turn end"<<endl;
        cout<<"Trainer 1 current party:"<<endl;
        current_trainers[index_t1].display_current_party();
        cout<<endl;
        cout<<"Trainer 2 current party:"<<endl;
        current_trainers[index_t2].display_current_party();
        cout<<endl;
        cout<<endl;

        //checking if someone won or not. then exit loop or not
        if(tn1win==true){
            break;
        }
        if(tn2win==true){
            break;
        }
    }

    //battle ends

    if(tn1win==true){
        cout<<"\n"<<current_trainers[index_t1].getTrainerName()<<" Trainer 1 wins!!"<<endl;
        current_trainers[index_t1].awardXP();
    }
    if(tn2win==true){
        cout<<"\n"<<current_trainers[index_t2].getTrainerName()<<" Trainer 2 wins!!"<<endl;
        current_trainers[index_t2].awardXP();
    }
    current_trainers[index_t1].restorehp();
    current_trainers[index_t2].restorehp();
}
void manage_current_party(Trainer *&current_trainers, int &index)
{
    int choice = -1;
    // current party menu display
    while (choice != 4)
    {
        cout << "Current Party Management" << endl;
        cout << "1.View Current party" << endl;
        cout << "2.Add Pokemon to Current party" << endl;
        cout << "3.Remove Pokemon from the Current party" << endl;
        cout << "4.Return to Trainer Menu" << endl;
        cin >> choice;
        if (choice == 1)
        {
            // 1.view current party
            current_trainers[index].display_current_party();
        }
        else if (choice == 2)
        {
            current_trainers[index].add_to_cp();
            // 2.Add Pokemon to current party
        }
        else if (choice == 3)
        {
            // 3.Remove pokemon from current party
            current_trainers[index].remove_from_cp();
        }
    }
    return;
}
Pokemon AddPokemonHelper()
{
    string input_pokemon_name;
    char input_pokemon_type;
    int input_pokemon_level;
    cout << "Enter pokemon name:" << endl;
    cin >> input_pokemon_name;
    cout << "Enter pokemon type(input a character)|| fire(f) water(w) grass(g)" << endl;
    cin >> input_pokemon_type;
    cout << "Enter pokemon level: " << endl;
    cin >> input_pokemon_level;
    Pokemon Pokiobj(input_pokemon_name, input_pokemon_type, input_pokemon_level);
    return Pokiobj;
}
void CreateTrainerHelper(Trainer *&current_trainers, int &_num_trainers)
{
    string name_of_trainer;
    // increasing size dynamically according to req.
    Trainer *temp;
    if (_num_trainers != 1)
    {
        temp = new Trainer[_num_trainers - 1];

        for (int i = 0; i < _num_trainers - 1; i++)
        {
            temp[i] = current_trainers[i];
        }
    }
    // delete [] current_trainers;
    current_trainers = new Trainer[_num_trainers];

    if (_num_trainers != 1)
    {
        for (int i = 0; i < _num_trainers - 1; i++)
        {
            current_trainers[i] = temp[i];
        }
    }

    cout << "Enter trainer's name: " << endl;
    cin >> name_of_trainer;

    current_trainers[_num_trainers - 1].setTrainerName(name_of_trainer);
}
void TrainerMenu(Trainer *&current_trainers, int &_num_trainers)
{

    int tm_choice = 0;
    while (tm_choice != 3)
    {
        cout << "What would you like to do:" << endl;
        cout << "1.Create Trainer" << endl;
        cout << "2.Access a trainer" << endl;
        cout << "3.Exit to Main Menu" << endl;
        cin >> tm_choice;

        if (tm_choice == 1)
        {
            // 1.Create Trainer
            _num_trainers++;
            CreateTrainerHelper(current_trainers, _num_trainers);
        }
        else if (tm_choice == 2)
        // 2.Access Trainer
        {
            if (_num_trainers == 0)
            {
                int ch = 0;
                cout << "No trainers currently exist.\nPress 1 if you want to create one. \nElse press 2 to return to trainer menu." << endl;
                cin >> ch;
                if (ch == 1)
                {
                    _num_trainers++;
                    CreateTrainerHelper(current_trainers, _num_trainers);
                }
            }
            else
            {
                // displaying all current trainers
                cout << "These trainers exist in game currently: " << endl;
                for (int i = 0; i < _num_trainers; i++)
                {
                    cout << i + 1 << ". " << current_trainers[i].getTrainerName() << endl;
                }
                string trainer_name;
                int index_of_trainer_found;
                cout << "Enter the trainer name which you want to access: " << endl;
                cin >> trainer_name;

                for (int i = 0; i < _num_trainers; i++)
                {
                    if (current_trainers[i].getTrainerName() == trainer_name)
                    {
                        index_of_trainer_found = i;
                        break;
                    }
                }

                // trainer accessed now going in trainer name's menu
                int choice = -1;

                while (choice != 4)
                {
                    cout << current_trainers[index_of_trainer_found].getTrainerName() << "'s Menu " << endl;
                    displayTrainerMenu();
                    cin >> choice;

                    if (choice == 1)
                    // 1.Add Pokemon
                    {
                        Pokemon pokobj;
                        pokobj = AddPokemonHelper();
                        current_trainers[index_of_trainer_found].AddPokemon(pokobj);
                        // cout<<"HelOOOOO" << endl;
                    }
                    if (choice == 2)
                    // 2.Display Pokemon
                    {
                        current_trainers[index_of_trainer_found].DisplayPokemon();
                    }
                    if (choice == 3)
                    // 3.Manage current party
                    {
                        manage_current_party(current_trainers, index_of_trainer_found);
                        // redirect to current party management menu
                    }
                    if (choice == 4)
                    {
                        return;
                    }
                }
            }
        }
    }
}

void Game()
{
    int num_trainers = 0;
    Trainer *current_trainers;

    int choice = 0;
    while (choice != 3)
    {
        displayGameMenu();
        cin >> choice;
        if (choice == 1)
        {
            //3.Trainer Menu
            TrainerMenu(current_trainers, num_trainers);
        }
        if (choice == 2)
        {
            // 2.Battle Menu
            if (num_trainers < 2)
            {
                cout << "There must be atleast 2 trainers for a batte to take place!" << endl;
            }
            else
            {
                string t1 = "";
                string t2 = "";
                int index_t1, index_t2 = 0;
                cout << "\nDisplaying all trainers: " << endl;
                for (int i = 0; i < num_trainers; i++)
                {
                    // display all trainers
                    cout << current_trainers[i].getTrainerName()<<endl;
                }
                cout << "\nEnter name of trainer 1: " << endl;
                cin >> t1;
                cout << "\nEnter name of trainer 2: " << endl;
                cin >> t2;
                for (int i = 0; i < num_trainers; i++)
                {
                    if (current_trainers[i].getTrainerName() == t1)
                    {
                        index_t1 = i;
                    }
                }
                for (int i = 0; i < num_trainers; i++)
                {
                    if (current_trainers[i].getTrainerName() == t2)
                    {
                        index_t2 = i;
                    }
                }
                if (current_trainers[index_t1].get_cp_count() == 0 || current_trainers[index_t2].get_cp_count() == 0)
                {
                    if (current_trainers[index_t1].get_cp_count() == 0)
                    {
                        cout << "\nNo trainers in current party of Trainer 1 : " << current_trainers[index_t1].getTrainerName()<<endl;
                    }
                    else
                    {
                        cout << "\nNo trainers in current party of Trainer 2 : " << current_trainers[index_t2].getTrainerName()<<endl;
                    }
                }
                else
                {
                    cout << "Preparing terminal for battle" << endl;
                    cout << "\n\n\n\n"
                         << endl;
                    Battle(current_trainers,index_t1,index_t2);
                }
            }
        }
        if(choice ==3){
            break;
        }
    }
    delete[] current_trainers;
}

int main()
{
    // Trainer ash("Ahmad");
    // Pokemon temp = AddPokemonHelper();
    // Pokemon yoyo("Pikachu",'f',6);
    // ash.AddPokemon(temp);
    // ash + yoyo;
    // // ash.DisplayPokemon();
    // cout<<ash;
    // above lines are for deep testing

    Game();
    return 0;
}
void Trainer::awardXP()
{
    for (int i = 0; i < 6; i++)
    {
        if (current_party[i] != nullptr)
        {
            current_party[i]->setXP(10);
        }
    }
}
void Trainer::restorehp()
{
    for (int i = 0; i < 6; i++)
    {
        if (current_party[i] != nullptr)
        {
            current_party[i]->setPokemonHP(current_party[i]->getc_totalhp());
        }
    }
}
bool Trainer::active_pok_passout(int _index)
{
    if (current_party[_index]->getc_hp() <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Trainer::pok_switch(int &ind)
{
    int ret_index = 0;
    // string pok_name = "";
    bool flag = true;
    if (all_pass_out() == true)
    {
        cout << "\nAll pokemons passed out. Can't switch" << endl;
    }
    else
    {
        while (flag == true)
        {
            display_current_party();
            cout << "\nEnter index of pokemon you want to switch to: " << endl;
            cin >> ret_index;
            ret_index--;
            // ret_index = get_cp_index(pok_name);
            if (current_party[ret_index]->getc_hp() <= 0)
            {
                cout << "\nChosen pokemon hp is 0. Try again." << endl;
            }
            else
            {
                flag = false;
                ind = ret_index;
            }
        }
    }
}
bool Trainer::all_pass_out()
{
    bool ans = true;
    for (int i = 0; i < 6; i++)
    {
        if (current_party[i] != nullptr)
        {
            if (current_party[i]->getc_hp() > 0)
            {
                ans = false;
            }
        }
    }
    return ans;
}
void Trainer::display_current_party()
{
    cout << "\nDisplaying Current Party: " << endl;
    for (int i = 0; i < count_in_current_party; i++)
    {
        if (current_party[i] != nullptr)
        {
            cout << (i+1) <<current_party[i]->getPokemonName() << " ------ Level: " << current_party[i]->getPokemonLevel() << " Current HP: " << current_party[i]->getc_hp() <<endl;
        }
    }
}
void Trainer::remove_from_cp()
{
    int index_removal = 0;
    string poki_name = "";
    cout << "Displaying CURRENT PARTY: " << endl;
    display_current_party();
    cout << "Enter name of the pokemon you want to remove: " << endl;
    cin >> poki_name;
    for (int i = 0; i < 6; i++)
    {
        if (current_party[i] != nullptr)
        {
            if (current_party[i]->getPokemonName() == poki_name)
            {
                index_removal = i;
                break;
            }
        }
    }
    cout << "\nINDEX IS: " << index_removal << endl;
    num_pokemon_owned++;
    if (num_pokemon_owned == 1)
    {
        pokemon_owned = new Pokemon[num_pokemon_owned];
        pokemon_owned[0] = *current_party[index_removal];
    }
    else
    {
        // increasing size of pokemon_owned array
        Pokemon *temp = new Pokemon[num_pokemon_owned];
        for (int i = 0; i < num_pokemon_owned - 1; i++)
        {
            temp[i] = pokemon_owned[i];
        }
        delete[] pokemon_owned;
        pokemon_owned = new Pokemon[num_pokemon_owned];
        for (int i = 0; i < num_pokemon_owned; i++)
        {
            // deep copy
            pokemon_owned[i] = temp[i];
        }
        delete[] temp;
        // ending increase size
        pokemon_owned[num_pokemon_owned - 1] = *current_party[index_removal]; // pokemon added at last index of pokemon_owned
    }
    cout << "Line 206" << endl;
    delete current_party[index_removal];    // freeing memory there
    current_party[index_removal] = nullptr; // that index points to null now
    count_in_current_party--;
    int c = 0;
    Pokemon *temp[6];
    for (int i = 0; i < 6; i++)
    {
        if (current_party[i] != nullptr)
        {
            temp[c] = current_party[i];
            c++;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        current_party[i] = nullptr;
    }
    // copying
    for (int i = 0; i < count_in_current_party; i++)
    {
        current_party[i] = temp[i];
    }
    // delete [] temp;
}
void Trainer::add_to_cp()
{
    string poki_name = "";
    int index_poki_po = 0;
    ;
    // displaying all pok in pokemon_owned
    DisplayPokemon();
    cout << "\nEnter name of pokemon you want to add to current party: " << endl;
    cin >> poki_name;
    for (int i = 0; i < num_pokemon_owned; i++)
    {
        if (pokemon_owned[i].getPokemonName() == poki_name)
        {
            index_poki_po = i;
            break;
        }
    }
    // cout<<"out of for loop"<<index_poki_po<<endl;
    current_party[count_in_current_party] = new Pokemon;
    *current_party[count_in_current_party] = pokemon_owned[index_poki_po];
    count_in_current_party++;
    // cout<<"last line of addtocp"<<endl;

    // removing pokemon from pokemon_owned
    if (num_pokemon_owned == 1)
    {
        delete[] pokemon_owned;
        num_pokemon_owned--;
    }
    else
    {
        Pokemon *temp;
        temp = new Pokemon[num_pokemon_owned - 1];
        int count = 0;
        for (int i = 0; i < num_pokemon_owned; i++)
        {
            if (pokemon_owned[i].getPokemonName() != pokemon_owned[index_poki_po].getPokemonName())
            {
                temp[count] = pokemon_owned[i];
                count++;
            }
        }
        delete[] pokemon_owned;
        num_pokemon_owned--;
        pokemon_owned = new Pokemon[num_pokemon_owned];
        for (int i = 0; i < num_pokemon_owned; i++)
        {
            pokemon_owned[i] = temp[i];
        }
        delete[] temp;
    }
}