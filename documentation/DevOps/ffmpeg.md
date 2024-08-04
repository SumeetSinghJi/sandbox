# Complete C++ FFMPEG SETUP GUIDE 2024

Very length answer but this will teach you FFMPEG to play/playback video with audio from the bottom to the top like a Wizard!

Full guide here: https://stackoverflow.com/questions/77742801/how-do-i-include-ffmpeg-for-development-in-a-windows-program/

## How to add FFMPEG library to your code

FFMPEG is the largest open source multimedia framework for video playback and codec methods.
FFMPEG requires building if you require include, libs and .dll's to utilise in a C/C++ program.

Step 1. Download this video - https://archive.org/download/NyanCatoriginal_201509
the download link is here: https://archive.org/download/NyanCatoriginal_201509/Nyan%20Cat%20%5Boriginal%5D.mp4

Step 2. Use an image splitter free program to split the audio and video e.g. I used this website
https://restream.io/tools/audio-extractor
to upload the video "Nyan cat [original]" and clicked split audio - then downloaded the audio file.

Step 3. Name the video file "nyan_cat_video.mp4" and the audio file "nyan_cat_audio.mp3

Step 4. Initialise SDL in your program

Step 5. Build FFMPEG following steps below

_______________________________________________________

WINDOWS - you can build with MSYS2 and running below commands in Mingw-64 shell

first install MSYS2 from the Github releases page here - https://github.com/msys2/msys2-installer/releases/tag/nightly-x86_64

download the msys2-x86_64-latest.exe and follow instructions to install, generally choose the C:/ drive as the installation location e.g. c:/msys2

