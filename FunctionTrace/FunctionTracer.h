// The MIT License (MIT)
// C++ Function Tracer 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once

#include <string>
#include <cstdio>

#if defined(__GNUC__)
#define SVFUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define SVFUNCTION_NAME __FUNCSIG__
#else
#define SVFUNCTION_NAME __func__
#endif

class FunctionTracer
{
public:
	FunctionTracer(const char* func, const char* file, int lineNum)
	{
		++Tabs;
		Log(func, file, lineNum);
	}
	
	~FunctionTracer()
	{
		--Tabs;
	}
	
	const char* GetTabs()
	{
		TabString = "";
		for(int i = 0; i < Tabs; ++i)
		{
			TabString += "    ";
		}
		return TabString.c_str();
	}

	static void EnablePrintFileLocation(bool enable)
	{
		PrintFileLocation = enable;
	}

private:
    void ReadPath()
	{
		const char* filename = "func_path.txt";
		FILE* fp = NULL;
#if defined(_MSC_VER)
		fopen_s(&fp, filename, "rt");
#else
		fp = fopen(filename, "rt");
#endif
		
		if (fp)
		{
			char line[256]; // Buffer to store each line
			if (fgets(line, sizeof(line), fp)) 
			{
				LogPath = line;
			}
			fclose(fp);
		}
		printf("LogPath: %s\n", LogPath.c_str());
	}

    void Log(const char* func, const char* file, int lineNum)
	{
		if (LogPath.empty())
		{
			ReadPath();
		}
		
		if (PrintFileLocation)
			printf("%s%s %s (line #%d)\n", GetTabs(), func, file, lineNum);
		else
			printf("%s%s\n", GetTabs(), func);

		FILE* fp = NULL;
#if defined(_MSC_VER)
		fopen_s(&fp, LogPath.c_str(), "at");
#else
		fp = fopen(LogPath.c_str(), "at");
#endif
		if (fp)
		{
			if (PrintFileLocation)
				fprintf(fp, "%s%s %s (line #%d)\n", GetTabs(), func, file, lineNum);
			else
				fprintf(fp, "%s%s\n", GetTabs(), func);

			fclose(fp);
			fp = NULL;
		}
		else
		{
			printf("Log file cannot be opened (%s)", LogPath.c_str());
		}
	}	
	static inline int Tabs = 0;
	static inline bool PrintFileLocation = false;
	static inline std::string LogPath;
	static inline std::string TabString;
};

#define FT \
FunctionTracer funcTracer(SVFUNCTION_NAME, __FILE__, __LINE__);
