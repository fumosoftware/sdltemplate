#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <toml++/toml.h>

/**
 * Attempts to load configuration data from ./data/config.toml
 * If the file does not exist, a default configuration is loaded instead.
 *
 * \return A hashmap of configuration data.
 */
toml::table load_or_create_config();

/**
 * Gets the default configuration data for the application.
 *
 * \return A hashmap of configuration data.
 */
toml::table default_config() noexcept;

#endif
