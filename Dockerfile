FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install -y apache2
RUN apt-get install libsdl2-dev
RUN apt-get install libsdl2-image-dev
RUN apt-get install SDL2_ttf-devel
