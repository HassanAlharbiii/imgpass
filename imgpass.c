#include <stdio.h>
#include "ui.h"

uiWindow *mainwin;

int onClosing(uiWindow *w, void *data)
{
	uiQuit();
	return 1;
}

static void onOpenFileClicked(uiButton *b, void *data)
{
	uiEntry *entry = uiEntry(data);
	char *filename;

	// [l, m, a, o, 0]
	//  ^
	// 432424 + 4 (sizeof(element))
	// something[4]
	filename = uiOpenFile(mainwin);
	if (filename == NULL) {
		uiEntrySetText(entry, "(cancelled)");
		return;
	}
	uiEntrySetText(entry, filename);
	uiFreeText(filename);
}

int main(void)
{
	uiInitOptions o = {0};
	const char *err;
	uiLabel *l;
	uiButton *button;
	uiEntry *entry;

	err = uiInit(&o);
	if (err != NULL) {
		fprintf(stderr, "Error initializing libui-ng: %s\n", err);
		uiFreeInitError(err);
		return 1;
	}

	// Create a new window
	mainwin = uiNewWindow("Hello World!", 300, 30, 0);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	l = uiNewLabel("Hello, World!");
	uiWindowSetChild(mainwin, uiControl(l));

	button = uiNewButton("  Open File  ");
	entry = uiNewEntry();
	uiEntrySetReadOnly(entry, 1);
	uiButtonOnClicked(button, onOpenFileClicked, entry);
	uiWindowSetChild(mainwin, uiControl(button));
	uiWindowSetChild(mainwin, uiControl(entry));

	uiControlShow(uiControl(mainwin));
	uiMain();
	uiUninit();
	return 0;
}