start the mingw64 shell within (as it's the easiest to work with) and run the below so that the MSYS2 Linux environment on Windows has all the dependencies to build FFMPEG
```bash
pacman -Syu --noconfirm &&
          pacman -S --noconfirm mingw-w64-x86_64-toolchain \
          mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer \
          mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-yasm mingw-w64-x86_64-gtest make git
```

Then once the linux environment is setup on your computer you can build using the same MSYS2 shell run the below commands. Note you can choose to disable programs during configure with ```--disable-programs``` e.g. ```./configure --prefix=C:/ffmpeg --enable-shared --enable-gpl --disable-programs``` if you don't want them. Note running the configure command may take some time be patient.

```bash
mkdir -p C:/ffmpeg
cd c:\ffmpeg
git clone https://git.ffmpeg.org/ffmpeg.git .
./configure --prefix=C:/ffmpeg --enable-shared --enable-gpl
make -j$(nproc)
make install
```



Copy lib and include files to your c++ compilers locations
```bash
Copy-Item -Path C:/ffmpeg/lib/pkgconfig -Destination "C:/msys2/mingw64/bin" -Recurse -Force
Copy-Item -Path C:/ffmpeg/bin/* -Destination "C:/msys2/mingw64/bin" -Recurse -Force
Copy-Item -Path C:/ffmpeg/include/* -Destination "C:/msys2/mingw64/include" -Recurse -Force
Copy-Item -Path C:/ffmpeg/lib/* -Destination "C:/msys2/mingw64/lib" -Recurse -Force
```

Copy the dll's to your projects directory next to your main.cpp for example
```bash
Copy-Item -Path C:/msys2/mingw64/bin/avcodec-61.dll C:/Documents/nyancat -Force
Copy-Item -Path C:/msys2/mingw64/bin/avformat-61.dll C:/Documents/nyancat -Force
Copy-Item -Path C:/msys2/mingw64/bin/avutil-59.dll C:/Documents/nyancat -Force
Copy-Item -Path C:/msys2/mingw64/bin/swresample-5.dll C:/Documents/nyancat -Force
```
Link to your main program (I included all SDL libs for ease of use)
```bash
-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
-lavformat -lavcodec -lavutil -lswscale -lavfilter -mwindows
```
_______________________________________________________

MACOS - no need to build, brew has it already run in CLI: brew install ffmpeg
Note you will need to use brew to install all the SDL libs
 No DLL required
 Link to your main program (i included all sdl libs for ease of use)
```bash
     -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavformat -lavcodec -lavutil -lswscale
```
_______________________________________________________

LINUX - run below code
Note you will need to use apt etc., to install all the SDL libs. Note you can choose to disable programs during configure with ```--disable-programs``` e.g. ```./configure --prefix=C:/ffmpeg --enable-shared --enable-gpl --disable-programs``` if you don't want them. Note running the configure command may take some time be patient.

```bash
git clone https://git.ffmpeg.org/ffmpeg.git .
./configure --prefix=${HOME}/ffmpeg/install  --enable-shared --enable-gpl
make -j$(nproc)
sudo make install
```



Then copy the ffmpeg include and lib files into your usr lib and include
```bash
sudo cp -rf ${HOME}/ffmpeg/install/include/* /usr/include
sudo cp -rf ${HOME}/ffmpeg/install/lib/* /usr/lib
```

Copy the DLL's from the /usr/lib folder do your projects directory so these sit next to your main.cpp
```bash
sudo cp /usr/lib/libavutil.so ~/Documents/nyancat
sudo cp /usr/lib/libswscale.so ~/Documents/nyancat
sudo cp /usr/lib/libavformat.so ~/Documents/nyancat
sudo cp /usr/lib/libavcodec.so ~/Documents/nyancat
sudo cp /usr/lib/libswresample.so ~/Documents/nyancat
```

link the following
```bash 
"-lavformat", "-lavcodec", "-lavutil", "-lswscale", "-lswresample",
```
_______________________________________________________

 EXAMPLE

 Step 6. Include this class in desired program
 ```bashinclude <FFmpegVideoPlayer.hpp>```

 Step 7. You will need SDL so that you can pass a window/renderer. If you don't know how to use SDL
 I suggest you first learn from YouTube + ChatGPT. That's how I learnt.
 Then in your code enter the below

 ```bashFFmpegVideoPlayer videoPlayer("nyan_cat_video.mp4", "nyan_cat_audio.mp4", window, renderer);```

 Step 8. Play the video. It will block the stack until it ends like any standard function.
 So within your main loop you can call it like this
```bash
 int main() {
   std::cout << "Meow!" << std::endl;

   sdl_start();

   // Play Intro video for game/movie etc.
   FFmpegVideoPlayer videoPlayer("nyan_cat_video.mp4", "nyan_cat_audio.mp4", window, renderer);
   videoPlayer.playVideo();

   // Then start the rest of the program
   sdl_run();
   sdl_exit();

   return 0;
 }
```
Step 9. A complete steps 6 - 8 is below for your ease of use name this file as main.cpp;
*/
```cpp
#include <iostream>
#include <SDL2/SDL.h>
#include "FFmpegPlayer.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;

SDL_Window *window{};
SDL_Renderer *renderer{};

void sdl_start() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error: Failed to initialise SDL: " << SDL_GetError() << std::endl;
        exit(1);
    } else {
        std::cerr << "Success: initialised: SDL2" << std::endl;
    }

    window = SDL_CreateWindow("BubbleUp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (!window) {
        std::cerr << "Error: Failed to create SDL Window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    } else {
        std::cerr << "Success: initialised: SDL2 window" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error: Failed to create Renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    } else {
        std::cerr << "Success: initialised: SDL2 renderer" << std::endl;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Set blend mode
}

void handle(bool &quitEventLoop) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quitEventLoop = true;
        }
    }
}

void update() {
    // Update game state here
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
    // Draw game elements here
    SDL_RenderPresent(renderer);
}

void sdl_run() {
    bool quitEventLoop = false;
    while (!quitEventLoop) {
        handle(quitEventLoop);
        update();
        draw();
    }
}

void sdl_exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    std::cout << "Meow!" << std::endl;

    sdl_start();

    // Play Intro video for game/movie etc.
    FFmpegVideoPlayer videoPlayer("nyan_cat_video.mp4", "nyan_cat_audio.mp3", window, renderer);
    videoPlayer.playVideo();

    // Then start the rest of the program
    sdl_run();
    sdl_exit();

    return 0;
}
```

Step 10. Create a file called FFmpegPlayer.h and fill with code below

```cpp
#ifndef FFMPEGPLAYER_H
#define FFMPEGPLAYER_H
/*
    Author: ENTER YOUR NAME HERE AVATAR
    Dated: ENTER TODAYS DATE HERE
    Minimum C++ Standard: C++17
    Purpose: Class Declaration file
    License: MIT License
*/

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
}
 
class FFmpegVideoPlayer
{
private:
    const char *videoFile{}; /**< the video filepath to play */
    const char *musicFile{}; /**< the audio filepath to play, split from video, currently this code is not working to isolate audio stream requires manual splitting */
    SDL_Window *window{}; /**< the SDL Window to play the video on passed as a reference in an existing SDL app */
    SDL_Renderer *renderer{}; /**< the SDL renderer to play the video on passed as a reference in an existing SDL app */
    AVFormatContext *formatCtx{}; /**< the video file */
    int videoStreamIndex{}; /**< the found and split video stream */
    int audioStreamIndex{}; /**< the found and split audio stream */
    const AVCodec *videoCodec{}; /**< the found video codec */
    const AVCodec *audioCodec{}; /**< the found audio codec */
    AVCodecContext *videoCodecCtx{}; /**< the found video codec */
    AVCodecContext *audioCodecCtx{}; /**< the found audio codec */
    Mix_Music *music{}; /**< the SDL mixer to play the audio on passed as a reference in an existing SDL app */

public:

/**
 * @brief default FFmpegVideoPlayer constructor
*/
    FFmpegVideoPlayer(const char *videoFile, const char *musicFile, SDL_Window *window, SDL_Renderer *renderer)
        : videoFile(videoFile), musicFile(musicFile), window(window), renderer(renderer), formatCtx(nullptr),
          videoStreamIndex(-1), audioStreamIndex(-1), videoCodec(nullptr), audioCodec(nullptr),
          videoCodecCtx(nullptr), audioCodecCtx(nullptr), music(nullptr)
    {
        avformat_network_init();

        // Open the input file
        if (avformat_open_input(&formatCtx, videoFile, nullptr, nullptr) < 0)
        {
            char errbuf[AV_ERROR_MAX_STRING_SIZE];
            av_strerror(errno, errbuf, AV_ERROR_MAX_STRING_SIZE);
            std::cerr << "Error: Could not open Video file: " << videoFile << " - " << errbuf << std::endl;
            return;
        }

        // // Debug: Printing stream information for debugging
        // std::cout << "Debug: Printing stream information for debugging:" << std::endl;
        // av_dump_format(formatCtx, 0, videoFile, 0);

        // Find the stream information
        if (avformat_find_stream_info(formatCtx, nullptr) < 0)
        {
            char errbuf[AV_ERROR_MAX_STRING_SIZE];
            av_strerror(errno, errbuf, AV_ERROR_MAX_STRING_SIZE);
            std::cerr << "Error: Could not find stream information: " << errbuf << std::endl;
            avformat_close_input(&formatCtx); // Close input on failure
            return;
        }

        // Find the first video stream and audio stream
        for (unsigned int i = 0; i < formatCtx->nb_streams; i++)
        {
            if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && videoStreamIndex < 0)
            {
                videoStreamIndex = i;
                std::cout << "Found Video Stream: Index " << videoStreamIndex << std::endl;
                // // Debug: Print video codec information
                // std::cout << "Debug: Video Codec Information:" << std::endl;
                // av_dump_format(formatCtx, videoStreamIndex, videoFile, 0);
            }
            else if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && audioStreamIndex < 0)
            {
                audioStreamIndex = i;
                std::cout << "Found Audio Stream: Index " << audioStreamIndex << std::endl;
                // // Debug: Print audio codec information
                // std::cout << "Debug: Audio Codec Information:" << std::endl;
                // av_dump_format(formatCtx, audioStreamIndex, videoFile, 0); // Changed this line
            }
        }

        if (videoStreamIndex == -1 && audioStreamIndex == -1)
        {
            std::cerr << "Error: Could not find video or audio stream." << std::endl;
            avformat_close_input(&formatCtx); // Close input on failure
            return;
        }

        // Open video codec
        if (videoStreamIndex >= 0)
        {
            videoCodecCtx = avcodec_alloc_context3(nullptr);
            if (!videoCodecCtx)
            {
                std::cerr << "Error: Could not allocate video codec context." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            avcodec_parameters_to_context(videoCodecCtx, formatCtx->streams[videoStreamIndex]->codecpar);
            videoCodec = avcodec_find_decoder(videoCodecCtx->codec_id);
            if (!videoCodec)
            {
                std::cerr << "Error: Could not find video codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            if (avcodec_open2(videoCodecCtx, videoCodec, nullptr) < 0)
            {
                std::cerr << "Error: Could not open video codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
        }

        // Open audio codec
        if (audioStreamIndex >= 0)
        {
            audioCodecCtx = avcodec_alloc_context3(nullptr);
            if (!audioCodecCtx)
            {
                std::cerr << "Error: Could not allocate audio codec context." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            avcodec_parameters_to_context(audioCodecCtx, formatCtx->streams[audioStreamIndex]->codecpar);
            audioCodec = avcodec_find_decoder(audioCodecCtx->codec_id);
            if (!audioCodec)
            {
                std::cerr << "Error: Could not find audio codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }
            if (avcodec_open2(audioCodecCtx, audioCodec, nullptr) < 0)
            {
                std::cerr << "Error: Could not open audio codec." << std::endl;
                avformat_close_input(&formatCtx); // Close input on failure
                return;
            }

            // Initialize SDL Mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
            {
                std::cerr << "Error: Failed to open audio channel: " << Mix_GetError() << std::endl;
                return;
            }

            // Initialize music with SDL Mixer
            music = Mix_LoadMUS(musicFile);
            if (!music)
            {
                std::cerr << "Error: Failed to load music file: " << Mix_GetError() << std::endl;
                return;
            }
        }
    }

/**
 * @brief default FFmpegVideoPlayer deconstructor
*/
    ~FFmpegVideoPlayer()
    {
        if (videoCodecCtx)
        {
            avcodec_free_context(&videoCodecCtx);
        }
        if (audioCodecCtx)
        {
            avcodec_free_context(&audioCodecCtx);
        }
        if (formatCtx)
        {
            avformat_close_input(&formatCtx);
        }
        if (music)
        {
            Mix_FreeMusic(music);
        }
        Mix_CloseAudio();
    }

/**
 * @brief play audioFile
 *
 * The audio playback pipeline is below
 *
 * Original file -> split into videoFile/musicFile -> musicFile -> initialise SDL_Mixer -> Mix_PlayMusic -> playAudio() -> playVideo() {playAudio()}
*/
    void playAudio() const
    {
        // Play music
        if (Mix_PlayMusic(music, 0) == -1)
        {
            std::cerr << "Error: Failed to play music: " << Mix_GetError() << std::endl;
            return;
        }
    }

/**
 * @brief play the video and call the audio at the same time
 *
 * The video playback pipeline is below
 *
 * Original file -> split into videoFile/musicFile -> videoFile -> videoStream -> while (packet -> frame -> texture -> renderer)
 *
 * Their is an input event loop because it's important to allow moving/resizing/closing the window while the video is playing
 * if you havn't initialised the event loop outside of this function yet.
 *
*/
void playVideo() const
{
    // Check if constructor initialised successfully
    if (!formatCtx || !videoCodecCtx || !audioCodecCtx)
    {
        std::cerr << "Error: FFmpeg initialization failed." << std::endl;
        return;
    }

    // Create SDL texture
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
                                             videoCodecCtx->width, videoCodecCtx->height);
    if (texture == nullptr)
    {
        std::cerr << "Error: Could not create SDL texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Allocate frame
    AVFrame *frame = av_frame_alloc();
    AVPacket packet;

    // Calculate delay to achieve desired frame rate
    double frame_delay = 1.0 / av_q2d(formatCtx->streams[videoStreamIndex]->avg_frame_rate);

    // Start audio playback
    playAudio();

    // Start video playback loop
    bool end_of_stream = false; // Flag to track end of video stream
    while (!end_of_stream)      // Loop until end of stream
    {
        // Read video frames
        while (!end_of_stream && av_read_frame(formatCtx, &packet) >= 0)
        {
            if (packet.stream_index == videoStreamIndex)
            {
                avcodec_send_packet(videoCodecCtx, &packet);
                avcodec_receive_frame(videoCodecCtx, frame);

                SDL_RenderClear(renderer);

                // Update the video texture
                SDL_UpdateYUVTexture(texture, nullptr,
                                     frame->data[0], frame->linesize[0],
                                     frame->data[1], frame->linesize[1],
                                     frame->data[2], frame->linesize[2]);

                // Render the video frame
                SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                SDL_RenderPresent(renderer);

                // Delay the video so that it plays at the same speed as video stream
                SDL_Delay((Uint32)(frame_delay * 1000)); // Convert to milliseconds

                /*
                    It's necessary to have an event loop here.
                    The reason is while the video is playing, if you move the window
                    SDL expects their to be a key input handle loop logic to take care of this event
                    but because their are no case for events it will crash.

                    Thus we initialise a fake event loop and also pressing any button skips the cutscene which
                    can be customised
                */
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                    case SDL_KEYDOWN:
                    case SDL_CONTROLLERBUTTONDOWN:
                    case SDL_MOUSEBUTTONDOWN:
                    case SDL_FINGERDOWN:
                        end_of_stream = true;
                        break;
                    }
                }
            }
            av_packet_unref(&packet);
        }

        // When video stream ends, quit and return
        if (av_read_frame(formatCtx, &packet) == AVERROR_EOF)
            end_of_stream = true;
    }

    // Cleanup
    av_frame_free(&frame);
    SDL_DestroyTexture(texture);
}

};

#endif //FFMPEGPLAYER_H
```

Step 11. Ensure that your list of files looks like the below. Note I included the DLL's for both Linux and Windows. If your just building on
windows then only copy those dll's over. The reason I have both is to make the software multiplatform (portable)
```bash
avcodec-61.dll
avformat-61.dll
avutil-59.dll
FFmpegPlayer.h
libavcodec.so
libavformat.so
libavutil.so
libcurl-4.dll
libswresample.so
libswscale.so
main.cpp
nyan_cat_audio.mp3
nyan_cat_video.mp4
SDL2.dll
SDL2_image.dll
SDL2_mixer.dll
SDL2_TTF.dll
swresample-5.dll
```

Step 12. Build by running the below in the command line: 
```bash
PS C:\Users\Sumeet\Documents\nyancat> g++ main.cpp -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavcodec -lavformat -lavutil -lswscale -lswresample
PS C:\Users\Sumeet\Documents\nyancat> ./main.exe
Meow!
Success: initialised: SDL2
Success: initialised: SDL2 window
Success: initialised: SDL2 renderer
Found Video Stream: Index 0
Found Audio Stream: Index 1
PS C:\Users\Sumeet\Documents\nyancat>
```
Step 13. Done. Be proud of yourself Avatar!

Step 14 (OPTIONAL) CMAKE - 
Install cmake on your computer by running the below code in your CLI
Macos: brew install cmake
Linux: sudo apt install cmake
Windows: winget install CMake

Then create a CMAKElists.txt and enter code in below and run 
```cmake
cmake_minimum_required(VERSION 3.28)
project(nyancat)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add your source files
add_executable(nyancat main.cpp
        FFmpegPlayer.h)

# Include directories for FFmpeg
include_directories(C:/ffmpeg/include)

# Link directories for FFmpeg
link_directories(C:/ffmpeg/lib)

# Link SDL + FFmpeg libraries (mingw32 is optional as that's for my Windows MSYS2 setup)
target_link_libraries(nyancat
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        avformat
        avcodec
        avutil
        swscale
        swresample
)
```
then run the below to use Cmake to compile the software and output a binary/executable main.exe/main
```bash
cmake ..
make
```