/*
 * SPDX-FileCopyrightText: © 2024 Gencppm Contributors
 * SPDX-FileContributor: Ashley Hawkins <awhawkins@proton.me>
 *
 * SPDX-License-Identifier: AGPL-3.0-only
 *
 * This file includes work covered by the following copyright and permission notices:
 *
 *  Copyright (c) 2019-2022, Alibaba Group Holding Limited
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

module;
#include <string>
export module gencppm:stringfix;

#if defined(__GLIBCXX__)
// https://github.com/alibaba/async_simple/blob/d6f201192bb332fc9dabcfdf3fa29e85c83c7f45/third_party_module/stdmodules/string.cppm#L28-L42
// Thank you, Chuanqi Xu, for finding the solution to this problem.
extern "C++"
{
	template class std::allocator<char>;
	template class std::allocator<wchar_t>;
}
#endif
