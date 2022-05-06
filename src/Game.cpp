#define WIDTH (600)
#define HEIGHT (400)

#include "Game.h"
#include "InputHandler.h"

#include "Walker.h"
#include "Mover.h"
#include "Attractor.h"
#include "Utility.h"
#include "Ball.h"
#include <algorithm>

Game* Game::s_pInstance = 0;

// 한글 입력 테스트: Replit에서 입력
// 이 함수의 기능은 어쩌고 저쩌고
// 한글 입력 테스트2: VS에서 입력
// 한글한글한글한글한글한글한글한글한글한글
// UTF-8 BOM으로 변경
// 다시 VS로 가져가면?
bool Game::setup()
{
	bool result;

	result = init("Nature of Code", 100, 100, WIDTH, HEIGHT, false);

	_walker = new Walker();
	attractor = new Attractor(WIDTH / 2, HEIGHT / 2, 100);
	printf("\n\n\n\n\n\n\n\n");
	printf("한글 테스트\n");
	printf("\n\n\n\n\n\n\n\n");
	return result;
}

void Game::update()
{
	float turnRate = 0.03;
	Vector2D gravity = Vector2D(0, 0.01);

	if (KeyIsDown(SDL_SCANCODE_LEFT))
	{
		_walker->turn(-turnRate);
	}
	else if (KeyIsDown(SDL_SCANCODE_RIGHT))
	{
		_walker->turn(turnRate);
	}

	if (KeyIsDown(SDL_SCANCODE_Z))
	{
		_walker->thrust();
	}

	if (KeyIsDown(SDL_SCANCODE_X))
	{
		movers.push_back(new Mover(_walker->GetPos().getX(), _walker->GetPos().getY(), Utility::GetRandomFloat(50, 150)));
	}

	if (InputHandler::Instance()->getMouseButtonState(0))
	{
		Vector2D force = Vector2D(0.1, -0.1);
		force.normalize();
		force *= 10;
		balls.push_back(new Ball(35, HEIGHT - 25, Utility::GetRandomFloat(20, 30), force));
	}

	_walker->update();
	_walker->wrapEdges();

	for (Mover* mover : movers)
	{
		mover->update();
		attractor->attract(mover);
	}

	for (Ball* ball : balls)
	{
		ball->update();
		ball->applyForce(gravity * ball->mass);

		if (ball->finished()) RemoveBall(ball);
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

	attractor->draw(m_pRenderer);
	_walker->draw(m_pRenderer);

	for (Mover* mover : movers)
	{
		mover->draw(m_pRenderer);
	}

	filledCircleRGBA(m_pRenderer, 25, HEIGHT - 20, 6, 255, 255, 255, 255);
	lineRGBA(m_pRenderer, 25, HEIGHT - 20, 40, HEIGHT - 40, 255, 255, 255, 255);

	for (Ball* ball : balls)
	{
		ball->draw(m_pRenderer);
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	delete _walker;

	for (int i = 0; i < movers.size(); i++)
	{
		delete movers[i];
	}
	movers.clear();

	for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
	}
	balls.clear();

	TheInputHandler::Instance()->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	m_pWindow = NULL;
	m_pRenderer = NULL;

	SDL_Quit();
}

//==================================================

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);

	if (m_pWindow != NULL)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pRenderer);
	}
	else
	{
		return false; // � � � l
	}

	m_bRunning = true;

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

	return true;
}

bool Game::running()
{
	return m_bRunning;
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

bool Game::KeyIsDown(SDL_Scancode code)
{
	return InputHandler::Instance()->isKeyDown(code);
}

void Game::RemoveBall(Ball* ball)
{
	balls.erase(std::remove(std::begin(balls), std::end(balls), ball), std::end(balls));
}