#!/bin/bash

sleep 10

YOUTUBE_URL="rtmp://a.rtmp.youtube.com/live2/xuhk-s9jv-m7xc-jybu-f1my"

libcamera-vid -t 0 --inline --width 640 --height 360 --framerate 20 \
--profile high -o - | \
ffmpeg -re -f h264 -i - \
-ar 44100 -ac 1 -f s16le -acodec pcm_s16le -i /dev/zero \
-vcodec libx264 -preset veryfast -crf 23 -b:v 1000k -maxrate 1000k -bufsize 1000k \
-acodec aac -ab 64k -g 40 -f flv "$YOUTUBE_URL"
