source ~/emsdk/emsdk_env.sh

^ Or wherever you have it.

git clone https://github.com/ford442/SDL2.git 

cd SDL2

cd test

emcc wav.c -o sdl2.js -O3 -sENVIRONMENT=web -sINITIAL_MEMORY=1400mb -sALLOW_MEMORY_GROWTH=0 -s MALLOC="emmalloc" -sFORCE_FILESYSTEM=1 -sEXPORTED_FUNCTIONS='["_main","_pl"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' --closure 1 -g0 -flto=full -sSUPPORT_LONGJMP=0 --pre-js filesys.js --extern-post-js ccall.js -sUSE_SDL=2 




                         Simple DirectMedia Layer

                                  (SDL)

                                Version 2.0

---
https://www.libsdl.org/

Simple DirectMedia Layer is a cross-platform development library designed
to provide low level access to audio, keyboard, mouse, joystick, and graphics
hardware via OpenGL and Direct3D. It is used by video playback software,
emulators, and popular games including Valve's award winning catalog
and many Humble Bundle games.

More extensive documentation is available in the docs directory, starting
with README.md

Enjoy!
	Sam Lantinga				(slouken@libsdl.org)
