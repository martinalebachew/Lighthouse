// application.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the webapp wrapper class Application.
*/

#include "application.hpp"

Application::Application() {
  app_ = App::Create();
  window_ = Window::Create(
    app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT, false,
    kWindowFlags_Titled | kWindowFlags_Hidden
  );

  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);
  overlay_->Resize(window_->width(), window_->height());

  overlay_->view()->LoadURL("file:///index.html");
  window_->Show();

  app_->set_listener(this);
  window_->set_listener(this);
  overlay_->view()->set_load_listener(this);
  overlay_->view()->set_view_listener(this);
}

void Application::Run() {
  app_->Run();
}

void Application::OnUpdate() {
  // This is called repeatedly from the application's update loop.
  // You should update any app logic here.
}

void Application::OnClose(ultralight::Window* window) {
  app_->Quit();
}

void Application::OnDOMReady(
  ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const String &url
) {
  // This is called when a frame's DOM has finished loading on the page.
  // This is the best time to setup any JavaScript bindings.
}

void Application::OnChangeCursor(ultralight::View* caller, Cursor cursor) {
  window_->SetCursor(cursor);
}

void Application::OnChangeTitle(ultralight::View* caller, const String &title) {
  window_->SetTitle(title.utf8().data());
}
