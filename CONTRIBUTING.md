<!--
SPDX-FileCopyrightText: © 2024 Ashley Hawkins <awhawkins@proton.me>
SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>

SPDX-License-Identifier: CC-BY-SA-4.0
-->

# Contributing guidelines

## Pre-commit hooks

The source repository contains a `pre-commit` configuration file which defines some useful pre-commit hooks to help conform to the contributing guidelines. Visit <https://pre-commit.com/#quick-start> to learn about how to get it set up.

## Copyright information

All files in the repo must have copyright information conformant with the [REUSE](https://reuse.software/) spec. You can use `reuse` command line tool to help with headers or  

## Formatting

All manually written C++ source files must be formatted with clang-format. Generated ones like those in module_shims/*_generated/ don't need to be formatted because generaly they aren't being edited by humans and they are generated with decently readable formatting.
