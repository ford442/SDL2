
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
EM_JS(void,ma,(),{let d=S();if(d)d();d=S();function S(){let w=document.getElementById("iwid").innerHTML;let h=document.getElementById("ihig").innerHTML;w=Math.round(w);h=Math.round(h);let g=new GPU;let Rn=document.getElementById("frate").innerHTML;let l=(w*h*4);let m=((l/65536)+1);m=Math.floor(m);let W=new WebAssembly.Memory({initial:m});let o=[w,h];let k=document.getElementById("cp");let v=document.getElementById("mv");let t=g.createKernel(function(v){let p=v[this.thread.y][this.thread.x];return[p[0],p[1],p[2]];}).setTactic("precision").setPipeline(true).setOutput(o).setStrictIntegers(true).setFixIntegerDivisionAccuracy(false);let r=g.createKernel(function(f){let p=f[this.thread.y][this.thread.x];this.color(p[0],p[1],p[2]);}).setTactic("precision").setGraphical(true).setOutput(o).setStrictIntegers(true).setFixIntegerDivisionAccuracy(false);
let $=new Uint8ClampedArray(W.buffer,0,l);$.set(t(v),0);r(t($));$.set(t(v),0);k.appendChild(r.canvas);r(t($));$.set(t(v),0);let T=false;let ms=1;let R=16;let f=(1000/Rn);let canvas=document.querySelector("canvas");canvas.style.cssText="image-rendering:pixelated;";function M(){if(T){return;}r(t($));$.set(t(v),0);let mq=((ms*f)/R);let k=Math.floor(mq);let y=((k*f)-(k*Rn));if(y>8){R=8;}ms=ms+1;setTimeout(function(){M();},R);}M();document.getElementById("di").onclick=function(){T=true;k.removeChild(r.canvas);t.destroy();r.destroy();g.destroy();S();};return()=>{k.removeChild(r.canvas);T=true;};}});
static struct{SDL_AudioSpec spec;Uint8 *sound;Uint32 soundlen;int soundpos;}wave;
static SDL_AudioDeviceID device;
static void close_audio(){if(device != 0){SDL_CloseAudioDevice(device);device=0;}}
static void quit(int rc){close_audio();SDL_FreeWAV(wave.sound);SDL_Quit();exit(rc);}
static void open_audio(){device=SDL_OpenAudioDevice(NULL,SDL_FALSE,&wave.spec,NULL,0);if(!device){SDL_FreeWAV(wave.sound);quit(2);}SDL_PauseAudioDevice(device,SDL_FALSE);}
static void reopen_audio(){close_audio();open_audio();}
void SDLCALL fillerup(void *unused,Uint8 *stream,int len){Uint8 *waveptr;int waveleft;waveptr=wave.sound+wave.soundpos;waveleft=wave.soundlen-wave.soundpos;
while (waveleft <= len){SDL_memcpy(stream,waveptr,waveleft);stream+=waveleft;len-=waveleft;waveptr=wave.sound;waveleft=wave.soundlen;wave.soundpos=0;}
SDL_memcpy(stream,waveptr,len);wave.soundpos+=len;}
static int done=0;
void loop(){if(done || (SDL_GetAudioDeviceStatus(device) != SDL_AUDIO_PLAYING))emscripten_cancel_main_loop();}
void pl(){int i;char filename[4096];close_audio();SDL_FreeWAV(wave.sound);wave.soundpos=0;emscripten_cancel_main_loop();
if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0){quit (1);}
SDL_strlcpy(filename,"/sample.wav",sizeof(filename));
if(SDL_LoadWAV(filename,&wave.spec,&wave.sound,&wave.soundlen) == NULL){quit(1);}
wave.spec.callback=fillerup;open_audio();
SDL_FlushEvents(SDL_AUDIODEVICEADDED,SDL_AUDIODEVICEREMOVED);
emscripten_set_main_loop(loop,1,0);}
int main(){ma();return (0);}
