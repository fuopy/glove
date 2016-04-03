#ifndef _SPAWNER_H
#define _SPAWNER_H

struct Spawner {
	char x;
	char y;
	bool active;
	char spawnDelay;
	char health;
};

void add_spawner(char x, char y);
void update_spawner(Spawner& obj);
void draw_spawner(Spawner &obj);
void destroy_spawner(Spawner& obj);
void damage_spawner(Spawner& obj, short dmg);

#endif
