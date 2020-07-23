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

Mob gener_mob(const int& tile)
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

void step(Hero& Oleg, const string& direction, int& status)
{
	if (direction == "up") Oleg.y--;
	if (direction == "down") Oleg.y++;
	if (direction == "right") Oleg.x++;
	if (direction == "left") Oleg.x--;
	
	if (Oleg.y < 0) Oleg.y++;
	if (Oleg.x < 0) Oleg.x++;
	if (Oleg.y > 4) Oleg.y--;
	if (Oleg.x > 4) Oleg.x--;
}

void step_log(const int& x, const int& y, const vector<vector<int>>& map)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			if (i == y && j == x)
				cout << "#" << " ";
			else cout << map[i][j] << " ";
		cout << endl;
	}
}

void battle_log_start(string name)
{
	cout << "Oleg vs " << name << endl;
}

void move(Hero& Oleg, const string& extion, int& status, const vector<vector<int>>& map, Mob& bat)
{
	step(Oleg, extion, status);
	step_log(Oleg.x, Oleg.y, map);
	if (getRandomNumber(1, 3) == 1)
	{
		status = 1;
		bat = gener_mob(map[Oleg.y][Oleg.x]);
		battle_log_start(bat.name);
	}

}

void battle_log(int Oleg_hp, const string& bat_name, int bat_hp, int stat)
{
	if (stat == 0)
	{
		cout << "Oleg hp: " << Oleg_hp << endl;
		cout << bat_name << " hp: " << bat_hp << endl;
	}
	if (stat == 1)
	{
		cout << "Oleg win" << endl;
		cout << "Oleg hp: " << Oleg_hp << endl;
	}
	if (stat == 2)
	{
		cout << "Oleg duy" << endl;
	}
}

void battle(Hero& Oleg, Mob& bat, string extion)
{
	if (extion == "atc") bat.hp = bat.hp - Oleg.atc + bat.def;
	if (getRandomNumber(1, bat.time) == 1) Oleg.hp = Oleg.hp - bat.atc + Oleg.def;
}

void war(Hero& Oleg, Mob& bat,const string& extion, int& status,const vector<vector<int>>& map)
{
	battle(Oleg, bat, extion);
	if (bat.hp > 0) battle_log(Oleg.hp, bat.name, bat.hp, 0);
	if (bat.hp <= 0)
	{
		battle_log(Oleg.hp, bat.name, bat.hp, 1);
		step_log(Oleg.x, Oleg.y, map);
		status = 0;
	}
	if (Oleg.hp <= 0) battle_log(Oleg.hp, bat.name, bat.hp, 2);
}

void Game_text(Hero& Oleg, const vector<vector<int>>& map, int& status, Mob& bat)
{	
	string extion;
	cin >> extion;
	if (status == 0 && (extion == "up" || extion == "down" || extion == "right" || extion == "left")) move(Oleg, extion, status, map, bat);
	if (status == 1 && (extion == "atc" || extion == "wait" || extion == "explore")) war(Oleg, bat, extion, status, map);
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	vector<vector<int>> map = generMap();

	Hero Oleg;
	Oleg.x = 1;
	Oleg.y = 4;
	Oleg.hp = 10;
	Oleg.atc = 2;
	Oleg.def = 1;

	int status = 0;
	Mob bat = gener_mob(1);
	step_log(Oleg.x, Oleg.y, map);
	cout << "Oleg " << "Hp: " << Oleg.hp << " Atc: " << Oleg.atc << " Def: " << Oleg.def << " tile: " << map[Oleg.y][Oleg.x] << endl;
	while (Oleg.hp > 0)
	{	
		Game_text(Oleg, map, status, bat);
	}

}

