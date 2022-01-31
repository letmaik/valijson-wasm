#include <iostream>
#include "json_schema.h"
#include <emscripten/emscripten.h>

int main()
{
  std::cout << "Initialized." << std::endl;
}

extern "C"
{

EMSCRIPTEN_KEEPALIVE void main_emcc(char* input_json_c, char* schema_json_c)
{
  try
  {
    auto input_json = nlohmann::json::parse(input_json_c);
    auto schema_json = nlohmann::json::parse(schema_json_c);

    auto schema_error_msg = json::validate_json(input_json, schema_json);
    if (schema_error_msg.has_value())
    {
      std::cout << "Error validating JSON schema:" << std::endl;
      std::cout << schema_error_msg.value() << std::endl;
    }
    else
    {
      std::cout << "JSON Schema validation succeeded!" << std::endl;
    }
  }
  catch (std::exception& exc)
  {
    std::cout << "Error:" << std::endl;
    std::cout << exc.what() << std::endl;
  }
}

} // extern "C"
