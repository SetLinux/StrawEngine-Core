#pragma once
#include "../Addons/Sprite.h"

#include <GL/glew.h>
#include "../Math/Math.h"
#include <vector>
#include <algorithm>
#include <deque>
#include <map>
#include <unordered_map>

#define SPRITESIZE sizeof(Vertex) * 4
#define MAXSPRITES 190000
#define BUFFERSIZE SPRITESIZE * MAXSPRITES
#define INDICESBUFFERSIZE MAXSPRITES * 6
struct RenderBatch{
public:
  RenderBatch(){
    sprites.reserve(100000);
  };

public:
  unsigned int TextureID;
  std::vector<Sprite*> sprites;

};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Init();
	void Begin();
	//Submit a Sprite to the Renderer remember to end it after
	void Submit(Sprite* input);
	void End();
	void Looper();
private:
	void InnerSubmit(Sprite* input);
	int IndNum(int vecnum);
	int IndNumMap(int mapnum);
	unsigned int m_VAO, m_VBO, m_IBO;
	int m_IndexCounter;
	Vertex* m_Buffer;
	std::vector<RenderBatch*> renderBatches;
	std::map<int,std::vector<Sprite*>> RQ;
};

