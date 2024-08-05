
# YOUTUBE DOWNLOADER USE GUIDE

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS

To download YouTube videos (considering you are only downloading your own videos!) you will need to install a software called "yt-dlb" = YouTube Downloader

Requires FFMPEG to be installed and added to environmental variables with .DLL files besides the .exe (only on Windows/Linux)

1. Install FFMPEG as per https://stackoverflow.com/questions/77742801/how-do-i-include-ffmpeg-for-development-in-a-windows-program/

2. Instal yt-dlb for your OS https://github.com/yt-dlp/yt-dlp/releases 

3. Find the URL of the webpage you are downloading e.g, 

4. Login through Chrome to your YouTube account to bypass age verificaiton which will auto save your cookies

5. Run the command below to download the video into the location run in. (Note if you have FFMPEG installed yt-dlb will auto detect and use it to combine the seperate downloaded audio and video stream)
```bash
yt-dlp --cookies-from-browser chrome https://www.youtube.com/watch?v=sUsvlCWvQrQ

# EXAMPLE OUTPUT BELOW
PS C:\Users\Sumeet> yt-dlp --cookies-from-browser chrome https://www.youtube.com/watch?v=sUsvlCWvQrQ
Extracting cookies from chrome
Extracted 5151 cookies from chrome
[youtube] Extracting URL: https://www.youtube.com/watch?v=sUsvlCWvQrQ
[youtube] sUsvlCWvQrQ: Downloading webpage
[youtube] sUsvlCWvQrQ: Downloading ios player API JSON
[youtube] sUsvlCWvQrQ: Downloading player d2e656ee
WARNING: [youtube] sUsvlCWvQrQ: nsig extraction failed: Some formats may be missing
         n = aOaSSpIWPXlya5Ga ; player = https://www.youtube.com/s/player/d2e656ee/player_ias.vflset/en_US/base.js
WARNING: [youtube] sUsvlCWvQrQ: nsig extraction failed: Some formats may be missing
         n = liXS1H6QSC3iKfer ; player = https://www.youtube.com/s/player/d2e656ee/player_ias.vflset/en_US/base.js
[youtube] sUsvlCWvQrQ: Downloading m3u8 information
[info] sUsvlCWvQrQ: Downloading 1 format(s): 135+140
[download] Destination: Marrickville West public school 2002 year drama [sUsvlCWvQrQ].f135.mp4
[download] 100% of   51.78MiB in 00:00:10 at 5.02MiB/s
[download] Destination: Marrickville West public school 2002 year drama [sUsvlCWvQrQ].f140.m4a
[download] 100% of    8.41MiB in 00:00:04 at 1.70MiB/s
[Merger] Merging formats into "Marrickville West public school 2002 year drama [sUsvlCWvQrQ].mp4"
Deleting original file Marrickville West public school 2002 year drama [sUsvlCWvQrQ].f140.m4a (pass -k to keep)
Deleting original file Marrickville West public school 2002 year drama [sUsvlCWvQrQ].f135.mp4 (pass -k to keep)
PS C:\Users\Sumeet>
```