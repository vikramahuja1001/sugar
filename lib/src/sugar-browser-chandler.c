#include <stdio.h>
#include <string.h>

#include "sugar-marshal.h"
#include "sugar-browser-chandler.h"

enum {
  HANDLE_CONTENT,
  LAST_SIGNAL
};
static guint signals[LAST_SIGNAL] = { 0 };

G_DEFINE_TYPE(SugarBrowserChandler, sugar_browser_chandler, G_TYPE_OBJECT)

SugarBrowserChandler *browserChandler = NULL;

static void
sugar_browser_chandler_init(SugarBrowserChandler *browserChandler)
{
}

static void
sugar_browser_chandler_class_init(SugarBrowserChandlerClass *browser_chandler_class)
{
	signals[HANDLE_CONTENT] =
		g_signal_new ("handle-content",
					  G_OBJECT_CLASS_TYPE (browser_chandler_class),
		  			  G_SIGNAL_RUN_LAST,
		  			  G_STRUCT_OFFSET (SugarBrowserChandlerClass, handle_content),
					  NULL, NULL,
					  sugar_marshal_VOID__STRING_STRING_STRING,
					  G_TYPE_NONE, 3,
					  G_TYPE_STRING,
					  G_TYPE_STRING,
					  G_TYPE_STRING);
}

SugarBrowserChandler *
sugar_get_browser_chandler()
{  
	if(browserChandler == NULL)
		browserChandler = g_object_new(SUGAR_TYPE_BROWSER_CHANDLER, NULL);
 	
	return browserChandler;
}

void
sugar_browser_chandler_handle_content (SugarBrowserChandler *browser_chandler, 
									   const char *url, 
									   const char *mime_type, 
									   const char *tmp_file_name)
{	
	g_signal_emit(browser_chandler, 
				  signals[HANDLE_CONTENT],
                  0 /* details */, 
                  url,
                  mime_type,
                  tmp_file_name);          
}
