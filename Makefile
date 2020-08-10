IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
docker run -d --name firefox -e DISPLAY=$IP:0 -v /tmp/.X11-unix:/tmp/.X11-unix jess/firefox
