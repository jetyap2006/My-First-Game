#define is_down(d) input->buttons[d].is_down
#define pressed(d) (input->buttons[d].is_down && input->buttons[d].changed)
#define released(d) (!input->buttons[d].is_down && input->buttons[d].changed)

float player_p_1, player_dp_1; // d = derivative;
float player_p_2, player_dp_2;
float arena_half_size_x = 85.0f, arena_half_size_y = 45.0f;
float player_p_half_size_x = 2.5, player_p_half_size_y = 12.0f;
float ball_p_x, ball_p_y, ball_dp_x = 150.f, ball_dp_y;
float ball_half_size = 1;

int player_score_1(0), player_score_2(0);

//Equations of motion : 
//1) v = u + at;
//2) s = ut + (a * t ^ 2)/2
					
internal void simulate_player(float* p, float* dp, float ddp, float dt)
{


	ddp -= *dp * 3.0f; //friction;
	*p = *p + *dp * dt + 0.5 * (ddp * dt * dt); //physics implementations
	*dp = *dp + ddp * dt;


	//upper collision
	if (*p + player_p_half_size_y > arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	{	//just draw it out then you will understand the concept

		*p = arena_half_size_y - player_p_half_size_y - 0.005 * arena_half_size_y;
		*dp = 0; // reset the velocity

	}
	//lower collision
	else if (*p - player_p_half_size_y < -arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	{	//just draw it out then you will understand the concept

		*p = -arena_half_size_y + player_p_half_size_y + 0.005 * arena_half_size_y;
		*dp = 0; // reset the velocity

	}

}

internal void draw_number(int score, float x, float y, float size, u32 color)
{	
	bool drew_number = false;
	float half_size = 0.5f * size;
	while (score || drew_number == false)
	{	
		drew_number = true;
		int digits = score % 10;
		score /= 10;
		
		switch (digits)

		{
		case 0:
		{
			draw_rect(x - size, y, half_size, size * 2.5f, color);
			draw_rect(x + size, y, half_size, size * 2.5f, color);
			draw_rect(x, y + 2 * (size), half_size, half_size, color);
			draw_rect(x, y - 2 * (size), half_size, half_size, color);
			x -= 4.f;
		} break;

		case 1:
		{
			draw_rect(x, y, half_size, size * 2.5f, color);
			x -= 4.f;
		}break;

		case 2: {
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x + size, y + size, half_size, 0.5 * 2.5 * size, color);
			draw_rect(x - size, y - size, half_size, 0.5 * 2.5 * size, color);
			x -= 4.f;
		}break;

		case 3:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x + size, y + size, half_size, 0.5 * 2.5 * size, color);
			draw_rect(x + size, y - size, half_size, 0.5 * 2.5 * size, color);
			x -= 4.f;

		}break;

		case 4:
		{
			draw_rect(x + size, y, half_size, size * 2.5f, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x - size, y + size, half_size, 0.5 * 2.5 * size, color);
			x -= 4.f;

		}break;

		case 5:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x - size, y + size, half_size, 0.5 * 2.5 * size, color);
			draw_rect(x + size, y - size, half_size, 0.5 * 2.5 * size, color);
			x -= 4.f;

		}break;

		case 6:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x - size, y, half_size, size * 2.5f, color);
			draw_rect(x + size, y - size, half_size, 0.5 * 2.5 * size, color);
			x -= 4.f;

		}break;
		case 7:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x + size, y, half_size, size * 2.5f, color);
			x -= 4.f;

		}break;
		case 8:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x - size, y, half_size, size * 2.5f, color);
			draw_rect(x + size, y, half_size, size * 2.5f, color);
			x -= 4.f;

		}break;
		case 9:
		{
			draw_rect(x, y + 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y - 2 * (size), 1.5 * size, half_size, color);
			draw_rect(x, y, 1.5 * size, half_size, color);
			draw_rect(x - size, y + size, half_size, 0.5 * 2.5 * size, color);
			draw_rect(x + size, y, half_size, size * 2.5f, color);
			x -= 4.f;

		}break;

		default:
			break;
		}
	}

}

