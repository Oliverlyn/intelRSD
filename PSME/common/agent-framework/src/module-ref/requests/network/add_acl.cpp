/*!
 * @copyright
 * Copyright (c) 2016 Intel Corporation
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
 * @file requests/network/add_acl.cpp
 * @brief Network request AddAcl implementation
 * */

#include "agent-framework/module-ref/requests/network/add_acl.hpp"
#include "agent-framework/module-ref/constants/common.hpp"

#include <json/json.h>

using namespace agent_framework::model::requests;
using namespace agent_framework::model::literals;
using namespace agent_framework::model;

AddAcl::AddAcl(const std::string& switch_id,
               const attribute::Array<string>& ports,
               const attribute::Oem& oem):
    m_switch(switch_id),
    m_ports(ports),
    m_oem(oem) {}

Json::Value AddAcl::to_json() const {
    Json::Value value;
    value[Acl::SWITCH] = m_switch;
    value[Acl::PORTS] = m_ports.to_json();
    value[Acl::OEM] = m_oem.to_json();
    return value;
}

AddAcl AddAcl::from_json(const Json::Value& json) {
    return AddAcl{
        json[Acl::SWITCH].asString(),
        attribute::Array<string>::from_json(json[Acl::PORTS]),
        attribute::Oem::from_json(json[Acl::OEM])
    };
}
