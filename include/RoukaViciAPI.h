// See Roukavici.hh for return code descriptions
// TODO: Copy over all comments when the API is finished
#pragma once

#include "DebugCallback.h"

/// InitRVici initializes the library
/**
 * Automatically starts trying to find the device as well
 * Returns an opaque handle to the API
 */
void* InitRVici();

/// Manually search for the device
/**
 * See RoukaVici::FindDevice for return codes
 */
int FindDevice(void* handle);

/// Returns RoukaVici's current status
/**
 * See RoukaVici::Status for return codes
 */
int Status(void* handle);

/// Frees all data used up by the library
void StopRVici(void* handle);

/// Write to the device directly
int Write(void* handle, const char * msg);

/// Cause a vibration in motor x  with intensity y (from 0 to 255)
int Vibrate(void* handle, char motor, char intensity);

/// Create a new vibration group
/**
 * See RoukaVici::NewGroup for return codes
 */
int NewGroup(void* handle, const char *  name);

/// Adds the given motor to the parameter group
/**
 * See RoukaVici::AddToGroup for return codes
 */
int AddToGroup(void* handle, const char *  name, char motor);

/// Removes the given motor from the group
/**
 * See RoukaVici::RmFromGroup for return codes
 */
int RmFromGroup(void* handle, const char *  name, char motor);

/// Causes a group to vibrate with the given intensity (0-255)
void VibrateGroup(void* handle, const char* name, char intensity);

/// Changes device managers
int ChangeDeviceManager(void* handle, const int idx);

/// Sets Roukavici's logging method
void SetLogMode( const int mode);

/// Gets Roukavici's logging method
int GetLogMode(void* handle);

/// Gets the file which RoukaVici logs to
int SetLogFile(const char* name);

/// Register the debug function callback.
void RegisterDebugCallback(DebugCallback cb);

/// Register the Unity debug function.
void RegisterUnityDebugCallback(UnityDebugCallback cb);
