#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <toml++/toml.h>

/**
 * Loads the config from ./data/config.toml.
 * If the config file cannot be found:
 *  1) Writes the default config contents to ./data/config.toml
 *  2) Loads that default config.
 * \sa default_config
 * \returns The current config.
 */
toml::table load_or_create_config();

/**
 * Gets the default config.toml contents.
 * Should never throw, if it does then there is a huge problem!!
 * \sa load_or_create_config
 * \returns The default config.
 */
toml::table default_config() noexcept;

#endif
