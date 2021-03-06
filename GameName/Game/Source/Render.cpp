#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Entities.h"
#include "Defs.h"
#include "Log.h"
#include "Input.h"
#define VSYNC true

Render::Render(bool isActive) : Module(isActive)
{
	name.Create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
	toSave = true;
	saveConfigs = true;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
		isVSYNC = true;
	}
	else
	{
		isVSYNC = false;
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = app->win->screenSurface->w;
		camera.h = app->win->screenSurface->h;
		camera.x = 0;
		camera.y = 0;
	}

	return ret;
}

// Called before the first frame
bool Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	cameraDrag = false;
	dragging = false;
	borderMovement = false;
	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::Update(float dt)
{
	if((app->input->GetKey(SDL_SCANCODE_M)) ==  KEY_DOWN)
		isFreeCam = !isFreeCam;

	CameraMovement();

	
	return true;
}

bool Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// method to load the state, for now load camera's x and y
// Load Game State
bool Render::LoadState(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// method to save the state of the renderer
// Save Game State
bool Render::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

bool Render::SaveConfig(pugi::xml_node& data) const
{
	pugi::xml_node ren = data.append_child("vsync");

	ren.append_attribute("value") = isVSYNC;

	return true;
}

void Render::SetVSYNC(bool vsync)
{
	this->isVSYNC = vsync;
	if (vsync)
	{
		SDL_GL_SetSwapInterval(1);
	}
	else {
		SDL_GL_SetSwapInterval(0);
	}
}

bool Render::GetVSYNC()
{
	return isVSYNC;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::CameraFocus(iPoint position)
{
	if (!isFreeCam)
	{
		camera.x = -(position.x * app->win->GetScale() - camera.w * 0.5f);
		camera.y = -(position.y * app->win->GetScale() - camera.h * 0.5f);
	}
}

void Render::CameraMovement()
{
	if (isFreeCam)
	{
		if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
		{
			camera.x += 10;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
		{
			camera.x -= 10;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))
		{
			camera.y += 10;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT))
		{
			camera.y -= 10;
		}
	}
	else if (cameraDrag)
	{
		int distanceX = 0;
		int distanceY = 0;

		KeyState mouseRightButton = app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT);

		if (mouseRightButton == KEY_DOWN && !dragging)
		{
			app->input->GetMousePosition(dragPointX, dragPointY);
			dragging = true;

			
		}
		int pos_x = 0;
		int pos_y = 0;
		
		if (mouseRightButton == KEY_REPEAT)
		{
			
			app->input->GetMousePosition(pos_x, pos_y);

			distanceX = pos_x - dragPointX;
			distanceY = pos_y - dragPointY;
		}

		/*LOG("dragging %i", dragging);
		LOG("dragPoint x: %i", dragPointX);
		LOG("dragPoint y: %i", dragPointY);
		LOG("pos_x: %i", pos_x);
		LOG("pos_y: %i", pos_y);
		LOG("distance x: %i", (int)((float)distanceX / cameraMultiplier));
		LOG("distance y: %i", (int)((float)distanceY / cameraMultiplier));
		*/

		if (mouseRightButton == KEY_UP)
		{
			dragging = false;
		}


		camera.x -= (int) (distanceX / 100);
		camera.y -= (int) (distanceY / 100);

	}
	else if (borderMovement)
	{
		int pos_x, pos_y;
		app->input->GetMousePosition(pos_x, pos_y);

		if (pos_x < borderMargin && -camera.x - borderCamSpeed > 0)
		{
			camera.x -= borderCamSpeed * -1;
		}

		if (pos_x > app->win->GetWidth() - borderMargin && -(camera.x + app->win->GetWidth()) + borderCamSpeed < 32 * 44)
		{
			camera.x += borderCamSpeed * -1;
		}

		if (pos_y < borderMargin && -camera.y - borderCamSpeed > 0)
		{
			camera.y -= borderCamSpeed * -1;
		}

		if (pos_y > app->win->GetHeight() - borderMargin && -(camera.y + app->win->GetHeight()) + borderCamSpeed < 32 * 44)
		{
			camera.y += borderCamSpeed * -1;
		}

	}


}

void Render::ResetCameraPosition()
{
	camera.x = 0;
	camera.y = 0;
}

void Render::DeactivateCamerMovement()
{
	cameraFollowCombat = false;
}

void Render::ActivateCameraCombat()
{
	cameraFollowCombat = true;
	playerFollowing = app->entities->players.getFirst()->data;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

// Blit to screen
bool Render::DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY, float multiplier, SDL_RendererFlip dir) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(section != NULL)
	{
		rect.w = section->w * multiplier;
		rect.h = section->h * multiplier;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if(pivotX != INT_MAX && pivotY != INT_MAX)
	{
		pivot.x = pivotX;
		pivot.y = pivotY;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, dir) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for (uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Render::DrawTextureScaled(SDL_Texture* texture, int x, int y, int width, int height, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY) const
{
	bool ret = true;
	uint scale = app->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	rect.w = width * scale;
	rect.h = height * scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivotX != INT_MAX && pivotY != INT_MAX)
	{
		pivot.x = pivotX;
		pivot.y = pivotY;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
