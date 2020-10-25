OBJS = main.cpp Game.cpp Game.hpp TextureManager.cpp TextureManager.hpp Map.cpp Map.hpp Ball.hpp Ball.cpp Player.hpp Player.cpp Block.hpp Block.cpp

OBJ_Name = SDLMain

build-windows : $(OBJS)

	g++ $(OBJS) -IC:\Users\nico\Development\x86_64-w64-mingw32\include -L C:\Users\nico\Development\x86_64-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2_image -lSDL2 -o $(OBJ_Name)
	$(OBJ_Name).exe

clean :
	rm $(OBJ_Name)
run-windows :
	$(OBJ_Name).exe

build: $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -lSDL2_ttf -o $(OBJ_Name)
	./$(OBJ_Name)
run: 
	./$(OBJ_Name)

.PHONY: build setup-windows setup-osx
