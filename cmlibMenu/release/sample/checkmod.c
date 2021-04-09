////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  INIT METHOD
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char ms_libmenu_path[] = { "ms0:/seplugins/lib/prxlibmenu.prx"};
char ef_libmenu_path[] = { "ef0:/seplugins/lib/prxlibmenu.prx"};
//------------------------------------------------------
int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}

int init(void)
{
	while(1)
	{
		if(sceKernelFindModuleByName("sceKernelLibrary")){
			// prxlibmenu loading Check
			if( sceKernelFindModuleByName("prxlibmenu") == NULL ) {
				// load prxlibmenu
				LoadStartModule(ms_libmenu_path);
				
				if( sceKernelFindModuleByName("prxlibmenu") == NULL ){
					// PSP Go Built-in Memory Support
					LoadStartModule(ef_libmenu_path);
				}
			}

			break;
		}
		
		sceKernelDelayThread(1000);
	}
	return 0;
}

