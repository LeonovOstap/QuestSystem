// Fill out your copyright notice in the Description page of Project Settings.


#include "LogUtilities.h"

FNodeCompilerLog::FNodeCompilerLog()
{
	GLog->AddOutputDevice(this);
}

