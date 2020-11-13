// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/OutputDevice.h"
/**
 * 
 */
class QUESTSEDITOR_API FNodeCompilerLog : public FOutputDevice
{
public:
	FNodeCompilerLog();
	FString OutPut;
protected:
	virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override
	{
		if (Category == FName("LogQuestNodeCompiler"))
		{
			OutPut += V;
			OutPut += LINE_TERMINATOR;
		}
	}
};
