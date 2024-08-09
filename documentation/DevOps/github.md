
# PROGRAMMING WITH GITHUB

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS
- [1. Terminologies](#terminologies)
- [2. Requirements](#requirements)
- [3. Installing](#installing)
- [4. Profile script](#profile-script)
- [5. Common Commands](#common-commands)
- [6. Secrets and keys](#secrets-and-keys)
- [7. Caches and Artifacts](#caches-and-artifacts)
- [8. C++ example workflow](#c++-example-workflow)
- [9. React example workflow](#react-example-workflow)
- [10. Python example workflow](#python-example-workflow)

# TERMINOLOGIES

GitHub actions: Refer to the CI/CD pipeline for free offered by GitHub. A playbook file is placed in you're projects codebase
and code is used to configure CI/CD such as compiling the code on a Windows VM then pushing that code to Cloud for production.

Runners: are the VM/Docker platforms that the environment is defined in the yml playbook is run on.
E.g, if you want to test and deploy python code the .yml file will outline steps to install packages on an Ubuntu VM/Docker for subsequent CI/CD
testing before deployment

# REQUIREMENTS

See INSTALATION

# INSTALLATION

Github actions is an CI/CD pipeline to push code to GitHub and trigger any additional commands e.g, to compile, test, push on success, etc.,

To use Github actions in your GitHub project all you need to do is create this file and filepath in the top level of your project
./github/workflows/actions.yml

Then you just define rules as discussed later on within this guide and you have full CI/CD pipeline. GitHub playbooks comes with predefined
code for doing basic instructions such as using a specific VM or setting up a timelimit before a VM stops running and the workflow cancels
to prevent overrunning and consuming resources which could be expensive. GitHub only supports free code up to a certain usage in storage, performance
and time.

To extend the functionality of the playbook such as to adopt new technologies like pushing to a new Cloud provider, third party developers
can create GitHub actions Marketplace workflows which are similar to mini GitHub repositories only for use in playbooks.

## MARKETPLACE

The example playboko below has inbuilt code for naming the workflow job and using a specific runner, but the "uses" keyword
define marketplace workflows such as below "jakejarvis/s3-sync-action@v0.5.1" is a created by a third party developer to extend the
basic CI/CD functionality to allow pushing to S3. This way the playbook can be extended indefinitely and customised however you desire.

```yml
name: actions
run-name: Deploy to S3 bucket

on: [push]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v2
      
      - name: Sync to S3
        uses: jakejarvis/s3-sync-action@v0.5.1
        with:
          args: --delete
        env:
          AWS_S3_BUCKET: sumeet-singh.com
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: us-east-1
          SOURCE_DIR: './build'
```

# PROFILE SCRIPT

N/a

# COMMON COMMANDS

N/a - skip to the invidual examples below

# SECRETS AND KEYS 

Repo's can have Repository/environmental secrets and keys which allow you to add keys such as API's in GitHub repo page
and not within the code base itself. So when the code is pushed to GitHub, a GitHub actions CI/CD workflow will find that secret key
and add it to the code so that it's not exposed.

To add keys you must go to the Repo page - settings - secrets - then choose either for repository or environment
then add the keys name in name field, and the ID value in ID field and save.

Then within a GitHub actions yaml file include the hidden variables e.g, ```${secrets.KEYNAME}```

EXAMPLE 
Website www.agnisamooh.com has a S3 bucket to upload the react website live to.
1. Within AWS a secret Key pair are created as below
[vscode-aws-toolkit]
aws_access_key_id = alksjdalksjdalksjd
aws_secret_access_key = asjdlkasjdlksajdlkajsdsdjsalk
2. Then in the GitHub secrets and variables page they are added: the GitHub repo https://github.com/SumeetSinghJi/agnisamooh.com/settings/secrets/actions
3. Then in the project folder a new path is created under ./github/workflows/actions.yml
4. The below code is added to it. Now when the code is pushed to GitHub the github actions workflow will trigger which builds
the react project, then also pushes it to aws S3 using the secret key pair. This way the keys are not exposed to public
```yml
name: actions
run-name: ${{ github.actor }} Deploy to S3 bucket

on: [push]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v2
      
      - name: Sync to S3
        uses: jakejarvis/s3-sync-action@v0.5.1
        with:
          args: --delete
        env:
          AWS_S3_BUCKET: sumeet-singh.com
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: us-east-1
          SOURCE_DIR: './build'
```

# CACHES AND ARTIFACTS

Caches are for uploading dependencies for persistent storage between runners, whereas artifacts are for workflow job scope only to 
download/push/zip directories/files.

Caches only upload and save if a workflow is succesfull by creating an end task to save cache for next run.
Viewed under github actions in it's own webpage called caches.

Artifacts will upload at the point of that task being complete to the workflows local scope and do not persist for subsequent runs
however they can be downloaded anytime. You could store/retrieve them to/from a external storage such as S3 bucket and then retrieve for another
run or you can identify a succesfull job that stored an artifact and use GitHub API to curl find and retrieve.
Viewed by clicking on a job and seeing the logs on right side of gui.

Either method ONLY works with absolute file paths so instead of
Linux: ${HOME} use /home/runner/

## ARTIFACT AWS EXAMPLE
```yaml
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

      - name: Download FFmpeg build from S3
        id: download-s3
        run: |
          aws s3 cp s3://your-bucket-name/path/to/artifact/linux-ffmpeg-build.tar.gz /home/runner/linux-ffmpeg-build.tar.gz || echo "No artifact found"
        env:
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: your-region

      - name: Extract FFmpeg build if artifact was downloaded
        if: success() && steps.download-s3.outputs['aws-s3-exit-code'] == '0'
        run: |
          tar -xzvf /home/runner/linux-ffmpeg-build.tar.gz -C /home/runner

      - name: Build FFmpeg
        if: failure() || steps.download-s3.outputs['aws-s3-exit-code'] != '0'
        run: |
          cd ${HOME}/ffmpeg
          git clone https://git.ffmpeg.org/ffmpeg.git .
          ./configure --prefix=${HOME}/ffmpeg/install --enable-shared --enable-gpl --disable-programs
          make -j$(nproc)
          sudo make install

      - name: Create archive of FFmpeg build
        if: failure() || steps.download-s3.outputs['aws-s3-exit-code'] != '0'
        run: |
          tar -czvf /home/runner/linux-ffmpeg-build.tar.gz -C /home/runner ffmpeg

      - name: Upload FFmpeg build to S3
        run: |
          aws s3 cp /home/runner/linux-ffmpeg-build.tar.gz s3://your-bucket-name/path/to/artifact/linux-ffmpeg-build.tar.gz
        env:
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: your-region

      - name: Copy FFmpeg files to /usr
        run: |
          sudo cp -rf ${HOME}/ffmpeg/install/include/* /usr/include
          sudo cp -rf ${HOME}/ffmpeg/install/lib/* /usr/lib
```

## ARTIFACT GITHUB API EXAMPLE
```yml
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

      - name: Download Artifact from Previous Run
        id: download-artifact
        run: |
          # iterate backwards from most recent run to see if any run has artifact that matches name to use to download later on in workflow
          curl -H "Authorization: token ${{ secrets.GITHUB_TOKEN }}" \
              -H "Accept: application/vnd.github.v3+json" \
              https://api.github.com/repos/SumeetSinghJi/BubbleUp/actions/runs \
              -o runs.json

          # Iterate through runs to find one with artifacts
          RUN_ID=$(jq -r '.workflow_runs[] | select(.status == "completed") | .id' runs.json)
          for id in $RUN_ID; do
            echo "Checking run ID: $id"
            curl -H "Authorization: token ${{ secrets.GITHUB_TOKEN }}" \
                -H "Accept: application/vnd.github.v3+json" \
                https://api.github.com/repos/SumeetSinghJi/BubbleUp/actions/runs/$id/artifacts \
                -o artifacts.json

            ARTIFACT_ID=$(jq -r '.artifacts[] | select(.name == "linux-ffmpeg-build") | .id' artifacts.json)
            if [ -n "$ARTIFACT_ID" ]; then
              echo "Artifact found in run ID: $id"
              curl -L -H "Authorization: token ${{ secrets.GITHUB_TOKEN }}" \
                  -H "Accept: application/vnd.github.v3+json" \
                  https://api.github.com/repos/SumeetSinghJi/BubbleUp/actions/artifacts/$ARTIFACT_ID/zip \
                  --output linux-ffmpeg-build.zip
              unzip linux-ffmpeg-build.zip -d /home/runner/ffmpeg
              exit 0
            fi
          done

          echo "No artifact found in recent runs"
          exit 1

      - name: Extract FFmpeg build if artifact was downloaded
        if: steps.download-artifact.outcome == 'success'
        run: |
          tar -xzvf linux-ffmpeg-build.tar.gz -C /home/runner

      - name: Build FFmpeg
        if: failure() || !steps.download-artifact.outputs['success']
        run: |
          cd ${HOME}/ffmpeg
          git clone https://git.ffmpeg.org/ffmpeg.git .
          ./configure --prefix=${HOME}/ffmpeg/install --enable-shared --enable-gpl --disable-programs
          make -j$(nproc)
          sudo make install

      - name: Create archive of FFmpeg build
        if: failure() || !steps.download-artifact.outputs['success']
        run: |
          tar -czvf /home/runner/linux-ffmpeg-build.tar.gz -C /home/runner ffmpeg

      - name: Upload FFmpeg build as artifact
        if: steps.download-artifact.outcome == 'failure'
        uses: actions/upload-artifact@v3
        with:
          name: linux-ffmpeg-build
          path: /home/runner/linux-ffmpeg-build.tar.gz
          if-no-files-found: warn

      - name: Copy FFmpeg files to /usr
        run: |
          sudo cp -rf ${HOME}/ffmpeg/install/include/* /usr/include
          sudo cp -rf ${HOME}/ffmpeg/install/lib/* /usr/lib
```

## CACHE EXAMPLE
```yml
```

# C++ EXAMPLE WORKFLOW

name: test and release software

```yml
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
        key: ${{ runner.os }}-ffmpeg-cache-key-v1
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
      shell: bash
      run: |
        g++ \
        -fdiagnostics-color=always \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -ID:/a/_temp/msys64/mingw64/include \
        -g \
        "${{ github.workspace }}/tests/testcases.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/tests/testcases.exe" \
        -LD:/a/_temp/msys64/mingw64/lib \
        -lboost_system-mt \
        -lws2_32 \
        -lmingw32 \
        -lSDL2main \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lgtest \
        -lgtest_main \
        -lcurl \
        -lzip \
        -lz \
        -lavformat \
        -lavcodec \
        -lavutil \
        -lswscale \
        -lavfilter \

    - name: Test test binary
      run: |
        cd tests
        mv testcases.exe ..
        cd ..
        ./testcases

    - name: Compile final binary
      run: |
        g++ \
        -fdiagnostics-color=always \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -ID:/a/_temp/msys64/mingw64/include \
        -g \
        "${{ github.workspace }}/main.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/main.exe" \
        -LD:/a/_temp/msys64/mingw64/lib \
        -lboost_system-mt \
        -lws2_32 \
        -lmingw32 \
        -lSDL2main \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lgtest \
        -lgtest_main \
        -lcurl \
        -lzip \
        -lz \
        -lavformat \
        -lavcodec \
        -lavutil \
        -lswscale \
        -lavfilter \
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
        clang++ \
        -fcolor-diagnostics \
        -fansi-escape-codes \
        -std=c++17 \
        -stdlib=libc++ \
        -I/opt/homebrew/include \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -g \
        "${{ github.workspace }}/tests/testcases.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/tests/testcases" \
        -L/opt/homebrew/lib \
        -lboost_system \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lavformat \
        -lavcodec \
        -lavutil \
        -lswscale \
        -lgtest \
        -lcurl \
        -lzip \

    - name: Test test binary 
      run: |
        cd tests
        mv testcases ..
        cd ..
        ./testcases

    - name: Compile final binary
      run: |
        clang++ \
        -fcolor-diagnostics \
        -fansi-escape-codes \
        -std=c++17 \
        -stdlib=libc++ \
        -I/opt/homebrew/include \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -g \
        "${{ github.workspace }}/main.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/main" \
        -L/opt/homebrew/lib \
        -lboost_system \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lavformat \
        -lavcodec \
        -lavutil \
        -lswscale \
        -lgtest \
        -lcurl \
        -lzip \
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
        g++ \
        -std=c++17 \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -I/usr/include \
        -I/usr/include/x86_64-linux-gnu \
        -g \
        "${{ github.workspace }}/tests/testcases.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/tests/testcases" \
        -I/usr/include \
        -L/usr/lib \
        -lboost_system \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lgtest \
        -lcurl \
        -lzip \
        -lavutil \
        -lswscale \
        -lavformat \
        -lavcodec \
        -lswresample \

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
        g++ \
        -std=c++17 \
        -I"${{ github.workspace }}/headers" \
        -I"${{ github.workspace }}/headers/buttons" \
        -I"${{ github.workspace }}/headers/entities" \
        -I/usr/include \
        -I/usr/include/x86_64-linux-gnu \
        -g \
        "${{ github.workspace }}/main.cpp" \
        "${{ github.workspace }}/src/"*.cpp \
        "${{ github.workspace }}/src/buttons/"*.cpp \
        "${{ github.workspace }}/src/entities/"*.cpp \
        -o \
        "${{ github.workspace }}/main" \
        -I/usr/include \
        -L/usr/lib \
        -lboost_system \
        -lSDL2 \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lgtest \
        -lcurl \
        -lzip \
        -lavutil \
        -lswscale \
        -lavformat \
        -lavcodec \
        -lswresample \
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
```

# REACT EXAMPLE WORKFLOW

Using CI/CD - to upload React website to S3 static bucket

Assuming you have followed steps above to
a. setup the AWS environment by following ```AWS_web_hosting_commands.md```
b. setup the github with aws keys
c. built the website e.g. by following ```react_commands.md```

1. Create file: .github\workflows\actions.yml in your repo and add data below then push repo to upload
and test website access

```yml
name: actions
run-name: ${{ github.actor }} Deploy to S3 bucket

on: [push]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v2
      
      - name: Sync to S3
        uses: jakejarvis/s3-sync-action@v0.5.1
        with:
          args: --delete
        env:
          AWS_S3_BUCKET: sumeet-singh.com
          AWS_ACCESS_KEY_ID: ${{ secrets.AWS_ACCESS_KEY_ID }}
          AWS_SECRET_ACCESS_KEY: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          AWS_REGION: us-east-1
          SOURCE_DIR: './build'
```

# PYTHON EXAMPLE WORKFLOW

```yml
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

    - name: Set up Python
      uses: actions/setup-python@v2
      with:
        python-version: '3.9'

    - name: Install dependencies
      run: |
        pip install Pillow requests pyinstaller pyautogui

    - name: Build for Windows
      run: |
        pyinstaller --onefile --noconsole --icon=assets/view_earth.ico --name=Heroes3MapLiker Heroes3MapLiker.py # outputs binary to /dist

    - name: Run Windows Tests
      run: python tests.py

    - name: Package Windows artifacts
      run: |
        New-Item -ItemType Directory -Force -Path "dist/windows"
        Copy-Item -Path "dist/Heroes3MapLiker.exe" -Destination "dist/windows/"
        Copy-Item -Path "assets" -Destination "dist/windows/" -Recurse
        Copy-Item -Path "README.md" -Destination "dist/windows/"
        Compress-Archive -Path "dist/windows/*" -DestinationPath "dist/Heroes3MapLiker-windows.zip"

    - name: Upload Windows artifact
      uses: actions/upload-artifact@v2
      with:
        name: windows-zip
        path: dist/Heroes3MapLiker-windows.zip

  build_and_test_macos:
    runs-on: macos-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up Python
      uses: actions/setup-python@v2
      with:
        python-version: '3.9'

    - name: Install dependencies
      run: |
        pip install Pillow requests pyinstaller pyautogui

    - name: Build for macOS
      run: |
        pyinstaller --onefile --noconsole --icon=assets/view_earth.ico --name=Heroes3MapLiker Heroes3MapLiker.py # outputs binary to /dist
        chmod -R +rwx dist
        ls -l dist

    - name: Run macOS Tests
      run: python tests.py

    - name: Package macOS artifacts
      run: |
        mkdir -p dist/macos
        cp dist/Heroes3MapLiker dist/macos/
        cp -r assets dist/macos/
        cp -r README.md dist/macos/
        zip -r dist/Heroes3MapLiker-macos.zip dist/macos/

    - name: Upload macOS artifact
      uses: actions/upload-artifact@v2
      with:
        name: macos-zip
        path: dist/Heroes3MapLiker-macos.zip

  build_and_test_linux:
    runs-on: ubuntu-latest
    timeout-minutes: 30

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up Python
      uses: actions/setup-python@v2
      with:
        python-version: '3.9'

    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y python3-tk
        pip install Pillow requests pyinstaller pyautogui

    - name: Build for Linux
      run: |
        pyinstaller --onefile --noconsole --icon=assets/view_earth.ico --name=Heroes3MapLiker Heroes3MapLiker.py # outputs binary to /dist

    - name: Run Linux Tests
      run: python tests.py

    - name: Package Linux artifacts
      run: |
        mkdir -p dist/linux
        cp dist/Heroes3MapLiker dist/linux/
        cp -r assets dist/linux/
        cp -r README.md dist/linux/
        zip -r dist/Heroes3MapLiker-linux.zip dist/linux/

    - name: Upload Linux artifact
      uses: actions/upload-artifact@v2
      with:
        name: linux-zip
        path: dist/Heroes3MapLiker-linux.zip

  # build_and_test_android:
  #   runs-on: ubuntu-latest
  #   timeout-minutes: 30

  #   steps:
  #   - name: Checkout repository
  #     uses: actions/checkout@v3

  #   - name: Set up Python
  #     uses: actions/setup-python@v2
  #     with:
  #       python-version: '3.9'

  #   - name: Set Up JDK
  #     uses: actions/setup-java@v3
  #     with:
  #       distribution: 'zulu'
  #       java-version: '17'

  #   - name: Install dependencies
  #     run: |
  #       sudo apt-get update
  #       sudo apt-get install -y python3-tk
  #       pip install Kivy buildozer Pillow requests pyinstaller pyautogui 

  #   - name: Modify build.spec
  #     run: | 
  #       # First create .py code with Kivy framework. Fill details in file build.spec for cross-platform/.apk gen with buildozer
  #       echo "title = Heroes3MapLiker" >> build.spec
  #       echo "package.name = Heroes3MapLiker" >> build.spec
  #       echo "source.dir = ./" >> build.spec
  #       echo "requirements = kivy" >> build.spec
  #       echo "android.permissions = INTERNET" >> build.spec
  #       echo "version = 0.1" >> build.spec
  #       echo "android.sdk = 21" >> build.spec
  #       echo "p4a.branch = """ >> build.spec

  #   - name: Build Android APK
  #     run: |
  #       buildozer init
  #       buildozer -v android debug

  #   - name: Set up Android emulator
  #     run: |
  #       adb install bin/Heroes3MapLiker.apk

  #   - name: Run Android Tests
  #     run: |
  #       adb shell am start -n com.example.heroes3mapliker/.MainActivity \
  #       adb shell input keyevent KEYCODE_HOME \
  #       adb uninstall com.example.heroes3mapliker

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

  #   - name: Create GitHub Release
  #     id: create_release
  #     uses: actions/create-release@v1
  #     env:
  #       GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
  #     with:
  #       tag_name: v1.0.0
  #       release_name: Release v1.0.0
  #       draft: false
  #       prerelease: false

  #   - name: Upload Windows Release Asset
  #     uses: actions/upload-release-asset@v1
  #     env:
  #       GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
  #     with:
  #       upload_url: ${{ steps.create_release.outputs.upload_url }}
  #       asset_path: ./dist/Heroes3MapLiker-windows.zip
  #       asset_name: Heroes3MapLiker-windows.zip
  #       asset_content_type: application/zip

  #   - name: Upload macOS Release Asset
  #     uses: actions/upload-release-asset@v1
  #     env:
  #       GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
  #     with:
  #       upload_url: ${{ steps.create_release.outputs.upload_url }}
  #       asset_path: ./dist/Heroes3MapLiker-macos.zip
  #       asset_name: Heroes3MapLiker-macos.zip
  #       asset_content_type: application/zip

  #   - name: Upload Linux Release Asset
  #     uses: actions/upload-release-asset@v1
  #     env:
  #       GITHUB_TOKEN: ${{ secrets.RELEASE_TOKEN }}
  #     with:
  #       upload_url: ${{ steps.create_release.outputs.upload_url }}
  #       asset_path: ./dist/Heroes3MapLiker-linux.zip
  #       asset_name: Heroes3MapLiker-linux.zip
  #       asset_content_type: application/zip
```

