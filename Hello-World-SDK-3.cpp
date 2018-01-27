// Downloaded from https://developer.x-plane.com/code-sample/hello-world-sdk-3/


#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"

#include <string.h>
#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

#include <stdio.h>

XPLMDataRef l4m = NULL;

PLUGIN_API float flight_loop_callback (
	float inElapsedSinceLastCall,
	float	inElapsedTimeSinceLastFlightLoop,
	int	  inCounter,
	void * inRefcon) {

	printf ("SHA: in flight_loop_callback\n");

	if (l4m == NULL) {
		// find a dataref
		l4m = XPLMFindDataRef ("laminar/B738/fmc1/Line01_M");
		if (l4m != NULL) {
			// check its datatype
			printf ("Found laminar/B738/fmc1/Line01_M [%d]\n", XPLMGetDataRefTypes (l4m));
		} else {
			printf ("Couldn't find laminar/B738/fmc1/Line01_M\n");
		}
	}

	if (l4m != NULL) {
		char buffer [40];
		int c = XPLMGetDatab (
			l4m,
			buffer,
			0,
			40
		);

		buffer[c] = '\0';
		printf ("Got %d [%s]", c, buffer);
	}

	return 1.0;

};

PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "HelloWorld3Plugin");
	strcpy(outSig, "xpsdk.examples.helloworld3plugin");
	strcpy(outDesc, "A Hello World plug-in for the XPLM300 SDK.");
	
	
	printf ("SHA: in XPluginStart!\n");

	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	printf ("SHA: in XPluginStop!\n");
}

PLUGIN_API void XPluginDisable(void) {
	printf ("SHA: in XPluginDisable!\n");

	XPLMUnregisterFlightLoopCallback (
		&flight_loop_callback,
		NULL
	);
}

PLUGIN_API int  XPluginEnable(void)  { 
	printf ("SHA: in XPluginEnable\n");

	// register a FlightLoopCallback
	XPLMRegisterFlightLoopCallback (
		&flight_loop_callback,
		1,
		NULL
	);

	return 1; 
}


PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) {
	printf ("SHA: in XPluginReceiveMessage!\n");
}

