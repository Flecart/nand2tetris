
	// Questo non funziona nel caso in cui vado a richiedere
	// qualcosa di altro, tipo screen, e la memoria pensa ancora che io voglio
	// una ram... basterebbe demultiplexer e multiplexer? Non lo so ...
	// Bit(in=isRam, load=load, out=lastIsRam);
	// Bit(in=isScreen, load=load, out=lastIsScreen);

	// Mux16(a=keyboardOut, b=screenOut, sel=lastIsScreen, out=keybMuxScreen);
	// Mux16(a=keybMuxScreen, b=ramOut, sel=lastIsRam, out=out);