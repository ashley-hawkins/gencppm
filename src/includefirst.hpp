/*
 * SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 */

// Include these first to work around clang bug with false positive ODR violations
#include <cstddef>
#include <cstdint>
#if __has_include(<compare>)
#include <compare>
#endif
