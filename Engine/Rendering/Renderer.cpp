#include "Renderer.h"
#include "../Game/Entity.h"

Renderer::Renderer()
    : m_VBO(0), m_VAO(0), m_IBO(0), m_IndexCounter(0), m_Buffer(nullptr) {}

Renderer::~Renderer() {}
void Renderer::Looper() {}
int Renderer::IndNum(int vecnum) {
  int counter = 0;
  return counter;
}

void Renderer::InnerSubmit(Sprite *input) {

  m_Buffer->position = input->vertices[0].position;
  m_Buffer->TexCoord = input->vertices[0].TexCoord;
  m_Buffer++;
  m_Buffer->position = input->vertices[1].position;
  m_Buffer->TexCoord = input->vertices[1].TexCoord;
  m_Buffer++;
  m_Buffer->position = input->vertices[2].position;
  m_Buffer->TexCoord = input->vertices[2].TexCoord;
  m_Buffer++;
  m_Buffer->position = input->vertices[3].position;
  m_Buffer->TexCoord = input->vertices[3].TexCoord;
  m_Buffer++;
  m_IndexCounter += 6;
}
int Renderer::IndNumMap(int mapnumb) {
  int counter = 0;
  for (int i = 0; i < mapnumb; i++) {
    counter += RQ[i].size();
  }

  return counter;
}
void Renderer::Init() {

  unsigned int indices[INDICESBUFFERSIZE];
  int m_offset = 0;
  for (int i = 0; i < INDICESBUFFERSIZE; i += 6) {
    indices[i + 0] = (m_offset + 0);
    indices[i + 1] = (m_offset + 1);
    indices[i + 2] = (m_offset + 3);
    indices[i + 3] = (m_offset + 1);
    indices[i + 4] = (m_offset + 2);
    indices[i + 5] = (m_offset + 3);
    m_offset += 4;
  }
  glGenBuffers(1, &m_IBO);
  glGenBuffers(1, &m_VBO);
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, BUFFERSIZE, NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               INDICESBUFFERSIZE * sizeof(unsigned int), indices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex,Vertex::position)));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, Vertex::TexCoord));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
void Renderer::Begin() {
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  m_Buffer = (Vertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}
void Renderer::Submit(Sprite *input) {
  if (input->Visible) {
    RQ[(int)(input->tex->GetID())].emplace_back(input);
    if (RQ[(int)(input->tex->GetID())].size() <= 1) {
      RQ[(int)(input->tex->GetID())].reserve(190000);
    }
  }
}

void Renderer::End() {

  for (auto &it : RQ) {
    for (std::vector<Sprite *>::iterator ia = it.second.begin();
         ia != it.second.end(); ++ia) {

      InnerSubmit((*ia));
    }
  }

  glUnmapBuffer(GL_ARRAY_BUFFER);
  int conter = 0;
  for (auto &it : RQ) {
    glBindTexture(GL_TEXTURE_2D, it.second[0]->tex->GetID());
    glDrawElements(GL_TRIANGLES, it.second.size() * 6, GL_UNSIGNED_INT,
                   (void *)(conter * 6 * sizeof(unsigned int)));
    conter += it.second.size();
    it.second.clear();
  }
  RQ.clear();
}
