class Snake{
private:
	SDL_Renderer * s;
	int _arrow = 4;
	std::list<Part> body;
	std::map<std::string, SDL_Texture*> textures/* = {
		{"tbody",  SDL_CreateTextureFromSurface(s, IMG_Load("textures/body.png"))},
		{"thead",  SDL_CreateTextureFromSurface(s, IMG_Load("textures/head.png"))},
		{"ttail1",  SDL_CreateTextureFromSurface(s, IMG_Load("textures/tail1.png"))},
		{"ttail2",  SDL_CreateTextureFromSurface(s, IMG_Load("textures/tail2.png"))},
		}*/;

public:
	Snake(SDL_Renderer * s){
		this->s = s;
		textures["tbody"]	=   SDL_CreateTextureFromSurface(s, IMG_Load("textures/body.png"));
		textures["thead"]	=   SDL_CreateTextureFromSurface(s, IMG_Load("textures/head.png"));
		textures["ttail1"]	= SDL_CreateTextureFromSurface(s, IMG_Load("textures/tail1.png"));
		textures["ttail2"]	= SDL_CreateTextureFromSurface(s, IMG_Load("textures/tail2.png"));
		body.push_back(Part(10, 10));
		body.push_back(Part(10, 10));
		}
}
