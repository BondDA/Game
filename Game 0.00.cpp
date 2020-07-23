

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>



using namespace std;

class Hero
{
public:
	int x, y;
	int hp;
	int atc, def;
};
class Mob
{
public:
	string name;
	int hp, atc, def, time;
};

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

vector<vector<int>> generMap()
{
	vector <vector<int>> map;

	for (int i = 0; i < 5; i++)
	{
		map.push_back(vector<int>());

		for (int j = 0; j < 5; j++)
		{
			map[i].push_back(getRandomNumber(1, 6));
		}
	}

	return map;
	
}

Hero step(Hero Oleg)
{
	
	string direction;

	cin >> direction;
	if (direction == "up") Oleg.y--;
	if (direction == "down") Oleg.y++;
	if (direction == "right") Oleg.x++;
	if (direction == "left") Oleg.x--;
	cout << endl;
	
	if (Oleg.y < 0) Oleg.y++;
	if (Oleg.x < 0 ) Oleg.x++;
	if (Oleg.y > 4 ) Oleg.y--;
	if (Oleg.x > 4 ) Oleg.x--;
	
	return Oleg;
}

Mob bat(int tile)
{
	Mob cr;
	if (tile == 1)
	{
		cr.name = "Mouse";
		cr.atc = 1;
		cr.def = 0;
		cr.hp = 3;
		cr.time = 2;
	}
	if (tile == 2)
	{
		cr.name = "lazzy cat";
		cr.atc = 3;
		cr.def = 1;
		cr.hp = 10;
		cr.time = 5;
	}
	if (tile == 3)
	{
		cr.name = "Hob-goblin";
		cr.atc = 5;
		cr.def = 0;
		cr.hp = 2;
		cr.time = 1;
	}
	if (tile == 4)
	{
		cr.name = "gremlin";
		cr.atc = 2;
		cr.def = 1;
		cr.hp = 10;
		cr.time = 3;
	}
	if (tile == 5)
	{
		cr.name = "kapitoshka";
		cr.atc = -1;
		cr.def = 0;
		cr.hp = 1;
		cr.time = 1;
	}
	if (tile == 6)
	{
		cr.name = "lazzy cat";
		cr.atc = 3;
		cr.def = 1;
		cr.hp = 10;
		cr.time = 5;
	}
	return cr;
}

void battle(Hero& Oleg, Mob cr)
{
	string move;
	int raund = 0;
	cout << "Mob hp" << cr.hp << endl;
	while (Oleg.hp > 0 && cr.hp > 0)
	{
		raund++;
		cin >> move;
		if (move == "atc") cr.hp = cr.hp - Oleg.atc + cr.def;
		if (raund % cr.time == 0) Oleg.hp = Oleg.hp - cr.atc + Oleg.def;
		cout << "Oleg hp: " << Oleg.hp;
		cout << "Mob hp" << cr.hp <<endl;
	}
	if (Oleg.hp <= 0) Oleg.atc = 0, Oleg.def = 0;
}

Hero battle_log(Hero& Oleg, const vector<vector<int>> &map)
{
	Mob cr = bat(map[Oleg.y][Oleg.x]);
	cout << "Oleg vs " << cr.name << endl;
	battle(Oleg, cr);
	return Oleg;
}


void duy()
{
	while (true);
}
void Game(vector<vector<int>> map, Hero Oleg)
{
	

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			if (i == Oleg.y && j == Oleg.x)
				cout << "#" << " ";
			else cout << map[i][j] << " ";
		cout << endl;
	}
	cout << "Oleg " << "Hp: " << Oleg.hp << " Atc: " << Oleg.atc << " Def: " << Oleg.def << " tile: " << map[Oleg.y][Oleg.x] << endl;
	if (Oleg.hp < 0)
	{
		cout << "##### YOU LOSE #####";
		duy();
	}

	Oleg = step(Oleg);
	if (getRandomNumber(1, 3) == 1) battle_log(Oleg, map);
	 
	Game(map, Oleg);
		
}




int main()
{
	srand(static_cast<unsigned int>(time(0)));

	vector<vector<int>> map = generMap();
    
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << map[i][j] <<" ";
		cout << endl;
	}
	/*/

	Hero Oleg ;
	Oleg.x = 1;
	Oleg.y = 4;
	Oleg.hp = 10;
	Oleg.atc = 2;
	Oleg.def = 1;

	Game (map, Oleg);


}