internal void simulate_game(Input* input , float dt)
{	
	float player_ddp_1 = 0.0f, player_ddp_2 = 0.0f;
	
	
	clear_screen(0xfff6e40);
	if (is_down(BUTTON_UP)) player_ddp_1 += 600.f;
	if (is_down(BUTTON_DOWN)) player_ddp_1-= 600.f;
	if (is_down(BUTTON_W)) player_ddp_2 += 600.f;
	if (is_down(BUTTON_S)) player_ddp_2 -= 600.f;

	simulate_player(&player_p_1, &player_dp_1, player_ddp_1, dt);
	simulate_player(&player_p_2, &player_dp_2, player_ddp_2, dt);
	//player_ddp_1 -= player_dp_1 * 3.0f; //friction;
	//player_p_1 = player_p_1  + player_dp_1 * dt + 0.5 * (player_ddp_1 * dt * dt); //physics implementations
	//player_dp_1= player_dp_1 + player_ddp_1 * dt;


	////upper collision
	//if (player_p_1 + player_p_half_size_y > arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	//{	//just draw it out then you will understand the concept

	//	player_p_1 = arena_half_size_y - player_p_half_size_y - 0.005* arena_half_size_y;
	//	player_dp_1 = 0; // reset the velocity

	//}
	////lower collision
	//else if (player_p_1 - player_p_half_size_y < -arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	//{	//just draw it out then you will understand the concept

	//	player_p_1 =  -arena_half_size_y + player_p_half_size_y + 0.005 * arena_half_size_y;
	//	player_dp_1 = 0; // reset the velocity

	//}


	//player_ddp_2 -= player_dp_2 * 3.0f; //friction;
	//player_p_2 = player_p_2 + player_dp_2 * dt + 0.5 * (player_ddp_2 * dt * dt); //physics implementations
	/*player_dp_2 = player_dp_2 + player_ddp_2 * dt;*/

	////upper collision
	//if (player_p_2 + player_p_half_size_y > arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	//{	//just draw it out then you will understand the concept

	//	player_p_2 = arena_half_size_y - player_p_half_size_y - 0.005 * arena_half_size_y;
	//	player_dp_2 = 0; // reset the velocity

	//}
	////lower collision
	//else if (player_p_2 - player_p_half_size_y < -arena_half_size_y) // if the position of player plus the half size of the player is greater than the arena half size , we are colliding
	//{	//just draw it out then you will understand the concept

	//	player_p_2 = -arena_half_size_y + player_p_half_size_y + 0.005 * arena_half_size_y;
	//	player_dp_2 = 0; // reset the velocity

	//}
	//
	ball_p_x += ball_dp_x * dt;
	ball_p_y += ball_dp_y * dt;
	

	{  //Simulate ball

		if (ball_p_x + ball_half_size > 80 - player_p_half_size_x &&          //ball collision
		ball_p_x - ball_half_size < 80 + player_p_half_size_x &&
		ball_p_y + ball_half_size > player_p_2 - player_p_half_size_y &&   //if the highest y position of the ball is greater than the lowest y position of the player stick
		ball_p_y - ball_half_size < player_p_2 + player_p_half_size_y)     // if the lowest y position of the ball is 
		{
			ball_p_x = 80 - player_p_half_size_x - ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player_p_2) * 2;
		}

		else if (ball_p_x - ball_half_size < -80 + player_p_half_size_x &&          //ball collision
			ball_p_x + ball_half_size > -80 - player_p_half_size_x &&
			ball_p_y - ball_half_size < player_p_1 + player_p_half_size_y &&   //if the highest y position of the ball is greater than the lowest y position of the player stick
			ball_p_y + ball_half_size > player_p_1 - player_p_half_size_y)     // if the lowest y position of the ball is 
		{
			ball_p_x = -80 + player_p_half_size_x + ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player_p_1) * 2;
		}

		if (ball_p_y + ball_half_size > arena_half_size_y)  // if it hits the upper or the bottom of the arena 
		{
			ball_dp_y *= -1;
		}
		else if (ball_p_y - ball_half_size < -arena_half_size_y)
		{
			ball_dp_y *= -1;
		}


		if (ball_p_x + ball_half_size > arena_half_size_x)  // if it hits the left or right wing of the arena
		{
			ball_p_x = 0.0f;
			ball_dp_x *= -1;
			ball_dp_y = 0.0f;
			ball_p_y = 0.0f;
			player_score_1++;

		}

		if (ball_p_x - ball_half_size < -arena_half_size_x)
		{
			ball_p_x = 0.0f;
			ball_dp_x *= 1;
			ball_dp_y = 0.0f;
			ball_p_y = 0.0f;
			player_score_2++;
		}

	}
	//Rendering
	draw_rect(0, 0, 85, 45, 0xfffab40); // arena

	/*draw_rect(-20 - 1, 40, 0.5, 2.5, 0xbbffbb);*/

	//Scoreboard
	draw_number(player_score_1, -20, 40.f, 1.f, 0xbbffbb);
	draw_number(player_score_2, 20, 40.f, 1.f, 0xbbffbb);

	draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffffff); //ball

	draw_rect(-80, player_p_1, player_p_half_size_x, player_p_half_size_y, 0xff0000);
	draw_rect(80, player_p_2, player_p_half_size_x, player_p_half_size_y, 0xff0000);


}