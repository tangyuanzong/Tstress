#!/bin/bash
g++ -o M Main.cpp Tstress.cpp Tstress.h Epoll.cpp Epoll.h Socket.cpp Socket.h Thread_pool.h Thread_pool.cpp Thread.cpp Thread.h -lpthread

echo Compile successfuily!
