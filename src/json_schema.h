// https://github.com/microsoft/CCF/blob/main/src/host/json_schema.h
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the Apache 2.0 License.
#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <sstream>
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/validator.hpp>

namespace json
{
  static std::optional<std::string> validate_json(
    const nlohmann::json& input_json, const nlohmann::json& schema_json)
  {
    valijson::Schema schema;
    valijson::SchemaParser parser;
    valijson::Validator validator;

    valijson::adapters::NlohmannJsonAdapter schema_adapter(schema_json);
    valijson::adapters::NlohmannJsonAdapter target_adapter(input_json);

    parser.populateSchema(schema_adapter, schema);

    valijson::ValidationResults results;
    if (!validator.validate(schema, target_adapter, &results))
    {
      std::stringstream validation_error_msg;
      valijson::ValidationResults::Error error;
      size_t error_num = 0;
      while (results.popError(error))
      {
        std::string error_ctx;
        for (auto const& c : error.context)
        {
          error_ctx += c;
        }
        validation_error_msg << "Error #" << error_num << std::endl;
        validation_error_msg << "  context: " << error_ctx << std::endl;
        validation_error_msg << "  message: " << error.description << std::endl;
        ++error_num;
      }
      return validation_error_msg.str();
    }

    return std::nullopt;
  }
}