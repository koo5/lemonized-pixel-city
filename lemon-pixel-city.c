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

#include <time.h>
#include <map>

class pixel_city: public obj
{
    public:
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
    pixel_city()
    {
	time_t t=time (NULL);
	RandomInit (t);
	CameraInit ();
        RenderInit ();
        TextureInit ();
        WorldInit ();
    }
    ~pixel_city()
    {
	TextureTerm ();
	WorldTerm ();
	RenderTerm ();
	CameraTerm ();
	WinTerm ();
    }
    SAVE(pixel_city)
    {
	YAML_EMIT_PARENT_MEMBERS(out,obj)
    }
    LOAD
    {
	YAML_LOAD_PARENT_MEMBERS(doc,obj)
    }
	
    static map<string,string>ini;
};
map<string,string>pixel_city::ini;
#define FORMAT_VECTOR       "%f %f %f"
#define MAX_RESULT          256
#define FORMAT_FLOAT        "%1.2f"
int IniInt (char* entry)
{
    map<string,string>::iterator I;
    I=pixel_city::ini.find(entry);
    if(I==pixel_city::ini.end())
    return 0;
    else
    return atoi(I->second.c_str());
}
void IniIntSet (char* entry, int val)
{
  char        buf[20];
  sprintf (buf, "%d", val);
  pixel_city::ini[entry]=buf;
}
float IniFloat (char* entry)
{
    map<string,string>::iterator I;
    I=pixel_city::ini.find(entry);
    if(I==pixel_city::ini.end())
    return 0;
    else
    return atof(I->second.c_str());
}
void IniFloatSet (char* entry, float val)
{
  char        buf[20];
  sprintf (buf, FORMAT_FLOAT, val);
  pixel_city::ini[entry]=buf;
}
void IniVectorSet (char* entry, GLvector v)
{
  char result[MAX_RESULT]; 
  sprintf (result, FORMAT_VECTOR, v.x, v.y, v.z);
  pixel_city::ini[entry]=result;
}
GLvector IniVector (char* entry)
{
    GLvector  v;
    map<string,string>::iterator I;
    I=pixel_city::ini.find(entry);
    if(I==pixel_city::ini.end())
    v.x = v.y = v.z = 0.0f;
    else
    sscanf (I->second.c_str(), FORMAT_VECTOR, &v.x, &v.y, &v.z);
    return v;
}
