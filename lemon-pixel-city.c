#include "Camera.h"
#include "Car.h"
#include "Entity.h"
#include "glTypes.h"
#include "Ini.h"
#include "Macro.h"
#include "Random.h"
#include "Render.h"
#include "Texture.h"
#include "Win.h"
#include "World.h"
#include "Visible.h"

#define has_pixel_city

#include <time.h>

class pixel_city: public obj
{
    void keyp(int key, int uni, int mod)
    {
	switch (key)
	{
    	    case SDLK_F1:
	    RenderHelpToggle ();
	    break;
    	    case SDLK_F5:
	    CameraReset ();
	    break;
    	    case SDLK_UP:
	    CameraMedial (1.0f);
	    break;
    	    case SDLK_DOWN:
	    CameraMedial (-1.0f);
	    break;
    	    case SDLK_LEFT:
	    CameraLateral (1.0f);
	    break;
    	    case SDLK_RIGHT:
	    CameraLateral (-1.0f);
	    break;
    	    case SDLK_PAGEUP:
	    CameraVertical (1.0f);
	    break;
    	    case SDLK_PAGEDOWN:
	    CameraVertical (-1.0f);
	    break;
	    case SDLK_r:
	    WorldReset();
	    break;
	    case SDLK_w:
	    RenderWireframeToggle();
	    break;
	    case SDLK_e:
	    RenderEffectCycle();
	    break;
	    case SDLK_l:
	    RenderLetterboxToggle();
	    break;
	    case SDLK_f:
	    RenderFPSToggle();
	    break;
	    case SDLK_g:
	    RenderFogToggle();
	    break;
	    case SDLK_t:
	    RenderFlatToggle();
	    break;
	    case SDLK_c:
	    CameraAutoToggle();
	    break;
	    case SDLK_b:
	    CameraNextBehavior();
	    break;
	}
    }
    void draw (int picking)
    {
	if(!picking)
	{
	    CameraUpdate ();
	    EntityUpdate ();
    	    WorldUpdate ();
    	    TextureUpdate ();
            VisibleUpdate ();
            CarUpdate ();
        }
        RenderUpdate (picking);
    }
    pixel-city()
    {
	time_t t=time (NULL);
	RandomInit (t);
	logit("pixel-city initialized with time %u", t);
	CameraInit ();
        RenderInit ();
        TextureInit ();
        WorldInit ();
    }
    ~pixel-city()
    {
	TextureTerm ();
	WorldTerm ();
	RenderTerm ();
	CameraTerm ();
	WinTerm ();
    }
};
