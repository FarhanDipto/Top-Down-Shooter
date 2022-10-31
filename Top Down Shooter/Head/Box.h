typedef struct Player Player;
typedef struct Wall Wall;
typedef struct Foot Foot;
typedef struct Bullet Bullet;
typedef struct Enemy Enemy;
typedef struct Enemy_Bullet Enemy_Bullet;
typedef struct Map Map;
typedef struct Button Button;
typedef struct Health Health;
typedef struct Menu Menu;

struct Menu
{
	int x;
	int y;
	int h;
	int w;

	Menu()
	{
		w = 1280;
		h = 720;
	}

	Menu(int _x, int _y)
	{
		x = _x;
		y = _y;
		w = 1280;
		h = 720;
	}
};

struct Health
{
	int x;
	int y;
	int w;
	int h;
	int a;
	int b;

	bool picked;

	int heal;

	Health()
	{

	}
	Health(int _x, int _y)
	{
		x = _x;
		y = _y;

		w = 50;
		h = 50;

		heal = 25;

		picked = false;

	}
};

struct Button
{
	int x;
	int y;
	int h;
	int w;
	bool hover;

	Button(int _x, int _y)
	{
		x = _x;
		y = _y;
		w = 429;
		h = 54;
		hover = false;
	}


};

struct Map
{	
	int x;
	int y;
	int a;
	int b;

	Map(int _x, int _y)
	{
		x = _x;
		y = _y;

	}

};
struct Foot
{
	int fx;
	int fy;
	int fw;
	int fh;

	Foot()
	{
		fw = 86;
		fh = 62;
	}
};

struct Wall
{
	int x;
	int y;
	int h;
	int w;
	int a;
	int b;

	Wall()
	{

	}

	Wall(int _x, int _y, int wi, int hi)
	{
		x = _x;
		y = _y;
		h = hi;
		w = wi;
	}
};

struct Player
{
	
	int x;
	int y;
	int h;
	int w;

	int a;
	int b;

	int hitbox_x;
	int hitbox_y;
	int hitbox_h;
	int hitbox_w;

	Foot ft;

	bool canShoot;
	bool Gameover;
	int bullet_index;

	double angle;

	int health;

	int clock_start;
	int clock_end;
	int score;

	char name[100];
	int name_index;
	int enemy_kiiled;

	//Upper body



	Player(int _x, int _y)
	{
		x = _x - 80;
		y = _y - 54;

		hitbox_x = _x - 80 + 22;
		hitbox_y = _y - 54 + 14;
		hitbox_w = 74;
		hitbox_h = 74;

		h = 103;
		w = 156;



		ft.fx = x + (w / 2);
		ft.fy = y + (h / 2);
		canShoot = false;
		bullet_index = 0;

		health = 100;
		Gameover = false;
		name_index = 0;
		enemy_kiiled = 0;
	}

	bool wal_Col(Wall wa)
	{
		if((hitbox_x + hitbox_w > wa.x && hitbox_x < wa.x + wa.w) && (hitbox_y + hitbox_h > wa.y && hitbox_y < wa.y + wa.h))
		{
				return true;
		}
		return false;
	}
	


	void Angle_count(int mx, int my)
	{
		int DiffX = mx - x;
		int DiffY = my - y;

		if (DiffX > 0 && DiffY > 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			angle = temp;
		}
		else if (DiffY > 0 && DiffX < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			temp += 180.0;
			angle = temp;
		}
		else if (DiffY < 0 && DiffX < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			temp += 180;
			angle = temp;
		}
		else if (DiffX > 0 && DiffY < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			angle = temp;
		}
		else if (DiffY == 0 && DiffX > 0) angle = 0;
		else if (DiffX == 0 && DiffY > 0) angle = 90;
		else if (DiffY == 0 && DiffX < 0) angle = 180;
		else if (DiffY < 0 && DiffX == 0) angle = 270;
	}

	void player_health_pickup(Health &h)
	{
		if((hitbox_x + hitbox_w > h.x && hitbox_x < h.x + h.w) && (hitbox_y + hitbox_h > h.y && hitbox_y < h.y + h.h))
		{
			health += h.heal;
			h.x = -1000;
			h.y = -1000;
			h.w = 0;
			h.h = 0;


			if(health >= 100)
			{
				health = 100;
				
			}
		}
	}

	
	
};

