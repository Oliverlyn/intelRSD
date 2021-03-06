/*!
 * @copyright
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file json_to_string_vector.cpp
 * @brief json to vector<string> converting function
 * */

#include "agent-framework/module-ref/utils/compute_hash.hpp"

extern "C" {
#include <md5/md5.h>
}
#include <json/json.h>

#include <vector>

namespace agent_framework {
namespace model {
namespace utils {

std::string compute_hash(const std::string& input) {
    std::vector<uint8_t> result;
    result.resize(16);

    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input.c_str(), input.size());
    MD5_Final(result.data(), &context);

    return std::string(result.cbegin(), result.cend());

}

std::string compute_hash(const Json::Value& json) {
    return compute_hash(json.toStyledString());
}

}
}
}
