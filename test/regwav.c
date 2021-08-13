#include"../include/SDL.h"
#include"../include/SDL_config.h"
#include<stdio.h>
#include<stdlib.h>
#include<emscripten/emscripten.h>
static struct{SDL_AudioSpec spec;Uint8 *snd;Uint32 slen;int pos;}wave;
static SDL_AudioDeviceID dev;
static void cls_aud(){if(dev!=0){SDL_PauseAudioDevice(dev,SDL_TRUE);SDL_CloseAudioDevice(dev);dev=0;}}
static void qu(register int rc){SDL_Quit();exit(rc);}
static void opn_aud(){dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);if(!dev){SDL_FreeWAV(wave.snd);qu(2);}SDL_PauseAudioDevice(dev,SDL_FALSE);}
static void reopn_aud(){cls_aud();opn_aud();}
void SDLCALL bfr(void *unused,Uint8 *stm,register int len){Uint8 *wptr;register int lft;wptr=wave.snd+wave.pos;lft=wave.slen-wave.pos;
while(lft<=len){SDL_memcpy(stm,wptr,lft);stm+=lft;len-=lft;wptr=wave.snd;lft=wave.slen;wave.pos=0;}
SDL_memcpy(stm,wptr,len);wave.pos+=len;}
// static int done=0;
void lp(){
// if(done||(SDL_GetAudioDeviceStatus(dev)!=SDL_AUDIO_PLAYING))emscripten_cancel_main_loop();
}
void pl(){register int i;char flnm[4096];cls_aud();SDL_FreeWAV(wave.snd);emscripten_cancel_main_loop();SDL_Quit();
if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS)<0){qu(1);}
SDL_strlcpy(flnm,"/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen)==NULL){qu(1);}
wave.pos=0;
wave.spec.callback=bfr;opn_aud();
// SDL_FlushEvents(SDL_AUDIODEVICEADDED,SDL_AUDIODEVICEREMOVED);
emscripten_set_main_loop(lp,1,0);}
int main(){return (0);}
