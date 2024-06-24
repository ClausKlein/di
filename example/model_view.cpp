//
// Copyright (c) 2012-2020 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "model_view.hpp"

#include <boost/bind/bind.hpp>
#include <boost/di.hpp>
#include <functional>
#include <iostream>
#include <string>

namespace di = boost::di;

void renderer::run(const std::string& text) { std::cout << std::to_string(++device_).append(text) << std::endl; }

void view::run() { renderer_.run(title_); }

void view::refresh(bool value) { renderer_.run(std::string(" value = ") + std::to_string(value)); }

void user::run() {
  controller_.set(true);
  controller_.set(false);
}

void controller::set(bool value) { model_.set(value); }

bool controller::get() { return model_.get(); }

void controller::start() {
  model_.start();
  view_.run();
}

void app::run() {
  controller_.start();
  user_.run();
}

int main() {
  using namespace boost::placeholders;
  using boost::signals2::connection;

  /// USE DEPENDENCY INJECTION PARTLY
  {
    renderer renderer_(42);
    view view_{" We needs DI!", renderer_};
    model model_;
    // ======================================
    connection connection_ = model_.connect(boost::bind(&view::refresh, &view_, _1));
    // ======================================
    // controller controller_{model_, view_, connection_};
    // user user_(controller_);
    // app app_{controller_, user_};

    auto injector = di::make_injector(di::bind<model>().to(model_),  //
                                      di::bind<view>().to(view_),    //
                                      di::bind<connection>().to(connection_));
    auto app_ = injector.create<app>();
    app_.run();
  }

  /// WITH ONLY DEPENDENCY INJECTION
  {
    auto injector =                                                         //
        di::make_injector(di::bind<int>().to(42),                           // renderer device
                          di::bind<std::string>().to(" DI w/o connection")  // view title
                                                                            // TODO(CK): missing connection!
        );
    auto app_ = injector.create<app>();
    app_.run();
  }
}
