___________________________________________________________________________

              C++ COMPILE, TEST, AND RELEASE
___________________________________________________________________________


name: test and release software

on:
  push:
    branches:
      - main

jobs:
  build_and_test_windows:
    runs-on: windows-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up MSYS2
      uses: msys2/setup-msys2@v2
      with:
        msystem: MINGW64
        update: true

    - name: Install dependencies
      shell: msys2 {0}
      run: |
        pacman -Syu --noconfirm &&
          pacman -S --noconfirm mingw-w64-x86_64-toolchain \
          mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer \
          mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-libzip mingw-w64-x86_64-zlib \
          mingw-w64-x86_64-boost mingw-w64-x86_64-curl-winssl mingw-w64-x86_64-yasm \
          mingw-w64-x86_64-gtest make git

    - name: Check C compiler
      shell: msys2 {0}
      run: |
        echo "#include <stdio.h>" > test.c
        echo 'int main() { printf("Hello, world!\\n"); return 0; }' >> test.c
        gcc -o test test.c
        ./test

    - name: Print MSYS2 variables
      shell: msys2 {0}
      run: |
        # For troubleshooting e.g. Running these commands locally to match the remote
        echo "PATH: $PATH"
        echo "MSYSTEM: $MSYSTEM"
        echo "MINGW_PACKAGE_PREFIX: $MINGW_PACKAGE_PREFIX"
        gcc --version
        g++ --version
        where gcc

    - name: Copy dependencies DLLs
      shell: msys2 {0}
      run: |
        cp /mingw64/bin/libboost_system-mt.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/SDL2.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/SDL2_image.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/SDL2_mixer.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/SDL2_ttf.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/libcurl-4.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/libzip.dll "D:/a/BubbleUp/BubbleUp/"
        cp /mingw64/bin/zlib1.dll "D:/a/BubbleUp/BubbleUp/"
        # google test has no dll header only, and -link lib during compile

    - name: Ensure FFmpeg directory exists
      run: mkdir -p C:/ffmpeg

    - name: Cache FFmpeg build
      id: ffmpeg-cache
      uses: actions/cache@v2
      with:
        path: C:/ffmpeg
        key: ${{ runner.os }}-ffmpeg-${{ hashFiles('ffmpeg/.git/HEAD') }}
        restore-keys: |
          ${{ runner.os }}-ffmpeg-

    - name: Build FFmpeg
      shell: msys2 {0}
      if: steps.ffmpeg-cache.outputs.cache-hit != 'true'
      run: |
        cd C:/ffmpeg
        git clone https://git.ffmpeg.org/ffmpeg.git .
        ./configure --prefix=C:/ffmpeg --enable-shared --enable-gpl --disable-programs
        make -j$(nproc)
        make install

    - name: Copy ffmpeg files to /mingw64
      run: |
        Remove-Item -Recurse C:/ffmpeg/lib/pkgconfig -Force
        Copy-Item -Path C:/ffmpeg/bin/* -Destination "D:/a/_temp/msys64/mingw64/bin" -Recurse -Force
        Copy-Item -Path C:/ffmpeg/include/* -Destination "D:/a/_temp/msys64/mingw64/include" -Recurse -Force
        Copy-Item -Path C:/ffmpeg/lib/* -Destination "D:/a/_temp/msys64/mingw64/lib" -Recurse -Force

    - name: Copy FFmpeg DLLs to workspace
      run: |
        Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avcodec-61.dll ${{ github.workspace }}/ -Force
        Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avformat-61.dll ${{ github.workspace }}/ -Force
        Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/avutil-59.dll ${{ github.workspace }}/ -Force
        Copy-Item -Path D:/a/_temp/msys64/mingw64/bin/swresample-5.dll ${{ github.workspace }}/ -Force

    - name: Compile test binary
      run: |
        g++ -fdiagnostics-color=always -I${{ github.workspace }}/headers -ID:/a/_temp/msys64/mingw64/include  `
          -g ${{ github.workspace }}/tests/testcases.cpp ${{ github.workspace }}/src/*.cpp `
          ${{ github.workspace }}/src/buttons/*.cpp ${{ github.workspace }}/src/entities/*.cpp `
          -o ${{ github.workspace }}/tests/testcases.exe -LD:/a/_temp/msys64/mingw64/lib `
          -lboost_system-mt -lws2_32 -lmingw32 -lSDL2main -lSDL2 `
          -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgtest -lgtest_main -lcurl -lzip -lz `
          -lavformat -lavcodec -lavutil -lswscale -lavfilter -mwindows

    - name: Test test binary
      run: |
        cd tests
        mv testcases.exe ..
        cd ..
        ./testcases.exe

    - name: Compile final binary
      run: |
        g++ -fdiagnostics-color=always `
          -g ${{ github.workspace }}/main.cpp ${{ github.workspace }}/src/*.cpp `
          ${{ github.workspace }}/src/buttons/*.cpp ${{ github.workspace }}/src/entities/*.cpp `
          -o ${{ github.workspace }}/main.exe `
          -I${{ github.workspace }}/headers -ID:/a/_temp/msys64/mingw64/include -LD:/a/_temp/msys64/mingw64/lib `
          -lboost_system-mt -lws2_32 -lmingw32 -lSDL2main -lSDL2 `
          -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgtest -lgtest_main -lcurl -lzip -lz `
          -lavformat -lavcodec -lavutil -lswscale -lavfilter -mwindows
      if: success()

    - name: Package artifacts
      run: |
        New-Item -ItemType Directory -Path "dist/windows" -Force
        Copy-Item -Path "assets" -Destination "dist/windows" -Recurse
        Copy-Item -Path "docs" -Destination "dist/windows" -Recurse
        Copy-Item -Path "etc" -Destination "dist/windows" -Recurse
        Copy-Item -Path "headers" -Destination "dist/windows" -Recurse
        Copy-Item -Path "src" -Destination "dist/windows" -Recurse
        Copy-Item -Path "dist/Heroes3MapLiker.exe" -Destination "distwindows"
        Copy-Item -Path "avcodec-61.dll" -Destination "dist/windows"
        Copy-Item -Path "avformat-61.dll" -Destination "dist/windows"
        Copy-Item -Path "avutil-59.dll" -Destination "dist/windows"
        Copy-Item -Path "CREDITS.md" -Destination "dist/windows"
        Copy-Item -Path "game_log.txt" -Destination "dist/windows"
        Copy-Item -Path "libboost_system-mt.dll" -Destination "dist/windows"
        Copy-Item -Path "libcurl-4.dll" -Destination "dist/windows"
        Copy-Item -Path "libzip.dll" -Destination "dist/windows"
        Copy-Item -Path "LICENSE" -Destination "dist/windows"
        Copy-Item -Path "README.md" -Destination "dist/windows"
        Copy-Item -Path "SDL2.dll" -Destination "dist/windows"
        Copy-Item -Path "SDL2_image.dll" -Destination "dist/windows"
        Copy-Item -Path "SDL2_mixer.dll" -Destination "dist/windows"
        Copy-Item -Path "SDL2_ttf.dll" -Destination "dist/windows"
        Copy-Item -Path "swresample-5.dll" -Destination "dist/windows"
        Copy-Item -Path "zlib1.dll" -Destination "dist/windows"
        Compress-Archive -Path "dist/windows/*" -DestinationPath "dist/Heroes3MapLiker-windows.zip"

    - name: Upload artifact
      uses: actions/upload-artifact@v2
      with:
        name: windows-zip
        path: dist/BubbleUP-windows.zip

  build_and_test_macos:
    runs-on: macos-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Install dependencies
      run: |
        brew install gcc boost ffmpeg googletest libzip sdl2 sdl2_image sdl2_mixer sdl2_ttf

    - name: Compile test binary 
      run: |
        clang++ -fcolor-diagnostics -fansi-escape-codes -std=c++17 -stdlib=libc++ \
          -I/opt/homebrew/include \
          -I${{ github.workspace }}/headers -g ${{ github.workspace }}/tests/testcases.cpp \
          ${{ github.workspace }}/src/*.cpp ${{ github.workspace }}/src/buttons/*.cpp \
          ${{ github.workspace }}/src/entities/*.cpp \
          -o ${{ github.workspace }}/tests/testcases \
          -L/opt/homebrew/lib \
          -lboost_system -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavformat -lavcodec \
          -lavutil -lswscale -lgtest -lcurl -lzip

    - name: Test test binary 
      run: |
        cd tests
        mv testcases ..
        cd ..
        ./testcases

    - name: Compile final binary
      run: |
        cd ..
        clang++ -fcolor-diagnostics -fansi-escape-codes -std=c++17 -stdlib=libc++ \
          -I/opt/homebrew/include \
          -I${{ github.workspace }}/headers -g ${{ github.workspace }}/main.cpp \
          ${{ github.workspace }}/src/*.cpp ${{ github.workspace }}/src/buttons/*.cpp \
          ${{ github.workspace }}/src/entities/*.cpp \
          -o ${{ github.workspace }}/main \
          -L/opt/homebrew/lib \
          -lboost_system -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lavformat -lavcodec \
          -lavutil -lswscale -lgtest -lcurl -lzip
      if: success()

    - name: Package artifacts
      run: |
        mkdir -p dist/macos
        cp -r assets dist/macos/
        cp -r docs dist/macos/
        cp -r etc dist/macos/
        cp -r headers dist/macos/
        cp -r src dist/macos/
        cp dist/Heroes3MapLiker dist/macos/
        cp CREDITS.md dist/macos/
        cp game_log.txt dist/macos/
        cp LICENSE dist/macos/
        cp README.md dist/macos/
        zip -r dist/Heroes3MapLiker-macos.zip dist/macos/*

    - name: Upload artifact
      uses: actions/upload-artifact@v2
      with:
        name: macos-zip
        path: dist/BubbleUP-macos.zip

  build_and_test_linux:
    runs-on: ubuntu-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Install build dependencies
      run: |
          sudo apt update
          sudo apt install -y build-essential g++ libboost-all-dev libcurl4-gnutls-dev libzip-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev googletest libgtest-dev yasm
    
    - name: Ensure FFmpeg directory exists
      run: mkdir -p ${HOME}/ffmpeg

    - name: Cache FFmpeg build
      id: ffmpeg-cache
      uses: actions/cache@v2
      with:
        path: ${HOME}/ffmpeg
        key: ${{ runner.os }}-ffmpeg-${{ hashFiles('ffmpeg/.git/HEAD') }}
        restore-keys: |
          ${{ runner.os }}-ffmpeg-

    - name: Build FFmpeg
      if: steps.ffmpeg-cache.outputs.cache-hit != 'true'
      run: |
        cd ${HOME}/ffmpeg
        git clone https://git.ffmpeg.org/ffmpeg.git .
        ./configure --prefix=${HOME}/ffmpeg/install  --enable-shared --enable-gpl --disable-programs
        make -j$(nproc)
        sudo make install
    
    - name: Copy FFmpeg files to /usr
      run: |
        sudo cp -rf ${HOME}/ffmpeg/install/include/* /usr/include
        sudo cp -rf ${HOME}/ffmpeg/install/lib/* /usr/lib

    - name: Copy FFmpeg shared libs to workspace
      run: |
        cp /usr/lib/libavutil.so ${{ github.workspace }}
        cp /usr/lib/libswscale.so ${{ github.workspace }}
        cp /usr/lib/libavformat.so ${{ github.workspace }}
        cp /usr/lib/libavcodec.so ${{ github.workspace }}
        cp /usr/lib/libswresample.so ${{ github.workspace }}

    - name: Compile test binary
      run: |
        g++ -g ${{ github.workspace }}/tests/testcases.cpp ${{ github.workspace }}/src/*.cpp \
          ${{ github.workspace }}/src/buttons/*.cpp ${{ github.workspace }}/src/entities/*.cpp \
          -o ${{ github.workspace }}/tests/testcases -std=c++17 \
          -I${{ github.workspace }}/headers -I/usr/include -I/usr/include/x86_64-linux-gnu -I/usr/include \
          -L/usr/lib -L/usr/lib \
          -lboost_system -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgtest -lcurl -lzip \
          -lavutil -lswscale -lavformat -lavcodec -lswresample

    - name: Check if running on headless display
      id: check_headless
      run: |
        if status=$(sudo systemctl status display-manager 2>/dev/null); then
          if [[ $status == *"Unit display-manager.service could not be found."* ]]; then
            echo "::set-output name=headless::true"
          else
            echo "::set-output name=headless::false"
          fi
        else
          echo "::set-output name=headless::false"
        fi

    - name: Test test binary
      if: steps.check_headless.outputs.headless != 'true'
      run: |
        cd tests
        mv testcases ..
        cd ..
        ./testcases

    - name: Compile final binary
      run: |
        cd ..
        g++ -g ${{ github.workspace }}/main.cpp ${{ github.workspace }}/src/*.cpp \
          ${{ github.workspace }}/src/buttons/*.cpp ${{ github.workspace }}/src/entities/*.cpp \
          -o ${{ github.workspace }}/main -std=c++17 \
          -I${{ github.workspace }}/headers -I/usr/include -I/usr/include/x86_64-linux-gnu -I/usr/include \
          -L/usr/lib -L/usr/lib \
          -lboost_system -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgtest -lcurl -lzip \
          -lavutil -lswscale -lavformat -lavcodec -lswresample
      if: success()

    - name: Package artifacts
      run: |
        mkdir -p dist/linux
        cp -r assets dist/linux/
        cp -r docs dist/linux/
        cp -r etc dist/linux/
        cp -r headers dist/linux/
        cp -r src dist/linux/
        cp dist/Heroes3MapLiker dist/linux/
        cp CREDITS.md dist/linux/
        cp game_log.txt dist/linux/
        cp libavcodec.so.61.6.100 dist/linux/
        cp libavformat.so.61.3.104 dist/linux/
        cp libavutil.so.59.21.100 dist/linux/
        cp libswresample.so.5.2.100 dist/linux/
        cp libswscale.so.8.2.100 dist/linux/
        cp LICENSE dist/linux/
        cp README.md dist/linux/
        zip -r dist/Heroes3MapLiker-linux.zip dist/linux/*

    - name: Upload artifact
      uses: actions/upload-artifact@v2
      with:
        name: linux-zip
        path: dist/BubbleUP-linux.zip

  create_release:
    needs: [build_and_test_windows, build_and_test_macos, build_and_test_linux]
    runs-on: ubuntu-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Download Windows artifact
      uses: actions/download-artifact@v2
      with:
        name: windows-zip
        path: ./dist

    - name: Download macOS artifact
      uses: actions/download-artifact@v2
      with:
        name: macos-zip
        path: ./dist

    - name: Download Linux artifact
      uses: actions/download-artifact@v2
      with:
        name: linux-zip
        path: ./dist

    - name: Create GitHub Release
      id: create_release
      uses: actions/create-release@v1
      env:
        GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
      with:
        tag_name: v1.0.0
        release_name: Release v1.0.0
        draft: false
        prerelease: false

    - name: Upload Windows Release Asset
      uses: actions/upload-release-asset@v1
      env:
        GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
      with:
        upload_url: ${{ steps.create_release.outputs.upload_url }}
        asset_path: ./dist/Heroes3MapLiker-windows.zip
        asset_name: Heroes3MapLiker-windows.zip
        asset_content_type: application/zip

    - name: Upload macOS Release Asset
      uses: actions/upload-release-asset@v1
      env:
        GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
      with:
        upload_url: ${{ steps.create_release.outputs.upload_url }}
        asset_path: ./dist/Heroes3MapLiker-macos.zip
        asset_name: Heroes3MapLiker-macos.zip
        asset_content_type: application/zip

    - name: Upload Linux Release Asset
      uses: actions/upload-release-asset@v1
      env:
        GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
      with:
        upload_url: ${{ steps.create_release.outputs.upload_url }}
        asset_path: ./dist/Heroes3MapLiker-linux.zip
        asset_name: Heroes3MapLiker-linux.zip
        asset_content_type: application/zip