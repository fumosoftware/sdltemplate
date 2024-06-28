#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <toml++/toml.h>
toml::table load_or_create_config();

toml::table default_config() noexcept;

#endif
