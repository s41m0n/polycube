/**
* router API generated from router.yang
*
* NOTE: This file is auto generated by polycube-codegen
* https://github.com/polycube-network/polycube-codegen
*/


/* Do not edit this file manually */

/*
* RouteBase.h
*
*
*/

#pragma once

#include "../serializer/RouteJsonObject.h"






#include <spdlog/spdlog.h>

using namespace polycube::service::model;

class Router;

class RouteBase {
 public:
  
  RouteBase(Router &parent);
  
  virtual ~RouteBase();
  virtual void update(const RouteJsonObject &conf);
  virtual RouteJsonObject toJsonObject();

  /// <summary>
  /// Destination network IP
  /// </summary>
  virtual std::string getNetwork() = 0;

  /// <summary>
  /// Next hop; if destination is local will be shown &#39;local&#39; instead of the ip address
  /// </summary>
  virtual std::string getNexthop() = 0;

  /// <summary>
  /// Outgoing interface
  /// </summary>
  virtual std::string getInterface() = 0;

  /// <summary>
  /// Cost of this route
  /// </summary>
  virtual uint32_t getPathcost() = 0;
  virtual void setPathcost(const uint32_t &value) = 0;

  std::shared_ptr<spdlog::logger> logger();
 protected:
  Router &parent_;
};
