all: proj.exe

proj.exe: scancode.o isr.o sprite.o GenQueue.o rtc.o kbc.o queue.o timer.o music.o ints.o video-graphics.o playTimeCounter.o screenBorder.o jogo.o inicialMenus.o gameBoard.o main.o
	gcc scancode.o isr.o sprite.o GenQueue.o rtc.o kbc.o queue.o timer.o music.o ints.o video-graphics.o playTimeCounter.o screenBorder.o jogo.o inicialMenus.o gameBoard.o main.o -o proj.exe
	
isr.o: isr.asm
	nasm -t -f coff isr.asm -o isr.o
	
scancode.o: scancode.asm
	nasm -t -f coff scancode.asm -o scancode.o

jogo.o: jogo.c jogo.h gameBoard.h playTimeCounter.h queue.h sprite.h screenBorder.h structs.h inicialMenus.h
	gcc -Wall -c jogo.c

GenQueue.o: GenQueue.h GenQueue.c utypes.h
	gcc -Wall -c GenQueue.c

rtc.o: rtc.c rtc.h GenQueue.h utypes.h music.h ints.h
	gcc -Wall -c rtc.c

kbc.o: kbc.c kbc.h utypes.h timer.h ints.h
	gcc -Wall -c kbc.c

queue.o: queue.c queue.h utypes.h music.h
	gcc -Wall -c queue.c

timer.o: timer.c timer.h
	gcc -Wall -c timer.c

music.o: music.c music.h timer.h
	gcc -Wall -c music.c
	
ints.o: ints.c ints.h
	gcc -Wall -c ints.c

main.o: main.c inicialMenus.h ints.h rtc.h structs.h video-graphics.h
	gcc -Wall -c main.c

video-graphics.o: video-graphics.c utypes.h
	gcc -Wall -c video-graphics.c
	
playTimeCounter.o: playTimeCounter.h playTimeCounter.c video-graphics.h constants.h rtc.h
	gcc -Wall -c playTimeCounter.c

screenBorder.o: screenBorder.h screenBorder.c video-graphics.h constants.h
	gcc -Wall -c screenborder.c
	
inicialMenus.o: inicialMenus.h inicialMenus.c rtc.h ints.h jogo.h queue.h structs.h video-graphics.h
	gcc -Wall -c inicialMenus.c

gameBoard.o: gameBoard.h gameBoard.c video-graphics.h constants.h
	gcc -Wall -c gameBoard.c

sprite.o: sprite.h sprite.c video-graphics.h
	gcc -Wall -c sprite.c

clean:
	rm -r *.o *.exe