// application.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the webapp wrapper class Application.
*/

#pragma once
#include <AppCore/AppCore.h>

#define WINDOW_WIDTH  979
#define WINDOW_HEIGHT 557

using namespace ultralight;

class Application
  : public AppListener,
    public WindowListener,
    public LoadListener,
    public ViewListener {
public:
  Application();
  void Run();
  void OnUpdate() override;
  void OnClose(ultralight::Window* window) override;
  void OnDOMReady(
    ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const String &url
  ) override;
  void OnChangeCursor(ultralight::View* caller, Cursor cursor) override;
  void OnChangeTitle(ultralight::View* caller, const String &title) override;

protected:
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> overlay_;
};
