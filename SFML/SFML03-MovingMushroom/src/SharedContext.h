#pragma once
#include "Window.h"
#include "EventManager.h"

struct SharedContext
{
	SharedContext() : mWindow(nullptr), mEventManager(nullptr) {}
	Window *mWindow;
	EventManager *mEventManager;
};