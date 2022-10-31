void int_to_string(int time, char *arr)
{
	int temp = time;
	int count = 0;
	int loop_run;

	while(temp != 0)
	{
		temp /= 10;
		count++;
	}

	arr[count] = '\0';
	count--;
	loop_run = count;

	for(int i = 0; i <= loop_run; i++)
	{
		arr[count] = (time % 10) + '0';

		time /= 10;

		count--;

	}
}

bool button_hover(int mx, int my, Button b)
{
	if((mx > b.x && mx < b.x + b.w) && (my > b.y && my < b.y + b.h))
	{
			return true;
	}

	return false;
}

bool enemy_Col(Player p, Enemy wa)
	{
		if((p.hitbox_x + p.hitbox_w > wa.x && p.hitbox_x < wa.x + wa.w) && (p.hitbox_y + p.hitbox_h > wa.y && p.hitbox_y < wa.y + wa.h))
		{
				return true;
		}
		return false;
	}

bool player_wal_Col(Player pl, Wall wa)
{
	if((pl.hitbox_x + pl.hitbox_w > wa.x && pl.hitbox_x < wa.x + wa.w) && (pl.hitbox_y + pl.hitbox_h > wa.y && pl.hitbox_y < wa.y + wa.h))
	{
			return true;
	}

	return false;
}

bool player_Col(Enemy e, Player p)
	{
		if((p.hitbox_x + p.hitbox_w > e.s_x && p.hitbox_x < e.s_x + e.s_w) && (p.hitbox_y + p.hitbox_h > e.s_y && p.hitbox_y < e.s_y + e.s_h))
		{
				return true;
		}
		return false;
	}


void Angle_count(int x, int y, int px, int py, double &angle)
{
    int DiffX = px - x;
    int DiffY = py - y;

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
    else if (DiffY == 0 && DiffX > 0)
    {
        angle = 0;
    }
    else if (DiffX == 0 && DiffY > 0)
    {
        angle = 90;
    }
    else if (DiffY == 0 && DiffX < 0)
    {
        angle = 180;
    }
    else if (DiffY < 0 && DiffX == 0)
    {
        angle = 270;
    }
}

void int_to_char(int n, char *arr)
{
	int i = 0;

	while(n != 0)
	{
		arr[i] = (n % 10) + '0';
		i++;
		n /= 10;
	}
	
	arr[i] = '\0';
}