struct Enemy_Bullet {
    int x;
    int y;
    int velocity;
	double angle;


    struct Enemy_Bullet () {
        x = 10000;
        y = 10000;
        velocity = 25;
		angle = 45;
    }

    void AddVelocity () {
        x += cos (angle * (acos(-1.0) / 180)) * velocity;
        y += sin (angle * (acos(-1.0) / 180)) * velocity;

        if (x >= 10000) x = 10000;
        if (y >= 10000) y = 10000;
    }

	void player_hit(Player &p)
	{
		if((x > p.hitbox_x && x < p.hitbox_x + p.hitbox_w) && (y + 2 > p.hitbox_y && y < p.hitbox_y + p.hitbox_h))
		{
			p.health -= 3;
			x = 10000;
			y = 10000;
			angle = 45;

			printf("%d\n", p.health);
		}

		
	}

};

struct Enemy
{
	int x;
	int y;
	int w;
	int h;

	int a;
	int b;

	int s_x;
	int s_y;
	int s_w;
	int s_h;

	int s_a;
	int s_b;

	int health;

	double shoot_angle;

	bool shoot;
	bool dead;
	bool sound;
	int bullet_index;
	Enemy_Bullet *eb;

	Enemy()
	{
		h = 103;
		w = 156;
		shoot_angle = 90;
		bullet_index = 0;

		health = 100;

		eb = new struct Enemy_Bullet[50];
		sound = true;
	}

	Enemy(int _x, int _y, int _s_x, int _s_y, int _s_w, int _s_h)
	{
		x = _x;
		y = _y;
		h = 103;
		w = 156;

		s_x = _s_x;
		s_y = _s_y;
		s_w = _s_w;
		s_h = _s_h;
		shoot_angle = 90;
		bullet_index = 0;

		health = 100;
		dead = false;

		eb = new struct Enemy_Bullet[50];
	}

	void Angle_count(int mx, int my)
	{
		int DiffX = mx - x;
		int DiffY = my - y;

		if (DiffX > 0 && DiffY > 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			shoot_angle = temp;
		}
		else if (DiffY > 0 && DiffX < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			temp += 180.0;
			shoot_angle = temp;
		}
		else if (DiffY < 0 && DiffX < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			temp += 180;
			shoot_angle = temp;
		}
		else if (DiffX > 0 && DiffY < 0)
		{
			double temp = atan (((double)DiffY / (double) DiffX));
			temp = temp * (180.0 / acos (-1.0));
			shoot_angle = temp;
		}
		else if (DiffY == 0 && DiffX > 0) shoot_angle = 0;
		else if (DiffX == 0 && DiffY > 0) shoot_angle = 90;
		else if (DiffY == 0 && DiffX < 0) shoot_angle = 180;
		else if (DiffY < 0 && DiffX == 0) shoot_angle = 270;
	}

	bool player_enemy_dit(Player &p)
	{
		if((p.hitbox_x + p.hitbox_w > s_x && p.hitbox_x < s_x + s_w) && (p.hitbox_y + p.hitbox_h > s_y && p.hitbox_y < s_y + s_h))
		{
				return true;
		}
		return false;
	}


};

struct Bullet {
    int x;
    int y;
    int velocity;
	double angle;

    Bullet () {
        x = 10000;
        y = 10000;
        velocity = 25;
		angle = 45;

    }

    void AddVelocity () {
        x += cos (angle * (acos(-1.0) / 180)) * velocity;
        y += sin (angle * (acos(-1.0) / 180)) * velocity;

        if (x >= 10000) x = 10000;
        if (y >= 10000) y = 10000;
    }

	void enemy_hit(Enemy &e, Player &p)
	{
		if((x > e.x && x < e.x + e.w) && (y + 2 > e.y && y < e.y + e.h))
		{
			e.health -= 20;
			x = 10000;
			y = 10000;
			angle = 45;

			if(e.health <= 0)
			{
				e.x = -1000;
				e.y = -1000;

				e.s_x = -10;
				e.s_y = -10;
				e.s_h = -10;
				e.s_w = -10;
				e.dead = true;

				p.enemy_kiiled++;
			}
		}
	}

	void Wall_hit(Wall &w)
	{
		if((x > w.x && x < w.x + w.w) && (y + 2 > w.y && y < w.y + w.h))
		{
			x = 10000;
			y = 10000;
			angle = 45;
		}
	}
};
