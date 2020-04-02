#include <string>
#include <SDL_image.h>

#include "Game.h"
#include "Color.h"
#include "Constants.h"
#include "Input.h"

Game::Game()
{
}

Game::~Game()
{
	net.clear();
	TTF_CloseFont(font);
	TTF_Quit();
}

void Game::load(SDL_Renderer& renderer)
{
	for (int i = 0; i < 8; ++i) {
		net.push_back(std::make_unique<DrawableRect>(
			Vector2(static_cast<float>(SCREEN_WIDTH / 2 - NET_WIDTH / 2), static_cast<float>(i * (NET_HEIGHT + NET_SPACE))),
			NET_WIDTH,
			NET_HEIGHT, 
			Color(), 
			renderer
		));
	}
	left_paddle = std::make_shared<Paddle>(Vector2(0, 200), Vector2(20, 100), renderer, true);
	right_paddle = std::make_shared<Paddle>(OPPONENT_START, Vector2(20, 100), renderer, false);
	font = TTF_OpenFont("assets/arial.ttf", 12);

	ball = Ball(BALL_START, BALL_SPEED, renderer, left_paddle, right_paddle);

	Color text_color = Color(255, 255, 255, 255);
	std::string left_score_string = std::to_string(left_score);
	std::string right_score_string = std::to_string(right_score);
	left_score_text = Text(Vector2(50, 50), left_score_string, font, 60, 60, text_color, renderer);
	right_score_text = Text(Vector2(SCREEN_WIDTH - 100, 50), right_score_string, font, 60, 60, text_color, renderer);
	victory_text = Text(Vector2(250, 150), "", font, 200, 50, Color(), renderer);
	restart_text = Text(Vector2(200, 220), "", font, 300, 50, Color(), renderer);
	restart_text.set_text("Click to restart game", font);

#if _DEBUG
	fps = Text(Vector2(20, 420), "", font, 300, 50, Color(), renderer);
#endif

	restart();
}

void Game::update(float dt)
{
	// Game
	if (outcome == 0) {
		left_paddle->update(dt);
		right_paddle->update(dt);

		ball.update(dt);
		
		if (ball.get_position().get_x() < 0)
		{
			right_score_text.set_text(std::to_string(++right_score), font);
			if (right_score >= MAX_SCORE) {
				victory_text.set_text("AI wins", font);
				outcome = 2;
			}
			else {
				reset();
			}
		}
		else if (ball.get_position().get_x() > SCREEN_WIDTH)
		{
			left_score_text.set_text(std::to_string(++left_score), font);
			if (left_score >= MAX_SCORE) {
				victory_text.set_text("Player wins", font);
				outcome = 1;
			}
			else {
				reset();
			}
		}
	}
	else {
		if (Input::left_button_just_clicked()) {
			restart();
		}
	}

#if _DEBUG
	if(dt > 0.02)
		fps.set_text(std::to_string(dt), font);
#endif
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	if (outcome == 0) {
		for (auto it = net.begin(); it != net.end(); ++it)
		{
			it->get()->draw(renderer);
		}
		left_paddle->draw(renderer);
		right_paddle->draw(renderer);
		ball.draw(renderer);
		left_score_text.draw(renderer);
		right_score_text.draw(renderer);
	}
	else {
		victory_text.draw(renderer);
		restart_text.draw(renderer);
	}

#if _DEBUG
	fps.draw(renderer);
#endif

	SDL_RenderPresent(&renderer);
}

void Game::reset() 
{
	ball.set_position(BALL_START);
	ball.set_speed(BALL_SPEED);
}

void Game::restart()
{
	left_score = 0;
	right_score = 0;
	std::string left_score_string = std::to_string(left_score);
	std::string right_score_string = std::to_string(right_score);
	left_score_text.set_text(left_score_string, font);
	right_score_text.set_text(right_score_string, font);
	reset();
	outcome = 0;
}