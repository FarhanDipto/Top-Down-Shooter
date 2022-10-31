#include "Head/iGraphics.h"
#include "Head/bass.h"
#include <Math.h>
#include <string.h>
#include <time.h>
#include "Head/Box.h"
#include "Head/Cust_func.h"


HSTREAM gun_fire_sound;
HSTREAM reload_sound;
HSTREAM kill_sound;
HSTREAM menu_sound;
HSTREAM first_level_sound;
HSTREAM boss_level_sound;
HSTREAM gameover_sound;


int seen = 0;
int menu[11];
int ins[3];
int credits[4];
int cx = 917,cy = -806;
int gameover;
int enemy_killed = 0;


char score[20];

int bullet_show[32];
Button ins_b_back(20, 624);
Button cerdits_b_back(20, 624);
Button end_seen_b(20,624);

Button highscore_b_back(20, 624);


Button play_b(0, 222);
Button ins_b(0, 159);
Button credits_b(0, 95);
Button exit_b(0, 32);
Button highscore_b(500, 32);

struct Menu ch[6];
int back[8]; 

Map m(0, 0);
Player p(750, 450);

int health[20];
int a,b;
int bg;
int end_seen;

int ft_d_stand, ft_d[20], ft_d_index = 0;
bool d_stand = true;
int ft_a_stand, ft_a[20], ft_a_index = 0;
bool a_stand = true;
int ft_w_stand, ft_w[20], ft_w_index = 0;
bool w_stand = true;
int ft_s_stand, ft_s[20], ft_s_index = 0;
bool s_stand = true;
int w_standcounter = 0, a_standcounter = 0, s_standcounter = 0, d_standcounter = 0;
int bd_stand;
int enemy_image;

int reload_index = 0, reload_counter = 0, reload_png[20];
bool reload = false;
Bullet *bullet = new struct Bullet[30];
int bullet_image;

struct Enemy enemy[17];
struct Wall wall[45];
struct Health health_one[5];
int heal_image;
int high_bg;

void sound_load()
{
	gun_fire_sound = BASS_StreamCreateFile(false, "sounds\\gun_fire_sound.mp3", 0, 0, BASS_SAMPLE_MONO);
	reload_sound = BASS_StreamCreateFile(false, "sounds\\reload_sound.mp3", 0, 0, BASS_SAMPLE_MONO);
	kill_sound = BASS_StreamCreateFile(false, "sounds\\kill_sound.mp3", 0, 0, BASS_SAMPLE_MONO);
	menu_sound = BASS_StreamCreateFile(false, "sounds\\menu_sound.mp3", 0, 0, BASS_SAMPLE_LOOP);
	first_level_sound = BASS_StreamCreateFile(false, "sounds\\first_level_sound.mp3", 0, 0, BASS_SAMPLE_LOOP);
	boss_level_sound = BASS_StreamCreateFile(false, "sounds\\boss_level_sound.mp3", 0, 0, BASS_SAMPLE_LOOP);
	gameover_sound = BASS_StreamCreateFile(false, "sounds\\gameover_sound.mp3", 0, 0, BASS_SAMPLE_LOOP);
}

void set_health_axis()
{
	health_one[0] = Health(1367, 827);

	health_one[1] = Health(774, 1467);

	health_one[2] = Health(1988, 1445);

	health_one[3] = Health(2255, 428);

	health_one[4] = Health(2286, 1600);

}
void setEnemyAxis()
{
	enemy[0] = Enemy(903, 612, 873, 594, 220, 400);
	enemy[1] = Enemy(668, 1411, 683, 1105, 150, 404);
	enemy[2] = Enemy(693, 1147, 683, 1105, 680, 212);

	enemy[3] = Enemy(903, 1614, 881, 1372, 434, 367);
	enemy[4] = Enemy(923, 1391, 881, 1372, 434, 367);

	enemy[5] = Enemy(1666, 1385, 1400, 1372, 434, 367);
	enemy[6] = Enemy(1505, 1494, 1400, 1372, 434, 367);
	enemy[7] = Enemy(1666, 1613, 1400, 1372, 434, 367);

	enemy[8] = Enemy(2270 + 260, 1391, 2213, 1340, 455, 455);
	enemy[9] = Enemy(2270 + 260, 1629 + 50, 2213, 1340, 455, 455);

	enemy[10] = Enemy(2976 + 50, 1622 - 220, 2731, 1340, 455, 455);

	enemy[11] = Enemy(2981, 1126, 2723 - 250, 1069, 457, 212);

	enemy[12] = Enemy(2976 - 90, 566, 2917, 540, 263, 442);
	enemy[13] = Enemy(2976 - 90, 878, 2917, 540, 263, 442);

	enemy[14] = Enemy(1840, 448, 1790, 397, 355, 455 + 100);
	enemy[15] = Enemy(2246, 540, 2050, 397, 532, 481 + 100);
	enemy[16] = Enemy(2657, 423, 2503, 397, 355, 455 + 100);

}
void set_wall_cordinate()
{
	wall[0] = Wall(855, 580, 33, 525);
	wall[1] = Wall(855, 580, 575, 16);
	wall[2] = Wall(855, 860, 46, 9);
	wall[3] = Wall(1040, 860, 144, 9);
	wall[4] = Wall(1167, 580, 18, 319);
	wall[5] = Wall(1167, 1069, 18, 36);
	wall[6] = Wall(1314, 580, 18, 37);
	wall[7] = Wall(1314, 787, 18, 82);
	wall[8] = Wall(1314, 808, 448, 9);
	wall[9] = Wall(1314, 1038, 18, 67);
	wall[10] = Wall(1397, 557, 17, 38);
	wall[11] = Wall(1397, 360, 17, 28);
	wall[12] = Wall(1397, 360, 204, 13);
	wall[13] = Wall(1587, 360, 14, 236);
	wall[14] = Wall(1729, 360, 33, 505);
	wall[15] = Wall(1729, 360, 1162, 21);
	wall[16] = Wall(1570, 580, 192, 16);
	wall[17] = Wall(1729, 1035, 33, 70);
	wall[18] = Wall(634, 1083, 1400, 22);
	wall[19] = Wall(634, 1083, 33, 457);
	wall[20] = Wall(634, 1519, 254, 21);
	wall[21] = Wall(1828, 1548, 397, 21);
	wall[22] = Wall(855, 1733, 1006, 21);
	wall[23] = Wall(2192, 1784, 1008, 21);
	wall[24] = Wall(2650, 1659, 18, 147);
	wall[25] = Wall(1349, 1699, 18, 54);
	wall[26] = Wall(634, 1342, 57, 21);
	wall[27] = Wall(831, 1342, 222, 21);
	wall[28] = Wall(855, 1342, 33, 412);
	wall[29] = Wall(1193, 1342, 764, 21);
	wall[30] = Wall(1349, 1342, 18, 188);
	wall[31] = Wall(1828, 1342, 33, 412);
	wall[32] = Wall(2097, 1342, 779, 21);
	wall[33] = Wall(2192, 1342, 33, 463);
	wall[34] = Wall(2650, 1342, 18, 157);
	wall[35] = Wall(2997, 1342, 196, 21);
	wall[36] = Wall(2330, 976, 870, 28);
	wall[37] = Wall(2856, 818, 36, 186);
	wall[38] = Wall(2856, 360, 36, 288);
	wall[39] = Wall(2856, 521, 344, 21);
	wall[40] = Wall(3167, 521, 33, 1284);
	wall[41] = Wall(0, 0, 3840, 360);
	wall[42] = Wall(0, 0, 640, 2160);
	wall[43] = Wall(3200, 0, 640, 2160);
	wall[44] = Wall(0, 1800, 3840, 360);

}
void wall_animation()
{
	iSetColor(86, 86, 86);
	for(int i = 0; i < 41; i++)
	{
		iFilledRectangle(wall[i].x,wall[i].y, wall[i].w, wall[i].h);
	}
}
void Fire() 
{
    for (int i = 0; i < 30; i++) 
	{
        bullet[i].AddVelocity();
	}

	for(int i = 0; i < 17; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			enemy[i].eb[j].AddVelocity();
		}
	}

}
void enemyFire()
{


	for(int i = 0; i < 17; i++)
	{
		if(enemy[i].player_enemy_dit(p) && enemy[i].shoot == true)
		{
			enemy[i].shoot = false;
			enemy[i].Angle_count(p.x, p.y);

			enemy[i].eb[enemy[i].bullet_index].angle = enemy[i].shoot_angle;

			enemy[i].eb[enemy[i].bullet_index].x = enemy[i].x + enemy[i].w / 2 - 20;
			enemy[i].eb[enemy[i].bullet_index].y = enemy[i].y + enemy[i].h / 2 - 11;

			enemy[i].bullet_index++;

			if(enemy[i].bullet_index == 50)
				enemy[i].bullet_index = 0;
		}
	}
}
void Fire_Delay() 
{
    p.canShoot = true;
}
void Enemy_Fire_delay() 
{
	for(int i = 0; i < 17; i++)
	{
		enemy[i].shoot = true;
	}
}

