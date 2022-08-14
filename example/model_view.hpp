//
// Copyright (c) 2012-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <boost/signals2/signal.hpp>
#include <string>

class controller;

class renderer {
  int device_;

 public:
  explicit renderer(int device) : device_(device) {}
  void run(const std::string& text);
};

class model {
 public:
  void start(){};
  void set(bool value) {
    value_ = value;
    sig_(value);
  };
  bool get() { return value_; };

  // ======================================
  typedef boost::signals2::signal<void(bool)> signal_t;

  /* Connect a slot to the signal which will be emitted whenever value is updated at the model. */
  boost::signals2::connection connect(const signal_t::slot_type& subscriber) { return sig_.connect(subscriber); }

 private:
  signal_t sig_;
  // ======================================
  bool value_{};
};

class view {
  std::string title_;
  renderer& renderer_;

 public:
  explicit view(std::string title, renderer& renderer) : title_(title), renderer_(renderer) {}
  void run();
  // ======================================
  void refresh(bool value);
  // ======================================
};

class user {
  controller& controller_;

 public:
  explicit user(controller& controller) : controller_(controller) {}
  void run();
};

class app {
  controller& controller_;
  user& user_;

 public:
  explicit app(controller& controller, user& user) : controller_(controller), user_(user) {}
  void run();
};

/// the controller creates the object tree
class controller {
  model& model_;
  view& view_;
  // ======================================
  boost::signals2::connection connection_;
  // ======================================

 public:
  explicit controller(model& model, view& view, boost::signals2::connection connection)
      : model_(model), view_(view), connection_(connection) {}
  void start();
  void set(bool value);
  bool get();
};
