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
 * */

#include "psme/rest-ref/endpoints/network_protocol.hpp"
#include "psme/rest-ref/constants/constants.hpp"
#include "json/json.hpp"
#include "configuration/configuration.hpp"
#include <map>

using namespace psme::rest;
using namespace app::rest;
using namespace app::rest::constants;
using namespace agent_framework::model::enums;

namespace {

namespace LocalLiterals {
    const char SERVER[] = "server";
    const char CONNECTORS[] = "connectors";
    const char PORT[] = "port";
    const char USE_SSL[] = "use-ssl";
}

json::Value make_prototype() {
    json::Value r(json::Value::Type::OBJECT);

    r[Common::ODATA_CONTEXT] = "/redfish/v1/$metadata#ManagerNetworkProtocol.ManagerNetworkProtocol";
    r[Common::ODATA_ID] = json::Value::Type::NIL;
    r[Common::ODATA_TYPE] = "#ManagerNetworkProtocol.1.0.0.ManagerNetworkProtocol";
    r[Common::ID] = json::Value::Type::NIL;
    r[Common::NAME] = "Manager Network Protocol";
    r[Common::DESCRIPTION] = "Manager Network Protocol description";
    r[Common::STATUS][Common::STATE] = json::Value::Type::NIL;
    r[Common::STATUS][Common::HEALTH] = json::Value::Type::NIL;
    r[Common::STATUS][Common::HEALTH_ROLLUP] = json::Value::Type::NIL;
    r[NetworkProtocol::HOST_NAME] = json::Value::Type::NIL;
    r[NetworkProtocol::FQDN] = json::Value::Type::NIL;
    r[NetworkProtocol::HTTP][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::HTTP][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::HTTPS][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::HTTPS][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::IPMI][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::IPMI][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::SSH][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::SSH][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::SNMP][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::SNMP][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::VIRTUAL_MEDIA][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::VIRTUAL_MEDIA][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::SSDP][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::SSDP][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::SSDP][NetworkProtocol::NOTIFY_IPV6_SCOPE] = json::Value::Type::NIL;
    r[NetworkProtocol::SSDP][NetworkProtocol::NOTIFY_MULTICAST_INTERVAL] = json::Value::Type::NIL;
    r[NetworkProtocol::SSDP][NetworkProtocol::NOTIFY_TTL] = json::Value::Type::NIL;
    r[NetworkProtocol::TELNET][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::TELNET][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[NetworkProtocol::KVMIP][NetworkProtocol::PROTOCOL_ENABLED] = json::Value::Type::NIL;
    r[NetworkProtocol::KVMIP][NetworkProtocol::PORT] = json::Value::Type::NIL;
    r[Common::OEM] = json::Value::Type::OBJECT;
    return r;
}

json::Value read_protocols_for_chassis_manager() {
    json::Value r{};
    r[constants::NetworkProtocol::HTTP][constants::NetworkProtocol::PROTOCOL_ENABLED] = true;
    r[constants::NetworkProtocol::HTTPS][constants::NetworkProtocol::PROTOCOL_ENABLED] = true;

    const json::Value connectors =
        configuration::Configuration::get_instance().
        to_json()[LocalLiterals::SERVER][LocalLiterals::CONNECTORS];

    for(const auto& connector : connectors) {
        if(connector[LocalLiterals::USE_SSL].as_bool()) {
            r[constants::NetworkProtocol::HTTPS][constants::NetworkProtocol::PORT] =
                connector[LocalLiterals::PORT].as_uint();
        } else {
            r[constants::NetworkProtocol::HTTP][constants::NetworkProtocol::PORT] =
                connector[LocalLiterals::PORT].as_uint();
        }
    }

    return r;
}

}

endpoint::NetworkProtocol::NetworkProtocol(const std::string& path) : Endpoint(path) {}
endpoint::NetworkProtocol::~NetworkProtocol() {}

void endpoint::NetworkProtocol::get(const server::Request& req, server::Response& res) {
    auto r = make_prototype();

    r[Common::ODATA_ID] = PathBuilder(req).build();
    r[Common::ID] = "NetworkProtocol";

    std::map<NetworkServiceName, std::string> service_name_to_rest_literal {
        {NetworkServiceName::HTTP, constants::NetworkProtocol::HTTP},
        {NetworkServiceName::HTTPS, constants::NetworkProtocol::HTTPS},
        {NetworkServiceName::VirtualMedia, constants::NetworkProtocol::VIRTUAL_MEDIA},
        {NetworkServiceName::SNMP, constants::NetworkProtocol::SNMP},
        {NetworkServiceName::Telnet, constants::NetworkProtocol::TELNET},
        {NetworkServiceName::SSDP, constants::NetworkProtocol::SSDP},
        {NetworkServiceName::IPMI, constants::NetworkProtocol::IPMI},
        {NetworkServiceName::SSH, constants::NetworkProtocol::SSH},
        {NetworkServiceName::KVMIP, constants::NetworkProtocol::KVMIP}
    };

    auto manager = psme::rest::endpoint::utils::get_manager(req.params[PathParam::MANAGER_ID]);
    for(const auto& service: manager.get_network_services()){
        r[service_name_to_rest_literal[service.get_name()]][constants::NetworkProtocol::PROTOCOL_ENABLED] = service.get_enabled();
        r[service_name_to_rest_literal[service.get_name()]][constants::NetworkProtocol::PORT] = service.get_port();
    }

    // drawer manager has HTTP & HTTPS enabled
    if ( ManagerInfoType::EnclosureManager == manager.get_manager_type()){
        r += read_protocols_for_chassis_manager();
    }

    set_response(res, r);
}