void back1_change()
{
	ch[0].x += 1;

	if(ch[0].x >= 1280)
		ch[0].x = -1280;
}
void back2_change()
{
	ch[1].x += 1;

	if(ch[1].x >= 1280)
		ch[1].x = -1280;
}
void back3_change()
{
	ch[2].x += 1;

	if(ch[2].x >= 1280)
		ch[2].x = -1280;
}
void back4_change()
{
	ch[3].x += 1;

	if(ch[3].x >= 1280)
		ch[3].x = -1280;
}
void back5_change()
{
	ch[4].x += 1;

	if(ch[4].x >= 1280)
		ch[4].x = -1280;
}

void keyboardInput(unsigned char key)
{
	m.a = m.x;
	m.b = m.y;
	for(int i = 0; i < 45; i++)
	{
		wall[i].a = wall[i].x;
		wall[i].b = wall[i].y;
	}
	for(int i = 0; i < 17; i++)
	{
		enemy[i].a = enemy[i].x;
		enemy[i].s_a = enemy[i].s_x;
		enemy[i].b = enemy[i].y;
		enemy[i].s_b = enemy[i].s_y;
	}
	for(int i = 0; i < 5; i++)
	{
		health_one[i].a = health_one[i].x;
		health_one[i].b = health_one[i].y;
	}

	if(key == 'w')
	{
		m.y -= 5;
		for(int i = 0; i < 45; i++)
		{
			wall[i].y -=5;
		}

		for(int i = 0; i < 17; i++)
		{
			enemy[i].y -= 5;
			enemy[i].s_y -= 5;
		}
		for(int i = 0; i < 5; i++)
		{
			health_one[i].y -= 5;
		}
		ft_w_index++;

		if(ft_w_index >= 20) 
			ft_w_index = 0;

		w_stand =	false;
		
	}

	if(key == 's')
	{
		m.y += 5;
		for(int i = 0; i < 45; i++)
		{
			wall[i].y +=5;
		}

		for(int i = 0; i < 17; i++)
		{
			enemy[i].y += 5;
			enemy[i].s_y += 5;
		}
		for(int i = 0; i < 5; i++)
		{
			health_one[i].y += 5;
		}
		ft_s_index++;

		if(ft_s_index >= 20)
			ft_s_index = 0;

		s_stand =	false;
	}

	if(key == 'd')
	{
		m.x -= 5;
		for(int i = 0; i < 45; i++)
		{
			wall[i].x -=5;
		}

		for(int i = 0; i < 17; i++)
		{
			enemy[i].x -= 5;
			enemy[i].s_x -= 5;
		}
		for(int i = 0; i < 5; i++)
		{
			health_one[i].x -= 5;
		}
		ft_d_index++;

		if(ft_d_index >= 20)
			ft_d_index = 0;

		d_stand =	false;
	}

	if(key == 'a')
	{
		m.x += 5;
		for(int i = 0; i < 45; i++)
		{
			wall[i].x +=5;
		}

		for(int i = 0; i < 17; i++)
		{
			enemy[i].x += 5;
			enemy[i].s_x += 5;
		}
		for(int i = 0; i < 5; i++)
		{
			health_one[i].x += 5;
		}
		ft_a_index++;

		if(ft_a_index >= 20)
			ft_a_index = 0;

		a_stand =	false;
	}

	if(key == 'r')
	{
		BASS_ChannelPlay(reload_sound, true);
		reload = true;
		p.bullet_index = 0;
	}

	for(int i = 0; i < 45; i++)
	{
		if(p.wal_Col(wall[i]))
		{
			m.x = m.a;
			m.y = m.b;
			for(int i = 0; i < 45; i++)
			{
				wall[i].x = wall[i].a;
				wall[i].y = wall[i].b;
			}
			for(int i = 0; i < 17; i++)
			{
				enemy[i].x = enemy[i].a;
				enemy[i].s_x = enemy[i].s_a;
				enemy[i].y = enemy[i].b;
				enemy[i].s_y = enemy[i].s_b;
			}
			for(int i = 0; i < 5; i++)
			{
				health_one[i].x = health_one[i].a;
				health_one[i].y = health_one[i].b;
			}
		}
	}
}

void playerMouseInput(int button, int state, int mx, int my)
{
	if(seen == 1)
	{
		if (button == 0 && p.canShoot == true && reload == false) 
		{
			if(p.bullet_index < 30)
				BASS_ChannelPlay(gun_fire_sound, true);

			//BASS_ChannelStop(gun_fire_sound);

			p.canShoot = false;
			bullet[p.bullet_index].angle = p.angle;

			bullet[p.bullet_index].x = p.x + p.w / 2 - 20;
			bullet[p.bullet_index].y = p.y + p.h / 2 - 11;

			p.bullet_index++;

			
		}
	}
}
void menu_button_hover(int mx, int my)
{
	if(seen == 0)
	{
		if(button_hover(mx, my, play_b))
			play_b.hover = true;
		else
			play_b.hover = false;

		if(button_hover(mx, my, ins_b))
			ins_b.hover = true;
		else
			ins_b.hover = false;

		if(button_hover(mx, my, credits_b))
			credits_b.hover = true;
		else
			credits_b.hover = false;

		if(button_hover(mx, my, exit_b))
			exit_b.hover = true;
		else
			exit_b.hover = false;

		if(button_hover(mx, my, highscore_b))
			highscore_b.hover = true;
		else
			highscore_b.hover = false;

	}
	
	else if(seen == 3)
	{
		if(button_hover(mx, my, end_seen_b))
			end_seen_b.hover = true;
		else
			end_seen_b.hover = false;
	}

	else if(seen == 5)
	{
		if(button_hover(mx, my, highscore_b_back))
			highscore_b_back.hover = true;
		else
			highscore_b_back.hover = false;
	}

	else if(seen == 7)
	{
		if(button_hover(mx, my, ins_b_back))
			ins_b_back.hover = true;
		else
			ins_b_back.hover = false;
	}
	else if(seen == 8)
	{
		if(button_hover(mx, my, cerdits_b_back))
			cerdits_b_back.hover = true;
		else
			cerdits_b_back.hover = false;
	}
}

