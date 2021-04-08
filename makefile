all: keyer
keyer: keyer.c stb_image.h stb_image_write.h
	gcc -o keyer keyer.c
clean:
	rm -rf keyer