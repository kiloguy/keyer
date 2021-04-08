#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#define		STB_IMAGE_IMPLEMENTATION
#define		STB_IMAGE_WRITE_IMPLEMENTATION
#include	"stb_image.h"
#include	"stb_image_write.h"

int help() {
	fprintf(stderr, "Usage: keyer <input file> <output file> <r> <g> <b> [a]\n\n");
	fprintf(stderr, "       If the input image has 4 channels (rgba), \"a\" should be specified.\n");
	fprintf(stderr, "       Value of r, g, b, a are integer 0 ~ 255.\n");
	fprintf(stderr, "       Currently only support output PNG format.\n");
}

int ee(const char* message) {
	fprintf(stderr, message);
	return -1;
}

int main(int argc, char* argv[]) {
	if(argc != 6 && argc != 7)
		return help();

	int i;
	unsigned char rgba[4];
	for(i = 3; i < argc; i++) {
		unsigned char v = atoi(argv[i]);
		if(v < 0 || v > 255)
			return help();
		rgba[i - 3] = v;
	}

	int w, h, n;
	unsigned char* image = stbi_load(argv[1], &w, &h, &n, 0);

	if(image == NULL)
		return ee("Cannot load input image.\n");
	if(n != 3 && n != 4) {
		stbi_image_free(image);
		return ee("Input image format unsupport.\n");
	}

	printf("Iput image: %dx%dx%d\n", w, h, n);

	if(n == 3 && argc != 6 || n == 4 && argc != 7) {
		stbi_image_free(image);
		return ee("Input image format wrong.\n");
	}

	unsigned char* output = (unsigned char*)malloc(w * h * 4);
	int p, o = 0;
	for(p = 0; p < w * h; p++) {
		int same = 1;
		for(i = 0; i < argc - 3; i++) {
			if(rgba[i] != image[(argc - 3) * p + i]){
				same = 0;
				break;
			}
		}
		if(same)
			memset(output + o, 0, 4);
		else {
			output[o + 3] = 255;
			memcpy(output + o, image + (argc - 3) * p, argc - 3);
		}
		o += 4;
	}

	if(stbi_write_png(argv[2], w, h, 4, output, w * 4) == 0) {
		stbi_image_free(image);
		free(output);
		return ee("Image write failed.\n");
	}

	stbi_image_free(image);
	printf("Complete.\n");

	return 0;
}