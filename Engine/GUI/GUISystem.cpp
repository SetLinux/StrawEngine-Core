#include "GUISystem.h"
#include "../Game/Game.h"
#include <iostream>

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

std::function<void()> GUI::myDraw{[]() {}};
Game *GUI::gm;
nk_context *GUI::ctx;
nk_colorf GUI::bg;
struct nk_font* GUI::roboto;

void GUI::Init(Game *game, const std::string &ResPath) {

  bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

  ctx = nk_glfw3_init(game->m_Window->m_window, NK_GLFW3_INSTALL_CALLBACKS);
  struct nk_font_atlas *atlas;

  game->m_Window->ctx = ctx;
  nk_glfw3_font_stash_begin(&atlas);
  /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas,
   * "../../../extra_font/DroidSans.ttf", 14, 0);*/
  /*struct nk_font *future = nk_font_atlas_add_from_file(atlas,
   * "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
  /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas,
   * "../../../extra_font/ProggyClean.ttf", 12, 0);*/
  /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas,
   * "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
  /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas,
   * "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
  nk_glfw3_font_stash_end();
}
void GUI::LoadScheme(const std::string &schemeFile) {}
void GUI::SetFont(const std::string &FontFile) {}
void GUI::UpdateGUIIO() {
  //  nk_sdl_handle_event(&event);
  
  nk_glfw3_new_frame();
}

void GUI::BeginRender(float dt) {
  ctx->style.window.fixed_background = nk_style_item_hide();
  nk_begin(ctx, "Demo", nk_rect(0, 0, 1000,1000),NK_WINDOW_NO_SCROLLBAR);
}
void inject_time_pulse(double &last) {
  // inject the time that passed since the last call
  
}
void GUI::StartRow(int width, int height, int columns) {
  nk_layout_row_static(ctx, height,width, columns);
}
bool GUI::Button(const std::string& text){
  return nk_button_label(ctx,text.c_str());
}
void GUI::Label(const std::string &text){
  
  nk_label(ctx,text.c_str(),NK_TEXT_ALIGN_LEFT);
}
void GUI::EndRender() {
  nk_end(ctx);
  nk_glfw3_render(NK_ANTI_ALIASING_ON, 3000000, 300000);

}
