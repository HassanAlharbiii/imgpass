build: imgpass.c
	gcc imgpass.c libui-ng/build/meson-out/libui.a `pkg-config --cflags --libs gtk+-3.0` -o imgpass