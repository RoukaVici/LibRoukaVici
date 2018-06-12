#pragma once

#include <string>
#include <map>
#include "exported.hh"
#include "DebugCallback.h"

class ManagerFactory;
class DeviceManager;
class GroupManager;

/// This class contains all the exposed public API methods
/**
 * In a C++ project, it can be created directly, without using the exposed C functions,
 * and without losing any of the API methods.
 */
class EXPORTED RoukaVici {
public:
  // Public constructor, to check
  RoukaVici();
  ~RoukaVici();

  /// Lets the developer write any string to the device.
  /**
   * 0 - OK
   * 1 - No device to send to
   * 2 - Error while writing to device
   * Note that this function returning 0 does not *necessarily* indicate that the vibration will be 100% successful, as some write functions could fail behind the scenes without the library being aware of it (for example, writing over a network)
   */
  int Write(const std::string& msg) const;

  /// Simple vibration
  /**
   * 0 - OK
   * 1 - No device to send to
   * 2 - Error while writing to device
   * Note that this function returning 0 does not *necessarily* indicate that the vibration will be 100% successful, as some write functions could fail behind the scenes without the library being aware of it (for example, writing over a network)
   */
  int Vibrate(char motor, char intensity) const;

  /// Returns values indicating current status
  /**
   * 0: No errors
   * 1: Device not found
   */
  int Status();

  /// Orders the device manager to find a device
  /**
   * 0: Device found
   * Other return values depend on the DeviceManager used, refer to their headers
   */
  int FindDevice();

  /// Create a new vibration group
  /**
   * 0: Success
   * 1: Group already exists
   */
  int NewGroup(const std::string& name);
  /// Add motor to group
  /**
   * 0: Success
   * 1: Motor already in group
   * 2: No such group
   */
  int AddToGroup(const std::string& name, char motor);
  /// Remove motor from group
  /**
   * 0: Success
   * 1: Motor not in group
   * 2: No such group
   */
  int RmFromGroup(const std::string& name, char motor);

  /// Vibrates the given group at the given intensity
  /**
   * Will return at the first error with the proper error code, even if there are motors left in the group.
   * 0: Success
   * 1: No device connected
   * 2: Write failed
   * 3: No such group
   */
  int VibrateGroup(const std::string& name, char intensity) const;

  /// Changes device managers
  /**
   * Return values:
   * 0: Success
   * 1: No such manager (did you compile the lib with support for that manager?)
   */
  int ChangeDeviceManager(const std::string& name);

  /// Changes the logging method
  /**
   * Logging methods:
   * 0: Write to std::cout/std::cerr
   * 1: Write to file
   * 2: Use DebugCallback
   * 3: Use UnityDebugCallback
   */
  static void SetLogMode(const int mode);
  /// Get the current logging method
  static int  GetLogMode();

  /// Sets the logging file path.
  /**
   * Default value: ./RoukaViciLog.txt
   */
  static void SetLogFile(const std::string& path);

  /// Lets you register a debug callback which will receive a C function
  /**
   * callback: void (*function)(const char * message);
   */
  static void RegisterDebugCallback(DebugCallback callback);

  /// Lets you register a debug callback with an Unity function
  /**
   * callback: void (*function)(const char * message);
   */
  static void RegisterUnityDebugCallback(UnityDebugCallback callback);

private:
  ManagerFactory                *mf;
  DeviceManager                 *dm;
  GroupManager                  *grps;
};
