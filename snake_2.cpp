#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;

void SDL_RenderDrawCircle(SDL_Renderer * renderer, int centreX, int centreY, int radius) {
	int X; int Y; int F;
	for (int F = 0; F < 360; ++F) SDL_RenderDrawPoint(renderer, centreX + radius * cos(F), centreY - radius * sin(F));
	}

class Part{
	private:
		// 	Ссылка на следующий кусок
		Part* next;
		Part* prev;
		// Свой порядковый номер, для отладки
		int partNum;
		// Координаты по-умолчанию..
		int x=-1;
		int y=-1;

	public:
		// Part* prev;
		// Part* next;

	Part(Part* prev, int partNum){
		this->partNum = partNum;
		this->prev = prev;
		this->next = nullptr;
		}

	void step(int x, int y){
		int ox=this->x;
		int oy=this->y;
		this->x=x;
		this->y=y;
		if(this->next != nullptr) next->step(ox,oy);
		}
	// void eat
	void eat(int cnt){
		// if(this->next == nullptr)
			// Part next;
			// next=Part(this, 2);
		/// ?????????????????????????????????????????????????????????
		}
	// void eat
	void draw(SDL_Renderer* screen){
			SDL_SetRenderDrawColor(screen, 0xFF, 0xFF, 0xFF, 0xFF);
			if(this->next != nullptr)
				SDL_RenderDrawCircle(screen, this->x*30+20, this->y*30+20, 5);
			else
				SDL_RenderDrawCircle(screen, this->x*30+20, this->y*30+20, 10);

		}
	};

class Snake{
	// Кординаты головы змеи.
	int x = 10;
	int y = 10;
	int dx;
	int dy; 	
	Part head = Part(nullptr, 0);
	Part body = Part(&head, 1);
	// Part body = Part(&body, 1);
	unsigned int arrow;


	public:
		// Два конструктора??? *********
		// ~ ?? *********
		Snake(){
			SDL_Log("Constructor");
			// printf("%s\n", type(head.next));

			}


		void last(){
			// return;
			// return 10;
			}

		void eat(int cnt){
			printf("%s", "Нямс:");
			printf("%i\n", cnt);
			int n=0;
			body.eat(cnt);
			while(++n<=cnt){
				printf("%i\n", n);
				}

			}

		void step(int arrow){
			printf("%i\n", arrow);
			int ox=this->x;
			int oy=this->y;
			if(arrow == 1) this->y-=1;
			if(arrow == 2) this->x+=1;
			if(arrow == 3) this->y+=1;
			if(arrow == 4) this->x-=1;
			body.step(ox,oy);
			}

		void draw(SDL_Renderer* screen){
			

			body.draw(screen);
			SDL_SetRenderDrawColor(screen, 0xFF, 0, 0, 0xFF);

			SDL_RenderDrawCircle(screen, this->x*30+20, this->y*30+20, 10);


			}

		// НАХ const?? ****
		void check() const{
			SDL_Log("checked!");
		}
	};



class Game{
	// ? Создавать их в конструкторе с проверкой!!
	SDL_Window *window = SDL_CreateWindow("+", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
	SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);			
	protected:
		int field[50][50];
	public:
		Game(){
			if (SDL_Init(SDL_INIT_VIDEO) < 0) { exit(1);}
			if (this->window == NULL) { SDL_Quit(); exit(2); }

			SDL_SetRenderDrawColor(this->s, 0, 0, 0, 0xFF);
			SDL_RenderClear(this->s);
	        SDL_RenderPresent(s);

			printf("%s\n", "clsd");
			// SDL_SetRenderDrawColor(this->s, 0xFF, 0xFF, 0xFF, 0xFF);

			}
		void quit(){
			SDL_DestroyWindow(this->window);
			SDL_DestroyRenderer(this->s);
			printf("%s\n", "exit 0");
			SDL_Quit();
			}

		// Заполнение поля
		void fill(){
			SDL_SetRenderDrawColor(this->s, 0, 0x40, 0, 0xFF);
			for (int x = 0; x < 20; ++x)
				for (int y = 0; y < 20; ++y)
					SDL_RenderDrawCircle(this->s, x*30+20,y*30+20,10);
			SDL_SetRenderDrawColor(this->s, 0, 0, 0, 0xFF);

		}

		// Меню
		void menu(){
			/// Обработчик меню, если выбрано играть - 
				this->play();

			this->quit();
			}

		// Игровой процесс
		void play(){
			// Заполняем поле
			SDL_Event event;
			Snake snake;// = Snake(this->s);
			int arrow = 0;
			bool play = true;
			int dx;
			int dy;

			while(play){
				while (SDL_PollEvent(&event)) {
							switch (event.type) {
								case SDL_QUIT: SDL_Log("sQUIrT"); play = false; break;
								case SDL_KEYDOWN:
								// Завершаемся при нажатии Esc...
								if (event.key.keysym.sym == SDLK_ESCAPE) play = false;
								// Управление
				                if (event.key.keysym.sym == SDLK_RIGHT) arrow=2;
				                if (event.key.keysym.sym == SDLK_LEFT) arrow=4;
				                if (event.key.keysym.sym == SDLK_UP) arrow=1;
				                if (event.key.keysym.sym == SDLK_DOWN) arrow=3;
				                // ЖРУУ !!
				                if (event.key.keysym.sym == SDLK_KP_PLUS)
				                	snake.eat(5);
								break;

								default:;
								}

								} // обработка закрытия
							SDL_SetRenderDrawColor(this->s, 0, 0, 0, 0xFF);
							SDL_RenderClear(this->s);

							this->fill();
							snake.step(arrow);

							snake.draw(s);
							SDL_RenderPresent(s);

				}
			}

		void draw(){}

	};


// Фция рисования окружности
int main() {
	SDL_Event evt;

	Game game;
	game.play();
	game.quit();

	}
