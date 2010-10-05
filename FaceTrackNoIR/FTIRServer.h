/********************************************************************************
* FTIRServer		FTIRServer is the Class, that communicates headpose-data	*
*					to games, using the NPClient.dll.		         			*
*																				*
* Copyright (C) 2010	Wim Vriend (Developing)									*
*						Ron Hendriks (Testing and Research)						*
*																				*
* This program is free software; you can redistribute it and/or modify it		*
* under the terms of the GNU General Public License as published by the			*
* Free Software Foundation; either version 3 of the License, or (at your		*
* option) any later version.													*
*																				*
* This program is distributed in the hope that it will be useful, but			*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY	*
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for	*
* more details.																	*
*																				*
* You should have received a copy of the GNU General Public License along		*
* with this program; if not, see <http://www.gnu.org/licenses/>.				*
*																				*
********************************************************************************/
#pragma once
#ifndef INCLUDED_FTIRSERVER_H
#define INCLUDED_FTIRSERVER_H
 
//#include "Windows.h" 
#include "FTIRTypes.h"
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QLibrary>
#include <QUdpSocket>

typedef void (WINAPI *importSetPosition)(float x, float y, float z, float xRot, float yRot, float zRot);
//typedef bool (WINAPI *importGetData)(TFreeTrackData * data);
//typedef HANDLE (WINAPI *importGetMapHandle)(void);

using namespace std;

class FTIRServer : public QThread {
	Q_OBJECT

public: 

	// public member methods
	FTIRServer();
	~FTIRServer();

	bool FTIRCreateMapping(HANDLE handle);
	void FTIRDestroyMapping();
	bool FTIRCheckClientDLL();

	// protected member methods
protected:
	void run();

private:
	// Handles to neatly terminate thread...
	HANDLE m_StopThread;
	HANDLE m_WaitThread;

	HANDLE hFTIRMemMap;
	FTIRMemMap *pMemData;
	HANDLE hFTIRMutex;

	// Private properties
	QString ProgramName;
	QLibrary FTIRClientLib;
	static float scale2AnalogLimits( float x, float min_x, float max_x );

public:

	// Settings for calculating the Virtual Pose
	static float virtPosX;
	static float virtPosY;
	static float virtPosZ;
	
	static float virtRotX;
	static float virtRotY;
	static float virtRotZ;

	static void setVirtRotX(float rot) { virtRotX = scale2AnalogLimits (rot, -180.0f, 180.0f); }
	static void setVirtRotY(float rot) { virtRotY = scale2AnalogLimits (rot, -180.0f, 180.0f); }
	static void setVirtRotZ(float rot) { virtRotZ = scale2AnalogLimits (rot, -180.0f, 180.0f); }

	static void setVirtPosX(float pos) { virtPosX = scale2AnalogLimits (pos * 10.0f, -500.0f, 500.0f); }
	static void setVirtPosY(float pos) { virtPosY = scale2AnalogLimits (pos * 10.0f, -500.0f, 500.0f); }
	static void setVirtPosZ(float pos) { virtPosZ = scale2AnalogLimits (pos * 10.0f, -500.0f, 500.0f); }

};


#endif//INCLUDED_FTIRSERVER_H
//END
