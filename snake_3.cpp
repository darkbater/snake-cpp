#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Part{
public:
	int x;
	int y;
	Part(int x,int y){
		this->x=x;
		this->y=y;
		}
	void test(){
		printf("%i:", this->x);
		printf("%i\n", this->y);
		}
	void step(int x, int y){
		this->x=x;
		this->y=y;
		}
	};

class Snake{
private:
	int _arrow = 4;
	std::list<Part> body;

public:
	Snake(){
		body.push_back(Part(10, 10));
		body.push_back(Part(11, 10));
		body.push_back(Part(12, 10));
		}

	void arrow(int arrow){
		this->_arrow=arrow;
		}

	void draw(SDL_Renderer* s){
		// this->_arrow=arrow;
		SDL_Surface * image = IMG_Load("textures/body.png");
		// SDL_Surface * image = SDL_LoadBMP("textures/body.bmp");
		// SDL_Surface * i2 = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_Texture * snake = SDL_CreateTextureFromSurface(s, image);
		   SDL_SetTextureBlendMode(snake, SDL_BLENDMODE_BLEND);

		SDL_Rect dstrect={
			w:32,
			h:32,
			};
		// SDL_RenderCopy(s, snake, NULL, NULL);
		// SDL_SetTextureBlendMode(snake, SDL_BLENDMODE_BLEND);
		// SDL_SetTextureAlphaMod(snake, 127);


		for(Part &p : body){
			dstrect.x=p.x*32+200;
			dstrect.y=p.y*32+75;
			SDL_RenderCopy(s, snake, NULL, &dstrect);
			}

		SDL_DestroyTexture(snake);
		// SDL_RenderPresent(s);

		}

	void step(){
		int nx = body.front().x;
		int ny = body.front().y;
		int ox;
		int oy;
		printf("%s\n", "step");
		switch (_arrow){case 1:--ny;break;
						case 2:++nx;break;
						case 3:++ny;break;
						case 4:--nx;break;
						};
		if(nx<0)nx=19;
		if(ny<0)ny=19;
		if(nx>=20)nx=0;
		if(ny>=20)ny=0;
		for(Part &p : body){
			ox=p.x;oy=p.y;
			p.step(nx,ny);
			nx=ox;ny=oy;
			}
		}

	void test(){
		printf("%s\n", "test");
		for(Part p : body){
			printf("%i:", p.x);
			printf("%i\n", p.y);
			}
		}
	};

class Game{
	Snake snake;
	SDL_Window *window = SDL_CreateWindow("+", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
	SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);			
	SDL_Surface * image =  SDL_LoadBMP("textures/grass.bmp");
	SDL_Texture * grass =  SDL_CreateTextureFromSurface(this->s, this->image);

public:
	Game(){
		SDL_SetRenderDrawColor(s,0,0,0,255);
		// SDL_RenderClear(s);
		SDL_RenderPresent(s);
		}

	void cls(){
		SDL_SetRenderDrawColor(this->s,0,0,0,255);
		// SDL_RenderClear(this->s);
		SDL_RenderPresent(this->s);

		}
	void field(){
		int x; int y;

		SDL_Rect dstrect={
			w:32,
			h:32,
			};
		printf("%s\n", "start");
		// SDL_RenderCopy(this->s, grass, NULL, NULL);

		for (int dx = 0; dx < 20; ++dx){
			for (int dy = 0; dy < 20; ++dy){
				x = dx*32+200;
				y = dy*32+75;
				dstrect.x=x;
				dstrect.y=y;
				SDL_RenderCopy(this->s, grass, NULL, &dstrect);
				}
			}
		// SDL_RenderPresent(this->s);
		}
	void play(){
		SDL_Event event;
		this->field();
		snake.draw(s);
		SDL_RenderPresent(s);
		bool play = true;
		while(play){ // Игровой процесс
			while (SDL_PollEvent(&event)) {/// События
						switch (event.type) {
							case SDL_QUIT: SDL_Log("sQUIrT"); play = false; break;
							case SDL_KEYDOWN:
								switch(event.key.keysym.sym){
									// Завершаемся при нажатии Esc...
									case SDLK_ESCAPE:	play = false;break;
									// Управление
				                	case SDLK_RIGHT:	snake.arrow(2);break;
				                	case SDLK_LEFT:		snake.arrow(4);break;
				                	case SDLK_UP:		snake.arrow(1);break;
				                	case SDLK_DOWN:		snake.arrow(3);break;
				                	// Тесть
				                	case SDLK_KP_ENTER:	{
						                	// this->cls();
						                	printf("%s\n", "enter");
						                	snake.step();
						                	this->field();
						                	// snake.draw(this->s);
						                	snake.draw(this->s);
						                	// snake.test();
											SDL_RenderPresent(s);
						                	break;
											}
				                	};
								break;
							default:;
							}

						} // События
	               	// this->cls();
                	printf("%s\n", "enter");
                	SDL_Delay(100);
                	snake.step();
                	this->field();
                	// snake.draw(this->s);
                	snake.draw(this->s);
                	// snake.test();
					SDL_RenderPresent(s);

					} /// Игровой процесс

		};

	void quit(){
		SDL_DestroyTexture(grass);
		SDL_DestroyWindow(this->window);
		SDL_DestroyRenderer(this->s);
		printf("%s\n", "exit 0");
		SDL_Quit();
		exit(0);
		}

	void menu(){
		this->play();
		};
	};

int main(){
	Game game;
	game.menu();
	}
