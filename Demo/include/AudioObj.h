#ifndef AUDIOOBJ_H
#define AUDIOOBJ_H

#include <stdexcept>
#include "location.h"
#include "velocity.h"
#include "complex.h"
#include "CircBuff.h"
#include "WavObject.h"

using namespace std;
#define BUFFER_CAPACITY 65000 //This will be capacity of circular buffer and also size of memory allocated in wavObject

class AudioObj {
	
	Location location;
    Velocity velocity;
    bool active;
    float volume;
    bool repeat;
    CircBuff<complex> circBuff;
    WavObject wavObject;
    int Azimuth;
    int elevation;
    bool toLoadMoreData;

    
public:

	//Creates a new audio object at the world's origin, {0,0,0}.
    AudioObj(const std::string wavFileName) : active(false), volume(1), repeat(true), circBuff(BUFFER_CAPACITY), wavObject(BUFFER_CAPACITY, wavFileName), toLoadMoreData(true) {
        wavObject.loadMoreData(32768, repeat);
        circBuff.write(wavObject.complexTempData, 32768);
        }

	//Creates a new audio object at the location specified by the parameter.
    AudioObj(const Location& loc, const Velocity& vel, const std::string wavFileName) : location(loc), velocity(vel), active(false), volume(1), repeat(true), circBuff(BUFFER_CAPACITY), wavObject(BUFFER_CAPACITY, wavFileName), toLoadMoreData(true) {
        wavObject.loadMoreData(32768, repeat);
        circBuff.write(wavObject.complexTempData, 32768);
    }
    
    AudioObj(const std::string wavFileName, int Azi, int ele):active(false), volume(1), repeat(true), circBuff(BUFFER_CAPACITY), wavObject(BUFFER_CAPACITY, wavFileName), Azimuth(Azi), elevation(ele), toLoadMoreData(true)
    {
        wavObject.loadMoreData(32768, repeat);
        circBuff.write(wavObject.complexTempData, 32768);
        
    }
    
    ~AudioObj () { }
	
	//Returns the array of the object's location.
	Location getLocation() const;
    
    //Changes the object's location to that which is specifies in the parameter.
	void setLocation (const Location& loc);
	void setLocation (VariableForLocation x, VariableForLocation y, VariableForLocation z);
    
    Velocity getVelocity() const;
    int getAzimuth()
    {
        return Azimuth;
    }
    int getElevation()
    {
        return elevation;
    }
    void setVelocity (const Velocity& vel);
    void setVelocity (VariableForVelocity dx, VariableForVelocity dy, VariableForVelocity dz);
    
    //Returns the volume of the audio object.
	//This will be a value from 0 to 1.
	float getVolume() const;
    
    //Sets the volume of the audio object. This will only accept values from 0 to 1.
	void setVolume(float vol);

	//Returns whether or not the object is active
	bool isActive() const;

	//Changes whether or not the object is active
	void setActive(bool active);
    
    bool fillAudioData(complex *, unsigned int);
    
    void writeCircBuff (void);
    
};

#endif