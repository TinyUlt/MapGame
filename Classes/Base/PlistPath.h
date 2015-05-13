#pragma once

typedef struct _FileName
{  
	const char *name;  

} FileName;  

static FileName g_PlistFile[] = 
{
	{"NewAnimation/NewAnimation.ExportJson"},
};
static int g_PlistFileCount = sizeof(g_PlistFile) / sizeof(g_PlistFile[0]);  

static FileName g_AnimationFile[]  =
{
	{"manAnimation/manAnimation.ExportJson"},
};
static int g_AnimationFileCount = sizeof(g_AnimationFile) / sizeof(g_AnimationFile[0]);  
