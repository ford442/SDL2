#include "../include/SDL.h"
#include "../include/SDL_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
EM_JS(void,ma,(),{let d=S();if(d)d();d=S();function S(){let w=document.getElementById("iwid").innerHTML;let h=document.getElementById("ihig").innerHTML;w=Math.round(w);h=Math.round(h);let g=new GPU;let Rn=document.getElementById("frate").innerHTML;let l=(w*h*4);let m=((l/65536)+1);m=Math.floor(m);let W=new WebAssembly.Memory({initial:m});let o=[w,h];let k=document.getElementById("cp");let v=document.getElementById("mv");let t=g.createKernel(function(v){let p=v[this.thread.y][this.thread.x];return[p[0],p[1],p[2]];}).setTactic("precision").setPipeline(true).setOutput(o).setStrictIntegers(true).setFixIntegerDivisionAccuracy(false);let r=g.createKernel(function(f){let p=f[this.thread.y][this.thread.x];this.color(p[0],p[1],p[2]);}).setTactic("precision").setGraphical(true).setOutput(o).setStrictIntegers(true).setFixIntegerDivisionAccuracy(false);
let $=new Uint8ClampedArray(W.buffer,0,l);$.set(t(v),0);r(t($));$.set(t(v),0);k.appendChild(r.canvas);r(t($));$.set(t(v),0);let T=false;let ms=1;let R=16;let f=(1000/Rn);let canvas=document.querySelector("canvas");canvas.style.cssText="image-rendering:pixelated;";function M(){if(T){return;}r(t($));$.set(t(v),0);let mq=((ms*f)/R);let k=Math.floor(mq);let y=((k*f)-(k*Rn));if(y>8){R=8;}ms=ms+1;setTimeout(function(){M();},R);}M();document.getElementById("di").onclick=function(){T=true;k.removeChild(r.canvas);t.destroy();r.destroy();g.destroy();S();};return()=>{k.removeChild(r.canvas);T=true;};}});
int main(){ma();return (0);}
static struct{SDL_AudioSpec spec;Uint8 *snd;Uint32 slen;int pos;}wave;
static SDL_AudioDeviceID dev;
static void cls_aud(){if(dev != 0){SDL_CloseAudioDevice(dev);dev=0;}}
static void qu(int rc){cls_aud();SDL_FreeWAV(wave.snd);SDL_Quit();exit(rc);}
static void opn_aud(){dev=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);if(!dev){SDL_FreeWAV(wave.snd);qu(2);}SDL_PauseAudioDevice(dev,SDL_FALSE);}
static void reopn_aud(){cls_aud();opn_aud();}
void SDLCALL bfr(void *unused,Uint8 *stm,int len){Uint8 *wptr;int lft;wptr=wave.snd+wave.pos;lft=wave.slen-wave.pos;
while (lft <= len){SDL_memcpy(stm,wptr,lft);stm+=lft;len-=lft;wptr=wave.snd;lft=wave.slen;wave.pos=0;}
SDL_memcpy(stm,wptr,len);wave.pos+=len;}
static int done=0;
void lp(){if(done || (SDL_GetAudioDeviceStatus(dev) != SDL_AUDIO_PLAYING))emscripten_cancel_main_loop();}
void pl(){SDL_PauseAudioDevice(dev,SDL_TRUE);int i;char flnm[4096];cls_aud();SDL_FreeWAV(wave.snd);emscripten_cancel_main_loop();
if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0){qu (1);}
SDL_strlcpy(flnm,"/sample.wav",sizeof(flnm));
if(SDL_LoadWAV(flnm,&wave.spec,&wave.snd,&wave.slen) == NULL){qu(1);}
wave.pos=0;
wave.spec.callback=bfr;opn_aud();
// SDL_FlushEvents(SDL_AUDIODEVICEADDED,SDL_AUDIODEVICEREMOVED);
emscripten_set_main_loop(lp,1,0);}