void heal_animation()
{
	for(int i = 0; i < 5; i++)
	{
		iShowImage(health_one[i].x, health_one[i].y, health_one[i].w, health_one[i].h, heal_image);
		p.player_health_pickup(health_one[i]);
	}
}
void Player_animation()
{
	if(d_stand == false)
	{
		d_standcounter++;
		iShowImage(p.x + p.w /2 - p.ft.fw / 2 - 21, p.y + p.h / 2- p.ft.fh / 2 - 12, p.ft.fw, p.ft.fh, ft_d[ft_d_index]);
		if(d_standcounter >= 200)
		{
			d_stand = true;
			d_standcounter = 0;
		}
	}
	else if(a_stand == false)
	{
		a_standcounter++;
		iShowImage(p.x + p.w /2 - p.ft.fw / 2 - 21, p.y + p.h / 2- p.ft.fh / 2 - 12, p.ft.fw, p.ft.fh, ft_a[ft_a_index]);
		if(a_standcounter >= 200)
		{
			a_stand = true;
			a_standcounter = 0;
		}
	}
	else if(w_stand == false)
	{
		w_standcounter++;
		iShowImage(p.x + p.w /2 - p.ft.fw / 2 - 21, p.y + p.h / 2- p.ft.fh / 2 - 12, p.ft.fw, p.ft.fh, ft_w[ft_w_index]);
		if(w_standcounter >= 200)
		{
			w_stand = true;
			w_standcounter = 0;
		}
	}
	else if(s_stand == false)
	{
		s_standcounter++;
		iShowImage(p.x + p.w /2 - p.ft.fw / 2 - 21, p.y + p.h / 2- p.ft.fh / 2 - 12, p.ft.fw, p.ft.fh, ft_s[ft_s_index]);
		if(s_standcounter >= 200)
		{
			s_stand = true;
			s_standcounter = 0;
		}
	}
	if(reload == true)
	{
		iRotate(p.x + p.w / 2 - 20, p.y + p.h / 2 - 11, p.angle);
		iShowImage(p.x, p.y, p.w, p.h, reload_png[reload_index]);
		iUnRotate();
	}

	else if(reload == false)
	{
		iRotate(p.x + p.w / 2 - 20, p.y + p.h / 2 - 11, p.angle);
		iShowImage(p.x, p.y, p.w, p.h, reload_png[0]);
		iUnRotate();
	}
}
void Bullet_animation()
{
	if(p.bullet_index <= 30)
	{
		for (int i = 0; i < 30; i++) 
		{
        
			iRotate(bullet[i].x, bullet[i].y , bullet[i].angle);
			iShowImage(bullet[i].x, bullet[i].y - 13, 15, 8, bullet_image);
			iUnRotate();

			for(int j = 0; j < 17; j++)
			{
				bullet[i].enemy_hit(enemy[j], p);
				

			}

			int count = 0;
			for(int j = 0; j < 17; j++)
			{
				if(enemy[j].dead && enemy[j].sound)
				{
					BASS_ChannelPlay(kill_sound, false);
					enemy[j].sound = false;
				}
				
			}

			if(p.enemy_kiiled == 17)
			{
				BASS_ChannelStop(first_level_sound);
				p.clock_end = clock();
				p.score = (p.clock_end - p.clock_start)/1000;
				BASS_ChannelPlay(boss_level_sound, false);
				seen = 3;
			}

			for(int k = 0; k < 41; k++)
				bullet[i].Wall_hit(wall[k]);
		}
	}

	for(int j = 0; j < 17; j++)
	{
		for(int i = 0; i < 50; i++)
		{
			iRotate(enemy[j].eb[i].x, enemy[j].eb[i].y , enemy[j].eb[i].angle);
			iShowImage(enemy[j].eb[i].x, enemy[j].eb[i].y - 13, 15, 8, bullet_image);
			iUnRotate();

			enemy[j].eb[i].player_hit(p);
			
		}
	}


}
void reload_animation()
{
	if(reload == true)
	{
		reload_index++;

		if(reload_index > 19)
		{
			reload = false;
			reload_index = 0;
		}
	}
	
}
void enemyBullet_animation()
{
	for(int i = 0; i < 17; i++)
	{
		iRotate(enemy[i].x + enemy[i].w / 2 - 20, enemy[i].y + enemy[i].h / 2 - 11, enemy[i].shoot_angle);
		iShowImage(enemy[i].x , enemy[i].y, enemy[i].w, enemy[i].h, enemy_image);;
		iUnRotate();
	}
}
void show_menu()
{
	iShowImage(0, 0, 1280, 720, menu[0]);

	iShowImage(ch[0].x, ch[0].y, ch[0].w, ch[0].h, back[2]);
	iShowImage(ch[1].x, ch[1].y, ch[1].w, ch[1].h, back[3]);
	iShowImage(690, 0, 311, 658, back[0]);

	iShowImage(ch[2].x, ch[2].y, ch[2].w, ch[2].h, back[4]);
	iShowImage(ch[3].x, ch[3].y, ch[3].w, ch[3].h, back[5]);
	iShowImage(ch[4].x, ch[4].y, ch[4].w, ch[4].h, back[6]);

	
	iShowImage(690, 253, 558, 94, back[1]);

		if(play_b.hover)
			iShowImage(play_b.x, play_b.y, play_b.w, play_b.h, menu[2]);
		else
			iShowImage(play_b.x, play_b.y, play_b.w, play_b.h, menu[1]);

		if(ins_b.hover)
			iShowImage(ins_b.x, ins_b.y, ins_b.w, ins_b.h, menu[4]);
		else
			iShowImage(ins_b.x, ins_b.y, ins_b.w, ins_b.h, menu[3]);

		if(credits_b.hover)
			iShowImage(credits_b.x, credits_b.y, credits_b.w, credits_b.h, menu[6]);
		else
			iShowImage(credits_b.x, credits_b.y, credits_b.w, credits_b.h, menu[5]);

		if(exit_b.hover)
			iShowImage(exit_b.x, exit_b.y, exit_b.w, exit_b.h, menu[8]);
		else
			iShowImage(exit_b.x, exit_b.y, exit_b.w, exit_b.h, menu[7]);

		if(highscore_b.hover)
			iShowImage(highscore_b.x, highscore_b.y, highscore_b.w, highscore_b.h, menu[10]);
		else
			iShowImage(highscore_b.x, highscore_b.y, highscore_b.w, highscore_b.h, menu[9]);
}
void health_animation()
{
	if(p.health <= 100 && p.health >= 96)
		iShowImage(20, 20, 402, 36, health[19]);

	else if(p.health <= 95 && p.health >= 91)
		iShowImage(20, 20, 402, 36, health[18]);

	else if(p.health <= 90 && p.health >= 86)
		iShowImage(20, 20, 402, 36, health[17]);

	else if(p.health <= 85 && p.health >= 81)
		iShowImage(20, 20, 402, 36, health[16]);

	else if(p.health <= 80 && p.health >= 76)
		iShowImage(20, 20, 402, 36, health[15]);

	else if(p.health <= 75 && p.health >= 71)
		iShowImage(20, 20, 402, 36, health[14]);

	else if(p.health <= 70 && p.health >= 66)
		iShowImage(20, 20, 402, 36, health[13]);

	else if(p.health <= 65 && p.health >= 61)
		iShowImage(20, 20, 402, 36, health[12]);

	else if(p.health <= 60 && p.health >= 56)
		iShowImage(20, 20, 402, 36, health[11]);

	else if(p.health <= 55 && p.health >= 51)
		iShowImage(20, 20, 402, 36, health[10]);

	else if(p.health <= 50 && p.health >= 46)
		iShowImage(20, 20, 402, 36, health[9]);

	else if(p.health <= 45 && p.health >= 41)
		iShowImage(20, 20, 402, 36, health[8]);

	else if(p.health <= 40 && p.health >= 36)
		iShowImage(20, 20, 402, 36, health[7]);

	else if(p.health <= 35 && p.health >= 31)
		iShowImage(20, 20, 402, 36, health[6]);

	else if(p.health <= 30 && p.health >= 26)
		iShowImage(20, 20, 402, 36, health[5]);

	else if(p.health <= 25 && p.health >= 21)
		iShowImage(20, 20, 402, 36, health[4]);

	else if(p.health <= 20 && p.health >= 16)
		iShowImage(20, 20, 402, 36, health[3]);

	else if(p.health <= 15 && p.health >= 11)
		iShowImage(20, 20, 402, 36, health[2]);

	else if(p.health <= 10 && p.health >= 6)
		iShowImage(20, 20, 402, 36, health[1]);

	else if(p.health <= 5)
		iShowImage(20, 20, 402, 36, health[0]);
}
void show_ins()
{
	iShowImage(0, 0, 1280, 720, ins[0]);

	if(ins_b_back.hover)
		iShowImage(ins_b_back.x, ins_b_back.y, ins_b_back.w, ins_b_back.h, ins[2]);

	else
		iShowImage(ins_b_back.x, ins_b_back.y, ins_b_back.w, ins_b_back.h, ins[1]);
}
void show_credits()
{
	iShowImage(0, 0, 1280, 720, credits[0]);
	iShowImage(cx, cy, 357, 806, credits[4]);


	if(cerdits_b_back.hover)
		iShowImage(cerdits_b_back.x, cerdits_b_back.y, cerdits_b_back.w, cerdits_b_back.h, credits[2]);

	else
		iShowImage(cerdits_b_back.x, cerdits_b_back.y, cerdits_b_back.w, cerdits_b_back.h, credits[1]);
}
void credits_animation()
{
	if(seen == 8)
	{
		cy += 2;
	
		if(cy >= 720)
			cy = -806;
	}
}
void show_gameover()
{
	iShowImage(0, 0, 1280, 720, gameover);

	p.health = 100;
	p.x = 750 - 80 + 22;
	p.y = 450 - 54 + 14;
	p.bullet_index = 0;

	for(int i = 0; i < 17; i++)
	{
		enemy[i].health = 100;
		enemy[i].dead = false;
	}


	m.x = 0;
	m.y = 0;
	health_one[0] = Health(1367, 827);
	health_one[1] = Health(774, 1467);
	health_one[2] = Health(1988, 1445);
	health_one[3] = Health(2255, 428);
	health_one[4] = Health(2286, 1600);
	wall[0] = Wall(855, 580, 33, 525);
	wall[1] = Wall(855, 580, 575, 16);
	wall[2] = Wall(855, 860, 46, 9);
	wall[3] = Wall(1040, 860, 144, 9);
	wall[4] = Wall(1167, 580, 18, 319);
	wall[5] = Wall(1167, 1069, 18, 36);
	wall[6] = Wall(1314, 580, 18, 37);
	wall[7] = Wall(1314, 787, 18, 82);
	wall[8] = Wall(1314, 808, 448, 9);
	wall[9] = Wall(1314, 1038, 18, 67);
	wall[10] = Wall(1397, 557, 17, 38);
	wall[11] = Wall(1397, 360, 17, 28);
	wall[12] = Wall(1397, 360, 204, 13);
	wall[13] = Wall(1587, 360, 14, 236);
	wall[14] = Wall(1729, 360, 33, 505);
	wall[15] = Wall(1729, 360, 1162, 21);
	wall[16] = Wall(1570, 580, 192, 16);
	wall[17] = Wall(1729, 1035, 33, 70);
	wall[18] = Wall(634, 1083, 1400, 22);
	wall[19] = Wall(634, 1083, 33, 457);
	wall[20] = Wall(634, 1519, 254, 21);
	wall[21] = Wall(1828, 1548, 397, 21);
	wall[22] = Wall(855, 1733, 1006, 21);
	wall[23] = Wall(2192, 1784, 1008, 21);
	wall[24] = Wall(2650, 1659, 18, 147);
	wall[25] = Wall(1349, 1699, 18, 54);
	wall[26] = Wall(634, 1342, 57, 21);
	wall[27] = Wall(831, 1342, 222, 21);
	wall[28] = Wall(855, 1342, 33, 412);
	wall[29] = Wall(1193, 1342, 764, 21);
	wall[30] = Wall(1349, 1342, 18, 188);
	wall[31] = Wall(1828, 1342, 33, 412);
	wall[32] = Wall(2097, 1342, 779, 21);
	wall[33] = Wall(2192, 1342, 33, 463);
	wall[34] = Wall(2650, 1342, 18, 157);
	wall[35] = Wall(2997, 1342, 196, 21);
	wall[36] = Wall(2330, 976, 870, 28);
	wall[37] = Wall(2856, 818, 36, 186);
	wall[38] = Wall(2856, 360, 36, 288);
	wall[39] = Wall(2856, 521, 344, 21);
	wall[40] = Wall(3167, 521, 33, 1284);
	wall[41] = Wall(0, 0, 3840, 360);
	wall[42] = Wall(0, 0, 640, 2160);
	wall[43] = Wall(3200, 0, 640, 2160);
	wall[44] = Wall(0, 1800, 3840, 360);

	enemy[0] = Enemy(903, 612, 873, 594, 220, 400);
	enemy[1] = Enemy(668, 1411, 683, 1105, 150, 404);
	enemy[2] = Enemy(693, 1147, 683, 1105, 680, 212);
	enemy[3] = Enemy(903, 1614, 881, 1372, 434, 367);
	enemy[4] = Enemy(923, 1391, 881, 1372, 434, 367);
	enemy[5] = Enemy(1666, 1385, 1400, 1372, 434, 367);
	enemy[6] = Enemy(1505, 1494, 1400, 1372, 434, 367);
	enemy[7] = Enemy(1666, 1613, 1400, 1372, 434, 367);
	enemy[8] = Enemy(2270 + 260, 1391, 2213, 1340, 455, 455);
	enemy[9] = Enemy(2270 + 260, 1629 + 50, 2213, 1340, 455, 455);
	enemy[10] = Enemy(2976 + 50, 1622 - 220, 2731, 1340, 455, 455);
	enemy[11] = Enemy(2981, 1126, 2723 - 250, 1069, 457, 212);
	enemy[12] = Enemy(2976 - 90, 566, 2917, 540, 263, 442);
	enemy[13] = Enemy(2976 - 90, 878, 2917, 540, 263, 442);
	enemy[14] = Enemy(1840, 448, 1790, 397, 355, 455 + 100);
	enemy[15] = Enemy(2246, 540, 2050, 397, 532, 481 + 100);
	enemy[16] = Enemy(2657, 423, 2503, 397, 355, 455 + 100);
}
void show_highscore()
{
	iShowImage(0, 0, 1280, 720, high_bg);

	if(highscore_b_back.hover)
		iShowImage(highscore_b_back.x, highscore_b_back.y, highscore_b_back.w, highscore_b_back.h, ins[2]);

	else
		iShowImage(highscore_b_back.x, highscore_b_back.y, highscore_b_back.w, highscore_b_back.h, ins[1]);


	iText(120, 550, "No", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(620, 550, "Name", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1020, 550, "Score", GLUT_BITMAP_TIMES_ROMAN_24);

	iText(120, 500, "1.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 450, "2.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 400, "3.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 350, "4.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 300, "5.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 250, "6.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 200, "7.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 150, "8.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 100, "9.", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(120, 50, "10.", GLUT_BITMAP_TIMES_ROMAN_24);

	char name;
	char score;
	int in = 0;


	FILE *fp1, *fp2;

	fp1 = fopen("Name.txt", "r");
	fp2 = fopen("Highscore.txt", "r");


	/*while(fp1 != EOF)
	{
		fscanf(fp1, "%s",name[in]);
		fscanf(fp2, "%s",score[in]);

		in++;
	}/*


	/*if(fscanf(fp1, "%s",name) != EOF)	
	{
		fscanf(fp2, "%s",score);
		iText(620, 500, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 500, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 450, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 450, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 400, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 400, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}


	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 350, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 350, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 300, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 300, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 250, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 250, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 200, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 200, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 150, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 150, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 100, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 100, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(fscanf(fp1, "%s",name) != EOF)
	{
		fscanf(fp2, "%s",score);	
		iText(620, 50, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1020, 50, score, GLUT_BITMAP_TIMES_ROMAN_24);
	}*/


	fclose(fp1);
	fclose(fp2);
		
						
}
void show_level1_complete()
{
	iShowImage(0, 0, 1280, 720, end_seen);

	if(end_seen_b.hover)
		iShowImage(end_seen_b.x, end_seen_b.y, end_seen_b.w, end_seen_b.h, ins[2]);

	else
		iShowImage(end_seen_b.x, end_seen_b.y, end_seen_b.w, end_seen_b.h, ins[1]);

	int_to_string(p.score, score);

	iText(725, 176, score, GLUT_BITMAP_TIMES_ROMAN_24);

	iText(725, 116, p.name, GLUT_BITMAP_TIMES_ROMAN_24);
	
	p.health = 100;
	p.x = 750 - 80 + 22;
	p.y = 450 - 54 + 14;
	p.bullet_index = 0;

	for(int i = 0; i < 17; i++)
	{
		enemy[i].health = 100;
		enemy[i].dead = false;
	}


	m.x = 0;
	m.y = 0;
	health_one[0] = Health(1367, 827);
	health_one[1] = Health(774, 1467);
	health_one[2] = Health(1988, 1445);
	health_one[3] = Health(2255, 428);
	health_one[4] = Health(2286, 1600);
	wall[0] = Wall(855, 580, 33, 525);
	wall[1] = Wall(855, 580, 575, 16);
	wall[2] = Wall(855, 860, 46, 9);
	wall[3] = Wall(1040, 860, 144, 9);
	wall[4] = Wall(1167, 580, 18, 319);
	wall[5] = Wall(1167, 1069, 18, 36);
	wall[6] = Wall(1314, 580, 18, 37);
	wall[7] = Wall(1314, 787, 18, 82);
	wall[8] = Wall(1314, 808, 448, 9);
	wall[9] = Wall(1314, 1038, 18, 67);
	wall[10] = Wall(1397, 557, 17, 38);
	wall[11] = Wall(1397, 360, 17, 28);
	wall[12] = Wall(1397, 360, 204, 13);
	wall[13] = Wall(1587, 360, 14, 236);
	wall[14] = Wall(1729, 360, 33, 505);
	wall[15] = Wall(1729, 360, 1162, 21);
	wall[16] = Wall(1570, 580, 192, 16);
	wall[17] = Wall(1729, 1035, 33, 70);
	wall[18] = Wall(634, 1083, 1400, 22);
	wall[19] = Wall(634, 1083, 33, 457);
	wall[20] = Wall(634, 1519, 254, 21);
	wall[21] = Wall(1828, 1548, 397, 21);
	wall[22] = Wall(855, 1733, 1006, 21);
	wall[23] = Wall(2192, 1784, 1008, 21);
	wall[24] = Wall(2650, 1659, 18, 147);
	wall[25] = Wall(1349, 1699, 18, 54);
	wall[26] = Wall(634, 1342, 57, 21);
	wall[27] = Wall(831, 1342, 222, 21);
	wall[28] = Wall(855, 1342, 33, 412);
	wall[29] = Wall(1193, 1342, 764, 21);
	wall[30] = Wall(1349, 1342, 18, 188);
	wall[31] = Wall(1828, 1342, 33, 412);
	wall[32] = Wall(2097, 1342, 779, 21);
	wall[33] = Wall(2192, 1342, 33, 463);
	wall[34] = Wall(2650, 1342, 18, 157);
	wall[35] = Wall(2997, 1342, 196, 21);
	wall[36] = Wall(2330, 976, 870, 28);
	wall[37] = Wall(2856, 818, 36, 186);
	wall[38] = Wall(2856, 360, 36, 288);
	wall[39] = Wall(2856, 521, 344, 21);
	wall[40] = Wall(3167, 521, 33, 1284);
	wall[41] = Wall(0, 0, 3840, 360);
	wall[42] = Wall(0, 0, 640, 2160);
	wall[43] = Wall(3200, 0, 640, 2160);
	wall[44] = Wall(0, 1800, 3840, 360);

	enemy[0] = Enemy(903, 612, 873, 594, 220, 400);
	enemy[1] = Enemy(668, 1411, 683, 1105, 150, 404);
	enemy[2] = Enemy(693, 1147, 683, 1105, 680, 212);
	enemy[3] = Enemy(903, 1614, 881, 1372, 434, 367);
	enemy[4] = Enemy(923, 1391, 881, 1372, 434, 367);
	enemy[5] = Enemy(1666, 1385, 1400, 1372, 434, 367);
	enemy[6] = Enemy(1505, 1494, 1400, 1372, 434, 367);
	enemy[7] = Enemy(1666, 1613, 1400, 1372, 434, 367);
	enemy[8] = Enemy(2270 + 260, 1391, 2213, 1340, 455, 455);
	enemy[9] = Enemy(2270 + 260, 1629 + 50, 2213, 1340, 455, 455);
	enemy[10] = Enemy(2976 + 50, 1622 - 220, 2731, 1340, 455, 455);
	enemy[11] = Enemy(2981, 1126, 2723 - 250, 1069, 457, 212);
	enemy[12] = Enemy(2976 - 90, 566, 2917, 540, 263, 442);
	enemy[13] = Enemy(2976 - 90, 878, 2917, 540, 263, 442);
	enemy[14] = Enemy(1840, 448, 1790, 397, 355, 455 + 100);
	enemy[15] = Enemy(2246, 540, 2050, 397, 532, 481 + 100);
	enemy[16] = Enemy(2657, 423, 2503, 397, 355, 455 + 100);
}

void MenuLoad()
{
	ch[0] = Menu(-4,0);
	ch[1] = Menu(-50,0);
	ch[2] = Menu(-100,0);
	ch[3] = Menu(-150,0);
	ch[4] = Menu(-200,0);
	ch[5] = Menu(-250,0);

	back[0] = iLoadImage("menu\\front.png");
	back[1] = iLoadImage("menu\\name.png");
	back[2] = iLoadImage("menu\\back1.png");
	back[3] = iLoadImage("menu\\back2.png");
	back[4] = iLoadImage("menu\\back3.png");
	back[5] = iLoadImage("menu\\back4.png");
	back[6] = iLoadImage("menu\\back5.png");



	menu[0] = iLoadImage("menu\\back.png");
	menu[1] = iLoadImage("menu\\play.png");
	menu[2] = iLoadImage("menu\\play_hover.png");

	menu[3] = iLoadImage("menu\\ins.png");
	menu[4] = iLoadImage("menu\\ins_hover.png");

	menu[5] = iLoadImage("menu\\credits.png");
	menu[6] = iLoadImage("menu\\credits_hover.png");

	menu[7] = iLoadImage("menu\\exit.png");
	menu[8] = iLoadImage("menu\\exit_hover.png");

	menu[9] = iLoadImage("menu\\highscore.png");
	menu[10] = iLoadImage("menu\\highscore_hover.png");



	//ins
	ins_b_back.w = 208;
	ins_b_back.h = 76;


	ins[0] = iLoadImage("INS.png");
	ins[1] = iLoadImage("back_button.png");
	ins[2] = iLoadImage("back_button_hover.png");
	

	highscore_b_back.w = 208;
	highscore_b_back.h = 76;

	end_seen_b.w = 208;
	end_seen_b.h = 76;
	//credits

	cerdits_b_back.w = 208;
	cerdits_b_back.h = 76;

	credits[0] = iLoadImage("CREDITS.png");
	credits[4] = iLoadImage("CREDITS_up.png");
	credits[1] = iLoadImage("back_button.png");
	credits[2] = iLoadImage("back_button_hover.png");
}
void image_Load()
{
	high_bg = iLoadImage("high_bg.png");
	end_seen = iLoadImage("end_seen.png");
	gameover = iLoadImage("gameover.png");
	heal_image = iLoadImage("heal.png");
	enemy_image = iLoadImage("enemy.png");
	ft_d_stand = iLoadImage("walkd\\foot5.png");
	ft_a_stand = iLoadImage("walka\\foot5.png");
	ft_w_stand = iLoadImage("walkw\\foot5.png");
	ft_s_stand = iLoadImage("walks\\foot5.png");

	ft_d[0] = iLoadImage("walkd\\foot.png");
	ft_d[1] = iLoadImage("walkd\\foot1.png");
	ft_d[2] = iLoadImage("walkd\\foot2.png");
	ft_d[3] = iLoadImage("walkd\\foot3.png");
	ft_d[4] = iLoadImage("walkd\\foot4.png");
	ft_d[5] = iLoadImage("walkd\\foot5.png");
	ft_d[6] = iLoadImage("walkd\\foot6.png");
	ft_d[7] = iLoadImage("walkd\\foot7.png");
	ft_d[8] = iLoadImage("walkd\\foot8.png");
	ft_d[9] = iLoadImage("walkd\\foot9.png");
	ft_d[10] = iLoadImage("walkd\\foot10.png");
	ft_d[11] = iLoadImage("walkd\\foot11.png");
	ft_d[12] = iLoadImage("walkd\\foot12.png");
	ft_d[13] = iLoadImage("walkd\\foot13.png");
	ft_d[14] = iLoadImage("walkd\\foot14.png");
	ft_d[15] = iLoadImage("walkd\\foot15.png");
	ft_d[16] = iLoadImage("walkd\\foot16.png");
	ft_d[17] = iLoadImage("walkd\\foot17.png");
	ft_d[18] = iLoadImage("walkd\\foot18.png");
	ft_d[19] = iLoadImage("walkd\\foot19.png");

	ft_w[0] = iLoadImage("walkw\\foot.png");
	ft_w[1] = iLoadImage("walkw\\foot1.png");
	ft_w[2] = iLoadImage("walkw\\foot2.png");
	ft_w[3] = iLoadImage("walkw\\foot3.png");
	ft_w[4] = iLoadImage("walkw\\foot4.png");
	ft_w[5] = iLoadImage("walkw\\foot5.png");
	ft_w[6] = iLoadImage("walkw\\foot6.png");
	ft_w[7] = iLoadImage("walkw\\foot7.png");
	ft_w[8] = iLoadImage("walkw\\foot8.png");
	ft_w[9] = iLoadImage("walkw\\foot9.png");
	ft_w[10] = iLoadImage("walkw\\foot10.png");
	ft_w[11] = iLoadImage("walkw\\foot11.png");
	ft_w[12] = iLoadImage("walkw\\foot12.png");
	ft_w[13] = iLoadImage("walkw\\foot13.png");
	ft_w[14] = iLoadImage("walkw\\foot14.png");
	ft_w[15] = iLoadImage("walkw\\foot15.png");
	ft_w[16] = iLoadImage("walkw\\foot16.png");
	ft_w[17] = iLoadImage("walkw\\foot17.png");
	ft_w[18] = iLoadImage("walkw\\foot18.png");
	ft_w[19] = iLoadImage("walkw\\foot19.png");

	ft_a[0] = iLoadImage("walka\\foot.png");
	ft_a[1] = iLoadImage("walka\\foot1.png");
	ft_a[2] = iLoadImage("walka\\foot2.png");
	ft_a[3] = iLoadImage("walka\\foot3.png");
	ft_a[4] = iLoadImage("walka\\foot4.png");
	ft_a[5] = iLoadImage("walka\\foot5.png");
	ft_a[6] = iLoadImage("walka\\foot6.png");
	ft_a[7] = iLoadImage("walka\\foot7.png");
	ft_a[8] = iLoadImage("walka\\foot8.png");
	ft_a[9] = iLoadImage("walka\\foot9.png");
	ft_a[10] = iLoadImage("walka\\foot10.png");
	ft_a[11] = iLoadImage("walka\\foot11.png");
	ft_a[12] = iLoadImage("walka\\foot12.png");
	ft_a[13] = iLoadImage("walka\\foot13.png");
	ft_a[14] = iLoadImage("walka\\foot14.png");
	ft_a[15] = iLoadImage("walka\\foot15.png");
	ft_a[16] = iLoadImage("walka\\foot16.png");
	ft_a[17] = iLoadImage("walka\\foot17.png");
	ft_a[18] = iLoadImage("walka\\foot18.png");
	ft_a[19] = iLoadImage("walka\\foot19.png");

	ft_s[0] = iLoadImage("walks\\foot.png");
	ft_s[1] = iLoadImage("walks\\foot1.png");
	ft_s[2] = iLoadImage("walks\\foot2.png");
	ft_s[3] = iLoadImage("walks\\foot3.png");
	ft_s[4] = iLoadImage("walks\\foot4.png");
	ft_s[5] = iLoadImage("walks\\foot5.png");
	ft_s[6] = iLoadImage("walks\\foot6.png");
	ft_s[7] = iLoadImage("walks\\foot7.png");
	ft_s[8] = iLoadImage("walks\\foot8.png");
	ft_s[9] = iLoadImage("walks\\foot9.png");
	ft_s[10] = iLoadImage("walks\\foot10.png");
	ft_s[11] = iLoadImage("walks\\foot11.png");
	ft_s[12] = iLoadImage("walks\\foot12.png");
	ft_s[13] = iLoadImage("walks\\foot13.png");
	ft_s[14] = iLoadImage("walks\\foot14.png");
	ft_s[15] = iLoadImage("walks\\foot15.png");
	ft_s[16] = iLoadImage("walks\\foot16.png");
	ft_s[17] = iLoadImage("walks\\foot17.png");
	ft_s[18] = iLoadImage("walks\\foot18.png");
	ft_s[19] = iLoadImage("walks\\foot19.png");

	reload_png[0] = iLoadImage("reload\\r.png");
	reload_png[1] = iLoadImage("reload\\r1.png");
	reload_png[2] = iLoadImage("reload\\r2.png");
	reload_png[3] = iLoadImage("reload\\r3.png");
	reload_png[4] = iLoadImage("reload\\r4.png");
	reload_png[5] = iLoadImage("reload\\r5.png");
	reload_png[6] = iLoadImage("reload\\r6.png");
	reload_png[7] = iLoadImage("reload\\r7.png");
	reload_png[8] = iLoadImage("reload\\r8.png");
	reload_png[9] = iLoadImage("reload\\r9.png");
	reload_png[10] = iLoadImage("reload\\r10.png");
	reload_png[11] = iLoadImage("reload\\r11.png");
	reload_png[12] = iLoadImage("reload\\r12.png");
	reload_png[13] = iLoadImage("reload\\r13.png");
	reload_png[14] = iLoadImage("reload\\r14.png");
	reload_png[15] = iLoadImage("reload\\r15.png");
	reload_png[16] = iLoadImage("reload\\r16.png");
	reload_png[17] = iLoadImage("reload\\r17.png");
	reload_png[18] = iLoadImage("reload\\r18.png");
	reload_png[19] = iLoadImage("reload\\r19.png");


	bullet_image = iLoadImage("bullet.png");

	bg = iLoadImage("back.png");
}
void health_barLoad()
{
	health[0] = iLoadImage("Health_Bar\\5.png");
	health[1] = iLoadImage("Health_Bar\\10.png");
	health[2] = iLoadImage("Health_Bar\\15.png");
	health[3] = iLoadImage("Health_Bar\\20.png");
	health[4] = iLoadImage("Health_Bar\\25.png");
	health[5] = iLoadImage("Health_Bar\\30.png");
	health[6] = iLoadImage("Health_Bar\\35.png");
	health[7] = iLoadImage("Health_Bar\\40.png");
	health[8] = iLoadImage("Health_Bar\\45.png");
	health[9] = iLoadImage("Health_Bar\\50.png");
	health[10] = iLoadImage("Health_Bar\\55.png");
	health[11] = iLoadImage("Health_Bar\\60.png");
	health[12] = iLoadImage("Health_Bar\\65.png");
	health[13] = iLoadImage("Health_Bar\\70.png");
	health[14] = iLoadImage("Health_Bar\\75.png");
	health[15] = iLoadImage("Health_Bar\\80.png");
	health[16] = iLoadImage("Health_Bar\\85.png");
	health[17] = iLoadImage("Health_Bar\\90.png");
	health[18] = iLoadImage("Health_Bar\\95.png");
	health[19] = iLoadImage("Health_Bar\\100.png");

}
void bullet_number_load()
{
	bullet_show[0] = iLoadImage("bullet_number\\30.png");
	bullet_show[1] = iLoadImage("bullet_number\\29.png");
	bullet_show[2] = iLoadImage("bullet_number\\28.png");
	bullet_show[3] = iLoadImage("bullet_number\\27.png");
	bullet_show[4] = iLoadImage("bullet_number\\26.png");
	bullet_show[5] = iLoadImage("bullet_number\\25.png");
	bullet_show[6] = iLoadImage("bullet_number\\24.png");
	bullet_show[7] = iLoadImage("bullet_number\\23.png");
	bullet_show[8] = iLoadImage("bullet_number\\22.png");
	bullet_show[9] = iLoadImage("bullet_number\\21.png");
	bullet_show[10] = iLoadImage("bullet_number\\20.png");
	bullet_show[11] = iLoadImage("bullet_number\\19.png");
	bullet_show[12] = iLoadImage("bullet_number\\18.png");
	bullet_show[13] = iLoadImage("bullet_number\\17.png");
	bullet_show[14] = iLoadImage("bullet_number\\16.png");
	bullet_show[15] = iLoadImage("bullet_number\\15.png");
	bullet_show[16] = iLoadImage("bullet_number\\14.png");
	bullet_show[17] = iLoadImage("bullet_number\\13.png");
	bullet_show[18] = iLoadImage("bullet_number\\12.png");
	bullet_show[19] = iLoadImage("bullet_number\\11.png");
	bullet_show[20] = iLoadImage("bullet_number\\10.png");
	bullet_show[21] = iLoadImage("bullet_number\\09.png");
	bullet_show[22] = iLoadImage("bullet_number\\08.png");
	bullet_show[23] = iLoadImage("bullet_number\\07.png");
	bullet_show[24] = iLoadImage("bullet_number\\06.png");
	bullet_show[25] = iLoadImage("bullet_number\\05.png");
	bullet_show[26] = iLoadImage("bullet_number\\04.png");
	bullet_show[27] = iLoadImage("bullet_number\\03.png");
	bullet_show[28] = iLoadImage("bullet_number\\02.png");
	bullet_show[29] = iLoadImage("bullet_number\\01.png");
	bullet_show[30] = iLoadImage("bullet_number\\00.png");
	bullet_show[31] = iLoadImage("bullet_number\\000.png");

}
void bullet_number_animation()
{
	if((30 - p.bullet_index) == 30)
		iShowImage(1100, 30, 142, 55, bullet_show[0]);

	else if((30 - p.bullet_index) == 29)
		iShowImage(1100, 30, 142, 55, bullet_show[1]);

	else if((30 - p.bullet_index) == 28)
		iShowImage(1100, 30, 142, 55, bullet_show[2]);

	else if((30 - p.bullet_index) == 27)
		iShowImage(1100, 30, 142, 55, bullet_show[3]);

	else if((30 - p.bullet_index) == 26)
		iShowImage(1100, 30, 142, 55, bullet_show[4]);

	else if((30 - p.bullet_index) == 25)
		iShowImage(1100, 30, 142, 55, bullet_show[5]);

	else if((30 - p.bullet_index) == 24)
		iShowImage(1100, 30, 142, 55, bullet_show[6]);

	else if((30 - p.bullet_index) == 23)
		iShowImage(1100, 30, 142, 55, bullet_show[7]);

	else if((30 - p.bullet_index) == 22)
		iShowImage(1100, 30, 142, 55, bullet_show[8]);

	else if((30 - p.bullet_index) == 21)
		iShowImage(1100, 30, 142, 55, bullet_show[9]);

	else if((30 - p.bullet_index) == 20)
		iShowImage(1100, 30, 142, 55, bullet_show[10]);

	else if((30 - p.bullet_index) == 19)
		iShowImage(1100, 30, 142, 55, bullet_show[11]);

	else if((30 - p.bullet_index) == 18)
		iShowImage(1100, 30, 142, 55, bullet_show[12]);

	else if((30 - p.bullet_index) == 17)
		iShowImage(1100, 30, 142, 55, bullet_show[13]);

	else if((30 - p.bullet_index) == 16)
		iShowImage(1100, 30, 142, 55, bullet_show[14]);

	else if((30 - p.bullet_index) == 15)
		iShowImage(1100, 30, 142, 55, bullet_show[15]);

	else if((30 - p.bullet_index) == 14)
		iShowImage(1100, 30, 142, 55, bullet_show[16]);

	else if((30 - p.bullet_index) == 13)
		iShowImage(1100, 30, 142, 55, bullet_show[17]);

	else if((30 - p.bullet_index) == 12)
		iShowImage(1100, 30, 142, 55, bullet_show[18]);

	else if((30 - p.bullet_index) == 11)
		iShowImage(1100, 30, 142, 55, bullet_show[19]);

	else if((30 - p.bullet_index) == 10)
		iShowImage(1100, 30, 142, 55, bullet_show[20]);

	else if((30 - p.bullet_index) == 9)
		iShowImage(1100, 30, 142, 55, bullet_show[21]);

	else if((30 - p.bullet_index) == 8)
		iShowImage(1100, 30, 142, 55, bullet_show[22]);

	else if((30 - p.bullet_index) == 7)
		iShowImage(1100, 30, 142, 55, bullet_show[23]);

	else if((30 - p.bullet_index) == 6)
		iShowImage(1100, 30, 142, 55, bullet_show[24]);

	else if((30 - p.bullet_index) == 5)
		iShowImage(1100, 30, 142, 55, bullet_show[25]);

	else if((30 - p.bullet_index) == 4)
		iShowImage(1100, 30, 142, 55, bullet_show[26]);

	else if((30 - p.bullet_index) == 3)
		iShowImage(1100, 30, 142, 55, bullet_show[27]);

	else if((30 - p.bullet_index) == 2)
		iShowImage(1100, 30, 142, 55, bullet_show[28]);

	else if((30 - p.bullet_index) == 1)
		iShowImage(1100, 30, 142, 55, bullet_show[29]);

	else if((30 - p.bullet_index) <= 0)
	{
		iShowImage(1100, 30, 142, 55, bullet_show[30]);
		iShowImage(800, 30, 224, 39, bullet_show[31]);
	}
}

void iDraw()
{
	iClear();

	if(seen == 0)
	{
		show_menu();
	}

	else if(seen == 1)
	{
		iShowImage(m.x, m.y, 3840, 2160, bg);
		
		Bullet_animation();
		Player_animation();
		enemyBullet_animation();
		enemyFire();
		wall_animation();
		heal_animation();
		health_animation();
		bullet_number_animation();

		if(p.health <= 0)
		{
			seen = 6;
			BASS_ChannelStop(first_level_sound);
			BASS_ChannelPlay(gameover_sound, false);
		}
	}

	else if(seen == 3)
	{
		iSetColor(255, 255, 255);
		show_level1_complete();
	}

	else if(seen == 5)
	{
		iSetColor(255, 255, 255);
		show_highscore();
	}

	else if(seen == 6)
	{
		iSetColor(255, 255, 255);
		show_gameover();
	}

	else if(seen == 7)
	{
		iSetColor(255, 255, 255);
		show_ins();
	}
	else if(seen == 8)
	{
		iSetColor(255, 255, 255);
		show_credits();
	}
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	menu_button_hover(mx, my);
	p.Angle_count(mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
	if(seen == 0)
	{
		if(play_b.hover && button == 0 && state == 0)
		{
			BASS_ChannelStop(menu_sound);
			p.clock_start = clock();
			seen = 1;
			BASS_ChannelPlay(first_level_sound, false);
		}
		else if(highscore_b.hover && button == 0 && state == 0)
			seen = 5;

		else if(exit_b.hover && button == 0 && state == 0)
			exit(0);

		else if(credits_b.hover && button == 0 && state == 0)
			seen = 8;

		else if(ins_b.hover && button == 0 && state == 0)
			seen = 7;

		

	}
	else if(seen == 3)
	{
		if(end_seen_b.hover && button == 0 && state == 0)
		{
			FILE *fp1;
			fp1 = fopen("Highscore.txt", "a");
			fprintf(fp1, "%d\n", p.score);
			fclose(fp1);

			FILE *fp2;
			fp2 = fopen("Name.txt", "a");
			fprintf(fp2, "%s\n", p.name);
			fclose(fp2);
			
			seen = 0;
		}
	}

	else if(seen == 5)
	{
		if(highscore_b_back.hover && button == 0 && state == 0) 
			seen = 0;
	}
	else if(seen == 7)
	{
		if(ins_b_back.hover && button == 0 && state == 0) 
			seen = 0;
	}
	else if(seen == 8)
	{
		if(cerdits_b_back.hover && button == 0 && state == 0) 
			seen = 0;
	}

	playerMouseInput(button, state, mx, my);
}

void iKeyboard(unsigned char key)
{	
	keyboardInput(key);

	if(seen == 6 && key)
		seen = 0;

	if(seen == 3)
	{
		if(key != '\b')
		{
			p.name[p.name_index] = key;
			p.name_index++;
			p.name[p.name_index] = '\0';
		}

		else if(key == '\b')
		{
			if(p.name_index <= 0)
			{
				p.name_index = 0;
			}

			else
			{
				p.name_index--;
			}
			p.name[p.name_index] = '\0';
		}
	}

	
}

void iSpecialKeyboard(unsigned char key)
{
	if(seen == 6 && key)
		seen = 0;
}

int main()
{
	iSetTimer(150, back1_change);
	iSetTimer(50, back2_change);
	iSetTimer(30, back3_change);
	iSetTimer(10, back4_change);
	iSetTimer(5, back5_change);


	iSetTimer(75,reload_animation);
	iSetTimer(5, Fire);
    iSetTimer(650, Fire_Delay);
	iSetTimer(900, Enemy_Fire_delay);
	iSetTimer(1, credits_animation);

	iInitialize(1280, 720, "shooter");

	if(!BASS_Init(-1, 44100, 0, NULL, NULL))
		printf("gun_fire sound not played");
	
	sound_load();
	set_health_axis();
	health_barLoad();
	MenuLoad();
	set_wall_cordinate();
	setEnemyAxis();
	image_Load();
	bullet_number_load();

	BASS_ChannelPlay(menu_sound, false);


	bullet_image = iLoadImage("bullet.png");
	bg = iLoadImage("back.png");

	iStart();
	return 0;
}